/**
 * @file
 * Arduino Joystick shield communications
 */

/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <aj_tutorial/joystick.h>
#if defined(HOST_BUILD)
#include <stdlib.h>
#else
#include <aj_tutorial/smsg.h>
#endif


#define CMD_BUF_SIZE 5

enum {
    JS_EVENT,
    SET_X_RANGE,
    SET_Y_RANGE,
    RESET
};

#if defined(HOST_BUILD)
static int16_t rangeLeft = 0;
static int16_t rangeRight = 1024;
static int16_t rangeUp = 0;
static int16_t rangeDown = 1024;
#endif

bool Joystick::ReadJoystick(uint16_t& buttons, int16_t& x, int16_t& y)
{
#if defined(HOST_BUILD)
    usleep(1000 * (random() % 3000 + 100));
    x = random() % (rangeRight - rangeLeft) + rangeLeft;
    y = random() % (rangeDown - rangeUp) + rangeUp;
    buttons = random() & 0xffff;
#else
    uint8_t buf[7];
    int ret;

    ret = smsg.Read(buf, sizeof(buf));
    if ((ret != sizeof(buf)) || (buf[0] != JS_EVENT)) {
        return false;
    }
    buttons = (buf[1] << 8) | buf[2];
    x = (buf[3] << 8) | buf[4];
    y = (buf[5] << 8) | buf[6];
#endif

    return true;
}

bool Joystick::SetOutputRange(int16_t left, int16_t right, int16_t up, int16_t down)
{
#if defined(HOST_BUILD)
    rangeLeft = left;
    rangeRight = right;
    rangeUp = up;
    rangeDown = down;

    return true;
#else
    return (SendSetCmd(SET_X_RANGE, left, right) &&
            SendSetCmd(SET_Y_RANGE, up, down));
#endif
}

bool Joystick::ResetRange()
{
#if defined(HOST_BUILD)
    rangeLeft = 0;
    rangeRight = 1024;
    rangeUp = 0;
    rangeDown = 1024;

    return true;
#else

    uint8_t cmd = RESET;
    return (smsg.Write(&cmd, sizeof(cmd)) != 1);
#endif
}

bool Joystick::SendSetCmd(uint8_t cmd, int16_t i1, int16_t i2)
{
#if defined(HOST_BUILD)
    return true;
#else
    uint8_t buf[CMD_BUF_SIZE];
    buf[0] = cmd;
    buf[1] = i1 >> 8;
    buf[2] = i1 & 0xff;
    buf[3] = i2 >> 8;
    buf[4] = i2 & 0xff;
    int ret = smsg.Write(buf, sizeof(buf));
    usleep(2000);
    return (ret == CMD_BUF_SIZE);
#endif
}
