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
#ifdef LSF_JNI_JPRIMITIVEARRAY_H_

#define QCC_MODULE LSF_QCC_MODULE

namespace lsf {

template <typename JTYPE, typename CTYPE>
JPrimitiveArray<JTYPE, CTYPE>::JPrimitiveArray(JTYPE jarr)
{
    jarray = jarr;

    Reset();
}

template <typename JTYPE, typename CTYPE>
JPrimitiveArray<JTYPE, CTYPE>::~JPrimitiveArray()
{
    Destroy();
}

template <typename JTYPE, typename CTYPE>
CTYPE* JPrimitiveArray<JTYPE, CTYPE>::c_arr()
{
    Create();
    return carray;
}

template <typename JTYPE, typename CTYPE>
jsize JPrimitiveArray<JTYPE, CTYPE>::len()
{
    Create();
    return length;
}

template <typename JTYPE, typename CTYPE>
void JPrimitiveArray<JTYPE, CTYPE>::Reset()
{
    carray = NULL;
    length = 0;

    getMethod = NULL;
    releaseMethod = NULL;
}

template <typename JTYPE, typename CTYPE>
void JPrimitiveArray<JTYPE, CTYPE>::Create()
{
    if (jarray && !carray) {
        JNIEnv* env = GetEnv();

        getMethod = GetMethodToGetPrimitiveArrayElements();
        releaseMethod = GetMethodToReleasePrimitiveArrayElements();

        if (getMethod && releaseMethod) {
            carray = (env->*getMethod)(jarray, NULL);

            if (!env->ExceptionCheck() && carray) {
                length = env->GetArrayLength(jarray);
            } else {
                QCC_LogError(ER_FAIL, ("GetPrimitiveArrayElements() failed"));
                Reset();
            }
        }
    }
}

template <typename JTYPE, typename CTYPE>
void JPrimitiveArray<JTYPE, CTYPE>::Destroy()
{
    if (jarray && carray) {
        (GetEnv()->*releaseMethod)(jarray, carray, 0);
        Reset();
    }
}

} /* namespace lsf */

#undef QCC_MODULE

#endif /* LSF_JNI_JPRIMITIVEARRAY_H_ */
