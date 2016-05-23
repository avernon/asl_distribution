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

#ifndef CONTROL_MARSHAL_UTIL_H_
#define CONTROL_MARSHAL_UTIL_H_

/** @defgroup ControlMarshalUtil Control Marshaling Utilities
 * details Functions that assist in Marshaling Controls.
 *  @{
 */

#include <alljoyn.h>
#include <alljoyn/controlpanel/Definitions.h>
#include <alljoyn/controlpanel/Common/BaseWidget.h>

/**
 * StartOptionalParams - Start Marshaling the Optional Parameters' container array.
 * @param reply
 * @param arg
 * @return aj_status
 */
#define StartOptionalParams(reply, arg) AJ_MarshalContainer(reply, arg, AJ_ARG_ARRAY)

/**
 * Add a layout Hint. Can be used for all kinds of MetaData (Property, Action etc)
 * @param reply
 * @param hints
 * @param numHints
 * @return aj_status
 */
AJ_Status AddHints(AJ_Message* reply, const uint16_t hints[], uint16_t numHints);

/**
 * Add Constraint Value
 * @param reply
 * @param sig
 * @param value
 * @param displayValue
 * @return aj_status
 */
AJ_Status AddConstraintValue(AJ_Message* reply, const char* sig, const void* value, const char* displayValue);

/**
 * Add ConstraintRange component
 * @param reply
 * @param valueSig
 * @param min
 * @param max
 * @param increment
 * @return aj_status
 */
AJ_Status AddConstraintRange(AJ_Message* reply, const char* valueSig, const void* min, const void* max, const void* increment);

/**
 * Start a Complex OptionalParam component
 * @param reply
 * @param arg
 * @param key
 * @param sig
 * @return aj_status
 */
AJ_Status StartComplexOptionalParam(AJ_Message* reply, AJ_Arg* arg, uint16_t key, const char* sig);

/**
 * Add a basic type Optional Param
 * @param reply
 * @param key
 * @param sig
 * @param value
 * @return aj_status
 */
AJ_Status AddBasicOptionalParam(AJ_Message* reply, uint16_t key, const char* sig, const void* value);

/**
 * Add a property for GetAll response
 * @param reply
 * @param key
 * @param sig
 * @param widget
 * @param language
 * @param functionPtr
 * @return aj_status
 */
AJ_Status AddPropertyForGetAll(AJ_Message* reply, char* key, const char* sig,
                               BaseWidget* widget, uint16_t language, MarshalWidgetFptr functionPtr);

/**
 * Helper functions. Receives sig value and void* and does the marshalling
 * @param reply
 * @param sig
 * @param value
 * @return status
 */
AJ_Status MarshalVariant(AJ_Message* reply, const char* sig, const void* value);

/**
 * MarshalAllRootProperties - includes only version
 * @param reply
 * @return aj_status
 */
AJ_Status MarshalAllRootProperties(AJ_Message* reply);

/**
 * Marshal Version Property for root interfaces
 * @param reply
 * @return aj_status
 */
AJ_Status MarshalVersionRootProperties(AJ_Message* reply);

/** @} */
#endif /* CONTROL_SERVICE_H_ */
