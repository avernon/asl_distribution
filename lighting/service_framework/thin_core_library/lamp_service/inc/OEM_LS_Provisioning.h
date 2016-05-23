# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
#ifndef _OEM_LS_PROVISIONING_H_
#define _OEM_LS_PROVISIONING_H_
/**
 * @file OEM_LS_Provisioning.h
 * @defgroup property_store The OEM-defined properties used by About/Config Service
 * @{
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

/**
 * Initialize the property store.  This will initialize our propertystore to
 * the default property values and then attempt to overwrite them with values
 * stored in NVRAM.  This function only needs to be changed if the OEM chooses
 * to add config properties.
 *
 * @param  None
 * @return Status of the operation
 */
AJ_Status PropertyStore_Init(void);

/**
 * Persist device ID.
 * Device ID is a unique identifier for this device.
 * The Lamp Service will generate the DeviceID the first time it boots up.
 * Since the ID must persist across calls to FactoryReset, the Lamp Service must persist it separately from the Config data.
 * This function is called to persist the ID.
 *
 * @param  None
 * @return None
 */
void SavePersistentDeviceId(void);

/**
 * The max length of the default language name
 */
#define LANG_VALUE_LENGTH 7

/**
 * The max length of the realm name
 */
#define KEY_VALUE_LENGTH 10

/**
 * The max length of the machine ID
 */
#define MACHINE_ID_LENGTH (UUID_LENGTH * 2)

/**
 * The max length of the device name
 */
#define DEVICE_NAME_VALUE_LENGTH LSF_MAX_NAME_LENGTH

/**
 * The max length of the password
 */
#define PASSWORD_VALUE_LENGTH (AJ_ADHOC_LEN * 2)

#endif
