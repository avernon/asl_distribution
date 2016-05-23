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

#include <Joystick.h>


//const uint8_t buttonMap[]= { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
const uint8_t buttonMap[]= { 3, 4, 5, 6, 7, 8, 9 };
//const uint8_t buttonMap[]= { 7, 3, 4, 5, 6 };

Joystick js(A1, A0, 0, 996, 0, 996,
            buttonMap, sizeof(buttonMap) / sizeof(buttonMap[0]), 0);

int printnow = 0;
int printinterval = 1000;

void setup() {
  Serial.begin(9600);
  js.begin();
  js.setXRange(-16, 16);
  js.setYRange(-16, 16);
  printnow = millis() + printinterval;
}


void loop() {
  int now = millis();
  if (js.stateChanged() && (now - printnow > 0)) {
    printnow = now + printinterval;
    int i;
    int xpos = js.readXPos();
    int ypos = js.readYPos();
    int xraw = js.readRawXPos();
    int yraw = js.readRawYPos();
    unsigned short buttons = js.readButtons();
    Serial.print("x: ");
    Serial.print(xpos);
    Serial.print(" (");
    Serial.print(xraw);
    Serial.print(")   y: ");
    Serial.print(ypos);
    Serial.print(" (");
    Serial.print(yraw);
    Serial.print(")   buttons[");
    Serial.print(sizeof(buttonMap) / sizeof(buttonMap[0]));
    Serial.print("]:");
    for (i = 0; i < (sizeof(buttonMap) / sizeof(buttonMap[0])); ++i)
    {
      if (bitRead(buttons, i)) {
        Serial.write(' ');
        Serial.print(i);
        Serial.write(':');
        Serial.print(buttonMap[i]);
      }
    }
    Serial.println();
  }
}
