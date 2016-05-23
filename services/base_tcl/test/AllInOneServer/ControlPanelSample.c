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

/**
 * Per-module definition of the current module for debug logging.  Must be defined
 * prior to first inclusion of aj_debug.h.
 * The corresponding flag dbgAJSVCAPP is defined in the containing sample app.
 */
#define AJ_MODULE AJSVCAPP
#include <ajtcl/aj_debug.h>

#include <ajtcl/alljoyn.h>
#include <ajtcl/services/ControlPanelService.h>
#include "ControlPanelProvided.h"
#include "ControlPanelGenerated.h"
#include "ControlPanelSample.h"
#include <ajtcl/aj_link_timeout.h>

#ifndef NDEBUG
extern AJ_EXPORT uint8_t dbgAJSVCAPP;
#endif

static AJ_Object controlleeObjectList[] = {
    AJCPS_CONTROLLEE_GENERATED_OBJECTS
    { NULL }
};

AJ_Status Controlee_Init()
{
    AJ_Status status = AJ_OK;

    status = AJCPS_Start(controlleeObjectList, &GeneratedMessageProcessor, &IdentifyMsgOrPropId, &IdentifyMsgOrPropIdForSignal, &IdentifyRootMsgOrPropId);
    WidgetsInit();

    return status;
}

void Controlee_DoWork(AJ_BusAttachment* busAttachment)
{
    return;
}

AJ_Status Controlee_Finish()
{
    return AJ_OK;
}
