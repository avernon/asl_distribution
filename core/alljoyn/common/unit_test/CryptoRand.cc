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
 * This file tests AES-128 CTR DRBG (no prediction resistance)
 * Known answer tests taken from
 * http://csrc.nist.gov/groups/STM/cavp/documents/drbg/drbgtestvectors.zip
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
#include <qcc/Debug.h>
#include <qcc/String.h>
#include <qcc/StringUtil.h>
#include <qcc/Util.h>

#include <Status.h>

#include <gtest/gtest.h>

using namespace qcc;
using namespace std;

typedef struct {
    const char* seed;      /* Seed input */
    const char* reseed;    /* Reseed input */
    const char* rand;      /* Output */
} TEST_CASE;

static TEST_CASE const test_nodf[] = {
    // no DF - no reseed
    {
        "ce50f33da5d4c1d3d4004eb35244b7f2cd7f2e5076fbf6780a7ff634b249a5fc",
        "",
        "6545c0529d372443b392ceb3ae3a99a30f963eaf313280f1d1a1e87f9db373d3"
        "61e75d18018266499cccd64d9bbb8de0185f213383080faddec46bae1f784e5a",
    },
    {
        "a385f70a4d450321dfd18d8379ef8e7736fee5fbf0a0aea53b76696094e8aa93",
        "",
        "1a062553ab60457ed1f1c52f5aca5a3be564a27545358c112ed92c6eae2cb759"
        "7cfcc2e0a5dd81c5bfecc941da5e8152a9010d4845170734676c8c1b6b3073a5",
    },
    // no DF - reseed
    {
        "ed1e7f21ef66ea5d8e2a85b9337245445b71d6393a4eecb0e63c193d0f72f9a9",
        "303fb519f0a4e17d6df0b6426aa0ecb2a36079bd48be47ad2a8dbfe48da3efad",
        "f80111d08e874672f32f42997133a5210f7a9375e22cea70587f9cfafebe0f6a"
        "6aa2eb68e7dd9164536d53fa020fcab20f54caddfab7d6d91e5ffec1dfd8deaa",
    },
    {
        "eab5a9f23ceac9e4195e185c8cea549d6d97d03276225a7452763c396a7f70bf",
        "4258765c65a03af92fc5816f966f1a6644a6134633aad2d5d19bd192e4c1196a",
        "2915c9fabfbf7c62d68d83b4e65a239885e809ceac97eb8ef4b64df59881c277"
        "d3a15e0e15b01d167c49038fad2f54785ea714366d17bb2f8239fd217d7e1cba",
    },
};

TEST(DRBG_Test, DRBG_Test_Vector) {
    QStatus status = ER_OK;
    size_t i;
    size_t size;
    uint8_t data[4096];

    for (i = 0; i < ArraySize(test_nodf); i++) {
        Crypto_DRBG ctx;
        size = HexStringToBytes(test_nodf[i].seed, data, sizeof (data));
        status = ctx.Seed(data, size);
        EXPECT_EQ(ER_OK, status) << "  Seed error " << QCC_StatusText(status);

        if (strlen(test_nodf[i].reseed)) {
            size = HexStringToBytes(test_nodf[i].reseed, data, sizeof (data));
            status = ctx.Seed(data, size);
            EXPECT_EQ(ER_OK, status) << "  Seed error " << QCC_StatusText(status);
        }

        size = strlen(test_nodf[i].rand) / 2;
        status = ctx.Generate(data, size);
        EXPECT_EQ(ER_OK, status) << "  Generate error " << QCC_StatusText(status);
        status = ctx.Generate(data, size);
        EXPECT_EQ(ER_OK, status) << "  Generate error " << QCC_StatusText(status);

        String hex = BytesToHexString(data, size, true);
        EXPECT_STREQ(test_nodf[i].rand, hex.c_str());
    }

    status = Crypto_GetRandomBytes(NULL, 0);
    EXPECT_EQ(ER_CRYPTO_ERROR, status) << "  Output buffer check failed " << QCC_StatusText(status);
    status = Crypto_GetRandomBytes(data, sizeof(data));
    EXPECT_EQ(ER_OK, status) << "  Generate error " << QCC_StatusText(status);
}
