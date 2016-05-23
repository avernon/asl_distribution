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

#import "LSFLampManagerCallback.h"

LSFLampManagerCallback::LSFLampManagerCallback(id<LSFLampManagerCallbackDelegate> delegate) : _lmDelegate(delegate)
{
    //Empty Constructor
}

LSFLampManagerCallback::~LSFLampManagerCallback()
{
    _lmDelegate = nil;
}

void LSFLampManagerCallback::GetAllLampIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& lampIDs)
{
    NSMutableArray *lampIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = lampIDs.begin(); iter != lampIDs.end(); ++iter)
    {
        [lampIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    [_lmDelegate getAllLampIDsReplyWithCode: responseCode andLampIDs: lampIDsArray];
}

void LSFLampManagerCallback::GetLampNameReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFString& language, const LSFString& lampName)
{
    [_lmDelegate getLampNameReplyWithCode: responseCode lampID: [NSString stringWithUTF8String: lampID.c_str()] language: [NSString stringWithUTF8String: language.c_str()] andLampName: [NSString stringWithUTF8String: lampName.c_str()]];
}

void LSFLampManagerCallback::GetLampManufacturerReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFString& language, const LSFString& manufacturer)
{
    [_lmDelegate getLampManufacturerReplyWithCode: responseCode lampID: [NSString stringWithUTF8String: lampID.c_str()] language: [NSString stringWithUTF8String: language.c_str()] andManufacturer: [NSString stringWithUTF8String: manufacturer.c_str()]];
}

void LSFLampManagerCallback::SetLampNameReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFString& language)
{
    [_lmDelegate setLampNameReplyWithCode: responseCode lampID: [NSString stringWithUTF8String: lampID.c_str()] andLanguage: [NSString stringWithUTF8String: language.c_str()]];
}

void LSFLampManagerCallback::LampNameChangedCB(const LSFString& lampID, const LSFString& lampName)
{
    [_lmDelegate lampsNameChangedWithID: [NSString stringWithUTF8String: lampID.c_str()] andName: [NSString stringWithUTF8String: lampName.c_str()]];
}

void LSFLampManagerCallback::LampsFoundCB(const LSFStringList& lampIDs)
{
    NSMutableArray *lampIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = lampIDs.begin(); iter != lampIDs.end(); ++iter)
    {
        [lampIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    [_lmDelegate lampsFound: lampIDsArray];
}

void LSFLampManagerCallback::LampsLostCB(const LSFStringList& lampIDs)
{
    NSMutableArray *lampIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = lampIDs.begin(); iter != lampIDs.end(); ++iter)
    {
        [lampIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    [_lmDelegate lampsLost: lampIDsArray];
}

void LSFLampManagerCallback::GetLampDetailsReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampDetails& lampDetails)
{
    LSFSDKLampDetails *details = [[LSFSDKLampDetails alloc] init];
    details.lampMake = lampDetails.make;
    details.lampModel = lampDetails.model;
    details.deviceType = lampDetails.type;
    details.lampType = lampDetails.lampType;
    details.baseType = lampDetails.lampBaseType;
    details.lampBeamAngle = lampDetails.lampBeamAngle;
    details.dimmable = lampDetails.dimmable;
    details.color = lampDetails.color;
    details.variableColorTemp = lampDetails.variableColorTemp;
    details.hasEffects = lampDetails.hasEffects;
    details.maxVoltage = lampDetails.maxVoltage;
    details.minVoltage = lampDetails.minVoltage;
    details.wattage = lampDetails.wattage;
    details.incandescentEquivalent = lampDetails.incandescentEquivalent;
    details.maxLumens = lampDetails.maxLumens;
    details.minTemperature = lampDetails.minTemperature;
    details.maxTemperature = lampDetails.maxTemperature;
    details.colorRenderingIndex = lampDetails.colorRenderingIndex;
    details.lampID = [NSString stringWithUTF8String: lampID.c_str()];
    
    [_lmDelegate getLampDetailsReplyWithCode: responseCode lampID: [NSString stringWithUTF8String: lampID.c_str()] andLampDetails: details];
}

void LSFLampManagerCallback::GetLampParametersReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampParameters& lampParameters)
{
    LSFSDKLampParameters *parameters = [[LSFSDKLampParameters alloc] init];
    parameters.lumens = lampParameters.lumens;
    parameters.energyUsageMilliwatts = lampParameters.energyUsageMilliwatts;
    
    [_lmDelegate getLampParametersReplyWithCode: responseCode lampID: [NSString stringWithUTF8String: lampID.c_str()] andLampParameters: parameters];
}

void LSFLampManagerCallback::GetLampParametersEnergyUsageMilliwattsFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& energyUsageMilliwatts)
{
    [_lmDelegate getLampParametersEnergyUsageMilliwattsFieldReplyWithCode: responseCode lampID: [NSString stringWithUTF8String: lampID.c_str()] andEnergyUsage: energyUsageMilliwatts];
}

void LSFLampManagerCallback::GetLampParametersLumensFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& brightnessLumens)
{
    [_lmDelegate getLampParametersLumensFieldReplyWithCode: responseCode lampID: [NSString stringWithUTF8String: lampID.c_str()] andBrightnessLumens: brightnessLumens];
}

void LSFLampManagerCallback::GetLampStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampState& lampState)
{
    LSFLampState *state = [[LSFLampState alloc] init];
    state.onOff = lampState.onOff;
    state.brightness = lampState.brightness;
    state.hue = lampState.hue;
    state.saturation = lampState.saturation;
    state.colorTemp = lampState.colorTemp;
    
    [_lmDelegate getLampStateReplyWithCode: responseCode lampID: [NSString stringWithUTF8String: lampID.c_str()] andLampState: state];
}

void LSFLampManagerCallback::GetLampStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const bool& onOff)
{
    [_lmDelegate getLampStateOnOffFieldReplyWithCode: responseCode lampID: [NSString stringWithUTF8String: lampID.c_str()] andOnOff: onOff];
}

void LSFLampManagerCallback::GetLampStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& hue)
{
    [_lmDelegate getLampStateHueFieldReplyWithCode: responseCode lampID: [NSString stringWithUTF8String: lampID.c_str()] andHue:hue];
}

void LSFLampManagerCallback::GetLampStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& saturation)
{
    [_lmDelegate getLampStateSaturationFieldReplyWithCode: responseCode lampID: [NSString stringWithUTF8String: lampID.c_str()] andSaturation:saturation];
}

void LSFLampManagerCallback::GetLampStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& brightness)
{
    [_lmDelegate getLampStateBrightnessFieldReplyWithCode: responseCode lampID: [NSString stringWithUTF8String: lampID.c_str()] andBrightness:brightness];
}

void LSFLampManagerCallback::GetLampStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& colorTemp)
{
    [_lmDelegate getLampStateColorTempFieldReplyWithCode: responseCode lampID: [NSString stringWithUTF8String: lampID.c_str()] andColorTemp:colorTemp];
}

void LSFLampManagerCallback::ResetLampStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    [_lmDelegate resetLampStateReplyWithCode: responseCode andLampID: [NSString stringWithUTF8String: lampID.c_str()]];
}

void LSFLampManagerCallback::LampStateChangedCB(const LSFString& lampID, const LampState& lampState)
{
    LSFLampState *state = [[LSFLampState alloc] init];
    state.onOff = lampState.onOff;
    state.brightness = lampState.brightness;
    state.hue = lampState.hue;
    state.saturation = lampState.saturation;
    state.colorTemp = lampState.colorTemp;

    [_lmDelegate lampsStateChangedWithID: [NSString stringWithUTF8String: lampID.c_str()] andLampState: state];
}

void LSFLampManagerCallback::TransitionLampStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    [_lmDelegate transitionLampStateReplyWithCode: responseCode andLampID: [NSString stringWithUTF8String: lampID.c_str()]];
}

void LSFLampManagerCallback::PulseLampWithStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    [_lmDelegate pulseLampWithStateReplyWithCode: responseCode andLampID: [NSString stringWithUTF8String: lampID.c_str()]];
}

void LSFLampManagerCallback::PulseLampWithPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    [_lmDelegate pulseLampWithPresetReplyWithCode: responseCode andLampID: [NSString stringWithUTF8String: lampID.c_str()]];
}

void LSFLampManagerCallback::TransitionLampStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    [_lmDelegate transitionLampStateOnOffFieldReplyWithCode: responseCode andLampID: [NSString stringWithUTF8String: lampID.c_str()]];
}

void LSFLampManagerCallback::TransitionLampStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    [_lmDelegate transitionLampStateHueFieldReplyWithCode: responseCode andLampID: [NSString stringWithUTF8String: lampID.c_str()]];
}

void LSFLampManagerCallback::TransitionLampStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    [_lmDelegate transitionLampStateSaturationFieldReplyWithCode: responseCode andLampID: [NSString stringWithUTF8String: lampID.c_str()]];
}

void LSFLampManagerCallback::TransitionLampStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    [_lmDelegate transitionLampStateBrightnessFieldReplyWithCode: responseCode andLampID: [NSString stringWithUTF8String: lampID.c_str()]];
}

void LSFLampManagerCallback::TransitionLampStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    [_lmDelegate transitionLampStateColorTempFieldReplyWithCode: responseCode andLampID: [NSString stringWithUTF8String: lampID.c_str()]];
}

void LSFLampManagerCallback::GetLampFaultsReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampFaultCodeList& faultCodes)
{
    NSMutableArray *faultCodeArray = [[NSMutableArray alloc] init];
    
    for (std::list<LampFaultCode>::const_iterator iter = faultCodes.begin(); iter != faultCodes.end(); ++iter)
    {
        [faultCodeArray addObject: [NSNumber numberWithInt: (*iter)]];
    }
    
    [_lmDelegate getLampFaultsReplyWithCode: responseCode lampID: [NSString stringWithUTF8String: lampID.c_str()] andFaultCodes: faultCodeArray];
}

void LSFLampManagerCallback::GetLampServiceVersionReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& lampServiceVersion)
{
    [_lmDelegate getLampServiceVersionReplyWithCode: responseCode lampID: [NSString stringWithUTF8String: lampID.c_str()] andLampServiceVersion:lampServiceVersion];
}

void LSFLampManagerCallback::ClearLampFaultReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampFaultCode& faultCode)
{
    [_lmDelegate clearLampFaultReplyWithCode: responseCode lampID: [NSString stringWithUTF8String: lampID.c_str()] andFaultCode: faultCode];
}

void LSFLampManagerCallback::ResetLampStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    [_lmDelegate resetLampStateOnOffFieldReplyWithCode: responseCode andLampID: [NSString stringWithUTF8String: lampID.c_str()]];
}

void LSFLampManagerCallback::ResetLampStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    [_lmDelegate resetLampStateHueFieldReplyWithCode: responseCode andLampID: [NSString stringWithUTF8String: lampID.c_str()]];
}

void LSFLampManagerCallback::ResetLampStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    [_lmDelegate resetLampStateSaturationFieldReplyWithCode: responseCode andLampID: [NSString stringWithUTF8String: lampID.c_str()]];
}

void LSFLampManagerCallback::ResetLampStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    [_lmDelegate resetLampStateBrightnessFieldReplyWithCode: responseCode andLampID: [NSString stringWithUTF8String: lampID.c_str()]];
}

void LSFLampManagerCallback::ResetLampStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    [_lmDelegate resetLampStateColorTempFieldReplyWithCode: responseCode andLampID: [NSString stringWithUTF8String: lampID.c_str()]];
}

void LSFLampManagerCallback::TransitionLampStateToPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    [_lmDelegate transitionLampStateToPresetReplyWithCode: responseCode andLampID: [NSString stringWithUTF8String: lampID.c_str()]];
}

void LSFLampManagerCallback::GetLampSupportedLanguagesReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFStringList& supportedLanguages)
{
    NSMutableArray *supportedLanguagesArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = supportedLanguages.begin(); iter != supportedLanguages.end(); ++iter)
    {
        [supportedLanguagesArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    [_lmDelegate getLampSupportedLanguagesReplyWithCode: responseCode lampID: [NSString stringWithUTF8String: lampID.c_str()] andSupportedLanguages: supportedLanguagesArray];
}

void LSFLampManagerCallback::SetLampEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFString& effectID)
{
    [_lmDelegate setLampEffectReplyWithCode: responseCode lampID: [NSString stringWithUTF8String: lampID.c_str()] andEffectID:[NSString stringWithUTF8String: effectID.c_str()]];
}

void LSFLampManagerCallback::GetConsolidatedLampDataSetReplyCB(const LSFResponseCode &responseCode, const LSFString &lampID, const LSFString &language, const LSFString &lampName, const lsf::LampDetails &lampDetails, const lsf::LampState &lampState, const lsf::LampParameters &lampParameters)
{
    LSFSDKLampDetails *details = [[LSFSDKLampDetails alloc] init];
    details.lampMake = lampDetails.make;
    details.lampModel = lampDetails.model;
    details.deviceType = lampDetails.type;
    details.lampType = lampDetails.lampType;
    details.baseType = lampDetails.lampBaseType;
    details.lampBeamAngle = lampDetails.lampBeamAngle;
    details.dimmable = lampDetails.dimmable;
    details.color = lampDetails.color;
    details.variableColorTemp = lampDetails.variableColorTemp;
    details.hasEffects = lampDetails.hasEffects;
    details.maxVoltage = lampDetails.maxVoltage;
    details.minVoltage = lampDetails.minVoltage;
    details.wattage = lampDetails.wattage;
    details.incandescentEquivalent = lampDetails.incandescentEquivalent;
    details.maxLumens = lampDetails.maxLumens;
    details.minTemperature = lampDetails.minTemperature;
    details.maxTemperature = lampDetails.maxTemperature;
    details.colorRenderingIndex = lampDetails.colorRenderingIndex;
    details.lampID = [NSString stringWithUTF8String: lampID.c_str()];

    LSFLampState *state = [[LSFLampState alloc] init];
    state.onOff = lampState.onOff;
    state.brightness = lampState.brightness;
    state.hue = lampState.hue;
    state.saturation = lampState.saturation;
    state.colorTemp = lampState.colorTemp;

    LSFSDKLampParameters *parameters = [[LSFSDKLampParameters alloc] init];
    parameters.lumens = lampParameters.lumens;
    parameters.energyUsageMilliwatts = lampParameters.energyUsageMilliwatts;

    [_lmDelegate getConsolidatedLampDataSetReplyWithCode: responseCode lampID: [NSString stringWithUTF8String: lampID.c_str()] language: [NSString stringWithUTF8String: language.c_str()] lampName: [NSString stringWithUTF8String: lampName.c_str()] lampDetails: details lampState: state andLampParameters: parameters];
}
