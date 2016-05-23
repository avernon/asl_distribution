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

#ifndef CONTROL_MARSHAL_UTIL_H_
#define CONTROL_MARSHAL_UTIL_H_

/** @defgroup ControlMarshalUtil Control Marshaling Utilities
 * details Functions that assist in Marshaling Controls.
 *  @{
 */

#include <ajtcl/alljoyn.h>
#include <ajtcl/services/Definitions.h>
#include <ajtcl/services/Common/BaseWidget.h>

/**
 * StartOptionalParams - Start Marshaling the Optional Parameters' container array.
 * @param reply - message to marshal into
 * @param arg - arg to hold the container
 * @return aj_status - success/failure
 */
#define StartOptionalParams(reply, arg) AJ_MarshalContainer(reply, arg, AJ_ARG_ARRAY)

/**
 * Add a layout Hint. Can be used for all kinds of MetaData (Property, Action etc)
 * @param reply - message to marshal into
 * @param hints - hints to marshal
 * @param numHints - number of hints to marshal
 * @return aj_status - success/failure
 */
AJ_Status AddHints(AJ_Message* reply, const uint16_t hints[], uint16_t numHints);

/**
 * Add Constraint Value
 * @param reply - message to marshal into
 * @param sig - signature of value
 * @param value - value to marshal
 * @param displayValue - displayValue to marshal
 * @return aj_status - success/failure
 */
AJ_Status AddConstraintValue(AJ_Message* reply, const char* sig, const void* value, const char* displayValue);

/**
 * Add ConstraintRange component
 * @param reply - message to marshal into
 * @param valueSig - signature of value
 * @param min - min Value
 * @param max - max Value
 * @param increment - increment Value
 * @return aj_status - success/failure
 */
AJ_Status AddConstraintRange(AJ_Message* reply, const char* valueSig, const void* min, const void* max, const void* increment);

/**
 * Start a Complex OptionalParam component
 * @param reply - message to marshal into
 * @param arg - arg to hold value
 * @param key - key in dictionary
 * @param sig - signature of value
 * @return aj_status - success/failure
 */
AJ_Status StartComplexOptionalParam(AJ_Message* reply, AJ_Arg* arg, uint16_t key, const char* sig);

/**
 * Add a basic type Optional Param
 * @param reply - message to marshal into
 * @param key - key in dictionary
 * @param sig - signature of value
 * @param value - value to marshal
 * @return aj_status - success/failure
 */
AJ_Status AddBasicOptionalParam(AJ_Message* reply, uint16_t key, const char* sig, const void* value);

/**
 * Add a property for GetAll response
 * @param reply - message to marshal into
 * @param key - key in dictionary
 * @param sig - signature of value
 * @param widget - widget being marshalled
 * @param language - language requested
 * @param functionPtr - function Pointer to marshal the value
 * @return aj_status - success/failure
 */
AJ_Status AddPropertyForGetAll(AJ_Message* reply, char* key, const char* sig,
                               BaseWidget* widget, uint16_t language, MarshalWidgetFptr functionPtr);

/**
 * Helper functions. Receives sig value and void* and does the marshalling
 * @param reply - message to marshal into
 * @param sig - signature of value
 * @param value - value as void*
 * @return aj_status - success/failure
 */
AJ_Status MarshalVariant(AJ_Message* reply, const char* sig, const void* value);

/**
 * MarshalAllRootProperties - includes only version
 * @param reply - message to marshal into
 * @return aj_status - success/failure
 */
AJ_Status MarshalAllRootProperties(AJ_Message* reply);

/**
 * Marshal Version Property for root interfaces
 * @param reply - message to marshal into
 * @return aj_status - success/failure
 */
AJ_Status MarshalVersionRootProperties(AJ_Message* reply);

/** @} */
#endif /* CONTROL_SERVICE_H_ */
