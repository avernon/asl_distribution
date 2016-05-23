/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#ifndef ConnectorCapabilities_H
#define ConnectorCapabilities_H

#include <vector>
#include <alljoyn/Status.h>
#include <alljoyn/gateway/RuleObjectDescription.h>

namespace ajn {
namespace gwc {
/**
 * The manifest rules of the Connector App
 */
class ConnectorCapabilities {
  public:

    /**
     * Constructor - init must be called
     */
    ConnectorCapabilities() { }

    /**
     * init
     * @param manifRulesAJ MsgArg with manifest rules
     * @return {@link QStatus}
     */
    QStatus init(const ajn::MsgArg*manifRulesAJ);

    /**
     * Destructor
     */
    virtual ~ConnectorCapabilities();

    /**
     * The {@link RuleObjectDescription} objects that the Connector App
     * exposes to its clients
     * @return List of exposed services
     */
    const std::vector<RuleObjectDescription*>& getExposedServices() const;

    /**
     * The {@link RuleObjectDescription} objects that the Connector App
     * supports for being remoted
     * @return List of remoted interfaces
     */
    const std::vector<RuleObjectDescription*>& getRemotedServices() const;

    /**
     * release allocations and empty object. must be called before deletion of object.
     * @return {@link QStatus}
     */
    QStatus release();

  private:
    /**
     * The interfaces that the Connector App exposes to its clients
     */
    std::vector<RuleObjectDescription*> m_ExposedServices;

    /**
     * The interfaces that the Connector App allows to remote
     */
    std::vector<RuleObjectDescription*> m_RemotedServices;

    void emptyVectors();

};
}
}
#endif /* defined(ConnectorCapabilities_H) */
