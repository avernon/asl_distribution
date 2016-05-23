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

#import "alljoyn/controlpanel/Property.h"
#import "AJCPSProperty.h"
#import "alljoyn/about/AJNConvertUtil.h"
#import "AJCPSControlPanelDevice.h"
#import "AJCPSConstraintList.h"

@interface AJCPSProperty ()
//using AJCPSWidget handle
@end


@implementation AJCPSProperty

- (id)initWithHandle:(ajn::services::Property *)handle
{
	self = [super initWithHandle:handle];
	if (self) {
	}
	return self;
}

/**
 * Get the PropertyType
 * @return PropertyType
 */
- (AJCPSPropertyType)getPropertyType
{
	return ((ajn::services::Property *)self.handle)->getPropertyType();
}

/**
 * Get the PropertyValue of the property
 * @return the value of the property
 */
- (void)getPropertyValue:(AJCPSPropertyValue &)propertyValue
{
	[self convertToAJCPSPropertyValue:((ajn::services::Property *)self.handle)->getPropertyValue() to:&propertyValue];
}

/**
 * Get the Unit of Measure
 * @return Unit of Measure Values
 */
- (NSString *)getUnitOfMeasure
{
	return [AJNConvertUtil convertQCCStringtoNSString:((ajn::services::Property *)self.handle)->getUnitOfMeasure()];
}

/**
 * Get the Constraint List vector
 * @return the Constraint List vector
 */
//const std::vector<ConstraintList>&
- (NSArray *)getConstraintList
{
    // TODO: the list gets erased when we leave this loop
    
	NSMutableArray *constraintList = [[NSMutableArray alloc]init];
    
	for (int i = 0; i != ((ajn::services::Property *)self.handle)->getConstraintList().size(); i++) {
		[constraintList addObject:[[AJCPSConstraintList alloc] initWithHandle:(ajn::services::ConstraintList *)&((ajn::services::Property *)self.handle)->getConstraintList().at(i)]];
	}
    
	return constraintList;
}

- (AJCPSConstraintRange *)getConstraintRange
{
    ajn::services::ConstraintRange *constraintRange = ((ajn::services::Property *)self.handle)->getConstraintRange();
    if (constraintRange) {
        return [[AJCPSConstraintRange alloc] initWithHandle:constraintRange];
    }
    else
        return nil;
}

- (QStatus)setValueFromBool:(bool)value
{
	return ((ajn::services::Property *)self.handle)->setValue(value);
}

- (QStatus)setValueFromUnsignedShort:(uint16_t)value
{
	return ((ajn::services::Property *)self.handle)->setValue(value);
}

- (QStatus)setValueFromShort:(int16_t)value
{
	return ((ajn::services::Property *)self.handle)->setValue(value);
}

- (QStatus)setValueFromUnsignedLong:(uint32_t)value
{
	return ((ajn::services::Property *)self.handle)->setValue(value);
}

- (QStatus)setValueFromLong:(int32_t)value
{
	return ((ajn::services::Property *)self.handle)->setValue(value);
}

- (QStatus)setValueFromUnsignedLongLong:(uint64_t)value
{
	return ((ajn::services::Property *)self.handle)->setValue(value);
}

- (QStatus)setValueFromLongLong:(int64_t)value
{
	return ((ajn::services::Property *)self.handle)->setValue(value);
}

- (QStatus)setValueFromDouble:(double)value
{
	return ((ajn::services::Property *)self.handle)->setValue(value);
}

- (QStatus)setValueFromCString:(const char *)value
{
	return ((ajn::services::Property *)self.handle)->setValue(value);
}

- (QStatus)setValueFromDate:(AJCPSCPSDate *)value
{
	return ((ajn::services::Property *)self.handle)->setValue(*[value handle]);
}

- (QStatus)setValueFromTime:(AJCPSCPSTime *)value
{
	return ((ajn::services::Property *)self.handle)->setValue(value);
}

- (void)convertToAJCPSPropertyValue:(ajn::services::PropertyValue) constraintValue to:(AJCPSPropertyValue *)tConstraintValue
{
    switch ([self getPropertyType]) {
        case 	AJCPS_BOOL_PROPERTY :
            tConstraintValue->boolValue = constraintValue.boolValue;
            
            break;
        case 	AJCPS_UINT16_PROPERTY :
            tConstraintValue->uint16Value = constraintValue.uint16Value;
            
            break;
        case 	AJCPS_INT16_PROPERTY :
            tConstraintValue->int16Value = constraintValue.int16Value;
            
            break;
        case 	AJCPS_UINT32_PROPERTY :
            tConstraintValue->uint32Value = constraintValue.uint32Value;
            
            break;
        case 	AJCPS_INT32_PROPERTY :
            tConstraintValue->int32Value = constraintValue.int32Value;
            
            break;
        case 	AJCPS_UINT64_PROPERTY :
            tConstraintValue->uint64Value = constraintValue.uint64Value;
            
            break;
        case 	AJCPS_INT64_PROPERTY :
            tConstraintValue->int64Value  = constraintValue.int64Value;
            
            break;
        case 	AJCPS_DOUBLE_PROPERTY :
            tConstraintValue->doubleValue = constraintValue.doubleValue;
            
            break;
        case 	AJCPS_STRING_PROPERTY :
            tConstraintValue->charValue = constraintValue.charValue;
            
            break;
        case 	AJCPS_DATE_PROPERTY : //TODO
            
            break;
        case 	AJCPS_TIME_PROPERTY : //TODO
            
            break;
        default:
            break;
    }
}

@end
