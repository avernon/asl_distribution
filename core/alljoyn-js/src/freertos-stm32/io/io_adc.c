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

uint32_t AJS_TargetIO_AdcRead(void* adcCtx)
{
    ADC_pin* adc = (ADC_pin*)adcCtx;

    // Regular ADC read
    ADC_SoftwareStartConv(ADC1); //Start the conversion
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);   //Processing the conversion
    return ADC_GetConversionValue(ADC1); //Return the converted data
}
AJ_Status AJS_TargetIO_AdcOpen(uint16_t pinIndex, void** adcCtx)
{
    ADC_InitTypeDef adc_init;
    ADC_CommonInitTypeDef adc_common;
    GPIO_InitTypeDef gpio_init;
    uint8_t adc_channel;
    ADC_pin* adc;


    uint16_t physicalPin = AJS_TargetIO_GetInfo(pinIndex)->physicalPin;
    size_t channel;

    for (channel = 0; channel < ArraySize(pinInfo); ++channel) {
        if (pinInfo[channel].pinNum == physicalPin) {
            break;
        }
    }
    if (channel >= ArraySize(pinInfo)) {
        return AJ_ERR_INVALID;
    }
    adc = AJS_Alloc(NULL, sizeof(ADC));
    memset(adc, 0, sizeof(ADC));
    adc->gpioPin = pinInfo[channel].physicalPin;
    adc->GPIOx = pinInfo[channel].GPIOx;
    /*
     * Enable ADC Clocks and find what channel the pin is on
     */
    switch (pinInfo[channel].pinNum) {
    case (16):
        adc->ADCx = ADC1;
        adc_channel = ADC_Channel_11;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
        break;

    case (17):
        adc->ADCx = ADC1;
        adc_channel = ADC_Channel_12;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
        break;

    case (34):
        adc->ADCx = ADC1;
        adc_channel = ADC_Channel_15;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
        break;

    case (33):
        //Temperature sensor
        adc->ADCx = ADC1;
        adc_channel = ADC_Channel_TempSensor;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
        ADC_TempSensorVrefintCmd(ENABLE);
        break;

    default:
        AJ_ErrPrintf(("ADC is not supported for pin %u\n", pinInfo[channel].physicalPin));
        return AJ_ERR_INVALID;
    }

    gpio_init.GPIO_Pin = adc->gpioPin;
    gpio_init.GPIO_Mode = GPIO_Mode_AN;
    gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init(adc->GPIOx, &gpio_init);

    /* Put everything back to power-on defaults */
    ADC_DeInit();
    ADC_CommonStructInit(&adc_common);
    adc_common.ADC_Mode = ADC_Mode_Independent;
    adc_common.ADC_Prescaler = ADC_Prescaler_Div8;
    adc_common.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    adc_common.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;

    ADC_CommonInit(&adc_common);

    ADC_StructInit(&adc_init);
    adc_init.ADC_Resolution = ADC_Resolution_12b;
    adc_init.ADC_ScanConvMode = DISABLE;
    adc_init.ADC_ContinuousConvMode = ENABLE;
    adc_init.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    adc_init.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    adc_init.ADC_DataAlign = ADC_DataAlign_Right;
    adc_init.ADC_NbrOfConversion = 1;

    ADC_Init(adc->ADCx, &adc_init);

    ADC_RegularChannelConfig(adc->ADCx, adc_channel, 1, ADC_SampleTime_144Cycles);

    ADC_Cmd(adc->ADCx, ENABLE);

    *adcCtx = (void*)adc;

    return AJ_OK;
}
