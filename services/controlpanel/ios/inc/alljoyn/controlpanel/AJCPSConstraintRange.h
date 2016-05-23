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
#import "alljoyn/controlpanel/ConstraintRange.h"
#import "AJCPSControlPanelEnums.h"

typedef union {
	/**
	 * Value of type uint16_t
	 */
	uint16_t uint16Value;
	/**
	 * Value of type int16_t
	 */
	int16_t int16Value;
	/**
	 * Value of type uint32_t
	 */
	uint32_t uint32Value;
	/**
	 * Value of type int32_t
	 */
	int32_t int32Value;
	/**
	 * Value of type uint64_t
	 */
	uint64_t uint64Value;
	/**
	 * Value of type int64_t
	 */
	int64_t int64Value;
	/**
	 * Value of type double
	 */
	double doubleValue;
} AJCPSConstraintRangeVal;

/**
 * AJCPSConstraintRange defines a range of
 * Values and constrain a property to those values.
 * The Constraint is applied on the controller side.
 * No validations are done in the Controlee.
 */
@interface AJCPSConstraintRange : NSObject

- (id)initWithHandle:(ajn ::services ::ConstraintRange *)handle;

/**
 * get the IncrementValue of the Constraint Range
 * @return IncrementValue
 */
- (uint16_t)getIncrementValue;

/**
 * Get the MaxValue of the Constraint Range
 * @return MaxValue
 */
- (uint16_t)getMaxValue;

/**
 * Get the MinValue of the Constraint Range
 * @return MinValue
 */
- (uint16_t)getMinValue;

@end