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

#include "NUtil.h"
#include "XObject.h"
#include "XScene.h"
#include "XStateTransitionEffect.h"
#include "XPresetTransitionEffect.h"
#include "XStatePulseEffect.h"
#include "XPresetPulseEffect.h"

#include "org_allseen_lsf_Scene.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;
using namespace lsf;

JNIEXPORT
void JNICALL Java_org_allseen_lsf_Scene_setStateTransitionEffects(JNIEnv *env, jobject thiz, jobjectArray jEffects)
{
    XScene *xDelegate = GetHandle<XScene*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    XObject::CopyArray<TransitionLampsLampGroupsToState, XStateTransitionEffect>(XClass::xStateTransitionEffect, jEffects, xDelegate->transitionToStateComponent);
}

JNIEXPORT
jobjectArray JNICALL Java_org_allseen_lsf_Scene_getStateTransitionEffects(JNIEnv *env, jobject thiz)
{
    XScene *xDelegate = GetHandle<XScene*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jobjectArray jEffects = XObject::NewArray<TransitionLampsLampGroupsToState, XStateTransitionEffect>(XClass::xStateTransitionEffect, xDelegate->transitionToStateComponent);
    if (env->ExceptionCheck() || !jEffects) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    return jEffects;
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_Scene_setPresetTransitionEffects(JNIEnv *env, jobject thiz, jobjectArray jEffects)
{
    XScene *xDelegate = GetHandle<XScene*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    XObject::CopyArray<TransitionLampsLampGroupsToPreset, XPresetTransitionEffect>(XClass::xPresetTransitionEffect, jEffects, xDelegate->transitionToPresetComponent);
}

JNIEXPORT
jobjectArray JNICALL Java_org_allseen_lsf_Scene_getPresetTransitionEffects(JNIEnv *env, jobject thiz)
{
    XScene *xDelegate = GetHandle<XScene*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jobjectArray jEffects = XObject::NewArray<TransitionLampsLampGroupsToPreset, XPresetTransitionEffect>(XClass::xPresetTransitionEffect, xDelegate->transitionToPresetComponent);
    if (env->ExceptionCheck() || !jEffects) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    return jEffects;
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_Scene_setStatePulseEffects(JNIEnv *env, jobject thiz, jobjectArray jEffects)
{
    XScene *xDelegate = GetHandle<XScene*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    XObject::CopyArray<PulseLampsLampGroupsWithState, XStatePulseEffect>(XClass::xStatePulseEffect, jEffects, xDelegate->pulseWithStateComponent);
}

JNIEXPORT
jobjectArray JNICALL Java_org_allseen_lsf_Scene_getStatePulseEffects(JNIEnv *env, jobject thiz)
{
    XScene *xDelegate = GetHandle<XScene*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jobjectArray jEffects = XObject::NewArray<PulseLampsLampGroupsWithState, XStatePulseEffect>(XClass::xStatePulseEffect, xDelegate->pulseWithStateComponent);
    if (env->ExceptionCheck() || !jEffects) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    return jEffects;
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_Scene_setPresetPulseEffects(JNIEnv *env, jobject thiz, jobjectArray jEffects)
{
    XScene *xDelegate = GetHandle<XScene*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    XObject::CopyArray<PulseLampsLampGroupsWithPreset, XPresetPulseEffect>(XClass::xPresetPulseEffect, jEffects, xDelegate->pulseWithPresetComponent);
}

JNIEXPORT
jobjectArray JNICALL Java_org_allseen_lsf_Scene_getPresetPulseEffects(JNIEnv *env, jobject thiz)
{
    XScene *xDelegate = GetHandle<XScene*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jobjectArray jEffects = XObject::NewArray<PulseLampsLampGroupsWithPreset, XPresetPulseEffect>(XClass::xPresetPulseEffect, xDelegate->pulseWithPresetComponent);
    if (env->ExceptionCheck() || !jEffects) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    return jEffects;
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_Scene_toString(JNIEnv *env, jobject thiz)
{
    return XObject::ToString<XScene>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_Scene_createNativeObject(JNIEnv *env, jobject thiz)
{
    CreateHandle<XScene>(thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_Scene_destroyNativeObject(JNIEnv *env, jobject thiz)
{
    DestroyHandle<XScene>(thiz);
}

