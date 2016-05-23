/******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

/**
 * This class encapsulates the tracking ID that is returned when groups, presets, effect, and scenes are
 * created in the Lighting system. The tracking ID can be matched to objects created by the developer
 * themselves.
 */
@interface LSFSDKTrackingID : NSObject

/** @name Class Properties */

/**
 * Specifies the value of the tracking ID.
 */
@property (nonatomic) uint32_t value;

/** @name Initializing an LSFSDKTrackingID Object */

/**
 * Constructs a LSFSDKTrackingID object.
 *
 * @warning This method is intended to be used internally. Client software should not instantiate
 * LSFSDKLampParameters directly, but should instead get them from the LSFSDKLamp using the [LSFSDKLamp parameters]
 * method.
 */
-(id)init;

/**
 * Constructs a LSFSDKTrackingID object using the provided value.
 *
 * @warning This method is intended to be used internally. Client software should not instantiate
 * LSFSDKLampParameters directly, but should instead get them from the LSFSDKLamp using the [LSFSDKLamp parameters]
 * method.
 *
 * @param value  The value to use as the tracking ID
 */
-(id)initWithValue: (uint32_t)value;

@end
