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
#include "JLampState.h"
#include "NUtil.h"
#include "XCppDelegator.h"
#include "XPresetManager.h"
#include "XPresetManagerCallback.h"

#include "org_allseen_lsf_PresetManager.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;
using namespace lsf;

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_PresetManager_getAllPresetIDs(JNIEnv *env, jobject thiz)
{
    return XCppDelegator::Call_ControllerClientStatus<XPresetManager>(env, thiz, &XPresetManager::GetAllPresetIDs);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_PresetManager_getPreset(JNIEnv *env, jobject thiz, jstring jPresetID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<XPresetManager>(env, thiz, jPresetID, &XPresetManager::GetPreset);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_PresetManager_getPresetName(JNIEnv *env, jobject thiz, jstring jPresetID, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String<XPresetManager>(env, thiz, jPresetID, jLanguage, &XPresetManager::GetPresetName);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_PresetManager_setPresetName(JNIEnv *env, jobject thiz, jstring jPresetID, jstring jPresetName, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String_String<XPresetManager>(env, thiz, jPresetID, jPresetName, jLanguage, &XPresetManager::SetPresetName);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_PresetManager_createPreset(JNIEnv *env, jobject thiz, jobject jPreset, jstring jPresetName, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_Object_String_String<XPresetManager, JLampState, LampState>(env, thiz, jPreset, jPresetName, jLanguage, &XPresetManager::CreatePreset);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_PresetManager_updatePreset(JNIEnv *env, jobject thiz, jstring jPresetID, jobject jPreset)
{
    return XCppDelegator::Call_ControllerClientStatus_String_Object<XPresetManager, JLampState, LampState>(env, thiz, jPresetID, jPreset, &XPresetManager::UpdatePreset);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_PresetManager_deletePreset(JNIEnv *env, jobject thiz, jstring jPresetID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<XPresetManager>(env, thiz, jPresetID, &XPresetManager::DeletePreset);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_PresetManager_getDefaultLampState(JNIEnv *env, jobject thiz)
{
    return XCppDelegator::Call_ControllerClientStatus<XPresetManager>(env, thiz, &XPresetManager::GetDefaultLampState);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_PresetManager_setDefaultLampState(JNIEnv *env, jobject thiz, jobject jDefaultLampState)
{
    return XCppDelegator::Call_ControllerClientStatus_Object<XPresetManager, JLampState, LampState>(env, thiz, jDefaultLampState, &XPresetManager::SetDefaultLampState);
}

JNIEXPORT void JNICALL Java_org_allseen_lsf_PresetManager_createNativeObject(JNIEnv *env, jobject thiz, jobject jControllerClient, jobject jPresetManagerCallback)
{
    JControllerClient *xControllerClient = GetHandle<JControllerClient*>(jControllerClient);
    if (env->ExceptionCheck() || !xControllerClient) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    XPresetManagerCallback *xPresetManagerCallback = GetHandle<XPresetManagerCallback*>(jPresetManagerCallback);
    if (env->ExceptionCheck() || !xPresetManagerCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    XPresetManager* xPresetManager = new XPresetManager(thiz, *xControllerClient, *xPresetManagerCallback);
    if (env->ExceptionCheck() || !xPresetManager) {
        QCC_LogError(ER_FAIL, ("JSavedStateManager() failed"));
        return;
    }

    CreateHandle<XPresetManager>(thiz, xPresetManager);
}

JNIEXPORT void JNICALL Java_org_allseen_lsf_PresetManager_destroyNativeObject(JNIEnv *env, jobject thiz)
{
    DestroyHandle<XPresetManager>(thiz);
}
