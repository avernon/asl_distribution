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

#include "JLampState.h"
#include "NUtil.h"
#include "XTransitionEffectV2.h"
#include "XTransitionEffect.h"

#include "org_allseen_lsf_TransitionEffectV2.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;
using namespace lsf;

JNIEXPORT
void JNICALL Java_org_allseen_lsf_TransitionEffectV2_setLampState(JNIEnv *env, jobject thiz, jobject jLampState)
{
    XTransitionEffectV2 *xTransitionEffectV2 = GetHandle<XTransitionEffectV2*>(thiz);
    if (env->ExceptionCheck() || !xTransitionEffectV2) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    JLampState::CopyLampState(jLampState, xTransitionEffectV2->state);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_TransitionEffectV2_getLampState(JNIEnv *env, jobject thiz)
{
    XTransitionEffectV2 *xTransitionEffectV2 = GetHandle<XTransitionEffectV2*>(thiz);
    if (env->ExceptionCheck() || !xTransitionEffectV2) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    return JLampState::NewLampState(xTransitionEffectV2->state);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_TransitionEffectV2_setPresetID(JNIEnv *env, jobject thiz, jstring jPresetID)
{
    XTransitionEffectV2 *xTransitionEffectV2 = GetHandle<XTransitionEffectV2*>(thiz);
    if (env->ExceptionCheck() || !xTransitionEffectV2) {
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

    xTransitionEffectV2->presetID = xPresetID.c_str();
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_TransitionEffectV2_getPresetID(JNIEnv *env, jobject thiz)
{
    XTransitionEffectV2 *xTransitionEffectV2 = GetHandle<XTransitionEffectV2*>(thiz);
    if (env->ExceptionCheck() || !xTransitionEffectV2) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jstring jPresetID = env->NewStringUTF(xTransitionEffectV2->presetID.c_str());
    if (env->ExceptionCheck() || !jPresetID) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jPresetID;
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_TransitionEffectV2_setTransitionPeriod(JNIEnv *env, jobject thiz, jlong jTransitionPeriod)
{
    XTransitionEffect::SetTransitionPeriod<XTransitionEffectV2>(env, thiz, jTransitionPeriod);
}

JNIEXPORT
jlong JNICALL Java_org_allseen_lsf_TransitionEffectV2_getTransitionPeriod(JNIEnv *env, jobject thiz)
{
    return XTransitionEffect::GetTransitionPeriod<XTransitionEffectV2>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_TransitionEffectV2_createNativeObject(JNIEnv *env, jobject thiz)
{
    CreateHandle<XTransitionEffectV2>(thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_TransitionEffectV2_destroyNativeObject(JNIEnv *env, jobject thiz)
{
    DestroyHandle<XTransitionEffectV2>(thiz);
}

