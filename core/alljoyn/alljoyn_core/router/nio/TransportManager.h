/*
 * TransportManager.h
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
#ifndef TRANSPORTMANAGER_H_
#define TRANSPORTMANAGER_H_

#include "TransportBase.h"
#include "Proactor.h"

#include <map>
#include <mutex>
#include <string>


namespace nio {

/**
 * A class used to manage the various endpoints in our system.
 */
class TransportManager {
  public:
    TransportManager(Proactor& proactor);

    TransportManager(const TransportManager&) = delete;
    TransportManager& operator=(const TransportManager&) = delete;

    virtual ~TransportManager();

    /**
     * Start listening on a transport spec and get a callback when somebody tries to join.
     *
     * @param spec  A transport-specific representation of how to listen
     * @param cb    A callback that will be invoked when somebody tries to join.
     *              cb may reject the joiner by returning false.
     *
     * @return      ER_OK if successful, error otherwise
     */
    QStatus Listen(const std::string& spec, TransportBase::AcceptedCB cb);

    /**
     * Stop listening on the given spec
     *
     * @param spec  A transport-specific listen spec, previously passed to Listen
     *
     * @return      ER_OK if successful, error otherwise
     */
    QStatus StopListen(const std::string& spec);

    /**
     * Initiate a connection to a remote endpoint.
     *
     * @param spec  A transport-specific representation of the remote endpoint.
     * @param cb    A callback that will be invoked with the new endpoint on success.
     *
     * @return      ER_OK if successful, error otherwise
     */
    QStatus Connect(const std::string& spec, TransportBase::ConnectedCB cb);

  private:

    TransportBase* GetTransport(const std::string& spec);
    TransportBase* CreateTransport(const std::string& name);

    Proactor& proactor;

    std::map<std::string, TransportBase*> transports;
    std::mutex transports_lock;
};

} /* namespace nio */

#endif /* TRANSPORTMANAGER_H_ */
