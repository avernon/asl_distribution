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

SMsg smsg;

void setup() {
  Serial.begin(9600);
  smsg.begin();
}

void invert(byte* buffer, int size)
{
  while (size > 0) {
    --size;
    buffer[size] = ~buffer[size];
  }
}

void loop() {
  if (smsg.available()) {
    byte buffer[SMsg::MAX_MSG_LEN];
    int ret;
    memset(buffer, 0, sizeof(buffer));
    ret = smsg.read(buffer, sizeof(buffer));
    Serial.print("ret = ");
    Serial.println(ret, DEC);
    if (ret > 0) {
      invert(buffer, ret);
      delay(500);
      smsg.write(buffer, ret);
    }
  }
}

