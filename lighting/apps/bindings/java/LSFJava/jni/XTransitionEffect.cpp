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

// This .cpp file is #include'd in the .h file because some templated
// methods must be defined there. The following #ifdef allows the
// templated code to be visible there.
#ifdef LSF_JNI_XTRANSITIONEFFECT_H_INCLUDE_TEMPLATE_METHODS

#include <qcc/Debug.h>

#include "NDefs.h"
#include "XTransitionEffect.h"

#define QCC_MODULE LSF_QCC_MODULE

namespace lsf {

template <typename T>
void XTransitionEffect::SetTransitionPeriod(JNIEnv *env, jobject thiz, jlong jTransitionPeriod)
{
    T *xDelegate = GetHandle<T*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    xDelegate->transitionPeriod = (uint32_t)jTransitionPeriod;
}

template <typename T>
jlong XTransitionEffect::GetTransitionPeriod(JNIEnv *env, jobject thiz)
{
    T *xDelegate = GetHandle<T*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return (jint)0;
    }

    return (jlong)xDelegate->transitionPeriod;
}

} /* namespace lsf */

#undef QCC_MODULE

#endif /* LSF_JNI_XTRANSITIONEFFECT_H_INCLUDE_TEMPLATE_METHODS */
