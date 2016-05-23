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

/**
 * This class encapsulates colors in the HSVT color space. Every color contains brightness,
 * hue, saturation, and colorTemp. The brightness must be between 0-100, hue must be
 * between 0-360, saturation must be between 0-100, and colorTemp must be between
 * 1000-20000.
 */
@interface LSFSDKColor : NSObject

/** @name Class Properties */

/**
 * The hue component of the LSFSDKColor object (0-360).
 *
 * @warning If the provided HSVT values are outside the expected range, they will be normalized to the
 * expected range.
 */
@property (nonatomic) unsigned int hue;

/**
 * The saturation component of the LSFSDKColor object (0-100).
 *
 * @warning If the provided HSVT values are outside the expected range, they will be normalized to the
 * expected range.
 */
@property (nonatomic) unsigned int saturation;

/**
 * The brightness component of the LSFSDKColor object (0-100).
 *
 * @warning If the provided HSVT values are outside the expected range, they will be normalized to the
 * expected range.
 */
@property (nonatomic) unsigned int brightness;

/**
 * The color temperature component of the LSFSDKColor object (1000-20000).
 *
 * @warning If the provided HSVT values are outside the expected range, they will be normalized to the
 * expected range.
 */
@property (nonatomic) unsigned int colorTemp;

/** @name Initializing an LSFSDKColor Object */

/**
 * Constructs an LSFSDKColor object using the provided HSVT values.
 *
 * @warning If the provided HSVT values are outside the expected range, they will be normalized to the
 * expected range.
 *
 * @param hsvt  Array of HSVT values
 */
-(id)initWithHsvt: (NSArray *)hsvt;

/**
 * Constructs an LSFSDKColor object using the provided HSVT values.
 *
 * @warning If the provided HSVT values are outside the expected range, they will be normalized to the
 * expected range.
 *
 * @param hueValue  The hue component of the color (0-360)
 * @param satValue  The saturation component of the color (0-100)
 * @param brightnessValue  The brightness component of the color (0-100)
 * @param colorTempValue  The colorTemp component of the color (1000-20000)
 */
-(id)initWithHue: (unsigned int)hueValue saturation: (unsigned int)satValue brightness: (unsigned int)brightnessValue colorTemp: (unsigned int)colorTempValue;

/**
 * Constructs an LSFSDKColor object using the provided LSFSDKColor object.
 *
 * @param color  The other Color object
 */
-(id)initWithColor: (LSFSDKColor *)color;

/** @name Constants */

/**
 * Specifies the color red.
 */
+(LSFSDKColor *)red;

/**
 * Specifies the color green.
 */
+(LSFSDKColor *)green;

/**
 * Specifies the color blue.
 */
+(LSFSDKColor *)blue;

/**
 * Specifies the color white.
 */
+(LSFSDKColor *)white;

@end
