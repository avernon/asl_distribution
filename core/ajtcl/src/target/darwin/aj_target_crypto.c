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
#define AJ_MODULE TARGET_CRYPTO

#include <ajtcl/aj_target.h>
#include <ajtcl/aj_crypto.h>
#include <ajtcl/aj_crypto_aes_priv.h>
#include <ajtcl/aj_crypto_drbg.h>
#include <ajtcl/aj_debug.h>

/**
 * Turn on per-module debug printing by setting this variable to non-zero value
 * (usually in debugger).
 */
#ifndef NDEBUG
uint8_t dbgTARGET_CRYPTO = 0;
#endif

/*
 * Context for AES-128 CTR DRBG
 */
static CTR_DRBG_CTX drbgctx;

uint32_t AJ_PlatformEntropy(uint8_t* data, uint32_t size)
{
    FILE* f = fopen("/dev/urandom", "r");
    if (NULL == f) {
        return 0;
    }
    size = fread(data, sizeof (uint8_t), size, f);
    fclose(f);
    return size;
}

void AJ_RandBytes(uint8_t* rand, uint32_t size)
{
    AJ_Status status = AJ_ERR_SECURITY;
    uint8_t seed[SEEDLEN];

    if (rand && size) {
        status = AES_CTR_DRBG_Generate(&drbgctx, rand, size);
        if (AJ_OK != status) {
            // Reseed required
            AJ_PlatformEntropy(seed, sizeof (seed));
            AES_CTR_DRBG_Reseed(&drbgctx, seed, sizeof (seed));
            status = AES_CTR_DRBG_Generate(&drbgctx, rand, size);
        }
    } else {
        // This is the first call to initialize
        size = AJ_PlatformEntropy(seed, sizeof (seed));
        drbgctx.df = (SEEDLEN == size) ? 0 : 1;
        AES_CTR_DRBG_Instantiate(&drbgctx, seed, sizeof (seed), drbgctx.df);
    }
}
