/**
 * @file aj_x509.c
 *
 * Utilites for X.509 Certificates
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

/**
 * Per-module definition of the current module for debug logging.  Must be defined
 * prior to first inclusion of aj_debug.h
 */
#define AJ_MODULE X509

#include "aj_debug.h"
#include "aj_creds.h"
#include "aj_util.h"
#include "aj_x509.h"

/**
 * Turn on per-module debug printing by setting this variable to non-zero value
 * (usually in debugger).
 */
#ifndef NDEBUG
uint8_t dbgX509 = 0;
#endif

// 1.2.840.10045.4.3.2
const uint8_t OID_SIG_ECDSA_SHA256[]  = { 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04, 0x03, 0x02 };
// 1.2.840.10045.2.1
const uint8_t OID_KEY_ECC[]           = { 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x02, 0x01 };
// 1.2.840.10045.3.1.7
const uint8_t OID_CRV_PRIME256V1[]    = { 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x03, 0x01, 0x07 };
// 2.5.4.10
const uint8_t OID_DN_OU[]             = { 0x55, 0x04, 0x0B };
// 2.5.4.3
const uint8_t OID_DN_CN[]             = { 0x55, 0x04, 0x03 };
// 2.5.29.19
const uint8_t OID_BASIC_CONSTRAINTS[] = { 0x55, 0x1D, 0x13 };
// 2.5.29.17
const uint8_t OID_SUB_ALTNAME[]       = { 0x55, 0x1D, 0x11 };
// 2.16.840.1.101.3.4.2.1
const uint8_t OID_DIG_SHA256[]        = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01 };
// 1.3.6.1.4.1.44924.1
const uint8_t OID_CUSTOM_CERT_TYPE[]  = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0xDE, 0x7C, 0x01, 0x01 };
// 1.3.6.1.4.1.44924.2
const uint8_t OID_CUSTOM_DIGEST[]     = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0xDE, 0x7C, 0x01, 0x02 };

uint8_t CompareOID(DER_Element* der, const uint8_t* oid, size_t len)
{
    if (der->size != len) {
        return 0;
    }
    return (0 == memcmp(der->data, oid, len));
}

static AJ_Status DecodeCertificateName(DER_Element* der, uint8_t type, AJ_GUID* ou, AJ_GUID* cn)
{
    AJ_Status status = AJ_OK;
    DER_Element set;
    DER_Element seq;
    DER_Element oid;
    DER_Element tmp;

    while ((AJ_OK == status) && (der->size)) {
        status = AJ_ASN1DecodeElement(der, ASN_SET_OF, &set);
        if (AJ_OK != status) {
            return status;
        }
        status = AJ_ASN1DecodeElement(&set, ASN_SEQ, &seq);
        if (AJ_OK != status) {
            return status;
        }
        status = AJ_ASN1DecodeElement(&seq, ASN_OID, &oid);
        if (AJ_OK != status) {
            return status;
        }
        status = AJ_ASN1DecodeElement(&seq, ASN_UTF8, &tmp);
        if (AJ_OK != status) {
            return status;
        }
        if (CompareOID(&oid, OID_DN_OU, sizeof (OID_DN_OU))) {
            status = AJ_GUID_FromString(ou, (const char*) tmp.data);
            if (AJ_OK != status) {
                return status;
            }
        } else if (CompareOID(&oid, OID_DN_CN, sizeof (OID_DN_CN))) {
            status = AJ_GUID_FromString(cn, (const char*) tmp.data);
            if (AJ_OK != status) {
                return status;
            }
        }
    }

    return status;
}

static AJ_Status DecodeCertificatePub(DER_Element* der, AJ_KeyInfo* keyinfo)
{
    AJ_Status status;
    DER_Element seq;
    DER_Element bit;
    DER_Element oid1;
    DER_Element oid2;
    uint8_t tags1[] = { ASN_SEQ, ASN_BITS };
    uint8_t tags2[] = { ASN_OID, ASN_OID };

    status = AJ_ASN1DecodeElements(der, tags1, sizeof (tags1), &seq, &bit);
    if (AJ_OK != status) {
        return status;
    }

    /*
     * We only accept NISTP256 ECC keys at the moment.
     */
    status = AJ_ASN1DecodeElements(&seq, tags2, sizeof (tags2), &oid1, &oid2);
    if (AJ_OK != status) {
        return status;
    }
    if (sizeof (OID_KEY_ECC) != oid1.size) {
        return AJ_ERR_INVALID;
    }
    if (0 != memcmp(OID_KEY_ECC, oid1.data, oid1.size)) {
        return AJ_ERR_INVALID;
    }
    if (sizeof (OID_CRV_PRIME256V1) != oid2.size) {
        return AJ_ERR_INVALID;
    }
    if (0 != memcmp(OID_CRV_PRIME256V1, oid2.data, oid2.size)) {
        return AJ_ERR_INVALID;
    }

    /*
     * We only accept uncompressed ECC points.
     */
    if ((2 + KEY_ECC_PUB_SZ) != bit.size) {
        return AJ_ERR_INVALID;
    }
    if ((0x00 != bit.data[0]) || (0x04 != bit.data[1])) {
        return AJ_ERR_INVALID;
    }
    bit.data += 2;
    bit.size -= 2;

    memset(keyinfo, 0, sizeof (AJ_KeyInfo));
    keyinfo->fmt = KEY_FMT_ALLJOYN;
    keyinfo->use = KEY_USE_SIG;
    keyinfo->kty = KEY_TYP_ECC;
    keyinfo->alg = KEY_ALG_ECDSA_SHA256;
    keyinfo->crv = KEY_CRV_NISTP256;
    AJ_BigvalDecode(bit.data, &keyinfo->key.publickey.x, KEY_ECC_SZ);
    bit.data += KEY_ECC_SZ;
    bit.size -= KEY_ECC_SZ;
    AJ_BigvalDecode(bit.data, &keyinfo->key.publickey.y, KEY_ECC_SZ);

    return status;
}

static AJ_Status DecodeCertificateExt(X509Certificate* certificate, DER_Element* der)
{
    AJ_Status status;
    DER_Element tmp;
    DER_Element seq;
    DER_Element oid;
    DER_Element oct;
    uint8_t tags[] = { ASN_OID, ASN_OCTETS };

    certificate->type = UNKNOWN_CERTIFICATE;
    status = AJ_ASN1DecodeElement(der, ASN_SEQ, &tmp);
    if (AJ_OK != status) {
        return status;
    }
    der->size = tmp.size;
    der->data = tmp.data;
    while ((AJ_OK == status) && (der->size)) {
        status = AJ_ASN1DecodeElement(der, ASN_SEQ, &seq);
        if (AJ_OK != status) {
            return status;
        }
        status = AJ_ASN1DecodeElements(&seq, tags, sizeof (tags), &oid, &oct);
        if (AJ_OK != status) {
            return status;
        }
        if (CompareOID(&oid, OID_BASIC_CONSTRAINTS, sizeof (OID_BASIC_CONSTRAINTS))) {
            status = AJ_ASN1DecodeElement(&oct, ASN_SEQ, &seq);
            if (AJ_OK != status) {
                return status;
            }
            status = AJ_ASN1DecodeElement(&seq, ASN_BOOLEAN, &tmp);
            if (AJ_OK != status) {
                return status;
            }
        } else if (CompareOID(&oid, OID_CUSTOM_CERT_TYPE, sizeof (OID_CUSTOM_CERT_TYPE))) {
            status = AJ_ASN1DecodeElement(&oct, ASN_SEQ, &seq);
            if (AJ_OK != status) {
                return status;
            }
            status = AJ_ASN1DecodeElement(&seq, ASN_INTEGER, &tmp);
            if (AJ_OK != status) {
                return status;
            }
            if (sizeof (uint32_t) < tmp.size) {
                return AJ_ERR_INVALID;
            }
            certificate->type = 0;
            while (tmp.size--) {
                certificate->type <<= 8;
                certificate->type  |= *tmp.data++;
            }
        } else if (CompareOID(&oid, OID_SUB_ALTNAME, sizeof (OID_SUB_ALTNAME))) {
            certificate->alias.size = oct.size;
            certificate->alias.data = oct.data;
        } else if (CompareOID(&oid, OID_CUSTOM_DIGEST, sizeof (OID_CUSTOM_DIGEST))) {
            status = AJ_ASN1DecodeElement(&oct, ASN_SEQ, &seq);
            if (AJ_OK != status) {
                return status;
            }
            status = AJ_ASN1DecodeElements(&seq, tags, sizeof (tags), &oid, &oct);
            if (AJ_OK != status) {
                return status;
            }
            if (!CompareOID(&oid, OID_DIG_SHA256, sizeof (OID_DIG_SHA256))) {
                return AJ_ERR_INVALID;
            }
            if (SHA256_DIGEST_LENGTH != oct.size) {
                return AJ_ERR_INVALID;
            }
            memcpy(certificate->digest, oct.data, SHA256_DIGEST_LENGTH);
        } else {
            // Ignore extensions we don't know
            AJ_DumpBytes("UNKNOWN", oid.data, oid.size);
            AJ_DumpBytes("UNKNOWN", oct.data, oct.size);
        }
    }

    return status;
}

static AJ_Status DecodeCertificateTBS(X509Certificate* certificate, DER_Element* tbs)
{
    AJ_Status status;
    DER_Element ver;
    DER_Element oid;
    DER_Element iss;
    DER_Element utc;
    DER_Element sub;
    DER_Element pub;
    DER_Element ext;
    DER_Element tmp;
    DER_Element time1;
    DER_Element time2;
    uint8_t tags1[] = { ASN_CONTEXT_SPECIFIC, ASN_INTEGER, ASN_SEQ, ASN_SEQ, ASN_SEQ, ASN_SEQ, ASN_SEQ, ASN_CONTEXT_SPECIFIC };
    uint8_t tags2[] = { ASN_UTC_TIME, ASN_UTC_TIME };

    status = AJ_ASN1DecodeElements(tbs, tags1, sizeof (tags1), 0, &ver, &certificate->serial, &oid, &iss, &utc, &sub, &pub, 3, &ext);
    if (AJ_OK != status) {
        return status;
    }

    /*
     * We only accept X.509v3 certificates.
     */
    status = AJ_ASN1DecodeElement(&ver, ASN_INTEGER, &tmp);
    if (AJ_OK != status) {
        return status;
    }
    if ((0x1 != tmp.size) || (0x2 != *tmp.data)) {
        return AJ_ERR_INVALID;
    }

    /*
     * We only accept ECDSA-SHA256 signed certificates at the moment.
     */
    status = AJ_ASN1DecodeElement(&oid, ASN_OID, &tmp);
    if (AJ_OK != status) {
        return status;
    }
    if (!CompareOID(&tmp, OID_SIG_ECDSA_SHA256, sizeof (OID_SIG_ECDSA_SHA256))) {
        return AJ_ERR_INVALID;
    }

    status = DecodeCertificateName(&iss, 0, NULL, &certificate->issuer);
    if (AJ_OK != status) {
        return status;
    }
    status = AJ_ASN1DecodeElements(&utc, tags2, sizeof (tags2), &time1, &time2);
    if (AJ_OK != status) {
        return status;
    }
    status = DecodeCertificateName(&sub, 0, &certificate->guild, &certificate->subject);
    if (AJ_OK != status) {
        return status;
    }
    status = DecodeCertificatePub(&pub, &certificate->keyinfo);
    if (AJ_OK != status) {
        return status;
    }
    memset(certificate->digest, 0, SHA256_DIGEST_LENGTH);
    status = DecodeCertificateExt(certificate, &ext);

    return status;
}

static AJ_Status DecodeCertificateSig(DER_Element* der, ecc_signature* signature)
{
    AJ_Status status;
    DER_Element seq;
    DER_Element int1;
    DER_Element int2;
    uint8_t tags[] = { ASN_INTEGER, ASN_INTEGER };

    status = AJ_ASN1DecodeElement(der, ASN_SEQ, &seq);
    if (AJ_OK != status) {
        return status;
    }
    status = AJ_ASN1DecodeElements(&seq, tags, sizeof (tags), &int1, &int2);
    if (AJ_OK != status) {
        return status;
    }

    /*
     * Skip over unused bits.
     */
    if ((0 < int1.size) && (0 == *int1.data)) {
        int1.data++;
        int1.size--;
    }
    if ((0 < int2.size) && (0 == *int2.data)) {
        int2.data++;
        int2.size--;
    }

    memset(signature, 0, sizeof (ecc_signature));
    AJ_BigvalDecode(int1.data, &signature->r, int1.size);
    AJ_BigvalDecode(int2.data, &signature->s, int2.size);

    return status;
}

AJ_Status AJ_X509DecodeCertificateDER(X509Certificate* certificate, DER_Element* der)
{
    AJ_Status status;
    DER_Element seq;
    DER_Element tbs;
    DER_Element tmp;
    DER_Element oid;
    DER_Element sig;
    uint8_t tags1[] = { ASN_SEQ };
    uint8_t tags2[] = { ASN_SEQ, ASN_SEQ, ASN_BITS };

    AJ_InfoPrintf(("AJ_X509DecodeCertificateDER(certificate=%p, der=%p)\n", certificate, der));

    if ((NULL == certificate) || (NULL == der)) {
        return AJ_ERR_INVALID;
    }

    status = AJ_ASN1DecodeElements(der, tags1, sizeof (tags1), &seq);
    if (AJ_OK != status) {
        return status;
    }
    status = AJ_ASN1DecodeElements(&seq, tags2, sizeof (tags2), &tbs, &tmp, &sig);
    if (AJ_OK != status) {
        return status;
    }
    /*
     * The signed TBS includes the sequence and length fields.
     */
    certificate->tbs.data = tbs.data - 4;
    certificate->tbs.size = tbs.size + 4;

    status = DecodeCertificateTBS(certificate, &tbs);
    if (AJ_OK != status) {
        return status;
    }

    /*
     * We only accept ECDSA-SHA256 signed certificates at the moment.
     */
    status = AJ_ASN1DecodeElement(&tmp, ASN_OID, &oid);
    if (AJ_OK != status) {
        return status;
    }
    if (!CompareOID(&oid, OID_SIG_ECDSA_SHA256, sizeof (OID_SIG_ECDSA_SHA256))) {
        return AJ_ERR_INVALID;
    }

    /*
     * Remove the byte specifying unused bits, this should always be zero.
     */
    if ((0 == sig.size) || (0 != *sig.data)) {
        return AJ_ERR_INVALID;
    }
    sig.data++;
    sig.size--;
    status = DecodeCertificateSig(&sig, &certificate->signature);

    return status;
}

AJ_Status AJ_X509SelfVerify(const X509Certificate* certificate)
{
    AJ_InfoPrintf(("AJ_X509SelfVerify(certificate=%p)\n", certificate));
    return AJ_ECDSAVerify(certificate->tbs.data, certificate->tbs.size, &certificate->signature, &certificate->keyinfo.key.publickey);
}

AJ_Status AJ_X509Verify(const X509Certificate* certificate, const AJ_KeyInfo* key)
{
    AJ_InfoPrintf(("AJ_X509Verify(certificate=%p, key=%p)\n", certificate, key));
    return AJ_ECDSAVerify(certificate->tbs.data, certificate->tbs.size, &certificate->signature, &key->key.publickey);
}
