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
#ifndef _AJ_MSG_PRIV_H
#define _AJ_MSG_PRIV_H

/**
 * @file aj_msg_priv.h
 * @defgroup aj_msg_priv Non-public Message Marshaling and Unmarshaling APIs
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

#include <ajtcl/alljoyn.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns the signature of the next arg to be unmarshalled.
 *
 * @param msg   A pointer to the message currently being unmarshaled
 *
 * @return  Pointer to the signature of the next arg to unmarshal.
 */
AJ_EXPORT
const char* AJ_NextArgSig(AJ_Message* msg);

/**
 * Check if the type ID is a container type (array, struct, dictionay entry).
 *
 * @param typeId  The type or element type if the array flag is set
 *
 * @return  Indication if the type is a container or not.
 *          - TRUE (1) iff the type is a container.
 *          - FLASE (0) iff the type is not a container.
 */
AJ_EXPORT
int AJ_IsContainerType(char typeId);

/**
 * Check if the type ID is a scalar type (boolean, byte, int16, int32, int64, uint16, uint32, uint64, double).
 *
 * @param typeId  The type or element type if the array flag is set
 *
 * @return  Indication if the type is a scalar or not.
 *          - TRUE (1) iff the type is a scalar.
 *          - FLASE (0) iff the type is not a scalar.
 */
AJ_EXPORT
int AJ_IsScalarType(char typeId);

/**
 * Check if the type ID is a string type (string, object path, signature).
 *
 * @param typeId  The type or element type if the array flag is set
 *
 * @return  Indication if the type is a string or not.
 *          - TRUE (1) iff the type is a string.
 *          - FLASE (0) iff the type is not a string.
 */
AJ_EXPORT
int AJ_IsStringType(char typeId);

/**
 * Check if the type ID is a basic type (string or scalar).
 *
 * @param typeId  The type or element type if the array flag is set
 *
 * @return  Indication if the type is a basic type or not.
 *          - TRUE (1) iff the type is a basic type.
 *          - FLASE (0) iff the type is not a basic type.
 */
AJ_EXPORT
int AJ_IsBasicType(char typeId);

/**
 * For scalar types, get the size of that type.  For non-scalar types, get the alignment.
 *
 * @param typeId  The type or element type if the array flag is set
 *
 * @return  Size (or alignment) of the type.
 */
AJ_EXPORT
size_t AJ_GetTypeSize(char typeId);

/**
 * Lookup the message identifier and set the msgId on the message.
 *
 * @param msg    The message already initialized with object, interface, and member fields
 * @param secure Returns boolen indicating if the object or interface was marked secure
 *
 * @return  - AJ_OK if the message was found
 *          - AJ_ERR_SIGNATURE if the message was found but the signature was missing or incorrect.
 *            The message identified is still set.
 *          - AJ_ERR_NO_MATCH if the message could not be identified
 */
AJ_EXPORT
AJ_Status AJ_LookupMessageId(AJ_Message* msg, uint8_t* secure);

/**
 * Lookup a property identifier and get the property signature
 *
 * @param msg     A property Get or Set method call or reply message
 * @param iface   The interface the property is defined on
 * @param prop    The property name
 * @param propId  Returns the property identifier
 * @param sig     Returns the property type signature
 * @param secure  Returns boolen indicating if the property is on an object or interface marked secure
 *
 * @return  - AJ_OK if the message was found
 *          - AJ_ERR_NO_MATCH if the property could not be identified
 */
AJ_EXPORT
AJ_Status AJ_IdentifyProperty(AJ_Message* msg, const char* iface, const char* prop, uint32_t* propId, const char** sig, uint8_t* secure);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif

