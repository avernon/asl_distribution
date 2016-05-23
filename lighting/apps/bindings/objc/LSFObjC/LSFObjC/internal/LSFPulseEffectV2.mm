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

#import "LSFPulseEffectV2.h"
#import <LSFTypes.h>

@interface LSFPulseEffectV2()

@property (nonatomic, readonly) lsf::PulseEffect *pulseEffect;

@end

@implementation LSFPulseEffectV2

@synthesize pulseEffect = _pulseEffect;

-(id)init
{
    self = [super init];

    if (self)
    {
        self.handle = new lsf::PulseEffect();
    }

    return self;
}

-(id)initWithToLampState: (LSFLampState *)toLampState period: (unsigned int)period duration: (unsigned int)duration numPulses: (unsigned int)numPulses
{
    self = [super init];

    if (self)
    {
        self.handle = new lsf::PulseEffect(*static_cast<lsf::LampState*>(toLampState.handle), period, duration, numPulses);
    }

    return self;
}

-(id)initWithToLampState: (LSFLampState *)toLampState period: (unsigned int)period duration: (unsigned int)duration numPulses: (unsigned int)numPulses fromLampState: (LSFLampState *)fromLampState
{
    self = [super init];

    if (self)
    {
        self.handle = new lsf::PulseEffect(*static_cast<lsf::LampState*>(toLampState.handle), period, duration, numPulses, *static_cast<lsf::LampState*>(fromLampState.handle));
    }

    return self;
}

-(id)initWithToPreset: (NSString *)toLampPreset period: (unsigned int)period duration: (unsigned int)duration numPulses: (unsigned int)numPulses
{
    self = [super init];

    if (self)
    {
        std::string tpid([toLampPreset UTF8String]);
        self.handle = new lsf::PulseEffect(tpid, period, duration, numPulses);
    }

    return self;
}

-(id)initWithToPreset: (NSString *)toLampPreset period: (unsigned int)period duration: (unsigned int)duration numPulses: (unsigned int)numPulses fromPreset: (NSString *)fromLampPreset
{
    self = [super init];

    if (self)
    {
        std::string tpid([toLampPreset UTF8String]);
        std::string fpid([fromLampPreset UTF8String]);
        self.handle = new lsf::PulseEffect(tpid, period, duration, numPulses, fpid);
    }

    return self;
}

-(void)setToState: (LSFLampState *)toState
{
    self.pulseEffect->toState = *(static_cast<lsf::LampState*>(toState.handle));
}

-(LSFLampState *)toState
{
    LSFLampState *toLampState = [[LSFLampState alloc] initWithOnOff: self.pulseEffect->toState.onOff brightness: self.pulseEffect->toState.brightness hue: self.pulseEffect->toState.hue saturation: self.pulseEffect->toState.saturation colorTemp: self.pulseEffect->toState.colorTemp];
    toLampState.isNull = self.pulseEffect->toState.nullState;

    return toLampState;
}

-(void)setPulsePeriod: (unsigned int)pulsePeriod
{
    self.pulseEffect->pulsePeriod = pulsePeriod;
}

-(unsigned int)pulsePeriod
{
    return self.pulseEffect->pulsePeriod;
}

-(void)setPulseDuration: (unsigned int)pulseDuration
{
    self.pulseEffect->pulseDuration = pulseDuration;
}

-(unsigned int)pulseDuration
{
    return self.pulseEffect->pulseDuration;
}

-(void)setNumPulses: (unsigned int)numPulses
{
    self.pulseEffect->numPulses = numPulses;
}

-(unsigned int)numPulses
{
    return self.pulseEffect->numPulses;
}

-(void)setFromState: (LSFLampState *)fromState
{
    self.pulseEffect->fromState = *(static_cast<lsf::LampState*>(fromState.handle));
}

-(LSFLampState *)fromState
{
    LSFLampState *fromLampState = [[LSFLampState alloc] initWithOnOff: self.pulseEffect->fromState.onOff brightness: self.pulseEffect->fromState.brightness hue: self.pulseEffect->fromState.hue saturation: self.pulseEffect->fromState.saturation colorTemp: self.pulseEffect->fromState.colorTemp];
    fromLampState.isNull = self.pulseEffect->fromState.nullState;

    return fromLampState;
}

-(void)setToPreset: (NSString *)toPreset
{
    std::string tpid([toPreset UTF8String]);
    self.pulseEffect->toPreset = tpid;
}

-(NSString *)toPreset
{
    return [NSString stringWithUTF8String: (self.pulseEffect->toPreset).c_str()];
}

-(void)setFromPreset: (NSString *)fromPreset
{
    std::string fpid([fromPreset UTF8String]);
    self.pulseEffect->fromPreset = fpid;
}

-(NSString *)fromPreset
{
    return [NSString stringWithUTF8String: (self.pulseEffect->fromPreset).c_str()];
}

-(void)setInvalidArgs: (BOOL)invalidArgs
{
    self.pulseEffect->invalidArgs = invalidArgs;
}

-(BOOL)invalidArgs
{
    return self.pulseEffect->invalidArgs;
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
-(lsf::PulseEffect *)pulseEffect
{
    return static_cast<lsf::PulseEffect*>(self.handle);
}

@end
