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

#include <alljoyn/version.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/about/AboutIconService.h>
#include <alljoyn/about/AboutServiceApi.h>
#include <alljoyn/about/AboutPropertyStoreImpl.h>

#include <alljoyn/about/AboutClient.h>
#include <alljoyn/about/AnnouncementRegistrar.h>

#include <qcc/Thread.h>
#include <qcc/GUID.h>

/*
 * This test uses the GUID128 in multiple places to generate a random string.
 * We are using random strings in many of the interface names to prevent multiple
 * tests interfering with one another. Some automated build systems could run this
 * same test on multiple platforms at one time.  Since the names announced could
 * be seen across platforms we want to make the names unique so we know we are
 * responding to an advertisement we have made.
 */

/*
 * The unit test use many busy wait loops.  The busy wait loops were chosen
 * over thread sleeps because of the ease of understanding the busy wait loops.
 * Also busy wait loops do not require any platform specific threading code.
 */
#define WAIT_TIME 5

using namespace ajn;
using namespace services;


class AnnounceHandlerTestSessionPortListener : public SessionPortListener {
    virtual bool AcceptSessionJoiner(SessionPort sessionPort, const char* joiner, const SessionOpts& opts)
    {
        QCC_UNUSED(sessionPort);
        QCC_UNUSED(joiner);
        QCC_UNUSED(opts);
        return true;
    }
};

class AnnounceHandler2Test : public testing::Test {
  public:
    BusAttachment* g_msgBus;

    virtual void SetUp() {

        QStatus status;

        serviceBus = new BusAttachment("announceHandlerTest", true);
        status = serviceBus->Start();
        ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
        status = serviceBus->Connect();
        ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

        AboutServiceApi::Init(*serviceBus, propertyStore);
        EXPECT_TRUE(AboutServiceApi::getInstance() != NULL);

        SessionPort port = 25;
        SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
        AnnounceHandlerTestSessionPortListener listener;
        status = serviceBus->BindSessionPort(port, opts, listener);
        EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

        status = AboutServiceApi::getInstance()->Register(port);
        EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

        status = serviceBus->RegisterBusObject(*AboutServiceApi::getInstance());
        EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    }

    virtual void TearDown() {
        AboutServiceApi::DestroyInstance();
        if (serviceBus) {
            serviceBus->Stop();
            serviceBus->Join();
            BusAttachment* deleteMe = serviceBus;
            serviceBus = NULL;
            delete deleteMe;
        }
    }

    BusAttachment* serviceBus;
    AboutPropertyStoreImpl propertyStore;
};

static bool announceHandlerFlag = false;

class MyAnnounceHandler2 : public ajn::services::AnnounceHandler {

  public:

    virtual void Announce(unsigned short version, unsigned short port, const char* busName, const ObjectDescriptions& objectDescs,
                          const AboutData& aboutData)
    {
        QCC_UNUSED(version);
        QCC_UNUSED(port);
        QCC_UNUSED(busName);
        QCC_UNUSED(objectDescs);
        QCC_UNUSED(aboutData);
        announceHandlerFlag = true;
    }
};
/*
 * This test was created to recreate memory-leak reported for ASACORE-1295
 */
TEST_F(AnnounceHandler2Test, ReceiveAnnouncement_WithEmptyPropertyStore_ThisIsABadConfiguration_PropertyStoreShouldAlwaysBePopulated)
{
    QStatus status;
    announceHandlerFlag = false;
    qcc::GUID128 guid;
    qcc::String ifaceName = "o" + guid.ToShortString() + ".test.AnnounceHandler2Test";
    std::vector<qcc::String> object_interfaces;
    object_interfaces.push_back(ifaceName);
    status = AboutServiceApi::getInstance()->AddObjectDescription("/org/alljoyn/test", object_interfaces);
    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    // receive
    BusAttachment clientBus("Receive Announcement client Test", true);
    status = clientBus.Start();
    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    status = clientBus.Connect();
    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    MyAnnounceHandler2 announceHandler;

    const char* interfaces[1];
    interfaces[0] = ifaceName.c_str();
    AnnouncementRegistrar::RegisterAnnounceHandler(clientBus, announceHandler,
                                                   interfaces, sizeof(interfaces) / sizeof(interfaces[0]));


    status = AboutServiceApi::getInstance()->Announce();
    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    //Wait for a maximum of 10 sec for the Announce Signal.
    for (int msec = 0; msec < 10000; msec += WAIT_TIME) {
        if (announceHandlerFlag) {
            break;
        }
        qcc::Sleep(WAIT_TIME);
    }

    ASSERT_TRUE(announceHandlerFlag);

    AnnouncementRegistrar::UnRegisterAnnounceHandler(clientBus, announceHandler,
                                                     interfaces, sizeof(interfaces) / sizeof(interfaces[0]));

    status = clientBus.Stop();
    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    status = clientBus.Join();
    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
}
