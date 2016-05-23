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

#ifndef _LSF_GROUPMANAGER_CALLBACK_H
#define _LSF_GROUPMANAGER_CALLBACK_H

#import "LSFLampGroupManagerCallbackDelegate.h"
#import <LampGroupManager.h>

using namespace lsf;

class LSFLampGroupManagerCallback : public LampGroupManagerCallback {
  public:
    LSFLampGroupManagerCallback(id<LSFLampGroupManagerCallbackDelegate> delegate);
    ~LSFLampGroupManagerCallback();    
    void GetAllLampGroupIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& lampGroupIDs);
    void GetLampGroupNameReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID, const LSFString& language, const LSFString& lampGroupName);
    void SetLampGroupNameReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID, const LSFString& language);
    void LampGroupsNameChangedCB(const LSFStringList& lampGroupIDs);
    void CreateLampGroupReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID);
    void CreateLampGroupWithTrackingReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID, const uint32_t& trackingID);
    void LampGroupsCreatedCB(const LSFStringList& lampGroupIDs);
    void GetLampGroupReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID, const LampGroup& lampGroup);
    void DeleteLampGroupReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID);
    void LampGroupsDeletedCB(const LSFStringList& lampGroupIDs);
    void TransitionLampGroupStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID);
    void PulseLampGroupWithStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID);
    void PulseLampGroupWithPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID);
    void TransitionLampGroupStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID);
    void TransitionLampGroupStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID);
    void TransitionLampGroupStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID);
    void TransitionLampGroupStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID);
    void TransitionLampGroupStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID);
    void ResetLampGroupStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID);
    void ResetLampGroupStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID);
    void ResetLampGroupStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID);
    void ResetLampGroupStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID);
    void ResetLampGroupStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID);
    void ResetLampGroupStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID);
    void UpdateLampGroupReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID);
    void LampGroupsUpdatedCB(const LSFStringList& lampGroupIDs);
    void TransitionLampGroupStateToPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID);
    void SetLampGroupEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID, const LSFString& effectID);

  private:
    id<LSFLampGroupManagerCallbackDelegate> _lgmDelegate;
};

#endif /* defined(_LSF_GROUPMANAGER_CALLBACK_H) */
