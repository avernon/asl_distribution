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
#include <android/log.h>

#include "XPulseEffectManagerCallback.h"
#include "XCppTestDelegator.h"

#include "JEnum.h"
#include "JEnumArray.h"
#include "JLampDetails.h"
#include "XPulseEffectV2.h"
#include "JLampState.h"
#include "JStringArray.h"
#include "NTypes.h"
#include "NUtil.h"

#include "XCppTestDelegator.h"

#include "org_allseen_lsf_test_PulseEffectManagerCallbackTest.h"

#define QCC_MODULE "AJN-LSF-JNI-TEST"

using namespace ajn;
using namespace lsf;

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PulseEffectManagerCallbackTest_getPulseEffectReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jPulseEffectID, jobject jPulseEffect)
{

    return XCppTestDelegator::Call_Void_ResponseCode_String_Object<XPulseEffectManagerCallback, XPulseEffectV2, PulseEffect>(env, jCallback, jResponseCode, jPulseEffectID, jPulseEffect, &XPulseEffectManagerCallback::GetPulseEffectReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PulseEffectManagerCallbackTest_applyPulseEffectOnLampsReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jPulseEffectID, jobjectArray jLampIDs)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_StringList<XPulseEffectManagerCallback>(env, jCallback, jResponseCode, jPulseEffectID, jLampIDs, &XPulseEffectManagerCallback::ApplyPulseEffectOnLampsReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PulseEffectManagerCallbackTest_applyPulseEffectOnLampGroupsReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jPulseEffectID, jobjectArray jLampGroupIDs)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_StringList<XPulseEffectManagerCallback>(env, jCallback, jResponseCode, jPulseEffectID, jLampGroupIDs, &XPulseEffectManagerCallback::ApplyPulseEffectOnLampGroupsReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PulseEffectManagerCallbackTest_getAllPulseEffectIDsReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jobjectArray jPulseEffectIDs)
{
    return XCppTestDelegator::Call_Void_ResponseCode_StringList<XPulseEffectManagerCallback>(env, jCallback, jResponseCode, jPulseEffectIDs, &XPulseEffectManagerCallback::GetAllPulseEffectIDsReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PulseEffectManagerCallbackTest_getPulseEffectNameReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jPulseEffectID, jstring jLanguage, jstring jPulseEffectName)
{

    return XCppTestDelegator::Call_Void_ResponseCode_String_String_String<XPulseEffectManagerCallback>(env, jCallback, jResponseCode, jPulseEffectID, jLanguage, jPulseEffectName, &XPulseEffectManagerCallback::GetPulseEffectNameReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PulseEffectManagerCallbackTest_setPulseEffectNameReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jPulseEffectID, jstring jLanguage)
{

    return XCppTestDelegator::Call_Void_ResponseCode_String_String<XPulseEffectManagerCallback>(env, jCallback, jResponseCode, jPulseEffectID, jLanguage, &XPulseEffectManagerCallback::SetPulseEffectNameReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PulseEffectManagerCallbackTest_updatePulseEffectReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jPulseEffectID)
{

    return XCppTestDelegator::Call_Void_ResponseCode_String<XPulseEffectManagerCallback>(env, jCallback, jResponseCode, jPulseEffectID, &XPulseEffectManagerCallback::UpdatePulseEffectReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PulseEffectManagerCallbackTest_deletePulseEffectReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jPulseEffectID)
{

    return XCppTestDelegator::Call_Void_ResponseCode_String<XPulseEffectManagerCallback>(env, jCallback, jResponseCode, jPulseEffectID, &XPulseEffectManagerCallback::DeletePulseEffectReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PulseEffectManagerCallbackTest_pulseEffectsNameChangedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jPulseEffectIDs)
{

    return XCppTestDelegator::Call_Void_StringList<XPulseEffectManagerCallback>(env, jCallback, jPulseEffectIDs, &XPulseEffectManagerCallback::PulseEffectsNameChangedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PulseEffectManagerCallbackTest_pulseEffectsCreatedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jPulseEffectIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XPulseEffectManagerCallback>(env, jCallback, jPulseEffectIDs, &XPulseEffectManagerCallback::PulseEffectsCreatedCB, __func__);
}


JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PulseEffectManagerCallbackTest_pulseEffectsUpdatedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jPulseEffectIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XPulseEffectManagerCallback>(env, jCallback, jPulseEffectIDs, &XPulseEffectManagerCallback::PulseEffectsUpdatedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PulseEffectManagerCallbackTest_pulseEffectsDeletedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jPulseEffectIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XPulseEffectManagerCallback>(env, jCallback, jPulseEffectIDs, &XPulseEffectManagerCallback::PulseEffectsDeletedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PulseEffectManagerCallbackTest_createPulseEffectReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jPulseEffectID, jlong jTrackingID)
{

    return XCppTestDelegator::Call_Void_ResponseCode_String_UInt32<XPulseEffectManagerCallback>(env, jCallback, jResponseCode, jPulseEffectID, jTrackingID, &XPulseEffectManagerCallback::CreatePulseEffectReplyCB, __func__);
}


