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

#ifndef GatewayAclRules_H_
#define GatewayAclRules_H_

#include <alljoyn/gateway/GatewayMgmt.h>
#include <alljoyn/gateway/GatewayAppIdentifier.h>
#include <alljoyn/gateway/GatewayRuleObjectDescription.h>

namespace ajn {
namespace gw {

typedef std::vector<GatewayRuleObjectDescription> GatewayRuleObjectDescriptions;
typedef std::map<GatewayAppIdentifier, std::vector<GatewayRuleObjectDescription> > GatewayRemoteAppRules;

/**
 * Class used to define AclRules
 */
class GatewayAclRules {

  public:

    /**
     * Constructor of the GatewayAclRules class
     */
    GatewayAclRules();

    /**
     * Destructor of the GatewayAclRules class
     */
    virtual ~GatewayAclRules();

    /**
     * Get the ExposedServicesRules of the AclRules
     * @return exposedServicesRules
     */
    const GatewayRuleObjectDescriptions& getExposedServicesRules() const;

    /**
     * Set the ExposedServicesRules of the AclRules
     * @param exposedServicesRules
     */
    void setExposedServicesRules(const GatewayRuleObjectDescriptions& exposedServicesRules);

    /**
     * Get the RemoteAppPermissions of the AclRules
     * @return remoteAppPermissions
     */
    const GatewayRemoteAppRules& getRemoteAppRules() const;

    /**
     * Set the RemoteAppRules of the AclRules
     * @param remoteAppRules
     */
    void setRemoteAppRules(const GatewayRemoteAppRules& remoteAppRules);

  private:

    /**
     * Exposed Services Rules
     */
    GatewayRuleObjectDescriptions m_ExposedServicesRules;

    /**
     * RemoteAppRules
     */
    GatewayRemoteAppRules m_RemoteAppRules;

};

} /* namespace gw */
} /* namespace ajn */

#endif /* GatewayAclRules_H_ */
