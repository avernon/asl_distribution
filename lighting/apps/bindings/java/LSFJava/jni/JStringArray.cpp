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

#include <sstream>
#include <iterator>

#include <qcc/Debug.h>

#include "JStringArray.h"
#include "NUtil.h"

#define QCC_MODULE "AJN-LSF-JNI"

namespace lsf {

jobjectArray JStringArray::NewStringArray(const std::list<std::string>& strs)
{
    JScopedEnv env;
    std::list<std::string>::size_type count = strs.size();

    jclass jcls = env->FindClass("java/lang/String");
    if (env->ExceptionCheck() || !jcls) {
        QCC_LogError(ER_FAIL, ("FindClass() failed"));
        return NULL;
    }

    jobjectArray jarr = env->NewObjectArray(count, jcls, NULL);
    if (env->ExceptionCheck() || !jarr) {
        QCC_LogError(ER_FAIL, ("NewObjectArray() failed"));
        return NULL;
    }

    std::list<std::string>::const_iterator it = strs.begin();
    for (int i = 0; i < count; i++, it++) {
        jstring jstr = env->NewStringUTF(it->c_str());
        if (env->ExceptionCheck() || !jstr) {
            QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
            return NULL;
        }

        env->SetObjectArrayElement(jarr, i, jstr);
        if (env->ExceptionCheck()) {
            QCC_LogError(ER_FAIL, ("SetObjectArrayElement() failed"));
            return NULL;
        }

        env->DeleteLocalRef(jstr);
    }

    return jarr;
}

void JStringArray::CopyStringArray(jobjectArray jarr, std::list<std::string>& strs)
{
    JScopedEnv env;

    jsize count = env->GetArrayLength(jarr);
    if (env->ExceptionCheck() || (count < 0)) {
        QCC_LogError(ER_FAIL, ("GetArrayLength() invalid"));
        return;
    }

    strs.clear();

    for (jsize i = 0; i < count; i++) {
        jstring jobj = (jstring)env->GetObjectArrayElement(jarr, i);
        if (env->ExceptionCheck() || !jobj) {
            QCC_LogError(ER_FAIL, ("GetObjectArrayElement() failed"));
            return;
        }

        // We put the JString in its own scope here because its dtor
        // must execute before the call to DeleteLocalRef(). If the
        // call to DeleteLocalRef() executes first, then when the dtor
        // runs you will get a "accessed stale local reference" error
        // from JNI.
        {
            JString jstr(jobj);
            if (env->ExceptionCheck()) {
                QCC_LogError(ER_FAIL, ("JString failed"));
                return;
            }

            std::string str = jstr.c_str();
            strs.push_back(str);
        }

        env->DeleteLocalRef(jobj);
   }
}

std::string JStringArray::FlattenStringList(const std::list<std::string>& strs)
{
    std::ostringstream flattened;
    std::copy(strs.begin(), strs.end(), std::ostream_iterator<std::string>(flattened, ", "));

    return flattened.str();
}

} /* namespace lsf */

#undef QCC_MODULE
