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

#ifndef _ONBOARDINGSERVICE_H_
#define _ONBOARDINGSERVICE_H_

/** @defgroup OnboardingService Onboarding Service Framework
 *
 *  @{
 */

#include <ajtcl/alljoyn.h>
#include <ajtcl/services/ServicesCommon.h>

/**
 * Turn on per-module debug printing by setting this variable to non-zero value
 * (usually in debugger).
 */
#ifndef NDEBUG
extern uint8_t dbgAJOBS;
#endif

/**
 * Published Onboarding BusObjects.
 */

extern AJ_Object AJOBS_ObjectList[];                  /**< onboarding objects */

/**
 * Register the Onboarding Service Bus Objects list
 * @return aj_status
 */
AJ_Status AJOBS_RegisterObjectList();

#define AJOBS_SSID_MAX_LENGTH  32                     /**< ssid max length */

/*
 * Onboarding Service Message Handlers
 */

/**
 * Handler for property getters associated with org.alljoyn.Onboarding.
 * @param replyMsg
 * @param propId
 * @param context
 * @return aj_status
 */
AJ_Status AJOBS_PropGetHandler(AJ_Message* replyMsg, uint32_t propId, void* context);

/**
 * Handler for property setters associated with org.alljoyn.Onboarding.
 * @param replyMsg
 * @param propId
 * @param context
 * @return aj_status
 */
AJ_Status AJOBS_PropSetHandler(AJ_Message* replyMsg, uint32_t propId, void* context);

/**
 * Handler for ConfigureWiFi request in org.alljoyn.Onboarding.
 * @param msg
 * @return aj_status
 */
AJ_Status AJOBS_ConfigureWiFiHandler(AJ_Message* msg);

/**
 * Handler for ConnectWiFi request in org.alljoyn.Onboarding.
 * @param msg
 * @return aj_status
 */
AJ_Status AJOBS_ConnectWiFiHandler(AJ_Message* msg);

/**
 * Handler for OffboardWiFi request in org.alljoyn.Onboarding.
 * @param msg
 * @return aj_status
 */
AJ_Status AJOBS_OffboardWiFiHandler(AJ_Message* msg);

/**
 * Handler for GetScanInfo request in org.alljoyn.Onboarding.
 * @param msg
 * @return aj_status
 */
AJ_Status AJOBS_GetScanInfoHandler(AJ_Message* msg);

/*
   //will be used in future versions
   AJ_Status AJOBS_SendConnectionResult(AJ_BusAttachment* bus);
 */

/**
 * Called when Routing Node is connected.
 * @param busAttachment
 * @return aj_status
 */
AJ_Status AJOBS_ConnectedHandler(AJ_BusAttachment* busAttachment);

/**
 * Called just before disconnecting from the Router Node.
 * @param busAttachment
 * @return aj_status
 */
AJ_Status AJOBS_DisconnectHandler(AJ_BusAttachment* busAttachment);

/**
 * Called when a new incoming message requires processing.
 * @param busAttachment
 * @param msg
 * @param msgStatus
 * @return service_Status
 */
AJSVC_ServiceStatus AJOBS_MessageProcessor(AJ_BusAttachment* busAttachment, AJ_Message* msg, AJ_Status* msgStatus);

/** @} */ //End of group 'OnboardingService'
 #endif // _ONBOARDINGSERVICE_H_
