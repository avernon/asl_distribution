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

#ifndef GATEWAYAPPMANAGER_H_
#define GATEWAYAPPMANAGER_H_

#include <alljoyn/BusAttachment.h>
#include <alljoyn/gateway/GatewayMgmt.h>
#include <map>

namespace ajn {
namespace gw {

//forward declarations
class AppMgmtBusObject;
class GatewayConnectorApp;

/**
 * Class used to manage Applications
 */
class GatewayConnectorAppManager {
  public:

    /**
     * Constructor for GatewayConnectorAppManager
     */
    GatewayConnectorAppManager();

    /**
     * Destructor for GatewayConnectorAppManager
     */
    virtual ~GatewayConnectorAppManager();

    /**
     * Initialize the GatewayConnectorAppManager
     * @param bus - bus used to register
     * @return status - success/failure
     */
    QStatus init(BusAttachment* bus);

    /**
     * Shutdown the GatewayConnectorAppManager
     * @param bus - bus used to unregister
     * @return status - success/failure
     */
    QStatus shutdown(BusAttachment* bus);

    /**
     * receive Sig Child Signal
     * @param pid - pid of process that died
     */
    void sigChildReceived(pid_t pid);

    /**
     * Get the Apps stored by the App Manager
     * @return apps
     */
    std::map<qcc::String, GatewayConnectorApp*> getConnectorApps() const;

  private:

    /**
     * Load the installed Apps by parsing the apps directory
     * @return
     */
    QStatus loadConnectorApps();

    /**
     * BusObject used for AppMgmt
     */
    AppMgmtBusObject* m_AppMgmtBusObject;

    /**
     * The map storing the Apps
     */
    std::map<qcc::String, GatewayConnectorApp*> m_ConnectorApps;
};

} /* namespace gw */
} /* namespace ajn */

#endif /* GATEWAYAPPMANAGER_H_ */
