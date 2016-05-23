/**
 * @file
 */
/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Contributed by Qualcomm Connected Experiences, Inc.,
 *    with authorization from the AllSeen Alliance, Inc.
 *    
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *    
 *        http://www.apache.org/licenses/LICENSE-2.0
 *    
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *    
 *    Pursuant to Section 1 of the License, the work of authorship constituting
 *    a Work and any Contribution incorporated in the Work shall mean only that
 *    Contributor's code submissions authored by that Contributor.  Any rights
 *    granted under the License are conditioned upon acceptance of these
 *    clarifications.
 ******************************************************************************/
/******************************************************************************
 * This code statically links to code available from
 * http://www.st.com/web/en/catalog/tools/ and that code is subject to a license
 * agreement with terms and conditions that you will be responsible for from
 * STMicroelectronics if you employ that code. Use of such code is your responsibility.
 * Neither AllSeen Alliance nor any contributor to this AllSeen code base has any
 * obligations with respect to the STMicroelectronics code that to which you will be
 * statically linking this code. One requirement in the license is that the
 * STMicroelectronics code may only be used with STMicroelectronics processors as set
 * forth in their agreement."
 *******************************************************************************/

#include "io_common.h"

AJ_Status AJS_HW_TimerSet(uint32_t freq, void* context);

#define MAX_PWM_PINS 4

static GPIO* pwmPins[MAX_PWM_PINS];
static uint8_t pwmCount;

AJ_Status AllocPWM(GPIO* pin)
{
    size_t i;
    AJ_ASSERT(!pin->pwm.dutyCycle);
    for (i = 0; i < MAX_PWM_PINS; ++i) {
        if (!pwmPins[i]) {
            pwmPins[i] = pin;
            pin->pwm.count = 0;
            ++pwmCount;
            return AJ_OK;
        }
    }
    return AJ_ERR_RESOURCES;
}
void ReleasePWM(GPIO* pin)
{
    size_t i;
    for (i = 0; i < MAX_PWM_PINS; ++i) {
        if (pwmPins[i] == pin) {
            pwmPins[i] = NULL;
            pin->pwm.dutyCycle = 0;
            --pwmCount;
            break;
        }
    }
    if (pwmCount == 0) {
        AJS_HW_TimerSet(0, NULL);
    }
}
static uint8_t initialized = FALSE;

#define TIMER_CLK 21000000  //21 MHz

/*
 * The STM32 needs two values to initalize: pulse and period. They are dependent
 * on the duty cycle and frequency values passed in.
 *
 * pulse = DC (TIMER_CLK / (freq * 100))
 *
 * period = (TIMER_CLK / freq) - 1
 */

AJ_Status AJS_HW_TimerSet(uint32_t freq, void* context)
{
    GPIO_InitTypeDef timerGPIO;
    TIM_TimeBaseInitTypeDef timerBase;
    TIM_OCInitTypeDef timerInit;
    uint8_t pinSource;
    uint16_t prescaler;
    uint32_t pulse, period;

    GPIO* gpio = (GPIO*)context;
    if (freq == 0) {
        if (initialized) {
            TIM_Cmd(TIM3, DISABLE);
            TIM_DeInit(TIM3);
            //Stop the HW timer
            //Deinit the HW timer
        }
    }
    if (!initialized) {
        timerGPIO.GPIO_Pin = gpio->gpioPin;
        timerGPIO.GPIO_Mode = GPIO_Mode_AF;
        timerGPIO.GPIO_Speed = GPIO_Speed_100MHz;
        timerGPIO.GPIO_OType = GPIO_OType_PP;
        timerGPIO.GPIO_PuPd = GPIO_PuPd_UP;
        GPIO_Init(gpio->GPIOx, &timerGPIO);

        pinSource = pinToSource(gpio->gpioPin);

        GPIO_PinAFConfig(gpio->GPIOx, pinSource, GPIO_AF_TIM3);

        prescaler = (uint16_t)((SystemCoreClock / 2) / 28000000) - 1;
        period = (TIMER_CLK / freq) - 1;
        pulse = gpio->pwm.dutyCycle * (TIMER_CLK / (freq * 100));

        timerBase.TIM_ClockDivision = 0;
        timerBase.TIM_CounterMode = TIM_CounterMode_Up;
        timerBase.TIM_Period =  period;
        timerBase.TIM_Prescaler = prescaler;

        TIM_TimeBaseInit(TIM3, &timerBase);

        timerInit.TIM_OCMode = TIM_OCMode_PWM1;
        timerInit.TIM_OutputState = TIM_OutputState_Enable;
        //timerInit.TIM_Pulse = gpio->pwm.dutyCycle;
        timerInit.TIM_Pulse = pulse;
        timerInit.TIM_OCPolarity = TIM_OCPolarity_High;
        TIM_OC1Init(TIM3, &timerInit);
        TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);
        TIM_ARRPreloadConfig(TIM3, ENABLE);

        TIM_Cmd(TIM3, ENABLE);

        initialized = TRUE;
    } else {
        period = (TIMER_CLK / freq) - 1;
        pulse = gpio->pwm.dutyCycle * (TIMER_CLK / (freq * 100));
        TIM3->CCR1 = pulse;
        TIM3->ARR = period;
    }
}

AJ_Status AJS_TargetIO_PinPWM(void* pinCtx, double dutyCycle, uint32_t freq)
{
    AJ_Status status = AJ_OK;;
    GPIO* gpio = (GPIO*)pinCtx;
    uint8_t dc = (uint8_t)(dutyCycle * 100);

    if ((dc == 0) || (dc == 255)) {
        AJS_TargetIO_PinSet(pinCtx, dutyCycle);
        return AJ_OK;
    }
    if (!gpio->pwm.dutyCycle) {
        status = AllocPWM(gpio);
    }
    if (status == AJ_OK) {
        gpio->pwm.dutyCycle = dc;
        AJS_HW_TimerSet(freq, pinCtx);
    }
    return AJ_OK;
}
