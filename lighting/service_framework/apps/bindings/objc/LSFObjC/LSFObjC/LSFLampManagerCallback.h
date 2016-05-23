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

#ifndef _LSF_LAMPMANAGER_CALLBACK_H
#define _LSF_LAMPMANAGER_CALLBACK_H

#import "LSFLampManagerCallbackDelegate.h"
#import "LampManager.h"

using namespace lsf;

class LSFLampManagerCallback : public LampManagerCallback {
  public:
    LSFLampManagerCallback(id<LSFLampManagerCallbackDelegate> delegate);
    ~LSFLampManagerCallback();    
    void GetAllLampIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& lampIDs);
    void GetLampNameReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFString& language, const LSFString& lampName);
    void GetLampManufacturerReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFString& language, const LSFString& manufacturer);
    void SetLampNameReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFString& language);
    void LampNameChangedCB(const LSFString& lampID, const LSFString& lampName);
    void LampsFoundCB(const LSFStringList& lampIDs);
    void LampsLostCB(const LSFStringList& lampIDs);
    void GetLampDetailsReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampDetails& lampDetails);
    void GetLampParametersReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampParameters& lampParameters);
    void GetLampParametersEnergyUsageMilliwattsFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& energyUsageMilliwatts);
    void GetLampParametersLumensFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& brightnessLumens);
    void GetLampStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampState& lampState);
    void GetLampStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const bool& onOff);
    void GetLampStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& hue);
    void GetLampStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& saturation);
    void GetLampStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& brightness);
    void GetLampStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& colorTemp);
    void ResetLampStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID);
    void LampStateChangedCB(const LSFString& lampID, const LampState& lampState);
    void TransitionLampStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID);
    void PulseLampWithStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID);
    void PulseLampWithPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID);
    void TransitionLampStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID);
    void TransitionLampStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID);
    void TransitionLampStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID);
    void TransitionLampStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID);
    void TransitionLampStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID);
    void GetLampFaultsReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampFaultCodeList& faultCodes);
    void GetLampServiceVersionReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& lampServiceVersion);
    void ClearLampFaultReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampFaultCode& faultCode);
    void ResetLampStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID);
    void ResetLampStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID);
    void ResetLampStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID);
    void ResetLampStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID);
    void ResetLampStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID);
    void TransitionLampStateToPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID);
    void GetLampSupportedLanguagesReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFStringList& supportedLanguages);

  private:
    id<LSFLampManagerCallbackDelegate> _lmDelegate;
};

#endif /* defined(_LSF_LAMPMANAGER_CALLBACK_H) */
