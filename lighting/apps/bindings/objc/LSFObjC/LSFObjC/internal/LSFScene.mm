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

#import "LSFScene.h"
#import "LSFUtils.h"
#import <LSFTypes.h>

@interface LSFScene()

@property (nonatomic, readonly) lsf::Scene *scene;

@end

@implementation LSFScene

@synthesize scene = _scene;

-(id)init
{
    self = [super init];
    
    if (self)
    {
        self.handle = new lsf::Scene();
    }
    
    return self;
}

-(id)initWithStateTransitionEffects: (NSArray *)stateTransitionEffects presetTransitionEffects: (NSArray *)presetTransitionEffects statePulseEffects: (NSArray *)statePulseEffects andPresetPulseEffects: (NSArray *)presetPulseEffects
{
    self = [super init];
    
    if (self)
    {
        lsf::TransitionLampsLampGroupsToStateList tllgtsl = [LSFUtils convertNSArrayToStateTransitionEffects: stateTransitionEffects];
        lsf::TransitionLampsLampGroupsToPresetList tllgtpl = [LSFUtils convertNSArrayToPresetTransitionEffects: presetTransitionEffects];
        lsf::PulseLampsLampGroupsWithStateList pllgwsl = [LSFUtils convertNSArrayToStatePulseEffects: statePulseEffects];
        lsf::PulseLampsLampGroupsWithPresetList pllgwpl = [LSFUtils convertNSArrayToPresetPulseEffects: presetPulseEffects];
        
        self.handle = new lsf::Scene(tllgtsl, tllgtpl, pllgwsl, pllgwpl);
    }
    
    return self;
}

-(void)setTransitionToStateComponent: (NSArray *)transitionToStateComponent
{
    self.scene->transitionToStateComponent = [LSFUtils convertNSArrayToStateTransitionEffects: transitionToStateComponent];
}

-(NSArray *)transitionToStateComponent
{
    return [LSFUtils convertStateTransitionEffectsToNSArray: self.scene->transitionToStateComponent];
}

-(void)setTransitionToPresetComponent: (NSArray *)transitionToPresetComponent
{
    self.scene->transitionToPresetComponent = [LSFUtils convertNSArrayToPresetTransitionEffects: transitionToPresetComponent];
}

-(NSArray *)transitionToPresetComponent
{
    return [LSFUtils convertPresetTransitionEffectsToNSArray: self.scene->transitionToPresetComponent];
}

-(void)setPulseWithStateComponent: (NSArray *)pulseWithStateComponent
{
    self.scene->pulseWithStateComponent = [LSFUtils convertNSArrayToStatePulseEffects: pulseWithStateComponent];
}

-(NSArray *)pulseWithStateComponent
{
    return [LSFUtils convertStatePulseEffectsToNSArray: self.scene->pulseWithStateComponent];
}

-(void)setPulseWithPresetComponent: (NSArray *)pulseWithPresetComponent
{
    self.scene->pulseWithPresetComponent = [LSFUtils convertNSArrayToPresetPulseEffects: pulseWithPresetComponent];
}

-(NSArray *)pulseWithPresetComponent
{
    return [LSFUtils convertPresetPulseEffectsToNSArray: self.scene->pulseWithPresetComponent];
}

-(LSFResponseCode)isDependentOnPreset: (NSString *)presetID
{
    std::string pid([presetID UTF8String]);
    return self.scene->IsDependentOnPreset(pid);
}

-(LSFResponseCode)isDependentOnLampGroup: (NSString *)lampGroupID
{
    std::string lgid([lampGroupID UTF8String]);
    return self.scene->IsDependentOnLampGroup(lgid);
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
- (lsf::Scene *)scene
{
    return static_cast<lsf::Scene*>(self.handle);
}

@end
