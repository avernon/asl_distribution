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

#import "LSFPresetTransitionEffect.h"
#import "LSFTypes.h"
#import "LSFUtils.h"

@interface LSFPresetTransitionEffect()

@property (nonatomic, readonly) lsf::TransitionLampsLampGroupsToPreset *presetTransitionEffect;

@end

@implementation LSFPresetTransitionEffect

-(id)initWithLampIDs: (NSArray *)lampIDs lampGroupIDs: (NSArray *)lampGroupIDs andPresetID: (NSString *)presetID
{
    self = [super init];
    
    if (self)
    {
        lsf::LSFStringList lampIDList = [LSFUtils convertNSArrayToStringList: lampIDs];
        lsf::LSFStringList lampGroupIDList = [LSFUtils convertNSArrayToStringList: lampGroupIDs];
        std::string pid([presetID UTF8String]);
        self.handle = new lsf::TransitionLampsLampGroupsToPreset(lampIDList, lampGroupIDList, pid);
    }
    
    return self;
}

-(id)initWithLampIDs: (NSArray *)lampIDs lampGroupIDs: (NSArray *)lampGroupIDs presetID: (NSString *)presetID andTransitionPeriod: (unsigned int)transitionPeriod
{
    self = [super init];
    
    if (self)
    {
        lsf::LSFStringList lampIDList = [LSFUtils convertNSArrayToStringList: lampIDs];
        lsf::LSFStringList lampGroupIDList = [LSFUtils convertNSArrayToStringList: lampGroupIDs];
        std::string pid([presetID UTF8String]);
        self.handle = new lsf::TransitionLampsLampGroupsToPreset(lampIDList, lampGroupIDList, pid, transitionPeriod);
    }
    
    return self;
}

-(void)setLamps: (NSArray *)lampIDs
{
    lsf::LSFStringList lampIDList = [LSFUtils convertNSArrayToStringList: lampIDs];
    self.presetTransitionEffect->lamps = lampIDList;
}

-(NSArray *)lamps
{
    lsf::LSFStringList lampIDs = self.presetTransitionEffect->lamps;
    return [LSFUtils convertStringListToNSArray: lampIDs];
}

-(void)setLampGroups: (NSArray *)lampGroupIDs
{
    lsf::LSFStringList lampGroupIDList = [LSFUtils convertNSArrayToStringList: lampGroupIDs];
    self.presetTransitionEffect->lampGroups = lampGroupIDList;
}

-(NSArray *)lampGroups
{
    lsf::LSFStringList lampGroupIDs = self.presetTransitionEffect->lampGroups;
    return [LSFUtils convertStringListToNSArray: lampGroupIDs];
}

-(void)setTransitionPeriod: (unsigned int)transitionPeriod
{
    self.presetTransitionEffect->transitionPeriod = transitionPeriod;
}

-(unsigned int)transitionPeriod
{
    return self.presetTransitionEffect->transitionPeriod;
}

-(void)setPresetID: (NSString *)presetID
{
    std::string pid([presetID UTF8String]);
    self.presetTransitionEffect->presetID = pid;
}

-(NSString *)presetID
{
    return [NSString stringWithUTF8String: (self.presetTransitionEffect->presetID).c_str()];
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
- (lsf::TransitionLampsLampGroupsToPreset *)presetTransitionEffect
{
    return static_cast<lsf::TransitionLampsLampGroupsToPreset*>(self.handle);
}

@end
