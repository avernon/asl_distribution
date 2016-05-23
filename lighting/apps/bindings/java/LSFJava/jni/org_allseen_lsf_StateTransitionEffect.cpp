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
#include "XStateTransitionEffect.h"
#include "XTransitionEffect.h"

#include "org_allseen_lsf_StateTransitionEffect.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;
using namespace lsf;

JNIEXPORT
void JNICALL Java_org_allseen_lsf_StateTransitionEffect_setLamps(JNIEnv *env, jobject thiz, jobjectArray jLampIDs)
{
    XLampMemberList::SetLamps<XStateTransitionEffect>(env, thiz, jLampIDs);
}

JNIEXPORT
jobjectArray JNICALL Java_org_allseen_lsf_StateTransitionEffect_getLamps(JNIEnv *env, jobject thiz)
{
    return XLampMemberList::GetLamps<XStateTransitionEffect>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_StateTransitionEffect_setLampGroups(JNIEnv *env, jobject thiz, jobjectArray jLampGroupIDs)
{
    XLampMemberList::SetLampGroups<XStateTransitionEffect>(env, thiz, jLampGroupIDs);
}

JNIEXPORT
jobjectArray JNICALL Java_org_allseen_lsf_StateTransitionEffect_getLampGroups(JNIEnv *env, jobject thiz)
{
    return XLampMemberList::GetLampGroups<XStateTransitionEffect>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_StateTransitionEffect_setTransitionPeriod(JNIEnv *env, jobject thiz, jlong jTransitionPeriod)
{
    XTransitionEffect::SetTransitionPeriod<XStateTransitionEffect>(env, thiz, jTransitionPeriod);
}

JNIEXPORT
jlong JNICALL Java_org_allseen_lsf_StateTransitionEffect_getTransitionPeriod(JNIEnv *env, jobject thiz)
{
    return XTransitionEffect::GetTransitionPeriod<XStateTransitionEffect>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_StateTransitionEffect_setLampState(JNIEnv *env, jobject thiz, jobject jLampState)
{
    XStateTransitionEffect *xStateTransitionEffect = GetHandle<XStateTransitionEffect*>(thiz);
    if (env->ExceptionCheck() || !xStateTransitionEffect) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    JLampState::CopyLampState(jLampState, xStateTransitionEffect->state);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_StateTransitionEffect_getLampState(JNIEnv *env, jobject thiz)
{
    XStateTransitionEffect *xStateTransitionEffect = GetHandle<XStateTransitionEffect*>(thiz);
    if (env->ExceptionCheck() || !xStateTransitionEffect) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    return JLampState::NewLampState(xStateTransitionEffect->state);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_StateTransitionEffect_toString(JNIEnv *env, jobject thiz)
{
    return XObject::ToString<XStateTransitionEffect>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_StateTransitionEffect_createNativeObject(JNIEnv *env, jobject thiz)
{
    CreateHandle<XStateTransitionEffect>(thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_StateTransitionEffect_destroyNativeObject(JNIEnv *env, jobject thiz)
{
    DestroyHandle<XStateTransitionEffect>(thiz);
}
