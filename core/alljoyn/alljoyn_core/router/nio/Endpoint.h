/*
 * EndpointBase.h
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

#ifndef ENDPOINTBASE_H_
#define ENDPOINTBASE_H_

#include "Buffer.h"

#include <functional>
#include <string>
#include <memory>
#include <stdint.h>

#include <alljoyn/Status.h>

namespace nio {

typedef std::shared_ptr<Buffer> MessageType;

class TransportBase;

class Endpoint {

  public:

    typedef uint64_t Handle;
    const static Handle INVALID_HANDLE;

    Endpoint(TransportBase& transport, Handle handle, const std::string& spec);

    Endpoint(const Endpoint&) = delete;
    Endpoint& operator=(const Endpoint&) = delete;

    virtual ~Endpoint();

    std::string ToString() const;

    typedef std::function<void (std::shared_ptr<Endpoint>, MessageType, QStatus)> SendCompleteCB;

    /**
     * Send a message to this endpoint
     *
     * @param msg   The message to send
     * @param cb    The callback to make when the entire message has been sent
     *
     * @return      The error code.  If not ER_OK, the callback WILL NEVER HAPPEN.
     *
     * Do not call Send() again until the callback has happened.
     */
    QStatus Send(MessageType msg, SendCompleteCB cb);

    typedef std::function<void (std::shared_ptr<Endpoint>, MessageType, QStatus)> ReadMessageCB;

    /**
     * Receive a message from this endpoint
     *
     * @param msg   The message to receive
     * @param cb    The callback to make when the entire message has been received
     *
     * @return      The error code.  If not ER_OK, the callback WILL NEVER HAPPEN.
     *
     * Once the callback has been made, you must call Recv again to receive another.
     * Not calling Recv again will apply backpressure.
     */
    QStatus Recv(MessageType msg, ReadMessageCB cb);

    /*
     * Stop listening for incoming data from this endpoint.
     */
    //QStatus UnregisterMessageRecvCB();

    void Disconnect(bool force = false);

  protected:
    TransportBase& transport;
    Handle handle;
    const std::string spec;
};

} /* namespace nio */

#endif /* ENDPOINTBASE_H_ */
