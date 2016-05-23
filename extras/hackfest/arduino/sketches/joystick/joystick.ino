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
#include <SMsg.h>

#define CMD_BUF_SIZE 5

enum {
  JS_EVENT,
  SET_X_RANGE,
  SET_Y_RANGE,
  RESET,
  INVALID
};


const uint8_t buttonMap[]= { 7, 6, 5, 4, 3, 8, 9 };
Joystick js(A1, A0, 0, 990, 0, 990,
            buttonMap, sizeof(buttonMap) / sizeof(buttonMap[0]), 0);

SMsg smsg;

void setup() {
  Serial.begin(115200);
  smsg.begin();
  js.begin();
}


void loop() {
  if (smsg.available()) {
    byte buf[CMD_BUF_SIZE];
    buf[0] = INVALID;
    int ret = smsg.read(buf, sizeof(buf));
    if (ret < 1) {
      if (smsg.linuxRebooting()) {
        js.end();
        Serial.println("Linino is rebooting - everything is paused for up to 2 minutes...");
        smsg.waitLinuxBoot();
        Serial.println("reboot done");
        js.reset();
        js.begin();
      }
      return;
    }
    processCommand(buf, ret);
  }
  if (js.stateChanged()) {
    byte buf[7];
    int x = js.readXPos();
    int y = js.readYPos();
    unsigned short b = js.readButtons();
    buf[0] = JS_EVENT;
    buf[1] = b >> 8;
    buf[2] = b & 0xff;
    buf[3] = x >> 8;
    buf[4] = x & 0xff;
    buf[5] = y >> 8;
    buf[6] = y & 0xff;
    smsg.write(buf, sizeof(buf));
  }
}

void processCommand(byte* buf, uint8_t bufSize)
{
  int16_t i1 = ((int16_t)buf[1] << 8) | buf[2];
  int16_t i2 = ((int16_t)buf[3] << 8) | buf[4];
  switch (buf[0]) {
    case SET_X_RANGE:
      if (bufSize == 5) {
        Serial.println("Set X range");
        js.setXRange(i1, i2);
      }
      break;

    case SET_Y_RANGE:
      if (bufSize == 5) {
        Serial.println("Set Y range");
        js.setYRange(i1, i2);
      } else {
        Serial.print("invalid buf size for set Y: ");
        Serial.println(bufSize);
      }
      break;

    case RESET:
      if (bufSize == 1) {
        Serial.println("Reset");
        js.reset();
      }
      break;
    
    default:
      Serial.println("Invalid command");
      break;
  }
}

