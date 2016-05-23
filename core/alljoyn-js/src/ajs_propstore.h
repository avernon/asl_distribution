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

#ifndef _AJS_PROPSTORE_H_
#define _AJS_PROPSTORE_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/services/PropertyStore.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PASSWORD_VALUE_LENGTH     (AJ_ADHOC_LEN * 2)

/**
 * Initialize the property store
 */
AJ_Status AJS_PropertyStore_Init();

/**
 * Returns TRUE is the property is read only
 */
uint8_t AJS_PropertyStore_IsReadOnly(int8_t index);

/**
 * Function to retrieve a password from the property store.
 *
 * @param buffer Buffer to return the password
 * @param bufLen The size of the buffer
 *
 * @return  Returns the actual length of the password
 */
uint32_t AJS_PasswordCallback(uint8_t* buffer, uint32_t bufLen);

#ifdef __cplusplus
}
#endif

#endif //_AJS_PROPSTORE_H
