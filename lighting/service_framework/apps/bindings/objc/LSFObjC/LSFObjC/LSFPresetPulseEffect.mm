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

#import "LSFPresetPulseEffect.h"
#import "LSFTypes.h"
#import "LSFUtils.h"

@interface LSFPresetPulseEffect()

@property (nonatomic, readonly) lsf::PulseLampsLampGroupsWithPreset *presetPulseEffect;

@end

@implementation LSFPresetPulseEffect

@synthesize presetPulseEffect = _presetPulseEffect;

-(id)initWithLampIDs: (NSArray *)lampIDs lampGroupIDs: (NSArray *)lampGroupIDs toPresetID: (NSString *)toPresetID period: (unsigned int)period duration: (unsigned int)duration andNumPulses: (unsigned int)numPulses
{
    self = [super init];
    
    if (self)
    {
        lsf::LSFStringList lampIDList = [LSFUtils convertNSArrayToStringList: lampIDs];
        lsf::LSFStringList lampGroupIDList = [LSFUtils convertNSArrayToStringList: lampGroupIDs];
        std::string tpid([toPresetID UTF8String]);
        self.handle = new lsf::PulseLampsLampGroupsWithPreset(lampIDList, lampGroupIDList, tpid, period, duration, numPulses);
    }
    
    return self;
}

-(id)initWithLampIDs: (NSArray *)lampIDs lampGroupIDs: (NSArray *)lampGroupIDs fromPresetID: (NSString *)fromPresetID toPresetID: (NSString *)toPresetID period: (unsigned int)period duration: (unsigned int)duration andNumPulses: (unsigned int)numPulses
{
    self = [super init];
    
    if (self)
    {
        lsf::LSFStringList lampIDList = [LSFUtils convertNSArrayToStringList: lampIDs];
        lsf::LSFStringList lampGroupIDList = [LSFUtils convertNSArrayToStringList: lampGroupIDs];
        std::string fpid([fromPresetID UTF8String]);
        std::string tpid([toPresetID UTF8String]);
        self.handle = new lsf::PulseLampsLampGroupsWithPreset(lampIDList, lampGroupIDList, fpid, tpid, period, duration, numPulses);
    }
    
    return self;
}

-(void)setLamps: (NSArray *)lampIDs
{
    lsf::LSFStringList lampIDList = [LSFUtils convertNSArrayToStringList: lampIDs];
    self.presetPulseEffect->lamps = lampIDList;
}

-(NSArray *)lamps
{
    lsf::LSFStringList lampIDs = self.presetPulseEffect->lamps;
    return [LSFUtils convertStringListToNSArray: lampIDs];
}

-(void)setLampGroups: (NSArray *)lampGroupIDs
{
    lsf::LSFStringList lampGroupIDList = [LSFUtils convertNSArrayToStringList: lampGroupIDs];
    self.presetPulseEffect->lampGroups = lampGroupIDList;
}

-(NSArray *)lampGroups
{
    lsf::LSFStringList lampGroupIDs = self.presetPulseEffect->lampGroups;
    return [LSFUtils convertStringListToNSArray: lampGroupIDs];
}

-(void)setPeriod: (unsigned int)period
{
    self.presetPulseEffect->pulsePeriod = period;
}

-(unsigned int)period
{
    return self.presetPulseEffect->pulsePeriod;
}

-(void)setDuration: (unsigned int)duration
{
    self.presetPulseEffect->pulseDuration = duration;
}

-(unsigned int)duration
{
    return self.presetPulseEffect->pulseDuration;
}

-(void)setNumPulses: (unsigned int)numPulses
{
    self.presetPulseEffect->numPulses = numPulses;
}

-(unsigned int)numPulses
{
    return self.presetPulseEffect->numPulses;
}

-(void)setFromPresetID: (NSString *)fromPresetID
{
    std::string fpid([fromPresetID UTF8String]);
    self.presetPulseEffect->fromPreset = fpid;
}

-(NSString *)fromPresetID
{
    return [NSString stringWithUTF8String: (self.presetPulseEffect->fromPreset).c_str()];
}

-(void)setToPresetID: (NSString *)toPresetID
{
    std::string tpid([toPresetID UTF8String]);
    self.presetPulseEffect->toPreset = tpid;
}

-(NSString *)toPresetID
{
    return [NSString stringWithUTF8String: (self.presetPulseEffect->toPreset).c_str()];
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
- (lsf::PulseLampsLampGroupsWithPreset *)presetPulseEffect
{
    return static_cast<lsf::PulseLampsLampGroupsWithPreset*>(self.handle);
}

@end
