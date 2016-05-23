# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
/**
 * @file
 *
 * Define atomic read-modify-write memory options for Microsoft compiler
 */

/******************************************************************************
 *
 *
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
 ******************************************************************************/
#ifndef _TOOLCHAIN_QCC_ATOMIC_H
#define _TOOLCHAIN_QCC_ATOMIC_H

#include <windows.h>

namespace qcc {

/**
 * Increment an int32_t and return it's new value atomically.
 *
 * @param mem   Pointer to int32_t to be incremented.
 * @return  New value (after increment) of *mem
 */
inline int32_t IncrementAndFetch(volatile int32_t* mem) {
    return InterlockedIncrement(reinterpret_cast<volatile long*>(mem));
}

/**
 * Decrement an int32_t and return it's new value atomically.
 *
 * @param mem   Pointer to int32_t to be decremented.
 * @return  New value (after decrement) of *mem
 */
inline int32_t DecrementAndFetch(volatile int32_t* mem) {
    return InterlockedDecrement(reinterpret_cast<volatile long*>(mem));
}

}

#endif
