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

#import "LSFStateTransitionEffect.h"
#import "LSFUtils.h"
#import <LSFTypes.h>

@interface LSFStateTransitionEffect()

@property (nonatomic, readonly) lsf::TransitionLampsLampGroupsToState *stateTransitionEffect;

@end

@implementation LSFStateTransitionEffect

@synthesize stateTransitionEffect = _stateTransitionEffect;

-(id)initWithLampIDs: (NSArray *)lampIDs lampGroupIDs: (NSArray *)lampGroupIDs andLampState: (LSFLampState *)lampState
{
    self = [super init];
    
    if (self)
    {
        lsf::LSFStringList lampIDList = [LSFUtils convertNSArrayToStringList: lampIDs];
        lsf::LSFStringList lampGroupIDList = [LSFUtils convertNSArrayToStringList: lampGroupIDs];
        self.handle = new lsf::TransitionLampsLampGroupsToState(lampIDList, lampGroupIDList, *(static_cast<lsf::LampState*>(lampState.handle)));
    }
    
    return self;
}

-(id)initWithLampIDs: (NSArray *)lampIDs lampGroupIDs: (NSArray *)lampGroupIDs lampState: (LSFLampState *)lampState andTransitionPeriod: (unsigned int)transitionPeriod
{
    self = [super init];
    
    if (self)
    {
        lsf::LSFStringList lampIDList = [LSFUtils convertNSArrayToStringList: lampIDs];
        lsf::LSFStringList lampGroupIDList = [LSFUtils convertNSArrayToStringList: lampGroupIDs];
        self.handle = new lsf::TransitionLampsLampGroupsToState(lampIDList, lampGroupIDList, *(static_cast<lsf::LampState*>(lampState.handle)), transitionPeriod);
    }
    
    return self;
}

-(void)setLamps: (NSArray *)lampIDs
{
    lsf::LSFStringList lampIDList = [LSFUtils convertNSArrayToStringList: lampIDs];
    self.stateTransitionEffect->lamps = lampIDList;
}

-(NSArray *)lamps
{
    lsf::LSFStringList lampIDs = self.stateTransitionEffect->lamps;
    return [LSFUtils convertStringListToNSArray: lampIDs];
}

-(void)setLampGroups: (NSArray *)lampGroupIDs
{
    lsf::LSFStringList lampGroupIDList = [LSFUtils convertNSArrayToStringList: lampGroupIDs];
    self.stateTransitionEffect->lampGroups = lampGroupIDList;
}

-(NSArray *)lampGroups
{
    lsf::LSFStringList lampGroupIDs = self.stateTransitionEffect->lampGroups;
    return [LSFUtils convertStringListToNSArray: lampGroupIDs];
}

-(void)setTransitionPeriod: (unsigned int)transitionPeriod
{
    self.stateTransitionEffect->transitionPeriod = transitionPeriod;
}

-(unsigned int)transitionPeriod
{
    return self.stateTransitionEffect->transitionPeriod;
}

-(void)setLampState: (LSFLampState *)lampState
{
    self.stateTransitionEffect->state = *(static_cast<lsf::LampState*>(lampState.handle));
}

-(LSFLampState *)lampState
{
    return [[LSFLampState alloc] initWithOnOff: self.stateTransitionEffect->state.onOff brightness: self.stateTransitionEffect->state.brightness hue: self.stateTransitionEffect->state.hue saturation: self.stateTransitionEffect->state.saturation colorTemp: self.stateTransitionEffect->state.colorTemp];
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
- (lsf::TransitionLampsLampGroupsToState *)stateTransitionEffect
{
    return static_cast<lsf::TransitionLampsLampGroupsToState*>(self.handle);
}

@end
