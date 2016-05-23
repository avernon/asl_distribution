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

#import "LSFLampGroupManager.h"
#import "LSFLampGroupManagerCallback.h"

@interface LSFLampGroupManager()

@property (nonatomic, readonly) lsf::LampGroupManager *lampGroupManager;
@property (nonatomic, assign) LSFLampGroupManagerCallback *lampGroupManagerCallback;

@end

@implementation LSFLampGroupManager

@synthesize lampGroupManager = _lampGroupManager;
@synthesize lampGroupManagerCallback = _lampGroupManagerCallback;

-(id)initWithControllerClient: (LSFControllerClient *)controllerClient andLampManagerCallbackDelegate: (id<LSFLampGroupManagerCallbackDelegate>)lgmDelegate
{
    self = [super init];
    
    if (self)
    {
        self.lampGroupManagerCallback = new LSFLampGroupManagerCallback(lgmDelegate);
        self.handle = new lsf::LampGroupManager(*(static_cast<lsf::ControllerClient*>(controllerClient.handle)), *(self.lampGroupManagerCallback));
    }
    
    return self;
}

-(ControllerClientStatus)getAllLampGroupIDs
{
    return self.lampGroupManager->GetAllLampGroupIDs();
}

-(ControllerClientStatus)getLampGroupNameForID: (NSString *)groupID
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->GetLampGroupName(gid);
}

-(ControllerClientStatus)getLampGroupNameForID: (NSString *)groupID andLanguage: (NSString *)language
{
    std::string gid([groupID UTF8String]);
    std::string lang([language UTF8String]);
    return self.lampGroupManager->GetLampGroupName(gid, lang);
}

-(ControllerClientStatus)setLampGroupNameForID: (NSString *)groupID andName: (NSString *)name
{
    std::string gid([groupID UTF8String]);
    std::string groupName([name UTF8String]);
    return self.lampGroupManager->SetLampGroupName(gid, groupName);
}

-(ControllerClientStatus)setLampGroupNameForID: (NSString *)groupID andName: (NSString *)name andLanguage: (NSString *)language
{
    std::string gid([groupID UTF8String]);
    std::string groupName([name UTF8String]);
    std::string lang([language UTF8String]);
    return self.lampGroupManager->SetLampGroupName(gid, groupName, lang);
}

-(ControllerClientStatus)createLampGroup: (LSFLampGroup *)lampGroup withName: (NSString *)lampGroupName
{
    std::string groupName([lampGroupName UTF8String]);
    return self.lampGroupManager->CreateLampGroup(*(static_cast<lsf::LampGroup*>(lampGroup.handle)), groupName);
}

-(ControllerClientStatus)createLampGroup: (LSFLampGroup *)lampGroup withName: (NSString *)lampGroupName andLanguage: (NSString *)language
{
    std::string groupName([lampGroupName UTF8String]);
    std::string lang([language UTF8String]);
    return self.lampGroupManager->CreateLampGroup(*(static_cast<lsf::LampGroup*>(lampGroup.handle)), groupName, lang);
}

-(ControllerClientStatus)updateLampGroupWithID: (NSString *)groupID andLampGroup: (LSFLampGroup *)lampGroup
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->UpdateLampGroup(gid, *(static_cast<lsf::LampGroup*>(lampGroup.handle)));
}

-(ControllerClientStatus)getLampGroupWithID: (NSString *)groupID
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->GetLampGroup(gid);
}

-(ControllerClientStatus)deleteLampGroupWithID: (NSString *)groupID
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->DeleteLampGroup(gid);
}

-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID toState: (LSFLampState *)state
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->TransitionLampGroupState(gid, *(static_cast<lsf::LampState*>(state.handle)));
}

-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID toState: (LSFLampState *)state withTransitionPeriod: (unsigned int)transitionPeriod
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->TransitionLampGroupState(gid, *(static_cast<lsf::LampState*>(state.handle)), transitionPeriod);
}

-(ControllerClientStatus)pulseLampGroupID: (NSString *)groupID toLampState: (LSFLampState *)toState withPeriod: (unsigned int)period duration: (unsigned int)duration andNumPulses: (unsigned int)numPulses
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->PulseLampGroupWithState(gid, *(static_cast<lsf::LampState*>(toState.handle)), period, duration, numPulses);
}

-(ControllerClientStatus)pulseLampGroupID: (NSString *)groupID toLampState: (LSFLampState *)toState withPeriod: (unsigned int)period duration: (unsigned int)duration numPulses: (unsigned int)numPulses fromLampState: (LSFLampState *)fromState
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->PulseLampGroupWithState(gid, *(static_cast<lsf::LampState*>(toState.handle)), period, duration, numPulses, *(static_cast<lsf::LampState*>(fromState.handle)));
}

-(ControllerClientStatus)pulseLampGroupID: (NSString *)groupID toPreset: (NSString *)toPresetID withPeriod: (unsigned int)period duration: (unsigned int)duration andNumPulses: (unsigned int)numPulses
{
    std::string gid([groupID UTF8String]);
    std::string pid([toPresetID UTF8String]);
    return self.lampGroupManager->PulseLampGroupWithPreset(gid, pid, period, duration, numPulses);
}

-(ControllerClientStatus)pulseLampGroupID: (NSString *)groupID toPreset: (NSString *)toPresetID withPeriod: (unsigned int)period duration: (unsigned int)duration andNumPulses: (unsigned int)numPulses fromPreset: (NSString *)fromPresetID
{
    std::string gid([groupID UTF8String]);
    std::string tpid([toPresetID UTF8String]);
    std::string fpid([fromPresetID UTF8String]);
    return self.lampGroupManager->PulseLampGroupWithPreset(gid, tpid, period, duration, numPulses, fpid);
}

-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID onOffField: (BOOL)onOff
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->TransitionLampGroupStateOnOffField(gid, onOff);
}

-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID hueField: (unsigned int)hue
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->TransitionLampGroupStateHueField(gid, hue);
}

-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID hueField: (unsigned int)hue withTransitionPeriod: (unsigned int)transitionPeriod
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->TransitionLampGroupStateHueField(gid, hue, transitionPeriod);
}

-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID saturationField: (unsigned int)saturation
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->TransitionLampGroupStateSaturationField(gid, saturation);
}

-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID saturationField: (unsigned int)saturation withTransitionPeriod: (unsigned int)transitionPeriod
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->TransitionLampGroupStateSaturationField(gid, saturation, transitionPeriod);
}

-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID brightnessField: (unsigned int)brightness
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->TransitionLampGroupStateBrightnessField(gid, brightness);
}

-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID brightnessField: (unsigned int)brightness withTransitionPeriod: (unsigned int)transitionPeriod
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->TransitionLampGroupStateBrightnessField(gid, brightness, transitionPeriod);
}

-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID colorTempField: (unsigned int)colorTemp
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->TransitionLampGroupStateColorTempField(gid, colorTemp);
}

-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID colorTempField: (unsigned int)colorTemp withTransitionPeriod: (unsigned int)transitionPeriod
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->TransitionLampGroupStateColorTempField(gid, colorTemp, transitionPeriod);
}

-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID toPreset: (NSString *)presetID
{
    std::string gid([groupID UTF8String]);
    std::string pid([presetID UTF8String]);
    return self.lampGroupManager->TransitionLampGroupStateToPreset(gid, pid);
}

-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID toPreset: (NSString *)presetID withTransitionPeriod: (unsigned int)transitionPeriod
{
    std::string gid([groupID UTF8String]);
    std::string pid([presetID UTF8String]);
    return self.lampGroupManager->TransitionLampGroupStateToPreset(gid, pid, transitionPeriod);
}

-(ControllerClientStatus)resetLampGroupStateForID: (NSString *)groupID
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->ResetLampGroupState(gid);
}

-(ControllerClientStatus)resetLampGroupStateOnOffFieldForID: (NSString *)groupID
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->ResetLampGroupStateOnOffField(gid);
}

-(ControllerClientStatus)resetLampGroupStateHueFieldForID: (NSString *)groupID
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->ResetLampGroupStateHueField(gid);
}

-(ControllerClientStatus)resetLampGroupStateSaturationFieldForID: (NSString *)groupID
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->ResetLampGroupStateSaturationField(gid);
}

-(ControllerClientStatus)resetLampGroupStateBrightnessFieldForID: (NSString *)groupID
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->ResetLampGroupStateBrightnessField(gid);
}

-(ControllerClientStatus)resetLampGroupStateColorTempFieldForID: (NSString *)groupID
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->ResetLampGroupStateColorTempField(gid);
}

-(ControllerClientStatus)getLampGroupDataSetForID: (NSString *)groupID
{
    std::string gid([groupID UTF8String]);
    return self.lampGroupManager->GetLampGroupDataSet(gid);
}

-(ControllerClientStatus)getLampGroupDataSetForID: (NSString *)groupID andLanguage: (NSString *)language
{
    std::string gid([groupID UTF8String]);
    std::string lang([language UTF8String]);
    return self.lampGroupManager->GetLampGroupDataSet(gid, lang);
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
- (lsf::LampGroupManager *)lampGroupManager
{
    return static_cast<lsf::LampGroupManager*>(self.handle);
}

@end
