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

#include "../../ajs.h"
#include "../../ajs_io.h"

AJ_Status AJS_TargetIO_AdcOpen(uint16_t channel, void** adcCtx)
{
    return AJ_ERR_UNEXPECTED;
}

AJ_Status AJS_TargetIO_AdcClose(void* adcCtx)
{
    return AJ_ERR_UNEXPECTED;
}

uint32_t AJS_TargetIO_AdcRead(void* adcCtx)
{
    return 0;
}

AJ_Status AJS_TargetIO_DacOpen(uint16_t pin, void** dacCtx)
{
    return AJ_ERR_UNEXPECTED;
}

AJ_Status AJS_TargetIO_DacClose(void* dacCtx)
{
    return AJ_ERR_UNEXPECTED;
}

void AJS_TargetIO_DacWrite(void* dacCtx, uint32_t val)
{
}
AJ_Status AJS_TargetIO_SpiRead(void* ctx, uint32_t length, uint8_t* buffer)
{
    AJ_InfoPrintf(("AJS_TargetIO_SpiRead()"));
    return AJ_ERR_UNEXPECTED;
}
void AJS_TargetIO_SpiWrite(void* ctx, uint8_t* data, uint32_t length)
{
    AJ_InfoPrintf(("AJS_TargetIO_SpiWrite(): Wrote %i\n", data));
    return;
}
AJ_Status AJS_TargetIO_SpiOpen(uint8_t mosi, uint8_t miso, uint8_t cs, uint8_t clk, uint32_t prescaler,
                               uint8_t master, uint8_t cpol, uint8_t cpha, uint8_t data, void** spiCtx)
{
    return AJ_ERR_UNEXPECTED;
}
AJ_Status AJS_TargetIO_SpiClose(void* spiCtx)
{
    return AJ_ERR_UNEXPECTED;
}
uint32_t AJS_TargetIO_UartRead(void* uartCtx, uint8_t* buf, uint32_t length)
{
    AJ_InfoPrintf(("AJS_TargetIO_UartRead()"));
    return 0;
}
AJ_Status AJS_TargetIO_UartWrite(void* uartCtx, uint8_t* data, uint32_t length)
{
    AJ_InfoPrintf(("AJS_TargetIO_UartWrite(): Wrote %u bytes\n", length));
    return 0;
}
AJ_Status AJS_TargetIO_UartOpen(uint8_t txPin, uint8_t rxPin, uint32_t baud, void** uartCtx)
{
    return 0;
}
AJ_Status AJS_TargetIO_UartClose(void* uartCtx)
{
    return AJ_ERR_UNEXPECTED;
}

AJ_Status AJS_TargetIO_I2cOpen(uint8_t sda, uint8_t scl, uint32_t clock, uint8_t mode, uint8_t ownAddress, void** ctx)
{
    return AJ_ERR_UNEXPECTED;
}

AJ_Status AJS_TargetIO_I2cClose(void* ctx)
{
    return AJ_ERR_UNEXPECTED;
}

AJ_Status AJS_TargetIO_I2cTransfer(void* ctx, uint8_t addr, uint8_t* txBuf, uint8_t txLen, uint8_t* rxBuf, uint8_t rxLen, uint8_t* rxBytes)
{
    return AJ_ERR_UNEXPECTED;
}
