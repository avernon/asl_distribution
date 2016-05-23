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
#include "XMasterScene.h"
#include "XMasterSceneManager.h"
#include "XMasterSceneManagerCallback.h"

#include "org_allseen_lsf_MasterSceneManager.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;
using namespace lsf;

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_MasterSceneManager_getAllMasterSceneIDs(JNIEnv *env, jobject thiz)
{
    return XCppDelegator::Call_ControllerClientStatus<XMasterSceneManager>(env, thiz, &XMasterSceneManager::GetAllMasterSceneIDs);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_MasterSceneManager_getMasterSceneName(JNIEnv *env, jobject thiz, jstring jMasterSceneID, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String<XMasterSceneManager>(env, thiz, jMasterSceneID, jLanguage, &XMasterSceneManager::GetMasterSceneName);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_MasterSceneManager_setMasterSceneName(JNIEnv *env, jobject thiz, jstring jMasterSceneID, jstring jMasterSceneName, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String_String<XMasterSceneManager>(env, thiz, jMasterSceneID, jMasterSceneName, jLanguage, &XMasterSceneManager::SetMasterSceneName);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_MasterSceneManager_createMasterScene(JNIEnv *env, jobject thiz, jobject jMasterScene, jstring jMasterSceneName, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_Object_String_String<XMasterSceneManager, XMasterScene, MasterScene>(env, thiz, jMasterScene, jMasterSceneName, jLanguage, &XMasterSceneManager::CreateMasterScene);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_MasterSceneManager_updateMasterScene(JNIEnv *env, jobject thiz, jstring jMasterSceneID, jobject jMasterScene)
{
    return XCppDelegator::Call_ControllerClientStatus_String_Object<XMasterSceneManager, XMasterScene, MasterScene>(env, thiz, jMasterSceneID, jMasterScene, &XMasterSceneManager::UpdateMasterScene);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_MasterSceneManager_getMasterScene(JNIEnv *env, jobject thiz, jstring jMasterSceneID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<XMasterSceneManager>(env, thiz, jMasterSceneID, &XMasterSceneManager::GetMasterScene);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_MasterSceneManager_deleteMasterScene(JNIEnv *env, jobject thiz, jstring jMasterSceneID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<XMasterSceneManager>(env, thiz, jMasterSceneID, &XMasterSceneManager::DeleteMasterScene);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_MasterSceneManager_applyMasterScene(JNIEnv *env, jobject thiz, jstring jMasterSceneID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<XMasterSceneManager>(env, thiz, jMasterSceneID, &XMasterSceneManager::ApplyMasterScene);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_MasterSceneManager_createMasterSceneWithTracking(JNIEnv *env, jobject thiz, jobject jTrackingID, jobject jMasterScene, jstring jMasterSceneName, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_TrackingID_Object_String_String<XMasterSceneManager, XMasterScene, MasterScene>(env, thiz, jTrackingID, jMasterScene, jMasterSceneName, jLanguage, &XMasterSceneManager::CreateMasterSceneWithTracking);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_MasterSceneManager_getMasterSceneDataSet(JNIEnv *env, jobject thiz, jstring jMasterSceneID, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String<XMasterSceneManager>(env, thiz, jMasterSceneID, jLanguage, &XMasterSceneManager::GetMasterSceneDataSet);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_MasterSceneManager_createNativeObject(JNIEnv *env, jobject thiz, jobject jController, jobject jCallback)
{
    JControllerClient *xController = GetHandle<JControllerClient*>(jController);
    if (!xController) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    XMasterSceneManagerCallback *xCallback = GetHandle<XMasterSceneManagerCallback*>(jCallback);
    if (!xCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    XMasterSceneManager* xmsm = new XMasterSceneManager(thiz, *xController, *xCallback);
    if (!xmsm) {
        QCC_LogError(ER_FAIL, ("JSceneManager() failed"));
        return;
    }

    CreateHandle<XMasterSceneManager>(thiz, xmsm);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_MasterSceneManager_destroyNativeObject(JNIEnv *env, jobject thiz)
{
    DestroyHandle<XMasterSceneManager>(thiz);
}
