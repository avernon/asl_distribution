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

#include <aj_tutorial/joystick.h>

#define BUTTON_A (1 << 0)
#define BUTTON_B (1 << 1)
#define BUTTON_C (1 << 2)
#define BUTTON_D (1 << 3)
#define BUTTON_E (1 << 4)
#define BUTTON_F (1 << 5)
#define BUTTON_G (1 << 6)

#define JS_BUTTON BUTTON_C

int main(void)
{
    Joystick js;
    bool done = false;
    uint16_t oldbuttons = 0;

    printf("Press and release Joystick button to exit.\n");

    while (!done) {
        uint16_t buttons;
        int16_t x;
        int16_t y;
        if (js.ReadJoystick(buttons, x, y)) {
            printf("x: %d   y: %d   buttons:", x, y);
            if (buttons & BUTTON_A) printf(" A");
            if (buttons & BUTTON_B) printf(" B");
            if (buttons & BUTTON_C) printf(" C");
            if (buttons & BUTTON_D) printf(" D");
            if (buttons & BUTTON_E) printf(" E");
            if (buttons & BUTTON_F) printf(" F");
            if (buttons & BUTTON_G) printf(" G");
            if (buttons & JS_BUTTON) printf(" Joystick");
            printf("\n");

            if (!(buttons & JS_BUTTON) && (oldbuttons & JS_BUTTON)) {
                done = true;
            }
            if ((buttons & BUTTON_A) && !(oldbuttons & BUTTON_A)) {
                js.SetOutputRange(-16, 16, -16, 16);
            }
            if ((buttons & BUTTON_B) && !(oldbuttons & BUTTON_B)) {
                js.ResetRange();
            }
            if ((buttons & BUTTON_G) && !(oldbuttons & BUTTON_G)) {
                js.SetOutputRange(-1, 1, -1, 1);
            }
            if ((buttons & BUTTON_F) && !(oldbuttons & BUTTON_F)) {
                js.SetOutputRange(10, 0, 0, 10);
            }
            if ((buttons & BUTTON_D) && !(oldbuttons & BUTTON_D)) {
                js.SetOutputRange(-10, 0, 0, -10);
            }
            oldbuttons = buttons;
        } else {
            printf("JS read failed\n");
        }
    }

    return 0;
}
