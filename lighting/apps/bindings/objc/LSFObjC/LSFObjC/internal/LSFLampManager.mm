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

#import "LSFLampManager.h"
#import "LSFLampManagerCallback.h"

@interface LSFLampManager()

@property (nonatomic, readonly) lsf::LampManager *lampManager;
@property (nonatomic, assign) LSFLampManagerCallback *lampManagerCallback;

@end

@implementation LSFLampManager

@synthesize lampManager = _lampManager;
@synthesize lampManagerCallback = _lampManagerCallback;

-(id)initWithControllerClient: (LSFControllerClient *)controllerClient andLampManagerCallbackDelegate: (id<LSFLampManagerCallbackDelegate>)lmDelegate
{
    self = [super init];
    
    if (self)
    {
        self.lampManagerCallback = new LSFLampManagerCallback(lmDelegate);
        self.handle = new lsf::LampManager(*(static_cast<lsf::ControllerClient*>(controllerClient.handle)), *(self.lampManagerCallback));
    }
    
    return self;
}
-(ControllerClientStatus)getAllLampIDs
{
    return self.lampManager->GetAllLampIDs();
}

-(ControllerClientStatus)getLampManufacturerForID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->GetLampManufacturer(lid);
}

-(ControllerClientStatus)getLampManufacturerForID: (NSString *)lampID andLanguage: (NSString *)language
{
    std::string lid([lampID UTF8String]);
    std::string lang([language UTF8String]);
    return self.lampManager->GetLampManufacturer(lid, lang);
}

-(ControllerClientStatus)getLampName: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->GetLampName(lid);
}

-(ControllerClientStatus)getLampName: (NSString *)lampID andLanguage: (NSString *)language
{
    std::string lid([lampID UTF8String]);
    std::string lang([language UTF8String]);
    return self.lampManager->GetLampName(lid, lang);
}

-(ControllerClientStatus)setLampNameWithID: (NSString *)lampID andName: (NSString *)name
{
    std::string lid([lampID UTF8String]);
    std::string lampName([name UTF8String]);
    return self.lampManager->SetLampName(lid, lampName);
}

-(ControllerClientStatus)setLampNameWithID: (NSString *)lampID name: (NSString *)name andLanguage: (NSString *)language
{
    std::string lid([lampID UTF8String]);
    std::string lampName([name UTF8String]);
    std::string lang([language UTF8String]);
    return self.lampManager->SetLampName(lid, lampName, lang);
}

-(ControllerClientStatus)getLampDetailsForID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->GetLampDetails(lid);
}

-(ControllerClientStatus)getLampParametersForID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->GetLampParameters(lid);
}

-(ControllerClientStatus)getLampParameterEnergyUsageMilliwattsFieldForID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->GetLampParametersEnergyUsageMilliwattsField(lid);
}

-(ControllerClientStatus)getLampParameterLumensFieldForID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->GetLampParametersLumensField(lid);
}

-(ControllerClientStatus)getLampStateForID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->GetLampState(lid);
}

-(ControllerClientStatus)getLampStateOnOffFieldForID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->GetLampStateOnOffField(lid);
}

-(ControllerClientStatus)getLampStateHueFieldForID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->GetLampStateHueField(lid);
}

-(ControllerClientStatus)getLampStateSaturationFieldForID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->GetLampStateSaturationField(lid);
}

-(ControllerClientStatus)getLampStateBrightnessFieldForID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->GetLampStateBrightnessField(lid);
}

-(ControllerClientStatus)getLampStateColorTempFieldForID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->GetLampStateColorTempField(lid);
}

-(ControllerClientStatus)resetLampStateForID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->ResetLampState(lid);
}

-(ControllerClientStatus)resetLampStateOnOffFieldForID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->ResetLampStateOnOffField(lid);
}

-(ControllerClientStatus)resetLampStateHueFieldForID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->ResetLampStateHueField(lid);
}

-(ControllerClientStatus)resetLampStateSaturationFieldForID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->ResetLampStateSaturationField(lid);
}

-(ControllerClientStatus)resetLampStateBrightnessFieldForID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->ResetLampStateBrightnessField(lid);
}

-(ControllerClientStatus)resetLampStateColorTempFieldForID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->ResetLampStateColorTempField(lid);
}

-(ControllerClientStatus)transitionLampID: (NSString *)lampID toLampState: (LSFLampState *)lampState
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->TransitionLampState(lid, *static_cast<lsf::LampState*>(lampState.handle));
}

-(ControllerClientStatus)transitionLampID: (NSString *)lampID toLampState: (LSFLampState *)lampState withTransitionPeriod: (unsigned int)transitionPeriod
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->TransitionLampState(lid, *static_cast<lsf::LampState*>(lampState.handle), transitionPeriod);
}

-(ControllerClientStatus)pulseLampID: (NSString *)lampID toLampState: (LSFLampState *)toLampState withPeriod: (unsigned int)period duration: (unsigned int)duration andNumPulses: (unsigned int)numPulses
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->PulseLampWithState(lid, *static_cast<lsf::LampState*>(toLampState.handle), period, duration, numPulses);
}

-(ControllerClientStatus)pulseLampID: (NSString *)lampID toLampState: (LSFLampState *)toLampState withPeriod: (unsigned int)period duration: (unsigned int)duration numPulses: (unsigned int)numPulses andFromLampState: (LSFLampState *)fromLampState
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->PulseLampWithState(lid, *static_cast<lsf::LampState*>(toLampState.handle), period, duration, numPulses, *static_cast<lsf::LampState*>(fromLampState.handle));
}

-(ControllerClientStatus)pulseLampID: (NSString *)lampID toPreset: (NSString *)toPresetID withPeriod: (unsigned int)period duration: (unsigned int)duration andNumPulses: (unsigned int)numPulses
{
    std::string lid([lampID UTF8String]);
    std::string toPreset([toPresetID UTF8String]);
    return self.lampManager->PulseLampWithPreset(lid, toPreset, period, duration, numPulses);
}

-(ControllerClientStatus)pulseLampID: (NSString *)lampID toPreset: (NSString *)toPresetID withPeriod: (unsigned int)period duration: (unsigned int)duration andNumPulses: (unsigned int)numPulses andFromPresetID: (NSString *)fromPresetID
{
    std::string lid([lampID UTF8String]);
    std::string toPreset([toPresetID UTF8String]);
    std::string fromPreset([fromPresetID UTF8String]);
    return self.lampManager->PulseLampWithPreset(lid, toPreset, period, duration, numPulses, fromPreset);
}

-(ControllerClientStatus)transitionLampID: (NSString *)lampID onOffField: (BOOL)onOff
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->TransitionLampStateOnOffField(lid, onOff);
}

-(ControllerClientStatus)transitionLampID: (NSString *)lampID hueField: (unsigned int)hue
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->TransitionLampStateHueField(lid, hue);
}

-(ControllerClientStatus)transitionLampID: (NSString *)lampID hueField: (unsigned int)hue withTransitionPeriod: (unsigned int)transitionPeriod
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->TransitionLampStateHueField(lid, hue, transitionPeriod);
}

-(ControllerClientStatus)transitionLampID: (NSString *)lampID saturationField: (unsigned int)saturation
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->TransitionLampStateSaturationField(lid, saturation);
}

-(ControllerClientStatus)transitionLampID: (NSString *)lampID saturationField: (unsigned int)saturation withTransitionPeriod: (unsigned int)transitionPeriod
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->TransitionLampStateSaturationField(lid, saturation, transitionPeriod);
}

-(ControllerClientStatus)transitionLampID: (NSString *)lampID brightnessField: (unsigned int)brightness
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->TransitionLampStateBrightnessField(lid, brightness);
}

-(ControllerClientStatus)transitionLampID: (NSString *)lampID brightnessField: (unsigned int)brightness withTransitionPeriod: (unsigned int)transitionPeriod
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->TransitionLampStateBrightnessField(lid, brightness, transitionPeriod);
}

-(ControllerClientStatus)transitionLampID: (NSString *)lampID colorTempField: (unsigned int)colorTemp
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->TransitionLampStateColorTempField(lid, colorTemp);
}

-(ControllerClientStatus)transitionLampID: (NSString *)lampID colorTempField: (unsigned int)colorTemp withTransitionPeriod: (unsigned int)transitionPeriod
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->TransitionLampStateColorTempField(lid, colorTemp, transitionPeriod);
}

-(ControllerClientStatus)transitionLampID: (NSString *)lampID toPresetID: (NSString *)presetID
{
    std::string lid([lampID UTF8String]);
    std::string preset([presetID UTF8String]);
    return self.lampManager->TransitionLampStateToPreset(lid, preset);
}

-(ControllerClientStatus)transitionLampID: (NSString *)lampID toPresetID: (NSString *)presetID withTransitionPeriod: (unsigned int)transitionPeriod
{
    std::string lid([lampID UTF8String]);
    std::string preset([presetID UTF8String]);
    return self.lampManager->TransitionLampStateToPreset(lid, preset, transitionPeriod);
}

-(ControllerClientStatus)getLampFaultsForID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->GetLampFaults(lid);
}

-(ControllerClientStatus)getLampServiceVersionForID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->GetLampServiceVersion(lid);
}

-(ControllerClientStatus)clearLampFaultForID: (NSString *) lampID andFaultCode: (LampFaultCode)faultCode
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->ClearLampFault(lid, faultCode);
}

-(ControllerClientStatus)getLampSupportedLanguagesForID: (NSString *) lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->GetLampSupportedLanguages(lid);
}

-(ControllerClientStatus)getLampDataSetForID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->GetLampDataSet(lid);
}

-(ControllerClientStatus)getLampDataSetForID: (NSString *)lampID andLanguage: (NSString *)language
{
    std::string lid([lampID UTF8String]);
    std::string lang([language UTF8String]);
    return self.lampManager->GetLampDataSet(lid, lang);
}

-(ControllerClientStatus)getConsolidatedLampDataSetForID:(NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    return self.lampManager->GetConsolidatedLampDataSet(lid);
}

-(ControllerClientStatus)getConsolidatedLampDataSetForID:(NSString *)lampID andLanguage:(NSString *)language
{
    std::string lid([lampID UTF8String]);
    std::string lang([language UTF8String]);
    return self.lampManager->GetConsolidatedLampDataSet(lid, lang);
}

-(ControllerClientStatus)setLampEffectForID: (NSString *)lampID withEffectID: (NSString *)effectID
{
    std::string lid([lampID UTF8String]);
    std::string eid([effectID UTF8String]);
    return CONTROLLER_CLIENT_OK; //self.lampManager->SetLampEffect(lid, eid);
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
- (lsf::LampManager *)lampManager
{
    return static_cast<lsf::LampManager*>(self.handle);
}

@end
