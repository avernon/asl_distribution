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
#ifndef _AJ_AUTHENTICATION_H
#define _AJ_AUTHENTICATION_H

/**
 * @file aj_authentication.h
 * @defgroup aj_authentication Implementation of Authentication mechanisms
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

#include <ajtcl/aj_bus.h>
#include <ajtcl/aj_config.h>
#include <ajtcl/aj_target.h>
#include <ajtcl/aj_cert.h>
#include <ajtcl/aj_crypto_sha2.h>

#ifdef __cplusplus
extern "C" {
#endif

/* The key exchange is in the 16 MSB */
#define AUTH_KEYX_ECDHE        0x00400000

/* The key authentication suite is in the 16 LSB */
#define AUTH_SUITE_ECDHE_NULL  (AUTH_KEYX_ECDHE | 0x0001)
#define AUTH_SUITE_ECDHE_PSK   (AUTH_KEYX_ECDHE | 0x0002)
#define AUTH_SUITE_ECDHE_ECDSA (AUTH_KEYX_ECDHE | 0x0004)

#define AJ_AUTH_SUITES_NUM     3    /**< Number of supported authentication suites */

#define AUTH_CLIENT            0
#define AUTH_SERVER            1

#define HASH_MSG_UNMARSHALED   ((uint8_t)0)
#define HASH_MSG_MARSHALED     ((uint8_t)1)

/*
 * We now define two versions of conversation hash: one that only hashes
 * things inside KeyExchanger, used in authentication versions 3 and below, and
 * the entire authentication conversation, used starting with version 4. These
 * constants are used internally for calls to UpdateHash to indicate which
 * version of the conversation hash a particular call pertains to.
 *
 * To stay consistent with the authentication version numbers, these are called
 * V1 and V4.
 */
#define CONVERSATION_V1 ((uint32_t)0x0000)
#define CONVERSATION_V4 ((uint32_t)0x0004)

/* The authentication conversation version is stored in the upper 16
 * bits of the version value, and the keygen version is stored in the
 * lower 16 bits
 */
#define AJ_UNPACK_AUTH_VERSION(v)   ((v) >> 16)
#define AJ_UNPACK_KEYGEN_VERSION(v) ((v) & 0xFFFF)

typedef struct _KeyExchangeContext {
    AJ_ECCPublicKey pub;
    AJ_ECCPrivateKey prv;
} KeyExchangeContext;

/**
 * Context for PSK authentication
 * Memory is not allocated and copied
 * The pointer addresses memory that exists in the lifetime of its usage
 */
typedef struct _PSKContext {
    uint8_t* hint;                                 /**< PSK hint */
    size_t size;                                   /**< Size of PSK hint */
} PSKContext;

typedef struct _ECDSAContext {
    AJ_ECCPublicKey* key;                          /**< Array of public keys (subject + issuers) */
    size_t num;                                    /**< Number of public keys */
    uint8_t manifest[AJ_SHA256_DIGEST_LENGTH];     /**< Manifest digest */
    size_t size;                                   /**< Manifest size */
} ECDSAContext;

typedef struct _KeyAuthenticationContext {
    PSKContext psk;                                /**< Context for PSK authentication */
    ECDSAContext ecdsa;                            /**< Context for ECDSA authentication */
} KeyAuthenticationContext;

/**
 * Authentication context
 */
typedef struct _AJ_AuthenticationContext {
    AJ_BusAttachment* bus;                         /**< Bus attachement - required for auth callbacks */
    uint8_t role;                                  /**< Role (client or server) */
    uint32_t suite;                                /**< Authentication suite */
    uint32_t version;                              /**< Protocol version */
    AJ_SHA256_Context* hash;                       /**< Running hash of exchanged messages */
    KeyExchangeContext kectx;                      /**< Context for key exchange step */
    KeyAuthenticationContext kactx;                /**< Context for key authentication step */
    uint8_t mastersecret[AJ_MASTER_SECRET_LEN];    /**< Master secret */
    uint32_t expiration;                           /**< Master secret expiration */
    uint16_t slot;                                 /**< NVRAM slot of membership certificate */
    uint8_t code;                                  /**< Send Membership code (NONE, MORE, LAST) */
    uint8_t digest[AJ_SHA256_DIGEST_LENGTH];       /**< Conversation digest */
} AJ_AuthenticationContext;

/**
 * Marshal a key exchange message
 *
 * @param ctx          The authentication context
 * @param msg          The outgoing message
 *
 * @return
 *         - AJ_OK on success
 *         - An error status otherwise
 */
AJ_Status AJ_KeyExchangeMarshal(AJ_AuthenticationContext* ctx, AJ_Message* msg);

/**
 * Unmarshal a key exchange message
 *
 * @param ctx          The authentication context
 * @param msg          The incoming message
 *
 * @return
 *         - AJ_OK on success
 *         - An error status otherwise
 */
AJ_Status AJ_KeyExchangeUnmarshal(AJ_AuthenticationContext* ctx, AJ_Message* msg);

/**
 * Marshal a key authentication message
 *
 * @param ctx          The authentication context
 * @param msg          The outgoing message
 *
 * @return
 *         - AJ_OK on success
 *         - An error status otherwise
 */
AJ_Status AJ_KeyAuthenticationMarshal(AJ_AuthenticationContext* ctx, AJ_Message* msg);

/**
 * Unmarshal a key authentication message
 *
 * @param ctx          The authentication context
 * @param msg          The incoming message
 *
 * @return
 *         - AJ_OK on success
 *         - An error status otherwise
 */
AJ_Status AJ_KeyAuthenticationUnmarshal(AJ_AuthenticationContext* ctx, AJ_Message* msg);

/**
 * Check if an authentication suite is available
 *
 * @param bus          The bus attachment
 * @param suite        The authentication suite to check
 * @param version      The authentication protocol version
 *
 * @return  Return true or false
 */
uint8_t AJ_IsSuiteEnabled(AJ_BusAttachment* bus, uint32_t suite, uint32_t version);

/**
 * Enable an authentication suite
 *
 * @param bus          The bus attachment
 * @param suite        The authentication suite to enable
 */
void AJ_EnableSuite(AJ_BusAttachment* bus, uint32_t suite);


/**
 * Initialize/reset a conversation hash
 *
 * @param ctx          The authentication context
 *
 * @return
 *         - AJ_OK on success
 *         - An error status otherwise
 */
AJ_Status AJ_ConversationHash_Initialize(AJ_AuthenticationContext* ctx);

/**
 * Update the conversation hash with a uint8_t
 *
 * @param ctx                   The authentication context
 * @param conversationVersion   The minimum authentication version which applies to this update
 * @param byte                  The byte to hash
 *
 */
void AJ_ConversationHash_Update_UInt8(AJ_AuthenticationContext* ctx, uint32_t conversationVersion, uint8_t byte);

/**
 * Update the conversation hash with a byte array
 *
 * @param ctx                   The authentication context
 * @param conversationVersion   The minimum authentication version which applies to this update
 * @param buf                   The input array to hash
 * @param bufSize               The size of buf
 *
 */
void AJ_ConversationHash_Update_UInt8Array(AJ_AuthenticationContext* ctx, uint32_t conversationVersion, const uint8_t* buf, size_t bufSize);

/**
 * Update the conversation hash with a string. This function does not assume a null-terminated
 * string; it will hash exactly the number of characters indicated by strSize.
 *
 * @param ctx                   The authentication context
 * @param conversationVersion   The minimum authentication version which applies to this update
 * @param str                   The string content to hash
 * @param strSize               The length of the string
 *
 */
void AJ_ConversationHash_Update_String(AJ_AuthenticationContext* ctx, uint32_t conversationVersion, const char* str, size_t strSize);

/**
 * Update the conversation hash with a message. If the message has been created locally with calls to AJ_Marshal*
 * functions, this function must be called BEFORE AJ_DeliverMsg or AJ_DeliverMsgPartial is called on it.
 *
 * @param ctx                   The authentication context
 * @param conversationVersion   The minimum authentication version which applies to this update
 * @param msg                   The pointer to a message that was unmarshaled by an earlier call to AJ_UnmarshalMsg
 *                              or created by calls to AJ_Marshal*
 * @param isMarshaledMessage    1 if msg was created locally through AJ_Marshal* calls, or 0 if received
 *                              through a call to AJ_UnmarshalMsg
 *
 */
void AJ_ConversationHash_Update_Message(AJ_AuthenticationContext* ctx, uint32_t conversationVersion, AJ_Message* msg, uint8_t isMarshaledMessage);

/**
 * Get the conversation hash
 *
 * @param ctx           The authentication context
 *
 * @return
 *         - AJ_OK on success
 *         - An error status otherwise
 */
AJ_Status AJ_ConversationHash_GetDigest(AJ_AuthenticationContext* ctx);

/**
 * Reset the conversation hash
 *
 * @param ctx           The authentication context
 *
 * @return
 *         - AJ_OK on success
 *         - An error status otherwise
 */
AJ_Status AJ_ConversationHash_Reset(AJ_AuthenticationContext* ctx);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif
