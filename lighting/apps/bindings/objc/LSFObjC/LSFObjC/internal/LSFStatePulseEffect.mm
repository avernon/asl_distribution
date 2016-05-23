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

#import "LSFStatePulseEffect.h"
#import "LSFUtils.h"
#import <LSFTypes.h>

@interface LSFStatePulseEffect()

@property (nonatomic, readonly) lsf::PulseLampsLampGroupsWithState *statePulseEffect;

@end

@implementation LSFStatePulseEffect

@synthesize statePulseEffect = _statePulseEffect;

-(id)initWithLampIDs: (NSArray *)lampIDs lampGroupIDs: (NSArray *)lampGroupIDs toState: (LSFLampState *)toLampState period: (unsigned int)period duration: (unsigned int)duration andNumPulses: (unsigned int)numPulses
{
    self = [super init];
    
    if (self)
    {
        lsf::LSFStringList lampIDList = [LSFUtils convertNSArrayToStringList: lampIDs];
        lsf::LSFStringList lampGroupIDList = [LSFUtils convertNSArrayToStringList: lampGroupIDs];
        self.handle = new lsf::PulseLampsLampGroupsWithState(lampIDList, lampGroupIDList, *(static_cast<lsf::LampState*>(toLampState.handle)), period, duration, numPulses);
    }
    
    return self;
}

-(id)initWithLampIDs: (NSArray *)lampIDs lampGroupIDs: (NSArray *)lampGroupIDs fromState: (LSFLampState *)fromLampState toState: (LSFLampState *)toLampState period: (unsigned int)period duration: (unsigned int)duration andNumPulses: (unsigned int)numPulses
{
    self = [super init];
    
    if (self)
    {
        lsf::LSFStringList lampIDList = [LSFUtils convertNSArrayToStringList: lampIDs];
        lsf::LSFStringList lampGroupIDList = [LSFUtils convertNSArrayToStringList: lampGroupIDs];
        self.handle = new lsf::PulseLampsLampGroupsWithState(lampIDList, lampGroupIDList, *(static_cast<lsf::LampState*>(fromLampState.handle)), *(static_cast<lsf::LampState*>(toLampState.handle)), period, duration, numPulses);
    }
    
    return self;
}

-(void)setLamps: (NSArray *)lampIDs
{
    lsf::LSFStringList lampIDList = [LSFUtils convertNSArrayToStringList: lampIDs];
    self.statePulseEffect->lamps = lampIDList;
}

-(NSArray *)lamps
{
    lsf::LSFStringList lampIDs = self.statePulseEffect->lamps;
    return [LSFUtils convertStringListToNSArray: lampIDs];
}

-(void)setLampGroups: (NSArray *)lampGroupIDs
{
    lsf::LSFStringList lampGroupIDList = [LSFUtils convertNSArrayToStringList: lampGroupIDs];
    self.statePulseEffect->lampGroups = lampGroupIDList;
}

-(NSArray *)lampGroups
{
    lsf::LSFStringList lampGroupIDs = self.statePulseEffect->lampGroups;
    return [LSFUtils convertStringListToNSArray: lampGroupIDs];
}

-(void)setPeriod: (unsigned int)period
{
    self.statePulseEffect->pulsePeriod = period;
}

-(unsigned int)period
{
    return self.statePulseEffect->pulsePeriod;
}

-(void)setDuration: (unsigned int)duration
{
    self.statePulseEffect->pulseDuration = duration;
}

-(unsigned int)duration
{
    return self.statePulseEffect->pulseDuration;
}

-(void)setNumPulses: (unsigned int)numPulses
{
    self.statePulseEffect->numPulses = numPulses;
}

-(unsigned int)numPulses
{
    return self.statePulseEffect->numPulses;
}

-(void)setFromLampState: (LSFLampState *)fromLampState
{
    self.statePulseEffect->fromState = *(static_cast<lsf::LampState*>(fromLampState.handle));
}

-(LSFLampState *)fromLampState
{
    LSFLampState *fromState = [[LSFLampState alloc] initWithOnOff: self.statePulseEffect->fromState.onOff brightness: self.statePulseEffect->fromState.brightness hue: self.statePulseEffect->fromState.hue saturation: self.statePulseEffect->fromState.saturation colorTemp: self.statePulseEffect->fromState.colorTemp];
    fromState.isNull = self.statePulseEffect->fromState.nullState;

    return fromState;
}

-(void)setToLampState: (LSFLampState *)toLampState
{
    self.statePulseEffect->toState = *(static_cast<lsf::LampState*>(toLampState.handle));
}

-(LSFLampState *)toLampState
{
    return [[LSFLampState alloc] initWithOnOff: self.statePulseEffect->toState.onOff brightness: self.statePulseEffect->toState.brightness hue: self.statePulseEffect->toState.hue saturation: self.statePulseEffect->toState.saturation colorTemp: self.statePulseEffect->toState.colorTemp];
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
- (lsf::PulseLampsLampGroupsWithState *)statePulseEffect
{
    return static_cast<lsf::PulseLampsLampGroupsWithState*>(self.handle);
}

@end
