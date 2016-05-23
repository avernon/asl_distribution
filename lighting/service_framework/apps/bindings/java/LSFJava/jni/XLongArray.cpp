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

#include "XLongArray.h"
#include "NUtil.h"

#define QCC_MODULE "AJN-LSF-JNI"

namespace lsf {

jlongArray XLongArray::NewLongArray(const std::list<uint32_t>& vals)
{
    JScopedEnv env;
    std::list<uint32_t>::size_type count = vals.size();

    jlongArray jarr = env->NewLongArray(count);
    if (env->ExceptionCheck() || !jarr) {
        QCC_LogError(ER_FAIL, ("NewLongArray() failed"));
        return NULL;
    }

    std::list<uint32_t>::const_iterator it = vals.begin();
    for (int i = 0; i < count; i++, it++) {
        jlong jval = (jlong)(*it);

        env->SetLongArrayRegion(jarr, i, 1, &jval);
        if (env->ExceptionCheck()) {
            QCC_LogError(ER_FAIL, ("SetLongArrayRegion() failed"));
            return NULL;
        }
    }

    return jarr;
}

void XLongArray::CopyLongArray(jlongArray jarr, std::list<uint32_t>& vals)
{
    JScopedEnv env;

    jsize count = env->GetArrayLength(jarr);
    if (env->ExceptionCheck() || (count < 0)) {
        QCC_LogError(ER_FAIL, ("GetArrayLength() invalid"));
        return;
    }

    jlong* jvals = env->GetLongArrayElements(jarr, NULL);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("GetLongArrayElements() invalid"));
        return;
    }

    vals.clear();

    for (jsize i = 0; i < count; i++) {
        vals.push_back((uint32_t)jvals[i]);
    }

    env->ReleaseLongArrayElements(jarr, jvals, JNI_ABORT);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("ReleaseLongArrayElements() invalid"));
        return;
    }
}

} /* namespace lsf */

#undef QCC_MODULE
