/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#import "LSFSceneDataModel.h"
#import <internal/LSFStateTransitionEffect.h>
#import <internal/LSFStatePulseEffect.h>

@interface LSFSceneDataModel()

@end

@implementation LSFSceneDataModel

@synthesize noEffects = _noEffects;
@synthesize transitionEffects = _transitionEffects;
@synthesize pulseEffects = _pulseEffects;

-(id)init
{
    self = [self initWithSceneID: @""];

    if (self)
    {
        sceneInitialized = NO;
    }

    return self;
}

-(id)initWithSceneID:(NSString *)theID
{
    self = [super initWithID: theID andName: @"[Loading scene info...]"];

    if (self)
    {
        self.noEffects = [[NSMutableArray alloc] init];
        self.transitionEffects = [[NSMutableArray alloc] init];
        self.pulseEffects = [[NSMutableArray alloc] init];

        sceneInitialized = NO;
    }

    return self;
}

-(void)updateNoEffect: (LSFNoEffectDataModel *)elementModel
{
    BOOL updated = NO;

    for (int i = 0; !updated && i < self.noEffects.count; i++)
    {
        LSFNoEffectDataModel *nedm = [self.noEffects objectAtIndex: i];

        if ([elementModel.theID isEqualToString: nedm.theID])
        {
            [self.noEffects replaceObjectAtIndex: i withObject: elementModel];
            updated = YES;
        }
    }

    if (!updated)
    {
        [self.noEffects addObject: elementModel];
    }
}

-(void)updateTransitionEffect: (LSFTransitionEffectDataModel *)elementModel
{
    BOOL updated = NO;

    for (int i = 0; !updated && i < self.transitionEffects.count; i++)
    {
        LSFTransitionEffectDataModel *tedm = [self.transitionEffects objectAtIndex: i];

        if ([elementModel.theID isEqualToString: tedm.theID])
        {
            [self.transitionEffects replaceObjectAtIndex: i withObject: elementModel];
            updated = YES;
        }
    }

    if (!updated)
    {
        [self.transitionEffects addObject: elementModel];
    }
}

-(void)updatePulseEffect: (LSFPulseEffectDataModel *)elementModel
{
    BOOL updated = NO;

    for (int i = 0; !updated && i < self.pulseEffects.count; i++)
    {
        LSFPulseEffectDataModel *pedm = [self.pulseEffects objectAtIndex: i];

        if ([elementModel.theID isEqualToString: pedm.theID])
        {
            [self.pulseEffects replaceObjectAtIndex: i withObject: elementModel];
            updated = YES;
        }
    }

    if (!updated)
    {
        [self.pulseEffects addObject: elementModel];
    }
}

-(BOOL)removeElement: (NSString *)elementID
{
    BOOL removed = NO;

    //Check NoEffects Array
    for (int i = 0; !removed && i < self.noEffects.count; i++)
    {
        LSFNoEffectDataModel *nedm = [self.noEffects objectAtIndex: i];

        if ([elementID isEqualToString: nedm.theID])
        {
            [self.noEffects removeObjectAtIndex: i];
            removed = YES;
        }
    }

    //Check TransitionEffects Array
    for (int i = 0; !removed && i < self.transitionEffects.count; i++)
    {
        LSFTransitionEffectDataModel *tedm = [self.transitionEffects objectAtIndex: i];

        if ([elementID isEqualToString: tedm.theID])
        {
            [self.transitionEffects removeObjectAtIndex: i];
            removed = YES;
        }
    }

    //Check PulseEffects Array
    for (int i = 0; !removed && i < self.pulseEffects.count; i++)
    {
        LSFPulseEffectDataModel *pedm = [self.pulseEffects objectAtIndex: i];

        if ([elementID isEqualToString: pedm.theID])
        {
            [self.pulseEffects removeObjectAtIndex: i];
            removed = YES;
        }
    }

    return removed;
}

-(LSFScene *)toScene
{
    // TODO - Handle preset effects properly

    LSFScene *scene = [[LSFScene alloc] init];

    NSMutableArray *stateTransitionEffects = [[NSMutableArray alloc] init];
    NSMutableArray *statePulseEffects = [[NSMutableArray alloc] init];

    //Add no effects
    for (int i = 0; i < self.noEffects.count; i++)
    {
        LSFNoEffectDataModel *nedm = [self.noEffects objectAtIndex: i];
        LSFStateTransitionEffect *ste = [[LSFStateTransitionEffect alloc] initWithLampIDs: nedm.members.lamps lampGroupIDs: nedm.members.lampGroups lampState: nedm.state andTransitionPeriod: 0];
        [stateTransitionEffects addObject: ste];
    }

    //Add transition effects
    for (int i = 0; i < self.transitionEffects.count; i++)
    {
        LSFTransitionEffectDataModel *tedm = [self.transitionEffects objectAtIndex: i];
        LSFStateTransitionEffect *ste = [[LSFStateTransitionEffect alloc] initWithLampIDs: tedm.members.lamps lampGroupIDs: tedm.members.lampGroups lampState: tedm.state andTransitionPeriod: tedm.duration];
        [stateTransitionEffects addObject: ste];
    }

    //Add pulse effects
    for (int i = 0; i < self.pulseEffects.count; i++)
    {
        LSFPulseEffectDataModel *pedm = [self.pulseEffects objectAtIndex: i];
        LSFStatePulseEffect *spe = [[LSFStatePulseEffect alloc] initWithLampIDs: pedm.members.lamps lampGroupIDs: pedm.members.lampGroups fromState: pedm.state toState: pedm.endState period: pedm.period duration: pedm.duration andNumPulses: pedm.numPulses];
        [statePulseEffects addObject: spe];
    }

    //Set Scene
    scene.transitionToStateComponent = stateTransitionEffects;
    scene.pulseWithStateComponent = statePulseEffects;

    return scene;
}

-(void)fromScene: (LSFScene *)scene
{
    //Set Scene Initialized to true so the initialized event will fire
    sceneInitialized = YES;

    NSArray *stateTransitionEffects = scene.transitionToStateComponent;
    NSArray *statePulseEffects = scene.pulseWithStateComponent;

    [self.noEffects removeAllObjects];
    [self.transitionEffects removeAllObjects];
    [self.pulseEffects removeAllObjects];

    for (int i = 0; i < stateTransitionEffects.count; i++)
    {
        LSFStateTransitionEffect *ste = [stateTransitionEffects objectAtIndex: i];

        if (ste.transitionPeriod == 0)
        {
            LSFNoEffectDataModel *nedm = [[LSFNoEffectDataModel alloc] init];
            nedm.members.lamps = ste.lamps;
            nedm.members.lampGroups = ste.lampGroups;
            nedm.state = ste.lampState;

            [self.noEffects addObject: nedm];
        }
        else
        {
            LSFTransitionEffectDataModel *tedm = [[LSFTransitionEffectDataModel alloc] init];
            tedm.members.lamps = ste.lamps;
            tedm.members.lampGroups = ste.lampGroups;
            tedm.state = ste.lampState;
            tedm.duration = ste.transitionPeriod;

            [self.transitionEffects addObject: tedm];
        }
    }

    for (int i = 0; i < statePulseEffects.count; i++)
    {
        LSFStatePulseEffect *spe = [statePulseEffects objectAtIndex: i];
        LSFPulseEffectDataModel *pedm = [[LSFPulseEffectDataModel alloc] init];

        pedm.members.lamps = spe.lamps;
        pedm.members.lampGroups = spe.lampGroups;
        pedm.state = spe.fromLampState;
        pedm.state.isNull = spe.fromLampState.isNull;
        pedm.endState = spe.toLampState;
        pedm.endState.isNull = NO;
        pedm.period = spe.period;
        pedm.duration = spe.duration;
        pedm.numPulses = spe.numPulses;

        [self.pulseEffects addObject: pedm];
    }
}

-(BOOL)containsPreset: (NSString *)presetID
{
    for (LSFNoEffectDataModel *noEffect in [self noEffects])
    {
        if ([noEffect containsPreset: presetID])
        {
            return YES;
        }
    }

    for (LSFTransitionEffectDataModel *transitionEffect in [self transitionEffects])
    {
        if ([transitionEffect containsPreset: presetID])
        {
            return YES;
        }
    }

    for (LSFPulseEffectDataModel *pulseEffect in [self pulseEffects])
    {
        if ([pulseEffect containsPreset: presetID])
        {
            return YES;
        }
    }

    return NO;
}

-(BOOL)containsGroup: (NSString *)groupID
{
    for (LSFNoEffectDataModel *noEffect in [self noEffects])
    {
        if ([noEffect containsGroup: groupID])
        {
            return YES;
        }
    }

    for (LSFTransitionEffectDataModel *transitionEffect in [self transitionEffects])
    {
        if ([transitionEffect containsGroup: groupID])
        {
            return YES;
        }
    }

    for (LSFPulseEffectDataModel *pulseEffect in [self pulseEffects])
    {
        if ([pulseEffect containsGroup: groupID])
        {
            return YES;
        }
    }

    return NO;
}

-(BOOL)isInitialized
{
    return ([super isInitialized] && sceneInitialized);
}

@end
