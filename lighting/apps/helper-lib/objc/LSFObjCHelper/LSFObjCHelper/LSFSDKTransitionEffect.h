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
#import "LSFSDKColorItem.h"
#import "LSFSDKEffect.h"
#import "LSFSDKLampState.h"
#import "LSFSDKPreset.h"
#import "model/LSFTransitionEffectDataModelV2.h"

/**
 * This class represents a TransitionEffect definition in the lighting controller. This class
 * provides an interface to perform TransitionEffect operations. Supported operations include
 * modifying the transition effect properties, applying the transition effect to a lamp or group,
 * renaming, and deleting the transition effect. Transition effects gradually changes the color
 * state of a lamp or group over a given duration. Specifying a duration zero will change the
 * lamp or group state immediately. Transition effects are considered fully initialized if the
 * name, color state, and duration have been received. Transition effects are still operational
 * and can be applied to lamps or groups even in the uninitialized state.
 *
 * @warning This class is not meant to be instantiated directly. TransitionEffects should be retrieved
 * from the LSFSDKLightingDirector using the [LSFSDKLightingDirector transitionEffects] method.
 *
 * @warning This class does not support TransitionEffect creation. See [LSFSDKLightingDirector createTransitionEffectWithLampState:duration:name:].
 */
@interface LSFSDKTransitionEffect : LSFSDKColorItem <LSFSDKEffect>
{
    @protected LSFTransitionEffectDataModelV2 *transitionEffectDataModel;
}

/** @name Class Properties */

/**
 * Specifies the Preset associated with the current LSFSDKTransitionEffect.
 *
 * @warning This method may return null if the LSFSDKTransitionEffect was not created
 * using an existing LSFSDKPreset.
 *
 * @return The LSFSDKPreset associated with the LSFSDKTransitionEffect
 */
@property (nonatomic, strong) LSFSDKPreset *preset;

/**
 * Specifies the preset ID associated with the current LSFSDKTransitionEffect.
 *
 * @warning This method may return null if the LSFSDKTransitionEffect was not created
 * using an existing LSFSDKPreset.
 *
 * @return The preset ID associated with the LSFSDKTransitionEffect
 */
@property (nonatomic, strong) NSString *presetID;

/**
 * Specifies the duration of the current LSFSDKTransitionEffect.
 */
@property (nonatomic) unsigned int duration;

/** @name Initializing an LSFSDKTransitionEffect Object */

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 */
-(instancetype)init NS_UNAVAILABLE;

/** @name Transition Effect Operations */

/**
 * Modifies the current LSFSDKTransitionEffect using the provided lamp state and duration.
 *
 * @param state The new LampState
 * @param duration The new duration, in milliseconds
 */
-(void)modify: (id<LSFSDKLampState>)state duration: (unsigned int)duration;

/**
 * Permanently deletes the current LSFSDKTransitionEffect from the lighting controller.
 *
 * @warning You cannot delete a transition effect that is used by a scene element. The dependency
 * must be deleted first.
 */
-(void)deleteItem;

/** @name Finding Objects in a Transition Effect */

/**
 * Tests to see if the current LSFSDKTransitionEffect contains the provided Preset.
 *
 * @param preset The Preset to be confirmed a component of the LSFSDKTransitionEffect
 *
 * @return Returns true if the LSFSDKTransitionEffect contains the Preset, false otherwise
 */
-(BOOL)hasPreset: (LSFSDKPreset *)preset;

/** @name Protected methods */

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 *
 * @param presetID  The ID of the preset
 */
-(BOOL)hasPresetWithID: (NSString *)presetID;

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 */
-(LSFTransitionEffectDataModelV2 *)getTransitionEffectDataModel;

@end
