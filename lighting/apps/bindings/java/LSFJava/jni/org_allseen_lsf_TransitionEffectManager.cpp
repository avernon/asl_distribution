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
#include "XTransitionEffectV2.h"
#include "XTransitionEffectManager.h"
#include "XTransitionEffectManagerCallback.h"

#include "org_allseen_lsf_TransitionEffectManager.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;
using namespace lsf;

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_TransitionEffectManager_getAllTransitionEffectIDs(JNIEnv *env, jobject thiz)
{
    return XCppDelegator::Call_ControllerClientStatus<XTransitionEffectManager>(env, thiz, &XTransitionEffectManager::GetAllTransitionEffectIDs);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_TransitionEffectManager_getTransitionEffect(JNIEnv *env, jobject thiz, jstring jTransitionEffectID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<XTransitionEffectManager>(env, thiz, jTransitionEffectID, &XTransitionEffectManager::GetTransitionEffect);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_TransitionEffectManager_applyTransitionEffectOnLamps(JNIEnv *env, jobject thiz, jstring jTransitionEffectID, jobjectArray jLampIDs)
{
    return XCppDelegator::Call_ControllerClientStatus_String_StringList<XTransitionEffectManager>(env, thiz, jTransitionEffectID, jLampIDs, &XTransitionEffectManager::ApplyTransitionEffectOnLamps);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_TransitionEffectManager_applyTransitionEffectOnLampGroups(JNIEnv *env, jobject thiz, jstring jTransitionEffectID, jobjectArray jGroupIDs)
{
    return XCppDelegator::Call_ControllerClientStatus_String_StringList<XTransitionEffectManager>(env, thiz, jTransitionEffectID, jGroupIDs, &XTransitionEffectManager::ApplyTransitionEffectOnLampGroups);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_TransitionEffectManager_getTransitionEffectName(JNIEnv *env, jobject thiz, jstring jTransitionEffectID, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String<XTransitionEffectManager>(env, thiz, jTransitionEffectID, jLanguage, &XTransitionEffectManager::GetTransitionEffectName);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_TransitionEffectManager_setTransitionEffectName(JNIEnv *env, jobject thiz, jstring jTransitionEffectID, jstring jTransitionEffectName, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String_String<XTransitionEffectManager>(env, thiz, jTransitionEffectID, jTransitionEffectName, jLanguage, &XTransitionEffectManager::SetTransitionEffectName);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_TransitionEffectManager_createTransitionEffect(JNIEnv *env, jobject thiz, jobject jTrackingID, jobject jTransitionEffect, jstring jTransitionEffectName, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_TrackingID_Object_String_String<XTransitionEffectManager, XTransitionEffectV2, TransitionEffect>(env, thiz, jTrackingID, jTransitionEffect, jTransitionEffectName, jLanguage, &XTransitionEffectManager::CreateTransitionEffect);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_TransitionEffectManager_updateTransitionEffect(JNIEnv *env, jobject thiz, jstring jTransitionEffectID, jobject jTransitionEffect)
{
    return XCppDelegator::Call_ControllerClientStatus_String_Object<XTransitionEffectManager, XTransitionEffectV2, TransitionEffect>(env, thiz, jTransitionEffectID, jTransitionEffect, &XTransitionEffectManager::UpdateTransitionEffect);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_TransitionEffectManager_deleteTransitionEffect(JNIEnv *env, jobject thiz, jstring jTransitionEffectID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<XTransitionEffectManager>(env, thiz, jTransitionEffectID, &XTransitionEffectManager::DeleteTransitionEffect);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_TransitionEffectManager_getTransitionEffectDataSet(JNIEnv *env, jobject thiz, jstring jTransitionEffectID, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String<XTransitionEffectManager>(env, thiz, jTransitionEffectID, jLanguage, &XTransitionEffectManager::GetTransitionEffectDataSet);
}

JNIEXPORT void JNICALL Java_org_allseen_lsf_TransitionEffectManager_createNativeObject(JNIEnv *env, jobject thiz, jobject jControllerClient, jobject jTransitionEffectManagerCallback)
{
    JControllerClient *xControllerClient = GetHandle<JControllerClient*>(jControllerClient);
    if (env->ExceptionCheck() || !xControllerClient) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    XTransitionEffectManagerCallback *xTransitionEffectManagerCallback = GetHandle<XTransitionEffectManagerCallback*>(jTransitionEffectManagerCallback);
    if (env->ExceptionCheck() || !xTransitionEffectManagerCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    XTransitionEffectManager* xTransitionEffectManager = new XTransitionEffectManager(thiz, *xControllerClient, *xTransitionEffectManagerCallback);
    if (env->ExceptionCheck() || !xTransitionEffectManager) {
        QCC_LogError(ER_FAIL, ("JSavedStateManager() failed"));
        return;
    }

    CreateHandle<XTransitionEffectManager>(thiz, xTransitionEffectManager);
}

JNIEXPORT void JNICALL Java_org_allseen_lsf_TransitionEffectManager_destroyNativeObject(JNIEnv *env, jobject thiz)
{
    DestroyHandle<XTransitionEffectManager>(thiz);
}
