/*
 * TransportManager.cc
 *
 *  Created on: Jun 3, 2015
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
#include "TransportManager.h"
#include "TransportBase.h"
#include "TCPTransport.h"
#include "UDPTransport.h"

using namespace nio;

TransportManager::TransportManager(Proactor& proactor) : proactor(proactor)
{

}

TransportManager::~TransportManager()
{

}

static std::string GetTransportName(const std::string& spec)
{
    size_t col = spec.find(':');
    assert(col != std::string::npos);
    return spec.substr(0, col);
}

TransportBase* TransportManager::CreateTransport(const std::string& name)
{
    if (name == TCPTransport::TransportName) {
        return new TCPTransport(proactor);
    } else if (name == UDPTransport::TransportName) {
        return new UDPTransport(proactor);
    } else {
        printf("Transport [%s] not found\n", name.c_str());
        return nullptr;
    }
}

TransportBase* TransportManager::GetTransport(const std::string& spec)
{
    TransportBase* transport = nullptr;

    std::string name = GetTransportName(spec);

    std::lock_guard<std::mutex> g(transports_lock);
    auto it = transports.find(name);
    if (it != transports.end()) {
        transport = it->second;
    } else {
        transport = CreateTransport(name);

        if (transport) {
            transports[name] = transport;
        }
    }

    return transport;
}

QStatus TransportManager::Listen(const std::string& spec, TransportBase::AcceptedCB cb)
{
    QStatus status = ER_BUS_TRANSPORT_NOT_AVAILABLE;
    TransportBase* transport = GetTransport(spec);
    if (transport) {
        status = transport->Listen(spec, cb);
    }

    return status;
}

QStatus TransportManager::StopListen(const std::string& spec)
{
    QStatus status = ER_BUS_TRANSPORT_NOT_AVAILABLE;
    TransportBase* transport = GetTransport(spec);
    if (transport) {
        status = transport->StopListen(spec);
    }

    return status;
}

QStatus TransportManager::Connect(const std::string& spec, TransportBase::ConnectedCB cb)
{
    QStatus status = ER_BUS_TRANSPORT_NOT_AVAILABLE;
    TransportBase* transport = GetTransport(spec);
    if (transport) {
        return transport->Connect(spec, cb);
    }

    return status;
}
