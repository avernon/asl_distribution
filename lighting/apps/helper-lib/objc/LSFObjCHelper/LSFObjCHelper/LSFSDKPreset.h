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

#import "LSFSDKMutableColorItem.h"
#import "LSFSDKEffect.h"
#import "LSFSDKPower.h"
#import "LSFSDKColor.h"
#import "model/LSFPresetModel.h"

/**
 * This class represents a Preset definition in the lighting controller. This class
 * provides an interface to perform Preset operations. Supported operations include
 * modifying the preset power and color properties, applying the preset to a lamp or
 * group, renaming, and deleting the preset. Presets are considered fully initialized
 * when the name and the power and color state have been received. Groups are still
 * operational and can be applied to lamps and groups even in the uninitialized state.
 * In general, presets are transitions effects that occur instantly.
 *
 * @warning This class is not meant to be instantiated directly. Presets should be retrieved
 * from the LSFSDKLightingDirector using the [LSFSDKLightingDirector presets] method.
 *
 * @warning This class does not support Preset creation. See [LSFSDK LightingDirector createPresetWithPower:color:presetName:].
 */
@interface LSFSDKPreset : LSFSDKMutableColorItem <LSFSDKEffect>
{
    @protected LSFPresetModel *presetModel;
}

/** @name Initializing an LSFSDKPreset Object */

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 */
-(instancetype)init NS_UNAVAILABLE;

/** @name Preset Operations */

/**
 * Modifies the current LSFSDKPreset using the provided power and color state.
 *
 * @param power New Preset power state.
 * @param color New Preset color state.
 */
-(void)modifyWithPower: (Power)power color: (LSFSDKColor *)color;

/** @name Testing a Preset */

/**
 * Tests to see if the current Preset state matches the provided Preset.
 *
 * @param preset  The Preset for comparison.
 *
 * @return Returns true if the lamp states are equal, false otherwise
 */
-(BOOL)stateEquals: (LSFSDKPreset *)preset;

/**
 * Tests to see if the current Preset state matches the provided state.
 *
 * @param state  The MyLampState for comparison.
 *
 * @return Returns true if the lamp states are equal, false otherwise
 */
-(BOOL)stateEqualsMyLampState: (LSFSDKMyLampState *)state;

/**
 * Tests to see if the current Preset power and color state matches the provided power and
 * color state.
 *
 * @param power  The Power state to be compared
 * @param color  The Color state to be compared
 *
 * @return Returns true if the power and color states are equal, false otherwise
 */
-(BOOL)stateEqualsPower: (Power)power andColor: (LSFSDKColor *)color;

/** @name Protected methods */

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 */
-(LSFPresetModel *)getPresetDataModel;

@end
