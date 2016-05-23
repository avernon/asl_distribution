/******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

#ifndef _LSF_PULSEEFFECTMANAGER_CALLBACK_H
#define _LSF_PULSEEFFECTMANAGER_CALLBACK_H

#import "LSFPulseEffectManagerCallbackDelegate.h"
#import <PulseEffectManager.h>

using namespace lsf;

class LSFPulseEffectManagerCallback : public PulseEffectManagerCallback {
public:
    LSFPulseEffectManagerCallback(id<LSFPulseEffectManagerCallbackDelegate> delegate);
    ~LSFPulseEffectManagerCallback();
    void GetPulseEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const PulseEffect& pulseEffect);
    void ApplyPulseEffectOnLampsReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const LSFStringList& lampIDs);
    void ApplyPulseEffectOnLampGroupsReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const LSFStringList& lampGroupIDs);
    void GetAllPulseEffectIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& pulseEffectIDs);
    void GetPulseEffectNameReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const LSFString& language, const LSFString& pulseEffectName);
    void SetPulseEffectNameReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const LSFString& language);
    void PulseEffectsNameChangedCB(const LSFStringList& pulseEffectIDs);
    void CreatePulseEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const uint32_t& trackingID);
    void PulseEffectsCreatedCB(const LSFStringList& pulseEffectIDs);
    void UpdatePulseEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID);
    void PulseEffectsUpdatedCB(const LSFStringList& pulseEffectIDs);
    void DeletePulseEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID);
    void PulseEffectsDeletedCB(const LSFStringList& pulseEffectIDs);

private:
    id<LSFPulseEffectManagerCallbackDelegate> _pemDelegate;
};

#endif /* defined(_LSF_TRANSITIONEFFECTMANAGER_CALLBACK_H) */
