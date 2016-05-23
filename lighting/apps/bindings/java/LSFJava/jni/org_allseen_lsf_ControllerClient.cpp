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

#include <string.h>
#include <jni.h>

#include <qcc/Debug.h>

#include "JControllerClientCallback.h"
#include "JControllerClient.h"
#include "JEnum.h"
#include "NUtil.h"

#include "org_allseen_lsf_ControllerClient.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;
using namespace lsf;

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_ControllerClient_start(JNIEnv*env, jobject thiz)
{
    JControllerClient *xController = GetHandle<JControllerClient*>(thiz);
    if (env->ExceptionCheck() || !xController) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    return JEnum::jControllerClientStatusEnum->getObject((int)xController->Start());
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_ControllerClient_stop(JNIEnv*env, jobject thiz)
{
    JControllerClient *xController = GetHandle<JControllerClient*>(thiz);
    if (env->ExceptionCheck() || !xController) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    return JEnum::jControllerClientStatusEnum->getObject((int)xController->Stop());
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_ControllerClient_createNativeObject(JNIEnv *env, jobject thiz, jobject jbus, jobject jcallback)
{
    BusAttachment *xbus = GetHandle<BusAttachment*>(jbus, "handle");
    if (!xbus) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    JControllerClientCallback *xcallback = GetHandle<JControllerClientCallback*>(jcallback);
    if (!xcallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    JControllerClient *xcontroller = new JControllerClient(thiz, *xbus, *xcallback);
    if (!xcontroller) {
        QCC_LogError(ER_FAIL, ("JLampManager() failed"));
        return;
    }

    CreateHandle<JControllerClient>(thiz, xcontroller);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_ControllerClient_destroyNativeObject(JNIEnv*env, jobject thiz)
{
    DestroyHandle<JControllerClient>(thiz);
}

#undef QCC_MODULE
