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

/**
 * Per-module definition of the current module for debug logging.  Must be defined
 * prior to first inclusion of aj_debug.h.
 * The corresponding flag dbgAJSVCAPP is defined in the containing sample app.
 */
#define AJ_MODULE AJSVCAPP
#include <aj_debug.h>

#include <alljoyn/controlpanel/ControlPanelService.h>
#include "ControlPanelProvided.h"
#include "ControlPanelGenerated.h"
#include "ControlPanelSample.h"
#include <aj_link_timeout.h>

#ifndef NDEBUG
extern AJ_EXPORT uint8_t dbgAJSVCAPP;
#endif

AJ_Status Controlee_Init()
{
    AJ_Status status = AJCPS_Start(&GeneratedMessageProcessor, &IdentifyMsgOrPropId, &IdentifyMsgOrPropIdForSignal, &IdentifyRootMsgOrPropId);
    WidgetsInit();
    return status;
}

void Controlee_DoWork(AJ_BusAttachment* busAttachment)
{
    uint8_t sendUpdates = checkForUpdatesToSend();
    if (sendUpdates > 0) {

        // 0001 == need to update the temperature text field
        // 0010 == need to update the status text field
        // 0100 == need to update the state of temperature selector
        // 1000 == need to update the state of fan speed selector

        if ((sendUpdates & (1 << 0)) != 0) {
            AJ_AlwaysPrintf(("##### Sending update signal: temperature string field \n"));
            AJCPS_SendPropertyChangedSignal(busAttachment, EN_MYDEVICE_CURRENTTEMPSTRINGPROPERTY_SIGNAL_VALUE_CHANGED, AJCPS_GetCurrentSessionId());
        }
        if ((sendUpdates & (1 << 1)) != 0) {
            AJ_AlwaysPrintf(("##### Sending update signal: status string field \n"));
            AJCPS_SendPropertyChangedSignal(busAttachment, EN_MYDEVICE_STATUSSTRINGPROPERTY_SIGNAL_VALUE_CHANGED, AJCPS_GetCurrentSessionId());
        }
        if ((sendUpdates & (1 << 2)) != 0) {
            AJ_AlwaysPrintf(("##### Sending update signal: temperature selector state \n"));
            AJCPS_SendPropertyChangedSignal(busAttachment, EN_MYDEVICE_SET_TEMPERATURE_SIGNAL_PROPERTIES_CHANGED, AJCPS_GetCurrentSessionId());
        }
        if ((sendUpdates & (1 << 3)) != 0) {
            AJ_AlwaysPrintf(("##### Sending update signal: fan speed selector state \n"));
            AJCPS_SendPropertyChangedSignal(busAttachment, EN_MYDEVICE_FAN_SPEED_SIGNAL_PROPERTIES_CHANGED, AJCPS_GetCurrentSessionId());
        }
    }
    return;
}

AJ_Status Controlee_Finish(AJ_BusAttachment* busAttachment)
{
    return AJ_OK;
}
