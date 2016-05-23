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

#ifndef _APP_HANDLERS_H_
#define _APP_HANDLERS_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/services/ServicesCommon.h>

/**
 * Initialize the Services. called at the start of the application
 * @param aboutServicePort
 * @param deviceManufactureName
 * @param deviceProductName
 * @return aj_status
 */
AJ_Status AJServices_Init(uint16_t aboutServicePort, const char* deviceManufactureName, const char* deviceProductName);

/**
 * Run when the bus is connected to the Routing Node
 * application is idle
 * @param busAttachment
 * @param maxNumberOfAttempts - maximum number of attempts to initialize the services
 * @param sleepTimeBetweenAttempts - time in ms to sleep between attempts to initialize the services
 * @return aj_status for last request to Routing Node
 */
AJ_Status AJApp_ConnectedHandler(AJ_BusAttachment* busAttachment, uint8_t maxNumberOfAttempts, uint32_t sleepTimeBetweenAttempts);

/**
 * Process an incoming message
 * @param busAttachment
 * @param msg
 * @param status
 * @return servicestatus - shows if the message was processed or not
 */
AJSVC_ServiceStatus AJApp_MessageProcessor(AJ_BusAttachment* busAttachment, AJ_Message* msg, AJ_Status* status);

/**
 * Run when there is a timeout reading off the bus
 * application is idle
 * @param busAttachment
 */
void AJApp_DoWork(AJ_BusAttachment* busAttachment);

/**
 * Run when the bus is disconnecting from the Routing Node
 * Connection to Routing Node is either restarting or was stopped
 * @param busAttachment
 * @param restart
 * @return aj_status for last request to Routing Node
 */
AJ_Status AJApp_DisconnectHandler(AJ_BusAttachment* busAttachment, uint8_t restart);

#endif /* _APP_HANDLERS_H_ */
