/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

#ifndef _NOTIFICATIONCONSUMERSAMPLE_H_
#define _NOTIFICATIONCONSUMERSAMPLE_H_

#include <ajtcl/alljoyn.h>

#define CONSUMER_ACTION_NOTHING         0
#define CONSUMER_ACTION_DISMISS         1

/*
 * Functions that the application needs to implement
 */

/**
 * Initialize the Notification Service Consumer
 * @return status
 */
AJ_Status NotificationConsumer_Init();

/**
 * If idle, do work
 * @param busAttachment
 */
void NotificationConsumer_DoWork(AJ_BusAttachment* busAttachment);

/**
 * Finish Consumer - called when bus disconnects
 * @return status
 */
AJ_Status NotificationConsumer_Finish();

#endif /* _NOTIFICATIONCONSUMERSAMPLE_H_ */

