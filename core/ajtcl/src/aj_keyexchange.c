/**
 * @file
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

/**
 * Per-module definition of the current module for debug logging.  Must be defined
 * prior to first inclusion of aj_debug.h
 */
#define AJ_MODULE KEYEXCHANGE

#include <ajtcl/aj_target.h>
#include <ajtcl/aj_debug.h>
#include <ajtcl/aj_keyexchange.h>
#include <ajtcl/aj_crypto_ecc.h>
#include <ajtcl/aj_cert.h>

/**
 * Turn on per-module debug printing by setting this variable to non-zero value
 * (usually in debugger).
 */
#ifndef NDEBUG
uint8_t dbgKEYEXCHANGE = 0;
#endif

/*
 * ECC curve paramaters (version number)
 * In this code, we only support NIST P256
 */
#define ECC_NIST_P256 0

static AJ_Status ECDHE_Init(AJ_SHA256_Context* hash);
static AJ_Status ECDHE_Marshal(AJ_Message* msg);
static AJ_Status ECDHE_Unmarshal(AJ_Message* msg);
static void ECDHE_GetSecret(uint8_t** secret, size_t* secretlen);

AJ_KeyExchange AJ_KeyExchangeECDHE = {
    ECDHE_Init,
    ECDHE_Marshal,
    ECDHE_Unmarshal,
    ECDHE_GetSecret
};

typedef struct _AJ_ECDHEContext {
    AJ_KeyInfo pub;
    AJ_KeyInfo prv;
    uint8_t secret[SHA256_DIGEST_LENGTH];
    AJ_SHA256_Context* hash;
} AJ_ECDHEContext;


static AJ_ECDHEContext ecdhectx;

static AJ_Status ECDHE_Init(AJ_SHA256_Context* hash)
{
    ecdhectx.hash = hash;
    return AJ_KeyInfoGenerate(&ecdhectx.pub, &ecdhectx.prv, KEY_USE_SIG);
}

static AJ_Status ECDHE_Marshal(AJ_Message* msg)
{
    AJ_Status status;

    AJ_InfoPrintf(("AJ_ECDHE_Marshal(msg=%p)\n", msg));

    status = AJ_MarshalVariant(msg, "(yv)");
    status = AJ_KeyInfoMarshal(&ecdhectx.pub, msg, ecdhectx.hash);

    return status;
}

static AJ_Status ECDHE_Unmarshal(AJ_Message* msg)
{
    AJ_Status status;
    AJ_KeyInfo pub;
    char* variant;
    ecc_secret sec;
    uint8_t buf[KEY_ECC_SEC_SZ];
    AJ_SHA256_Context ctx;

    AJ_InfoPrintf(("AJ_ECDHE_Unmarshal(msg=%p)\n", msg));

    status = AJ_UnmarshalVariant(msg, (const char**) &variant);
    if (AJ_OK != status) {
        return status;
    }
    if (0 != strncmp(variant, "(yv)", 4)) {
        return AJ_ERR_INVALID;
    }
    status = AJ_KeyInfoUnmarshal(&pub, msg, ecdhectx.hash);
    if (AJ_OK != status) {
        return status;
    }
    if (KEY_USE_SIG != pub.use) {
        return AJ_ERR_SECURITY;
    }

    status = AJ_GenerateShareSecret(&pub.key.publickey, &ecdhectx.prv.key.privatekey, &sec);
    if (AJ_OK != status) {
        return status;
    }
    AJ_BigvalEncode(&sec.x, buf, KEY_ECC_SZ);
    AJ_BigvalEncode(&sec.y, buf + KEY_ECC_SZ, KEY_ECC_SZ);

    //Hash the point
    AJ_SHA256_Init(&ctx);
    AJ_SHA256_Update(&ctx, (const uint8_t*) buf, sizeof (buf));
    AJ_SHA256_Final(&ctx, ecdhectx.secret);

    return status;
}

static void ECDHE_GetSecret(uint8_t** secret, size_t* secretlen)
{
    AJ_InfoPrintf(("AJ_ECDHE_GetSecret(secret=%p, secretlen=%p)\n", secret, secretlen));

    *secret = ecdhectx.secret;
    *secretlen = sizeof (ecdhectx.secret);
}
