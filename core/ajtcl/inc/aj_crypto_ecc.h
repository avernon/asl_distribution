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
#ifndef _AJ_CRYPTO_ECC_H
#define _AJ_CRYPTO_ECC_H

/**
 * @file aj_crypto_ecc.h
 * @defgroup aj_crypto Cryptographic Support
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

typedef enum {B_FALSE, B_TRUE} boolean_t;

/**
 * ECC type sizes
 */
#define KEY_ECC_SZ (8 * sizeof (uint32_t))
#define KEY_ECC_PRV_SZ KEY_ECC_SZ
#define KEY_ECC_PUB_SZ (2 * KEY_ECC_SZ)
#define KEY_ECC_SEC_SZ (2 * KEY_ECC_SZ)
#define KEY_ECC_SIG_SZ (2 * KEY_ECC_SZ)

/* Size of affine_point_t */
#define KEY_ECC_OLD_SZ (19 * sizeof (uint32_t))

/**
 * We currently only support one type of key
 * This structure can be modified to support more in the future
 */
#define KEY_ALG_ECDSA_SHA256 0
#define KEY_CRV_NISTP256     0
typedef struct _AJ_ECCPublicKey {
    uint8_t alg;                   /**< Algorithm */
    uint8_t crv;                   /**< Elliptic curve */
    uint8_t x[KEY_ECC_SZ];
    uint8_t y[KEY_ECC_SZ];
} AJ_ECCPublicKey;

typedef struct _AJ_ECCPrivateKey {
    uint8_t alg;                   /**< Algorithm */
    uint8_t crv;                   /**< Elliptic curve */
    uint8_t x[KEY_ECC_SZ];
} AJ_ECCPrivateKey;

typedef AJ_ECCPrivateKey AJ_ECCSecret;

typedef struct _AJ_ECCSignature {
    uint8_t alg;                   /**< Algorithm */
    uint8_t crv;                   /**< Elliptic curve */
    uint8_t r[KEY_ECC_SZ];
    uint8_t s[KEY_ECC_SZ];
} AJ_ECCSignature;

/**
 * Generates an ECC key pair.
 *
 * @param pub The output public key
 * @param prv The output private key
 *
 * @return  - AJ_OK if the key pair is successfully generated.
 *          - AJ_ERR_SECURITY otherwise
 */
AJ_Status AJ_GenerateECCKeyPair(AJ_ECCPublicKey* pub, AJ_ECCPrivateKey* prv);

/**
 * Generates the Diffie-Hellman share secret.
 *
 * @param pub The peer's public key
 * @param prv The private key
 * @param sec The output share secret
 *
 * @return  - AJ_OK if the share secret is successfully generated.
 *          - AJ_ERR_SECURITY otherwise
 */
AJ_Status AJ_GenerateShareSecret(AJ_ECCPublicKey* pub, AJ_ECCPrivateKey* prv, AJ_ECCSecret* sec);

/**
 * Sign a digest using the DSA key
 * @param digest The digest to sign
 * @param prv The signing private key
 * @param sig The output signature
 * @return  - AJ_OK if the signing process succeeds
 *          - AJ_ERR_SECURITY otherwise
 */
AJ_Status AJ_ECDSASignDigest(const uint8_t* digest, const AJ_ECCPrivateKey* prv, AJ_ECCSignature* sig);

/**
 * Sign a buffer using the DSA key
 * @param buf The buffer to sign
 * @param len The buffer len
 * @param prv The signing private key
 * @param sig The output signature
 * @return  - AJ_OK if the signing process succeeds
 *          - AJ_ERR_SECURITY otherwise
 */
AJ_Status AJ_ECDSASign(const uint8_t* buf, uint16_t len, const AJ_ECCPrivateKey* prv, AJ_ECCSignature* sig);

/**
 * Verify DSA signature of a digest
 * @param digest The digest to sign
 * @param sig The signature
 * @param pub The signing public key
 * @return  - AJ_OK if the signature verification succeeds
 *          - AJ_ERR_SECURITY otherwise
 */
AJ_Status AJ_ECDSAVerifyDigest(const uint8_t* digest, const AJ_ECCSignature* sig, const AJ_ECCPublicKey* pub);

/**
 * Verify DSA signature of a buffer
 * @param buf The buffer to sign
 * @param len The buffer len
 * @param sig The signature
 * @param pub The signing public key
 * @return  - AJ_OK if the signature verification succeeds
 *          - AJ_ERR_SECURITY otherwise
 */
AJ_Status AJ_ECDSAVerify(const uint8_t* buf, uint16_t len, const AJ_ECCSignature* sig, const AJ_ECCPublicKey* pub);

/**
 * Old encoding of native public key.
 *
 * @param pub          The ECC public key
 * @param[out] b8      Big endian byte array
 *
 */
void AJ_BigEndianDecodePublicKey(AJ_ECCPublicKey* pu, uint8_t* b8);

/**
 * Old decoding of native public key.
 *
 * @param[out] pub     The ECC public key
 * @param b8           Big endian byte array
 *
 */
void AJ_BigEndianEncodePublicKey(AJ_ECCPublicKey* pub, uint8_t* b8);

/**
 * Generates the Diffie-Hellman share secret using old encoding.
 *
 * @param pub The peer's public key
 * @param prv The private key
 * @param sec The output share secret
 *
 * @return  - AJ_OK if the share secret is successfully generated.
 *          - AJ_ERR_SECURITY otherwise
 */
AJ_Status AJ_GenerateShareSecretOld(AJ_ECCPublicKey* pub, AJ_ECCPrivateKey* prv, AJ_ECCPublicKey* sec);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif
