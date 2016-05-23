/**
 * @file
 */
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
 ******************************************************************************/
#define AJ_MODULE ASN1

#include <stdarg.h>
#include "aj_asn1.h"
#include "aj_debug.h"

#ifndef NDEBUG
uint8_t dbgASN1 = 0;
#endif

static AJ_Status DecodeLength(DER_Element* der, DER_Element* out)
{
    size_t n;
    size_t len;

    if ((NULL == der->data) || (0 == der->size)) {
        return AJ_ERR_INVALID;
    }

    len = *(der->data)++;
    der->size--;
    if (0x80 & len) {
        n = len & 0x7F;
        if (n > sizeof (size_t)) {
            return AJ_ERR_INVALID;
        }
        len = 0;
        while ((n--) && (der->size--)) {
            len = (len << 8) + *(der->data)++;
        }
    }
    if (len > der->size) {
        return AJ_ERR_INVALID;
    }
    out->size = len;
    out->data = der->data;

    return AJ_OK;
}

AJ_Status AJ_ASN1DecodeElement(DER_Element* der, uint8_t tag, DER_Element* out)
{
    uint8_t tmp;

    AJ_InfoPrintf(("AJ_ASN1DecodeElement(der=%p, tag=%x, out=%p)\n", der, tag, out));

    if ((NULL == der) || (NULL == out)) {
        return AJ_ERR_INVALID;
    }
    if ((NULL == der->data) || (0 == der->size)) {
        return AJ_ERR_INVALID;
    }

    /*
     * Decode tag and check it is what we expect
     */
    tmp = *(der->data)++;
    der->size--;
    if (ASN_CONTEXT_SPECIFIC != (tmp & ASN_CONTEXT_SPECIFIC)) {
        tmp &= 0x1F;
    }
    if (tmp != tag) {
        return AJ_ERR_INVALID;
    }
    /*
     * Decode size
     */
    if (AJ_OK != DecodeLength(der, out)) {
        return AJ_ERR_INVALID;
    }
    der->data += out->size;
    der->size -= out->size;

    return AJ_OK;
}

AJ_Status AJ_ASN1DecodeElements(DER_Element* der, uint8_t* tags, size_t len, ...)
{
    AJ_Status status = AJ_OK;
    DER_Element* out;
    va_list argp;
    uint8_t tag;
    uint32_t tmp;

    AJ_InfoPrintf(("AJ_ASN1DecodeElements(der=%p, tags=%p, len=%zu)\n", der, tags, len));

    if ((NULL == der) || (NULL == tags)) {
        return AJ_ERR_INVALID;
    }

    va_start(argp, len);
    while ((AJ_OK == status) && len && (der->size)) {
        tag = *tags++;
        if (ASN_CONTEXT_SPECIFIC == tag) {
            tmp = va_arg(argp, uint32_t);
            tag = (ASN_CONTEXT_SPECIFIC | tmp);
        }
        out = va_arg(argp, DER_Element*);
        len--;
        status = AJ_ASN1DecodeElement(der, tag, out);
    }
    va_end(argp);

    /*
     * Should all be consumed
     */
    if (len || der->size) {
        status = AJ_ERR_INVALID;
    }

    return status;
}

