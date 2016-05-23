/*
 * Endpoint.cc
 *
 *  Created on: Jun 2, 2015
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
#include "Endpoint.h"

#include "TransportBase.h"

namespace nio {

const Endpoint::Handle Endpoint::INVALID_HANDLE = 0;

Endpoint::Endpoint(TransportBase& transport, Handle handle, const std::string& spec) :
    transport(transport), handle(handle), spec(spec)
{
}

Endpoint::~Endpoint()
{
}

QStatus Endpoint::Send(MessageType msg, SendCompleteCB cb)
{
    return transport.Send(handle, msg, cb);
}

QStatus Endpoint::Recv(MessageType msg, ReadMessageCB cb)
{
    return transport.Recv(handle, msg, cb);
}
/*
   QStatus Endpoint::UnregisterMessageRecvCB()
   {
    return transport.UnregisterMessageRecvCB(handle);
   }*/

void Endpoint::Disconnect(bool force)
{
    transport.Disconnect(handle, force);
}

std::string Endpoint::ToString() const
{
    return spec;
}

} /* namespace nio */
