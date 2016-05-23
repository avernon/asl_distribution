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
#ifndef _AJ_CRYPTO_SHA2_H
#define _AJ_CRYPTO_SHA2_H

/**
 * @file aj_crypto_sha2.h
 * @defgroup aj_crypto SHA-256 Cryptographic Support
 * @{
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

#include <ajtcl/aj_target.h>
#include <ajtcl/aj_status.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AJ_SHA256_DIGEST_LENGTH (32)

typedef struct AJ_SHA256_Context AJ_SHA256_Context;

/*** SHA-256/384/512 Function Prototypes ******************************/

/**
 * Initialize the hash context.  Calls to this function must be
 * matched with a call to AJ_SHA256_Final() to ensure that resources
 * are released.
 *
 * @return Pointer to context. NULL if init failed.
 */
AJ_SHA256_Context* AJ_SHA256_Init(void);

/**
 * Update the digest using the specific bytes
 * @param context the hash context
 * @param buf the bytes to digest
 * @param bufSize the number of bytes to digest
 */
void AJ_SHA256_Update(AJ_SHA256_Context* context, const uint8_t* buf, size_t bufSize);

/**
 * Retrieve the digest but keep the hash active for further updates.
 * @param context the hash context
 * @param digest the buffer to hold the digest.  Must be of size AJ_SHA256_DIGEST_LENGTH
 * @return AJ_OK if successful, otherwise error.
 */
AJ_Status AJ_SHA256_GetDigest(AJ_SHA256_Context* context, uint8_t* digest);

/**
 * Finish the hash calculation and free resources.
 * @param context the hash context
 * @param digest - the buffer to hold the digest.
 *        Must be NULL or of size AJ_SHA256_DIGEST_LENGTH.
 *        If the value is NULL, resources are freed but the digest
 *        is not calculated.
 * @return AJ_OK if successful, otherwise error.
 */
AJ_Status AJ_SHA256_Final(AJ_SHA256_Context* context, uint8_t* digest);

/**
 * Random function
 * @param inputs    array holding secret, label, seed
 * @param lengths   array holding the lengths of the inputs
 * @param count     the size of the input array
 * @param out       the buffer holding the random value
 * @param outLen    the buffer size
 * @return AJ_OK if succeeds; otherwise error
 */
AJ_Status AJ_Crypto_PRF_SHA256(const uint8_t** inputs, const uint8_t* lengths,
                               uint32_t count, uint8_t* out, uint32_t outLen);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif
