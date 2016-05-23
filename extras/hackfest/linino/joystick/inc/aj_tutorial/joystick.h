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

#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include <stdint.h>

#if !defined(HOST_BUILD)
#include <aj_tutorial/smsg.h>
#endif

class Joystick
{
  public:
    Joystick() { }
    ~Joystick() { }

#if !defined(HOST_BUILD)
    /**
     * Get access to the underlying file descriptor used to communicate with
     * the joystick driver sketch running on the Arduino.  Only use this file
     * descriptor with select() or epoll().  Use the methods in this class for
     * actual communication.
     *
     * @return  file descriptor
     */
    int GetFD() const { return smsg.GetFD(); }
#endif

    /**
     * Read event data from the joystick.
     *
     * @param[out] buttons  Bit map of which buttons are pressed.
     * @param[out] x        X position of the joystick
     * @param[out] y        Y position of the joystick
     *
     * @return  true if successfully read, false otherwise (probably communication error)
     */
    bool ReadJoystick(uint16_t& buttons, int16_t& x, int16_t& y);

    /**
     * Set the output range of the joystick position.  This just sets a
     * conversion of the joystick output to convenient values.  In other
     * words, you can set the output range to be from -10 to +10 even though
     * the raw analog values are from 3 to 998.
     *
     * @param left      Output value when joystick is fully left.
     * @param right     Output value when joystick is fully right.
     * @param up        Output value when joystick is fully up.
     * @param down      Output value when joystick is fully down.
     *
     * @return  true if successfully set, false otherwise (probably communication error)
     */
    bool SetOutputRange(int16_t left, int16_t right, int16_t up, int16_t down);

    /**
     * This defaults the calibration and output ranges to 0 to 1023.
     */
    bool ResetRange();

  private:
#if !defined(HOST_BUILD)
    SMsg smsg;
#endif

    bool SendSetCmd(uint8_t cmd, int16_t i1, int16_t i2);
    bool SendGetCmd(uint8_t cmd, int16_t& i1, int16_t& i2);
};

#endif
