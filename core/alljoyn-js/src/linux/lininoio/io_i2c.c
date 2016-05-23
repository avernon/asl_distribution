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

#define AJ_MODULE GPIO

#include <errno.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>

#include "ajs.h"
#include "ajs_io.h"

extern uint8_t dbgGPIO;

static const char i2c_dev[] = "/dev/i2c-0";

typedef struct {
    uint8_t addr;
    int fd;
} I2C_CONTEXT;

#ifndef NDEBUG
static const char* hex(const uint8_t* p, int len)
{
    static char buf[65];
    char* s = buf;

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
    I2C_CONTEXT* i2c = (I2C_CONTEXT*)ctx;
    int ret;

    if (addr != i2c->addr) {
        ret = ioctl(i2c->fd, I2C_SLAVE, addr);
        if (ret < 0) {
            AJ_ErrPrintf(("I2C_SLAVE IOCTL failed errno=%d\n", errno));
            return AJ_ERR_DRIVER;
        }
        i2c->addr = addr;
    }
    if (txBuf && txLen) {
        ret = write(i2c->fd, txBuf, txLen);
        if (ret < 0) {
            AJ_ErrPrintf(("I2C write failed errno=%d\n", errno));
            return AJ_ERR_DRIVER;
        }
        AJ_InfoPrintf(("I2C write sz=%d %s\n", txLen, hex(txBuf, txLen)));
    }
    if (rxBuf && rxLen) {
        ret = read(i2c->fd, rxBuf, rxLen);
        if (ret < 0) {
            AJ_ErrPrintf(("I2C read failed errno=%d\n", errno));
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
    I2C_CONTEXT* i2c;
    int fd;

    fd = open(i2c_dev, O_RDWR);
    if (fd < 0) {
        return AJ_ERR_DRIVER;
    }
    i2c = malloc(sizeof(I2C_CONTEXT));
    if (!i2c) {
        AJ_ErrPrintf(("AJS_TargetIO_PinOpen(): Malloc failed to allocate %d bytes\n", sizeof(I2C_CONTEXT)));
        return AJ_ERR_RESOURCES;
    }
    memset(i2c, 0, sizeof(I2C_CONTEXT));

    i2c->fd = fd;
    *ctx = i2c;

    return AJ_OK;
}

AJ_Status AJS_TargetIO_I2cClose(void* ctx)
{
    I2C_CONTEXT* i2c = (I2C_CONTEXT*)ctx;

    close(i2c->fd);
    free(ctx);

    return AJ_OK;
}
