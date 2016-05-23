/**
 * @file
 * Arduino LOL shield driver library.
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

#ifndef _LOL_DRIVER_H_
#define _LOL_DRIVER_H_

#include <Arduino.h>

class _LOL
{
  public:
    _LOL();
    ~_LOL();

    /**
     * Must be called in setup() to register display interrupt.
     */
    void begin();

    /**
     * Thsi stops the display interrupt.  This must be called when the Linux
     * side is rebooting otherwise the Linux side may hang during boot.
     */
    void end();

    /**
     * Renders the bitmap onto the LOL display.  The bitmap is an array of 9
     * uint16's.  Each uint16 represents one rout of LEDs.  Only the lower 14
     * bits of each uint16 is relevant for display.  The upper 2 bits are
     * ignored.  bitmap[0] represents the top row while bitmap[8] represents
     * the bottom row.  Bit 0 represents the right most column while bit 13
     * represents the left most column.  Orientation is based on digital I/O
     * pins are at the top of the board and the analog pins are at the bottom
     * of the board.
     *
     * @param bitmap    Bitmap image to be displayed.
     */
    void render(const uint16_t* bitmap);
};

extern _LOL LOL;

#endif
