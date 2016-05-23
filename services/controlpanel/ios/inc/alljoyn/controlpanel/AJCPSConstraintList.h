/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#import <Foundation/Foundation.h>
#import "alljoyn/controlpanel/ConstraintList.h"
#import "AJCPSControlPanelEnums.h"

/**
 * ConstraintValue - a union combining all possible values
 * that can make up a constraint
 */
typedef union {
    /**
     * Value for uint16_t
     */
    uint16_t uint16Value;
    /**
     * Value for int16_t
     */
    int16_t int16Value;
    /**
     * Value for uint32_t
     */
    uint32_t uint32Value;
    /**
     * Value for int32_t
     */
    int32_t int32Value;
    /**
     * Value for uint64_t
     */
    uint64_t uint64Value;
    /**
     * Value for int64_t
     */
    int64_t int64Value;
    /**
     * Value for double
     */
    double doubleValue;
    /**
     * Value for const char*
     */
    const char* charValue;
} AJCPSConstraintValue;

/**
 * AJCPSConstraintList defines a list of
 * Values and constrain a property to those values.
 * The Constraint is applied on the controller side.
 * No validations are done in the Controllee
 */
@interface AJCPSConstraintList : NSObject

- (id)initWithHandle:(ajn ::services ::ConstraintList *)handle;

/**
 * Get the Constraint Value
 * @return the Constraint Value
 */
- (AJCPSConstraintValue)getConstraintValue;

/**
 * Get the Property Type of the Constraint
 * @return propertyType of the Constraint
 */
- (AJCPSPropertyType)getPropertyType;

/**
 * Get the Display
 * @return Display Value
 */
- (NSString *)getDisplay;

@end