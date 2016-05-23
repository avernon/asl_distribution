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

#ifndef IO_COMMON_H_
#define IO_COMMON_H_

#include "../../ajs.h"
#include "../../ajs_io.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_spi.h"
#include <ajtcl/aj_target_platform.h>
#include "stm32f4xx_adc.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_i2c.h"
#include "misc.h"

typedef struct {
    GPIO_TypeDef* GPIOx;    //STM32 GPIO structure
    uint16_t physicalPin;   //Pin x for GPIOx (1-12)
    uint8_t pinFunc;       //Alternate function
    uint16_t pinNum;        //MCU pin number (1-100)
}PIN_Info;

typedef struct {
    uint8_t trigId;             //Trigger ID
    GPIO_TypeDef* GPIOx;        //STM32 GPIO structure
    uint16_t gpioPin;           //Pin number for the gpio pin
    uint8_t gpioAF;             //Alternate function (SPI, UART, etc)
    struct {
        uint8_t dutyCycle;
        uint8_t count;
    } pwm;
} GPIO;
typedef struct {
    SPI_TypeDef* SPIx;
    GPIO_TypeDef* SS_GPIO;
    uint16_t SS_Pin;
}SPI_Pin;

typedef struct {
    void* SPIx;
    GPIO_TypeDef* GPIOx;
    uint16_t physicalPin;
    uint16_t pinNum;
}SPI_Info;

typedef struct {
    ADC_TypeDef* ADCx;
    uint8_t channel;
}ADC_Info;

typedef struct {
    uint16_t gpioPin;
    ADC_TypeDef* ADCx;
    GPIO_TypeDef* GPIOx;
    uint8_t flag;               //Used for the accelerometer
} ADC_pin;

static uint8_t pinIdToSource[15];

static const ADC_Info adcInfo[] = {
    { ADC1, ADC_Channel_1 },
    { ADC1, ADC_Channel_0 },
    { ADC1, ADC_Channel_15 },
    { ADC1, ADC_Channel_14 }
};

static const SPI_Info spiInfo[] = {
    { SPI2, GPIOC, GPIO_Pin_3, 18 },        //MOSI
    { SPI2, GPIOC, GPIO_Pin_2, 19 },        //MISO
    { SPI2, GPIOB, GPIO_Pin_10, 47 },       //SCK
    { SPI2, GPIOB, GPIO_Pin_12, 51 },       //SS
    { SPI2, GPIOB, GPIO_Pin_13, 52 },       //SCK
    { SPI2, GPIOB, GPIO_Pin_14, 53 },       //MISO
    { SPI2, GPIOB, GPIO_Pin_15, 54 },       //MOSI
    { SPI2, GPIOB, GPIO_Pin_9, 96 },        //SS
    { SPI1, GPIOE, GPIO_Pin_3, 2 },          //SS (accel)
    { SPI1, GPIOA, GPIO_Pin_5, 30 },        //SCK SPI1
    { SPI1, GPIOA, GPIO_Pin_7, 32 },        //MOSI SPI1
    { SPI1, GPIOA, GPIO_Pin_6, 31 }         //MISO SPI1
};

static uint8_t pinIdToSource[15];

static const PIN_Info pinInfo[] = {
    { GPIOD, GPIO_Pin_12, 0xFF,          59 },      //LED1
    { GPIOD, GPIO_Pin_13, 0xFF,          60 },      //LED2
    { GPIOD, GPIO_Pin_14, 0xFF,          61 },      //LED3
    { GPIOD, GPIO_Pin_15, 0xFF,          62 },      //LED4
    { GPIOA, GPIO_Pin_0,  0xFF,          23 },      //Push button
    { GPIOC, GPIO_Pin_6,  GPIO_AF_TIM3,  63 },      //PWM1
    { GPIOC, GPIO_Pin_7,  GPIO_AF_TIM3,  64 },      //PWM2
    { GPIOB, GPIO_Pin_0,  GPIO_AF_TIM3,  35 },      //PWM3
    { GPIOB, GPIO_Pin_1,  GPIO_AF_TIM3,  36 },      //PWM4
    { GPIOC, GPIO_Pin_1,  0xFF,          16 },      //ADC1
    { GPIOC, GPIO_Pin_0,  0xFF,          17 },      //ADC2
    { GPIOC, GPIO_Pin_5,  0xFF,          34 },      //ADC3
    { GPIOC, GPIO_Pin_4,  0xFF,          33 },      //ADC4 - Temp
    { 0,              0,  0xFF,          97 },      //Sudo ADC - MEMS X Axis
    { 0,              0,  0xFF,          98 },      //Sudo ADC - MEMS X Axis
    { 0,              0,  0xFF,          99 },      //Sudo ADC - MEMS X Axis
};

uint8_t pinToSource(uint16_t pin);

#endif /* IO_COMMON_H_ */
