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

#ifndef _CONFIGSERVICE_H_
#define _CONFIGSERVICE_H_

/** @defgroup ConfigService Config Service Framework
 *
 *  @{
 */

#include <alljoyn.h>
#include <alljoyn/services_common/ServicesCommon.h>

/**
 * Published Config BusObjects and Interfaces.
 */
extern const AJ_InterfaceDescription AJSVC_ConfigInterfaces[];

/**
 * Following definitions are read by the application.
 */

/**
 * number of config objects
 */
#define NUM_CONFIG_OBJECTS 1

/**
 * Config app objects
 */
#define CONFIG_APPOBJECTS \
    { "/Config",             AJSVC_ConfigInterfaces, AJ_OBJ_FLAG_ANNOUNCED },

/**
 * Actions to perform when factory reset is requested.
 * Performed by the application.
 * @return status
 */
typedef AJ_Status (*AJCFG_FactoryReset)(void);

/**
 * Actions to perform when a device restart is requested.
 * Performed by the application.
 * @return aj_status
 */
typedef AJ_Status (*AJCFG_Restart)(void);

/**
 * Actions to perform when a new device passcode is set.
 * Performed by the application.
 * @param routerRealm
 * @param newPasscode
 * @param newPasscodeLen
 * @return aj_status
 */
typedef AJ_Status (*AJCFG_SetPasscode)(const char* routerRealm, const uint8_t* newPasscode, uint8_t newPasscodeLen);

/**
 * Check whether the given value is valid for the given key.
 * @param key
 * @param value
 * @return isValid
 */
typedef uint8_t (*AJCFG_IsValueValid)(const char* key, const char* value);

/**
 * Config Service API
 */

/**
 * Start Config service framework passing callbacks.
 * @param factoryReset
 * @param restart
 * @param setPasscode
 * @param isValueValid
 * @return aj_status
 */
AJ_Status AJCFG_Start(AJCFG_FactoryReset factoryReset, AJCFG_Restart restart, AJCFG_SetPasscode setPasscode, AJCFG_IsValueValid isValueValid);

/**
 * Called when router is connected.
 * @param busAttachment
 * @return aj_status
 */
AJ_Status AJCFG_ConnectedHandler(AJ_BusAttachment* busAttachment);

/**
 * Called when a new incoming message requires processing.
 * @param busAttachment
 * @param msg
 * @param msgStatus
 * @return aj_status
 */
AJSVC_ServiceStatus AJCFG_MessageProcessor(AJ_BusAttachment* busAttachment, AJ_Message* msg, AJ_Status* msgStatus);

/**
 * Called just before the router disconnects.
 * @param busAttachment
 * @return aj_status
 */
AJ_Status AJCFG_DisconnectHandler(AJ_BusAttachment* busAttachment);

/** @} */
 #endif // _CONFIGSERVICE_H_
