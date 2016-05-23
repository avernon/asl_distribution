/******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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
#include "XPulseEffectV2.h"
#include "XPulseEffect.h"

#include "org_allseen_lsf_PulseEffectV2.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;
using namespace lsf;

JNIEXPORT
void JNICALL Java_org_allseen_lsf_PulseEffectV2_setToLampState(JNIEnv *env, jobject thiz, jobject jLampState)
{
    XPulseEffectV2 *xPulseEffectV2 = GetHandle<XPulseEffectV2*>(thiz);
    if (env->ExceptionCheck() || !xPulseEffectV2) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    JLampState::CopyLampState(jLampState, xPulseEffectV2->toState);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_PulseEffectV2_getToLampState(JNIEnv *env, jobject thiz)
{
    XPulseEffectV2 *xPulseEffectV2 = GetHandle<XPulseEffectV2*>(thiz);
    if (env->ExceptionCheck() || !xPulseEffectV2) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    return JLampState::NewLampState(xPulseEffectV2->toState);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_PulseEffectV2_setFromLampState(JNIEnv *env, jobject thiz, jobject jLampState)
{
    XPulseEffectV2 *xPulseEffectV2 = GetHandle<XPulseEffectV2*>(thiz);
    if (env->ExceptionCheck() || !xPulseEffectV2) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    JLampState::CopyLampState(jLampState, xPulseEffectV2->fromState);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_PulseEffectV2_getFromLampState(JNIEnv *env, jobject thiz)
{
    XPulseEffectV2 *xPulseEffectV2 = GetHandle<XPulseEffectV2*>(thiz);
    if (env->ExceptionCheck() || !xPulseEffectV2) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    return JLampState::NewLampState(xPulseEffectV2->fromState);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_PulseEffectV2_setToPresetID(JNIEnv *env, jobject thiz, jstring jPresetID)
{
    XPulseEffectV2 *xPulseEffectV2 = GetHandle<XPulseEffectV2*>(thiz);
    if (env->ExceptionCheck() || !xPulseEffectV2) {
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

    xPulseEffectV2->toPreset = xPresetID.c_str();
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_PulseEffectV2_getToPresetID(JNIEnv *env, jobject thiz)
{
    XPulseEffectV2 *xPulseEffectV2 = GetHandle<XPulseEffectV2*>(thiz);
    if (env->ExceptionCheck() || !xPulseEffectV2) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jstring jPresetID = env->NewStringUTF(xPulseEffectV2->toPreset.c_str());
    if (env->ExceptionCheck() || !jPresetID) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jPresetID;
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_PulseEffectV2_setFromPresetID(JNIEnv *env, jobject thiz, jstring jPresetID)
{
    XPulseEffectV2 *xPulseEffectV2 = GetHandle<XPulseEffectV2*>(thiz);
    if (env->ExceptionCheck() || !xPulseEffectV2) {
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

    xPulseEffectV2->fromPreset = xPresetID.c_str();
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_PulseEffectV2_getFromPresetID(JNIEnv *env, jobject thiz)
{
    XPulseEffectV2 *xPulseEffectV2 = GetHandle<XPulseEffectV2*>(thiz);
    if (env->ExceptionCheck() || !xPulseEffectV2) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jstring jPresetID = env->NewStringUTF(xPulseEffectV2->fromPreset.c_str());
    if (env->ExceptionCheck() || !jPresetID) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jPresetID;
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_PulseEffectV2_setPulsePeriod(JNIEnv *env, jobject thiz, jlong jPulsePeriod)
{
    XPulseEffect::SetPulsePeriod<XPulseEffectV2>(env, thiz, jPulsePeriod);
}

JNIEXPORT
jlong JNICALL Java_org_allseen_lsf_PulseEffectV2_getPulsePeriod(JNIEnv *env, jobject thiz)
{
    return XPulseEffect::GetPulsePeriod<XPulseEffectV2>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_PulseEffectV2_setPulseDuration(JNIEnv *env, jobject thiz, jlong jPulseDuration)
{
    XPulseEffect::SetPulseDuration<XPulseEffectV2>(env, thiz, jPulseDuration);
}

JNIEXPORT
jlong JNICALL Java_org_allseen_lsf_PulseEffectV2_getPulseDuration(JNIEnv *env, jobject thiz)
{
    return XPulseEffect::GetPulseDuration<XPulseEffectV2>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_PulseEffectV2_setNumPulses(JNIEnv *env, jobject thiz, jlong jPulseCount)
{
    XPulseEffect::SetPulseCount<XPulseEffectV2>(env, thiz, jPulseCount);
}

JNIEXPORT
jlong JNICALL Java_org_allseen_lsf_PulseEffectV2_getNumPulses(JNIEnv *env, jobject thiz)
{
    return XPulseEffect::GetPulseCount<XPulseEffectV2>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_PulseEffectV2_createNativeObject(JNIEnv *env, jobject thiz)
{
    CreateHandle<XPulseEffectV2>(thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_PulseEffectV2_destroyNativeObject(JNIEnv *env, jobject thiz)
{
    DestroyHandle<XPulseEffectV2>(thiz);
}
