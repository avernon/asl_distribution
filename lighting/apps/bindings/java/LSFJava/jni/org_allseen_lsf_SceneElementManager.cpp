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

#include "JControllerClient.h"
#include "NUtil.h"
#include "XCppDelegator.h"
#include "XSceneElement.h"
#include "XSceneElementManager.h"
#include "XSceneElementManagerCallback.h"

#include "org_allseen_lsf_SceneElementManager.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;
using namespace lsf;

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_SceneElementManager_getAllSceneElementIDs(JNIEnv *env, jobject thiz)
{
    return XCppDelegator::Call_ControllerClientStatus<XSceneElementManager>(env, thiz, &XSceneElementManager::GetAllSceneElementIDs);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_SceneElementManager_getSceneElementName(JNIEnv *env, jobject thiz, jstring jSceneElementID, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String<XSceneElementManager>(env, thiz, jSceneElementID, jLanguage, &XSceneElementManager::GetSceneElementName);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_SceneElementManager_setSceneElementName(JNIEnv *env, jobject thiz, jstring jSceneElementID, jstring jSceneElementName, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String_String<XSceneElementManager>(env, thiz, jSceneElementID, jSceneElementName, jLanguage, &XSceneElementManager::SetSceneElementName);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_SceneElementManager_createSceneElement(JNIEnv *env, jobject thiz, jobject jTrackingID, jobject jSceneElement, jstring jSceneElementName, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_TrackingID_Object_String_String<XSceneElementManager, XSceneElement, SceneElement>(env, thiz, jTrackingID, jSceneElement, jSceneElementName, jLanguage, &XSceneElementManager::CreateSceneElement);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_SceneElementManager_updateSceneElement(JNIEnv *env, jobject thiz, jstring jSceneElementID, jobject jSceneElement)
{
    return XCppDelegator::Call_ControllerClientStatus_String_Object<XSceneElementManager, XSceneElement, SceneElement>(env, thiz, jSceneElementID, jSceneElement, &XSceneElementManager::UpdateSceneElement);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_SceneElementManager_deleteSceneElement(JNIEnv *env, jobject thiz, jstring jSceneElementID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<XSceneElementManager>(env, thiz, jSceneElementID, &XSceneElementManager::DeleteSceneElement);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_SceneElementManager_getSceneElement(JNIEnv *env, jobject thiz, jstring jSceneElementID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<XSceneElementManager>(env, thiz, jSceneElementID, &XSceneElementManager::GetSceneElement);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_SceneElementManager_applySceneElement(JNIEnv *env, jobject thiz, jstring jSceneElementID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<XSceneElementManager>(env, thiz, jSceneElementID, &XSceneElementManager::ApplySceneElement);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_SceneElementManager_getSceneElementDataSet(JNIEnv *env, jobject thiz, jstring jSceneElementID, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String<XSceneElementManager>(env, thiz, jSceneElementID, jLanguage, &XSceneElementManager::GetSceneElementDataSet);
}

JNIEXPORT void JNICALL Java_org_allseen_lsf_SceneElementManager_createNativeObject(JNIEnv *env , jobject thiz, jobject jControllerClient, jobject jSceneElementManagerCallback)
{
    JControllerClient *xControllerClient = GetHandle<JControllerClient*>(jControllerClient);
    if (env->ExceptionCheck() || !xControllerClient) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    XSceneElementManagerCallback *xSceneElementManagerCallback = GetHandle<XSceneElementManagerCallback*>(jSceneElementManagerCallback);
    if (env->ExceptionCheck() || !xSceneElementManagerCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    XSceneElementManager* xSceneElementManager = new XSceneElementManager(thiz, *xControllerClient, *xSceneElementManagerCallback);
    if (env->ExceptionCheck() || !xSceneElementManager) {
        QCC_LogError(ER_FAIL, ("JSavedStateManager() failed"));
        return;
    }

    CreateHandle<XSceneElementManager>(thiz, xSceneElementManager);
}

JNIEXPORT void JNICALL Java_org_allseen_lsf_SceneElementManager_destroyNativeObject(JNIEnv *env, jobject thiz)
{
    DestroyHandle<XSceneElementManager>(thiz);
}
