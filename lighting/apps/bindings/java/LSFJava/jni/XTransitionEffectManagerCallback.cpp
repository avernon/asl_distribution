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

#include <qcc/Debug.h>

#include "JEnum.h"
#include "XJavaDelegator.h"
#include "XTransitionEffectV2.h"
#include "XTransitionEffectManagerCallback.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;

namespace lsf {

XTransitionEffectManagerCallback::XTransitionEffectManagerCallback(jobject jobj)
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

XTransitionEffectManagerCallback::~XTransitionEffectManagerCallback()
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    env->DeleteWeakGlobalRef(jdelegate);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("DeleteWeakGlobalRef() failed"));
        return;
    }
}

void XTransitionEffectManagerCallback::GetAllTransitionEffectIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& transitionEffectIDs)
{
    XJavaDelegator::Call_Void_ResponseCode_StringList(jdelegate, __func__, responseCode, transitionEffectIDs);
}

void XTransitionEffectManagerCallback::ApplyTransitionEffectOnLampsReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const LSFStringList& lampIDs)
{
    XJavaDelegator::Call_Void_ResponseCode_String_StringList(jdelegate, __func__, responseCode, transitionEffectID, lampIDs);
}

void XTransitionEffectManagerCallback::ApplyTransitionEffectOnLampGroupsReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const LSFStringList& lampGroupIDs)
{
    XJavaDelegator::Call_Void_ResponseCode_String_StringList(jdelegate, __func__, responseCode, transitionEffectID, lampGroupIDs);
}

void XTransitionEffectManagerCallback::GetTransitionEffectNameReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const LSFString& language, const LSFString& transitionEffectName)
{
    XJavaDelegator::Call_Void_ResponseCode_String_String_String(jdelegate, __func__, responseCode, transitionEffectID, language, transitionEffectName);
}

void XTransitionEffectManagerCallback::SetTransitionEffectNameReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const LSFString& language)
{
    XJavaDelegator::Call_Void_ResponseCode_String_String(jdelegate, __func__, responseCode, transitionEffectID, language);
}

void XTransitionEffectManagerCallback::TransitionEffectsNameChangedCB(const LSFStringList& transitionEffectIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, transitionEffectIDs);
}

void XTransitionEffectManagerCallback::CreateTransitionEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const uint32_t& trackingID)
{
    XJavaDelegator::Call_Void_ResponseCode_String_UInt32(jdelegate, __func__, responseCode, transitionEffectID, trackingID);
}

void XTransitionEffectManagerCallback::TransitionEffectsCreatedCB(const LSFStringList& transitionEffectIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, transitionEffectIDs);
}

void XTransitionEffectManagerCallback::UpdateTransitionEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, transitionEffectID);
}

void XTransitionEffectManagerCallback::TransitionEffectsUpdatedCB(const LSFStringList& transitionEffectIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, transitionEffectIDs);
}

void XTransitionEffectManagerCallback::DeleteTransitionEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, transitionEffectID);
}

void XTransitionEffectManagerCallback::TransitionEffectsDeletedCB(const LSFStringList& transitionEffectIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, transitionEffectIDs);
}

void XTransitionEffectManagerCallback::GetTransitionEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const TransitionEffect& transitionEffect)
{
    XJavaDelegator::Call_Void_ResponseCode_String_Object<TransitionEffect, XTransitionEffectV2>(jdelegate, __func__, XClass::xTransitionEffectV2, responseCode, transitionEffectID, transitionEffect);
}

} /* namespace lsf */
