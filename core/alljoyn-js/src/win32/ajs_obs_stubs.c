/**
 * @file
 */
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

#include <ajtcl/alljoyn.h>
#include <ajtcl/services/OnboardingService.h>
#include <ajtcl/services/OnboardingManager.h>

int8_t AJOBS_GetState()
{
    return AJOBS_STATE_CONFIGURED_VALIDATED;
}

AJ_Status AJOBS_Start(const AJOBS_Settings* settings)
{
    return AJ_OK;
}

AJ_Status AJOBS_EstablishWiFi()
{
    return AJ_OK;
}

AJ_Status AJOBS_DisconnectWiFi()
{
    return AJ_OK;
}

AJ_Status AJOBS_SwitchToRetry()
{
    return AJ_OK;
}

AJ_Status AJOBS_ConnectedHandler(AJ_BusAttachment* busAttachment)
{
    return AJ_OK;
}

AJ_Status AJOBS_DisconnectHandler(AJ_BusAttachment* busAttachment)
{
    return AJ_OK;
}

AJSVC_ServiceStatus AJOBS_MessageProcessor(AJ_BusAttachment* busAttachment, AJ_Message* msg, AJ_Status* msgStatus)
{
    return AJSVC_SERVICE_STATUS_NOT_HANDLED;
}
