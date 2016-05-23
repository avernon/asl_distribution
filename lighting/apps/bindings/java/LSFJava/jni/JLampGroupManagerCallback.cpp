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
#include "JLampGroup.h"
#include "XJavaDelegator.h"

#include "JLampGroupManagerCallback.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;

namespace lsf {

JLampGroupManagerCallback::JLampGroupManagerCallback(jobject jobj)
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

JLampGroupManagerCallback::~JLampGroupManagerCallback()
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    env->DeleteWeakGlobalRef(jdelegate);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("DeleteWeakGlobalRef() failed"));
        return;
    }
}

void JLampGroupManagerCallback::GetAllLampGroupIDsReplyCB(const LSFResponseCode& responseCode, const LampGroupIDList& lampGroupIDs)
{
    XJavaDelegator::Call_Void_ResponseCode_StringList(jdelegate, __func__, responseCode, lampGroupIDs);
}

void JLampGroupManagerCallback::GetLampGroupNameReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID, const LSFString& language, const LampGroupName& lampGroupName)
{
    XJavaDelegator::Call_Void_ResponseCode_String_String_String(jdelegate, __func__, responseCode, lampGroupID, language, lampGroupName);
}

void JLampGroupManagerCallback::SetLampGroupNameReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID, const LSFString& language)
{
    XJavaDelegator::Call_Void_ResponseCode_String_String(jdelegate, __func__, responseCode, lampGroupID, language);
}

void JLampGroupManagerCallback::LampGroupsNameChangedCB(const LampGroupIDList& lampGroupIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, lampGroupIDs);
}

void JLampGroupManagerCallback::CreateLampGroupReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampGroupID);
}

void JLampGroupManagerCallback::LampGroupsCreatedCB(const LampGroupIDList& lampGroupIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, lampGroupIDs);
}

void JLampGroupManagerCallback::GetLampGroupReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID, const LampGroup& lampGroup)
{
    XJavaDelegator::Call_Void_ResponseCode_String_Object<LampGroup, JLampGroup>(jdelegate, __func__, XClass::xLampGroup, responseCode, lampGroupID, lampGroup);
}

void JLampGroupManagerCallback::DeleteLampGroupReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampGroupID);
}

void JLampGroupManagerCallback::LampGroupsDeletedCB(const LampGroupIDList& lampGroupIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, lampGroupIDs);
}

void JLampGroupManagerCallback::TransitionLampGroupStateReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampGroupID);
}

void JLampGroupManagerCallback::PulseLampGroupWithStateReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampGroupID);
}

void JLampGroupManagerCallback::PulseLampGroupWithPresetReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampGroupID);
}

void JLampGroupManagerCallback::TransitionLampGroupStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampGroupID);
}

void JLampGroupManagerCallback::TransitionLampGroupStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampGroupID);
}

void JLampGroupManagerCallback::TransitionLampGroupStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampGroupID);
}

void JLampGroupManagerCallback::TransitionLampGroupStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampGroupID);
}

void JLampGroupManagerCallback::TransitionLampGroupStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampGroupID);
}

void JLampGroupManagerCallback::ResetLampGroupStateReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampGroupID);
}

void JLampGroupManagerCallback::ResetLampGroupStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampGroupID);
}

void JLampGroupManagerCallback::ResetLampGroupStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampGroupID);
}

void JLampGroupManagerCallback::ResetLampGroupStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampGroupID);
}

void JLampGroupManagerCallback::ResetLampGroupStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampGroupID);
}

void JLampGroupManagerCallback::ResetLampGroupStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampGroupID);
}

void JLampGroupManagerCallback::UpdateLampGroupReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampGroupID);
}

void JLampGroupManagerCallback::LampGroupsUpdatedCB(const LampGroupIDList& lampGroupIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, lampGroupIDs);
}

void JLampGroupManagerCallback::TransitionLampGroupStateToPresetReplyCB(const LSFResponseCode& responseCode, const LampGroupID& lampGroupID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampGroupID);
}

void JLampGroupManagerCallback::CreateLampGroupWithTrackingReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID, const uint32_t& trackingID)
{
    XJavaDelegator::Call_Void_ResponseCode_String_UInt32(jdelegate, __func__, responseCode, lampGroupID, trackingID);
}

void JLampGroupManagerCallback::SetLampGroupEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID, const LSFString& effectID)
{
    XJavaDelegator::Call_Void_ResponseCode_String_String(jdelegate, __func__, responseCode, lampGroupID, effectID);
}

} /* namespace lsf */
