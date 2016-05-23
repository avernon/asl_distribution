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

#ifndef AclRules_H
#define AclRules_H

#include <map>
#include <vector>
#include <qcc/String.h>
#include <alljoyn/gateway/RemotedApp.h>
#include <alljoyn/gateway/RuleObjectDescription.h>
#include <alljoyn/gateway/ConnectorCapabilities.h>


namespace ajn {
namespace gwc {
class AclRules {
  public:
    /**
     * Constructor - must call appropriate init
     */
    AclRules();


    /**
     * init
     * @param exposedServicesArrayArg MsgArg containing the exposed services
     * @param remotedAppsArrayArg MsgArg containing the remoted apps
     * @param connectorCapabilities map of manifest rules for this connector app
     * @param internalMetadata internal metadata information from the server
     * @return {@link QStatus}
     */
    QStatus init(const MsgArg*exposedServicesArrayArg, const MsgArg*remotedAppsArrayArg, const ConnectorCapabilities& connectorCapabilities, const std::map<qcc::String, qcc::String>& internalMetadata);


    /**
     * init
     * @param exposedServices The interfaces that Connector App exposes to its clients
     * @param remotedApps The applications that may be reached by the Connector App
     * via the configured interfaces and object paths
     */
    QStatus init(std::vector<RuleObjectDescription*> const& exposedServices, std::vector<RemotedApp*> const& remotedApps);

    /**
     * Destructor
     */
    virtual ~AclRules();

    /**
     * The applications that may be reached by the Connector App
     * via the configured interfaces and object paths
     * @return List of the remoted applications
     */
    const std::vector<RemotedApp*>& getRemotedApps();

    /**
     * The interfaces that Connector App exposes to its clients
     * @return List of exposed services
     */
    const std::vector<RuleObjectDescription*>& getExposedServices();


    /**
     * Set the given metadata to the given one
     * @param metadata
     */
    void setMetadata(std::map<qcc::String, qcc::String> const& metadata);

    /**
     * Returns metadata value for the given key
     * @param key The metadata key
     * @return Metadata value or NULL if not found
     */
    qcc::String*getMetadata(const qcc::String& key);

    /**
     * Returns current metadata object
     * @return metadata
     */
    const std::map<qcc::String, qcc::String>& getMetadata();


    /**
     * release allocations and empty object. must be called before deletion of object.
     * @return {@link QStatus}
     */
    QStatus release();

  private:
    /**
     * This {@link AclRules} metadata
     */
    std::map<qcc::String, qcc::String> m_Metadata;


    /**
     * The interfaces that the Connector App exposes to its clients
     */
    std::vector<RuleObjectDescription*> m_ExposedServices;

    /**
     * The applications that may be reached by the Connector App
     * via the configured interfaces and object paths
     */
    std::vector<RemotedApp*> m_RemotedApps;

    void emptyVectors();
};
}
}
#endif /* defined(AclRules_H) */
