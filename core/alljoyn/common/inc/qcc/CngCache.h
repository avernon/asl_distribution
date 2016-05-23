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
#ifndef _CNG_CACHE_H
#define _CNG_CACHE_H
/**
 * @file
 *
 * This file defines the CngCache object used to manage the lifetime of global CNG handles.
 */

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
 ******************************************************************************/

#include <assert.h>
#include <windows.h>
#include <bcrypt.h>

#include <qcc/platform.h>

namespace qcc {

/**
 * This struct manages the lifetime of algorithm handles.
 */
struct CngCache {
    CngCache();
    ~CngCache();

    /**
     * Delete the opened algorithm handles.
     */
    void Cleanup();

    /**
     * Number of supported algorithms as defined by Crypto_Hash::Algorithm enum
     */
    static const int ALGORITHM_COUNT = 3;

    BCRYPT_ALG_HANDLE algHandles[ALGORITHM_COUNT][2];
    BCRYPT_ALG_HANDLE ccmHandle;
    BCRYPT_ALG_HANDLE ecbHandle;
    BCRYPT_ALG_HANDLE rsaHandle;
};

extern CngCache& cngCache;

} // qcc

#endif

