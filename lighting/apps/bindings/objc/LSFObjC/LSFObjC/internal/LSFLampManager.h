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
#import "LSFLampState.h"
#import "LSFControllerClient.h"
#import "LSFLampManagerCallbackDelegate.h"
#import <LampManager.h>

using namespace lsf;

@interface LSFLampManager : LSFObject

-(id)initWithControllerClient: (LSFControllerClient *)controllerClient andLampManagerCallbackDelegate: (id<LSFLampManagerCallbackDelegate>)lmDelegate;
-(ControllerClientStatus)getAllLampIDs;
-(ControllerClientStatus)getLampManufacturerForID: (NSString *)lampID;
-(ControllerClientStatus)getLampManufacturerForID: (NSString *)lampID andLanguage: (NSString *)language;
-(ControllerClientStatus)getLampName: (NSString *)lampID;
-(ControllerClientStatus)getLampName: (NSString *)lampID andLanguage: (NSString *)language;
-(ControllerClientStatus)setLampNameWithID: (NSString *)lampID andName: (NSString *)name;
-(ControllerClientStatus)setLampNameWithID: (NSString *)lampID name: (NSString *)name andLanguage: (NSString *)language;
-(ControllerClientStatus)getLampDetailsForID: (NSString *)lampID;
-(ControllerClientStatus)getLampParametersForID: (NSString *)lampID;
-(ControllerClientStatus)getLampParameterEnergyUsageMilliwattsFieldForID: (NSString *)lampID;
-(ControllerClientStatus)getLampParameterLumensFieldForID: (NSString *)lampID;
-(ControllerClientStatus)getLampStateForID: (NSString *)lampID;
-(ControllerClientStatus)getLampStateOnOffFieldForID: (NSString *)lampID;
-(ControllerClientStatus)getLampStateHueFieldForID: (NSString *)lampID;
-(ControllerClientStatus)getLampStateSaturationFieldForID: (NSString *)lampID;
-(ControllerClientStatus)getLampStateBrightnessFieldForID: (NSString *)lampID;
-(ControllerClientStatus)getLampStateColorTempFieldForID: (NSString *)lampID;
-(ControllerClientStatus)resetLampStateForID: (NSString *)lampID;
-(ControllerClientStatus)resetLampStateOnOffFieldForID: (NSString *)lampID;
-(ControllerClientStatus)resetLampStateHueFieldForID: (NSString *)lampID;
-(ControllerClientStatus)resetLampStateSaturationFieldForID: (NSString *)lampID;
-(ControllerClientStatus)resetLampStateBrightnessFieldForID: (NSString *)lampID;
-(ControllerClientStatus)resetLampStateColorTempFieldForID: (NSString *)lampID;
-(ControllerClientStatus)transitionLampID: (NSString *)lampID toLampState: (LSFLampState *)lampState;
-(ControllerClientStatus)transitionLampID: (NSString *)lampID toLampState: (LSFLampState *)lampState withTransitionPeriod: (unsigned int)transitionPeriod;
-(ControllerClientStatus)pulseLampID: (NSString *)lampID toLampState: (LSFLampState *)toLampState withPeriod: (unsigned int)period duration: (unsigned int)duration andNumPulses: (unsigned int)numPulses;
-(ControllerClientStatus)pulseLampID: (NSString *)lampID toLampState: (LSFLampState *)toLampState withPeriod: (unsigned int)period duration: (unsigned int)duration numPulses: (unsigned int)numPulses andFromLampState: (LSFLampState *)fromLampState;
-(ControllerClientStatus)pulseLampID: (NSString *)lampID toPreset: (NSString *)toPresetID withPeriod: (unsigned int)period duration: (unsigned int)duration andNumPulses: (unsigned int)numPulses;
-(ControllerClientStatus)pulseLampID: (NSString *)lampID toPreset: (NSString *)toPresetID withPeriod: (unsigned int)period duration: (unsigned int)duration andNumPulses: (unsigned int)numPulses andFromPresetID: (NSString *)fromPresetID;
-(ControllerClientStatus)transitionLampID: (NSString *)lampID onOffField: (BOOL)onOff;
-(ControllerClientStatus)transitionLampID: (NSString *)lampID hueField: (unsigned int)hue;
-(ControllerClientStatus)transitionLampID: (NSString *)lampID hueField: (unsigned int)hue withTransitionPeriod: (unsigned int)transitionPeriod;
-(ControllerClientStatus)transitionLampID: (NSString *)lampID saturationField: (unsigned int)saturation;
-(ControllerClientStatus)transitionLampID: (NSString *)lampID saturationField: (unsigned int)saturation withTransitionPeriod: (unsigned int)transitionPeriod;
-(ControllerClientStatus)transitionLampID: (NSString *)lampID brightnessField: (unsigned int)brightness;
-(ControllerClientStatus)transitionLampID: (NSString *)lampID brightnessField: (unsigned int)brightness withTransitionPeriod: (unsigned int)transitionPeriod;
-(ControllerClientStatus)transitionLampID: (NSString *)lampID colorTempField: (unsigned int)colorTemp;
-(ControllerClientStatus)transitionLampID: (NSString *)lampID colorTempField: (unsigned int)colorTemp withTransitionPeriod: (unsigned int)transitionPeriod;
-(ControllerClientStatus)transitionLampID: (NSString *)lampID toPresetID: (NSString *)presetID;
-(ControllerClientStatus)transitionLampID: (NSString *)lampID toPresetID: (NSString *)presetID withTransitionPeriod: (unsigned int)transitionPeriod;
-(ControllerClientStatus)getLampFaultsForID: (NSString *)lampID;
-(ControllerClientStatus)getLampServiceVersionForID: (NSString *)lampID;
-(ControllerClientStatus)clearLampFaultForID: (NSString *) lampID andFaultCode: (LampFaultCode)faultCode;
-(ControllerClientStatus)getLampSupportedLanguagesForID: (NSString *) lampID;
-(ControllerClientStatus)getLampDataSetForID: (NSString *)lampID;
-(ControllerClientStatus)getLampDataSetForID: (NSString *)lampID andLanguage: (NSString *)language;
-(ControllerClientStatus)getConsolidatedLampDataSetForID: (NSString *)lampID;
-(ControllerClientStatus)getConsolidatedLampDataSetForID: (NSString *)lampID andLanguage: (NSString *)language;
-(ControllerClientStatus)setLampEffectForID: (NSString *)lampID withEffectID: (NSString *)effectID;

@end
