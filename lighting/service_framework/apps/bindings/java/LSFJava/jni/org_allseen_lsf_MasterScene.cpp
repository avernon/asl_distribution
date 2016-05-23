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
#include <jni.h>

#include <qcc/Debug.h>

#include "JEnum.h"
#include "JStringArray.h"
#include "NUtil.h"
#include "XMasterScene.h"
#include "XObject.h"

#include "org_allseen_lsf_MasterScene.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;
using namespace lsf;

JNIEXPORT
void JNICALL Java_org_allseen_lsf_MasterScene_setScenes(JNIEnv *env, jobject thiz, jobjectArray jSceneIDs)
{
    XMasterScene *xDelegate = GetHandle<XMasterScene*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    JStringArray::CopyStringArray(jSceneIDs, xDelegate->scenes);
}

JNIEXPORT
jobjectArray JNICALL Java_org_allseen_lsf_MasterScene_getScenes(JNIEnv *env, jobject thiz)
{
    XMasterScene *xDelegate = GetHandle<XMasterScene*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jobjectArray jSceneIDs = JStringArray::NewStringArray(xDelegate->scenes);
    if (env->ExceptionCheck() || !jSceneIDs) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    return jSceneIDs;

}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_MasterScene_isDependentOnScene(JNIEnv *env, jobject thiz, jstring jSceneID)
{
    XMasterScene* xDelegate = GetHandle<XMasterScene*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    JString xSceneID(jSceneID);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xSceneID.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    LSFString cSceneID = xSceneID.c_str();

    jobject jResponseCode = JEnum::jResponseCodeEnum->getObject((int)(xDelegate->IsDependentOnScene(cSceneID)));
    if (env->ExceptionCheck() || !jResponseCode) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    return jResponseCode;
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_MasterScene_toString(JNIEnv *env, jobject thiz)
{
    return XObject::ToString<XMasterScene>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_MasterScene_createNativeObject(JNIEnv *env, jobject thiz)
{
    CreateHandle<XMasterScene>(thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_MasterScene_destroyNativeObject(JNIEnv *env, jobject thiz)
{
    DestroyHandle<XMasterScene>(thiz);
}

