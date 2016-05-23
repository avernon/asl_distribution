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

#ifndef LSF_JNI_XSCENEELEMENTMANAGERCALLBACK_H_
#define LSF_JNI_XSCENEELEMENTMANAGERCALLBACK_H_

#include <list>

#include <jni.h>

#include <SceneElementManager.h>   // lighting/service_framework

#include "NDefs.h"
#include "NUtil.h"
#include "NTypes.h"

namespace lsf {

class XSceneElementManagerCallback : public SceneElementManagerCallback {
  public:
    XSceneElementManagerCallback(jobject jobj);
    virtual ~XSceneElementManagerCallback();

    virtual void GetAllSceneElementIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& sceneElementIDs) LSF_OVERRIDE;
    virtual void GetSceneElementNameReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID, const LSFString& language, const LSFString& sceneElementName) LSF_OVERRIDE;
    virtual void SetSceneElementNameReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID, const LSFString& language) LSF_OVERRIDE;
    virtual void SceneElementsNameChangedCB(const LSFStringList& sceneElementIDs) LSF_OVERRIDE;
    virtual void CreateSceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID, const uint32_t& trackingID) LSF_OVERRIDE;
    virtual void SceneElementsCreatedCB(const LSFStringList& sceneElementIDs) LSF_OVERRIDE;
    virtual void UpdateSceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID) LSF_OVERRIDE;
    virtual void SceneElementsUpdatedCB(const LSFStringList& sceneElementIDs) LSF_OVERRIDE;
    virtual void DeleteSceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID) LSF_OVERRIDE;
    virtual void SceneElementsDeletedCB(const LSFStringList& sceneElementIDs) LSF_OVERRIDE;
    virtual void GetSceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID, const SceneElement& sceneElement) LSF_OVERRIDE;
    virtual void ApplySceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID) LSF_OVERRIDE;
    virtual void SceneElementsAppliedCB(const LSFStringList& sceneElementIDs) LSF_OVERRIDE;

  protected:
    jweak jdelegate;
};

} /* namespace lsf */
#endif /* LSF_JNI_XSCENEELEMENTMANAGERCALLBACK_H_ */
