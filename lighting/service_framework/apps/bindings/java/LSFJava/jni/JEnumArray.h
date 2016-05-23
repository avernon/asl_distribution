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

#ifndef LSF_JNI_JENUMARRAY_H_
#define LSF_JNI_JENUMARRAY_H_

#include <list>
#include <stddef.h>

#include <jni.h>

#include <qcc/Debug.h>

#include "JEnum.h"

#include "NDefs.h"
#include "NUtil.h"

namespace lsf {

class JEnumArray {
public:
    template <typename T> static jobjectArray NewEnumArray(JEnum &jenum, const std::list<T> &cenums);
    template <typename T> static void CopyEnumArray(jobjectArray jarr, JEnum &jenum, std::list<T> &cenums);
};

} /* namespace lsf */

// The templated method definitions must be included in this header
#include "JEnumArray.cpp"

#endif /* LSF_JNI_JENUMARRAY_H_ */

