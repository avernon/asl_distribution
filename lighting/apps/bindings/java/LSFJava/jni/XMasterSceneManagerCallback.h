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

#ifndef LSF_JNI_XMASTERSCENEMANAGERCALLBACK_H_
#define LSF_JNI_XMASTERSCENEMANAGERCALLBACK_H_

#include <jni.h>

#include <MasterSceneManager.h>   // lighting/service_framework

#include "NDefs.h"
#include "NTypes.h"

namespace lsf {

class XMasterSceneManagerCallback : public MasterSceneManagerCallback {
public:
    XMasterSceneManagerCallback(jobject jobj);
    virtual ~XMasterSceneManagerCallback();

    virtual void GetAllMasterSceneIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& masterSceneIDs) LSF_OVERRIDE;
    virtual void GetMasterSceneNameReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const LSFString& language, const LSFString& masterSceneName) LSF_OVERRIDE;
    virtual void SetMasterSceneNameReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const LSFString& language) LSF_OVERRIDE;
    virtual void MasterScenesNameChangedCB(const LSFStringList& masterSceneIDs) LSF_OVERRIDE;
    virtual void CreateMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID) LSF_OVERRIDE;
    virtual void MasterScenesCreatedCB(const LSFStringList& masterSceneIDs) LSF_OVERRIDE;
    virtual void GetMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const MasterScene& masterScene) LSF_OVERRIDE;
    virtual void DeleteMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID) LSF_OVERRIDE;
    virtual void MasterScenesDeletedCB(const LSFStringList& masterSceneIDs) LSF_OVERRIDE;
    virtual void UpdateMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID) LSF_OVERRIDE;
    virtual void MasterScenesUpdatedCB(const LSFStringList& masterSceneIDs) LSF_OVERRIDE;
    virtual void ApplyMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID) LSF_OVERRIDE;
    virtual void MasterScenesAppliedCB(const LSFStringList& masterSceneIDs) LSF_OVERRIDE;
    virtual void CreateMasterSceneWithTrackingReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const uint32_t& trackingID) LSF_OVERRIDE;

protected:
    jweak jdelegate;
};

} /* namespace lsf */
#endif /* LSF_JNI_XMASTERSCENEMANAGERCALLBACK_H_ */
