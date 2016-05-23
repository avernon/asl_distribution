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

#ifndef LSF_JNI_XSCENEMANAGERCALLBACK_H_
#define LSF_JNI_XSCENEMANAGERCALLBACK_H_

#include <list>

#include <jni.h>

#include <SceneManager.h>   // lighting/service_framework

#include "NDefs.h"
#include "NUtil.h"
#include "NTypes.h"

namespace lsf {

class XSceneManagerCallback : public SceneManagerCallback {
  public:
    XSceneManagerCallback(jobject jobj);
    virtual ~XSceneManagerCallback();

    virtual void GetAllSceneIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& sceneIDs) LSF_OVERRIDE;
    virtual void GetSceneNameReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID, const LSFString& language, const LSFString& sceneName) LSF_OVERRIDE;
    virtual void SetSceneNameReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID, const LSFString& language) LSF_OVERRIDE;
    virtual void ScenesNameChangedCB(const LSFStringList& sceneIDs) LSF_OVERRIDE;
    virtual void CreateSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID) LSF_OVERRIDE;
    virtual void ScenesCreatedCB(const LSFStringList& sceneIDs) LSF_OVERRIDE;
    virtual void UpdateSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID) LSF_OVERRIDE;
    virtual void ScenesUpdatedCB(const LSFStringList& sceneIDs) LSF_OVERRIDE;
    virtual void DeleteSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID) LSF_OVERRIDE;
    virtual void ScenesDeletedCB(const LSFStringList& sceneIDs) LSF_OVERRIDE;
    virtual void GetSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID, const Scene& scene) LSF_OVERRIDE;
    virtual void ApplySceneReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID) LSF_OVERRIDE;
    virtual void ScenesAppliedCB(const LSFStringList& sceneIDs) LSF_OVERRIDE;

  protected:
    jweak jdelegate;
};

} /* namespace lsf */
#endif /* LSF_JNI_XSCENEMANAGERCALLBACK_H_ */
