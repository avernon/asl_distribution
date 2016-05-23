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

#include "NUtil.h"
#include "JLampState.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;
using namespace lsf;

JLampState::JLampState(jobject jobj)
{
    // Currently nothing to do
}

JLampState::~JLampState()
{
    // Currently nothing to do
}

JLampState& JLampState::operator=(const LampState& other)
{
    LampState::operator=(other);
    return *this;
}

jobject JLampState::NewLampState(LampState& cLampState)
{
    JScopedEnv env;

    jmethodID jconstructor = env->GetMethodID(XClass::xLampState->classRef, "<init>", "()V");
    if (env->ExceptionCheck() || !jconstructor) {
        QCC_LogError(ER_FAIL, ("GetMethodID() failed"));
        return NULL;
    }

    jobject jobjValue = env->NewObject(XClass::xLampState->classRef, jconstructor);
    if (env->ExceptionCheck() || !jobjValue) {
        QCC_LogError(ER_FAIL, ("NewObject() failed"));
        return NULL;
    }

    JLampState *xobjValue = GetHandle<JLampState *>(jobjValue);
    if (env->ExceptionCheck() || !xobjValue) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    *xobjValue = cLampState;

    return jobjValue;
}

void JLampState::CopyLampState(jobject jSrcLampState, LampState& cDstLampState)
{
    JScopedEnv env;

    JLampState *xSrcLampState = GetHandle<JLampState*>(jSrcLampState);
    if (env->ExceptionCheck() || !xSrcLampState) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return;
    }

    cDstLampState = (LampState&)*xSrcLampState;
}

#undef QCC_MODULE

