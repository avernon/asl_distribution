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

#import "LSFPendingEffect.h"
#import <LSFSDKLightingDirector.h>

@implementation LSFPendingEffect

@synthesize state = _state;
@synthesize endState = _endState;
@synthesize duration = _duration;
@synthesize period = _period;
@synthesize pulses = _pulses;

-(id)init
{
    self = [super init];

    if (self)
    {
        _state = nil;
        _endState = nil;
        _duration = 5000;
        _period = 1000;
        _pulses = 10;
    }

    return self;
}

-(id)initFromEffectID: (NSString *)effectID
{
    self = [self init];

    id<LSFSDKEffect> effect = [[LSFSDKLightingDirector getLightingDirector] getEffectWithID: effectID];

    if (effect)
    {
        self.theID = effect.theID;
        self.name = effect.name;

        if ([effect isKindOfClass: [LSFSDKPreset class]])
        {
            LSFSDKPreset *preset = (LSFSDKPreset *) effect;
            self.type = PRESET;
            self.state = [preset getState];
        }
        else if ([effect isKindOfClass: [LSFSDKTransitionEffect class]])
        {
            LSFSDKTransitionEffect *transitionEffect = (LSFSDKTransitionEffect *) effect;
            self.type = TRANSITION;
            self.state = [transitionEffect getState];
            self.duration = [transitionEffect duration];
        }
        else if ([effect isKindOfClass: [LSFSDKPulseEffect class]])
        {
            LSFSDKPulseEffect *pulseEffect = (LSFSDKPulseEffect *)effect;
            self.type = PULSE;
            self.state = [pulseEffect startState];
            self.endState = [pulseEffect endState];
            self.duration = [pulseEffect duration];
            self.period = [pulseEffect period];
            self.pulses = [pulseEffect count];
        }
    }
    else
    {
        NSLog(@"Effect not found in Lighting Director. Returning default pending object");
    }

    return self;
}

@end
