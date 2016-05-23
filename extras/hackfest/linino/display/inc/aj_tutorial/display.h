/**
 * @file
 * Arduino LOL shield communications
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

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <stdint.h>
#include <string.h>

#if !defined(HOST_BUILD)
#include <aj_tutorial/smsg.h>
#endif

class Display
{
  public:
    Display();
    ~Display() { }

#if !defined(HOST_BUILD)
    /**
     * Get access to the underlying file descriptor used to communicate with
     * the LOL driver sketch running on the Arduino.  Only use this file
     * descriptor with select() or epoll().  Use the methods in this class for
     * actual communication.
     *
     * @return  file descriptor
     */
    int GetFD() const { return smsg.GetFD(); }
#endif

    /**
     * Clear the display (all LEDs off).
     *
     * @return  true if successfully cleared, false otherwise (communication error)
     */
    bool ClearDisplayBuffer();
    bool ClearDisplay() { return ClearDisplayBuffer() && SendDisplay(); }

    /**
     * Turn an individual LED on or off.
     *
     * @param x     X coordinate to turn on/off
     * @param y     y coordinate to turn on/off
     * @param on    whether to turn the LED on or off (default = on)
     *
     * @return  true if successfully drawn, false otherwise (bad coordinate or communication error)
     */
    bool DrawPointBuffer(uint8_t x, uint8_t y, bool on = true);
    bool DrawPoint(uint8_t x, uint8_t y, bool on = true) { return DrawPointBuffer(x, y, on) && SendDisplay(); }

    /**
     * Turns a line of LEDs on or off.
     *
     * @param x1    X coordinate of the start of the line to turn on/off
     * @param y1    y coordinate of the start of the line to turn on/off
     * @param x2    X coordinate of the end of the line to turn on/off
     * @param y2    y coordinate of the end of the line to turn on/off
     * @param on    whether to turn the LED on or off (default = on)
     *
     * @return  true if successfully drawn, false otherwise (bad coordinate or communication error)
     */
    bool DrawLineBuffer(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool on = true);
    bool DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool on = true)
    {
        return DrawLineBuffer(x1, y1, x2, y2, on) && SendDisplay();
    }

    /**
     * Turns a box of LEDs on or off.
     *
     * @param x1    X coordinate of one corner the box to turn on/off
     * @param y1    y coordinate of one corner the box to turn on/off
     * @param x2    X coordinate of the opposite corner of the box to turn on/off
     * @param y2    y coordinate of the opposite corner of the box to turn on/off
     * @param on    whether to turn the LED on or off (default = on)
     * @param fill  whether to draw just the outline of the box or the full box (default = full box)
     *
     * @return  true if successfully drawn, false otherwise (bad coordinate or communication error)
     */
    bool DrawBoxBuffer(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool on = true, bool fill = true);
    bool DrawBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool on = true, bool fill = true)
    {
        return DrawBoxBuffer(x1, y1, x2, y2, on, fill) && SendDisplay();
    }

    /**
     * Sends a bitmap directly to the LOL shield for display.
     *
     * @param bitmap    Array of 9 uint16_t's with the bitmap to display where
     *                  bitmap[0] is the top line, bitmap[8] is the bottom line
     *                  and bit 0 is the right most edge and bit 13 is the left
     *                  most edge.
     *
     * @return  true if successfully drawn, false otherwise (communication error)
     */
    bool DrawBitmapBuffer(const uint16_t* bitmap);
    bool DrawBitmap(const uint16_t* bitmap) { return DrawBitmapBuffer(bitmap) && SendDisplay(); }

    /**
     * Draw a score board.  Scores can range in value from 0 to 19.  Either
     * the right or left side of the score board can be highlighed by
     * inverting which LEDs are on/off.
     *
     * @param left              The left hand score
     * @param right             The right hand score
     * @param highlightLeft     Highlight the left hand score
     * @param highlightRight    Highlight the right hand score
     *
     * @return  true if successfully drawn, false otherwise (communication error)
     */
    bool DrawScoreBoardBuffer(uint8_t left, uint8_t right, bool highlightLeft = true, bool highlightRight = true);
    bool DrawScoreBoard(uint8_t left, uint8_t right, bool highlightLeft = true, bool highlightRight = true)
    {
        return DrawScoreBoardBuffer(left, right, highlightLeft, highlightRight) && SendDisplay();
    }

    /**
     * Draw a single character on the display.
     *
     * @param c     The character to display (if there is no character for it a '.' will be displayed.
     *
     * @return  true if successfully drawn, false otherwise (communication error)
     */
    bool DrawCharacterBuffer(char c);
    bool DrawCharacter(char c) { return DrawCharacterBuffer(c) && SendDisplay(); }

    /**
     * Save a copy of the display current display bitmap image into a buffer.
     *
     * @param bitmapBuffer  Pointer to an array of at lease 9 uint16_t's to store the display bitmap
     */
    void SaveDisplayBitmap(uint16_t* bitmapBuffer) const
    {
        memcpy(bitmapBuffer, display, sizeof(display));
    }

    /**
     * Send the display buffer to the Arduino side for display.
     *
     * @return  true if successfully sent, false otherwise (communication error)
     */
    bool SendDisplay();

  private:
#if !defined(HOST_BUILD)
    SMsg smsg;
#endif
    uint16_t display[9];

    void _DrawPoint(uint8_t x, uint8_t y, bool on);
};

#endif
