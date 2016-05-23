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
#import <LSFSDKLampDetails.h>
#import "LSFSDKGroupMember.h"
#import "LSFSDKEffect.h"
#import "LSFSDKLampAbout.h"
#import "model/LSFLampModel.h"

@class LSFSDKPreset;

/**
 * This class represents a Lamp that is connected to the lighting controller. This class
 * provides an interface to perform Lamp operations. Supported operations include changing
 * color and power state, renaming, applying effects and presets, and retrieving lamp data.
 * Lamps are considered fully initialized when the name, power and color state, and lamp
 * details have been received. Lamps are still operational even in the uninitialized state.
 *
 * @warning This class is not meant to be instantiated directly. Lamps should be retrieved
 * from the LSFSDKLightingDirector using the [LSFSDKLightingDirector lamps] method.
 */
@interface LSFSDKLamp : LSFSDKGroupMember
{
    @protected LSFLampModel *lampModel;
}

/** @name Class Properties */

/**
 * Returns the Lamp AllJoyn about data for the current LSFSDKLamp.
 *
 * @return Reference to LSFSDKLampAbout object
 */
@property (strong, nonatomic, readonly) LSFSDKLampAbout *about;

/**
 * Returns the LSFSDKLampDetails for the current LSFSDKLamp.
 *
 * @return Reference to LSFSDKLampDetails object
 */
@property (strong, nonatomic, readonly) LSFSDKLampDetails *details;

/**
 * Returns the LSFSDKLampParameters for the current LSFSDKLamp.
 *
 * @return Reference to LSFSDKLampParameters object
 */
@property (strong, nonatomic, readonly) LSFSDKLampParameters *parameters;

/**
 * Returns the minimum color temperature value supported by the current LSFSDKLamp.
 *
 * @return The Lamps minimum color temperature value
 */
@property (nonatomic, readonly) int colorTempMin;

/**
 * Returns the maximum color temperature value supported by the current LSFSDKLamp.
 *
 * @return The Lamps maximum color temperature value
 */
@property (nonatomic, readonly) int colorTempMax;

/** @name Initializing an LSFSDKGroup Object */

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 */
-(instancetype)init NS_UNAVAILABLE;

/** @name Protected methods */

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 */
-(LSFLampModel *)getLampDataModel;

@end
