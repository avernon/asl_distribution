/******************************************************************************
 *
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

#include <gtest/gtest.h>
#include <qcc/KeyInfoECC.h>

using namespace qcc;

TEST(KeyInfoECCTest, constructor) {
    KeyInfoECC keyInfoECC;
    EXPECT_EQ(KeyInfo::FORMAT_ALLJOYN, keyInfoECC.GetFormat());
    EXPECT_EQ((uint8_t)Crypto_ECC::ECC_NIST_P256, keyInfoECC.GetCurve());
    EXPECT_EQ((uint8_t)SigInfo::ALGORITHM_ECDSA_SHA_256, keyInfoECC.GetAlgorithm());
}

TEST(KeyInfoECCTest, export_import) {
    KeyInfoECC keyInfoECC;

    uint8_t dummyKeyId[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
    keyInfoECC.SetKeyId(dummyKeyId, 10);

    size_t exportSize = keyInfoECC.GetExportSize();
    // export size is KeyInfo exportSize + byte for the curve type
    EXPECT_EQ(static_cast<KeyInfo>(keyInfoECC).GetExportSize() + 1 * sizeof(uint8_t), exportSize);

    uint8_t* buf = new uint8_t[exportSize];
    EXPECT_EQ(ER_OK, keyInfoECC.Export(buf));

    KeyInfoECC importedKey;
    EXPECT_EQ(ER_OK, importedKey.Import(buf, exportSize));
    EXPECT_EQ(keyInfoECC.GetExportSize(), importedKey.GetExportSize());
    EXPECT_EQ(keyInfoECC.GetFormat(), importedKey.GetFormat());
    EXPECT_TRUE(keyInfoECC == importedKey);
    delete [] buf;
}

//Verify the compiler generated copy/assignment operators work as expected
TEST(KeyInfoECCTest, copy_assign)
{
    KeyInfoECC keyInfoECC;

    uint8_t dummyKeyId[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
    keyInfoECC.SetKeyId(dummyKeyId, 10);

    KeyInfoECC copyKeyInfo(keyInfoECC);
    KeyInfoECC assignedKeyInfo = keyInfoECC;

    EXPECT_TRUE(keyInfoECC == copyKeyInfo);
    EXPECT_TRUE(keyInfoECC == assignedKeyInfo);
    EXPECT_TRUE(copyKeyInfo == assignedKeyInfo);
}

TEST(KeyInfoNISTP256Test, constructor) {
    KeyInfoNISTP256 keyInfoNISTP256;
    EXPECT_EQ(KeyInfo::FORMAT_ALLJOYN, keyInfoNISTP256.GetFormat());
    EXPECT_EQ((uint8_t)Crypto_ECC::ECC_NIST_P256, keyInfoNISTP256.GetCurve());
    EXPECT_EQ((uint8_t)SigInfo::ALGORITHM_ECDSA_SHA_256, keyInfoNISTP256.GetAlgorithm());
}


