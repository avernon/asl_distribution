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

#ifndef _ONBOARDINGCONTROLLERAPI_H_
#define _ONBOARDINGCONTROLLERAPI_H_

/** @defgroup ControllerAPI Controller API
 *
 *  @{
 */

#include <alljoyn.h>
#include <alljoyn/onboarding/OnboardingManager.h>

/**
 * Onboarding get state.
 * @return state
 */
AJOBS_State AJOBS_ControllerAPI_GetState();
/**
 * Onboarding set state.
 * @param state
 */
void AJOBS_ControllerAPI_SetState(AJOBS_State state);

/**
 * Onboarding last error variable.
 */
const AJOBS_Error* AJOBS_ControllerAPI_GetError();

/**
 * Onboarding last scan time.
 */
const AJ_Time* AJOBS_ControllerAPI_GetLastScanTime();

/**
 * Onboarding scan infos variable.
 */
const AJOBS_ScanInfo* AJOBS_ControllerAPI_GetScanInfos();

/**
 * Onboarding scan infos count variable.
 */
uint8_t AJOBS_ControllerAPI_GetScanInfoCount();

/**
 * perform a check of the current configuration state and accordingly take the relevant action of
 * either establishing SoftAP mode if not configured
 * or attempt to connect using the current connection info.
 * @param obInfo
 * @return status
 */
AJ_Status AJOBS_ControllerAPI_StartSoftAPIfNeededOrConnect(AJOBS_Info* obInfo);

/**
 * disconnect from current mode (SoftAP or client) and go to idle mode.
 * @param reset
 * @return status
 */
AJ_Status AJOBS_ControllerAPI_GotoIdleWiFi(uint8_t reset);

/**
 * perform a offboarding clearing the current configuration state and values.
 * @return status
 */
AJ_Status AJOBS_ControllerAPI_DoOffboardWiFi();

/**
 * perform a scaninfo.
 * @return status
 */
AJ_Status AJOBS_ControllerAPI_DoScanInfo();

/**
 * return whether the Wi-Fi is in SoftAP mode.
 * @return success
 */
int8_t AJOBS_ControllerAPI_IsWiFiSoftAP();

/**
 * return whether the Wi-Fi is in client mode.
 * @return success
 */
int8_t AJOBS_ControllerAPI_IsWiFiClient();

/** @} */ // End of group 'ControllerAPI'
 #endif // _ONBOARDINGCONTROLLERAPI_H_
