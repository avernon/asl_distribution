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

#include "XLampMemberList.h"
#include "XObject.h"
#include "XPresetTransitionEffect.h"
#include "XTransitionEffect.h"

#include "org_allseen_lsf_PresetTransitionEffect.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;
using namespace lsf;

JNIEXPORT
void JNICALL Java_org_allseen_lsf_PresetTransitionEffect_setLamps(JNIEnv *env, jobject thiz, jobjectArray jLampIDs)
{
    XLampMemberList::SetLamps<XPresetTransitionEffect>(env, thiz, jLampIDs);
}

JNIEXPORT
jobjectArray JNICALL Java_org_allseen_lsf_PresetTransitionEffect_getLamps(JNIEnv *env, jobject thiz)
{
    return XLampMemberList::GetLamps<XPresetTransitionEffect>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_PresetTransitionEffect_setLampGroups(JNIEnv *env, jobject thiz, jobjectArray jLampGroupIDs)
{
    XLampMemberList::SetLampGroups<XPresetTransitionEffect>(env, thiz, jLampGroupIDs);
}

JNIEXPORT
jobjectArray JNICALL Java_org_allseen_lsf_PresetTransitionEffect_getLampGroups(JNIEnv *env, jobject thiz)
{
    return XLampMemberList::GetLampGroups<XPresetTransitionEffect>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_PresetTransitionEffect_setTransitionPeriod(JNIEnv *env, jobject thiz, jlong jTransitionPeriod)
{
    XTransitionEffect::SetTransitionPeriod<XPresetTransitionEffect>(env, thiz, jTransitionPeriod);
}

JNIEXPORT
jlong JNICALL Java_org_allseen_lsf_PresetTransitionEffect_getTransitionPeriod(JNIEnv *env, jobject thiz)
{
    return XTransitionEffect::GetTransitionPeriod<XPresetTransitionEffect>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_PresetTransitionEffect_setPresetID(JNIEnv *env, jobject thiz, jstring jPresetID)
{
    XPresetTransitionEffect *xPresetTransitionEffect = GetHandle<XPresetTransitionEffect*>(thiz);
    if (env->ExceptionCheck() || !xPresetTransitionEffect) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    JString xPresetID(jPresetID);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return;
    }

    if (!xPresetID.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return;
    }

    xPresetTransitionEffect->presetID = xPresetID.c_str();
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_PresetTransitionEffect_getPresetID(JNIEnv *env, jobject thiz)
{
    XPresetTransitionEffect *xPresetTransitionEffect = GetHandle<XPresetTransitionEffect*>(thiz);
    if (env->ExceptionCheck() || !xPresetTransitionEffect) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jstring jPresetID = env->NewStringUTF(xPresetTransitionEffect->presetID.c_str());
    if (env->ExceptionCheck() || !jPresetID) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jPresetID;
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_PresetTransitionEffect_toString(JNIEnv *env, jobject thiz)
{
    return XObject::ToString<XPresetTransitionEffect>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_PresetTransitionEffect_createNativeObject(JNIEnv *env, jobject thiz)
{
    CreateHandle<XPresetTransitionEffect>(thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_PresetTransitionEffect_destroyNativeObject(JNIEnv *env, jobject thiz)
{
    DestroyHandle<XPresetTransitionEffect>(thiz);
}

