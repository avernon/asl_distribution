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

#include "NUtil.h"
#include "JEnum.h"
#include "JStringArray.h"
#include "XObject.h"
#include "XSceneWithSceneElements.h"

#include "org_allseen_lsf_SceneWithSceneElements.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;
using namespace lsf;

JNIEXPORT
void JNICALL Java_org_allseen_lsf_SceneWithSceneElements_setSceneElements(JNIEnv *env, jobject thiz, jobjectArray jSceneElements)
{
    XSceneWithSceneElements *xSceneWithSceneElements = GetHandle<XSceneWithSceneElements*>(thiz);
    if (env->ExceptionCheck() || !xSceneWithSceneElements) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    JStringArray::CopyStringArray(jSceneElements, xSceneWithSceneElements->sceneElements);
}

JNIEXPORT
jobjectArray JNICALL Java_org_allseen_lsf_SceneWithSceneElements_getSceneElements(JNIEnv *env, jobject thiz)
{
    XSceneWithSceneElements *xSceneWithSceneElements = GetHandle<XSceneWithSceneElements*>(thiz);
    if (env->ExceptionCheck() || !xSceneWithSceneElements) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jobjectArray jSceneElements = JStringArray::NewStringArray(xSceneWithSceneElements->sceneElements);
    if (env->ExceptionCheck() || !jSceneElements) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    return jSceneElements;
}

JNIEXPORT jobject JNICALL Java_org_allseen_lsf_SceneWithSceneElements_isDependentOnSceneElement(JNIEnv *env, jobject thiz, jstring jSceneElementID)
{
    XSceneWithSceneElements* xSceneWithSceneElements = GetHandle<XSceneWithSceneElements*>(thiz);
    if (env->ExceptionCheck() || !xSceneWithSceneElements) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    JString xSceneElementID(jSceneElementID);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xSceneElementID.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    LSFString cSceneElementID = xSceneElementID.c_str();

    jobject jResponseCode = JEnum::jResponseCodeEnum->getObject((int)(xSceneWithSceneElements->IsDependentOnSceneElement(cSceneElementID)));
    if (env->ExceptionCheck() || !jResponseCode) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    return jResponseCode;
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_SceneWithSceneElements_toString(JNIEnv *env, jobject thiz)
{
    return XObject::ToString<XSceneWithSceneElements>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_SceneWithSceneElements_createNativeObject(JNIEnv *env, jobject thiz)
{
    CreateHandle<XSceneWithSceneElements>(thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_SceneWithSceneElements_destroyNativeObject(JNIEnv *env, jobject thiz)
{
    DestroyHandle<XSceneWithSceneElements>(thiz);
}
