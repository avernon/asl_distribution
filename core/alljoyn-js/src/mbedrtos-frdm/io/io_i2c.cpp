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

#define MODE_MASTER 0
#define MODE_SLAVE  1

typedef struct {
    I2C* object;
    uint8_t curAddr;
}I2C_Pin;

typedef struct {
    uint8_t pinNum;     //Pin number from io_info.c
    uint16_t pinId;     //mbed pin ID (PTxxx)
    uint32_t function;  //SDA, SCL
} I2C_Info;

static I2C_Info i2cInfo[] = {
    { 17, PTE25, AJS_IO_FUNCTION_I2C_SDA },
    { 18, PTE24, AJS_IO_FUNCTION_I2C_SCL }
};

#ifndef NDEBUG
static const char* hex(const uint8_t* p, int len)
{
    static char buf[65];
    char*s = buf;

    if (p) {
        while (len--) {
            sprintf(s, "%02x", *p++);
            s += 2;
        }
    } else {
        *s = 0;
    }
    return buf;
}
#endif

AJ_Status AJS_TargetIO_I2cTransfer(void* ctx, uint8_t addr, uint8_t* txBuf, uint8_t txLen, uint8_t* rxBuf, uint8_t rxLen, uint8_t* rxBytes)
{
    I2C_Pin* i2c = (I2C_Pin*)ctx;
    int ret;

    if (addr != i2c->curAddr) {
        i2c->curAddr = addr;
    }
    if (txBuf && txLen) {
        ret = i2c->object->write(i2c->curAddr, (const char*)txBuf, txLen);
        if (ret < 0) {
            AJ_ErrPrintf(("I2C write failed\n"));
            return AJ_ERR_DRIVER;
        }
        AJ_InfoPrintf(("I2C write sz=%d %s\n", txLen, hex(txBuf, txLen)));
    }
    if (rxBuf && rxLen) {
        ret = i2c->object->read(i2c->curAddr, (char*)rxBuf, rxLen);
        if (ret < 0) {
            AJ_ErrPrintf(("I2C read failed\n"));
            return AJ_ERR_DRIVER;
        }
        AJ_InfoPrintf(("I2C read sz=%d %s\n", ret, hex(rxBuf, ret)));
        if (rxBytes) {
            *rxBytes = ret;
        }
    }
    return AJ_OK;
}

AJ_Status AJS_TargetIO_I2cOpen(uint8_t sda, uint8_t scl, uint32_t clock, uint8_t mode, uint8_t ownAddress, void** ctx)
{
    I2C_Pin* i2c;
    uint8_t indexSda, indexScl;
    uint8_t sdaPin = AJS_TargetIO_GetInfo(sda)->physicalPin;
    uint8_t sclPin = AJS_TargetIO_GetInfo(scl)->physicalPin;
    if (mode == MODE_SLAVE) {
        AJ_ErrPrintf(("Slave mode is currently not supported\n"));
        return AJ_ERR_INVALID;
    }

    for (indexSda = 0; indexSda < ArraySize(i2cInfo); indexSda++) {
        if (i2cInfo[indexSda].pinNum == sdaPin) {
            if (i2cInfo[indexSda].function != AJS_IO_FUNCTION_I2C_SDA) {
                AJ_ErrPrintf(("AJS_TargetIO_I2cOpen(): Pin %u does not support I2C SDA functionality\n", sda));
                return AJ_ERR_INVALID;
            }
            break;
        }
    }
    for (indexScl = 0; indexScl < ArraySize(i2cInfo); indexScl++) {
        if (i2cInfo[indexScl].pinNum == sclPin) {
            if (i2cInfo[indexScl].function != AJS_IO_FUNCTION_I2C_SCL) {
                AJ_ErrPrintf(("AJS_TargetIO_I2cOpen(): Pin %u does not support I2C SCL functionality\n", scl));
                return AJ_ERR_INVALID;
            }
            break;
        }
    }
    if (indexScl >= ArraySize(i2cInfo) || indexSda >= ArraySize(i2cInfo)) {
        AJ_ErrPrintf(("AJS_TargetIO_I2cOpen(): The pin(s) your trying to open dont exist\n"));
        return AJ_ERR_INVALID;
    }

    i2c = (I2C_Pin*)AJS_Alloc(NULL, sizeof(I2C_Pin));
    memset(i2c, 0, sizeof(I2C));

    i2c->object = new I2C((PinName)i2cInfo[indexSda].pinId, (PinName)i2cInfo[indexScl].pinId);
    i2c->object->frequency(clock);

    *ctx = i2c;

    return AJ_OK;
}

AJ_Status AJS_TargetIO_I2cClose(void* ctx)
{
    I2C_Pin* i2c = (I2C_Pin*)ctx;
    if (i2c) {
        if (i2c->object) {
            delete i2c->object;
        }
        AJS_Free(NULL, i2c);
    }
    return AJ_OK;
}
