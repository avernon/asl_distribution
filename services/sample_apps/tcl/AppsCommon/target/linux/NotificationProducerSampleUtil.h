/******************************************************************************
 * Copyright (c) 2013 - 2014, AllSeen Alliance. All rights reserved.
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

#ifndef PRODUCER_SAMPLE_UTIL_H_
#define PRODUCER_SAMPLE_UTIL_H_

#include <alljoyn.h>

#define MESSAGES_INTERVAL 60000

void Producer_SetupEnv(uint8_t* inputMode);
void Producer_GetNotificationFromUser(AJNS_NotificationContent* notificationContent, uint16_t* messageType, uint32_t* ttl, uint32_t* nextMessageTime);
void Producer_GetShouldDeleteNotificationFromUser(AJ_BusAttachment* busAttachment, uint8_t* delMsg, uint16_t* delMsgType);
void Producer_FreeNotification(AJNS_NotificationContent* notificationContent);
#endif /* PRODUCER_SAMPLE_UTIL_H_ */

