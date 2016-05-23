#ifndef _AJS__SERVICES_H
#define _AJS__SERVICES_H
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

#include <ajtcl/aj_target.h>
#include <ajtcl/alljoyn.h>

#define NUM_CONTROLPANEL_OBJECTS 0

#include <ajtcl/services/ServicesHandlers.h>
#include <ajtcl/services/ServicesCommon.h>
#ifdef ONBOARDING_SERVICE
#include <ajtcl/services/OnboardingManager.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the Services. called at the start of the application
 *
 * @param aj                      The bus attachment
 */
AJ_Status AJS_ServicesInit(AJ_BusAttachment* aj);

/**
 * Pass a message for possible handling by one of the basic services.
 *
 * @param msg  The message to be handled
 *
 * @return - AJ_OK if the message was handled by a service
 *         - AJ_ERR_NO_MATCH if the message was not handled
 *         - Other errors indicating an unmarshalling failure
 */
AJ_Status AJS_ServicesMsgHandler(AJ_Message* msg);

#ifdef __cplusplus
}
#endif

#endif
