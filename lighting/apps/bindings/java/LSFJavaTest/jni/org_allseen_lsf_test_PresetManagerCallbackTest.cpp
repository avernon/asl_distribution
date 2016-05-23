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
#include <stddef.h>

#include <qcc/Debug.h>
#include <qcc/Log.h>

#include "JLampState.h"
#include "XPresetManagerCallback.h"
#include "XCppTestDelegator.h"

#include "org_allseen_lsf_test_PresetManagerCallbackTest.h"

#define QCC_MODULE "AJN-LSF-JNI-TEST"

using namespace ajn;
using namespace lsf;

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PresetManagerCallbackTest_getAllPresetIDsReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jobjectArray jPresetIDs)
{
    return XCppTestDelegator::Call_Void_ResponseCode_StringList<XPresetManagerCallback>(env, jCallback, jResponseCode, jPresetIDs, &XPresetManagerCallback::GetAllPresetIDsReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PresetManagerCallbackTest_getPresetReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jPresetID, jobject jPreset)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_Object<XPresetManagerCallback, JLampState, LampState>(env, jCallback, jResponseCode, jPresetID, jPreset, &XPresetManagerCallback::GetPresetReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PresetManagerCallbackTest_getPresetNameReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jPresetID, jstring jLanguage, jstring jPresetName)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_String_String<XPresetManagerCallback>(env, jCallback, jResponseCode, jPresetID, jLanguage, jPresetName, &XPresetManagerCallback::GetPresetNameReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PresetManagerCallbackTest_setPresetNameReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jPresetID, jstring jLanguage)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_String<XPresetManagerCallback>(env, jCallback, jResponseCode, jPresetID, jLanguage, &XPresetManagerCallback::SetPresetNameReplyCB, __func__);
}






JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PresetManagerCallbackTest_presetsNameChangedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jPresetIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XPresetManagerCallback>(env, jCallback, jPresetIDs, &XPresetManagerCallback::PresetsNameChangedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PresetManagerCallbackTest_createPresetReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jPresetID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<XPresetManagerCallback>(env, jCallback, jResponseCode, jPresetID, &XPresetManagerCallback::CreatePresetReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PresetManagerCallbackTest_presetsCreatedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jPresetIDs)
{
	return XCppTestDelegator::Call_Void_StringList<XPresetManagerCallback>(env, jCallback, jPresetIDs, &XPresetManagerCallback::PresetsCreatedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PresetManagerCallbackTest_updatePresetReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jPresetID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<XPresetManagerCallback>(env, jCallback, jResponseCode, jPresetID, &XPresetManagerCallback::UpdatePresetReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PresetManagerCallbackTest_presetsUpdatedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jPresetIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XPresetManagerCallback>(env, jCallback, jPresetIDs, &XPresetManagerCallback::PresetsUpdatedCB, __func__);
}


JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PresetManagerCallbackTest_deletePresetReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jPresetID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<XPresetManagerCallback>(env, jCallback, jResponseCode, jPresetID, &XPresetManagerCallback::DeletePresetReplyCB, __func__);
}


JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PresetManagerCallbackTest_presetsDeletedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jPresetIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XPresetManagerCallback>(env, jCallback, jPresetIDs, &XPresetManagerCallback::PresetsDeletedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PresetManagerCallbackTest_getDefaultLampStateReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jobject jDefaultLampState)
{
    return XCppTestDelegator::Call_Void_ResponseCode_Object<XPresetManagerCallback, JLampState, LampState>(env, jCallback, jResponseCode, jDefaultLampState, &XPresetManagerCallback::GetDefaultLampStateReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PresetManagerCallbackTest_setDefaultLampStateReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode)
{
    return XCppTestDelegator::Call_Void_ResponseCode<XPresetManagerCallback>(env, jCallback, jResponseCode, &XPresetManagerCallback::SetDefaultLampStateReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PresetManagerCallbackTest_defaultLampStateChangedCB(JNIEnv *env, jobject thiz, jobject jCallback)
{
    return XCppTestDelegator::Call_Void<XPresetManagerCallback>(env, jCallback, &XPresetManagerCallback::DefaultLampStateChangedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_PresetManagerCallbackTest_createPresetWithTrackingReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jPresetID, jlong jTrackingID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_UInt32<XPresetManagerCallback>(env, jCallback, jResponseCode, jPresetID, jTrackingID, &XPresetManagerCallback::CreatePresetWithTrackingReplyCB, __func__);
}

