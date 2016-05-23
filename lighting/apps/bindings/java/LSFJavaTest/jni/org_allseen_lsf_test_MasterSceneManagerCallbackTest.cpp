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

#include "XMasterScene.h"
#include "XMasterSceneManagerCallback.h"


#include "JEnum.h"
#include "JEnumArray.h"
#include "JLampDetails.h"
#include "JLampState.h"
#include "JStringArray.h"
#include "NTypes.h"
#include "NUtil.h"
#include "XCppTestDelegator.h"

#include "org_allseen_lsf_test_MasterSceneManagerCallbackTest.h"

#define QCC_MODULE "AJN-LSF-JNI-TEST"

using namespace ajn;
using namespace lsf;


JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_MasterSceneManagerCallbackTest_getAllMasterSceneIDsReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jobjectArray jMasterSceneIDs)
{
    return XCppTestDelegator::Call_Void_ResponseCode_StringList<XMasterSceneManagerCallback>(env, jCallback, jResponseCode, jMasterSceneIDs, &XMasterSceneManagerCallback::GetAllMasterSceneIDsReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_MasterSceneManagerCallbackTest_getMasterSceneNameReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jMasterSceneID, jstring jLanguage, jstring jMasterSceneName)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_String_String<XMasterSceneManagerCallback>(env, jCallback, jResponseCode, jMasterSceneID, jLanguage, jMasterSceneName, &XMasterSceneManagerCallback::GetMasterSceneNameReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_MasterSceneManagerCallbackTest_setMasterSceneNameReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jMasterSceneID, jstring jLanguage)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_String<XMasterSceneManagerCallback>(env, jCallback, jResponseCode, jMasterSceneID, jLanguage, &XMasterSceneManagerCallback::SetMasterSceneNameReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_MasterSceneManagerCallbackTest_createMasterSceneReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jMasterSceneID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<XMasterSceneManagerCallback>(env, jCallback, jResponseCode, jMasterSceneID, &XMasterSceneManagerCallback::CreateMasterSceneReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_MasterSceneManagerCallbackTest_deleteMasterSceneReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jMasterSceneID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<XMasterSceneManagerCallback>(env, jCallback, jResponseCode, jMasterSceneID, &XMasterSceneManagerCallback::DeleteMasterSceneReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_MasterSceneManagerCallbackTest_updateMasterSceneReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jMasterSceneID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<XMasterSceneManagerCallback>(env, jCallback, jResponseCode, jMasterSceneID, &XMasterSceneManagerCallback::UpdateMasterSceneReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_MasterSceneManagerCallbackTest_applyMasterSceneReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jMasterSceneID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<XMasterSceneManagerCallback>(env, jCallback, jResponseCode, jMasterSceneID, &XMasterSceneManagerCallback::ApplyMasterSceneReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_MasterSceneManagerCallbackTest_createMasterSceneWithTrackingReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jMasterSceneID, jlong jTrackingID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_UInt32<XMasterSceneManagerCallback>(env, jCallback, jResponseCode, jMasterSceneID, jTrackingID, &XMasterSceneManagerCallback::CreateMasterSceneWithTrackingReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_MasterSceneManagerCallbackTest_getMasterSceneReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jMasterSceneID, jobject jMasterScene)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_Object<XMasterSceneManagerCallback, XMasterScene, MasterScene>(env, jCallback, jResponseCode, jMasterSceneID, jMasterScene, &XMasterSceneManagerCallback::GetMasterSceneReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_MasterSceneManagerCallbackTest_masterScenesNameChangedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jMasterSceneIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XMasterSceneManagerCallback>(env, jCallback, jMasterSceneIDs, &XMasterSceneManagerCallback::MasterScenesNameChangedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_MasterSceneManagerCallbackTest_masterScenesCreatedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jMasterSceneIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XMasterSceneManagerCallback>(env, jCallback, jMasterSceneIDs, &XMasterSceneManagerCallback::MasterScenesCreatedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_MasterSceneManagerCallbackTest_masterScenesDeletedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jMasterSceneIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XMasterSceneManagerCallback>(env, jCallback, jMasterSceneIDs, &XMasterSceneManagerCallback::MasterScenesDeletedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_MasterSceneManagerCallbackTest_masterScenesUpdatedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jMasterSceneIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XMasterSceneManagerCallback>(env, jCallback, jMasterSceneIDs, &XMasterSceneManagerCallback::MasterScenesUpdatedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_MasterSceneManagerCallbackTest_masterScenesAppliedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jMasterSceneIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XMasterSceneManagerCallback>(env, jCallback, jMasterSceneIDs, &XMasterSceneManagerCallback::MasterScenesAppliedCB, __func__);
}


