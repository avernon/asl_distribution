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

#include "XSceneElement.h"
#include "XSceneElementManagerCallback.h"
#include "XCppTestDelegator.h"
#include "org_allseen_lsf_test_SceneElementManagerCallbackTest.h"

#define QCC_MODULE "AJN-LSF-JNI-TEST"

using namespace ajn;
using namespace lsf;


JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneElementManagerCallbackTest_getAllSceneElementIDsReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jobjectArray jSceneElementIDs)
{
    return XCppTestDelegator::Call_Void_ResponseCode_StringList<XSceneElementManagerCallback>(env, jCallback, jResponseCode, jSceneElementIDs, &XSceneElementManagerCallback::GetAllSceneElementIDsReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneElementManagerCallbackTest_getSceneElementNameReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jSceneElementID, jstring jLanguage, jstring jSceneElementName)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_String_String<XSceneElementManagerCallback>(env, jCallback, jResponseCode, jSceneElementID, jLanguage, jSceneElementName, &XSceneElementManagerCallback::GetSceneElementNameReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneElementManagerCallbackTest_setSceneElementNameReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jSceneElementID, jstring jLanguage)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_String<XSceneElementManagerCallback>(env, jCallback, jResponseCode, jSceneElementID, jLanguage, &XSceneElementManagerCallback::SetSceneElementNameReplyCB, __func__);
}


JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneElementManagerCallbackTest_getSceneElementReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jSceneElementID, jobject jSceneElement)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_Object<XSceneElementManagerCallback, XSceneElement, SceneElement>(env, jCallback, jResponseCode, jSceneElementID, jSceneElement, &XSceneElementManagerCallback::GetSceneElementReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneElementManagerCallbackTest_updateSceneElementReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jSceneElementID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<XSceneElementManagerCallback>(env, jCallback, jResponseCode, jSceneElementID, &XSceneElementManagerCallback::UpdateSceneElementReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneElementManagerCallbackTest_deleteSceneElementReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jSceneElementID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<XSceneElementManagerCallback>(env, jCallback, jResponseCode, jSceneElementID, &XSceneElementManagerCallback::DeleteSceneElementReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneElementManagerCallbackTest_applySceneElementReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jSceneElementID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<XSceneElementManagerCallback>(env, jCallback, jResponseCode, jSceneElementID, &XSceneElementManagerCallback::ApplySceneElementReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneElementManagerCallbackTest_sceneElementsNameChangedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jSceneElementIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XSceneElementManagerCallback>(env, jCallback, jSceneElementIDs, &XSceneElementManagerCallback::SceneElementsNameChangedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneElementManagerCallbackTest_sceneElementsCreatedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jSceneElementIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XSceneElementManagerCallback>(env, jCallback, jSceneElementIDs, &XSceneElementManagerCallback::SceneElementsCreatedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneElementManagerCallbackTest_sceneElementsUpdatedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jSceneElementIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XSceneElementManagerCallback>(env, jCallback, jSceneElementIDs, &XSceneElementManagerCallback::SceneElementsUpdatedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneElementManagerCallbackTest_sceneElementsDeletedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jSceneElementIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XSceneElementManagerCallback>(env, jCallback, jSceneElementIDs, &XSceneElementManagerCallback::SceneElementsDeletedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneElementManagerCallbackTest_sceneElementsAppliedCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jSceneElementIDs)
{
    return XCppTestDelegator::Call_Void_StringList<XSceneElementManagerCallback>(env, jCallback, jSceneElementIDs, &XSceneElementManagerCallback::SceneElementsAppliedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_SceneElementManagerCallbackTest_createSceneElementReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jSceneElementID, jlong jTrackingID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_UInt32<XSceneElementManagerCallback>(env, jCallback, jResponseCode, jSceneElementID, jTrackingID, &XSceneElementManagerCallback::CreateSceneElementReplyCB, __func__);
}


