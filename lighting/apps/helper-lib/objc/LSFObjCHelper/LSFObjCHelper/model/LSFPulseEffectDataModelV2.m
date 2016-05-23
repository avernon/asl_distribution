/******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

#import "LSFPulseEffectDataModelV2.h"

const NSString *PULSE_EFFECT_DEFAULT_NAME = @"<Loading pulse effect info...>";
const unsigned int PULSE_EFFECT_DEFAULT_PERIOD = 1000;
const unsigned int PULSE_EFFECT_DEFAULT_DURATION = 500;
const unsigned int PULSE_EFFECT_DEFAULT_COUNT = 10;

@implementation LSFPulseEffectDataModelV2

@synthesize endState = _endState;
@synthesize startPresetID = _startPresetID;
@synthesize endPresetID = _endPresetID;
@synthesize period = _period;
@synthesize duration = _duration;
@synthesize count = _count;
@synthesize startWithCurrent = _startWithCurrent;

-(id)init
{
    return [self initWithPulseEffectID: nil];
}

-(id)initWithPulseEffectID: (NSString *)pulseEffectID
{
    return [self initWithPulseEffectID: pulseEffectID andPulseEffectName: nil];
}

-(id)initWithPulseEffectID: (NSString *)pulseEffectID andPulseEffectName: (NSString *)pulseEffectName
{
    self = [super initWithID: pulseEffectID andName: (pulseEffectID != nil ? pulseEffectName : PULSE_EFFECT_DEFAULT_NAME)];

    if (self)
    {
        self.endState = [[LSFLampState alloc] init];
        self.startPresetID = nil;
        self.endPresetID = nil;
        self.period = PULSE_EFFECT_DEFAULT_PERIOD;
        self.duration = PULSE_EFFECT_DEFAULT_DURATION;
        self.count = PULSE_EFFECT_DEFAULT_COUNT;
        self.startWithCurrent = NO;

        endStateInitialized = NO;
        periodInitialized = NO;
        durationInitialized = NO;
        countInitialized = NO;
    }

    return self;
}

-(BOOL)containsPreset: (NSString *) presetID;
{
    return [presetID isEqualToString: [self startPresetID]] || [presetID isEqualToString: [self endPresetID]];
}

-(void)setEndState: (LSFLampState *)endState
{
    _endState = endState;
    endStateInitialized = YES;
}

-(LSFLampState *)endState
{
    return _endState;
}

-(void)setStartPresetID: (NSString *)startPresetID
{
    _startPresetID = startPresetID;
    stateInitialized = YES;
}

-(NSString *)startPresetID
{
    return _startPresetID;
}

-(void)setEndPresetID: (NSString *)endPresetID
{
    _endPresetID = endPresetID;
    endStateInitialized = YES;
}

-(NSString *)endPresetID
{
    return _endPresetID;
}

-(void)setPeriod: (unsigned int)period
{
    _period = period;
    periodInitialized = YES;
}

-(unsigned int)period
{
    return _period;
}

-(void)setDuration: (unsigned int)duration
{
    _duration = duration;
    durationInitialized = YES;
}

-(unsigned int)duration
{
    return _duration;
}

-(void)setCount: (unsigned int)count
{
    _count = count;
    countInitialized = YES;
}

-(unsigned int)count
{
    return _count;
}

-(BOOL)isInitialized
{
    return ([super isInitialized] && stateInitialized && endStateInitialized && periodInitialized && durationInitialized && countInitialized);
}

@end
