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

#ifndef _PROPERTYSTOREOEMPROVISIONING_H_
#define _PROPERTYSTOREOEMPROVISIONING_H_

/** @defgroup PropertyStoreOEMProvisioning
 *
 *  @{
 */

#include <alljoyn.h>
#include <aj_auth.h>
#include <aj_config.h>
#include <alljoyn/services_common/ServicesCommon.h>
#include <alljoyn/services_common/PropertyStore.h>

/**
 * Device manufacture name
 */
extern const char* deviceManufactureName;

/**
 * Device product name
 */
extern const char* deviceProductName;

#define LANG_VALUE_LENGTH 7
#define KEY_VALUE_LENGTH 10
#define MACHINE_ID_LENGTH (UUID_LENGTH * 2)
#define DEVICE_NAME_VALUE_LENGTH 32
#define PASSWORD_VALUE_LENGTH (AJ_ADHOC_LEN * 2)

extern const uint8_t AJSVC_PROPERTY_STORE_NUMBER_OF_LANGUAGES;
extern const char** propertyStoreDefaultLanguages;

/**
 * property structure
 */
typedef struct _PropertyStoreEntry {
    const char* keyName; // The property key name as shown in About and Config documentation

    // msb=public/private; bit number 3 - initialise once; bit number 2 - multi-language value; bit number 1 - announce; bit number 0 - read/write
    uint8_t mode0Write : 1;
    uint8_t mode1Announce : 1;
    uint8_t mode2MultiLng : 1;
    uint8_t mode3Init : 1;
    uint8_t mode4 : 1;
    uint8_t mode5 : 1;
    uint8_t mode6 : 1;
    uint8_t mode7Public : 1;
} PropertyStoreEntry;

/**
 * properties array variable with property definitions
 */
extern const PropertyStoreEntry propertyStoreProperties[AJSVC_PROPERTY_STORE_NUMBER_OF_KEYS];

/**
 * properties array variable with default values
 */
extern const char** propertyStoreDefaultValues[AJSVC_PROPERTY_STORE_NUMBER_OF_KEYS]; // Array of Array of size 1 or AJSVC_PROPERTY_STORE_NUMBER_OF_LANGUAGES constant buffers depending on whether the property is multilingual

/**
 * properties container for runtime values
 */
typedef struct _PropertyStoreRuntimeEntry {
    char** value;  // An array of size 1 or AJSVC_PROPERTY_STORE_NUMBER_OF_LANGUAGES mutable buffers depending on whether the property is multilingual
    uint8_t size; // The size of the value buffer(s)
} PropertyStoreConfigEntry;

/**
 * properties runtime array variable with runtime values of dynamically initialized and configurable properties
 */
extern PropertyStoreConfigEntry propertyStoreRuntimeValues[AJSVC_PROPERTY_STORE_NUMBER_OF_RUNTIME_KEYS];

#define AJ_PROPERTIES_NV_ID_BEGIN (AJ_NVRAM_ID_CREDS_MAX + 1)
#define AJ_PROPERTIES_NV_ID_END   (AJ_PROPERTIES_NV_ID_BEGIN + (int)AJSVC_PROPERTY_STORE_NUMBER_OF_RUNTIME_KEYS * (int)AJSVC_PROPERTY_STORE_NUMBER_OF_LANGUAGES - 1)

AJ_Status PropertyStore_Init();

/** @} */
 #endif //_PROPERTYSTOREOEMPROVISIONING_H_
