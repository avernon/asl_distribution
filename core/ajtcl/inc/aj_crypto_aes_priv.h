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
#ifndef _AJ_CRYPTO_AES_PRIV_H
#define _AJ_CRYPTO_AES_PRIV_H

/**
 * @file aj_crypto_aes_priv.h
 * @defgroup Private functions for low-level AES implementation
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

/**
 * AES counter mode encryption/decryption. Note that in CTR mode encrytion is its own inverse.
 *
 * @param key  The AES encryption key
 * @param in   The data to encrypt
 * @param out  The encrypted data
 * @param len  The length of the input data, must be multiple of 16
 * @param ctr  Pointer to a 16 byte counter block
 */
void AJ_AES_CTR_128(const uint8_t* key, const uint8_t* in, uint8_t* out, uint32_t len, uint8_t* ctr);

/**
 * AES CCM mode encryption
 *
 * @param key  The AES encryption key
 * @param in   The data to encrypt
 * @param out  The encrypted data
 * @param len  The length of the input data, must be multiple of 16
 * @param iv   Pointer to a 16 byte initialization vector
 */
void AJ_AES_CBC_128_ENCRYPT(const uint8_t* key, const uint8_t* in, uint8_t* out, uint32_t len, uint8_t* iv);


/**
 * Encrypt a single 16 byte block using AES in ECB mode
 *
 * @param key  The AES encryption key
 * @param in   The data to encrypt
 * @param out  The encrypted data
 */
void AJ_AES_ECB_128_ENCRYPT(const uint8_t* key, const uint8_t* in, uint8_t* out);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif
