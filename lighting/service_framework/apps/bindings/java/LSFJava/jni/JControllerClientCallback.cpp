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

#include "JEnumArray.h"
#include "JControllerClientCallback.h"
#include "JLampState.h"
#include "XJavaDelegator.h"

#define QCC_MODULE LSF_QCC_MODULE

using namespace ajn;

namespace lsf {

JControllerClientCallback::JControllerClientCallback(jobject jobj)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    /*
     * Be careful when using a weak global reference.  They can only be
     * passed to NewLocalRef, NewGlobalRef and DeleteWeakGlobalRef.
     */
    QCC_DbgPrintf(("Taking weak global reference to Java object %p", jobj));
    jdelegate = env->NewWeakGlobalRef(jobj);
    if (env->ExceptionCheck() || !jdelegate) {
        QCC_LogError(ER_FAIL, ("NewWeakGlobalRef() failed"));
        return;
    }
}

JControllerClientCallback::~JControllerClientCallback()
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    env->DeleteWeakGlobalRef(jdelegate);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("DeleteWeakGlobalRef() failed"));
        return;
    }
}

void JControllerClientCallback::ConnectedToControllerServiceCB(const LSFString& controllerServiceDeviceID, const LSFString& controllerServiceName)
{
    XJavaDelegator::Call_Void_String_String(jdelegate, __func__, controllerServiceDeviceID, controllerServiceName);
}

void JControllerClientCallback::DisconnectedFromControllerServiceCB(const LSFString& controllerServiceDeviceID, const LSFString& controllerServiceName)
{
    XJavaDelegator::Call_Void_String_String(jdelegate, __func__, controllerServiceDeviceID, controllerServiceName);
}

void JControllerClientCallback::ConnectToControllerServiceFailedCB(const LSFString& controllerServiceDeviceID, const LSFString& controllerServiceName)
{
    XJavaDelegator::Call_Void_String_String(jdelegate, __func__, controllerServiceDeviceID, controllerServiceName);
}

void JControllerClientCallback::ControllerClientErrorCB(const ErrorCodeList& errorCodeList)
{
    //TODO-FIX XJavaDelegator::Call_Void_EnumList(jdelegate, __func__, JEnumArray::NewEnumArray(*JEnum::jErrorCodeEnum, errorCodeList), "org/allseen/lsf/ErrorCode");
}

} /* namespace lsf */

#undef QCC_MODULE
