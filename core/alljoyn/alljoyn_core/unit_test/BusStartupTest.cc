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

#include <alljoyn/BusAttachment.h>

#include "ajTestCommon.h"

using namespace ajn;

class BusStartupTest : public testing::Test {
  public:
    BusAttachment* g_msgBus;

    virtual void SetUp() {
        g_msgBus = new BusAttachment("testservices", true);
        QStatus status = g_msgBus->Start();
        ASSERT_EQ(ER_OK, status);
    }

    virtual void TearDown() {
        if (g_msgBus) {
            BusAttachment* deleteMe = g_msgBus;
            g_msgBus = NULL;
            delete deleteMe;
        }
    }
    //Common setup function for all service tests
    QStatus ServiceBusSetup() {
        QStatus status = ER_OK;

        if (!g_msgBus->IsConnected()) {
            /* Connect to the daemon and wait for the bus to exit */
            status = g_msgBus->Connect(ajn::getConnectArg().c_str());
        }

        return status;
    }

};

TEST_F(BusStartupTest, SUCCESS_Start) {
    /*
     * The bus should be started by the setup this is just verifying that it
     * was started.
     */
    EXPECT_TRUE(g_msgBus->IsStarted());
}

TEST_F(BusStartupTest, Fail_Already_Started) {
    QStatus status = ER_OK;
    EXPECT_TRUE(g_msgBus->IsStarted());
    /* Restart the msg bus */
    status = g_msgBus->Start();
    ASSERT_EQ(ER_BUS_BUS_ALREADY_STARTED, status);
}

TEST_F(BusStartupTest, SUCCESS_Connect) {
    QStatus status = g_msgBus->Connect(ajn::getConnectArg().c_str());
    ASSERT_EQ(ER_OK, status);
}

TEST_F(BusStartupTest, Fail_Already_Connected) {
    QStatus status = ER_OK;
    /* Get env vars */
    status = g_msgBus->Connect(ajn::getConnectArg().c_str());
    ASSERT_EQ(ER_OK, status);
    ASSERT_TRUE(g_msgBus->IsConnected());
    /* Connect to the daemon and wait for the bus to exit */
    status = g_msgBus->Connect(ajn::getConnectArg().c_str());
    ASSERT_EQ(ER_BUS_ALREADY_CONNECTED, status);
}
