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

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <vector>

#include <qcc/String.h>
#include <qcc/Thread.h>

#include <alljoyn/BusAttachment.h>
#include <alljoyn/DBusStd.h>
#include <alljoyn/AllJoynStd.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/MsgArg.h>
#include <alljoyn/version.h>

#include <alljoyn/Status.h>

/* Header files included for Google Test Framework */
#include <gtest/gtest.h>
#include "ajTestCommon.h"

using namespace std;
using namespace qcc;
using namespace ajn;

static std::map<BusAttachment*, String> wkns;
static std::map<BusAttachment*, BusObjectTestBusObject*> testobjects;
static std::map<BusAttachment*, BusObjectTestSignalReceiver*> signalobjects;

static const char* OBJECT_PATH =   "/org/alljoyn/test/BusObjectTest";

class SessionTest : public testing::Test {
  public:
    BusAttachment busA;
    BusAttachment busB;
    BusAttachment busC;

    InterfaceDescription* CreateTestInterface(BusAttachment& busClient) {

        //add interface to client bus attachment
        InterfaceDescription* clienttestIntf = NULL;
        QStatus status = busClient.CreateInterface("org.test", clienttestIntf);
        EXPECT_EQ(ER_OK, status);
        assert(NULL != clienttestIntf);
        status = clienttestIntf->AddSignal("my_signal", "s", NULL, 0);
        EXPECT_EQ(ER_OK, status);
        clienttestIntf->Activate();

        return clienttestIntf;
    }

    virtual void SetUp() {

        BusAttachment*busses[] = {
            &busA,
            &busB,
            &busC,
        };

        wkns[&busA] = genUniqueName(busA);
        wkns[&busB] = genUniqueName(busB);
        wkns[&busC] = genUniqueName(busC);

        QStatus status = ER_FAIL;
        status = busA.Start();
        EXPECT_EQ(ER_OK, status);
        status = busA.Connect(getConnectArg("BUS_ADDRESS1").c_str());
        EXPECT_EQ(ER_OK, status);

        status = busB.Start();
        EXPECT_EQ(ER_OK, status);
        status = busB.Connect(getConnectArg("BUS_ADDRESS2").c_str());
        EXPECT_EQ(ER_OK, status);

        status = busC.Start();
        EXPECT_EQ(ER_OK, status);
        status = busC.Connect(getConnectArg("BUS_ADDRESS3").c_str());
        EXPECT_EQ(ER_OK, status);

        for (size_t i = 0; i < sizeof(busses) / sizeof(busses[0]); ++i) {
            InterfaceDescription*intf = CreateTestInterface(*busses[i]);
            ASSERT_TRUE(NULL != intf);
            testobjects[busses[i]] = new BusObjectTestBusObject(*busses[i], OBJECT_PATH);
            status = busses[i]->RegisterBusObject(*testobjects[busses[i]]);
            ASSERT_EQ(ER_OK, status);

            signalobjects[busses[i]] = new BusObjectTestSignalReceiver;
            const InterfaceDescription::Member*  signal_member = intf->GetMember("my_signal");
            status = busses[i]->RegisterSignalHandler(signalobjects[busses[i]],
                                                      static_cast<MessageReceiver::SignalHandler>(&BusObjectTestSignalReceiver::SignalHandler),
                                                      signal_member,
                                                      NULL);
            ASSERT_EQ(ER_OK, status);

            ASSERT_EQ(ER_OK, busses[i]->RequestName(wkns[busses[i]].c_str(), DBUS_NAME_FLAG_DO_NOT_QUEUE));
            ASSERT_EQ(ER_OK, busses[i]->AdvertiseName(wkns[busses[i]].c_str(), TRANSPORT_ANY));
        }

        for (size_t i = 0; i < sizeof(busses) / sizeof(busses[0]); ++i) {
            for (size_t j = 0; j < sizeof(busses) / sizeof(busses[0]); ++j) {
                status = busses[i]->FindAdvertisedName(wkns[busses[j]].c_str());
                ASSERT_EQ(ER_OK, status);
            }
        }




    }

    virtual void TearDown() {

        fflush(stdout);
        busC.Disconnect();
        busC.Stop();
        busC.Join();

        busB.Disconnect();
        busB.Stop();
        busB.Join();

        busA.Disconnect();
        busA.Stop();
        busA.Join();

        for (std::map<BusAttachment*, BusObjectTestBusObject*>::iterator it = testobjects.begin(); it != testobjects.end(); ++it) {
            delete it->second;
        }
        testobjects.clear();

        for (std::map<BusAttachment*, BusObjectTestSignalReceiver*>::iterator it = signalobjects.begin(); it != signalobjects.end(); ++it) {
            delete it->second;
        }
        signalobjects.clear();

        wkns.clear();
    }

    SessionTest() : busA("busA", true), busB("busB", true), busC("busC", true) {


    }

    ~SessionTest() { }


};

class TwoMultipointSessionsSessionPortListener : public SessionPortListener {
  public:
    virtual ~TwoMultipointSessionsSessionPortListener() { }
    virtual bool AcceptSessionJoiner(SessionPort sessionPort, const char* joiner, const SessionOpts& opts) { return true; }
};

TEST_F(SessionTest, TwoMultipointSessions)
{
    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, true, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
    SessionPort portA = 27;
    SessionPort portB = portA;

    BusAttachment busA("A");
    TwoMultipointSessionsSessionPortListener listenerA;
    ASSERT_EQ(ER_OK, busA.Start());
    ASSERT_EQ(ER_OK, busA.Connect(getConnectArg().c_str()));
    ASSERT_EQ(ER_OK, busA.BindSessionPort(portA, opts, listenerA));
    ASSERT_EQ(ER_OK, busA.RequestName("bus.A", DBUS_NAME_FLAG_DO_NOT_QUEUE));
    ASSERT_EQ(ER_OK, busA.AdvertiseName("bus.A", TRANSPORT_ANY));

    BusAttachment busB("B");
    TwoMultipointSessionsSessionPortListener listenerB;
    ASSERT_EQ(ER_OK, busB.Start());
    ASSERT_EQ(ER_OK, busB.Connect(getConnectArg().c_str()));
    ASSERT_EQ(ER_OK, busB.BindSessionPort(portB, opts, listenerB));
    ASSERT_EQ(ER_OK, busB.RequestName("bus.B", DBUS_NAME_FLAG_DO_NOT_QUEUE));
    ASSERT_EQ(ER_OK, busB.AdvertiseName("bus.B", TRANSPORT_ANY));

    SessionId outIdA;
    SessionOpts outOptsA;
    ASSERT_EQ(ER_OK, busA.JoinSession(wkns[&busB].c_str(), portB, NULL, outIdA, opts));

    SessionId outIdB;
    SessionOpts outOptsB;
    ASSERT_EQ(ER_OK, busB.JoinSession(wkns[&busA].c_str(), portA, NULL, outIdB, opts));

    /*
     * The bug is that joining two multipoint sessions with the same port resulted in only one
     * session, not two.  This asserts that there are in fact two different sessions created above.
     */
    ASSERT_NE(outIdA, outIdB);
}

bool sessionMemberAddedFlagA = false;
bool sessionMemberRemovedFlagA = false;
bool sessionMemberAddedFlagB = false;
bool sessionMemberRemovedFlagB = false;
bool sessionMemberAddedFlagC = false;
bool sessionMemberRemovedFlagC = false;
bool sessionJoinerAcceptedFlag = false;
bool sessionJoinedFlag = false;
bool sessionJoinedCBFlag = false;
SessionId bindMemberSessionId = 0;

class BindMemberSessionListenerA : public SessionListener {
  public:
    //virtual void SessionLost(SessionId sessionId, SessionLostReason reason) { }
    virtual void SessionMemberAdded(SessionId sessionId, const char* uniqueName) {
        sessionMemberAddedFlagA = true;
    }
    virtual void SessionMemberRemoved(SessionId sessionId, const char* uniqueName) {
        sessionMemberRemovedFlagA = true;
    }
};

class BindMemberSessionListenerB : public SessionListener {
  public:
    //virtual void SessionLost(SessionId sessionId, SessionLostReason reason) { }
    virtual void SessionMemberAdded(SessionId sessionId, const char* uniqueName) {
        sessionMemberAddedFlagB = true;
    }
    virtual void SessionMemberRemoved(SessionId sessionId, const char* uniqueName) {
        sessionMemberRemovedFlagB = true;
    }
};

class BindMemberSessionListenerC : public SessionListener {
  public:
    //virtual void SessionLost(SessionId sessionId, SessionLostReason reason) { }
    virtual void SessionMemberAdded(SessionId sessionId, const char* uniqueName) {
        sessionMemberAddedFlagC = true;
    }
    virtual void SessionMemberRemoved(SessionId sessionId, const char* uniqueName) {
        sessionMemberRemovedFlagC = true;
    }
};

class BindMemberSessionPortListener : public SessionPortListener {
  public:
    BindMemberSessionPortListener(BusAttachment* bus, BindMemberSessionListenerA* bindMemberSessionListener) :
        bus(bus),
        sessionListener(bindMemberSessionListener) { }
    virtual bool AcceptSessionJoiner(SessionPort sessionPort, const char* joiner, const SessionOpts& opts) {
        sessionJoinerAcceptedFlag = true;
        return true;
    }
    virtual void SessionJoined(SessionPort sessionPort, SessionId id, const char* joiner) {
        bindMemberSessionId = id;
        sessionJoinedFlag = true;
        QStatus status = bus->SetSessionListener(id, sessionListener);
        EXPECT_EQ(ER_OK, status);
    }
    BusAttachment* bus;
    BindMemberSessionListenerA* sessionListener;
};

class BindMemberJoinSessionAsyncCB : public ajn::BusAttachment::JoinSessionAsyncCB {
  public:
    virtual void JoinSessionCB(QStatus status, SessionId sessionId, const SessionOpts& opts, void* context) {
        EXPECT_EQ(ER_OK, status);
        sessionJoinedCBFlag = true;
    }
};
TEST_F(SessionTest, BindMemberAddedRemoved) {
    QStatus status = ER_FAIL;
    /* make sure global flags are initialized */
    sessionMemberAddedFlagA = false;
    sessionMemberRemovedFlagA = false;
    sessionMemberAddedFlagB = false;
    sessionMemberRemovedFlagB = false;
    sessionMemberAddedFlagC = false;
    sessionMemberRemovedFlagC = false;
    sessionJoinerAcceptedFlag = false;
    sessionJoinedFlag = false;
    sessionJoinedCBFlag = false;
    bindMemberSessionId = 0;

    SessionId multipointSessionId = 0;

    BusAttachment busA("bus.Aa", false);
    BusAttachment busB("bus.Bb", false);
    BusAttachment busC("bus.Cc", false);

    status = busA.Start();
    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    status = busA.Connect(getConnectArg().c_str());
    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    status = busB.Start();
    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    status = busB.Connect(getConnectArg().c_str());
    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    status = busC.Start();
    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    status = busC.Connect(getConnectArg().c_str());

    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, true, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);

    BindMemberSessionListenerA sessionListenerA;
    BindMemberSessionPortListener sessionPortListener(&busA, &sessionListenerA);
    SessionPort port = 0;

    status = busA.BindSessionPort(port, opts, sessionPortListener);
    EXPECT_EQ(ER_OK, status);

    BindMemberJoinSessionAsyncCB joinSessionCB;
    BindMemberSessionListenerB sessionListenerB;
    status = busB.JoinSessionAsync(wkns[&busA].c_str(), port, &sessionListenerB, opts, &joinSessionCB);

    //Wait upto 5 seconds all callbacks and listeners to be called.
    for (int i = 0; i < 500; ++i) {
        if (sessionJoinedCBFlag && sessionJoinedFlag) {
            break;
        }
        qcc::Sleep(10);
    }

    EXPECT_TRUE(sessionJoinedCBFlag);
    multipointSessionId = bindMemberSessionId;

    status = busA.SetSessionListener(bindMemberSessionId, &sessionListenerA);
    EXPECT_EQ(ER_OK, status);

    //Wait upto 5 seconds all callbacks and listeners to be called.
    for (int i = 0; i < 500; ++i) {
        if (sessionMemberAddedFlagB &&
            sessionJoinerAcceptedFlag &&
            sessionJoinedFlag) {
            break;
        }
        qcc::Sleep(10);
    }

    EXPECT_TRUE(sessionJoinerAcceptedFlag);
    EXPECT_TRUE(sessionJoinedFlag);
    EXPECT_TRUE(sessionMemberAddedFlagB);

    sessionMemberAddedFlagA = false;
    sessionMemberAddedFlagB = false;
    sessionJoinerAcceptedFlag = false;
    sessionJoinedFlag = false;
    sessionJoinedCBFlag = false;

    BindMemberSessionListenerC sessionListenerC;
    EXPECT_EQ(ER_OK, status);
    status = busC.JoinSessionAsync(wkns[&busA].c_str(), port, &sessionListenerC, opts, &joinSessionCB);


    //Wait upto 5 seconds all callbacks and listeners to be called.
    for (int i = 0; i < 500; ++i) {
        if (sessionJoinedCBFlag) {
            break;
        }
        qcc::Sleep(10);
    }

    EXPECT_EQ(multipointSessionId, bindMemberSessionId);

    //Wait upto 5 seconds all callbacks and listeners to be called.
    for (int i = 0; i < 500; ++i) {
        if (sessionMemberAddedFlagA &&
            sessionMemberAddedFlagB &&
            sessionMemberAddedFlagC &&
            sessionJoinerAcceptedFlag &&
            sessionJoinedFlag) {
            break;
        }
        qcc::Sleep(10);
    }

    EXPECT_TRUE(sessionMemberAddedFlagA);
    EXPECT_TRUE(sessionMemberAddedFlagB);
    EXPECT_TRUE(sessionMemberAddedFlagC);
    EXPECT_TRUE(sessionJoinerAcceptedFlag);
    EXPECT_TRUE(sessionJoinedFlag);

    status = busB.LeaveSession(bindMemberSessionId);
    EXPECT_EQ(ER_OK, status);

    //Wait upto 5 seconds all callbacks and listeners to be called.
    for (int i = 0; i < 500; ++i) {
        if (sessionMemberRemovedFlagA && sessionMemberRemovedFlagC) {
            break;
        }
        qcc::Sleep(10);
    }

    EXPECT_TRUE(sessionMemberRemovedFlagA);
    EXPECT_FALSE(sessionMemberRemovedFlagB);
    EXPECT_TRUE(sessionMemberRemovedFlagA);

    sessionMemberRemovedFlagA = false;
    sessionMemberRemovedFlagB = false;
    sessionMemberRemovedFlagC = false;

    status = busC.LeaveSession(bindMemberSessionId);
    EXPECT_EQ(ER_OK, status);

    //Wait upto 5 seconds all callbacks and listeners to be called.
    for (int i = 0; i < 500; ++i) {
        if (sessionMemberRemovedFlagA) {
            break;
        }
        qcc::Sleep(10);
    }

    EXPECT_TRUE(sessionMemberRemovedFlagA);
    EXPECT_FALSE(sessionMemberRemovedFlagB);
    EXPECT_FALSE(sessionMemberRemovedFlagC);

    for (int i = 0; i < 500; ++i) {
        if (sessionLostFlag) {
            break;
        }
        qcc::Sleep(10);
    }
    qcc::Sleep(10);
}

qcc::String sessionJoinedTestJoiner = "";

class SessionJoinedSessionPortListener : public SessionPortListener {
    virtual bool AcceptSessionJoiner(SessionPort sessionPort, const char* joiner, const SessionOpts& opts) {
        printf("AcceptSessionJoiner sessionPort = %d, joiner = %s\n", sessionPort, joiner);
        sessionJoinerAcceptedFlag = true;
        return true;
    }
    virtual void SessionJoined(SessionPort sessionPort, SessionId id, const char* joiner) {
        printf("SessionJoined sessionPort = %d, SessionId=%d, joiner = %s\n", sessionPort, id, joiner);
        bindMemberSessionId = id;
        sessionJoinedTestJoiner = joiner;
        sessionJoinedFlag = true;

    }
};

class SessionJoinTestSessionListener : public SessionListener {

  public:
    SessionId lastSessionId;
    size_t sessionLostCalled;
    SessionListener::SessionLostReason lastReason;

    SessionId sessionMemberAddedSessionId;
    size_t sessionMemberAddedCalled;
    qcc::String sessionMemberAddedUniqueName;

    SessionId sessionMemberRemovedSessionId;
    size_t sessionMemberRemovedCalled;
    qcc::String sessionMemberRemovedUniqueName;


    std::set<qcc::String> sessionMembers;
    const char*name;
    qcc::String uniqueName;

    SessionJoinTestSessionListener(const char*_name, qcc::String _uniqueName) :
        lastSessionId(0),
        sessionLostCalled(0),
        lastReason(ALLJOYN_SESSIONLOST_INVALID),
        sessionMemberAddedSessionId(0),
        sessionMemberAddedCalled(0),
        sessionMemberRemovedSessionId(0),
        sessionMemberRemovedCalled(0),
        name(_name),
        uniqueName(_uniqueName)
    { }


    virtual void SessionLost(SessionId sessionId, SessionLostReason reason) {
        lastSessionId = sessionId;
        lastReason = reason;
        ++sessionLostCalled;

    }

    virtual void SessionMemberAdded(SessionId sessionId, const char* uniqueName) {

        EXPECT_EQ(0U, sessionLostCalled);
        sessionMemberAddedSessionId = sessionId;
        sessionMemberAddedUniqueName = uniqueName;
        sessionMembers.insert(uniqueName);
        ++sessionMemberAddedCalled;

    }

    virtual void SessionMemberRemoved(SessionId sessionId, const char* uniqueName) {

        EXPECT_EQ(0U, sessionLostCalled);
        sessionMemberRemovedSessionId = sessionId;
        sessionMemberRemovedUniqueName = uniqueName;
        sessionMembers.erase(uniqueName);
        ++sessionMemberRemovedCalled;
    }

    void Reset() {
        sessionMemberAddedSessionId = 0;
        sessionMemberAddedCalled = 0;
        sessionMemberAddedUniqueName = "";

        sessionMemberRemovedSessionId = 0;
        sessionMemberRemovedCalled = 0;
        sessionMemberRemovedUniqueName = "";

        lastReason = SessionListener::ALLJOYN_SESSIONLOST_INVALID;
        lastSessionId = 0;
        sessionLostCalled = 0;
    }

    void ResetMemberAddedRemoved() {

        sessionMemberAddedSessionId = 0;
        sessionMemberAddedCalled = 0;
        sessionMemberAddedUniqueName = "";

        sessionMemberRemovedSessionId = 0;
        sessionMemberRemovedCalled = 0;
        sessionMemberRemovedUniqueName = "";
    }

};

static bool SessionJoinLeaveTest(BusAttachment& busHost, BusAttachment& busJoiner, bool joinerLeaves, bool multipoint) {

    QStatus status = ER_FAIL;
    bindMemberSessionId = 0;
    sessionJoinerAcceptedFlag = false;
    sessionJoinedFlag = false;
    QStatus status = ER_FAIL;

    BusAttachment busA("busAA", false);
    BusAttachment busB("busBB", false);

    status = busA.Start();
    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    status = busA.Connect(getConnectArg().c_str());
    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    status = busB.Start();
    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    status = busB.Connect(getConnectArg().c_str());
    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);

    SessionJoinedSessionPortListener sessionPortListener;
    SessionPort port = 0;

    status = busHost.BindSessionPort(port, opts, sessionPortListener);
    EXPECT_EQ(ER_OK, status);

    SessionListener blankSessionListener;
    SessionId sessionId;

    status = busJoiner.JoinSession(wkns[&busHost].c_str(), port, &sessionListenerJoiner, sessionId, opts);
    EXPECT_EQ(ER_OK, status);

    EXPECT_TRUE(sessionJoinerAcceptedFlag);
    //Wait upto 3 seconds all callbacks and listeners to be called.
    for (int i = 0; i < 300; ++i) {
        if (sessionJoinedFlag) {
            break;
        }
        qcc::Sleep(10);
    }

    EXPECT_TRUE(sessionJoinedFlag);
    EXPECT_EQ(bindMemberSessionId, sessionId);
    if (&busHost == &busJoiner) { /* self join case */
        EXPECT_STREQ(busHost.GetUniqueName().c_str(), sessionPortListener.sessionJoinedTestJoiner.c_str()) <<
            "The Joiner name " << sessionPortListener.sessionJoinedTestJoiner.c_str() <<
            " should be the same as" << busHost.GetUniqueName().c_str();


    } else {
        EXPECT_STRNE(busHost.GetUniqueName().c_str(), sessionPortListener.sessionJoinedTestJoiner.c_str()) <<
            "The Joiner name " << sessionPortListener.sessionJoinedTestJoiner.c_str() <<
            " should be different than " << busHost.GetUniqueName().c_str();
    }
    EXPECT_STREQ(busJoiner.GetUniqueName().c_str(), sessionPortListener.sessionJoinedTestJoiner.c_str()) <<
        "The Joiner name " << sessionPortListener.sessionJoinedTestJoiner.c_str() <<
        " should be the same as " << busJoiner.GetUniqueName().c_str();

    testobjects[&busHost]->SendSignal(sessionId);
    //Wait up to 1 seconds for all callbacks and listeners to be called.
    for (int i = 0; i < 100; ++i) {
        if (signalobjects[&busJoiner]->signalReceived > 0) {
            break;
        }
        qcc::Sleep(10);
    }
    qcc::Sleep(10);

    EXPECT_EQ(1U, signalobjects[&busJoiner]->signalReceived);
    if (&busHost == &busJoiner) {
        EXPECT_EQ(ER_FAIL, busHost.SetSessionListener(sessionId, NULL));
    } else {
        /* other join case */
        EXPECT_EQ(0U, signalobjects[&busHost]->signalReceived);

    }

    if (!multipoint) {
        status = busHost.RemoveSessionMember(sessionId, busJoiner.GetUniqueName());
        EXPECT_EQ(ER_ALLJOYN_REMOVESESSIONMEMBER_NOT_MULTIPOINT, status);
    }

    SessionJoinTestSessionListener*signalledListener;
    SessionJoinTestSessionListener*notSignalledListener;
    SessionListener::SessionLostReason sessionLostReason;
    if (joinerLeaves) {
        EXPECT_EQ(ER_OK, busJoiner.LeaveJoinedSession(sessionId));
        if (&busHost != &busJoiner) { /* other join case */
            EXPECT_EQ(ER_ALLJOYN_LEAVESESSION_REPLY_NO_SESSION, busJoiner.LeaveHostedSession(sessionId));
        }
        signalledListener = &sessionListenerHost;
        notSignalledListener = &sessionListenerJoiner;
        sessionLostReason = SessionListener::ALLJOYN_SESSIONLOST_REMOTE_END_LEFT_SESSION;

    } else {
        EXPECT_EQ(ER_OK, busHost.LeaveHostedSession(sessionId));

        if (&busHost != &busJoiner) { /* other join case */
            EXPECT_EQ(ER_ALLJOYN_LEAVESESSION_REPLY_NO_SESSION, busHost.LeaveJoinedSession(sessionId));
        } else {
            EXPECT_EQ(ER_ALLJOYN_LEAVESESSION_REPLY_NO_SESSION, busHost.LeaveSession(sessionId));
        }

        signalledListener = &sessionListenerJoiner;
        notSignalledListener = &sessionListenerHost;
        sessionLostReason = SessionListener::ALLJOYN_SESSIONLOST_REMOTE_END_LEFT_SESSION;
    }

    qcc::Sleep(100); /* not sure if this is needed */
    EXPECT_EQ(sessionId, signalledListener->lastSessionId);
    EXPECT_EQ(1U, signalledListener->sessionLostCalled);
    EXPECT_EQ(sessionLostReason, signalledListener->lastReason);
    EXPECT_EQ((SessionId)0, notSignalledListener->lastSessionId);
    EXPECT_EQ(0U, notSignalledListener->sessionLostCalled);
    EXPECT_EQ(SessionListener::ALLJOYN_SESSIONLOST_INVALID, notSignalledListener->lastReason);
    if (multipoint) {
        EXPECT_EQ(sessionId, sessionListenerHost.sessionMemberAddedSessionId);
        EXPECT_EQ(1U, sessionListenerHost.sessionMemberAddedCalled);
        EXPECT_STREQ(busJoiner.GetUniqueName().c_str(), sessionListenerHost.sessionMemberAddedUniqueName.c_str());
        EXPECT_EQ(sessionId, sessionListenerJoiner.sessionMemberAddedSessionId);
        EXPECT_EQ(1U, sessionListenerJoiner.sessionMemberAddedCalled);
        EXPECT_STREQ(busHost.GetUniqueName().c_str(), sessionListenerJoiner.sessionMemberAddedUniqueName.c_str());

        EXPECT_EQ(sessionId, signalledListener->sessionMemberRemovedSessionId);
        EXPECT_EQ(1U, signalledListener->sessionMemberRemovedCalled);
        EXPECT_STREQ(joinerLeaves ? busJoiner.GetUniqueName().c_str() : busHost.GetUniqueName().c_str(), signalledListener->sessionMemberRemovedUniqueName.c_str());
        EXPECT_EQ((SessionId)0, notSignalledListener->sessionMemberRemovedSessionId);
        EXPECT_EQ(0U, notSignalledListener->sessionMemberRemovedCalled);
        EXPECT_STREQ("", notSignalledListener->sessionMemberRemovedUniqueName.c_str());
    }

    qcc::Sleep(200);         /* let all callbacks finish */

    return true;
}

TEST_F(SessionTest, SessionJoined_OtherJoin_PP_JoinerLeaves) {

    EXPECT_TRUE(SessionJoinLeaveTest(busA, busB, true, false));

}

TEST_F(SessionTest, SessionJoined_OtherJoin_PP_HostLeaves) {

    EXPECT_TRUE(SessionJoinLeaveTest(busA, busB, false, false));

}

TEST_F(SessionTest, SessionJoined_OtherJoin_MP_JoinerLeaves) {

    EXPECT_TRUE(SessionJoinLeaveTest(busA, busB, true, true));

}

TEST_F(SessionTest, SessionJoined_OtherJoin_MP_HostLeaves) {

    EXPECT_TRUE(SessionJoinLeaveTest(busA, busB, false, true));

}


TEST_F(SessionTest, SessionJoined_SelfJoin_PP_JoinerLeaves) {

    EXPECT_TRUE(SessionJoinLeaveTest(busA, busA, true, false));

}

TEST_F(SessionTest, SessionJoined_SelfJoin_PP_HostLeaves) {

    EXPECT_TRUE(SessionJoinLeaveTest(busA, busA, false, false));

}

TEST_F(SessionTest, SessionJoined_SelfJoin_MP_JoinerLeaves) {

    EXPECT_TRUE(SessionJoinLeaveTest(busA, busA, true, true));

}

TEST_F(SessionTest, SessionJoined_SelfJoin_MP_HostLeaves) {

    EXPECT_TRUE(SessionJoinLeaveTest(busA, busA, false, true));
}

bool sessionLostFlagA;
bool sessionLostFlagB;
class RemoveSessionMemberBusAListener : public SessionPortListener, public SessionListener {
  public:
    RemoveSessionMemberBusAListener(BusAttachment* bus) : bus(bus) { }

    virtual bool AcceptSessionJoiner(SessionPort sessionPort, const char* joiner, const SessionOpts& opts) {
        printf("AcceptSessionJoiner sessionPort = %d, joiner = %s\n", sessionPort, joiner);
        return true;
    }
    virtual void SessionJoined(SessionPort sessionPort, SessionId id, const char* joiner) {
        printf("SessionJoined sessionPort = %d, SessionId=%d, joiner = %s\n", sessionPort, id, joiner);
        bindMemberSessionId = id;
        sessionJoinedTestJoiner = joiner;
        sessionJoinedFlag = true;
        bus->SetSessionListener(id, this);
    }
    virtual void SessionLost(SessionId sessionId) {
        sessionLostFlagA = true;
    }
    virtual void SessionMemberAdded(SessionId sessionId, const char* uniqueName) {
        sessionMemberAddedFlagA = true;
    }
    virtual void SessionMemberRemoved(SessionId sessionId, const char* uniqueName) {
        sessionMemberRemovedFlagA = true;
    }
    BusAttachment* bus;
};
class RemoveSessionMemberBusBListener : public SessionListener {

    virtual void SessionLost(SessionId sessionId) {
        sessionLostFlagB = true;
    }
    virtual void SessionMemberAdded(SessionId sessionId, const char* uniqueName) {
        sessionMemberAddedFlagB = true;
    }
    virtual void SessionMemberRemoved(SessionId sessionId, const char* uniqueName) {
        sessionMemberRemovedFlagB = true;
    }
};

TEST_F(SessionTest, RemoveSessionMember) {
    QStatus status = ER_FAIL;
    /* make sure global flags are initialized */
    sessionJoinedFlag = false;
    sessionLostFlagA = false;
    sessionMemberAddedFlagA = false;
    sessionMemberRemovedFlagA = false;
    sessionLostFlagB = false;
    sessionMemberAddedFlagB = false;
    sessionMemberRemovedFlagB = false;

    BusAttachment busA("bus.Aa", false);
    BusAttachment busB("bus.Bb", false);

    status = busA.Start();
    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    status = busA.Connect(getConnectArg().c_str());
    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    status = busB.Start();
    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    status = busB.Connect(getConnectArg().c_str());
    EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);

    /* Multi-point session */
    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, true, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);

    RemoveSessionMemberBusAListener sessionPortListener(&busA);
    SessionPort port = 1;

    status = busA.BindSessionPort(port, opts, sessionPortListener);
    EXPECT_EQ(ER_OK, status);

    RemoveSessionMemberBusBListener sessionListener;
    SessionId sessionId;

    status = busB.JoinSession(wkns[&busA].c_str(), port, &sessionListener, sessionId, opts);
    EXPECT_EQ(ER_OK, status);

    EXPECT_TRUE(sessionJoinerAcceptedFlag);
    //Wait upto 3 seconds all callbacks and listeners to be called.
    for (int i = 0; i < 300; ++i) {
        if (sessionJoinedFlag && sessionMemberAddedFlagA && sessionMemberAddedFlagB) {
            break;
        }
        qcc::Sleep(10);
    }

    EXPECT_TRUE(sessionJoinedFlag);
    EXPECT_TRUE(sessionMemberAddedFlagA);
    EXPECT_TRUE(sessionMemberAddedFlagB);

    status = busB.RemoveSessionMember(sessionId, busA.GetUniqueName());
    EXPECT_EQ(ER_ALLJOYN_REMOVESESSIONMEMBER_NOT_BINDER, status);

    status = busA.RemoveSessionMember(sessionId, busA.GetUniqueName());
    EXPECT_EQ(ER_ALLJOYN_REMOVESESSIONMEMBER_NOT_FOUND, status);

    status = busA.RemoveSessionMember(sessionId, ":Invalid");
    EXPECT_EQ(ER_ALLJOYN_REMOVESESSIONMEMBER_NOT_FOUND, status);

    status = busA.RemoveSessionMember(sessionId, busB.GetUniqueName());
    EXPECT_EQ(ER_OK, status);

    //Wait upto 2 seconds all callbacks and listeners to be called.
    for (int i = 0; i < 200; ++i) {
        if (sessionLostFlagA && sessionLostFlagB && sessionMemberRemovedFlagA && sessionMemberRemovedFlagB) {
            break;
        }
        qcc::Sleep(10);
    }

    EXPECT_TRUE(sessionLostFlagA);
    EXPECT_TRUE(sessionLostFlagB);
    EXPECT_TRUE(sessionMemberRemovedFlagA);
    EXPECT_TRUE(sessionMemberRemovedFlagB);

}

typedef enum {
    HOST_LEAVES,
    JOINER_LEAVES,
    JOINER2_LEAVES,
    HOST_REMOVES_JOINER,
    HOST_REMOVES_JOINER2,
    SIGNAL,
    STOP
} SessionAction;

#define CHECK(x)    do { \
        if (!(x)) { \
            if (g_print) { \
                fprintf(stderr, "Check '%s' on line %d failed.\n", # x, __LINE__); \
            } \
            return false; \
        } \
} while (0)

static bool MPJoinAllNotificationsDone(SessionJoinTestSessionListener* host, set<SessionJoinTestSessionListener*>& existingJoiners, SessionJoinTestSessionListener* joiner)
{
    set<SessionJoinTestSessionListener*>::iterator it;
    bool isPreSelfJoined = false;
    for (it = existingJoiners.begin(); it != existingJoiners.end(); ++it) {
        if ((*it)->uniqueName == host->uniqueName) {
            isPreSelfJoined = true;
        }
    }

    /* joiner always gets SessionMemberAdded for all other session participants */
    CHECK((joiner->sessionMemberAddedCalled == (existingJoiners.size() + (isPreSelfJoined ? 0 : 1))));
    for (it = existingJoiners.begin(); it != existingJoiners.end(); ++it) {
        CHECK((joiner->sessionMembers.count((*it)->uniqueName) == 1));
    }
    CHECK((joiner->sessionMembers.count(host->uniqueName) == 1));

    /* host always gets SessionMemberAdded for joiner */
    CHECK((host->sessionMemberAddedCalled == 1));
    CHECK((host->sessionMemberAddedUniqueName == joiner->uniqueName));

    /* other session participants are only involved if it's not a self-join */
    if (host->uniqueName != joiner->uniqueName) {
        /* it's not self-join so the other members should get notifications too */
        for (it = existingJoiners.begin(); it != existingJoiners.end(); ++it) {
            CHECK(((*it)->sessionMemberAddedCalled == 1));
            CHECK(((*it)->sessionMemberAddedUniqueName == joiner->uniqueName));
        }
    }

    return true;
}

static bool MPHostLeavesAllNotificationsDone(SessionJoinTestSessionListener*host, set<SessionJoinTestSessionListener*>& joiners) {
    /* deal with self-join and other-join in the appropriate manner */
    set<SessionJoinTestSessionListener*> otherJoiners;
    SessionJoinTestSessionListener* selfJoiner = NULL;

    set<SessionJoinTestSessionListener*>::iterator it;
    for (it = joiners.begin(); it != joiners.end(); ++it) {
        if ((*it)->uniqueName != host->uniqueName) {
            otherJoiners.insert(*it);
        } else {
            selfJoiner = *it;
        }
    }

    /* sanity check: host should never get SessionMemberRemoved or SessionLost calls */
    CHECK((host->sessionMemberRemovedCalled == 0));
    CHECK((host->sessionLostCalled == 0));

    /* If there was only one joiner left, the session is over. That one joiner is expected to
     * receive both SessionMemberRemoved and SessionLost.
     * If more joiners were still in play, nobody will get SessionLost. Depending on whether
     * a self-join was in progress, only the self-joiner or everybody will get SessionmemberRemoved. */
    if (joiners.size() == 1) {
        /* session is lost */
        SessionJoinTestSessionListener* joiner = *(joiners.begin());
        CHECK((joiner->sessionMemberRemovedCalled == 1));
        CHECK((joiner->sessionMemberRemovedUniqueName == host->uniqueName));
        CHECK((joiner->lastReason == SessionListener::ALLJOYN_SESSIONLOST_REMOTE_END_LEFT_SESSION));
    } else if (selfJoiner != NULL) {
        /* session is not lost, but self-join in play */
        CHECK((selfJoiner->sessionMemberRemovedCalled == 1));
        CHECK((selfJoiner->sessionMemberRemovedUniqueName == host->uniqueName));
        CHECK((selfJoiner->sessionLostCalled == 0));
        for (it = otherJoiners.begin(); it != otherJoiners.end(); ++it) {
            CHECK(((*it)->sessionMemberRemovedCalled ==  0));
            CHECK(((*it)->sessionLostCalled == 0));
        }
    } else {
        /* session is not lost, no self-join in play */
        for (it = otherJoiners.begin(); it != otherJoiners.end(); ++it) {
            CHECK(((*it)->sessionMemberRemovedCalled ==  1));
            CHECK(((*it)->sessionMemberRemovedUniqueName == host->uniqueName));
            CHECK(((*it)->sessionLostCalled == 0));
        }
    }

    return true;
}

static bool MPJoinerLeavesAllNotificationsDone(SessionJoinTestSessionListener* host, set<SessionJoinTestSessionListener*>& remainingJoiners, SessionJoinTestSessionListener* leaver, bool forced)
{
    /* make a proper distinction between self-join leaving and other-join leaving */
    bool isSelfLeave = (host != NULL) && (leaver->uniqueName == host->uniqueName);
    bool hostHasSelfJoined = false;
    set<SessionJoinTestSessionListener*>::iterator it;
    for (it = remainingJoiners.begin(); it != remainingJoiners.end(); ++it) {
        if (host && host->uniqueName == (*it)->uniqueName) {
            hostHasSelfJoined = true;
        }
    }

    if (host != NULL) {
        /* the host should always get SessionMemberRemoved.
         * if there are no remaining members in the session, we expect SessionLost as well */
        CHECK((host->sessionMemberRemovedCalled == 1));
        CHECK((host->sessionMemberRemovedUniqueName == leaver->uniqueName));

        if (remainingJoiners.size() == 0) {
            CHECK((host->sessionLostCalled == 1));
            CHECK((host->lastReason == SessionListener::ALLJOYN_SESSIONLOST_REMOTE_END_LEFT_SESSION));
        } else {
            CHECK((host->sessionLostCalled == 0));
        }
    }

    if (!isSelfLeave) {
        /* the remaining joiners should get SessionMemberRemoved.
         * if there is only one remaining joiner and no host, we expect SessionLost as well */
        bool expectSessionLost = (host == NULL) && (remainingJoiners.size() == 1);
        for (it = remainingJoiners.begin(); it != remainingJoiners.end(); ++it) {
            SessionJoinTestSessionListener* joiner = *it;
            CHECK((joiner->sessionMemberRemovedCalled == 1));
            CHECK((joiner->sessionMemberRemovedUniqueName == leaver->uniqueName));
            if (expectSessionLost) {
                CHECK((joiner->sessionLostCalled == 1));
                CHECK((joiner->lastReason == SessionListener::ALLJOYN_SESSIONLOST_REMOTE_END_LEFT_SESSION));
            } else {
                CHECK((joiner->sessionLostCalled == 0));
            }
        }
    }

    /* the leaver will only get SessionLost and SessionMemberRemoved, but only if it was forcibly removed by the host */
    if (forced) {
        CHECK((leaver->sessionLostCalled == 1));
        if (isSelfLeave) {
            CHECK((leaver->lastReason == SessionListener::ALLJOYN_SESSIONLOST_REMOVED_BY_BINDER_SELF));
        } else {
            CHECK((leaver->lastReason == SessionListener::ALLJOYN_SESSIONLOST_REMOVED_BY_BINDER));
        }
        size_t expectedRemovedCalls = remainingJoiners.size();
        if (host && !hostHasSelfJoined) {
            ++expectedRemovedCalls;
        }
        CHECK((leaver->sessionMemberRemovedCalled == expectedRemovedCalls));
        CHECK((leaver->sessionMembers.size() == 0));
    } else {
        CHECK((leaver->sessionLostCalled == 0));
        CHECK((leaver->sessionMemberRemovedCalled == 0));
    }

    return true;
}
#undef CHECK

static void MultipointMultipeerTest(BusAttachment& busHost, BusAttachment& busJoiner, BusAttachment& busJoiner2, const SessionAction*sa) {

    assert(&busJoiner != &busJoiner2);         /* this would not make sense for this test */

    QStatus status = ER_FAIL;
    bindMemberSessionId = 0;
    sessionJoinerAcceptedFlag = false;
    sessionJoinedFlag = false;

    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, true, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
    SessionJoinTestSessionListener sessionListenerHost("host");
    SessionJoinTestSessionListener sessionListenerJoiner("joiner");
    SessionJoinTestSessionListener sessionListenerJoiner2("joiner2");

    SessionJoinedSessionPortListener sessionPortListener(busHost, &sessionListenerHost);
    SessionPort port = 0;

    status = busHost.BindSessionPort(port, opts, sessionPortListener);
    EXPECT_EQ(ER_OK, status);

    SessionId sessionId;

    /* Joiner 1 */
    status = busJoiner.JoinSession(wkns[&busHost].c_str(), port, &sessionListenerJoiner, sessionId, opts);
    EXPECT_EQ(ER_OK, status);


    EXPECT_TRUE(sessionJoinerAcceptedFlag);
    //Wait upto 3 seconds all callbacks and listeners to be called.
    for (int i = 0; i < 300; ++i) {
        if (sessionJoinedFlag) {
            break;
        }
        qcc::Sleep(10);
    }
    qcc::Sleep(10);

    EXPECT_TRUE(sessionJoinedFlag);
    EXPECT_EQ(sessionId, bindMemberSessionId);

    sessionJoinerAcceptedFlag = false;
    sessionJoinedFlag = false;

    EXPECT_STREQ(busJoiner.GetUniqueName().c_str(), sessionListenerHost.sessionMemberAddedUniqueName.c_str());
    EXPECT_EQ(1, sessionListenerHost.sessionMemberAddedCalled);
    EXPECT_STREQ(busHost.GetUniqueName().c_str(), sessionListenerJoiner.sessionMemberAddedUniqueName.c_str());
    EXPECT_EQ(1, sessionListenerJoiner.sessionMemberAddedCalled);
    EXPECT_STREQ("", sessionListenerJoiner2.sessionMemberAddedUniqueName.c_str());
    EXPECT_EQ(0, sessionListenerJoiner2.sessionMemberAddedCalled);

    /* joiner 2 */
    status = busJoiner2.JoinSession(wkns[&busHost].c_str(), port, &sessionListenerJoiner2, sessionId, opts);
    EXPECT_EQ(ER_OK, status);

    EXPECT_TRUE(sessionJoinerAcceptedFlag);
    //Wait upto 3 seconds all callbacks and listeners to be called.
    for (int i = 0; i < 300; ++i) {
        if (sessionJoinedFlag) {
            break;
        }
        qcc::Sleep(10);
    }
    qcc::Sleep(100);
    EXPECT_TRUE(sessionJoinedFlag);
    EXPECT_EQ(sessionId, bindMemberSessionId);

    EXPECT_STREQ(busJoiner2.GetUniqueName().c_str(), sessionListenerHost.sessionMemberAddedUniqueName.c_str());
    EXPECT_EQ(2, sessionListenerHost.sessionMemberAddedCalled);
    EXPECT_STREQ(busJoiner2.GetUniqueName().c_str(), sessionListenerJoiner.sessionMemberAddedUniqueName.c_str());

    if (&busHost == &busJoiner2) {
        EXPECT_EQ(1, sessionListenerJoiner.sessionMemberAddedCalled);
    } else {
        EXPECT_EQ(2, sessionListenerJoiner.sessionMemberAddedCalled);
    }

    if (&busHost == &busJoiner) {
        EXPECT_EQ(1, sessionListenerJoiner2.sessionMemberAddedCalled);
    } else {
        EXPECT_EQ(2, sessionListenerJoiner2.sessionMemberAddedCalled);
    }
    EXPECT_STREQ(busJoiner2.GetUniqueName().c_str(), sessionListenerHost.sessionMemberAddedUniqueName.c_str());
    std::set<qcc::String> expectedMembers;
    expectedMembers.insert(busHost.GetUniqueName());
    expectedMembers.insert(busJoiner.GetUniqueName());
    EXPECT_EQ(expectedMembers, sessionListenerJoiner2.sessionMembers);

    testobjects[&busHost]->SendSignal(sessionId);
    //Wait upto 1 seconds all callbacks and listeners to be called.
    for (int i = 0; i < 300; ++i) {
        if (signalobjects[&busJoiner]->signalReceived > 0 && signalobjects[&busJoiner2]->signalReceived > 0) {
            break;
        }
        qcc::Sleep(10);
    }
    qcc::Sleep(10);
    EXPECT_EQ(1U, signalobjects[&busJoiner]->signalReceived);
    EXPECT_EQ(1U, signalobjects[&busJoiner2]->signalReceived);
    if (&busHost != &busJoiner && &busHost != &busJoiner2) { /* other join case */
        EXPECT_EQ(0U, signalobjects[&busHost]->signalReceived);
    } else {
        EXPECT_EQ(1U, signalobjects[&busHost]->signalReceived);
    }

    EXPECT_EQ(0U, sessionListenerHost.sessionLostCalled);
    EXPECT_EQ(0U, sessionListenerJoiner.sessionLostCalled);
    EXPECT_EQ(0U, sessionListenerJoiner2.sessionLostCalled);

    bool sessionHostInSession = true;
    bool sessionJoinerInSession = true;
    bool sessionJoiner2InSession = true;
    int members = 3;

    for (; *sa != STOP; ++sa) {
        BusAttachment*removeOrLeave = NULL;
        BusAttachment*otherJoiner = NULL;
        SessionJoinTestSessionListener*removeOrLeaveListener = NULL;
        SessionJoinTestSessionListener*otherJoinerListener = NULL;
        bool*otherJoinerInSession = NULL;
        bool*removeOrLeaveInSession = NULL;

        switch (*sa) {
        case HOST_LEAVES:
            {
                bool selfJoinLeaveWithJoined = false;
                bool selfJoinLeaveWithJoined2 = false;
                assert(sessionListenerHost.sessionLostCalled == 0);

                if (&busHost == &busJoiner && sessionJoinerInSession) {
                    selfJoinLeaveWithJoined = true;
                }
                if (&busHost == &busJoiner2 && sessionJoiner2InSession) {
                    selfJoinLeaveWithJoined2 = true;
                }

                EXPECT_EQ(ER_OK, busHost.LeaveHostedSession(sessionId));
                qcc::Sleep(200);
                sessionHostInSession = false;
                --members;

                EXPECT_EQ((SessionId)0, sessionListenerHost.sessionMemberRemovedSessionId);
                EXPECT_STREQ("", sessionListenerHost.sessionMemberRemovedUniqueName.c_str());
                EXPECT_EQ(0, sessionListenerHost.sessionMemberRemovedCalled);
                EXPECT_EQ(SessionListener::ALLJOYN_SESSIONLOST_INVALID, sessionListenerHost.lastReason);

                if (sessionJoinerInSession == true) {
                    if (selfJoinLeaveWithJoined2) {
                        EXPECT_EQ((SessionId)0, sessionListenerJoiner.sessionMemberRemovedSessionId);
                        EXPECT_EQ(0, sessionListenerJoiner.sessionMemberRemovedCalled);
                        EXPECT_EQ(SessionListener::ALLJOYN_SESSIONLOST_INVALID, sessionListenerHost.lastReason);

                    } else {
                        EXPECT_STREQ(busHost.GetUniqueName().c_str(), sessionListenerJoiner.sessionMemberRemovedUniqueName.c_str());
                        EXPECT_EQ(sessionId, sessionListenerJoiner.sessionMemberRemovedSessionId);
                        EXPECT_EQ(1, sessionListenerJoiner.sessionMemberRemovedCalled);
                        if (members == 1) {
                            EXPECT_EQ(SessionListener::ALLJOYN_SESSIONLOST_REMOTE_END_LEFT_SESSION, sessionListenerJoiner.lastReason);
                        } else {
                            EXPECT_EQ(SessionListener::ALLJOYN_SESSIONLOST_INVALID, sessionListenerJoiner.lastReason);
                        }
                    }
                }

                if (sessionJoiner2InSession == true) {
                    if (selfJoinLeaveWithJoined) {
                        EXPECT_EQ((SessionId)0, sessionListenerJoiner2.sessionMemberRemovedSessionId);
                        EXPECT_EQ(0, sessionListenerJoiner2.sessionMemberRemovedCalled);
                        EXPECT_EQ(SessionListener::ALLJOYN_SESSIONLOST_INVALID, sessionListenerJoiner2.lastReason);

                    } else {
                        EXPECT_EQ(sessionId, sessionListenerJoiner2.sessionMemberRemovedSessionId);
                        EXPECT_EQ(1, sessionListenerJoiner2.sessionMemberRemovedCalled);
                        EXPECT_STREQ(busHost.GetUniqueName().c_str(), sessionListenerJoiner2.sessionMemberRemovedUniqueName.c_str());
                        if (members == 1) {
                            EXPECT_EQ(SessionListener::ALLJOYN_SESSIONLOST_REMOTE_END_LEFT_SESSION, sessionListenerJoiner2.lastReason);
                        } else {
                            EXPECT_EQ(SessionListener::ALLJOYN_SESSIONLOST_INVALID, sessionListenerJoiner2.lastReason);
                        }
                    }
                }
            }
            break;

        case HOST_REMOVES_JOINER2:
        case JOINER2_LEAVES:
            removeOrLeave = &busJoiner2;
            removeOrLeaveListener = &sessionListenerJoiner2;
            removeOrLeaveInSession = &sessionJoiner2InSession;
            otherJoiner = &busJoiner;
            otherJoinerInSession = &sessionJoinerInSession;
            otherJoinerListener = &sessionListenerJoiner;

        /* FALLTHROUGH */
        case HOST_REMOVES_JOINER:
        case JOINER_LEAVES:
            {
                bool selfJoinRemoveOrLeave = false;
                if (removeOrLeave == NULL) {
                    removeOrLeave = &busJoiner;
                    removeOrLeaveListener = &sessionListenerJoiner;
                    removeOrLeaveInSession = &sessionJoinerInSession;
                    otherJoiner = &busJoiner2;
                    otherJoinerListener = &sessionListenerJoiner2;
                    otherJoinerInSession = &sessionJoiner2InSession;
                }
                if (removeOrLeave == &busHost && sessionHostInSession) {
                    selfJoinRemoveOrLeave = true;
                }
                assert(removeOrLeaveListener->sessionLostCalled == 0);
                if (*sa == HOST_REMOVES_JOINER || *sa == HOST_REMOVES_JOINER2) {
                    EXPECT_EQ(ER_OK, busHost.RemoveSessionMember(sessionId, removeOrLeave->GetUniqueName()));
                } else {
                    EXPECT_EQ(ER_OK, removeOrLeave->LeaveJoinedSession(sessionId));
                }
                qcc::Sleep(200);
                *removeOrLeaveInSession = false;
                --members;


                if (sessionHostInSession == true) {
                    EXPECT_EQ(1, sessionListenerHost.sessionMemberRemovedCalled);
                    EXPECT_EQ(sessionId, sessionListenerHost.sessionMemberRemovedSessionId);
                    EXPECT_STREQ(removeOrLeave->GetUniqueName().c_str(), sessionListenerHost.sessionMemberRemovedUniqueName.c_str());
                    if (members == 1) {
                        EXPECT_EQ(SessionListener::ALLJOYN_SESSIONLOST_REMOTE_END_LEFT_SESSION, sessionListenerHost.lastReason);
                    } else {
                        EXPECT_EQ(SessionListener::ALLJOYN_SESSIONLOST_INVALID, sessionListenerHost.lastReason);
                    }
                }

                if (*otherJoinerInSession == true) {
                    if (selfJoinRemoveOrLeave == true) {
                        EXPECT_EQ((SessionId)0, otherJoinerListener->sessionMemberRemovedSessionId);
                        EXPECT_EQ(0, otherJoinerListener->sessionMemberRemovedCalled);
                        EXPECT_EQ(SessionListener::ALLJOYN_SESSIONLOST_INVALID, otherJoinerListener->lastReason);

                    } else {
                        EXPECT_EQ(sessionId, otherJoinerListener->sessionMemberRemovedSessionId);
                        EXPECT_STREQ(removeOrLeave->GetUniqueName().c_str(), otherJoinerListener->sessionMemberRemovedUniqueName.c_str());
                        EXPECT_EQ(1, otherJoinerListener->sessionMemberRemovedCalled);
                        if (members == 1) {
                            EXPECT_EQ(SessionListener::ALLJOYN_SESSIONLOST_REMOTE_END_LEFT_SESSION, otherJoinerListener->lastReason);
                        } else {
                            EXPECT_EQ(SessionListener::ALLJOYN_SESSIONLOST_INVALID, otherJoinerListener->lastReason);
                        }
                    }
                }


                if (*sa == HOST_REMOVES_JOINER || *sa == HOST_REMOVES_JOINER2) {
                    EXPECT_EQ(sessionId, removeOrLeaveListener->sessionMemberRemovedSessionId);
                    if (&busHost == otherJoiner) { /* special casing for selfjoin... */
                        EXPECT_EQ(members - 1, removeOrLeaveListener->sessionMemberRemovedCalled);
                    } else {
                        EXPECT_EQ(members, removeOrLeaveListener->sessionMemberRemovedCalled);
                    }

                    EXPECT_EQ((size_t)0, removeOrLeaveListener->sessionMembers.size());
                    if (removeOrLeave == &busHost) {
                        EXPECT_EQ(SessionListener::ALLJOYN_SESSIONLOST_REMOVED_BY_BINDER_SELF, removeOrLeaveListener->lastReason);
                    } else {
                        EXPECT_EQ(SessionListener::ALLJOYN_SESSIONLOST_REMOVED_BY_BINDER, removeOrLeaveListener->lastReason);
                    }
                } else {
                    EXPECT_EQ((SessionId)0, removeOrLeaveListener->sessionMemberRemovedSessionId);
                    EXPECT_STREQ("", removeOrLeaveListener->sessionMemberRemovedUniqueName.c_str());
                    EXPECT_EQ(0, removeOrLeaveListener->sessionMemberRemovedCalled);
                    EXPECT_EQ(SessionListener::ALLJOYN_SESSIONLOST_INVALID, removeOrLeaveListener->lastReason);
                }
            }
            break;

        case SIGNAL:
            signalobjects[&busHost]->signalReceived = 0U;
            signalobjects[&busJoiner]->signalReceived = 0U;
            signalobjects[&busJoiner2]->signalReceived = 0U;

            if (sessionHostInSession) {
                testobjects[&busHost]->SendSignal(sessionId);
                //Wait upto 1 seconds all callbacks and listeners to be called.
                for (int i = 0; i < 300; ++i) {
                    if ((!sessionJoinerInSession || signalobjects[&busJoiner]->signalReceived > 0) && (!sessionJoiner2InSession || signalobjects[&busJoiner2]->signalReceived > 0)) {
                        break;
                    }
                    qcc::Sleep(10);
                }
                qcc::Sleep(10);


                if (sessionJoinerInSession) {
                    EXPECT_EQ(1U, signalobjects[&busJoiner]->signalReceived);
                }

                if (sessionJoiner2InSession) {
                    EXPECT_EQ(1U, signalobjects[&busJoiner2]->signalReceived);
                }
                if ((&busHost == &busJoiner && sessionJoinerInSession) || (&busHost == &busJoiner2 && sessionJoiner2InSession)) {
                    EXPECT_EQ(1U, signalobjects[&busHost]->signalReceived);
                } else {
                    EXPECT_EQ(0U, signalobjects[&busHost]->signalReceived);
                }
            }

            signalobjects[&busHost]->signalReceived = 0U;
            signalobjects[&busJoiner]->signalReceived = 0U;
            signalobjects[&busJoiner2]->signalReceived = 0U;

            if (sessionJoinerInSession) {
                testobjects[&busJoiner]->SendSignal(sessionId);
                //Wait upto 1 seconds all callbacks and listeners to be called.
                for (int i = 0; i < 300; ++i) {
                    if ((!sessionHostInSession || signalobjects[&busHost]->signalReceived > 0) && (!sessionJoiner2InSession || signalobjects[&busJoiner2]->signalReceived > 0)) {
                        break;
                    }
                    qcc::Sleep(10);
                }
                qcc::Sleep(10);


                if (sessionHostInSession) {
                    EXPECT_EQ(1U, signalobjects[&busHost]->signalReceived);
                }

                if (sessionJoiner2InSession) {
                    EXPECT_EQ(1U, signalobjects[&busJoiner2]->signalReceived);
                }

                if ((&busHost == &busJoiner && sessionHostInSession) || (&busJoiner == &busJoiner2 && sessionJoiner2InSession)) {
                    EXPECT_EQ(1U, signalobjects[&busJoiner]->signalReceived);
                } else {
                    EXPECT_EQ(0U, signalobjects[&busJoiner]->signalReceived);
                }
            }

            signalobjects[&busHost]->signalReceived = 0U;
            signalobjects[&busJoiner]->signalReceived = 0U;
            signalobjects[&busJoiner2]->signalReceived = 0U;

            if (sessionJoiner2InSession) {
                testobjects[&busJoiner2]->SendSignal(sessionId);
                //Wait upto 1 seconds all callbacks and listeners to be called.
                for (int i = 0; i < 300; ++i) {
                    if ((!sessionHostInSession || signalobjects[&busHost]->signalReceived > 0) && (!sessionJoinerInSession || signalobjects[&busJoiner]->signalReceived > 0)) {
                        break;
                    }
                    qcc::Sleep(10);
                }
                qcc::Sleep(10);


                if (sessionHostInSession) {
                    EXPECT_EQ(1U, signalobjects[&busHost]->signalReceived);
                }

                if (sessionJoinerInSession) {
                    EXPECT_EQ(1U, signalobjects[&busJoiner]->signalReceived);
                }

                if ((&busHost == &busJoiner2 && sessionHostInSession) || (&busJoiner == &busJoiner2 && sessionJoinerInSession)) {
                    EXPECT_EQ(1U, signalobjects[&busJoiner2]->signalReceived);
                } else {
                    EXPECT_EQ(0U, signalobjects[&busJoiner2]->signalReceived);
                }
            }

        case STOP:
            break;

        }

        sessionListenerHost.ResetMemberAddedRemoved();
        sessionListenerJoiner.ResetMemberAddedRemoved();
        sessionListenerJoiner2.ResetMemberAddedRemoved();


    }


    /* clean up the session to avoid callbacks after this function returns */
    busHost.LeaveSession(sessionId);
    busJoiner.LeaveSession(sessionId);
    busJoiner2.LeaveSession(sessionId);

    qcc::Sleep(100);         /* let all callbacks finish */

}

TEST_F(SessionTest, MultipointSelfJoinRemoveMember) {

    QStatus status = ER_FAIL;
    /* make sure global flags are initialized */
    sessionJoinedFlag = false;
    sessionLostFlagA = false;
    sessionMemberAddedFlagA = false;
    sessionMemberRemovedFlagA = false;
    sessionMemberAddedCounter = 0;
    sessionMemberRemovedCounter = 0;
    sessionLostCounter = 0;
    sessionJoinedCounter = 0;

    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, true, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);

    RemoveSessionMemberBusAListener sessionListener(&busA);
    SessionPort port = 0;

    status = busA.BindSessionPort(port, opts, sessionListener);
    EXPECT_EQ(ER_OK, status);

    SessionId sessionId;

    status = busA.JoinSession(wkns[&busA].c_str(), port, &sessionListener, sessionId, opts);
    EXPECT_EQ(ER_OK, status);

    EXPECT_TRUE(sessionJoinerAcceptedFlag);

    //Wait upto 3 seconds all callbacks and listeners to be called.
    for (int i = 0; i < 300; ++i) {
        if (sessionJoinedFlag && sessionMemberAddedFlagA) {
            break;
        }
        qcc::Sleep(10);
    }

    EXPECT_TRUE(sessionJoinedFlag);
    EXPECT_TRUE(sessionMemberAddedFlagA);
    EXPECT_EQ(2, sessionMemberAddedCounter);
    EXPECT_EQ(1, sessionJoinedCounter);

    /* test we can remove ourselves from a multipoint session */
    status = busA.RemoveSessionMember(sessionId, busA.GetUniqueName());
    EXPECT_EQ(ER_OK, status);

    //Wait upto 2 seconds all callbacks and listeners to be called.
    for (int i = 0; i < 200; ++i) {
        if (sessionLostFlagA && sessionMemberRemovedFlagA) {
            break;
        }
        qcc::Sleep(10);
    }

    EXPECT_TRUE(sessionLostFlagA);
    EXPECT_TRUE(sessionMemberRemovedFlagA);
    EXPECT_EQ(2, sessionMemberRemovedCounter);
    EXPECT_EQ(2, sessionLostCounter);

}

TEST_F(SessionTest, MultipointExtended_AB_C_2ndJoiner_B_leaves_C_leaves) {
    SessionAction actions[] = { SIGNAL, JOINER_LEAVES, SIGNAL, JOINER2_LEAVES, STOP };
    MultipointMultipeerTest(busA, busB, busC, actions);
}

TEST_F(SessionTest, MultipointExtended_AB_C_2ndJoiner_B_leaves_C_removed) {
    SessionAction actions[] = { SIGNAL, JOINER_LEAVES, SIGNAL, HOST_REMOVES_JOINER2, STOP };
    MultipointMultipeerTest(busA, busB, busC, actions);
}


TEST_F(SessionTest, MultipointExtended_AB_C_2ndJoiner_B_removed_C_leaves) {
    SessionAction actions[] = { SIGNAL, HOST_REMOVES_JOINER, SIGNAL, JOINER2_LEAVES, STOP };
    MultipointMultipeerTest(busA, busB, busC, actions);
}

TEST_F(SessionTest, MultipointExtended_AB_C_2ndJoiner_B_removed_C_removed) {
    SessionAction actions[] = { SIGNAL, HOST_REMOVES_JOINER, SIGNAL, HOST_REMOVES_JOINER2, STOP };
    MultipointMultipeerTest(busA, busB, busC, actions);
}


TEST_F(SessionTest, MultipointExtended_AB_C_2ndJoiner_A_leaves_B_leaves) {
    SessionAction actions[] = { SIGNAL, HOST_LEAVES, SIGNAL, JOINER_LEAVES, STOP };
    MultipointMultipeerTest(busA, busB, busC, actions);
}


TEST_F(SessionTest, MultipointExtended_AB_A_2ndJoiner_B_leaves_Ajoiner_leaves) {
    SessionAction actions[] = { SIGNAL, JOINER_LEAVES, SIGNAL, JOINER2_LEAVES, STOP };
    MultipointMultipeerTest(busA, busB, busA, actions);
}

TEST_F(SessionTest, MultipointExtended_AB_A_2ndJoiner_B_leaves_Ajoiner_removed) {
    SessionAction actions[] = { SIGNAL, JOINER_LEAVES, SIGNAL, HOST_REMOVES_JOINER2, STOP };
    MultipointMultipeerTest(busA, busB, busA, actions);
}


TEST_F(SessionTest, MultipointExtended_AB_A_2ndJoiner_B_removed_Ajoiner_leaves) {
    SessionAction actions[] = { SIGNAL, HOST_REMOVES_JOINER, SIGNAL, JOINER2_LEAVES, STOP };
    MultipointMultipeerTest(busA, busB, busA, actions);
}

TEST_F(SessionTest, MultipointExtended_AB_A_2ndJoiner_B_removed_Ajoiner_removed) {
    SessionAction actions[] = { SIGNAL, HOST_REMOVES_JOINER, SIGNAL, HOST_REMOVES_JOINER2, STOP };
    MultipointMultipeerTest(busA, busB, busA, actions);
}


TEST_F(SessionTest, MultipointExtended_AA_B_2ndJoiner_Ajoiner_leaves_Ahost_leaves) {
    SessionAction actions[] = { SIGNAL, JOINER_LEAVES, SIGNAL, HOST_LEAVES, STOP };
    MultipointMultipeerTest(busA, busA, busB, actions);
}


TEST_F(SessionTest, MultipointExtended_AA_B_2ndJoiner_A_removes_A_as_joiner_Ahost_leaves) {
    SessionAction actions[] = { SIGNAL, HOST_REMOVES_JOINER, SIGNAL, HOST_LEAVES, STOP };
    MultipointMultipeerTest(busA, busA, busB, actions);
}


#ifdef QCC_OS_GROUP_POSIX
#include <unistd.h>

/* This test requires builtin router */
/* This test actually works but gets blocked somwhere deep inside IODispatch when run together with the other SessionTests */
TEST(SessionSystemTest, DISABLED_MultipointExtended_AA_B_2ndJoiner_A_removes_A_as_joiner_Ahost_leaves_forked) {
    pid_t child;
    int procstatus;
    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, true, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
    const char*wkn = "org.bla";
    SessionPort port = 80;
    SessionId sessionId;
    sessionJoinedCounter = 0;
    sessionJoinerAcceptedFlag = false;
    sessionJoinedFlag = false;

    /* We only fork B */
    if ((child = fork()) == 0) {
        qcc::Sleep(50); /* without sleep the builtin router would often emit problems */
        /* child */
        /* joiner2 */
        SessionJoinTestSessionListener sessionListenerJoiner2("joiner2");
        BusAttachment busB("test", true);
        QStatus status = ER_FAIL;
        status = busB.Start();
        ASSERT_EQ(ER_OK, status);
        status = busB.Connect("null:");
        ASSERT_EQ(ER_OK, status);

        status = busB.FindAdvertisedName(wkn);
        ASSERT_EQ(ER_OK, status);

        qcc::Sleep(50); /* Wait some time to join */

        status = busB.JoinSession(wkn, port, &sessionListenerJoiner2, sessionId, opts);
        ASSERT_EQ(ER_OK, status);

        //Wait upto 3 seconds all callbacks and listeners to be called.
        for (int i = 0; i < 300; ++i) {
            if (sessionListenerJoiner2.sessionMemberAddedCalled == 1) {
                break;
            }
            qcc::Sleep(10);
        }

        ASSERT_EQ(1U, sessionListenerJoiner2.sessionMemberAddedCalled);
        ASSERT_EQ(1U, sessionListenerJoiner2.sessionMembers.size());     /* sessionMembers is a set */

        /* At this moment both Ahost and Ajoiner are gone (and so is the session) */
        for (int i = 0; i < 300; ++i) {
            if (sessionListenerJoiner2.sessionMemberRemovedCalled == 1) {
                break;
            }
            qcc::Sleep(10);
        }
        ASSERT_EQ(1U, sessionListenerJoiner2.sessionMemberRemovedCalled);
        ASSERT_EQ(1U, sessionListenerJoiner2.sessionLostCalled);
        EXPECT_EQ(SessionListener::ALLJOYN_SESSIONLOST_REMOTE_END_LEFT_SESSION, sessionListenerJoiner2.lastReason);

        busB.Disconnect();
        busB.Stop();
        busB.Join();
        exit(0);

    } else {
        /* parent */
        /* host, joiner */
        BusAttachment busA("test", true);
        QStatus status = ER_FAIL;
        status = busA.Start();
        EXPECT_EQ(ER_OK, status);
        status = busA.Connect("null:");
        EXPECT_EQ(ER_OK, status);

        SessionJoinTestSessionListener sessionListenerHost("host");
        SessionJoinTestSessionListener sessionListenerJoiner("joiner");
        SessionJoinedSessionPortListener sessionPortListener(busA, &sessionListenerHost);

        status = busA.BindSessionPort(port, opts, sessionPortListener);
        EXPECT_EQ(ER_OK, status);

        status = busA.RequestName(wkn, DBUS_NAME_FLAG_DO_NOT_QUEUE);
        EXPECT_EQ(ER_OK, status);
        status = busA.AdvertiseName(wkn, TRANSPORT_ANY);
        EXPECT_EQ(ER_OK, status);



        /* Joiner 1 */
        status = busA.JoinSession(wkn, port, &sessionListenerJoiner, sessionId, opts);
        EXPECT_EQ(ER_OK, status);

        EXPECT_TRUE(sessionJoinerAcceptedFlag);
        //Wait upto 50 seconds all callbacks and listeners to be called.
        for (int i = 0; i < 500; ++i) {
            if (sessionJoinedCounter == 2) {
                break;
            }
            qcc::Sleep(100);
        }

        EXPECT_TRUE(sessionJoinedFlag);
        EXPECT_EQ(sessionId, bindMemberSessionId);

        sessionJoinerAcceptedFlag = false;
        sessionJoinedFlag = false;

        EXPECT_EQ(2, sessionJoinedCounter);
        EXPECT_EQ(2U, sessionListenerHost.sessionMemberAddedCalled);
        EXPECT_EQ(2U, sessionListenerHost.sessionMembers.size());
        EXPECT_EQ(2U, sessionListenerJoiner.sessionMemberAddedCalled);
        EXPECT_EQ(2U, sessionListenerJoiner.sessionMembers.size());

        std::set<String> membersCopy = sessionListenerJoiner.sessionMembers;
        membersCopy.erase(busA.GetUniqueName());
        EXPECT_EQ(1U, membersCopy.size());

        status = busA.RemoveSessionMember(sessionId, busA.GetUniqueName());
        EXPECT_EQ(ER_OK, status);

        //Wait upto 1 seconds all callbacks and listeners to be called.
        for (int i = 0; i < 100; ++i) {
            if (sessionListenerHost.sessionMemberRemovedCalled == 1 &&
                sessionListenerJoiner.sessionMemberRemovedCalled == 2) {
                break;
            }
            qcc::Sleep(10);
        }

        EXPECT_EQ(1U, sessionListenerHost.sessionMemberRemovedCalled);
        EXPECT_EQ(2U, sessionListenerJoiner.sessionMemberRemovedCalled);
        EXPECT_EQ(0U, sessionListenerHost.sessionLostCalled);
        EXPECT_EQ(1U, sessionListenerJoiner.sessionLostCalled);
        EXPECT_EQ(SessionListener::ALLJOYN_SESSIONLOST_REMOVED_BY_BINDER_SELF, sessionListenerJoiner.lastReason);

        status = busA.LeaveSession(sessionId);
        EXPECT_EQ(ER_OK, status);

        if (waitpid(child, &procstatus, 0) < 0) {
            perror("waitpid");
            FAIL();
        }

        EXPECT_TRUE(WIFEXITED(procstatus));

        busA.Disconnect();
        busA.Stop();
        busA.Join();

    }

}
#endif

TEST_F(SessionTest, MultipointExtended_AA_B_2ndJoiner_Ahost_leaves_Ajoiner_leaves) {
    SessionAction actions[] = { SIGNAL, HOST_LEAVES, SIGNAL, JOINER_LEAVES, STOP };
    MultipointMultipeerTest(busA, busA, busB, actions);
}

TEST_F(SessionTest, MultipointExtended_AA_B_2ndJoiner_Ahost_leaves_B_leaves) {
    SessionAction actions[] = { SIGNAL, HOST_LEAVES, SIGNAL, JOINER2_LEAVES, STOP };
    MultipointMultipeerTest(busA, busA, busB, actions);
}

