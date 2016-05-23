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
#import "model/LSFPulseEffectDataModelV2.h"

/**
 * This class represents a PulseEffect definition in the lighting controller. This class
 * provides an interface to perform PulseEffect operations. Supported operations include
 * modifying the pulse effect properties, applying the pulse effect to a lamp or group,
 * renaming, and deleting the pulse effect. Pulse effects alternate between two color states
 * for a given duration and then return to their original state. Pulse effects are considered
 * fully initialized when their name, start and end color state, duration, period, and number
 * of pulses have been received. Pulse effects are still operational and can be applied to
 * lamps or groups even in the uninitialized state.
 *
 * @warning This class is not meant to be instantiated directly. PulseEffects should be retrieved
 * from the LightingDirector using the [LSFSDKLightingDirector pulseEffects] method.
 *
 * @warning This class does not support PulseEffect creation. See [LSFSDKLightingDirector createPulseEffectWithFromState:toState:period:duration:count:name:].
 */
@interface LSFSDKPulseEffect : LSFSDKColorItem <LSFSDKEffect>
{
    @protected LSFPulseEffectDataModelV2 *pulseEffectDataModel;
}

/** @name Class Properties */

/**
 * Specifies whether the current PulseEffect is using the current state as its starting
 * state.
 */
@property (nonatomic) BOOL isStartWithCurrent;

/**
 * Specifies the LSFSDKPulseEffect starting lamp state.
 */
@property (nonatomic, strong) LSFSDKMyLampState * startState;

/**
 * Specifies the LSFSDKPulseEffect ending lamp state.
 */
@property (nonatomic, strong) LSFSDKMyLampState * endState;

/**
 * Specifies the LSFSDKPreset associated with the LSFSDKPulseEffect start state.
 */
@property (nonatomic, strong) LSFSDKPreset * startPreset;

/**
 * Specifies the LSFSDKPreset associated with the LSFSDKPulseEffect end state.
 */
@property (nonatomic, strong) LSFSDKPreset * endPreset;

/**
 * Specifies the preset ID associated with the LSFSDKPulseEffect start state.
 */
@property (nonatomic, strong) NSString * startPresetID;

/**
 * Specifies the preset ID associated with the LSFSDKPulseEffect end state.
 */
@property (nonatomic, strong) NSString * endPresetID;

/**
 * Specifies the period of the LSFSDKPulseEffect, in milliseconds.
 */
@property (nonatomic) unsigned int period;

/**
 * Specifies the duration of the LSFSDKPulseEffect, in milliseconds.
 */
@property (nonatomic) unsigned int duration;

/**
 * Specifies the number of pulses in the LSFSDKPulseEffect.
 */
@property (nonatomic) unsigned int count;

/** @name Initializing an LSFSDKPulseEffect Object */

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 */
-(instancetype)init NS_UNAVAILABLE;

/** @name Pulse Effect Operations */

/**
 * Modifies the current PulseEffect using the provided parameters.
 *
 * @param fromState The new fromState
 * @param toState The new toState
 * @param period The new period, in milliseconds
 * @param duration The new duration, in milliseconds
 * @param count The new count
 */
-(void)modifyFromState: (id<LSFSDKLampState>)fromState toState: (id<LSFSDKLampState>)toState period: (unsigned int)period duration: (unsigned int)duration count: (unsigned int)count;

/**
 * Permanently deletes the current LSFSDKPulseEffect from the lighting controller.
 *
 * @warning You cannot delete a pulse effect that is used by a scene element. The dependency
 * must be deleted first.
 */
-(void)deleteItem;

/** @name Finding Objects in a Pulse Effect */

/**
 * Tests to see if the current LSFSDKPulseEffect contains the provided LSFSDKPreset.
 *
 * @param preset The LSFSDKPreset to be confirmed a component of the LSFSDKPulseEffect
 *
 * @return Returns true if the LSFSDKPulseEffect contains the LSFSDKPreset, false otherwise
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
-(LSFPulseEffectDataModelV2 *)getPulseEffectDataModel;

@end
