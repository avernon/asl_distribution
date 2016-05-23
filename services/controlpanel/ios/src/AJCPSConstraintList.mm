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

#import "AJCPSConstraintList.h"
#import "alljoyn/about/AJNConvertUtil.h"

@interface AJCPSConstraintList ()
@property (nonatomic) ajn::services::ConstraintList *handle;
@end

@implementation AJCPSConstraintList
- (id)initWithHandle:(ajn::services::ConstraintList *)handle
{
	self = [super init];
	if (self) {
		self.handle = handle;
	}
	return self;
}

/**
 * Get the Constraint Value
 * @return the Constraint Value
 */
- (AJCPSConstraintValue)getConstraintValue
{
	return [self convertToAJCPSConstraintValue:self.handle->getConstraintValue()];
}


/**
 * Get the Property Type of the Constraint
 * @return propertyType of the Constraint
 */
- (AJCPSPropertyType)getPropertyType
{
	return self.handle->getPropertyType();
}

/**
 * Get the Display
 * @return Display Value
 */
- (NSString *)getDisplay
{
   
    const qcc::String str = self.handle->getDisplay();

    return [AJNConvertUtil convertQCCStringtoNSString:str];
}


- (AJCPSConstraintValue)convertToAJCPSConstraintValue:(ajn::services::ConstraintValue) constraintValue
{
    AJCPSConstraintValue tConstraintValue;
    
    switch ([self getPropertyType]) {
        case 	AJCPS_UINT16_PROPERTY :
            tConstraintValue.uint16Value = constraintValue.uint16Value;
            
            break;
        case 	AJCPS_INT16_PROPERTY :
            tConstraintValue.int16Value = constraintValue.int16Value;
            
            break;
        case 	AJCPS_UINT32_PROPERTY :
            tConstraintValue.uint32Value = constraintValue.uint32Value;
            
            break;
        case 	AJCPS_INT32_PROPERTY :
            tConstraintValue.int32Value = constraintValue.int32Value;
            
            break;
        case 	AJCPS_UINT64_PROPERTY :
            tConstraintValue.uint64Value = constraintValue.uint64Value;
            
            break;
        case 	AJCPS_INT64_PROPERTY :
            tConstraintValue.int64Value  = constraintValue.int64Value;
            
            break;
        case 	AJCPS_DOUBLE_PROPERTY :
            tConstraintValue.doubleValue = constraintValue.doubleValue;
            
            break;
        case 	AJCPS_STRING_PROPERTY :
            tConstraintValue.charValue = constraintValue.charValue;
            
            break;
        case 	AJCPS_DATE_PROPERTY : //TODO
            
            break;
        case 	AJCPS_TIME_PROPERTY : //TODO
            
            break;
        default:
            break;
    }
    
    return tConstraintValue;
}
@end