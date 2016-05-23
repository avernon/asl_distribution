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
#ifndef _AJ_CERT_H
#define _AJ_CERT_H

/**
 * @file aj_cert.h
 * @defgroup aj_cert Certificate Utilities
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
#include <ajtcl/aj_crypto_ecc.h>
#include <ajtcl/aj_creds.h>
#include <ajtcl/aj_msg.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const uint8_t OID_SIG_ECDSA_SHA256[8];
extern const uint8_t OID_KEY_ECC[7];
extern const uint8_t OID_CRV_PRIME256V1[8];
extern const uint8_t OID_DN_OU[3];
extern const uint8_t OID_DN_CN[3];
extern const uint8_t OID_BASIC_CONSTRAINTS[3];
extern const uint8_t OID_SKI[3];
extern const uint8_t OID_AKI[3];
extern const uint8_t OID_SUB_ALTNAME[3];
extern const uint8_t OID_HASH_SHA256[9];
extern const uint8_t OID_CUSTOM_TYPE[10];
extern const uint8_t OID_CUSTOM_DIGEST[10];
extern const uint8_t OID_CUSTOM_GROUP[10];
extern const uint8_t OID_CUSTOM_ALIAS[10];

/**
 * Structure for a DER encoded element.
 */
typedef struct _DER_Element {
    size_t size;
    uint8_t* data;
} DER_Element;

/**
 * Decode one element from a DER encoded blob.
 *
 * @param der The input DER encoded blob.
 * @param tag The expected element type.
 * @param out The output decoded element.
 *
 * @return  Return AJ_Status
 *          - AJ_OK on success
 *          - AJ_ERR_INVALID on all failures
 */
AJ_Status AJ_ASN1DecodeElement(DER_Element* der, uint8_t tag, DER_Element* out);

/**
 * Decode many elements from a DER encoded blob.
 * This is a non-recursive decoder.
 * Only a depth of one may be decoded in one call.
 *
 * @param der  The input DER encoded blob.
 * @param tags The expected element types.
 * @param len  The number of types to decode.
 * @param ...  The output decoded elements.
 *
 * @return  Return AJ_Status
 *          - AJ_OK on success
 *          - AJ_ERR_INVALID on all failures
 */
AJ_Status AJ_ASN1DecodeElements(DER_Element* der, const uint8_t* tags, size_t len, ...);

#define CERT_FMT_X509_DER  0

typedef struct _X509Validity {
    uint64_t from;
    uint64_t to;
} X509Validity;

typedef struct _X509DistinguishedName {
    DER_Element ou;                      /**< Organizational Unit name */
    DER_Element cn;                      /**< Common name */
} X509DistinguishedName;

typedef struct _X509Extensions {
    uint32_t ca;                         /**< Certificate authority */
    uint32_t type;                       /**< Certificate type in AllJoyn ecosystem */
    DER_Element ski;                     /**< Subject Key Identifier */
    DER_Element aki;                     /**< Authority Key Identifier */
    DER_Element alias;                   /**< Alias (subject alt name) */
    DER_Element group;                   /**< Group (subject alt name) */
    DER_Element digest;                  /**< Associated digest */
} X509Extensions;

typedef struct _X509TbsCertificate {
    DER_Element serial;                  /**< The serial number */
    X509DistinguishedName issuer;        /**< The issuer's identity */
    X509Validity validity;               /**< The validity period */
    X509DistinguishedName subject;       /**< The subject's identity */
    AJ_ECCPublicKey publickey;           /**< The subject's public key */
    X509Extensions extensions;           /**< The certificate extensions */
} X509TbsCertificate;

/**
 * Structure for X.509 certificate.
 * Only useful for NISTP256 ECDSA signed certificates at the moment.
 * Can be modified to handle other types in the future.
 */
typedef struct _X509Certificate {
    DER_Element der;                     /**< Certificate DER encoding */
    DER_Element raw;                     /**< The raw tbs section */
    X509TbsCertificate tbs;              /**< The TBS section of the certificate */
    AJ_ECCSignature signature;           /**< The certificate signature */
} X509Certificate;

/**
 * Certificate chain: linked list of certificates
 * These are always root..end entity order.
 */
typedef struct _X509CertificateChain {
    X509Certificate certificate;         /**< The certificate */
    struct _X509CertificateChain* next;  /**< Linked list pointer */
} X509CertificateChain;

/**
 * Decode a PEM encoded private key
 *
 * @param key         The output decoded key.
 * @param pem         The input PEM.
 *
 * @return  Return AJ_Status
 *          - AJ_OK on success
 *          - AJ_ERR_INVALID on all failures
 */
AJ_Status AJ_DecodePrivateKeyPEM(AJ_ECCPrivateKey* key, const char* pem);

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
 * Decode a PEM encoded X.509 certificate.
 *
 * @param certificate The output decoded certificate.
 * @param pem         The input PEM.
 *
 * @return  Return AJ_Status
 *          - AJ_OK on success
 *          - AJ_ERR_RESOURCES on failure
 */
AJ_Status AJ_X509DecodeCertificatePEM(X509Certificate* certificate, const char* pem);

/**
 * Decode a PEM encoded X.509 certificate chain.
 * The order of certificates is important.
 * PEM strings are stored as end entity...root order.
 * This decodes to a linked list that is root...end entity order.
 *
 * @param pem         The input PEM.
 *
 * @return  Return chain on success, NULL on failure
 */
X509CertificateChain* AJ_X509DecodeCertificateChainPEM(const char* pem);

/**
 * Free the memory allocated to an X509CertificateChain* as returned
 * by AJ_X509DecodeCertificateChainPEM.
 *
 * @param root       Root of the certificate chain. If this is NULL, this function does nothing.
 */
void AJ_X509FreeDecodedCertificateChain(X509CertificateChain* root);

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
AJ_Status AJ_X509Verify(const X509Certificate* certificate, const AJ_ECCPublicKey* key);

/**
 * Verify a chain of X.509 certificates.
 * Root certificate is first.
 *
 * @param chain       The input certificate chain.
 * @param key         The verification key of the root. If this is NULL, don't verify the root.
 * @param type        The expected certificate type (EKU). If this is 0, don't verify the type.
 *
 * @return  Return AJ_Status
 *          - AJ_OK on success
 *          - AJ_ERR_SECURITY on failure
 */
AJ_Status AJ_X509VerifyChain(const X509CertificateChain* root, const AJ_ECCPublicKey* key, uint32_t type);

/**
 * Free memory associated with X.509 chain.
 *
 * @param root        The input certificate chain.
 */
void AJ_X509ChainFree(X509CertificateChain* root);

/**
 * Marshal a X.509 certificate chain.
 *
 * @param chain       The input certificate chain.
 * @param msg         The message.
 *
 * @return  Return AJ_Status
 *          - AJ_OK on success
 *          - AJ_ERR_SECURITY on failure
 */
AJ_Status AJ_X509ChainMarshal(X509CertificateChain* root, AJ_Message* msg);

/**
 * Unmarshal a X.509 certificate chain.
 *
 * @param chain       The output certificate chain.
 * @param msg         The message.
 *
 * @return  Return AJ_Status
 *          - AJ_OK on success
 *          - AJ_ERR_SECURITY on failure
 */
AJ_Status AJ_X509ChainUnmarshal(X509CertificateChain** root, AJ_Message* msg);

/**
 * Marshal a X.509 certificate chain to a local buffer.
 *
 * @param chain       The input certificate chain.
 * @param field       The local buffer.
 *
 * @return  Return AJ_Status
 *          - AJ_OK on success
 *          - AJ_ERR_SECURITY on failure
 */
AJ_Status AJ_X509ChainToBuffer(X509CertificateChain* root, AJ_CredField* field);

/**
 * Unmarshal a X.509 certificate chain from a local buffer.
 *
 * @param chain       The output certificate chain.
 * @param field       The local buffer.
 *
 * @return  Return AJ_Status
 *          - AJ_OK on success
 *          - AJ_ERR_SECURITY on failure
 */
AJ_Status AJ_X509ChainFromBuffer(X509CertificateChain** root, AJ_CredField* field);

/**
 * Return a reference to the leaf certificate in a chain.
 *
 * @param root         The certificate chain.
 *
 * @return Return the head of the reversed linked list.
 */
X509Certificate* AJ_X509LeafCertificate(X509CertificateChain* root);

/**
 * Reverse the certificate chain linked list.
 * The order for certificates in memory is root first.
 * The wire protocol expects leaf certificate first.
 *
 * @param root         The certificate chain.
 *
 * @return Return the head of the reversed linked list.
 */
X509CertificateChain* AJ_X509ReverseChain(X509CertificateChain* root);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif
