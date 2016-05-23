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

#ifndef LSF_JNI_XTRANSITIONEFFECTMANAGERCALLBACK_H_
#define LSF_JNI_XTRANSITIONEFFECTMANAGERCALLBACK_H_

#include <list>

#include <jni.h>

#include <TransitionEffectManager.h>   // lighting/service_framework

#include "NDefs.h"
#include "NUtil.h"
#include "NTypes.h"

namespace lsf {

class XTransitionEffectManagerCallback : public TransitionEffectManagerCallback {
  public:
    XTransitionEffectManagerCallback(jobject jobj);
    virtual ~XTransitionEffectManagerCallback();

    virtual void GetTransitionEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const TransitionEffect& transitionEffect) LSF_OVERRIDE;
    virtual void ApplyTransitionEffectOnLampsReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const LSFStringList& lampIDs) LSF_OVERRIDE;
    virtual void ApplyTransitionEffectOnLampGroupsReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const LSFStringList& lampGroupIDs) LSF_OVERRIDE;
    virtual void GetAllTransitionEffectIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& transitionEffectIDs) LSF_OVERRIDE;
    virtual void GetTransitionEffectNameReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const LSFString& language, const LSFString& transitionEffectName) LSF_OVERRIDE;
    virtual void SetTransitionEffectNameReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const LSFString& language) LSF_OVERRIDE;
    virtual void TransitionEffectsNameChangedCB(const LSFStringList& transitionEffectIDs) LSF_OVERRIDE;
    virtual void CreateTransitionEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const uint32_t& trackingID) LSF_OVERRIDE;
    virtual void TransitionEffectsCreatedCB(const LSFStringList& transitionEffectIDs) LSF_OVERRIDE;
    virtual void UpdateTransitionEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID) LSF_OVERRIDE;
    virtual void TransitionEffectsUpdatedCB(const LSFStringList& transitionEffectIDs) LSF_OVERRIDE;
    virtual void DeleteTransitionEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID) LSF_OVERRIDE;
    virtual void TransitionEffectsDeletedCB(const LSFStringList& transitionEffectIDs) LSF_OVERRIDE;

  protected:
    jweak jdelegate;
};

} /* namespace lsf */
#endif /* LSF_JNI_XTRANSITIONEFFECTMANAGERCALLBACK_H_ */
