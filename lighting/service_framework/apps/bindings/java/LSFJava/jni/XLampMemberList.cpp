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

// This .cpp file is #include'd in the .h file because some templated
// methods must be defined there. The following #ifdef allows the
// templated code to be visible there.
#ifdef LSF_JNI_XLAMPMEMBERLIST_H_INCLUDE_TEMPLATE_METHODS

#include <qcc/Debug.h>

#include "NDefs.h"
#include "NUtil.h"
#include "JStringArray.h"
#include "XLampMemberList.h"

#define QCC_MODULE LSF_QCC_MODULE

namespace lsf {

template <typename T>
void XLampMemberList::SetLamps(JNIEnv *env, jobject thiz, jobjectArray jLampIDs)
{
    T *xDelegate = GetHandle<T*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    JStringArray::CopyStringArray(jLampIDs, xDelegate->lamps);
}

template <typename T>
jobjectArray XLampMemberList::GetLamps(JNIEnv *env, jobject thiz)
{
    T *xDelegate = GetHandle<T*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jobjectArray jLamps = JStringArray::NewStringArray(xDelegate->lamps);
    if (env->ExceptionCheck() || !jLamps) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    return jLamps;
}

template <typename T>
void XLampMemberList::SetLampGroups(JNIEnv *env, jobject thiz, jobjectArray jLampGroupIDs)
{
    T *xDelegate = GetHandle<T*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    JStringArray::CopyStringArray(jLampGroupIDs, xDelegate->lampGroups);
}

template <typename T>
jobjectArray XLampMemberList::GetLampGroups(JNIEnv *env, jobject thiz)
{
    T *xDelegate = GetHandle<T*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jobjectArray jLampGroups = JStringArray::NewStringArray(xDelegate->lampGroups);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    return jLampGroups;
}

} /* namespace lsf */

#undef QCC_MODULE

#endif /* LSF_JNI_XLAMPMEMBERLIST_H_INCLUDE_TEMPLATE_METHODS */
