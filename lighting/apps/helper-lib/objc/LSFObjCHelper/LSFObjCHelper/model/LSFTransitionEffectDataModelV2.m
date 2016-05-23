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

#import "LSFTransitionEffectDataModelV2.h"

const NSString *TRANSITION_EFFECT_DEFAULT_NAME = @"<Loading transition effect info...>";
const unsigned int TRANSITION_EFFECT_DEFAULT_DURATION = 5000;

@implementation LSFTransitionEffectDataModelV2

@synthesize presetID = _presetID;
@synthesize duration = _duration;

-(id)init
{
    return [self initWithTransitionEffectID: nil];
}

-(id)initWithTransitionEffectID: (NSString *)transitionEffectID
{
    return [self initWithTransitionEffectID: transitionEffectID andTransitionEffectName: nil];
}

-(id)initWithTransitionEffectID: (NSString *)transitionEffectID andTransitionEffectName: (NSString *)transitionEffectName
{
    self = [super initWithID: transitionEffectID andName: (transitionEffectName != nil ? transitionEffectName : TRANSITION_EFFECT_DEFAULT_NAME)];

    if (self)
    {
        self.duration = TRANSITION_EFFECT_DEFAULT_DURATION;
        self.presetID = nil;

        durationInitialized = NO;
    }

    return self;
}

-(BOOL)containsPreset:(NSString *)presetID
{
    return [presetID isEqualToString: self.presetID];
}

-(void)setPresetID: (NSString *)presetID
{
    _presetID = presetID;
    stateInitialized = YES;
}

-(NSString *)presetID
{
    return _presetID;
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

-(BOOL)isInitialized
{
    return ([super isInitialized] && stateInitialized && durationInitialized);
}

@end
