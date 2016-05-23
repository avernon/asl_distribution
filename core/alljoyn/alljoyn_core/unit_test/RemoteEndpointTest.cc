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

#include "RemoteEndpoint.h"

/* Header files included for Google Test Framework */
#include <gtest/gtest.h>
#include "ajTestCommon.h"

using namespace std;
using namespace qcc;
using namespace ajn;

class TestStream : public Stream {
  public:
    bool shutdown;
    bool aborted;
    bool closed;
    Event sourceEvent;
    Event sinkEvent;
    TestStream() : shutdown(false), aborted(false), closed(false) { }

    virtual QStatus PullBytes(void*, size_t, size_t& actualBytes, uint32_t) { actualBytes = 0; return ER_SOCK_OTHER_END_CLOSED; }
    virtual QStatus PullBytesAndFds(void*, size_t, size_t& actualBytes, SocketFd*, size_t& numFds, uint32_t) { actualBytes = 0; numFds = 0; return ER_SOCK_OTHER_END_CLOSED; }
    virtual Event& GetSourceEvent() { return sourceEvent; }

    virtual QStatus PushBytes(const void*, size_t numBytes, size_t& numSent) { numSent = numBytes; return ER_OK; }
    virtual Event& GetSinkEvent() { return sinkEvent; }

    virtual QStatus Shutdown() { shutdown = true; return ER_OK; }
    virtual QStatus Abort() { aborted = true; return ER_OK; }
    virtual void Close() { closed = true; }
};

class _TestMessage : public _Message {
  public:
    _TestMessage(BusAttachment& bus) : _Message(bus) {
        EXPECT_EQ(ER_OK, SignalMsg("", "sender", NULL, 0, "/path", "iface", "signalName", NULL, 0, 0, 0));
    }
    _TestMessage(BusAttachment& bus, const char* sender) : _Message(bus) {
        EXPECT_EQ(ER_OK, SignalMsg("", sender, NULL, 0, "/path", "iface", "signalName", NULL, 0, 0, 0));
    }
    virtual ~_TestMessage() { }
};
typedef qcc::ManagedObj<_TestMessage> TestMessage;

class _TestRemoteEndpoint : public _RemoteEndpoint {
  public:
    _TestRemoteEndpoint(const char* uniqueName, BusAttachment& bus, bool incoming, const qcc::String& connectSpec, qcc::Stream* stream)
        : _RemoteEndpoint(bus, incoming, connectSpec, stream) {
        SetUniqueName(uniqueName);
        GetFeatures().protocolVersion = 3;
    }
    virtual ~_TestRemoteEndpoint() { }
    QStatus SetLinkTimeout(uint32_t idleTimeout, uint32_t probeTimeout, uint32_t maxIdleProbes) {
        return _RemoteEndpoint::SetLinkTimeout(idleTimeout, probeTimeout, maxIdleProbes);
    }
};
typedef qcc::ManagedObj<_TestRemoteEndpoint> TestRemoteEndpoint;

class RemoteEndpointTest : public testing::Test {
  public:
    BusAttachment bus;
    bool incoming;
    const String connectSpec;
    TestStream ts;
    Stream* s;
    TestRemoteEndpoint rep;
    RemoteEndpointTest() : bus("RemoteEndpointTest"), incoming(false), s(&ts), rep(":test.2", bus, incoming, connectSpec, s) { }
    void SetUp() {
        EXPECT_EQ(ER_OK, bus.Start());
        EXPECT_EQ(ER_OK, rep->Start());
    }
    void TearDown() {
        rep->Stop();
        rep->Join(0);
    }
};

TEST_F(RemoteEndpointTest, PushMessageAfterStopFails)
{
    EXPECT_EQ(ER_OK, rep->Stop());
    TestMessage tm(bus);
    Message m = Message::cast(tm);
    EXPECT_NE(ER_OK, rep->PushMessage(m));
}

TEST_F(RemoteEndpointTest, OrderlyReleaseWhenTxQueueIsEmpty)
{
    EXPECT_EQ(ER_OK, rep->Stop());
    ts.sourceEvent.SetEvent();
    EXPECT_EQ(ER_OK, rep->Join(40 * 1000));

    /* Verify that we got an orderly release and that the txQueue is empty */
    EXPECT_TRUE(ts.shutdown);
    EXPECT_FALSE(ts.aborted);
    EXPECT_TRUE(ts.closed);
}

TEST_F(RemoteEndpointTest, OrderlyReleaseWhenTxQueueIsNotEmpty)
{
    /*
     * Push some msgs into the txQueue
     */
    TestMessage tm(bus);
    Message m = Message::cast(tm);
    EXPECT_EQ(ER_OK, rep->PushMessage(m));

    EXPECT_EQ(ER_OK, rep->Stop());
    ts.sinkEvent.SetEvent();
    ts.sourceEvent.SetEvent();
    EXPECT_EQ(ER_OK, rep->Join(40 * 1000));

    /* Verify that we got an orderly release and that the txQueue is empty */
    EXPECT_TRUE(ts.shutdown);
    EXPECT_FALSE(ts.aborted);
    EXPECT_TRUE(ts.closed);
}

TEST_F(RemoteEndpointTest, AbortiveRelease)
{
    EXPECT_EQ(ER_OK, rep->Join(0));

    /* Verify that we got an abortive release */
    EXPECT_FALSE(ts.shutdown);
    EXPECT_TRUE(ts.aborted);
    EXPECT_TRUE(ts.closed);
}

TEST_F(RemoteEndpointTest, RxTimeout)
{
    EXPECT_EQ(ER_OK, rep->SetLinkTimeout(1, 1, 1));
    EXPECT_EQ(ER_OK, rep->Join(40 * 1000));
}

class TxTestStream : public TestStream {
  public:
    QStatus status;
    virtual QStatus PushBytes(const void*, size_t numBytes, size_t& numSent) {
        numSent = numBytes;
        sinkEvent.ResetEvent();
        return status;
    }
};

TEST_F(RemoteEndpointTest, TxTimeout)
{
    TxTestStream tts;
    s = &tts;
    TestRemoteEndpoint trep(":test.3", bus, incoming, connectSpec, s);
    EXPECT_EQ(ER_OK, trep->Start(0U, 0U, 0U, 1U)); /* Tx timeout of 1 sec. */
    /*
     * Tx timeout will kick in once we have a partial message push.
     */
    TestMessage tm(bus);
    Message m = Message::cast(tm);
    EXPECT_EQ(ER_OK, trep->PushMessage(m));
    tts.status = ER_TIMEOUT;
    tts.sinkEvent.SetEvent();
    EXPECT_EQ(ER_OK, trep->Join(40 * 1000));

    /* Verify that we got an abortive release */
    EXPECT_FALSE(tts.shutdown);
    EXPECT_TRUE(tts.aborted);
    EXPECT_TRUE(tts.closed);
}

TEST_F(RemoteEndpointTest, TxFail)
{
    TxTestStream tts;
    s = &tts;
    TestRemoteEndpoint trep(":test.3", bus, incoming, connectSpec, s);
    EXPECT_EQ(ER_OK, trep->Start());
    TestMessage tm(bus);
    Message m = Message::cast(tm);
    EXPECT_EQ(ER_OK, trep->PushMessage(m));
    tts.status = ER_FAIL;
    tts.sinkEvent.SetEvent();
    EXPECT_EQ(ER_OK, trep->Join(40 * 1000));

    /* Verify that we got an abortive release */
    EXPECT_FALSE(tts.shutdown);
    EXPECT_TRUE(tts.aborted);
    EXPECT_TRUE(tts.closed);
}

#ifdef ROUTER
#include "DaemonRouter.h"

class TestBusAttachment : public BusAttachment {
  public:
    TransportFactoryContainer factories;
    TestBusAttachment() : BusAttachment(new Internal("RemoteEndpointTest", *this, factories, new DaemonRouter, true, "", 4), 4) { }
};

TEST_F(RemoteEndpointTest, TxMaxControlMessages)
{
    TestBusAttachment tb;
    EXPECT_EQ(ER_OK, tb.Start());
    TxTestStream tts;
    s = &tts;
    TestRemoteEndpoint trep(":test.3", tb, incoming, connectSpec, s);
    EXPECT_EQ(ER_OK, trep->Start());
    QStatus status = ER_OK;
    while (status == ER_OK) {
        TestMessage tm(bus, "sender.1");
        Message m = Message::cast(tm);
        status = trep->PushMessage(m);
    }
    EXPECT_EQ(ER_OK, trep->Join());

    /* Verify that we got an abortive release */
    EXPECT_FALSE(tts.shutdown);
    EXPECT_TRUE(tts.aborted);
    EXPECT_TRUE(tts.closed);
}
#endif /* ROUTER */

static ThreadReturn STDCALL PushMessages(void* arg)
{
    RemoteEndpointTest* thiz = reinterpret_cast<RemoteEndpointTest*>(arg);
    TestMessage tm(thiz->bus);
    Message m = Message::cast(tm);
    EXPECT_EQ(ER_OK, thiz->rep->PushMessage(m));
    EXPECT_EQ(ER_OK, thiz->rep->PushMessage(m)); /* This will block */
    return 0;
}

TEST_F(RemoteEndpointTest, TxQueueIsFull)
{
    Thread pmThread("PushMessages", PushMessages);
    EXPECT_EQ(ER_OK, pmThread.Start(reinterpret_cast<void*>(this)));
    qcc::Sleep(500); /* Wait for PushMessages thread to block */
    EXPECT_EQ(ER_OK, rep->Stop());
    ts.sinkEvent.SetEvent();
    ts.sourceEvent.SetEvent();
    EXPECT_EQ(ER_OK, rep->Join(40 * 1000));
    EXPECT_EQ(ER_OK, pmThread.Join());
    /* Test passes if both PushMessage() calls succeed. */
}

TEST_F(RemoteEndpointTest, CreateDestroy)
{
    {
        TestRemoteEndpoint trep(":test.3", bus, incoming, connectSpec, s);
    }
}
