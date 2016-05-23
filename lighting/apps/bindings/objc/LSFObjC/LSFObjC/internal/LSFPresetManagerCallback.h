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

#ifndef _LSF_PRESETMANAGER_CALLBACK_H
#define _LSF_PRESETMANAGER_CALLBACK_H

#import "LSFPresetManagerCallbackDelegate.h"
#import <PresetManager.h>

using namespace lsf;

class LSFPresetManagerCallback : public PresetManagerCallback {
public:
    LSFPresetManagerCallback(id<LSFPresetManagerCallbackDelegate> delegate);
    ~LSFPresetManagerCallback();
    void GetPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const LampState& preset);
    void GetAllPresetIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& presetIDs);
    void GetPresetNameReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const LSFString& language, const LSFString& presetName);
    void SetPresetNameReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const LSFString& language);
    void PresetsNameChangedCB(const LSFStringList& presetIDs);
    void CreatePresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID);
    void CreatePresetWithTrackingReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const uint32_t& trackingID);
    void PresetsCreatedCB(const LSFStringList& presetIDs);
    void UpdatePresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID);
    void PresetsUpdatedCB(const LSFStringList& presetIDs);
    void DeletePresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID);
    void PresetsDeletedCB(const LSFStringList& presetIDs);
    void GetDefaultLampStateReplyCB(const LSFResponseCode& responseCode, const LampState& defaultLampState);
    void SetDefaultLampStateReplyCB(const LSFResponseCode& responseCode);
    void DefaultLampStateChangedCB(void);
    
private:
    id<LSFPresetManagerCallbackDelegate> _pmDelegate;
};

#endif /* defined(_LSF_PRESETMANAGER_CALLBACK_H) */
