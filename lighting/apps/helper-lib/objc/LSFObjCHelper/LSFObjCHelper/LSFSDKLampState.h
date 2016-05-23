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
 * Provides an interface for developers to implement and create their own LSFSDKLampState object.
 */
@protocol LSFSDKLampState <NSObject>

/**
 * Returns the power state of the LSFSDKLampState object.
 *
 * @return Returns true if the power is on, false otherwise
 */
-(BOOL)getPowerOn;

/**
 * Sets the power state of the LSFSDKLampState object.
 *
 * @param powerOn Specifies the power state
 */
-(void)setPowerOn: (BOOL)powerOn;

/**
 * Returns the HSVT color of the LSFSDKLampState object
 *
 * @return Integer array containing the HSVT color
 */
-(NSArray *)getColorHsvt;

/**
 * Sets the color of the LSFSDKLampState object using the provided values.
 *
 * @warning If the provided HSVT values are outside the expected range, they will be normalized to the
 * expected range.
 *
 * @param hueDegrees  The hue component of the desired color (0-360)
 * @param saturationPercent  The saturation component of the desired color (0-100)
 * @param brightnessPercent  The brightness component of the desired color (0-100)
 * @param colorTempDegrees  The color temperature component of the desired color (1000-20000)
 */
-(void)setColorHsvtWithHue: (unsigned int)hueDegrees saturation: (unsigned int)saturationPercent brightness: (unsigned int)brightnessPercent colorTemp: (unsigned int)colorTempDegrees;

@end
