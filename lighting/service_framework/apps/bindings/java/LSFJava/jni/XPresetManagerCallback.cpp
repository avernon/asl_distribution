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

#include <qcc/Debug.h>

#include "JEnum.h"
#include "JLampState.h"
#include "XJavaDelegator.h"
#include "XPresetManagerCallback.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;

namespace lsf {

XPresetManagerCallback::XPresetManagerCallback(jobject jobj)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    /*
     * Be careful when using a weak global reference.  They can only be
     * passed to NewLocalRef, NewGlobalRef and DeleteWeakGlobalRef.
     */
    QCC_DbgPrintf(("Taking weak global reference to Java object %p", jobj));
    jdelegate = env->NewWeakGlobalRef(jobj);
    if (env->ExceptionCheck() || !jdelegate) {
        QCC_LogError(ER_FAIL, ("NewWeakGlobalRef() failed"));
        return;
    }
}

XPresetManagerCallback::~XPresetManagerCallback()
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    env->DeleteWeakGlobalRef(jdelegate);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("DeleteWeakGlobalRef() failed"));
        return;
    }
}

void XPresetManagerCallback::GetPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const LampState& preset)
{
    XJavaDelegator::Call_Void_ResponseCode_String_Object<LampState, JLampState>(jdelegate, __func__, XClass::xLampState, responseCode, presetID, preset);
}

void XPresetManagerCallback::GetAllPresetIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& presetIDs)
{
    XJavaDelegator::Call_Void_ResponseCode_StringList(jdelegate, __func__, responseCode, presetIDs);
}

void XPresetManagerCallback::GetPresetNameReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const LSFString& language, const LSFString& presetName)
{
    XJavaDelegator::Call_Void_ResponseCode_String_String_String(jdelegate, __func__, responseCode, presetID, language, presetName);
}

void XPresetManagerCallback::SetPresetNameReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const LSFString& language)
{
    XJavaDelegator::Call_Void_ResponseCode_String_String(jdelegate, __func__, responseCode, presetID, language);
}

void XPresetManagerCallback::PresetsNameChangedCB(const LSFStringList& presetIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, presetIDs);
}

void XPresetManagerCallback::CreatePresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, presetID);
}

void XPresetManagerCallback::PresetsCreatedCB(const LSFStringList& presetIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, presetIDs);
}

void XPresetManagerCallback::UpdatePresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, presetID);
}

void XPresetManagerCallback::PresetsUpdatedCB(const LSFStringList& presetIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, presetIDs);
}

void XPresetManagerCallback::DeletePresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, presetID);
}

void XPresetManagerCallback::PresetsDeletedCB(const LSFStringList& presetIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, presetIDs);
}

} /* namespace lsf */
