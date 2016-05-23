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

#ifndef LSF_JNI_JLAMPGROUPMANAGERCALLBACK_H_
#define LSF_JNI_JLAMPGROUPMANAGERCALLBACK_H_

#include <list>
#include <string>

#include <LampGroupManager.h>   // lighting/service_framework

#include "NDefs.h"
#include "NUtil.h"
#include "NTypes.h"

namespace lsf {

class JLampGroupManagerCallback : public LampGroupManagerCallback {
  public:
    JLampGroupManagerCallback(jobject jobj);
    virtual ~JLampGroupManagerCallback();

    virtual void GetAllLampGroupIDsReplyCB(const LSFResponseCode& responseCode, const LampGroupIDList& lampGroupIDs) LSF_OVERRIDE;
    virtual void GetLampGroupNameReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID, const LSFString& language, const LampGroupName& lampGroupName) LSF_OVERRIDE;
    virtual void SetLampGroupNameReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID, const LSFString& language) LSF_OVERRIDE;
    virtual void LampGroupsNameChangedCB(const LampGroupIDList& lampGroupIDs) LSF_OVERRIDE;
    virtual void CreateLampGroupReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID) LSF_OVERRIDE;
    virtual void LampGroupsCreatedCB(const LampGroupIDList& lampGroupIDs) LSF_OVERRIDE;
    virtual void GetLampGroupReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID, const LampGroup& lampGroup) LSF_OVERRIDE;
    virtual void DeleteLampGroupReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID) LSF_OVERRIDE;
    virtual void LampGroupsDeletedCB(const LampGroupIDList& lampGroupIDs) LSF_OVERRIDE;
    virtual void TransitionLampGroupStateReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID) LSF_OVERRIDE;
    virtual void PulseLampGroupWithStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID) LSF_OVERRIDE;
    virtual void PulseLampGroupWithPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID) LSF_OVERRIDE;
    virtual void TransitionLampGroupStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID) LSF_OVERRIDE;
    virtual void TransitionLampGroupStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID) LSF_OVERRIDE;
    virtual void TransitionLampGroupStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID) LSF_OVERRIDE;
    virtual void TransitionLampGroupStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID) LSF_OVERRIDE;
    virtual void TransitionLampGroupStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID) LSF_OVERRIDE;
    virtual void ResetLampGroupStateReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID) LSF_OVERRIDE;
    virtual void ResetLampGroupStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID) LSF_OVERRIDE;
    virtual void ResetLampGroupStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID) LSF_OVERRIDE;
    virtual void ResetLampGroupStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID) LSF_OVERRIDE;
    virtual void ResetLampGroupStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID) LSF_OVERRIDE;
    virtual void ResetLampGroupStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID) LSF_OVERRIDE;
    virtual void UpdateLampGroupReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID) LSF_OVERRIDE;
    virtual void LampGroupsUpdatedCB(const LampGroupIDList& lampGroupIDs) LSF_OVERRIDE;
    virtual void TransitionLampGroupStateToPresetReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID) LSF_OVERRIDE;
    virtual void CreateLampGroupWithTrackingReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID, const uint32_t& trackingID) LSF_OVERRIDE;
    virtual void SetLampGroupEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID, const LSFString& effectID) LSF_OVERRIDE;

  protected:
    jweak jdelegate;
};

} /* namespace lsf */
#endif /* LSF_JNI_JLAMPGROUPMANAGERCALLBACK_H_ */
