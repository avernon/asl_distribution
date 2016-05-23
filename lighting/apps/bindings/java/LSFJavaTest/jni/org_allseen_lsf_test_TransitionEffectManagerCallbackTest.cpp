/******************************************************************************
 * Copyright (c), AllSeen Alliance. All rights reserved.
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
#include <stddef.h>

#include <qcc/Debug.h>
#include <qcc/Log.h>

#include "XTransitionEffectManagerCallback.h"
#include "XCppTestDelegator.h"

#include "JEnum.h"
#include "JEnumArray.h"
#include "JLampDetails.h"
#include "XTransitionEffectV2.h"

#include "JLampState.h"
#include "JStringArray.h"
#include "NTypes.h"
#include "NUtil.h"

#include "XCppTestDelegator.h"

#include "org_allseen_lsf_test_TransitionEffectManagerCallbackTest.h"

#define QCC_MODULE "AJN-LSF-JNI-TEST"

using namespace ajn;
using namespace lsf;


JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_TransitionEffectManagerCallbackTest_getTransitionEffectReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jTransitionEffectID, jobject jTransitionEffect)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_Object<XTransitionEffectManagerCallback, XTransitionEffectV2, TransitionEffect>(env, jCallback, jResponseCode, jTransitionEffectID, jTransitionEffect, &XTransitionEffectManagerCallback::GetTransitionEffectReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_TransitionEffectManagerCallbackTest_applyTransitionEffectOnLampsReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jTransitionEffectID, jobjectArray jLampIDs)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_StringList<XTransitionEffectManagerCallback>(env, jCallback, jResponseCode, jTransitionEffectID, jLampIDs, &XTransitionEffectManagerCallback::ApplyTransitionEffectOnLampsReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_TransitionEffectManagerCallbackTest_applyTransitionEffectOnLampGroupsReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jTransitionEffectID, jobjectArray jLampGroupIDs)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_StringList<XTransitionEffectManagerCallback>(env, jCallback, jResponseCode, jTransitionEffectID, jLampGroupIDs, &XTransitionEffectManagerCallback::ApplyTransitionEffectOnLampGroupsReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_TransitionEffectManagerCallbackTest_getAllTransitionEffectIDsReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jobjectArray jTransitionEffectIDs)
{
    return XCppTestDelegator::Call_Void_ResponseCode_StringList<XTransitionEffectManagerCallback>(env, jCallback, jResponseCode, jTransitionEffectIDs, &XTransitionEffectManagerCallback::GetAllTransitionEffectIDsReplyCB, __func__);
}


JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_TransitionEffectManagerCallbackTest_updateTransitionEffectReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jTransitionEffectID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<XTransitionEffectManagerCallback>(env, jCallback, jResponseCode, jTransitionEffectID, &XTransitionEffectManagerCallback::UpdateTransitionEffectReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_TransitionEffectManagerCallbackTest_deleteTransitionEffectReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jTransitionEffectID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<XTransitionEffectManagerCallback>(env, jCallback, jResponseCode, jTransitionEffectID, &XTransitionEffectManagerCallback::DeleteTransitionEffectReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_TransitionEffectManagerCallbackTest_getTransitionEffectNameReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jTransitionEffectID, jstring jLanguage, jstring jTransitionEffectName)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_String_String<XTransitionEffectManagerCallback>(env, jCallback, jResponseCode, jTransitionEffectID, jLanguage, jTransitionEffectName, &XTransitionEffectManagerCallback::GetTransitionEffectNameReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_TransitionEffectManagerCallbackTest_setTransitionEffectNameReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jTransitionEffectID, jstring jLanguage)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_String<XTransitionEffectManagerCallback>(env, jCallback, jResponseCode, jTransitionEffectID, jLanguage, &XTransitionEffectManagerCallback::SetTransitionEffectNameReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_TransitionEffectManagerCallbackTest_createTransitionEffectReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jTransitionEffectID, jlong jTrackingID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_UInt32<XTransitionEffectManagerCallback>(env, jCallback, jResponseCode, jTransitionEffectID, jTrackingID, &XTransitionEffectManagerCallback::CreateTransitionEffectReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_TransitionEffectManagerCallbackTest_transitionEffectsNameChangedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jTransitionEffectIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XTransitionEffectManagerCallback>(env, jCallback, jTransitionEffectIDs, &XTransitionEffectManagerCallback::TransitionEffectsNameChangedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_TransitionEffectManagerCallbackTest_transitionEffectsCreatedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jTransitionEffectIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XTransitionEffectManagerCallback>(env, jCallback, jTransitionEffectIDs, &XTransitionEffectManagerCallback::TransitionEffectsCreatedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_TransitionEffectManagerCallbackTest_transitionEffectsUpdatedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jTransitionEffectIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XTransitionEffectManagerCallback>(env, jCallback, jTransitionEffectIDs, &XTransitionEffectManagerCallback::TransitionEffectsUpdatedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_TransitionEffectManagerCallbackTest_transitionEffectsDeletedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jTransitionEffectIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XTransitionEffectManagerCallback>(env, jCallback, jTransitionEffectIDs, &XTransitionEffectManagerCallback::TransitionEffectsDeletedCB, __func__);
}

