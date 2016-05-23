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
#include "XJavaDelegator.h"
#include "XMasterScene.h"
#include "XMasterSceneManagerCallback.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;

namespace lsf {

XMasterSceneManagerCallback::XMasterSceneManagerCallback(jobject jobj)
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

XMasterSceneManagerCallback::~XMasterSceneManagerCallback()
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    env->DeleteWeakGlobalRef(jdelegate);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("DeleteWeakGlobalRef() failed"));
        return;
    }
}

void XMasterSceneManagerCallback::GetAllMasterSceneIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& masterSceneIDs)
{
    XJavaDelegator::Call_Void_ResponseCode_StringList(jdelegate, __func__, responseCode, masterSceneIDs);
}

void XMasterSceneManagerCallback::GetMasterSceneNameReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const LSFString& language, const LSFString& masterSceneName)
{
    XJavaDelegator::Call_Void_ResponseCode_String_String_String(jdelegate, __func__, responseCode, masterSceneID, language, masterSceneName);
}

void XMasterSceneManagerCallback::SetMasterSceneNameReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const LSFString& language)
{
    XJavaDelegator::Call_Void_ResponseCode_String_String(jdelegate, __func__, responseCode, masterSceneID, language);
}

void XMasterSceneManagerCallback::MasterScenesNameChangedCB(const LSFStringList& masterSceneIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, masterSceneIDs);
}

void XMasterSceneManagerCallback::CreateMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, masterSceneID);
}

void XMasterSceneManagerCallback::MasterScenesCreatedCB(const LSFStringList& masterSceneIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, masterSceneIDs);
}

void XMasterSceneManagerCallback::GetMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const MasterScene& masterScene)
{
    XJavaDelegator::Call_Void_ResponseCode_String_Object<MasterScene, XMasterScene>(jdelegate, __func__, XClass::xMasterScene, responseCode, masterSceneID, masterScene);
}

void XMasterSceneManagerCallback::DeleteMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, masterSceneID);
}

void XMasterSceneManagerCallback::MasterScenesDeletedCB(const LSFStringList& masterSceneIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, masterSceneIDs);
}

void XMasterSceneManagerCallback::UpdateMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, masterSceneID);
}

void XMasterSceneManagerCallback::MasterScenesUpdatedCB(const LSFStringList& masterSceneIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, masterSceneIDs);
}

void XMasterSceneManagerCallback::ApplyMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, masterSceneID);
}

void XMasterSceneManagerCallback::MasterScenesAppliedCB(const LSFStringList& masterSceneIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, masterSceneIDs);
}

void XMasterSceneManagerCallback::CreateMasterSceneWithTrackingReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const uint32_t& trackingID)
{
    XJavaDelegator::Call_Void_ResponseCode_String_UInt32(jdelegate, __func__, responseCode, masterSceneID, trackingID);
}

} /* namespace lsf */
