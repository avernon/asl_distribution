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
#ifndef _AJ_ASN1_H
#define _AJ_ASN1_H
/**
 * @file aj_asn1.h
 * @defgroup aj_asn1 ASN.1 decoding
 * @{
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

#include "aj_target.h"
#include "aj_status.h"

/**
 * DER encoding types.
 */
#define ASN_BOOLEAN          0x01
#define ASN_INTEGER          0x02
#define ASN_BITS             0x03
#define ASN_OCTETS           0x04
#define ASN_NULL             0x05
#define ASN_OID              0x06
#define ASN_UTF8             0x0C
#define ASN_SEQ              0x10
#define ASN_SET_OF           0x11
#define ASN_PRINTABLE        0x13
#define ASN_ASCII            0x16
#define ASN_UTC_TIME         0x17
#define ASN_CONTEXT_SPECIFIC 0xA0

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
AJ_Status AJ_ASN1DecodeElements(DER_Element* der, uint8_t* tags, size_t len, ...);

/**
 * @}
 */
#endif
