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
#include <qcc/KeyInfo.h>

using namespace qcc;

TEST(KeyInfoTest, Constructor)
{
    {
        KeyInfo keyInfo(KeyInfo::FORMAT_ALLJOYN);
        EXPECT_EQ(KeyInfo::FORMAT_ALLJOYN, keyInfo.GetFormat());
        EXPECT_EQ((size_t)0, keyInfo.GetKeyIdLen());
        EXPECT_TRUE(NULL == keyInfo.GetKeyId());
    }
    {
        KeyInfo keyInfo(KeyInfo::FORMAT_JWK);
        EXPECT_EQ(KeyInfo::FORMAT_JWK, keyInfo.GetFormat());
        EXPECT_EQ((size_t)0, keyInfo.GetKeyIdLen());
        EXPECT_TRUE(NULL == keyInfo.GetKeyId());
    }
    {
        KeyInfo keyInfo(KeyInfo::FORMAT_X509);
        EXPECT_EQ(KeyInfo::FORMAT_X509, keyInfo.GetFormat());
        EXPECT_EQ((size_t)0, keyInfo.GetKeyIdLen());
        EXPECT_TRUE(NULL == keyInfo.GetKeyId());
    }
}

TEST(KeyInfoTest, SetKeyId)
{
    KeyInfo keyInfo(KeyInfo::FORMAT_ALLJOYN);
    EXPECT_EQ(KeyInfo::FORMAT_ALLJOYN, keyInfo.GetFormat());
    EXPECT_EQ((size_t)0, keyInfo.GetKeyIdLen());
    EXPECT_TRUE(NULL == keyInfo.GetKeyId());

    uint8_t dummyKeyId[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
    keyInfo.SetKeyId(dummyKeyId, 10);
    size_t kLen = keyInfo.GetKeyIdLen();
    EXPECT_EQ(10, kLen);
    const uint8_t* kId = keyInfo.GetKeyId();
    for (size_t i = 0; i < kLen; ++i) {
        EXPECT_EQ(dummyKeyId[i], kId[i]);
    }
}

TEST(KeyInfoTest, export_import_Key)
{
    KeyInfo keyInfo(KeyInfo::FORMAT_ALLJOYN);
    EXPECT_EQ(KeyInfo::FORMAT_ALLJOYN, keyInfo.GetFormat());
    EXPECT_EQ((size_t)0, keyInfo.GetKeyIdLen());
    EXPECT_TRUE(NULL == keyInfo.GetKeyId());

    uint8_t dummyKeyId[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
    keyInfo.SetKeyId(dummyKeyId, 10);
    size_t exportSize = keyInfo.GetExportSize();
    // export size is the FormatType + the keylength uint32_t + the number of bytes in the key
    EXPECT_EQ(sizeof(KeyInfo::FormatType) + sizeof(uint32_t) + 10 * sizeof(uint8_t), exportSize);
    uint8_t* buf = new uint8_t[exportSize];
    EXPECT_EQ(ER_OK, keyInfo.Export(buf));

    //The import will fail if the format does not match
    KeyInfo importedKeyBad(KeyInfo::FORMAT_X509);
    EXPECT_EQ(ER_INVALID_DATA, importedKeyBad.Import(buf, exportSize));

    KeyInfo importedKey(KeyInfo::FORMAT_ALLJOYN);
    EXPECT_EQ(ER_OK, importedKey.Import(buf, exportSize));
    EXPECT_EQ(keyInfo.GetExportSize(), importedKey.GetExportSize());
    EXPECT_EQ(keyInfo.GetFormat(), importedKey.GetFormat());
    EXPECT_TRUE(keyInfo == importedKey);
    delete [] buf;
}

TEST(KeyInfoTest, copy_assign)
{
    KeyInfo keyInfo(KeyInfo::FORMAT_ALLJOYN);
    EXPECT_EQ(KeyInfo::FORMAT_ALLJOYN, keyInfo.GetFormat());
    EXPECT_EQ((size_t)0, keyInfo.GetKeyIdLen());
    EXPECT_TRUE(NULL == keyInfo.GetKeyId());

    uint8_t dummyKeyId[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
    keyInfo.SetKeyId(dummyKeyId, 10);

    KeyInfo copyKeyInfo(keyInfo);
    KeyInfo assignedKeyInfo(KeyInfo::FORMAT_X509);
    assignedKeyInfo = keyInfo;

    EXPECT_TRUE(keyInfo == copyKeyInfo);
    EXPECT_TRUE(keyInfo == assignedKeyInfo);
    EXPECT_TRUE(copyKeyInfo == assignedKeyInfo);
}
