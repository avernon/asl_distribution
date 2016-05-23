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
 *
 ******************************************************************************/

#ifndef LSF_JNI_JLAMPMANAGERCALLBACK_H_
#define LSF_JNI_JLAMPMANAGERCALLBACK_H_

#include <list>
#include <string>

#include <LampManager.h>    // lighting/service_framework

#include "NDefs.h"
#include "NUtil.h"
#include "NTypes.h"

namespace lsf {

class JLampManagerCallback : public LampManagerCallback {
  public:
    JLampManagerCallback(jobject jobj);
    virtual ~JLampManagerCallback();

    virtual void GetAllLampIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& lampIDs) LSF_OVERRIDE;
    virtual void GetLampNameReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFString& language, const LSFString& lampName) LSF_OVERRIDE;
    virtual void GetLampManufacturerReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFString& language, const LSFString& manufacturer) LSF_OVERRIDE;
    virtual void SetLampNameReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFString& language) LSF_OVERRIDE;
    virtual void LampNameChangedCB(const LSFString& lampID, const LSFString& lampName) LSF_OVERRIDE;
    virtual void LampsFoundCB(const LSFStringList& lampIDs) LSF_OVERRIDE;
    virtual void LampsLostCB(const LSFStringList& lampIDs) LSF_OVERRIDE;
    virtual void GetLampDetailsReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampDetails& lampDetails) LSF_OVERRIDE;
    virtual void GetLampParametersReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampParameters& lampParameters) LSF_OVERRIDE;
    virtual void GetLampParametersEnergyUsageMilliwattsFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& energyUsageMilliwatts) LSF_OVERRIDE;
    virtual void GetLampParametersLumensFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& brightnessLumens) LSF_OVERRIDE;
    virtual void GetLampStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampState& lampState) LSF_OVERRIDE;
    virtual void GetLampStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const bool& onOff) LSF_OVERRIDE;
    virtual void GetLampStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& hue) LSF_OVERRIDE;
    virtual void GetLampStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& saturation) LSF_OVERRIDE;
    virtual void GetLampStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& brightness) LSF_OVERRIDE;
    virtual void GetLampStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& colorTemp) LSF_OVERRIDE;
    virtual void ResetLampStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) LSF_OVERRIDE;
    virtual void LampStateChangedCB(const LSFString& lampID, const LampState& lampState) LSF_OVERRIDE;
    virtual void TransitionLampStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) LSF_OVERRIDE;
    virtual void PulseLampWithStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) LSF_OVERRIDE;
    virtual void PulseLampWithPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) LSF_OVERRIDE;
    virtual void TransitionLampStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) LSF_OVERRIDE;
    virtual void TransitionLampStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) LSF_OVERRIDE;
    virtual void TransitionLampStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) LSF_OVERRIDE;
    virtual void TransitionLampStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) LSF_OVERRIDE;
    virtual void TransitionLampStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) LSF_OVERRIDE;
    virtual void GetLampFaultsReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampFaultCodeList& faultCodes) LSF_OVERRIDE;
    virtual void GetLampServiceVersionReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& lampServiceVersion) LSF_OVERRIDE;
    virtual void ClearLampFaultReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampFaultCode& faultCode) LSF_OVERRIDE;
    virtual void ResetLampStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) LSF_OVERRIDE;
    virtual void ResetLampStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) LSF_OVERRIDE;
    virtual void ResetLampStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) LSF_OVERRIDE;
    virtual void ResetLampStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) LSF_OVERRIDE;
    virtual void ResetLampStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) LSF_OVERRIDE;
    virtual void TransitionLampStateToPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) LSF_OVERRIDE;
    virtual void GetLampSupportedLanguagesReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFStringList& supportedLanguages) LSF_OVERRIDE;;

  protected:
    jweak jdelegate;
};

} /* namespace lsf */
#endif /* LSF_JNI_JLAMPMANAGERCALLBACK_H_ */
