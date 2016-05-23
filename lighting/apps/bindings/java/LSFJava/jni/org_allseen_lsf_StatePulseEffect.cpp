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

#include "JLampState.h"
#include "NUtil.h"
#include "XLampMemberList.h"
#include "XObject.h"
#include "XPulseEffect.h"
#include "XStatePulseEffect.h"

#include "org_allseen_lsf_StatePulseEffect.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace lsf;

JNIEXPORT
void JNICALL Java_org_allseen_lsf_StatePulseEffect_setLamps(JNIEnv *env, jobject thiz, jobjectArray jLampIDs)
{
    XLampMemberList::SetLamps<XStatePulseEffect>(env, thiz, jLampIDs);
}

JNIEXPORT
jobjectArray JNICALL Java_org_allseen_lsf_StatePulseEffect_getLamps(JNIEnv *env, jobject thiz)
{
    return XLampMemberList::GetLamps<XStatePulseEffect>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_StatePulseEffect_setLampGroups(JNIEnv *env, jobject thiz, jobjectArray jLampGroupIDs)
{
    XLampMemberList::SetLampGroups<XStatePulseEffect>(env, thiz, jLampGroupIDs);
}

JNIEXPORT
jobjectArray JNICALL Java_org_allseen_lsf_StatePulseEffect_getLampGroups(JNIEnv *env, jobject thiz)
{
    return XLampMemberList::GetLampGroups<XStatePulseEffect>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_StatePulseEffect_setPulsePeriod(JNIEnv *env, jobject thiz, jlong jPulsePeriod)
{
    XPulseEffect::SetPulsePeriod<XStatePulseEffect>(env, thiz, jPulsePeriod);
}

JNIEXPORT
jlong JNICALL Java_org_allseen_lsf_StatePulseEffect_getPulsePeriod(JNIEnv *env, jobject thiz)
{
    return XPulseEffect::GetPulsePeriod<XStatePulseEffect>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_StatePulseEffect_setPulseDuration(JNIEnv *env, jobject thiz, jlong jPulseDuration)
{
    XPulseEffect::SetPulseDuration<XStatePulseEffect>(env, thiz, jPulseDuration);
}

JNIEXPORT
jlong JNICALL Java_org_allseen_lsf_StatePulseEffect_getPulseDuration(JNIEnv *env, jobject thiz)
{
    return XPulseEffect::GetPulseDuration<XStatePulseEffect>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_StatePulseEffect_setPulseCount(JNIEnv *env, jobject thiz, jlong jPulseCount)
{
    XPulseEffect::SetPulseCount<XStatePulseEffect>(env, thiz, jPulseCount);
}

JNIEXPORT
jlong JNICALL Java_org_allseen_lsf_StatePulseEffect_getPulseCount(JNIEnv *env, jobject thiz)
{
    return XPulseEffect::GetPulseCount<XStatePulseEffect>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_StatePulseEffect_setFromLampState(JNIEnv *env, jobject thiz, jobject jLampState)
{
    XStatePulseEffect *xStatePulseEffect = GetHandle<XStatePulseEffect*>(thiz);
    if (env->ExceptionCheck() || !xStatePulseEffect) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    JLampState::CopyLampState(jLampState, xStatePulseEffect->fromState);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_StatePulseEffect_getFromLampState(JNIEnv *env, jobject thiz)
{
    XStatePulseEffect *xStatePulseEffect = GetHandle<XStatePulseEffect*>(thiz);
    if (env->ExceptionCheck() || !xStatePulseEffect) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    return JLampState::NewLampState(xStatePulseEffect->fromState);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_StatePulseEffect_setToLampState(JNIEnv *env, jobject thiz, jobject jLampState)
{
    XStatePulseEffect *xStatePulseEffect = GetHandle<XStatePulseEffect*>(thiz);
    if (env->ExceptionCheck() || !xStatePulseEffect) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    JLampState::CopyLampState(jLampState, xStatePulseEffect->toState);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_StatePulseEffect_getToLampState(JNIEnv *env, jobject thiz)
{
    XStatePulseEffect *xStatePulseEffect = GetHandle<XStatePulseEffect*>(thiz);
    if (env->ExceptionCheck() || !xStatePulseEffect) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    return JLampState::NewLampState(xStatePulseEffect->toState);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_StatePulseEffect_toString(JNIEnv *env, jobject thiz)
{
    return XObject::ToString<XStatePulseEffect>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_StatePulseEffect_createNativeObject(JNIEnv *env, jobject thiz)
{
    CreateHandle<XStatePulseEffect>(thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_StatePulseEffect_destroyNativeObject(JNIEnv *env, jobject thiz)
{
    DestroyHandle<XStatePulseEffect>(thiz);
}

