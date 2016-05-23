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
#import "LSFSDKColorItem.h"

/**
 * Base class for Lighting items that support modification of power and color state.
 *
 * @warning Client software should not instantiate the LSFSDKMutableColorItem directly.
 */
@interface LSFSDKMutableColorItem : LSFSDKColorItem <LSFSDKLampState>

/**
 * Sets the Power of the Lighting item to on.
 */
-(void)turnOn;

/**
 * Sets the Power of the Lighting item to off.
 */
-(void)turnOff;

/**
 * Sets the Power state of the Lighting item.
 *
 * @param power The desired Power state
 */
-(void)setPower: (Power)power;

/**
 * Toggles the power state of the Lighting item.
 */
-(void)togglePower;

/**
 * Sets the color of the Lighting item to the provided HSVT color.
 *
 * @param color The desired LSFSDKColor
 */
-(void)setColor: (LSFSDKColor *)color;

/**
 * Sets the color of the Lighting item to the provided HSVT color.
 *
 * @warning If the provided HSVT values are outside the expected range, they will be normalized to the
 * expected range.
 *
 * @param hsvt  Array of HSVT values
 */
-(void)setColorHsvt: (NSArray *)hsvt;

/**
 * Changes the color state of the current Item to the provided hue.
 *
 * @param hueDegrees The hue component of the desired color (0-360)
 */
-(void)setHue: (unsigned int)hueDegrees;

/**
 * Changes the color state of the current Item to the provide saturation.
 *
 * @param saturationPercent The saturation component of the desired color (0-100)
 */
-(void)setSaturation: (unsigned int)saturationPercent;

/**
 * Changes the color state of the current Item to the provided brightness.
 *
 * @param brightnessPercent The brightness component of the desired color (0-100)
 */
-(void)setBrightness: (unsigned int)brightnessPercent;

/**
 * Changes the color state of the current Item to the provided color temperature.
 *
 * @param colorTempDegrees The color temperature component of the desired color (1000-20000)
 */
-(void)setColorTemp: (unsigned int)colorTempDegrees;

@end
