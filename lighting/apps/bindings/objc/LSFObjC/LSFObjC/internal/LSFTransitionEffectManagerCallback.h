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

#ifndef _LSF_TRANSITIONEFFECTMANAGER_CALLBACK_H
#define _LSF_TRANSITIONEFFECTMANAGER_CALLBACK_H

#import "LSFTransitionEffectManagerCallbackDelegate.h"
#import <TransitionEffectManager.h>

using namespace lsf;

class LSFTransitionEffectManagerCallback : public TransitionEffectManagerCallback {
public:
    LSFTransitionEffectManagerCallback(id<LSFTransitionEffectManagerCallbackDelegate> delegate);
    ~LSFTransitionEffectManagerCallback();
    void GetTransitionEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const TransitionEffect& transitionEffect);
    void ApplyTransitionEffectOnLampsReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const LSFStringList& lampIDs);
    void ApplyTransitionEffectOnLampGroupsReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const LSFStringList& lampGroupIDs);
    void GetAllTransitionEffectIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& transitionEffectIDs);
    void GetTransitionEffectNameReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const LSFString& language, const LSFString& transitionEffectName);
    void SetTransitionEffectNameReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const LSFString& language);
    void TransitionEffectsNameChangedCB(const LSFStringList& transitionEffectIDs);
    void CreateTransitionEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const uint32_t& trackingID);
    void TransitionEffectsCreatedCB(const LSFStringList& transitionEffectIDs);
    void UpdateTransitionEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID);
    void TransitionEffectsUpdatedCB(const LSFStringList& transitionEffectIDs);
    void DeleteTransitionEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID);
    void TransitionEffectsDeletedCB(const LSFStringList& transitionEffectIDs);

private:
    id<LSFTransitionEffectManagerCallbackDelegate> _temDelegate;
};

#endif /* defined(_LSF_TRANSITIONEFFECTMANAGER_CALLBACK_H) */
