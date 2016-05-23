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

#include <jni.h>

#include <qcc/Debug.h>

#include "NUtil.h"
#include "XControllerService.h"
#include "XCppDelegator.h"

#include "org_allseen_lsf_ControllerService.h"

#define QCC_MODULE LSF_QCC_MODULE

using namespace lsf;

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT
void JNICALL Java_org_allseen_lsf_ControllerService_start(JNIEnv *env, jobject thiz, jstring jKeyStorePath)
{
    XCppDelegator::Call_Void_String<XControllerService>(env, thiz, jKeyStorePath, &XControllerService::Start);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_ControllerService_stop(JNIEnv *env, jobject thiz)
{
    XCppDelegator::Call_Void<XControllerService>(env, thiz, &XControllerService::Stop);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_ControllerService_lightingReset(JNIEnv *env, jobject thiz)
{
    XCppDelegator::Call_Void<XControllerService>(env, thiz, &XControllerService::LightingReset);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_ControllerService_factoryReset(JNIEnv *env, jobject thiz)
{
    XCppDelegator::Call_Void<XControllerService>(env, thiz, &XControllerService::FactoryReset);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_ControllerService_sendNetworkConnected(JNIEnv *env, jobject thiz)
{
    XCppDelegator::Call_Void<XControllerService>(env, thiz, &XControllerService::SendNetworkConnected);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_ControllerService_sendNetworkDisconnected(JNIEnv *env, jobject thiz)
{
    XCppDelegator::Call_Void<XControllerService>(env, thiz, &XControllerService::SendNetworkDisconnected);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_ControllerService_createNativeObject(JNIEnv* env, jobject thiz)
{
    CreateHandle<XControllerService>(thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_ControllerService_destroyNativeObject(JNIEnv* env, jobject thiz)
{
    DestroyHandle<XControllerService>(thiz);
}

JNIEXPORT jstring JNICALL Java_org_allseen_lsf_ControllerService_getName(JNIEnv* env, jobject thiz)
{
    return XControllerService::getActive()->GetName();
}

JNIEXPORT jboolean JNICALL Java_org_allseen_lsf_ControllerService_isLeader(JNIEnv* env, jobject thiz)
{
    return XControllerService::getActive()->IsLeader();
}

#ifdef __cplusplus
}
#endif

