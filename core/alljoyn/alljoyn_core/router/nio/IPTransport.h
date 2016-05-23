/*
 * IPTransport.h
 *
 *  Created on: Jun 4, 2015
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
#ifndef IPTRANSPORT_H_
#define IPTRANSPORT_H_

#include "TransportBase.h"

#include <qcc/IPAddress.h>

#include <qcc/IfConfig.h>

#include <map>
#include <list>

namespace nio {

class Proactor;

class IPTransport : public TransportBase {

/**
 * Abstract base class implemented by AllJoyn users and called by AllJoyn to
 * inform users of security permission related events.
 */
class PermissionConfigurationListener {
  public:
    IPTransport(Proactor& proactor, const std::string& name);
    virtual ~IPTransport();

  protected:

    std::string NormalizeConnectionData(const qcc::IPAddress& addr, uint16_t port);

    typedef std::list<qcc::IPEndpoint> ListenEndpoints;
    bool ParseSpec(const std::string& spec, ListenEndpoints& eps);
    bool ParseSpec(const std::string& spec, qcc::IPAddress& ip, uint16_t& port, std::string& normSpec);

    std::map<std::string, std::list<qcc::IPAddress> > ip_addresses;

    void OnNetworkEntries(const std::vector<qcc::IfConfigEntry>& entries);
    void CheckNetworks();

};

} /* namespace nio */

#endif /* IPTRANSPORT_H_ */
