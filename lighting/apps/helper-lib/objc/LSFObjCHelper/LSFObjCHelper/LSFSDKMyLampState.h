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

#import <Foundation/Foundation.h>
#import "LSFSDKLampState.h"
#import "LSFSDKPower.h"
#import "LSFSDKColor.h"
#import <internal/LSFLampState.h>

/**
 * Default implementation of the LSFSDKLampState interface and represents the power and
 * color state of a Lighting item.
 */
@interface LSFSDKMyLampState : NSObject <LSFSDKLampState>

/** @name Class Properties */

/**
 * The power state.
 */
@property (nonatomic) Power power;

/**
 * The color state.
 */
@property (nonatomic, strong) LSFSDKColor *color;

/** @name Initializing an LSFSDKMyLampState Object */

/**
 * Constructs a LSFSDKMyLampState object.
 *
 * @param state  An existing LSFLampState.
 *
 * @return An LSFSDKMyLampState object
 */
-(id)initWithLSFLampState: (LSFLampState *)state;

/**
 * Constructs a LSFSDKMyLampState object.
 *
 * @warning If the provided HSVT values are outside the expected range, they will be normalized to the
 * expected range.
 *
 * @param power  The Power state.
 * @param hue  The hue component of the Color (0-360)
 * @param sat  The saturation component of a Color (0-100)
 * @param brightness  The brightness component of a Color (0-100)
 * @param colorTemp  The color temperature component of a Color (1000-20000)
 *
 * @return An LSFSDKMyLampState object
 */
-(id)initWithPower: (Power)power hue: (unsigned int)hue saturation: (unsigned int)sat brightness: (unsigned int)brightness colorTemp: (unsigned int)colorTemp;

/**
 * Constructs a LSFSDKMyLampState object.
 *
 * @param power  The Power state
 * @param colorState  The Color state
 *
 * @return An LSFSDKMyLampState object
 */
-(id)initWithPower: (Power)power color: (LSFSDKColor *)colorState;

@end
