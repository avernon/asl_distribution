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

#ifndef _LSF_MASTERSCENEMANAGER_CALLBACK_H
#define _LSF_MASTERSCENEMANAGER_CALLBACK_H

#import "LSFMasterSceneManagerCallbackDelegate.h"
#import "MasterSceneManager.h"

using namespace lsf;

class LSFMasterSceneManagerCallback : public MasterSceneManagerCallback {
public:
    LSFMasterSceneManagerCallback(id<LSFMasterSceneManagerCallbackDelegate> delegate);
    ~LSFMasterSceneManagerCallback();
    void GetAllMasterSceneIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& masterSceneList);
    void GetMasterSceneNameReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const LSFString& language, const LSFString& masterSceneName);
    void SetMasterSceneNameReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const LSFString& language);
    void MasterScenesNameChangedCB(const LSFStringList& masterSceneIDs);
    void CreateMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID);
    void MasterScenesCreatedCB(const LSFStringList& masterSceneIDs);
    void GetMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const MasterScene& masterScene);
    void DeleteMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID);
    void MasterScenesDeletedCB(const LSFStringList& masterSceneIDs);
    void UpdateMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID);
    void MasterScenesUpdatedCB(const LSFStringList& masterSceneIDs);
    void ApplyMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID);
    void MasterScenesAppliedCB(const LSFStringList& masterSceneIDs);
    
private:
    id<LSFMasterSceneManagerCallbackDelegate> _msmDelegate;
};

#endif /* defined(_LSF_MASTERSCENEMANAGER_CALLBACK_H) */