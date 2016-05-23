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

#include "JControllerClient.h"
#include "JEnum.h"
#include "NUtil.h"
#include "XCppDelegator.h"
#include "XScene.h"
#include "XSceneWithSceneElements.h"
#include "XSceneManager.h"
#include "XSceneManagerCallback.h"

#include "org_allseen_lsf_SceneManager.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;
using namespace lsf;

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_SceneManager_getAllSceneIDs(JNIEnv *env, jobject thiz)
{
    return XCppDelegator::Call_ControllerClientStatus<XSceneManager>(env, thiz, &XSceneManager::GetAllSceneIDs);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_SceneManager_getSceneName(JNIEnv *env, jobject thiz, jstring jSceneID, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String<XSceneManager>(env, thiz, jSceneID, jLanguage, &XSceneManager::GetSceneName);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_SceneManager_setSceneName(JNIEnv *env, jobject thiz, jstring jSceneID, jstring jSceneName, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String_String<XSceneManager>(env, thiz, jSceneID, jSceneName, jLanguage, &XSceneManager::SetSceneName);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_SceneManager_createScene(JNIEnv *env, jobject thiz, jobject jScene, jstring jSceneName, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_Object_String_String<XSceneManager, XScene, Scene>(env, thiz, jScene, jSceneName, jLanguage, &XSceneManager::CreateScene);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_SceneManager_updateScene(JNIEnv *env, jobject thiz, jstring jSceneID, jobject jScene)
{
    return XCppDelegator::Call_ControllerClientStatus_String_Object<XSceneManager, XScene, Scene>(env, thiz, jSceneID, jScene, &XSceneManager::UpdateScene);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_SceneManager_deleteScene(JNIEnv *env, jobject thiz, jstring jSceneID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<XSceneManager>(env, thiz, jSceneID, &XSceneManager::DeleteScene);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_SceneManager_getScene(JNIEnv *env, jobject thiz, jstring jSceneID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<XSceneManager>(env, thiz, jSceneID, &XSceneManager::GetScene);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_SceneManager_applyScene(JNIEnv *env, jobject thiz, jstring jSceneID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<XSceneManager>(env, thiz, jSceneID, &XSceneManager::ApplyScene);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_SceneManager_createSceneWithTracking(JNIEnv *env, jobject thiz, jobject jTrackingID, jobject jScene, jstring jSceneName, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_TrackingID_Object_String_String<XSceneManager, XScene, Scene>(env, thiz, jTrackingID, jScene, jSceneName, jLanguage, &XSceneManager::CreateSceneWithTracking);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_SceneManager_createSceneWithSceneElements(JNIEnv *env, jobject thiz, jobject jTrackingID, jobject jSceneWithSceneElements, jstring jSceneName, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_TrackingID_Object_String_String<XSceneManager, XSceneWithSceneElements, SceneWithSceneElements>(env, thiz, jTrackingID, jSceneWithSceneElements, jSceneName, jLanguage, &SceneManager::CreateSceneWithSceneElements);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_SceneManager_updateSceneWithSceneElements(JNIEnv *env, jobject thiz, jstring jSceneID, jobject jSceneWithSceneElements)
{
    return XCppDelegator::Call_ControllerClientStatus_String_Object<XSceneManager, XSceneWithSceneElements, SceneWithSceneElements>(env, thiz, jSceneID, jSceneWithSceneElements, &XSceneManager::UpdateSceneWithSceneElements);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_SceneManager_getSceneWithSceneElements(JNIEnv *env, jobject thiz, jstring jSceneID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<XSceneManager>(env, thiz, jSceneID, &XSceneManager::GetSceneWithSceneElements);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_SceneManager_getSceneDataSet(JNIEnv *env, jobject thiz, jstring jSceneID, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String<XSceneManager>(env, thiz, jSceneID, jLanguage, &XSceneManager::GetSceneDataSet);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_SceneManager_getSceneWithSceneElementsDataSet(JNIEnv *env, jobject thiz, jstring jSceneID, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String<XSceneManager>(env, thiz, jSceneID, jLanguage, &XSceneManager::GetSceneWithSceneElementsDataSet);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_SceneManager_createNativeObject(JNIEnv *env, jobject thiz, jobject jController, jobject jCallback)
{
    JControllerClient *xController = GetHandle<JControllerClient*>(jController);
    if (!xController) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    XSceneManagerCallback *xCallback = GetHandle<XSceneManagerCallback*>(jCallback);
    if (!xCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    XSceneManager* jsm = new XSceneManager(thiz, *xController, *xCallback);
    if (!jsm) {
        QCC_LogError(ER_FAIL, ("JSceneManager() failed"));
        return;
    }

    CreateHandle<XSceneManager>(thiz, jsm);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_SceneManager_destroyNativeObject(JNIEnv *env, jobject thiz)
{
    DestroyHandle<XSceneManager>(thiz);
}
