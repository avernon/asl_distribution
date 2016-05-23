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
#include "XScene.h"
#include "XSceneWithSceneElements.h"
#include "XSceneManagerCallback.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;

namespace lsf {

XSceneManagerCallback::XSceneManagerCallback(jobject jobj)
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

XSceneManagerCallback::~XSceneManagerCallback()
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    env->DeleteWeakGlobalRef(jdelegate);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("DeleteWeakGlobalRef() failed"));
        return;
    }
}

void XSceneManagerCallback::GetAllSceneIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& sceneIDs)
{
    XJavaDelegator::Call_Void_ResponseCode_StringList(jdelegate, __func__, responseCode, sceneIDs);
}

void XSceneManagerCallback::GetSceneNameReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID, const LSFString& language, const LSFString& sceneName)
{
    XJavaDelegator::Call_Void_ResponseCode_String_String_String(jdelegate, __func__, responseCode, sceneID, language, sceneName);
}

void XSceneManagerCallback::SetSceneNameReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID, const LSFString& language)
{
    XJavaDelegator::Call_Void_ResponseCode_String_String(jdelegate, __func__, responseCode, sceneID, language);
}

void XSceneManagerCallback::ScenesNameChangedCB(const LSFStringList& sceneIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, sceneIDs);
}

void XSceneManagerCallback::CreateSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, sceneID);
}

void XSceneManagerCallback::ScenesCreatedCB(const LSFStringList& sceneIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, sceneIDs);
}

void XSceneManagerCallback::UpdateSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, sceneID);
}

void XSceneManagerCallback::ScenesUpdatedCB(const LSFStringList& sceneIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, sceneIDs);
}

void XSceneManagerCallback::DeleteSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, sceneID);
}

void XSceneManagerCallback::ScenesDeletedCB(const LSFStringList& sceneIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, sceneIDs);
}

void XSceneManagerCallback::GetSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID, const Scene& scene)
{
    XJavaDelegator::Call_Void_ResponseCode_String_Object<Scene, XScene>(jdelegate, __func__, XClass::xScene, responseCode, sceneID, scene);
}

void XSceneManagerCallback::ApplySceneReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, sceneID);
}

void XSceneManagerCallback::ScenesAppliedCB(const LSFStringList& sceneIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, sceneIDs);
}

void XSceneManagerCallback::CreateSceneWithTrackingReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID, const uint32_t& trackingID)
{
    XJavaDelegator::Call_Void_ResponseCode_String_UInt32(jdelegate, __func__, responseCode, sceneID, trackingID);
}

void XSceneManagerCallback::CreateSceneWithSceneElementsReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID, const uint32_t& trackingID)
{
    XJavaDelegator::Call_Void_ResponseCode_String_UInt32(jdelegate, __func__, responseCode, sceneID, trackingID);
}

void XSceneManagerCallback::UpdateSceneWithSceneElementsReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, sceneID);
}

void XSceneManagerCallback::GetSceneWithSceneElementsReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID, const SceneWithSceneElements& scene)
{
    XJavaDelegator::Call_Void_ResponseCode_String_Object<SceneWithSceneElements, XSceneWithSceneElements>(jdelegate, __func__, XClass::xSceneWithSceneElements, responseCode, sceneID, scene);
}

} /* namespace lsf */
