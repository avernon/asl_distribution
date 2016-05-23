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

#include <alljoyn/BusAttachment.h>
#include "BusInternal.h"

/* Header files included for Google Test Framework */
#include <gtest/gtest.h>
#include "../ajTestCommon.h"

using namespace std;
using namespace qcc;
using namespace ajn;

/*
 * ASACORE-880
 */
TEST(BusAttachmentTest, RegisterTwoBusObjectsWithSamePathFails)
{
    BusAttachment bus(NULL);
    BusObject busObj0("/parent/child");
    BusObject busObj1("/parent/child");
    EXPECT_EQ(ER_OK, bus.RegisterBusObject(busObj0));
    EXPECT_NE(ER_OK, bus.RegisterBusObject(busObj1));
}

TEST(BusAttachmentTest, RegisterChildThenParentBusObjectSucceeds)
{
    BusAttachment bus(NULL);
    BusObject child("/parent/child");
    BusObject parent("/parent");
    EXPECT_EQ(ER_OK, bus.RegisterBusObject(child));
    EXPECT_EQ(ER_OK, bus.RegisterBusObject(parent));
}

/*
 * ASACORE-123
 */
class TestDBusObj : public ProxyBusObject {
  public:
    virtual QStatus MethodCall(const char* ifaceName, const char* methodName, const MsgArg* args, size_t numArgs,
                               Message& replyMsg, uint32_t timeout = DefaultCallTimeout, uint8_t flags = 0) const {
        return ER_OK;
    }
};

class TestBusAttachment : public BusAttachment {
  public:
    class TestInternal : public Internal {
      public:
        TestInternal(TestBusAttachment& bus, TransportFactoryContainer& factories) :
            Internal(NULL, bus, factories, NULL, false, NULL, 4), bus(bus) { }
        virtual QStatus TransportsStart() { return ER_OK; }
        virtual QStatus TransportsStop() { return ER_OK; }
        virtual QStatus TransportsJoin() { return ER_OK; }
        virtual QStatus TransportConnect(const char* requestedConnectSpec, qcc::String& actualConnectSpec) {
            actualConnectSpec = requestedConnectSpec;
            return ER_OK;
        }
        virtual QStatus TransportDisconnect(const char* connectSpec) { return ER_OK; }
        virtual const ProxyBusObject& GetDBusProxyObj() const { return dbusObj; }
        virtual QStatus RegisterSignalHandler(MessageReceiver* receiver, MessageReceiver::SignalHandler signalHandler,
                                              const InterfaceDescription::Member* member, const char* matchRule) {
            if (member->name == "NameOwnerChanged") {
                ++bus.nameOwnerChangedHandlerRegistered;
            }
            return ER_OK;
        }
        virtual QStatus UnregisterSignalHandler(MessageReceiver* receiver, MessageReceiver::SignalHandler signalHandler,
                                                const InterfaceDescription::Member* member, const char* matchRule) {
            if (member->name == "NameOwnerChanged") {
                --bus.nameOwnerChangedHandlerRegistered;
            }
            return ER_OK;
        }

        TestBusAttachment& bus;
        TestDBusObj dbusObj;
    };

    TransportFactoryContainer factories;
    int nameOwnerChangedHandlerRegistered;

    TestBusAttachment() : BusAttachment(new TestInternal(*this, factories), 4), nameOwnerChangedHandlerRegistered(0) { }
};

TEST(BusAttachmentTest, SingleSignalRegistrationWhenBusAttachmentIsLocallyDisconnectedThenConnected)
{
    TestBusAttachment bus;
    ASSERT_EQ(ER_OK, bus.Start());
    ASSERT_EQ(ER_OK, bus.Connect());

    /* Locally disconnect BusAttachment */
    ASSERT_EQ(ER_OK, bus.Disconnect());

    /* Reconnect and verify that there is no duplicate signal handler registration */
    ASSERT_EQ(ER_OK, bus.Connect());
    EXPECT_EQ(1, bus.nameOwnerChangedHandlerRegistered);
}

TEST(BusAttachmentTest, SingleSignalRegistrationWhenBusAttachmentIsRemotelyDisconnectedThenConnected)
{
    TestBusAttachment bus;
    ASSERT_EQ(ER_OK, bus.Start());
    ASSERT_EQ(ER_OK, bus.Connect());

    /* Remotely disconnect BusAttachment */
    bus.GetInternal().NonLocalEndpointDisconnected();

    /* Reconnect and verify that there is no duplicate signal handler registration */
    ASSERT_EQ(ER_OK, bus.Connect());
    EXPECT_EQ(1, bus.nameOwnerChangedHandlerRegistered);
}
