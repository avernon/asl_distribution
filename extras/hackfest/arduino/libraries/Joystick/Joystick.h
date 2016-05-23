/**
 * @file
 * Arduino Joystick shield driver library.
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

#include "Arduino.h"


/**
 * This library implements a generic Joystick driver.  It uses the Timer 1
 * interrupt to perform the actual reads of the buttons and joystick position.
 * This allows for a simple debounce algorithm and allows for averaging analog
 * reads to get a more stable joystick position reading.  This should work
 * with any joystick shield with an analog joystick.
 */
class Joystick
{
  public:
    /**
     * Setup reading from a Joystick shield.
     *
     * @param xPin          Analog pin for the X axis.
     * @param yPin          Analog pin for the Y axis.
     * @param buttonMap     Array of digital I/O pins that map to buttons.
     * @param numButtons    Size of the button map.
     * @param pressInd      Set to 1 if pressing a button causes the digital
     *                      input to read as 1.  Set to 0 if pressing a button
     *                      causes the digital input to read as 0.
     */
    Joystick(uint8_t xPin, uint8_t yPin,
             uint16_t xMin, uint16_t xMax,
             uint16_t yMin, uint16_t yMax,
             const uint8_t* buttonMap, uint8_t numButtons, uint8_t pressInd);
    ~Joystick();

    void begin();
    void end();

    /**
     * Sets the ouput range for the X axis.
     *
     * @param left      Output value for maximal left position.
     * @param right     Output value for maximal right position.
     */
    void setXRange(int left, int right);

    /**
     * Sets the ouput range for the Y axis.
     *
     * @param up        Output value for maximal up position.
     * @param down      Output value for maximal down position.
     */
    void setYRange(int up, int down);

    void reset();


    /**
     * Indicates if the state of any of the buttons or joystick position has
     * changed since the last read.  Calling this function does not constitute
     * as a "read" so this function will continue to return true until either
     * the button or joystick axis that change gets read or the state of the
     * joystick shield is restored to its previous state.
     *
     * @return  1 if the state changed; 0 if the state has not changed.
     */
    int stateChanged(void);

    /**
     * Read the button state.  This returns a bitmap of which buttons are
     * pressed and which are not.  Bit 0 is the first button in the buttonMap
     * that was passed into the constructor.  Bit 1 is the second button inthe
     * buttonMap, and so on.  This will update the internal state change
     * detection logic for button press events.
     *
     * @return  Bitmap of the button press state.
     */
    uint8_t readButtons(void) { return pressIndNormalizer ^ buttonState; }

    /**
     * Read the joystick X axis value.
     *
     * @return  The X axis value.
     */
    int readXPos(void);
    int readRawXPos(void);

    /**
     * Read the joystick Y axis value.
     *
     * @return  The Y axis value.
     */
    int readYPos(void);
    int readRawYPos(void);


  private:

    struct AxisInfo {
        int calMin;
        int calMid;
        int calMax;

        int outMin;
        int outMax;

        AxisInfo(int calMin, int calMax, int outMin, int outMax):
            calMin(calMin),
            calMid((calMax - calMin) / 2),
            calMax(calMax),
            outMin(outMin),
            outMax(outMax)
        {
        }
        void setRange(int min, int max) { outMin = min; outMax = max; }
        int scaleAnalog(long val);
    };

    AxisInfo x;
    AxisInfo y;

    uint8_t buttonState;
    int oldXPos;
    int oldYPos;

    const uint8_t xPin;
    const uint8_t yPin;
    const uint8_t* buttonMap;
    const uint8_t numButtons;
    const uint16_t pressIndNormalizer;

    uint8_t* debounceSum;

};

#endif
