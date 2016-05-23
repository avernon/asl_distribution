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
#include "XPulseEffectV2.h"
#include "XPulseEffectManager.h"
#include "XPulseEffectManagerCallback.h"

#include "org_allseen_lsf_PulseEffectManager.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;
using namespace lsf;

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_PulseEffectManager_getAllPulseEffectIDs(JNIEnv *env, jobject thiz)
{
    return XCppDelegator::Call_ControllerClientStatus<XPulseEffectManager>(env, thiz, &XPulseEffectManager::GetAllPulseEffectIDs);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_PulseEffectManager_getPulseEffect(JNIEnv *env, jobject thiz, jstring jPulseEffectID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<XPulseEffectManager>(env, thiz, jPulseEffectID, &XPulseEffectManager::GetPulseEffect);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_PulseEffectManager_applyPulseEffectOnLamps(JNIEnv *env, jobject thiz, jstring jPulseEffectID, jobjectArray jLampIDs)
{
    return XCppDelegator::Call_ControllerClientStatus_String_StringList<XPulseEffectManager>(env, thiz, jPulseEffectID, jLampIDs, &XPulseEffectManager::ApplyPulseEffectOnLamps);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_PulseEffectManager_applyPulseEffectOnLampGroups(JNIEnv *env, jobject thiz, jstring jPulseEffectID, jobjectArray jGroupIDs)
{
    return XCppDelegator::Call_ControllerClientStatus_String_StringList<XPulseEffectManager>(env, thiz, jPulseEffectID, jGroupIDs, &XPulseEffectManager::ApplyPulseEffectOnLampGroups);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_PulseEffectManager_getPulseEffectName(JNIEnv *env, jobject thiz, jstring jPulseEffectID, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String<XPulseEffectManager>(env, thiz, jPulseEffectID, jLanguage, &XPulseEffectManager::GetPulseEffectName);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_PulseEffectManager_setPulseEffectName(JNIEnv *env, jobject thiz, jstring jPulseEffectID, jstring jPulseEffectName, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String_String<XPulseEffectManager>(env, thiz, jPulseEffectID, jPulseEffectName, jLanguage, &XPulseEffectManager::SetPulseEffectName);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_PulseEffectManager_createPulseEffect(JNIEnv *env, jobject thiz, jobject jTrackingID, jobject jPulseEffect, jstring jPulseEffectName, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_TrackingID_Object_String_String<XPulseEffectManager, XPulseEffectV2, PulseEffect>(env, thiz, jTrackingID, jPulseEffect, jPulseEffectName, jLanguage, &XPulseEffectManager::CreatePulseEffect);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_PulseEffectManager_updatePulseEffect(JNIEnv *env, jobject thiz, jstring jPulseEffectID, jobject jPulseEffect)
{
    return XCppDelegator::Call_ControllerClientStatus_String_Object<XPulseEffectManager, XPulseEffectV2, PulseEffect>(env, thiz, jPulseEffectID, jPulseEffect, &XPulseEffectManager::UpdatePulseEffect);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_PulseEffectManager_deletePulseEffect(JNIEnv *env, jobject thiz, jstring jPulseEffectID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<XPulseEffectManager>(env, thiz, jPulseEffectID, &XPulseEffectManager::DeletePulseEffect);
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_PulseEffectManager_getPulseEffectDataSet(JNIEnv *env, jobject thiz, jstring jPulseEffectID, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String<XPulseEffectManager>(env, thiz, jPulseEffectID, jLanguage, &XPulseEffectManager::GetPulseEffectDataSet);
}

JNIEXPORT void JNICALL Java_org_allseen_lsf_PulseEffectManager_createNativeObject(JNIEnv *env, jobject thiz, jobject jControllerClient, jobject jPulseEffectManagerCallback)
{
    JControllerClient *xControllerClient = GetHandle<JControllerClient*>(jControllerClient);
    if (env->ExceptionCheck() || !xControllerClient) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    XPulseEffectManagerCallback *xPulseEffectManagerCallback = GetHandle<XPulseEffectManagerCallback*>(jPulseEffectManagerCallback);
    if (env->ExceptionCheck() || !xPulseEffectManagerCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    XPulseEffectManager* xPulseEffectManager = new XPulseEffectManager(thiz, *xControllerClient, *xPulseEffectManagerCallback);
    if (env->ExceptionCheck() || !xPulseEffectManager) {
        QCC_LogError(ER_FAIL, ("JSavedStateManager() failed"));
        return;
    }

    CreateHandle<XPulseEffectManager>(thiz, xPulseEffectManager);
}

JNIEXPORT void JNICALL Java_org_allseen_lsf_PulseEffectManager_destroyNativeObject(JNIEnv *env, jobject thiz)
{
    DestroyHandle<XPulseEffectManager>(thiz);
}
