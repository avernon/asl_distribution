/*
 * TCPTransport.h
 *
 *  Created on: May 29, 2015
 *      Author: erongo
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
#ifndef TCPTRANSPORT_H_
#define TCPTRANSPORT_H_

#include "TransportBase.h"
#include "IPTransport.h"

#include <mutex>
#include <map>
#include <list>

#include <qcc/IfConfig.h>
#include <qcc/Socket.h>

namespace nio {

class Proactor;

class TCPTransport : public IPTransport {

    class TCPEndpoint;

  public:

    static const std::string TransportName;

    TCPTransport(Proactor& proacator);

    TCPTransport(const TCPTransport&) = delete;
    TCPTransport& operator=(const TCPTransport&) = delete;

    ~TCPTransport();


    QStatus Send(Endpoint::Handle handle, MessageType msg, Endpoint::SendCompleteCB cb) override;
    QStatus Recv(Endpoint::Handle handle, MessageType msg, Endpoint::ReadMessageCB cb) override;

    QStatus Connect(const std::string& spec, ConnectedCB cb) override;
    QStatus Disconnect(Endpoint::Handle handle, bool force = false) override;


    QStatus Listen(const std::string& spec, AcceptedCB cb) override;
    QStatus StopListen(const std::string& spec) override;

  private:

    typedef std::shared_ptr<TCPEndpoint> TCPEndpointPtr;

    void EndpointDisconnected(TCPEndpointPtr ep);
    void CloseEndpoint(TCPEndpointPtr ep);

    TCPEndpointPtr CreateEndpoint(qcc::SocketFd sock, const qcc::IPAddress& addr, uint16_t port, bool incoming, const std::string& spec);
    TCPEndpointPtr GetEndpoint(Endpoint::Handle handle) const;
    void RemoveEndpoint(Endpoint::Handle handle);

    void WriteCallback(TCPEndpointPtr ep, MessageType msg, Endpoint::SendCompleteCB cb);
    void ReadCallback(TCPEndpointPtr ep, MessageType msg, Endpoint::ReadMessageCB cb);

    void AcceptCallback(qcc::SocketFd sock, AcceptedCB cb);

    uint32_t GetNumIncoming() const;


    typedef std::map<Endpoint::Handle, TCPEndpointPtr> EndpointMap;
    EndpointMap endpoints;
    mutable std::mutex endpoints_lock;
    uint32_t num_incoming;


    typedef std::map<std::string, TCPEndpointPtr> ListenMap;
    ListenMap listeners;
    std::mutex listeners_lock;

    // configuration
    uint32_t max_tcp_connections;
    uint32_t tcp_connect_timeout;
    uint32_t tcp_listen_backlog;
};

} /* namespace nio */

#endif /* TCPTRANSPORT_H_ */
