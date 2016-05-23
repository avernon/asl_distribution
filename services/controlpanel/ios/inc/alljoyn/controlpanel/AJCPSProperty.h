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
#import "AJCPSWidget.h"
#import "alljoyn/controlpanel/Property.h"
#import "AJCPSConstraintRange.h"
#import "alljoyn/controlpanel/CPSDate.h"
#import "alljoyn/controlpanel/CPSTime.h"
#import "AJCPSCPSDate.h"
#import "AJCPSCPSTime.h"

/**
 * Union that allows the definition of a function pointer
 * to get the Properties value.
 */
typedef union {
    /**
     * Get Value for type uint16t
     * @return value of Property
     */
    uint16_t uint16Value;
    /**
     * Get Value for type int16_t
     * @return value of Property
     */
    int16_t int16Value;
    /**
     * Get Value for type uint32_t
     * @return value of Property
     */
    uint32_t uint32Value;
    /**
     * Get Value for type int32_t
     * @return value of Property
     */
    int32_t int32Value;
    /**
     * Get Value for type uint64_t
     * @return value of Property
     */
    uint64_t uint64Value;
    /**
     * Get Value for type int64_t
     * @return value of Property
     */
    int64_t int64Value;
    /**
     * Get Value for type double
     * @return value of Property
     */
    double doubleValue;
    /**
     * Get Value for type const char*
     * @return value of Property
     */
    const char* charValue;
    
    /**
     * Get Value for type bool
     * @return value of Property
     */
    bool boolValue;
    /**
     * Get Value for type CPSDate
     * @return value of Property
     */
    // CPSDate* dateValue; TODO: arc forbids objc objects here
    /**
     * Get Value for type CPSTime
     * @return value of Property
     */
    // CPSTime* timeValue; TODO: arc forbids objc objects here
    
    /**
     * Get Value for type CPSDate
     * @return value of Property
     */
    ajn::services::CPSDate* dateValue;
    /**
     * Get Value for type CPSTime
     * @return value of Property
     */
    ajn::services::CPSTime* timeValue;
    
} AJCPSPropertyValue;

/**
 * AJCPSProperty is used to display a property Widget.
 */
@interface AJCPSProperty : AJCPSWidget

- (id)initWithHandle:(ajn ::services ::Property *)handle;

/**
 * Get the PropertyType
 * @return PropertyType
 */
- (AJCPSPropertyType)getPropertyType;

/**
 * Get the PropertyValue of the property
 * @param propertyValue - the property value according to the property type
 * @return the value of the property
 */
- (void)getPropertyValue:(AJCPSPropertyValue &)propertyValue;

/**
 * Get the Unit of Measure
 * @return Unit of Measure Values
 */
- (NSString *)getUnitOfMeasure;

/**
 * Get the Constraint List vector
 * @return the Constraint List vector
 */
//const std::vector<ConstraintList>&
- (NSArray *)getConstraintList;



/**
 * Get the Constraint Range
 * @return the Constraint Range
 */
- (AJCPSConstraintRange *)getConstraintRange;

/**
 * Set the new Value
 * @param value - new Value to be set to
 * @return status - success/failure
 */
- (QStatus)setValueFromBool:(bool)value;

/**
 * Set the new Value
 * @param value - new Value to be set to
 * @return status - success/failure
 */
- (QStatus)setValueFromUnsignedShort:(uint16_t)value;

/**
 * Set the new Value
 * @param value - new Value to be set to
 * @return status - success/failure
 */
- (QStatus)setValueFromShort:(int16_t)value;

/**
 * Set the new Value
 * @param value - new Value to be set to
 * @return status - success/failure
 */
- (QStatus)setValueFromUnsignedLong:(uint32_t)value;

/**
 * Set the new Value
 * @param value - new Value to be set to
 * @return status - success/failure
 */
- (QStatus)setValueFromLong:(int32_t)value;

/**
 * Set the new Value
 * @param value - new Value to be set to
 * @return status - success/failure
 */
- (QStatus)setValueFromUnsignedLongLong:(uint64_t)value;

/**
 * Set the new Value
 * @param value - new Value to be set to
 * @return status - success/failure
 */
- (QStatus)setValueFromLongLong:(int64_t)value;

/**
 * Set the new Value
 * @param value - new Value to be set to
 * @return status - success/failure
 */
- (QStatus)setValueFromDouble:(double)value;

/**
 * Set the new Value
 * @param value - new Value to be set to
 * @return status - success/failure
 */
- (QStatus)setValueFromCString:(const char *)value;



/**
 * Set the new Value
 * @param value - new Value to be set to
 * @return status - success/failure
 */
- (QStatus)setValueFromDate:(AJCPSCPSDate *)value;

/**
 * Set the new Value
 * @param value - new Value to be set to
 * @return status - success/failure
 */
- (QStatus)setValueFromTime:(AJCPSCPSTime *)value;

@end