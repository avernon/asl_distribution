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

#ifndef LSF_JNI_XPRESETMANAGERCALLBACK_H_
#define LSF_JNI_XPRESETMANAGERCALLBACK_H_

#include <list>

#include <jni.h>

#include <PresetManager.h>

#include "NDefs.h"
#include "NUtil.h"
#include "NTypes.h"

namespace lsf {

class XPresetManagerCallback : public PresetManagerCallback {
  public:
    XPresetManagerCallback(jobject jobj);
    virtual ~XPresetManagerCallback();

    virtual void GetPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const LampState& preset) LSF_OVERRIDE;
    virtual void GetAllPresetIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& presetIDs) LSF_OVERRIDE;
    virtual void GetPresetNameReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const LSFString& language, const LSFString& presetName) LSF_OVERRIDE;
    virtual void SetPresetNameReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const LSFString& language) LSF_OVERRIDE;
    virtual void PresetsNameChangedCB(const LSFStringList& presetIDs) LSF_OVERRIDE;
    virtual void CreatePresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID) LSF_OVERRIDE;
    virtual void PresetsCreatedCB(const LSFStringList& presetIDs) LSF_OVERRIDE;
    virtual void UpdatePresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID) LSF_OVERRIDE;
    virtual void PresetsUpdatedCB(const LSFStringList& presetIDs) LSF_OVERRIDE;
    virtual void DeletePresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID) LSF_OVERRIDE;
    virtual void PresetsDeletedCB(const LSFStringList& presetIDs) LSF_OVERRIDE;

  protected:
    jweak jdelegate;
};

} /* namespace lsf */
#endif /* LSF_JNI_XPRESETMANAGERCALLBACK_H_ */
