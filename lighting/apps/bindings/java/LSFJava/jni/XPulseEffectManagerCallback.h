/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

#ifndef LSF_JNI_XPULSEEFFECTMANAGERCALLBACK_H_
#define LSF_JNI_XPULSEEFFECTMANAGERCALLBACK_H_

#include <list>

#include <jni.h>

#include <PulseEffectManager.h>   // lighting/service_framework

#include "NDefs.h"
#include "NUtil.h"
#include "NTypes.h"

namespace lsf {

class XPulseEffectManagerCallback : public PulseEffectManagerCallback {
  public:
    XPulseEffectManagerCallback(jobject jobj);
    virtual ~XPulseEffectManagerCallback();

    virtual void GetPulseEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const PulseEffect& pulseEffect) LSF_OVERRIDE;
    virtual void ApplyPulseEffectOnLampsReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const LSFStringList& lampIDs) LSF_OVERRIDE;
    virtual void ApplyPulseEffectOnLampGroupsReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const LSFStringList& lampGroupIDs) LSF_OVERRIDE;
    virtual void GetAllPulseEffectIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& pulseEffectIDs) LSF_OVERRIDE;
    virtual void GetPulseEffectNameReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const LSFString& language, const LSFString& pulseEffectName) LSF_OVERRIDE;
    virtual void SetPulseEffectNameReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const LSFString& language) LSF_OVERRIDE;
    virtual void PulseEffectsNameChangedCB(const LSFStringList& pulseEffectIDs) LSF_OVERRIDE;
    virtual void CreatePulseEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const uint32_t& trackingID) LSF_OVERRIDE;
    virtual void PulseEffectsCreatedCB(const LSFStringList& pulseEffectIDs) LSF_OVERRIDE;
    virtual void UpdatePulseEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID) LSF_OVERRIDE;
    virtual void PulseEffectsUpdatedCB(const LSFStringList& pulseEffectIDs) LSF_OVERRIDE;
    virtual void DeletePulseEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID) LSF_OVERRIDE;
    virtual void PulseEffectsDeletedCB(const LSFStringList& pulseEffectIDs) LSF_OVERRIDE;

  protected:
    jweak jdelegate;
};

} /* namespace lsf */
#endif /* LSF_JNI_XPULSEEFFECTMANAGERCALLBACK_H_ */
