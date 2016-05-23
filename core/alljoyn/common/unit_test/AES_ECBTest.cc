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
 * This file tests AES-ECB mode.
 * The known answer tests are taken from http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf
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
#include <qcc/KeyBlob.h>
#include <qcc/String.h>
#include <qcc/StringUtil.h>
#include <qcc/Util.h>

#include <Status.h>

#include <gtest/gtest.h>

using namespace qcc;
using namespace std;

typedef struct {
    const char* key;     /* AES key */
    const char* input;   /* Input text */
    const char* output;  /* Encrypted output for verification */
} TEST_CASE;

static TEST_CASE testVector[] = {
    {
        "000102030405060708090a0b0c0d0e0f",
        "00112233445566778899aabbccddeeff",
        "69c4e0d86a7b0430d8cdb78070b4c55a"
    }
};

TEST(AES_ECBTest, AES_ECB_Test_Vector) {
    QStatus status = ER_OK;
    for (size_t i = 0; i < ArraySize(testVector); i++) {
        uint8_t key[16];
        uint8_t msg[16];

        HexStringToBytes(testVector[i].key, key, sizeof(key));
        HexStringToBytes(testVector[i].input, msg, sizeof(msg));

        KeyBlob kb(key, sizeof(key), KeyBlob::AES);
        Crypto_AES aes(kb, Crypto_AES::ECB_ENCRYPT);

        Crypto_AES::Block* out = new Crypto_AES::Block;
        status = aes.Encrypt(msg, sizeof(msg), out, 1);
        EXPECT_EQ(ER_OK, status) << "  Encryption error " << QCC_StatusText(status)
                                 << " for test #" << (i + 1);

        String output = BytesToHexString(out->data, 16, true);
        EXPECT_STREQ(testVector[i].output, output.c_str()) << "Encrypt verification failure for test #"
                                                           << (i + 1) << output.c_str();
        delete out;
    }
}
