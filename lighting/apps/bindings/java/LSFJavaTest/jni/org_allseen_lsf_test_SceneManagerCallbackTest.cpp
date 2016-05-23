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

#include "XScene.h"
#include "XSceneManagerCallback.h"
#include "XCppTestDelegator.h"

#include "JEnum.h"
#include "JEnumArray.h"
#include "XSceneWithSceneElements.h"
#include "JLampState.h"
#include "JStringArray.h"
#include "NTypes.h"
#include "NUtil.h"

#include "XCppTestDelegator.h"

#include "org_allseen_lsf_test_SceneManagerCallbackTest.h"

#define QCC_MODULE "AJN-LSF-JNI-TEST"

using namespace ajn;
using namespace lsf;

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_getAllSceneIDsReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jobjectArray jSceneIDs)
{
    return XCppTestDelegator::Call_Void_ResponseCode_StringList<XSceneManagerCallback>(env, jCallback, jResponseCode, jSceneIDs, &XSceneManagerCallback::GetAllSceneIDsReplyCB, __func__);
}


JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_getSceneNameReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jSceneID, jstring jLanugage, jstring jSceneName)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_String_String<XSceneManagerCallback>(env, jCallback, jResponseCode, jSceneID, jLanugage, jSceneName, &XSceneManagerCallback::GetSceneNameReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_setSceneNameReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jSceneID, jstring jLanugage)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_String<XSceneManagerCallback>(env, jCallback, jResponseCode, jSceneID, jLanugage, &XSceneManagerCallback::SetSceneNameReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_getSceneReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jSceneID, jobject jScene)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_Object<XSceneManagerCallback, XScene, Scene>(env, jCallback, jResponseCode, jSceneID, jScene, &XSceneManagerCallback::GetSceneReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_updateSceneWithSceneElementsReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jSceneID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<XSceneManagerCallback>(env, jCallback, jResponseCode, jSceneID, &XSceneManagerCallback::UpdateSceneWithSceneElementsReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_getSceneWithSceneElementsReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jSceneID, jobject jScene)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_Object<XSceneManagerCallback, XSceneWithSceneElements, SceneWithSceneElements>(env, jCallback, jResponseCode, jSceneID, jScene, &XSceneManagerCallback::GetSceneWithSceneElementsReplyCB, __func__);
}


JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_scenesNameChangedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jSceneIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XSceneManagerCallback>(env, jCallback, jSceneIDs, &XSceneManagerCallback::ScenesNameChangedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_scenesCreatedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jSceneIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XSceneManagerCallback>(env, jCallback, jSceneIDs, &XSceneManagerCallback::ScenesCreatedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_scenesUpdatedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jSceneIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XSceneManagerCallback>(env, jCallback, jSceneIDs, &XSceneManagerCallback::ScenesUpdatedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_scenesDeletedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jSceneIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XSceneManagerCallback>(env, jCallback, jSceneIDs, &XSceneManagerCallback::ScenesDeletedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_scenesAppliedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jSceneIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XSceneManagerCallback>(env, jCallback, jSceneIDs, &XSceneManagerCallback::ScenesAppliedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_createSceneReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jSceneID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<XSceneManagerCallback>(env, jCallback, jResponseCode, jSceneID, &XSceneManagerCallback::CreateSceneReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_updateSceneReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jSceneID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<XSceneManagerCallback>(env, jCallback, jResponseCode, jSceneID, &XSceneManagerCallback::UpdateSceneReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_deleteSceneReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jSceneID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<XSceneManagerCallback>(env, jCallback, jResponseCode, jSceneID, &XSceneManagerCallback::DeleteSceneReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_applySceneReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jSceneID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<XSceneManagerCallback>(env, jCallback, jResponseCode, jSceneID, &XSceneManagerCallback::ApplySceneReplyCB, __func__);
}


JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_createSceneWithTrackingReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jSceneID, jlong jTrackingID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_UInt32<XSceneManagerCallback>(env, jCallback, jResponseCode, jSceneID, jTrackingID, &XSceneManagerCallback::CreateSceneWithTrackingReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_createSceneWithSceneElementsReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jSceneID, jlong jTrackingID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_UInt32<XSceneManagerCallback>(env, jCallback, jResponseCode, jSceneID, jTrackingID, &XSceneManagerCallback::CreateSceneWithSceneElementsReplyCB, __func__);
}



