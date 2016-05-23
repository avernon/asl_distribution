/**
 * @file
 * SPICom test
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

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

#include <aj_tutorial/display.h>

#define msleep(x) usleep((x) * 1000)

static const uint16_t alljoynBitmap[] = {
    0x0488, //  |   @  @   @   |
    0x0a88, //  |  @ @ @   @   |
    0x0e88, //  |  @@@ @   @   |
    0x0aee, //  |  @ @ @@@ @@@ |
    0x0000, //  |              |
    0x12a9, //  | @  @ @ @ @  @|
    0x154d, //  | @ @ @ @  @@ @|
    0x154b, //  | @ @ @ @  @ @@|
    0x2249  //  |@   @  @  @  @|
};

int main(void)
{
    Display display;
    uint8_t x;
    uint8_t y;

    printf("Draw ALLJOYN\n");
    display.DrawBitmap(alljoynBitmap);

    msleep(2000);
    display.ClearDisplayBuffer();
    printf("Draw points on\n");
    for (y = 0; y < 9; ++y) {
        for (x = 0; x < 14; x += (y + 1)) {
            display.DrawPoint(x, y);
            msleep(100);
        }
    }

    msleep(2000);
    display.ClearDisplayBuffer();
    printf("Draw lines\n");
    for (x = 0; x < 9; x += 2) {
        display.DrawLine(x, 0, 8 - x, 8);
        msleep(200);
        display.DrawLineBuffer(x, 0, 8 - x, 8, false);
    }
    for (y = 2; y < 9; y += 2) {
        display.DrawLine(8, y, 0, 8 - y);
        msleep(200);
        display.DrawLineBuffer(8, y, 0, 8 - y, false);
    }
    for (x = 0; x < 9; x += 2) {
        display.DrawLine(8 - x, 8, x, 0);
        msleep(200);
    }
    for (y = 2; y < 9; y += 2) {
        display.DrawLine(0, 8 - y, 8, y);
        msleep(200);
    }

    msleep(2000);
    display.ClearDisplayBuffer();
    printf("Draw boxes\n");
    display.DrawBox(0, 0, 13, 8, true, false);
    msleep(500);
    display.DrawBox(2, 2, 11, 6, true, true);
    msleep(500);
    display.DrawBox(0, 0, 13, 8, true, true);
    display.DrawBox(0, 0, 13, 8, false, false);
    msleep(500);
    display.DrawBox(2, 2, 11, 6, false, true);

    msleep(2000);
    display.DrawBoxBuffer(0, 0, 13, 8);
    printf("Draw points off\n");
    for (y = 0; y < 9; ++y) {
        for (x = 0; x < 14; x += (y + 1)) {
            display.DrawPoint(x, y, false);
            msleep(100);
        }
    }

    msleep(2000);
    display.DrawBoxBuffer(0, 0, 13, 8);
    printf("Draw lines off\n");
    for (x = 0; x < 9; x += 2) {
        display.DrawLine(x, 0, 8 - x, 8, false);
        msleep(200);
        display.DrawLineBuffer(x, 0, 8 - x, 8, true);
    }
    for (y = 2; y < 9; y += 2) {
        display.DrawLine(8, y, 0, 8 - y, false);
        msleep(200);
        display.DrawLineBuffer(8, y, 0, 8 - y, true);
    }
    for (x = 0; x < 9; x += 2) {
        display.DrawLine(8 - x, 8, x, 0, false);
        msleep(200);
    }
    for (y = 2; y < 9; y += 2) {
        display.DrawLine(0, 8 - y, 8, y, false);
        msleep(200);
    }

    msleep(2000);
    display.ClearDisplayBuffer();
    printf("Draw scores\n");
    for (int score = 0; score < 39; ++score) {
        display.DrawScoreBoard(score / 2 + (score % 2), score / 2, score % 2, !(score % 2));
        msleep(500);
    }

    msleep(2000);
    display.ClearDisplayBuffer();
    printf("Draw characters\n");
    static const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxyz.! ";
    for (size_t i = 0; i < sizeof(characters) - 1; ++i) {
        printf("%c\n", characters[i]);
        display.DrawCharacter(characters[i]);
        msleep(200);
    }


    msleep(2000);
    printf("Done\n");
    display.ClearDisplay();

    return 0;
}
