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

#include <stddef.h>

#include <qcc/Debug.h>

#include "JControllerClientCallback.h"
#include "JEnumArray.h"
#include "JLampState.h"

#include "org_allseen_lsf_test_ControllerClientCallbackTest.h"

#define QCC_MODULE LSF_QCC_MODULE

using namespace ajn;
using namespace lsf;

jstring CallMethodVoidStringString(JNIEnv *env, jobject jcc, jstring jdid, jstring jname, void (JControllerClientCallback::*method)(const LSFString&, const LSFString&), char const *func)
{
    JControllerClientCallback* cobj = GetHandle<JControllerClientCallback*>(jcc);
    if (!cobj) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    JString xdid(jdid);
    if (env->ExceptionCheck() || !xdid.c_str()) {
        QCC_LogError(ER_FAIL, ("JString() failed"));
        return NULL;
    }

    JString xname(jname);
    if (env->ExceptionCheck() || !xname.c_str()) {
        QCC_LogError(ER_FAIL, ("JString() failed"));
        return NULL;
    }

    LSFString cdid = xdid.c_str();
    LSFString cname = xname.c_str();

    (cobj->*method)(cdid, cname);
    if (env->ExceptionCheck()) {
        return NULL;
    }

    jstring jfunc = env->NewStringUTF(GetJavaNativeMethodNameFromFunc(func).c_str());
    if (env->ExceptionCheck() || !jfunc) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jfunc;
}

jstring CallMethodVoidErrorCodeArr(JNIEnv *env, jobject jcc, jobjectArray jecl, void (JControllerClientCallback::*method)(const ErrorCodeList& errorCodeList), char const *func)
{
    JControllerClientCallback* cobj = GetHandle<JControllerClientCallback*>(jcc);
    if (!cobj) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    ErrorCodeList cecl;
    JEnumArray::CopyEnumArray(jecl, *JEnum::jErrorCodeEnum, cecl);

    (cobj->*method)(cecl);
    if (env->ExceptionCheck()) {
        return NULL;
    }

    jstring jfunc = env->NewStringUTF(GetJavaNativeMethodNameFromFunc(func).c_str());
    if (env->ExceptionCheck() || !jfunc) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jfunc;
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_ControllerClientCallbackTest_connectedToControllerServiceCB(JNIEnv *env, jobject thiz, jobject jcc, jstring jdid, jstring jname)
{
    return CallMethodVoidStringString(env, jcc, jdid, jname, &JControllerClientCallback::ConnectedToControllerServiceCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_ControllerClientCallbackTest_connectToControllerServiceFailedCB(JNIEnv *env, jobject thiz, jobject jcc, jstring jdid, jstring jname)
{
    return CallMethodVoidStringString(env, jcc, jdid, jname, &JControllerClientCallback::ConnectToControllerServiceFailedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_ControllerClientCallbackTest_disconnectedFromControllerServiceCB(JNIEnv *env, jobject thiz, jobject jcc, jstring jdid, jstring jname)
{
    return CallMethodVoidStringString(env, jcc, jdid, jname, &JControllerClientCallback::DisconnectedFromControllerServiceCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_ControllerClientCallbackTest_controllerClientErrorCB(JNIEnv *env, jobject thiz, jobject jcc, jobjectArray jecl)
{
    return CallMethodVoidErrorCodeArr(env, jcc, jecl, &JControllerClientCallback::ControllerClientErrorCB, __func__);
}

#undef QCC_MODULE
