/**
 * @file
 * DaemonTransport implementation for Windows (Win32)
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
#include <qcc/IPAddress.h>
#include <qcc/Socket.h>
#include <qcc/SocketStream.h>
#include <qcc/String.h>
#include <qcc/StringUtil.h>

#include <alljoyn/BusAttachment.h>
#include <alljoyn/Session.h>

#include "BusInternal.h"
#include "RemoteEndpoint.h"
#include "Router.h"
#include "DaemonTransport.h"

#define QCC_MODULE "DAEMON_TRANSPORT"

using namespace std;
using namespace qcc;

namespace ajn {

const char* DaemonTransport::TransportName = "localhost";

class _DaemonEndpoint;

typedef ManagedObj<_DaemonEndpoint> DaemonEndpoint;

/*
 * An endpoint class to handle the details of authenticating a connection in
 * the Unix Domain Sockets way.
 */
class _DaemonEndpoint : public _RemoteEndpoint {
    friend class DaemonTransport;
  public:

    _DaemonEndpoint(DaemonTransport* transport, BusAttachment& bus, SocketFd sock) :
        _RemoteEndpoint(bus, true, DaemonTransport::TransportName, &stream, DaemonTransport::TransportName),
        m_transport(transport),
        stream(sock)
    {
    }

    ~_DaemonEndpoint() { }

    /**
     * TCP endpoint does not support UNIX style user, group, and process IDs.
     */
    bool SupportsUnixIDs() const { return false; }

    QStatus SetIdleTimeouts(uint32_t& reqIdleTimeout, uint32_t& reqProbeTimeout)
    {
        uint32_t maxIdleProbes = m_transport->m_numHbeatProbes;

        /* If reqProbeTimeout == 0, Make no change to Probe timeout. */
        if (reqProbeTimeout == 0) {
            reqProbeTimeout = _RemoteEndpoint::GetProbeTimeout();
        } else if (reqProbeTimeout > m_transport->m_maxHbeatProbeTimeout) {
            /* Max allowed Probe timeout is m_maxHbeatProbeTimeout */
            reqProbeTimeout = m_transport->m_maxHbeatProbeTimeout;
        }

        /* If reqIdleTimeout == 0, Make no change to Idle timeout. */
        if (reqIdleTimeout == 0) {
            reqIdleTimeout = _RemoteEndpoint::GetIdleTimeout();
        }

        /* Requested link timeout must be >= m_minHbeatIdleTimeout */
        if (reqIdleTimeout < m_transport->m_minHbeatIdleTimeout) {
            reqIdleTimeout = m_transport->m_minHbeatIdleTimeout;
        }

        /* Requested link timeout must be <= m_maxHbeatIdleTimeout */
        if (reqIdleTimeout > m_transport->m_maxHbeatIdleTimeout) {
            reqIdleTimeout = m_transport->m_maxHbeatIdleTimeout;
        }

        return _RemoteEndpoint::SetIdleTimeouts(reqIdleTimeout, reqProbeTimeout, maxIdleProbes);
    }

  private:
    DaemonTransport* m_transport;        /**< The DaemonTransport holding the connection */
    SocketStream stream;
};

static const uint32_t NUL_BYTE_TIMEOUT = 5000;

void* DaemonTransport::Run(void* arg)
{
    SocketFd listenFd = SocketFd(arg);
    QStatus status = ER_OK;

    Event* listenEvent = new Event(listenFd, Event::IO_READ);

    while (!IsStopping()) {

        status = Event::Wait(*listenEvent);
        if (status != ER_OK) {
            QCC_LogError(status, ("Event::Wait failed"));
            break;
        }
        SocketFd newSock;

        while (true) {
            status = Accept(listenFd, newSock);
            if (status != ER_OK) {
                break;
            }
            qcc::String authName;
            qcc::String redirection;
            DaemonTransport* trans = this;
            DaemonEndpoint conn(trans, bus, newSock);

            QCC_DbgHLPrintf(("DaemonTransport::Run(): Accepting connection newSock=%d", newSock));

            /* Initialized the features for this endpoint */
            conn->GetFeatures().isBusToBus = false;
            conn->GetFeatures().allowRemote = false;
            conn->GetFeatures().handlePassing = true;

            endpointListLock.Lock(MUTEX_CONTEXT);
            endpointList.push_back(RemoteEndpoint::cast(conn));
            endpointListLock.Unlock(MUTEX_CONTEXT);

            uint8_t byte;
            size_t nbytes;
            /*
             * Read the initial NUL byte
             */
            status = conn->stream.PullBytes(&byte, 1, nbytes, NUL_BYTE_TIMEOUT);
            if ((status != ER_OK) || (nbytes != 1) || (byte != 0)) {
                status = (status == ER_OK) ? ER_FAIL : status;
            } else {
                status = conn->Establish("ANONYMOUS", authName, redirection);
            }
            if (status == ER_OK) {
                status = conn->Start(m_defaultHbeatIdleTimeout, m_defaultHbeatProbeTimeout, m_numHbeatProbes, m_maxHbeatProbeTimeout);
            }
            if (status != ER_OK) {
                QCC_LogError(status, ("Error starting DaemonEndpoint"));
                endpointListLock.Lock(MUTEX_CONTEXT);
                list<RemoteEndpoint>::iterator ei = find(endpointList.begin(), endpointList.end(), RemoteEndpoint::cast(conn));
                if (ei != endpointList.end()) {
                    endpointList.erase(ei);
                }
                endpointListLock.Unlock(MUTEX_CONTEXT);
                conn->Invalidate();
            }
        }
        if (ER_WOULDBLOCK == status || ER_READ_ERROR == status) {
            status = ER_OK;
        }

        if (status != ER_OK) {
            QCC_LogError(status, ("Error accepting new connection. Ignoring..."));
        }
    }

    delete listenEvent;

    qcc::Close(listenFd);

    QCC_DbgPrintf(("DaemonTransport::Run is exiting status=%s", QCC_StatusText(status)));
    return (void*) status;
}

static const char* LocalLoopbackAddr = "127.0.0.1";

QStatus DaemonTransport::NormalizeTransportSpec(const char* inSpec, qcc::String& outSpec, map<qcc::String, qcc::String>& argMap) const
{
    QStatus status = ParseArguments(DaemonTransport::TransportName, inSpec, argMap);
    if (status == ER_OK) {
        if (!argMap["addr"].empty()) {
            return ER_BUS_BAD_TRANSPORT_ARGS;
        }
        qcc::String port = Trim(argMap["port"]);
        if (port.empty()) {
            return ER_BUS_BAD_TRANSPORT_ARGS;
        }
        uint32_t portNum = StringToU32(port);
        if (portNum < 0 || portNum > 0xffff) {
            return ER_BUS_BAD_TRANSPORT_ARGS;
        }
        outSpec += "localhost:port=" + port;
    }
    return status;
}

static QStatus ListenFd(map<qcc::String, qcc::String>& argMap, SocketFd& listenFd)
{
    IPAddress listenAddr(LocalLoopbackAddr);
    uint16_t listenPort = StringToU32(argMap["port"]);

    QStatus status = Socket(QCC_AF_INET, QCC_SOCK_STREAM, listenFd);
    if (status != ER_OK) {
        QCC_LogError(status, ("DaemonTransport::ListenFd(): Socket() failed"));
        return status;
    }
    /*
     * Set the SO_REUSEADDR socket option so we don't have to wait for four
     * minutes while the endponit is in TIME_WAIT if we crash (or control-C).
     */
    status = qcc::SetReuseAddress(listenFd, true);
    if (status != ER_OK) {
        QCC_LogError(status, ("DaemonTransport::ListenFd(): SetReuseAddress() failed"));
        return status;
    }
    /*
     * Bind the socket to the listen address and start listening for incoming
     * connections on it.
     */
    status = Bind(listenFd, listenAddr, listenPort);
    if (status != ER_OK) {
        QCC_LogError(status, ("DaemonTransport::ListenFd(): Bind() failed"));
    } else {
        status = qcc::Listen(listenFd, 0);
        if (status == ER_OK) {
            QCC_DbgPrintf(("DaemonTransport::ListenFd(): Listening on <localhost> port %d", listenPort));
        } else {
            QCC_LogError(status, ("DaemonTransport::ListenFd(): Listen failed"));
        }
    }
    return status;
}

QStatus DaemonTransport::StartListen(const char* listenSpec)
{
    if (stopping == true) {
        return ER_BUS_TRANSPORT_NOT_STARTED;
    }
    if (IsRunning()) {
        return ER_BUS_ALREADY_LISTENING;
    }
    /* Normalize the listen spec. */
    QStatus status;
    qcc::String normSpec;
    map<qcc::String, qcc::String> serverArgs;
    status = NormalizeTransportSpec(listenSpec, normSpec, serverArgs);
    if (status != ER_OK) {
        QCC_LogError(status, ("DaemonTransport::StartListen(): Invalid localhost listen spec \"%s\"", listenSpec));
        return status;
    }
    SocketFd listenFd = qcc::INVALID_SOCKET_FD;
    status = ListenFd(serverArgs, listenFd);
    if (status == ER_OK) {
        status = Thread::Start((void*)listenFd);
    }
    if ((listenFd != qcc::INVALID_SOCKET_FD) && (status != ER_OK)) {
        qcc::Close(listenFd);
    }
    return status;
}

QStatus DaemonTransport::StopListen(const char* listenSpec)
{
    return Thread::Stop();
}


} // namespace ajn
