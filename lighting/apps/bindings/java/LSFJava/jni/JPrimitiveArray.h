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

#ifndef LSF_JNI_JPRIMITIVEARRAY_H_
#define LSF_JNI_JPRIMITIVEARRAY_H_

#include <jni.h>
#include <stddef.h>

#include "NUtil.h"

namespace lsf {

template <typename JTYPE, typename CTYPE>
class JPrimitiveArray {
  public:
    JPrimitiveArray(JTYPE jarr);
    virtual ~JPrimitiveArray();

    CTYPE* c_arr();
    jsize len();

  protected:
    typedef CTYPE* (JNIEnv::*GetMethod)(JTYPE, jboolean *);
    typedef void (JNIEnv::*ReleaseMethod)(JTYPE, CTYPE*, jint);

    JTYPE jarray;
    CTYPE* carray;
    jsize length;

    GetMethod getMethod;
    ReleaseMethod releaseMethod;

    void Reset();
    void Create();
    void Destroy();

    virtual GetMethod GetMethodToGetPrimitiveArrayElements() = 0;
    virtual ReleaseMethod GetMethodToReleasePrimitiveArrayElements() = 0;
};

} /* namespace lsf */

// The templated method definitions must be included in this header
#include "JPrimitiveArray.cpp"

#endif /* LSF_JNI_JPRIMITIVEARRAY_H_ */
