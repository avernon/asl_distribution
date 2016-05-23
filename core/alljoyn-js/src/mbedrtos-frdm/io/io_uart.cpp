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

#include "mbed.h"
#include "../../ajs.h"
#include "../../ajs_io.h"
#include "../../ajs_heap.h"

typedef struct {
    uint8_t pinNum;     //Pin number from io_info.c
    uint16_t pinId;     //Mbed pin ID
    uint32_t function;  //Pin function (TX or RX)
    uint8_t init;       //Flag specifying whether or not to init the pin
}UART_Info;

typedef struct {
    Serial* object;
}UART;

static UART_Info uartInfo[] = {
    { 1,  PTC16, AJS_IO_FUNCTION_UART_RX, false },
    { 2,  PTC17, AJS_IO_FUNCTION_UART_TX, false },
    { 38, PTC15, AJS_IO_FUNCTION_UART_RX, true  },
    { 39, PTC14, AJS_IO_FUNCTION_UART_TX, true  }
};

uint32_t AJS_TargetIO_UartRead(void* uartCtx, uint8_t* buf, uint32_t length)
{
    UART* uart = (UART*)uartCtx;
    uint32_t i = 0;
    while (i < length) {
        /* Check there is a character to read */
        if (uart->object->readable()) {
            buf[i] = uart->object->getc();
            i++;
        } else {
            break;
        }
    }
    return i;
}

AJ_Status AJS_TargetIO_UartWrite(void* uartCtx, uint8_t* data, uint32_t length)
{
    UART* uart = (UART*)uartCtx;
    uint32_t i = 0;
    while (i < length) {
        uart->object->putc(*(data + i));
        i++;
    }
    return AJ_OK;
}

/*
 * Debug print Serial object. If a user wants to print to the debug output they
 * have to use this one and not change any settings.
 */
extern Serial* pc;

AJ_Status AJS_TargetIO_UartOpen(uint8_t txPin, uint8_t rxPin, uint32_t baud, void** uartCtx)
{
    UART* uart;
    uint16_t pinTx, pinRx;
    uint16_t physicalTxPin = AJS_TargetIO_GetInfo(txPin)->physicalPin;
    uint16_t physicalRxPin = AJS_TargetIO_GetInfo(rxPin)->physicalPin;

    for (pinTx = 0; pinTx < ArraySize(uartInfo); ++pinTx) {
        if (uartInfo[pinTx].pinNum == physicalTxPin) {
            break;
        }
    }
    // Make sure the pin exists and its a TX pin
    if (pinTx >= ArraySize(uartInfo) || uartInfo[pinTx].function != AJS_IO_FUNCTION_UART_TX) {
        return AJ_ERR_INVALID;
    }
    for (pinRx = 0; pinRx < ArraySize(uartInfo); ++pinRx) {
        if (uartInfo[pinRx].pinNum == physicalRxPin) {
            break;
        }
    }
    // Make sure the pin exists and its an RX pin
    if (pinRx >= ArraySize(uartInfo) || uartInfo[pinRx].function != AJS_IO_FUNCTION_UART_RX) {
        return AJ_ERR_INVALID;
    }
    // Dont initialize the UART peripheral, just point the object to the current UART class
    if (uartInfo[pinTx].init == false || uartInfo[pinRx].init == false) {
        uart->object = pc;
        *uartCtx = uart;
        return AJ_OK;
    }
    uart = (UART*)AJS_Alloc(NULL, sizeof(UART));
    uart->object = new Serial((PinName)uartInfo[pinTx].pinId, (PinName)uartInfo[pinRx].pinId);
    uart->object->baud(baud);
    *uartCtx = uart;
    return AJ_OK;
}

AJ_Status AJS_TargetIO_UartClose(void* uartCtx)
{
    UART* uart = (UART*)uartCtx;
    if (uart) {
        if (uart->object) {
            delete uart->object;
        }
        AJS_Free(NULL, uart);
    }
    return AJ_OK;
}


