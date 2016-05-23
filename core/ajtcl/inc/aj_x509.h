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
#ifndef _AJ_X509_H
#define _AJ_X509_H
/**
 * @file
 *
 * Header file for X.509 certificate utilities
 */

/******************************************************************************
 * Copyright (c) 2014-2015, AllSeen Alliance. All rights reserved.
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

#include "aj_asn1.h"
#include "aj_creds.h"
#include "aj_crypto_ecc.h"
#include "aj_guid.h"

/**
 * OIDs used in X.509 certificates.
 */
extern const uint8_t OID_SIG_ECDSA_SHA256[];
extern const uint8_t OID_KEY_ECC[];
extern const uint8_t OID_CRV_PRIME256V1[];
extern const uint8_t OID_DN_OU[];
extern const uint8_t OID_DN_CN[];
extern const uint8_t OID_BASIC_CONSTRAINTS[];
extern const uint8_t OID_SUB_ALTNAME[];
extern const uint8_t OID_DIG_SHA256[];
extern const uint8_t OID_CUSTOM_DIGEST[];
extern const uint8_t OID_CUSTOM_CERT_TYPE[];

typedef enum {
    UNKNOWN_CERTIFICATE,
    IDENTITY_CERTIFICATE,
    MEMBERSHIP_CERTIFICATE
} CertificateType;

/**
 * Structure for X.509 certificate.
 * Only useful for NISTP256 ECDSA signed certificates at the moment.
 * Can be modified to handle other types in the future.
 */
typedef struct _X509Certificate {
    CertificateType type;                 /**< The certificate type */
    DER_Element tbs;                      /**< The TBS section of the certificate */
    DER_Element serial;                   /**< The serial number */
    AJ_GUID issuer;                       /**< The issuer's identity */
    AJ_GUID subject;                      /**< The subject's identity */
    AJ_GUID guild;                        /**< The subject's guild membership */
    AJ_KeyInfo keyinfo;                   /**< The subject's public key */
    DER_Element alias;                    /**< The subject's alias */
    uint8_t digest[SHA256_DIGEST_LENGTH]; /**< Digest field */
    ecc_signature signature;              /**< The certificate signature */
} X509Certificate;

/**
 * Decode a ASN.1 DER encoded X.509 certificate.
 *
 * @param certificate The output decoded certificate.
 * @param der         The input encoded DER blob.
 *
 * @return  Return AJ_Status
 *          - AJ_OK on success
 *          - AJ_ERR_INVALID on all failures
 */
AJ_Status AJ_X509DecodeCertificateDER(X509Certificate* certificate, DER_Element* der);

/**
 * Verify a self-signed X.509 certificate.
 *
 * @param certificate The input certificate.
 *
 * @return  Return AJ_Status
 *          - AJ_OK on success
 *          - AJ_ERR_SECURITY on failure
 */
AJ_Status AJ_X509SelfVerify(const X509Certificate* certificate);

/**
 * Verify a signed X.509 certificate.
 *
 * @param certificate The input certificate.
 * @param key         The verification key.
 *
 * @return  Return AJ_Status
 *          - AJ_OK on success
 *          - AJ_ERR_SECURITY on failure
 */
AJ_Status AJ_X509Verify(const X509Certificate* certificate, const AJ_KeyInfo* key);

#endif
