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

#import "LSFSDKPulseEffect.h"
#import "LSFSDKLamp.h"
#import "LSFSDKGroup.h"
#import "LSFSDKLightingItemUtil.h"
#import "LSFSDKLightingDirector.h"
#import "manager/LSFSDKAllJoynManager.h"
#import "model/LSFSDKLightingItemHasComponentFilter.h"

@implementation LSFSDKPulseEffect

@synthesize isStartWithCurrent = _isStartWithCurrent;
@synthesize startState = _startState;
@synthesize endState = _endState;
@synthesize startPreset = _startPreset;
@synthesize endPreset = _endPreset;
@synthesize startPresetID = _startPresetID;
@synthesize endPresetID = _endPresetID;
@synthesize period = _period;
@synthesize duration = _duration;
@synthesize count = _count;

-(void)modifyFromState: (id<LSFSDKLampState>)fromState toState: (id<LSFSDKLampState>)toState period: (unsigned int)period duration: (unsigned int)duration count: (unsigned int)count
{
    NSString *errorContext = @"LSFSDKPulseEffect modify: error";

    if ([self postInvalidArgIfNull: errorContext object: fromState] && [self postInvalidArgIfNull: errorContext object: toState])
    {
        if (([fromState isKindOfClass: [LSFSDKPreset class]]) && ([toState isKindOfClass: [LSFSDKPreset class]]))
        {
            [self postErrorIfFailure: errorContext status: [[LSFSDKAllJoynManager getPulseEffectManager] updatePulseEffectWithID: pulseEffectDataModel.theID andPulseEffect: [LSFSDKLightingItemUtil createPulseeffectFromPreset: (LSFSDKPreset *)fromState toPreset: (LSFSDKPreset *)toState period: period duration: duration count: count]]];
        }
        else
        {
            [self postErrorIfFailure: errorContext status: [[LSFSDKAllJoynManager getPulseEffectManager] updatePulseEffectWithID: pulseEffectDataModel.theID andPulseEffect: [LSFSDKLightingItemUtil createPulseEffectWithFromPowerOn: [fromState getPowerOn] fromColorHsvt: [fromState getColorHsvt] toPowerOn: [toState getPowerOn] toColorHsvt: [toState getColorHsvt] period: period duration: duration count: count]]];
        }
    }
}

-(void)deleteItem
{
    NSString *errorContext = @"LSFSDKPulseEffect delete: error";

    [self postErrorIfFailure: errorContext status: [[LSFSDKAllJoynManager getPulseEffectManager] deletePulseEffectWithID: pulseEffectDataModel.theID]];
}

-(BOOL)hasPreset:(LSFSDKPreset *)preset
{
    NSString *errorContext = @"LSFSDKPulseEffect hasPreset: error";
    return ([self postInvalidArgIfNull: errorContext object: preset]) ? [self hasPresetWithID: preset.theID] : NO;
}

-(BOOL)hasPresetWithID:(NSString *)presetID
{
    return [pulseEffectDataModel containsPreset: presetID];
}

/*
 * LSFSDKEffect implementation
 */
-(void)applyToGroupMember: (LSFSDKGroupMember *)member
{
    NSString *errorContext = @"LSFSDKPulseEffect applyToGroupMember: error";

    if ([self postInvalidArgIfNull: errorContext object: member])
    {
        [member applyEffect: self];
    }
}

/*
 * Override base class functions
 */
-(void)rename:(NSString *)name
{
    NSString *errorContext = @"LSFSDKPulseEffect rename: error";

    if ([self postInvalidArgIfNull: errorContext object: name])
    {
        [self postErrorIfFailure: errorContext status: [[LSFSDKAllJoynManager getPulseEffectManager] setPulseEffectNameWithID: pulseEffectDataModel.theID pulseEffectName: name]];
    }
}

-(LSFDataModel *)getColorDataModel
{
    return [self getPulseEffectDataModel];
}

-(BOOL)hasComponent:(LSFSDKLightingItem *)item
{
    NSString *errorContext = @"LSFSDKPulseEffect hasComponent: error";
    return ([self postInvalidArgIfNull: errorContext object: item]) ? [self hasPresetWithID: item.theID] : NO;
}

-(NSArray*)getDependentCollection
{
    LSFSDKLightingDirector *director = [LSFSDKLightingDirector getLightingDirector];

    NSMutableArray *dependents = [[NSMutableArray alloc] init];
    [dependents addObjectsFromArray: [[[director lightingManager] sceneElementCollectionManager] getSceneElementsCollectionWithFilter: [[LSFSDKLightingItemHasComponentFilter alloc] initWithComponent: self]]];

    return [NSArray arrayWithArray: dependents];
}

-(void)postError:(NSString *)name status:(LSFResponseCode)status
{
    dispatch_async([[[LSFSDKLightingDirector getLightingDirector] lightingManager] dispatchQueue], ^{
        [[[[LSFSDKLightingDirector getLightingDirector] lightingManager] pulseEffectCollectionManager] sendErrorEvent: name statusCode: status itemID: pulseEffectDataModel.theID];
    });
}

/**
 * <b>WARNING: This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.</b>
 */
-(LSFPulseEffectDataModelV2 *)getPulseEffectDataModel
{
    return pulseEffectDataModel;
}

-(BOOL)isStartWithCurrent
{
    return [pulseEffectDataModel startWithCurrent];
}

-(LSFSDKMyLampState *)startState
{
    return [self getState];
}

-(LSFSDKMyLampState *)endState
{
    LSFLampState *state = [pulseEffectDataModel endState];
    return [[LSFSDKMyLampState alloc] initWithPower: (state.brightness ? ON : OFF) color: [[LSFSDKColor alloc] initWithHue: state.hue saturation: state.saturation brightness: state.brightness colorTemp: state.colorTemp]];
}

-(LSFSDKPreset *)startPreset
{
    return [[LSFSDKLightingDirector getLightingDirector] getPresetWithID: [self startPresetID]];
}

-(LSFSDKPreset *)endPreset
{
    return [[LSFSDKLightingDirector getLightingDirector] getPresetWithID: [self endPresetID]];
}

-(NSString *)startPresetID
{
    return [pulseEffectDataModel startPresetID];
}

-(NSString *)endPresetID
{
    return [pulseEffectDataModel endPresetID];
}

-(unsigned int)period
{
    return [pulseEffectDataModel period];
}

-(unsigned int)duration
{
    return [pulseEffectDataModel duration];
}

-(unsigned int)count
{
    return [pulseEffectDataModel count];
}

@end
