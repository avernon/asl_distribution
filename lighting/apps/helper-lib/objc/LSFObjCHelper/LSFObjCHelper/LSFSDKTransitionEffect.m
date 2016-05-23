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

#import "LSFSDKTransitionEffect.h"
#import "LSFSDKLamp.h"
#import "LSFSDKGroup.h"
#import "LSFSDKLightingItemUtil.h"
#import "LSFSDKLightingDirector.h"
#import "manager/LSFSDKAllJoynManager.h"
#import "model/LSFSDKLightingItemHasComponentFilter.h"

@implementation LSFSDKTransitionEffect

@synthesize preset = _preset;
@synthesize presetID = _presetID;
@synthesize duration = _duration;

-(void)modify: (id<LSFSDKLampState>)state duration: (unsigned int)duration
{
    NSString *errorContext = @"LSFSDKTransitionEffect modify: error";

    if ([self postInvalidArgIfNull: errorContext object: state])
    {
        if ([state isKindOfClass: [LSFSDKPreset class]])
        {
            [self postErrorIfFailure: errorContext status: [[LSFSDKAllJoynManager getTransitionEffectManager] updateTransitionEffectWithID: transitionEffectDataModel.theID andTransitionEffect: [LSFSDKLightingItemUtil createTransitionEffectFromPreset:(LSFSDKPreset *)state duration: duration]]];
        }
        else
        {
            [self postErrorIfFailure: errorContext status: [[LSFSDKAllJoynManager getTransitionEffectManager] updateTransitionEffectWithID: transitionEffectDataModel.theID andTransitionEffect: [LSFSDKLightingItemUtil createTransitionEffectFromPower: [state getPowerOn] hsvt: [state getColorHsvt] duration: duration]]];
        }
    }
}

-(void)deleteItem
{
    NSString *errorContext = @"LSFSDKTransitionEffect deleteTransitionEffect: error";

    [self postErrorIfFailure: errorContext status: [[LSFSDKAllJoynManager getTransitionEffectManager] deleteTransitionEffectWithID: transitionEffectDataModel.theID]];
}

-(BOOL)hasPreset: (LSFSDKPreset *)preset
{
    NSString *errorContext = @"LSFSDKTransitionEffect hasPreset: error";
    return ([self postInvalidArgIfNull: errorContext object: preset]) ? [self hasPresetWithID: preset.theID] : NO;
}

-(BOOL)hasPresetWithID:(NSString *)presetID
{
    return [transitionEffectDataModel containsPreset: presetID];
}

/*
 * LSFSDKEffect implementation
 */
-(void)applyToGroupMember: (LSFSDKGroupMember *)member
{
    NSString *errorContext = @"LSFSDKTransitionEffect applyToGroupMember: error";

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
    NSString *errorContext = @"LSFSDKTransitionEffect rename: error";

    if ([self postInvalidArgIfNull: errorContext object: name])
    {
        [self postErrorIfFailure: errorContext status: [[LSFSDKAllJoynManager getTransitionEffectManager] setTransitionEffectNameWithID: transitionEffectDataModel.theID transitionEffectName: name]];
    }
}

-(BOOL)hasComponent:(LSFSDKLightingItem *)item
{
    NSString *errorContext = @"LSFSDKTransitionEffect hasComponent: error";
    return ([self postInvalidArgIfNull: errorContext object: item]) ? [self hasPresetWithID: item.theID] : NO;
}

-(NSArray *)getDependentCollection
{
    NSMutableArray *dependents = [[NSMutableArray alloc] init];

    LSFSDKLightingDirector *director = [LSFSDKLightingDirector getLightingDirector];
    [dependents addObjectsFromArray: [[[director lightingManager] sceneElementCollectionManager] getSceneElementsCollectionWithFilter:[[LSFSDKLightingItemHasComponentFilter alloc] initWithComponent: self]]];

    return [NSArray arrayWithArray: dependents];
}

-(LSFDataModel *)getColorDataModel
{
    return [self getTransitionEffectDataModel];
}

-(void)postError:(NSString *)name status:(LSFResponseCode)status
{
    dispatch_async([[[LSFSDKLightingDirector getLightingDirector] lightingManager] dispatchQueue], ^{
        [[[[LSFSDKLightingDirector getLightingDirector] lightingManager] transitionEffectCollectionManager] sendErrorEvent: name statusCode: status itemID: transitionEffectDataModel.theID];
    });
}

/**
 * <b>WARNING: This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.</b>
 */
-(LSFTransitionEffectDataModelV2 *)getTransitionEffectDataModel
{
    return transitionEffectDataModel;
}

-(NSString *)presetID
{
    return transitionEffectDataModel.presetID;
}

-(LSFSDKPreset *)preset
{
    return [[LSFSDKLightingDirector getLightingDirector] getPresetWithID: self.presetID];
}

-(unsigned int)duration
{
    return transitionEffectDataModel.duration;
}

@end
