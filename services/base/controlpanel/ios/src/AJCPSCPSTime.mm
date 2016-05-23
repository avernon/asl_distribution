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

#import "AJCPSCPSTime.h"

@interface AJCPSCPSTime ()
@property (nonatomic) ajn::services::CPSTime *handle;
@end

@implementation AJCPSCPSTime

- (id)initWithHour:(uint16_t) hour minute:(uint16_t) minute second:(uint16_t) second
{
    self = [super init];
	if (self) {
		self.handle = new  ajn::services::CPSTime(hour, minute, second);
	}
	return self;
}

- (id)initWithHandle:(ajn::services::CPSTime *)handle
{
	self = [super init];
	if (self) {
		self.handle = handle;
	}
	return self;
}

/**
 * Get the hour value of the date
 * @return hour value
 */
- (uint16_t)getHour
{
	return self.handle->getHour();
}

/**
 * Set the hour Value of the date
 * @param hour value
 */
- (void)setHour:(uint16_t)hour
{
	self.handle->setHour(hour);
}

/**
 * Get the Minute value of the date
 * @return minute value
 */
- (uint16_t)getMinute
{
	return self.handle->getMinute();
}

/**
 * Set the Minute value of the date
 * @param minute value
 */
- (void)setMinute:(uint16_t)minute
{
	return self.handle->setMinute(minute);
}

/**
 * Get the Second value of the date
 * @return second value
 */
- (uint16_t)getSecond
{
	return self.handle->getSecond();
}

/**
 * Set the Second value of the date
 * @param second value
 */
- (void)setSecond:(uint16_t)second
{
	return self.handle->setSecond(second);
}

@end