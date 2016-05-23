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

#ifndef _LSF_SCENEELEMENTMANAGER_CALLBACK_H
#define _LSF_SCENEELEMENTMANAGER_CALLBACK_H

#import "LSFSceneElementManagerCallbackDelegate.h"
#import <SceneElementManager.h>

using namespace lsf;

class LSFSceneElementManagerCallback : public SceneElementManagerCallback {
public:
    LSFSceneElementManagerCallback(id<LSFSceneElementManagerCallbackDelegate> delegate);
    ~LSFSceneElementManagerCallback();
    void GetAllSceneElementIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& sceneElementIDs);
    void GetSceneElementNameReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID, const LSFString& language, const LSFString& sceneElementName);
    void SetSceneElementNameReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID, const LSFString& language);
    void SceneElementsNameChangedCB(const LSFStringList& sceneElementIDs);
    void CreateSceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID, const uint32_t& trackingID);
    void SceneElementsCreatedCB(const LSFStringList& sceneElementIDs);
    void UpdateSceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID);
    void SceneElementsUpdatedCB(const LSFStringList& sceneElementIDs);
    void DeleteSceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID);
    void SceneElementsDeletedCB(const LSFStringList& sceneElementIDs);
    void GetSceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID, const SceneElement& sceneElement);
    void ApplySceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID);
    void SceneElementsAppliedCB(const LSFStringList& sceneElementIDs);

private:
    id<LSFSceneElementManagerCallbackDelegate> _semDelegate;
};

#endif /* defined(_LSF_SCENEELEMENTMANAGER_CALLBACK_H) */
