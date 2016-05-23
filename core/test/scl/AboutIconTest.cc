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

#include <gtest/gtest.h>
#include <alljoyn/AboutIconObj.h>
#include <alljoyn/AboutIconProxy.h>
#include <alljoyn/BusAttachment.h>
#include <BusInternal.h>

using namespace ajn;

static const size_t MAX_ICON_SIZE_IN_BYTES = ALLJOYN_MAX_ARRAY_LEN;
static const uint8_t ICON_BYTE = 0x11;

class LargeIcon {
  private:
    uint8_t* iconByteArrayPtr;
    size_t iconSize;

  public:

    LargeIcon() : iconSize(0)
    {

        iconByteArrayPtr = new uint8_t[MAX_ICON_SIZE_IN_BYTES];
        if (iconByteArrayPtr) {
            for (size_t iconByte = 0; iconByte < MAX_ICON_SIZE_IN_BYTES; iconByte++) {
                iconByteArrayPtr[iconByte] = ICON_BYTE;
            }
            iconSize = MAX_ICON_SIZE_IN_BYTES;
        }
    }

    LargeIcon(size_t icon_size) : iconSize(0)
    {

        iconByteArrayPtr = new uint8_t[icon_size];
        if (iconByteArrayPtr) {
            for (size_t iconByte = 0; iconByte < icon_size; iconByte++) {
                iconByteArrayPtr[iconByte] = ICON_BYTE;
            }
            iconSize = icon_size;
        }
    }

    ~LargeIcon()
    {
        if (iconByteArrayPtr) {
            delete [] iconByteArrayPtr;
            iconByteArrayPtr = NULL;
            iconSize = 0;
        }

    }

    uint8_t* getLargeIconArray()
    {
        return iconByteArrayPtr;
    }

    size_t getIconSize()
    {
        return iconSize;
    }
};

TEST(AboutIconTest, isAnnounced) {
    QStatus status = ER_FAIL;
    BusAttachment busAttachment("AboutIconTest", true);
    status = busAttachment.Start();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    status = busAttachment.Connect();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    AboutIconObj aboutIcon(busAttachment, "", "http://www.example.com", NULL, (size_t)0);

    MsgArg aodArg;
    status = busAttachment.GetInternal().GetAnnouncedObjectDescription(aodArg);
    AboutObjectDescription aod;
    aod.CreateFromMsgArg(aodArg);

    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    EXPECT_TRUE(aod.HasPath("/About/DeviceIcon"));
    EXPECT_TRUE(aod.HasInterface("org.alljoyn.Icon"));
    EXPECT_TRUE(aod.HasInterface("/About/DeviceIcon", "org.alljoyn.Icon"));

    busAttachment.Stop();
    busAttachment.Join();
}

TEST(AboutIconTest, GetUrl) {
    QStatus status = ER_FAIL;
    BusAttachment serviceBus("AboutIconTest Service");
    status = serviceBus.Start();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    status = serviceBus.Connect();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    AboutIconObj aboutIcon(serviceBus, "", "http://www.example.com", NULL, (size_t)0);

    BusAttachment clientBus("AboutIconTest Client");
    status = clientBus.Start();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    status = clientBus.Connect();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    AboutIconProxy aiProxy(clientBus);
    qcc::String url;
    aiProxy.GetUrl(serviceBus.GetUniqueName().c_str(), url, 0);
    EXPECT_STREQ("http://www.example.com", url.c_str());
}

TEST(AboutIconTest, GetVersion) {
    QStatus status = ER_FAIL;
    BusAttachment serviceBus("AboutIconTest Service");
    status = serviceBus.Start();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    status = serviceBus.Connect();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    AboutIconObj aboutIcon(serviceBus, "", "http://www.example.com", NULL, (size_t)0);

    BusAttachment clientBus("AboutIconTest Client");
    status = clientBus.Start();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    status = clientBus.Connect();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    AboutIconProxy aiProxy(clientBus);
    uint16_t version;
    aiProxy.GetVersion(serviceBus.GetUniqueName().c_str(), version, 0);
    EXPECT_EQ(aboutIcon.VERSION, version);
}

TEST(AboutIconTest, GetIcon) {
    QStatus status = ER_FAIL;
    BusAttachment serviceBus("AboutIconTest Service");
    status = serviceBus.Start();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    status = serviceBus.Connect();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    uint8_t aboutIconContent[] = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00,
                                   0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x0A,
                                   0x00, 0x00, 0x00, 0x0A, 0x08, 0x02, 0x00, 0x00, 0x00, 0x02,
                                   0x50, 0x58, 0xEA, 0x00, 0x00, 0x00, 0x04, 0x67, 0x41, 0x4D,
                                   0x41, 0x00, 0x00, 0xAF, 0xC8, 0x37, 0x05, 0x8A, 0xE9, 0x00,
                                   0x00, 0x00, 0x19, 0x74, 0x45, 0x58, 0x74, 0x53, 0x6F, 0x66,
                                   0x74, 0x77, 0x61, 0x72, 0x65, 0x00, 0x41, 0x64, 0x6F, 0x62,
                                   0x65, 0x20, 0x49, 0x6D, 0x61, 0x67, 0x65, 0x52, 0x65, 0x61,
                                   0x64, 0x79, 0x71, 0xC9, 0x65, 0x3C, 0x00, 0x00, 0x00, 0x18,
                                   0x49, 0x44, 0x41, 0x54, 0x78, 0xDA, 0x62, 0xFC, 0x3F, 0x95,
                                   0x9F, 0x01, 0x37, 0x60, 0x62, 0xC0, 0x0B, 0x46, 0xAA, 0x34,
                                   0x40, 0x80, 0x01, 0x00, 0x06, 0x7C, 0x01, 0xB7, 0xED, 0x4B,
                                   0x53, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44,
                                   0xAE, 0x42, 0x60, 0x82 };
    qcc::String mimeType("image/png");

    AboutIconObj aboutIcon(serviceBus, mimeType, "", aboutIconContent, sizeof(aboutIconContent) / sizeof(aboutIconContent[0]));

    BusAttachment clientBus("AboutIconTest Client");
    status = clientBus.Start();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    status = clientBus.Connect();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    AboutIconProxy aiProxy(clientBus);

    AboutIconProxy::Icon icon;
    aiProxy.GetIcon(serviceBus.GetUniqueName().c_str(), icon, 0);
    EXPECT_STREQ("image/png", icon.mimetype.c_str());
    ASSERT_EQ(sizeof(aboutIconContent) / sizeof(aboutIconContent[0]), icon.contentSize);
    for (size_t i = 0; i < icon.contentSize; ++i) {
        EXPECT_EQ(aboutIconContent[i], icon.content[i]);
    }

    size_t icon_size;
    aiProxy.GetSize(serviceBus.GetUniqueName().c_str(), icon_size, 0);
    EXPECT_EQ(sizeof(aboutIconContent) / sizeof(aboutIconContent[0]), icon_size);

    qcc::String retMimeType;
    aiProxy.GetMimeType(serviceBus.GetUniqueName().c_str(), retMimeType, 0);
    EXPECT_STREQ(mimeType.c_str(), retMimeType.c_str());
}

TEST(AboutIconTest, GetLargeIcon) {
    QStatus status = ER_FAIL;

    LargeIcon myIcon;

    uint8_t* aboutIconContent = myIcon.getLargeIconArray();
    size_t icon_size = myIcon.getIconSize();

    ASSERT_TRUE(NULL != aboutIconContent && icon_size == MAX_ICON_SIZE_IN_BYTES);

    BusAttachment serviceBus("AboutLargeIconTest Service");
    status = serviceBus.Start();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    status = serviceBus.Connect();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);


    qcc::String mimeType("image/png");

    AboutIconObj aboutIcon(serviceBus, mimeType, "", aboutIconContent, MAX_ICON_SIZE_IN_BYTES);

    BusAttachment clientBus("AboutLargeIconTest Client");
    status = clientBus.Start();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    status = clientBus.Connect();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    AboutIconProxy aiProxy(clientBus);

    AboutIconProxy::Icon icon;
    status = aiProxy.GetIcon(serviceBus.GetUniqueName().c_str(), icon, 0);
    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    EXPECT_STREQ("image/png", icon.mimetype.c_str());
    ASSERT_EQ(MAX_ICON_SIZE_IN_BYTES, icon.contentSize);

    for (size_t i = 0; i < icon.contentSize; ++i) {
        EXPECT_EQ(aboutIconContent[i], icon.content[i]);
    }

    aiProxy.GetSize(serviceBus.GetUniqueName().c_str(), icon_size, 0);
    EXPECT_EQ(MAX_ICON_SIZE_IN_BYTES, icon_size);

    qcc::String retMimeType;
    aiProxy.GetMimeType(serviceBus.GetUniqueName().c_str(), retMimeType, 0);
    EXPECT_STREQ(mimeType.c_str(), retMimeType.c_str());

}
//ASACORE-944
TEST(AboutIconTest, DISABLED_GetLargeIcon_Negative) {
    QStatus status = ER_FAIL;

    // icon over array limit
    LargeIcon myIcon((MAX_ICON_SIZE_IN_BYTES + 1));

    uint8_t* aboutIconContent = myIcon.getLargeIconArray();
    size_t icon_size = myIcon.getIconSize();

    ASSERT_TRUE((NULL != aboutIconContent) && (icon_size == MAX_ICON_SIZE_IN_BYTES + 1));

    BusAttachment serviceBus("AboutLargeIconTest Service");
    status = serviceBus.Start();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    status = serviceBus.Connect();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    qcc::String mimeType("image/png");

    // Ideally, there should be API like setIconContent which return QStatus
    AboutIconObj aboutIcon(serviceBus, mimeType, "", aboutIconContent, (MAX_ICON_SIZE_IN_BYTES + 1));


    BusAttachment clientBus("AboutLargeIconTest Client");
    status = clientBus.Start();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    status = clientBus.Connect();
    ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    AboutIconProxy aiProxy(clientBus);

    AboutIconProxy::Icon icon;
    // Should fail because icon is over alljoyn array limit
    status = aiProxy.GetIcon(serviceBus.GetUniqueName().c_str(), icon, 0);

    EXPECT_NE(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    EXPECT_STRNE("image/png", icon.mimetype.c_str());

    EXPECT_NE((MAX_ICON_SIZE_IN_BYTES + 1), icon.contentSize);

    aiProxy.GetSize(serviceBus.GetUniqueName().c_str(), icon_size, 0);
    EXPECT_NE((MAX_ICON_SIZE_IN_BYTES + 1), icon_size);

    qcc::String retMimeType;
    aiProxy.GetMimeType(serviceBus.GetUniqueName().c_str(), retMimeType, 0);
    EXPECT_STREQ(mimeType.c_str(), retMimeType.c_str());

}
