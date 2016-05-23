/**
 * @file
 * AllJoyn Joystick/Display common bits
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

#ifndef _AJ_COMMON_H_
#define _AJ_COMMON_H_

#include <alljoyn/BusAttachment.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/Session.h>
#include <alljoyn/SessionPortListener.h>


#define BUTTON_A (1 << 0)
#define BUTTON_B (1 << 1)
#define BUTTON_C (1 << 2)
#define BUTTON_D (1 << 3)
#define BUTTON_E (1 << 4)
#define BUTTON_F (1 << 5)
#define BUTTON_G (1 << 6)

#define JS_BUTTON BUTTON_C


extern const char* JS_SERVICE_NAME;
extern const ajn::SessionPort JS_SERVICE_PORT;
extern const char* JS_SERVICE_PATH;
extern const char* JS_INTERFACE_NAME;

void SetupSignalHandlers();
void WaitForQuit();
bool CreateInterface(ajn::BusAttachment& bus);
bool SetupAllJoyn(ajn::BusAttachment& bus,
                  ajn::BusListener& bListener,
                  ajn::BusObject* object,
                  ajn::SessionPortListener* spListener);

#endif
