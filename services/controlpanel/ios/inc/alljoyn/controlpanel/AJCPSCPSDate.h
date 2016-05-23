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
#import "alljoyn/controlpanel/CPSDate.h"

/**
 * AJCPSCPSDate allows sending of a Date as a Property
 */
@interface AJCPSCPSDate : NSObject

- (id)initWithDay:(uint16_t) day month:(uint16_t) month year:(uint16_t) year;


- (id)initWithHandle:(ajn ::services ::CPSDate *)handle;

/**
 * Get the day value of the date
 * @return day value
 */
- (uint16_t)getDay;

/**
 * Set the day Value of the date
 * @param day value
 */
- (void)setDay:(uint16_t)day;

/**
 * Get the Month value of the date
 * @return month value
 */
- (uint16_t)getMonth;

/**
 * Set the Month value of the date
 * @param month value
 */
- (void)setMonth:(uint16_t)month;

/**
 * Get the Year value of the date
 * @return year value
 */
- (uint16_t)getYear;

/**
 * Set the Year value of the date
 * @param year value
 */
- (void)setYear:(uint16_t)year;

@property (nonatomic, readonly)ajn::services::CPSDate * handle;

@end