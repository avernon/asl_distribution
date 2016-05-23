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

#import "internal/LSFObject.h"

/**
 * This class encapsulates all of the parameters for lamps and illustrates the current energy usage and
 * brightness output of the lamp.
 */
@interface LSFSDKLampParameters : LSFObject

/** @name Class Properties */

/**
 * Specifies the current energy usage of the lamp, in milliwatts.
 */
@property (nonatomic) unsigned int energyUsageMilliwatts;

/**
 * Specifies the current brightness of the lamp, in lumens.
 */
@property (nonatomic) unsigned int lumens;

/** @name Initializing an LSFSDKLampParameters Object */

/**
 * Constructs a LSFSDKLampParameters object.
 *
 * @warning This method is intended to be used internally. Client software should not instantiate
 * LSFSDKLampParameters directly, but should instead get them from the LSFSDKLamp using the [LSFSDKLamp parameters]
 * method.
 */
-(id)init;

@end
