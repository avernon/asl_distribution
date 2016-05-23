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
#ifndef _AJ_KEYAUTHENTICATION_H
#define _AJ_KEYAUTHENTICATION_H

/**
 * @file aj_keyauthentication.h
 * @defgroup aj_keyauthentication Implementation of Key Authentication mechanisms
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

typedef AJ_Status (*AJ_KAInit)(AJ_AuthListenerFunc authlistener, const uint8_t* mastersecret, size_t mastersecretlen, AJ_SHA256_Context* hash);
typedef AJ_Status (*AJ_KAMarshal)(AJ_Message* msg, uint8_t role);
typedef AJ_Status (*AJ_KAUnmarshal)(AJ_Message* msg, uint8_t role);
typedef AJ_Status (*AJ_KAGetIdentity)(AJ_Identity* identity, uint32_t* expiration);
typedef AJ_Status (*AJ_KAFinal)();

typedef struct _AJ_KeyAuthentication {
    AJ_KAInit Init;
    AJ_KAMarshal Marshal;
    AJ_KAUnmarshal Unmarshal;
    AJ_KAGetIdentity GetIdentity;
    AJ_KAFinal Final;
} AJ_KeyAuthentication;

#define AUTH_ECDSA
#define AUTH_PSK
#define AUTH_NULL

#define AUTH_CLIENT 0
#define AUTH_SERVER 1

#ifdef AUTH_ECDSA
extern AJ_KeyAuthentication AJ_KeyAuthenticationECDSA;
#endif
#ifdef AUTH_PSK
extern AJ_KeyAuthentication AJ_KeyAuthenticationPSK;
void AJ_PSK_SetPwdCallback(AJ_AuthPwdFunc pwdcallback);
#endif
#ifdef AUTH_NULL
extern AJ_KeyAuthentication AJ_KeyAuthenticationNULL;
#endif

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif
