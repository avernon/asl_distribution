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

#include <stddef.h>

#include <qcc/Debug.h>

#include "XTrackingID.h"
#include "NUtil.h"

#define QCC_MODULE "AJN-LSF-JNI"

namespace lsf {

jobject XTrackingID::NewTrackingID()
{
    JScopedEnv env;

    jmethodID jConstructor = env->GetMethodID(XClass::xTrackingID->classRef, "<init>", "()V");
    if (env->ExceptionCheck() || !jConstructor) {
        QCC_LogError(ER_FAIL, ("GetMethodID() failed"));
        return NULL;
    }

    jobject jTrackingID = env->NewObject(XClass::xTrackingID->classRef, jConstructor);
    if (env->ExceptionCheck() || !jTrackingID) {
        QCC_LogError(ER_FAIL, ("NewObject() failed"));
        return NULL;
    }

    return jTrackingID;
}

jobject XTrackingID::SetTrackingID(jobject jTrackingID, const uint32_t& cTrackingID)
{
    JScopedEnv env;

    jfieldID jFieldID = env->GetFieldID(XClass::xTrackingID->classRef, "value", "J");
    if (env->ExceptionCheck() || !jFieldID) {
        QCC_LogError(ER_FAIL, ("GetFieldID() failed"));
        return NULL;
    }

    env->SetLongField(jTrackingID, jFieldID, (jlong)cTrackingID);

    return jTrackingID;
}

} /* namespace lsf */

#undef QCC_MODULE
