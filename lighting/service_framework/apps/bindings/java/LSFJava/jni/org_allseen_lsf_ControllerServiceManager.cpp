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

#include "JControllerClient.h"
#include "XCppDelegator.h"
#include "XControllerServiceManager.h"
#include "XControllerServiceManagerCallback.h"

#include "org_allseen_lsf_ControllerServiceManager.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace lsf;

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_ControllerServiceManager_getControllerServiceVersion(JNIEnv *env, jobject thiz)
{
    return XCppDelegator::Call_ControllerClientStatus<XControllerServiceManager>(env, thiz, &XControllerServiceManager::GetControllerServiceVersion);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_ControllerServiceManager_lightingResetControllerService(JNIEnv *env, jobject thiz)
{
    return XCppDelegator::Call_ControllerClientStatus<XControllerServiceManager>(env, thiz, &XControllerServiceManager::LightingResetControllerService);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_ControllerServiceManager_createNativeObject(JNIEnv *env, jobject thiz, jobject jController, jobject jCallback)
{
    JControllerClient *jcc = GetHandle<JControllerClient*>(jController);
    if (!jcc) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    XControllerServiceManagerCallback *xcsmcb = GetHandle<XControllerServiceManagerCallback*>(jCallback);
    if (!xcsmcb) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    XControllerServiceManager* xcsm = new XControllerServiceManager(thiz, *jcc, *xcsmcb);
    if (!xcsm) {
        QCC_LogError(ER_FAIL, ("JLampGroupManager() failed"));
        return;
    }

    CreateHandle<XControllerServiceManager>(thiz, xcsm);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_ControllerServiceManager_destroyNativeObject(JNIEnv *env, jobject thiz)
{
    DestroyHandle<XControllerServiceManager>(thiz);
}

#ifdef __cplusplus
}
#endif

