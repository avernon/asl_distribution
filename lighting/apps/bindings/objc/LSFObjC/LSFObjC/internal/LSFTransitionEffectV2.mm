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

#import "LSFTransitionEffectV2.h"
#import <LSFTypes.h>

@interface LSFTransitionEffectV2()

@property (nonatomic, readonly) lsf::TransitionEffect *transitionEffect;

@end

@implementation LSFTransitionEffectV2

@synthesize transitionEffect = _transitionEffect;

-(id)init
{
    self = [super init];

    if (self)
    {
        self.handle = new lsf::TransitionEffect();
    }

    return self;
}

-(id)initWithLampState: (LSFLampState *)lampState
{
    self = [super init];

    if (self)
    {
        self.handle = new lsf::TransitionEffect(*static_cast<lsf::LampState*>(lampState.handle));
    }

    return self;
}

-(id)initWithLampState: (LSFLampState *)lampState transitionPeriod: (unsigned int)transitionPeriod
{
    self = [super init];

    if (self)
    {
        self.handle = new lsf::TransitionEffect(*static_cast<lsf::LampState*>(lampState.handle), transitionPeriod);
    }

    return self;
}

-(id)initWithPresetID: (NSString *)presetID
{
    self = [super init];

    if (self)
    {
        std::string pid([presetID UTF8String]);
        self.handle = new lsf::TransitionEffect(pid);
    }

    return self;
}

-(id)initWithPresetID: (NSString *)presetID transitionPeriod: (unsigned int)transitionPeriod
{
    self = [super init];

    if (self)
    {
        std::string pid([presetID UTF8String]);
        self.handle = new lsf::TransitionEffect(pid, transitionPeriod);
    }

    return self;
}

-(void)setLampState: (LSFLampState *)lampState
{
    self.transitionEffect->state = *(static_cast<lsf::LampState*>(lampState.handle));
}

-(LSFLampState *)lampState
{
    LSFLampState *lampState = [[LSFLampState alloc] initWithOnOff: self.transitionEffect->state.onOff brightness: self.transitionEffect->state.brightness hue: self.transitionEffect->state.hue saturation: self.transitionEffect->state.saturation colorTemp: self.transitionEffect->state.colorTemp];
    lampState.isNull = self.transitionEffect->state.nullState;

    return lampState;
}

-(void)setTransitionPeriod: (unsigned int)transitionPeriod
{
    self.transitionEffect->transitionPeriod = transitionPeriod;
}

-(unsigned int)transitionPeriod
{
    return self.transitionEffect->transitionPeriod;
}

-(void)setPresetID: (NSString *)presetID
{
    std::string pid([presetID UTF8String]);
    self.transitionEffect->presetID = pid;
}

-(NSString *)presetID
{
    return [NSString stringWithUTF8String: (self.transitionEffect->presetID).c_str()];
}

-(void)setInvalidArgs: (BOOL)invalidArgs
{
    self.transitionEffect->invalidArgs = invalidArgs;
}

-(BOOL)invalidArgs
{
    return self.transitionEffect->invalidArgs;
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
-(lsf::TransitionEffect *)transitionEffect
{
    return static_cast<lsf::TransitionEffect*>(self.handle);
}

@end
