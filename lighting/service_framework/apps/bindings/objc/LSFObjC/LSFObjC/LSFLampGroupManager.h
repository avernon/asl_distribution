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

#import "LSFObject.h"
#import "LSFLampGroup.h"
#import "LSFLampState.h"
#import "LSFControllerClient.h"
#import "LSFLampGroupManagerCallbackDelegate.h"
#import "LampGroupManager.h"

using namespace lsf;

@interface LSFLampGroupManager : LSFObject

-(id)initWithControllerClient: (LSFControllerClient *)controllerClient andLampManagerCallbackDelegate: (id<LSFLampGroupManagerCallbackDelegate>)lgmDelegate;
-(ControllerClientStatus)getAllLampGroupIDs;
-(ControllerClientStatus)getLampGroupNameForID: (NSString *)groupID;
-(ControllerClientStatus)getLampGroupNameForID: (NSString *)groupID andLanguage: (NSString *)language;
-(ControllerClientStatus)setLampGroupNameForID: (NSString *)groupID andName: (NSString *)name;
-(ControllerClientStatus)setLampGroupNameForID: (NSString *)groupID andName: (NSString *)name andLanguage: (NSString *)language;
-(ControllerClientStatus)createLampGroup: (LSFLampGroup *)lampGroup withName: (NSString *)lampGroupName;
-(ControllerClientStatus)createLampGroup: (LSFLampGroup *)lampGroup withName: (NSString *)lampGroupName andLanguage: (NSString *)language;
-(ControllerClientStatus)updateLampGroupWithID: (NSString *)groupID andLampGroup: (LSFLampGroup *)lampGroup;
-(ControllerClientStatus)getLampGroupWithID: (NSString *)groupID;
-(ControllerClientStatus)deleteLampGroupWithID: (NSString *)groupID;
-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID toState: (LSFLampState *)state;
-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID toState: (LSFLampState *)state withTransitionPeriod: (unsigned int)transitionPeriod;
-(ControllerClientStatus)pulseLampGroupID: (NSString *)groupID toLampState: (LSFLampState *)toState withPeriod: (unsigned int)period duration: (unsigned int)duration andNumPulses: (unsigned int)numPulses;
-(ControllerClientStatus)pulseLampGroupID: (NSString *)groupID toLampState: (LSFLampState *)toState withPeriod: (unsigned int)period duration: (unsigned int)duration numPulses: (unsigned int)numPulses fromLampState: (LSFLampState *)fromState;
-(ControllerClientStatus)pulseLampGroupID: (NSString *)groupID toPreset: (NSString *)toPresetID withPeriod: (unsigned int)period duration: (unsigned int)duration andNumPulses: (unsigned int)numPulses;
-(ControllerClientStatus)pulseLampGroupID: (NSString *)groupID toPreset: (NSString *)toPresetID withPeriod: (unsigned int)period duration: (unsigned int)duration andNumPulses: (unsigned int)numPulses fromPreset: (NSString *)fromPresetID;
-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID onOffField: (BOOL)onOff;
-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID hueField: (unsigned int)hue;
-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID hueField: (unsigned int)hue withTransitionPeriod: (unsigned int)transitionPeriod;
-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID saturationField: (unsigned int)saturation;
-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID saturationField: (unsigned int)saturation withTransitionPeriod: (unsigned int)transitionPeriod;
-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID brightnessField: (unsigned int)brightness;
-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID brightnessField: (unsigned int)brightness withTransitionPeriod: (unsigned int)transitionPeriod;
-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID colorTempField: (unsigned int)colorTemp;
-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID colorTempField: (unsigned int)colorTemp withTransitionPeriod: (unsigned int)transitionPeriod;
-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID toPreset: (NSString *)presetID;
-(ControllerClientStatus)transitionLampGroupID: (NSString *)groupID toPreset: (NSString *)presetID withTransitionPeriod: (unsigned int)transitionPeriod;
-(ControllerClientStatus)resetLampGroupStateForID: (NSString *)groupID;
-(ControllerClientStatus)resetLampGroupStateOnOffFieldForID: (NSString *)groupID;
-(ControllerClientStatus)resetLampGroupStateHueFieldForID: (NSString *)groupID;
-(ControllerClientStatus)resetLampGroupStateSaturationFieldForID: (NSString *)groupID;
-(ControllerClientStatus)resetLampGroupStateBrightnessFieldForID: (NSString *)groupID;
-(ControllerClientStatus)resetLampGroupStateColorTempFieldForID: (NSString *)groupID;
-(ControllerClientStatus)getLampGroupDataSetForID: (NSString *)groupID;
-(ControllerClientStatus)getLampGroupDataSetForID: (NSString *)groupID andLanguage: (NSString *)language;

@end