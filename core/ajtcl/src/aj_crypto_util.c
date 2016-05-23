/**
 * @file
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

/**
 * Per-module definition of the current module for debug logging.  Must be defined
 * prior to first inclusion of aj_debug.h
 */
#define AJ_MODULE CRYPTO_UTIL

#include <ajtcl/aj_target.h>
#include <ajtcl/aj_crypto.h>
#include <ajtcl/aj_config.h>

/**
 * Turn on per-module debug printing by setting this variable to non-zero value
 * (usually in debugger).
 */
#ifndef NDEBUG
uint8_t dbgCRYPTO_UTIL = 0;
#endif

AJ_Status AJ_RandHex(char* randBuf, uint32_t bufLen, uint32_t len)
{
    AJ_RandBytes((uint8_t*)randBuf, len);
    return AJ_RawToHex((const uint8_t*) randBuf, len, randBuf, bufLen, FALSE);
}

int AJ_Crypto_Compare(const void* buf1, const void* buf2, size_t count)
{
    size_t i = 0;
    uint8_t different = 0;

    AJ_ASSERT(buf1 != NULL);
    AJ_ASSERT(buf2 != NULL);

    /* This loop uses the same number of cycles for any two buffers of size count. */
    for (i = 0; i < count; i++) {
        different |= ((uint8_t*)buf1)[i] ^ ((uint8_t*)buf2)[i];
    }

    return (int)different;
}
