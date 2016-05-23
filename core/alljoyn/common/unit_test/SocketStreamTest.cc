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

#include <qcc/Environ.h>
#include <qcc/SocketStream.h>
#include <qcc/Thread.h>
#include <qcc/Util.h>

/* Header files included for Google Test Framework */
#include <gtest/gtest.h>

using namespace std;
using namespace qcc;

static ThreadReturn STDCALL ServerAccept(void* arg)
{
    SocketFd serverFd = reinterpret_cast<intptr_t>(arg);
    IPAddress clientAddr;
    uint16_t clientPort;
    SocketFd clientFd = INVALID_SOCKET_FD;
    EXPECT_EQ(ER_OK, Accept(serverFd, clientAddr, clientPort, clientFd));
    EXPECT_EQ(ER_OK, SetBlocking(clientFd, true));
    return reinterpret_cast<ThreadReturn>(clientFd);
}

class SocketStreamTest : public testing::Test {
  public:
    SocketFd serverFd;
    IPAddress serverAddr;
    uint16_t serverPort;
    SocketFd clientFd;
    SocketFd acceptedFd;
    uint8_t buf[32768];
    size_t numBytes;
    QStatus status;

    virtual void SetUp()
    {
        serverFd = INVALID_SOCKET_FD;
        clientFd = INVALID_SOCKET_FD;
        acceptedFd = INVALID_SOCKET_FD;

        /* Server SetUp */
        EXPECT_EQ(ER_OK, Socket(QCC_AF_INET, QCC_SOCK_STREAM, serverFd));
        serverAddr = Environ::GetAppEnviron()->Find("IP_ADDRESS", "127.0.0.1");
        serverPort = 0;
        EXPECT_EQ(ER_OK, Bind(serverFd, serverAddr, serverPort));
        EXPECT_EQ(ER_OK, GetLocalAddress(serverFd, serverAddr, serverPort));
        EXPECT_EQ(ER_OK, Listen(serverFd, 1));

        /* Connect Server and Client */
        Thread acceptThread("ServerAccept", ServerAccept);
        EXPECT_EQ(ER_OK, acceptThread.Start(reinterpret_cast<void*>(serverFd)));
        EXPECT_EQ(ER_OK, Socket(QCC_AF_INET, QCC_SOCK_STREAM, clientFd));
        EXPECT_EQ(ER_OK, qcc::Connect(clientFd, serverAddr, serverPort));
        EXPECT_EQ(ER_OK, SetBlocking(clientFd, true));
        EXPECT_EQ(ER_OK, acceptThread.Join());
        acceptedFd = reinterpret_cast<intptr_t>(acceptThread.GetExitValue());
    }

    virtual void TearDown()
    {
        Close(acceptedFd);
        Close(clientFd);
        Close(serverFd);
    }

    void Close(SocketFd& sockFd)
    {
        if (sockFd != INVALID_SOCKET_FD) {
            qcc::Close(sockFd);
            sockFd = INVALID_SOCKET_FD;
        }
    }
};

class SocketStreamTestErrors : public SocketStreamTest {
};

TEST_F(SocketStreamTestErrors, PullBytesZero)
{
    SocketStream unconnected(QCC_AF_INET, QCC_SOCK_STREAM);
    EXPECT_EQ(ER_READ_ERROR, unconnected.PullBytes(buf, 0, numBytes));
    SocketStream connected(acceptedFd); acceptedFd = INVALID_SOCKET_FD;
    EXPECT_EQ(ER_OK, connected.PullBytes(buf, 0, numBytes));
}

TEST_F(SocketStreamTestErrors, PullBytesDisconnected)
{
    SocketStream unconnected(QCC_AF_INET, QCC_SOCK_STREAM);
    EXPECT_EQ(ER_READ_ERROR, unconnected.PullBytes(buf, 1, numBytes));
}

TEST_F(SocketStreamTestErrors, PullBytesTimeout)
{
    SocketStream connected(acceptedFd); acceptedFd = INVALID_SOCKET_FD;
    EXPECT_EQ(ER_OK, SetBlocking(connected.GetSocketFd(), false));
    EXPECT_EQ(ER_TIMEOUT, connected.PullBytes(buf, 1, numBytes, 0));
}

TEST_F(SocketStreamTestErrors, PullBytesAfterOrderlyRelease)
{
    SocketStream client(clientFd); clientFd = INVALID_SOCKET_FD;
    client.Shutdown();
    SocketStream connected(acceptedFd); acceptedFd = INVALID_SOCKET_FD;
    EXPECT_EQ(ER_SOCK_OTHER_END_CLOSED, connected.PullBytes(buf, 1, numBytes));
    EXPECT_EQ(0U, numBytes);
}

TEST_F(SocketStreamTestErrors, PullBytesAfterAbortiveRelease)
{
    SocketStream client(clientFd); clientFd = INVALID_SOCKET_FD;
    client.Abort();
    client.Close();
    SocketStream connected(acceptedFd); acceptedFd = INVALID_SOCKET_FD;
    EXPECT_EQ(ER_OS_ERROR, connected.PullBytes(buf, 1, numBytes));
}

TEST_F(SocketStreamTestErrors, PushBytesZero)
{
    SocketStream unconnected(QCC_AF_INET, QCC_SOCK_STREAM);
    EXPECT_EQ(ER_OK, unconnected.PushBytes(buf, 0, numBytes));
    SocketStream connected(acceptedFd); acceptedFd = INVALID_SOCKET_FD;
    EXPECT_EQ(ER_OK, connected.PushBytes(buf, 0, numBytes));
}

TEST_F(SocketStreamTestErrors, PushBytesDisconnected)
{
    SocketStream unconnected(QCC_AF_INET, QCC_SOCK_STREAM);
    EXPECT_EQ(ER_WRITE_ERROR, unconnected.PushBytes(buf, 1, numBytes));
}

TEST_F(SocketStreamTestErrors, PushBytesTimeout)
{
    SocketStream connected(acceptedFd); acceptedFd = INVALID_SOCKET_FD;
    /*
     * Set this artificially low to force a blocking send.  Otherwise
     * different behavior occurs depending on the TCP window size
     * (either would block or connection reset).
     */
    EXPECT_EQ(ER_OK, SetSndBuf(connected.GetSocketFd(), 8192));
    EXPECT_EQ(ER_OK, SetBlocking(connected.GetSocketFd(), false));
    connected.SetSendTimeout(0);
    while ((status = connected.PushBytes(buf, ArraySize(buf), numBytes)) == ER_OK)
        ;
    EXPECT_EQ(ER_TIMEOUT, status);
}

TEST_F(SocketStreamTestErrors, PushBytesAfterAbortiveRelease)
{
    SocketStream client(clientFd); clientFd = INVALID_SOCKET_FD;
    client.Abort();
    client.Close();
    SocketStream connected(acceptedFd); acceptedFd = INVALID_SOCKET_FD;
    while ((status = connected.PushBytes(buf, ArraySize(buf), numBytes)) == ER_OK)
        ;
    EXPECT_EQ(ER_OS_ERROR, status);
}

class SocketStreamTestAndFdsErrors : public testing::Test {
  public:
    SocketFd endpoint[2];
    SocketFd clientFd;
    SocketFd acceptedFd;
    uint8_t buf[2048];
    size_t numBytes;
    SocketFd fds[SOCKET_MAX_FILE_DESCRIPTORS + 1];
    size_t numFds;
    QStatus status;

    virtual void SetUp()
    {
        EXPECT_EQ(ER_OK, SocketPair(endpoint));
        clientFd = endpoint[0];
        acceptedFd = endpoint[1];
        for (size_t i = 0; i < ArraySize(fds); ++i) {
            EXPECT_EQ(ER_OK, Socket(QCC_AF_INET, QCC_SOCK_STREAM, fds[i]));
        }
        numFds = SOCKET_MAX_FILE_DESCRIPTORS;
    }

    virtual void TearDown()
    {
        for (size_t i = 0; i < ArraySize(fds); ++i) {
            Close(fds[i]);
        }
        Close(acceptedFd);
        Close(clientFd);
    }

    void Close(SocketFd& sockFd)
    {
        if (sockFd != INVALID_SOCKET_FD) {
            qcc::Close(sockFd);
            sockFd = INVALID_SOCKET_FD;
        }
    }
};

TEST_F(SocketStreamTestAndFdsErrors, PullBytesAndFdsDisconnected)
{
    SocketStream unconnected(QCC_AF_INET, QCC_SOCK_STREAM);
    EXPECT_EQ(ER_READ_ERROR, unconnected.PullBytesAndFds(buf, 1, numBytes, fds, numFds));
}

TEST_F(SocketStreamTestAndFdsErrors, PullBytesAndFdsTimeout)
{
    SocketStream connected(acceptedFd); acceptedFd = INVALID_SOCKET_FD;
    EXPECT_EQ(ER_OK, SetBlocking(connected.GetSocketFd(), false));
    EXPECT_EQ(ER_TIMEOUT, connected.PullBytesAndFds(buf, 1, numBytes, fds, numFds, 0));
}

TEST_F(SocketStreamTestAndFdsErrors, PullBytesAndFdsBadArgs)
{
    SocketStream connected(acceptedFd); acceptedFd = INVALID_SOCKET_FD;
    EXPECT_EQ(ER_BAD_ARG_4, connected.PullBytesAndFds(buf, 1, numBytes, NULL, numFds, 0));
    numFds = 0;
    EXPECT_EQ(ER_BAD_ARG_5, connected.PullBytesAndFds(buf, 1, numBytes, fds, numFds, 0));
}

TEST_F(SocketStreamTestAndFdsErrors, PullBytesAndFdsAfterOrderlyRelease)
{
    SocketStream client(clientFd); clientFd = INVALID_SOCKET_FD;
    client.Shutdown();
    SocketStream connected(acceptedFd); acceptedFd = INVALID_SOCKET_FD;
    EXPECT_EQ(ER_SOCK_OTHER_END_CLOSED, connected.PullBytesAndFds(buf, 1, numBytes, fds, numFds));
    EXPECT_EQ(0U, numBytes);
}

TEST_F(SocketStreamTestAndFdsErrors, PullBytesAndFdsAfterAbortiveRelease)
{
    SocketStream client(clientFd); clientFd = INVALID_SOCKET_FD;
    client.Abort();
    client.Close();
    SocketStream connected(acceptedFd); acceptedFd = INVALID_SOCKET_FD;
    status = connected.PullBytesAndFds(buf, 1, numBytes, fds, numFds);
    /* Status depends on platform implementation of SocketPair. */
    EXPECT_TRUE((status == ER_SOCK_OTHER_END_CLOSED) || (status == ER_OS_ERROR));
}

TEST_F(SocketStreamTestAndFdsErrors, PushBytesAndFdsBadArgs)
{
    SocketStream connected(acceptedFd); acceptedFd = INVALID_SOCKET_FD;
    EXPECT_EQ(ER_BAD_ARG_2, connected.PushBytesAndFds(buf, 0, numBytes, fds, numFds, GetPid()));
    EXPECT_EQ(ER_BAD_ARG_4, connected.PushBytesAndFds(buf, 1, numBytes, NULL, numFds, GetPid()));
    EXPECT_EQ(ER_BAD_ARG_5, connected.PushBytesAndFds(buf, 1, numBytes, fds, 0, GetPid()));
}

TEST_F(SocketStreamTestAndFdsErrors, PushBytesAndFdsDisconnected)
{
    SocketStream unconnected(QCC_AF_INET, QCC_SOCK_STREAM);
    EXPECT_EQ(ER_WRITE_ERROR, unconnected.PushBytesAndFds(buf, 1, numBytes, fds, numFds, GetPid()));
}

TEST_F(SocketStreamTestAndFdsErrors, PushBytesAndFdsTimeout)
{
    SocketStream connected(acceptedFd); acceptedFd = INVALID_SOCKET_FD;
    /*
     * Set this artificially low to force a blocking send.  Otherwise
     * different behavior occurs depending on the TCP window size
     * (either would block or connection reset).
     */
    EXPECT_EQ(ER_OK, SetSndBuf(connected.GetSocketFd(), 8192));
    EXPECT_EQ(ER_OK, SetBlocking(connected.GetSocketFd(), false));
    connected.SetSendTimeout(0);
    while ((status = connected.PushBytesAndFds(buf, ArraySize(buf), numBytes, fds, numFds, GetPid())) == ER_OK)
        ;
    EXPECT_EQ(ER_TIMEOUT, status);
}

TEST_F(SocketStreamTestAndFdsErrors, PushBytesAndFdsAfterAbortiveRelease)
{
    SocketStream client(clientFd); clientFd = INVALID_SOCKET_FD;
    client.Abort();
    client.Close();
    SocketStream connected(acceptedFd); acceptedFd = INVALID_SOCKET_FD;
    EXPECT_EQ(ER_OS_ERROR, connected.PushBytesAndFds(buf, 1, numBytes, fds, numFds, GetPid()));
}

TEST_F(SocketStreamTest, DetachedShutdown)
{
    SocketFd dupFd;
    EXPECT_EQ(ER_OK, SocketDup(clientFd, dupFd));
    SocketStream client(clientFd); clientFd = INVALID_SOCKET_FD;

    client.DetachSocketFd();
    EXPECT_EQ(ER_OK, client.Shutdown());

    /* Verify underlying connection not shutdown by sending to it */
    EXPECT_EQ(ER_OK, Send(dupFd, buf, 1, numBytes));
    Close(dupFd);
}

TEST_F(SocketStreamTest, DetachedAbort)
{
    /* No cross-platform way to verify linger is not set currently. */
}

TEST_F(SocketStreamTest, DetachedClose)
{
    SocketFd dupFd;
    EXPECT_EQ(ER_OK, SocketDup(clientFd, dupFd));
    SocketStream client(clientFd); clientFd = INVALID_SOCKET_FD;

    client.DetachSocketFd();
    client.Close();

    /* Verify underlying connection not closed by sending to it */
    EXPECT_EQ(ER_OK, Send(dupFd, buf, 1, numBytes));
    Close(dupFd);
}
