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
#ifndef _AJ_AUTH_LISTENER_H
#define _AJ_AUTH_LISTENER_H

/**
 * @file aj_auth_listener.h
 * @defgroup aj_auth_listener Authentication Listener
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
#include <ajtcl/aj_net.h>
#include <ajtcl/aj_status.h>
#include <ajtcl/aj_util.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Command for auth listener callback
 */
#define AJ_CRED_PRV_KEY    0x0001 /**< private key */
#define AJ_CRED_PUB_KEY    0x0002 /**< public key */
#define AJ_CRED_CERT_CHAIN 0x0003 /**< certificate chain */

#define AJ_CRED_REQUEST    0
#define AJ_CRED_RESPONSE   1

/* The key exchange is in the 16 MSB */
#define AUTH_KEYX_ANONYMOUS     0x00010000
#define AUTH_KEYX_EXTERNAL      0x00020000
#define AUTH_KEYX_PIN           0x00040000
#define AUTH_KEYX_SRP           0x00080000
#define AUTH_KEYX_SRP_LOGON     0x00100000
#define AUTH_KEYX_RSA           0x00200000
#define AUTH_KEYX_ECDHE         0x00400000

/* The key authentication suite is in the 16 LSB */

#define AUTH_SUITE_ANONYMOUS    AUTH_KEYX_ANONYMOUS
#define AUTH_SUITE_EXTERNAL     AUTH_KEYX_EXTERNAL
#define AUTH_SUITE_PIN_KEYX     AUTH_KEYX_PIN
#define AUTH_SUITE_SRP_KEYX     AUTH_KEYX_SRP
#define AUTH_SUITE_SRP_LOGON    AUTH_KEYX_SRP_LOGON
#define AUTH_SUITE_RSA_KEYX     AUTH_KEYX_RSA

#define AUTH_SUITE_ECDHE_NULL   (AUTH_KEYX_ECDHE | 0x0001)
#define AUTH_SUITE_ECDHE_PSK    (AUTH_KEYX_ECDHE | 0x0002)
#define AUTH_SUITE_ECDHE_ECDSA  (AUTH_KEYX_ECDHE | 0x0004)

#define AJ_AUTH_SUITES_NUM      3    /**< Number of supported authentication suites */

/*
 * Type for a Credential entry for the auth listener callback
 */
typedef struct _AJ_Credential {
    uint8_t direction;   /**< request or response */
    uint32_t expiration; /**< auth listener to set key expiration value */
    uint8_t* data;       /**< data to or from the auth listener */
    size_t len;          /**< length of data */
} AJ_Credential;

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif
