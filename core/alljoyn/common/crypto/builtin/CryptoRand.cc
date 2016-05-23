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
/**
 * @file
 *
 * Secure random number generator
 *
 * CTR DRBG is implemented using algorithms described in the
 * NIST SP 800-90A standard, which can be found at
 * http://csrc.nist.gov/publications/nistpubs/800-90A/SP800-90A.pdf
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

#include <qcc/platform.h>

#include <qcc/Crypto.h>
#include "Crypto.h"

#include <Status.h>

#include <sys/types.h>

using namespace qcc;

#define QCC_MODULE  "CRYPTO"

struct Crypto_DRBG::Context {
    uint8_t v[Crypto_DRBG::OUTLEN];
    uint8_t k[Crypto_DRBG::KEYLEN];
    uint32_t c;
};

// One instance per application
static Crypto_DRBG* drbgctx = NULL;

static uint32_t PlatformEntropy(uint8_t* data, uint32_t size)
{
    FILE* f = fopen("/dev/urandom", "r");
    if (NULL == f) {
        return 0;
    }
    size = fread(data, sizeof (uint8_t), size, f);
    fclose(f);
    return size;
}

static void Increment(uint8_t* data, size_t size)
{
    while (size--) {
        data[size]++;
        if (data[size]) {
            break;
        }
    }
}

Crypto_DRBG::Crypto_DRBG()
{
    ctx = new Context();
    if (ctx) {
        memset(ctx, 0, sizeof (Context));
    }
}

Crypto_DRBG::~Crypto_DRBG()
{
    if (ctx) {
        memset(ctx, 0, sizeof (Context));
        delete ctx;
    }
}

QStatus Crypto_DRBG::Seed(uint8_t* seed, size_t size)
{
    if (SEEDLEN != size) {
        return ER_CRYPTO_ERROR;
    }
    Update(seed);
    ctx->c = 1;
    return ER_OK;
}

QStatus Crypto_DRBG::Generate(uint8_t* rand, size_t size)
{
    uint8_t data[SEEDLEN];
    size_t copy;
    Crypto_AES::Block block;

    if (RESEED_COUNT < ctx->c) {
        /*
         * If counter is at least RESEED_COUNT,
         * attempt seeding. Pass on error, try next call.
         */
        copy = PlatformEntropy(data, sizeof (data));
        if (sizeof (data) == copy) {
            Seed(data, sizeof (data));
        }
    }

    KeyBlob key(ctx->k, KEYLEN, KeyBlob::AES);
    Crypto_AES aes(key, Crypto_AES::ECB_ENCRYPT);
    while (size) {
        Increment(ctx->v, OUTLEN);
        copy = (size < OUTLEN) ? size : OUTLEN;
        aes.Encrypt(ctx->v, OUTLEN, &block, 1);
        memcpy(rand, block.data, copy);
        rand += copy;
        size -= copy;
    }
    memset(data, 0, SEEDLEN);
    Update(data);
    ctx->c++;

    return ER_OK;
}

void Crypto_DRBG::Update(uint8_t* data)
{
    QStatus status;
    size_t i = 0;
    uint8_t tmp[SEEDLEN];
    uint8_t* t = tmp;
    Crypto_AES::Block block;

    KeyBlob key(ctx->k, KEYLEN, KeyBlob::AES);
    Crypto_AES aes(key, Crypto_AES::ECB_ENCRYPT);
    for (i = 0; i < SEEDLEN; i += OUTLEN) {
        Increment(ctx->v, OUTLEN);
        status = aes.Encrypt(ctx->v, OUTLEN, &block, 1);
        if (status != ER_OK) {
            QCC_LogError(status, ("Encryption failed"));
        }
        assert(ER_OK == status);
        memcpy(t, block.data, OUTLEN);
        t += OUTLEN;
    }

    for (i = 0; i < SEEDLEN; i++) {
        tmp[i] ^= data[i];
    }

    memcpy(ctx->k, tmp, KEYLEN);
    memcpy(ctx->v, tmp + KEYLEN, OUTLEN);
}

QStatus qcc::Crypto_GetRandomBytes(uint8_t* data, size_t len)
{
    QStatus status = ER_CRYPTO_ERROR;

    if (NULL != data) {
        status = drbgctx->Generate(data, len);
    }

    return status;
}

QStatus Crypto::Init()
{
    uint8_t seed[Crypto_DRBG::SEEDLEN];
    size_t size;

    if (NULL == drbgctx) {
        drbgctx = new Crypto_DRBG;
    }
    /* Initial seeding, fail on error */
    size = PlatformEntropy(seed, sizeof (seed));
    if (sizeof (seed) == size) {
        drbgctx->Seed(seed, sizeof (seed));
    } else {
        QCC_DbgHLPrintf(("Low entropy: %" PRIuSIZET " (requested %" PRIuSIZET ")\n", size, sizeof (seed)));
        return ER_CRYPTO_ERROR;
    }

    ClearMemory(seed, sizeof (seed));
    return ER_OK;
}

void Crypto::Shutdown() {
    delete drbgctx;
    drbgctx = NULL;
}
