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

#ifndef CONTROLPANELCLIENT_H_
#define CONTROLPANELCLIENT_H_

#include "ControlPanelClientGenerated.h"
#include "alljoyn/controlpanel/ControlPanelService.h"
#include "alljoyn/controlpanel/Definitions.h"
#include "aj_debug.h"

/**
 * Static non consts.
 */
char announceSender[16];

/**
 * Objects implemented by the application. The first member in the AJ_Object structure is the path.
 * The second is the collection of all interfaces at that path.
 */

#define CONTROLPANEL_APPOBJECTS \
    CONTROLPANELAPPOBJECTS
/*
   typedef enum _AJSVC_ServiceStatus {
    AJSVC_SERVICE_STATUS_HANDLED,       //!< SERVICE_STATUS_HANDLED
    AJSVC_SERVICE_STATUS_NOT_HANDLED,   //!< SERVICE_STATUS_NOT_HANDLED
   } AJSVC_ServiceStatus;
 */
void CPS_Init();

AJ_Status CPS_StartService(AJ_BusAttachment* bus, const char* daemonName, uint32_t timeout, uint8_t connected);

void MakeMethodCall(uint32_t sessionId);

void CPS_IdleConnectedHandler(AJ_BusAttachment*bus);

AJSVC_ServiceStatus CPS_NotifySessionAccepted(uint32_t sessionId, const char*sender);

AJSVC_ServiceStatus CPS_MessageProcessor(AJ_BusAttachment* bus, AJ_Message* msg, AJ_Status*msgStatus);

void CPS_Finish();

#endif //end CONTROLPANELCLIENT_H_
