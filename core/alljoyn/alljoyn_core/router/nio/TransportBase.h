/*
 * TransportBase.h
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
#ifndef TRANSPORTBASE_H_
#define TRANSPORTBASE_H_

#include "Endpoint.h"

#include <functional>
#include <memory>
#include <string>
#include <map>

#include <alljoyn/Status.h>

namespace nio {

class Proactor;
class Buffer;

class TransportBase {
  public:

    TransportBase(Proactor& proactor, const std::string& name);

    TransportBase(const TransportBase&) = delete;
    TransportBase& operator=(const TransportBase&) = delete;

    virtual ~TransportBase();

    typedef std::shared_ptr<Endpoint> EndpointPtr;


    virtual QStatus Send(Endpoint::Handle handle, MessageType msg, Endpoint::SendCompleteCB cb) = 0;

    // whoever is listening for ReadMessageCB must call NotifyMessageDoneCB when the app is finished with the message
    // must call this again after each CB, when the listener is ready to recv again

    // these should be called from EndpointBase!
    virtual QStatus Recv(Endpoint::Handle handle, MessageType msg, Endpoint::ReadMessageCB cb) = 0;
    //virtual QStatus UnregisterMessageRecvCB(EndpointHandle handle) = 0;


    typedef std::function<void (EndpointPtr, QStatus)> ConnectedCB;
    virtual QStatus Connect(const std::string& spec, ConnectedCB cb) = 0;
    virtual QStatus Disconnect(Endpoint::Handle handle, bool force = false) = 0;


    typedef std::function<bool (EndpointPtr)> AcceptedCB;
    virtual QStatus Listen(const std::string& spec, AcceptedCB cb) = 0;
    virtual QStatus StopListen(const std::string& spec) = 0;

    std::string GetName() const;

  protected:

    Proactor& proactor;
    const std::string name;
};



} /* namespace nio */

#endif /* TRANSPORTBASE_H_ */
