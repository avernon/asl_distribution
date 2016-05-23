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
#include "XSceneElement.h"
#include "XLampMemberList.h"
#include "XObject.h"

#include "org_allseen_lsf_SceneElement.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;
using namespace lsf;

JNIEXPORT
void JNICALL Java_org_allseen_lsf_SceneElement_setLamps(JNIEnv *env, jobject thiz, jobjectArray jLampIDs)
{
    XLampMemberList::SetLamps<XSceneElement>(env, thiz, jLampIDs);
}

JNIEXPORT
jobjectArray JNICALL Java_org_allseen_lsf_SceneElement_getLamps(JNIEnv *env, jobject thiz)
{
    return XLampMemberList::GetLamps<XSceneElement>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_SceneElement_setLampGroups(JNIEnv *env, jobject thiz, jobjectArray jLampGroupIDs)
{
    XLampMemberList::SetLampGroups<XSceneElement>(env, thiz, jLampGroupIDs);
}

JNIEXPORT
jobjectArray JNICALL Java_org_allseen_lsf_SceneElement_getLampGroups(JNIEnv *env, jobject thiz)
{
    return XLampMemberList::GetLampGroups<XSceneElement>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_SceneElement_setEffectID(JNIEnv *env, jobject thiz, jstring jEffectID)
{
    XSceneElement *xSceneElement = GetHandle<XSceneElement*>(thiz);
    if (env->ExceptionCheck() || !xSceneElement) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    JString xEffectID(jEffectID);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return;
    }

    if (!xEffectID.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return;
    }

    xSceneElement->effectID = xEffectID.c_str();
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_SceneElement_getEffectID(JNIEnv *env, jobject thiz)
{
    XSceneElement *xSceneElement = GetHandle<XSceneElement*>(thiz);
    if (env->ExceptionCheck() || !xSceneElement) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jstring jEffectID = env->NewStringUTF(xSceneElement->effectID.c_str());
    if (env->ExceptionCheck() || !jEffectID) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jEffectID;
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_SceneElement_toString(JNIEnv *env, jobject thiz)
{
    return XObject::ToString<XSceneElement>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_SceneElement_createNativeObject(JNIEnv *env, jobject thiz)
{
    CreateHandle<XSceneElement>(thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_SceneElement_destroyNativeObject(JNIEnv *env, jobject thiz)
{
    DestroyHandle<XSceneElement>(thiz);
}
