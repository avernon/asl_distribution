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

#include "XJavaDelegator.h"
#include "XControllerServiceManagerCallback.h"

#define QCC_MODULE "AJN-LSF-JNI"

namespace lsf {

XControllerServiceManagerCallback::XControllerServiceManagerCallback(jobject jobj)
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

XControllerServiceManagerCallback::~XControllerServiceManagerCallback()
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    env->DeleteWeakGlobalRef(jdelegate);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("DeleteWeakGlobalRef() failed"));
        return;
    }
}

void XControllerServiceManagerCallback::GetControllerServiceVersionReplyCB(const uint32_t& version)
{
    XJavaDelegator::Call_Void_UInt32(jdelegate, __func__, version);
}

void XControllerServiceManagerCallback::LightingResetControllerServiceReplyCB(const LSFResponseCode& responseCode)
{
    XJavaDelegator::Call_Void_ResponseCode(jdelegate, __func__, responseCode);
}

void XControllerServiceManagerCallback::ControllerServiceLightingResetCB(void)
{
    XJavaDelegator::Call_Void(jdelegate, __func__);
}

void XControllerServiceManagerCallback::ControllerServiceNameChangedCB(const LSFString& controllerServiceDeviceID, const LSFString& controllerServiceName)
{
    XJavaDelegator::Call_Void_String_String(jdelegate, __func__, controllerServiceDeviceID, controllerServiceName);
}

} /* namespace lsf */
