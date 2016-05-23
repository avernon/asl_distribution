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
#ifndef _AJ_KEYEXCHANGE_H
#define _AJ_KEYEXCHANGE_H

/**
 * @file aj_keyexchange.h
 * @defgroup aj_keyexchange Implementation of Key Exchange mechanisms
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
#include <ajtcl/aj_peer.h>
#include <ajtcl/aj_crypto_sha2.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Key Exchange Types
 */
#define AJ_KE_ECDHE   0x1

typedef AJ_Status (*AJ_KEInit)(AJ_SHA256_Context* hash);
typedef AJ_Status (*AJ_KEMarshal)(AJ_Message* msg);
typedef AJ_Status (*AJ_KEUnmarshal)(AJ_Message* msg);
typedef void (*AJ_KEGetSecret)(uint8_t** secret, size_t* secretlen);

typedef struct _AJ_KeyExchange {
    AJ_KEInit Init;
    AJ_KEMarshal Marshal;
    AJ_KEUnmarshal Unmarshal;
    AJ_KEGetSecret GetSecret;
} AJ_KeyExchange;

/**
 * ECDHE key exchange
 */
extern AJ_KeyExchange AJ_KeyExchangeECDHE;

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif
