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

// The template definitions below are intended to be #include'd from
// the corresponding .h file, hence the #ifdef guard
#ifdef LSF_JNI_JENUMARRAY_H_

#define QCC_MODULE LSF_QCC_MODULE

namespace lsf {

template <typename T> jobjectArray JEnumArray::NewEnumArray(JEnum &jenum, const std::list<T> &cEnums)
{
    JScopedEnv env;

    typename std::list<T>::size_type count = cEnums.size();
    if (!count) {
        QCC_LogError(ER_FAIL, ("Empty list"));
        return NULL;
    }

    jobjectArray jarr = env->NewObjectArray(count, jenum.getClass(), NULL);
    if (env->ExceptionCheck() || !jarr) {
        QCC_LogError(ER_FAIL, ("NewObjectArray() failed"));
        return NULL;
    }

    typename std::list<T>::const_iterator it = cEnums.begin();
    for (int i = 0; i < count; i++, it++) {
        jobject jobj = jenum.getObject((int)*it);
        if (env->ExceptionCheck() || !jobj) {
            QCC_LogError(ER_FAIL, ("getObject() failed"));
            return NULL;
        }

        env->SetObjectArrayElement(jarr, i, jobj);
        if (env->ExceptionCheck()) {
            QCC_LogError(ER_FAIL, ("SetObjectArrayElement() failed"));
            return NULL;
        }

        env->DeleteLocalRef(jobj);
    }

    return jarr;
}

template <typename T> void JEnumArray::CopyEnumArray(jobjectArray jarr, JEnum &jenum, std::list<T> &cenums)
{
    JScopedEnv env;

    jsize count = env->GetArrayLength(jarr);
    if (env->ExceptionCheck() || !count) {
        QCC_LogError(ER_FAIL, ("GetArrayLength() invalid"));
        return;
    }

    cenums.empty();

    for (jsize i = 0; i < count; i++) {
        jobject jobj = env->GetObjectArrayElement(jarr, i);
        if (env->ExceptionCheck() || !jobj) {
            QCC_LogError(ER_FAIL, ("GetObjectArrayElement() failed"));
            return;
        }

        cenums.push_back((T)jenum.getValue(jobj));

        env->DeleteLocalRef(jobj);
    }
}

} /* namespace lsf */

#undef QCC_MODULE

#endif /* LSF_JNI_JENUMARRAY_H_ */
