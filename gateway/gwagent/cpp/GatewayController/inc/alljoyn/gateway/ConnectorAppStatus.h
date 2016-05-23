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

#ifndef ConnectorAppStatus_H
#define ConnectorAppStatus_H

#include <qcc/String.h>
#include <alljoyn/MsgArg.h>
#include <alljoyn/gateway/Enums.h>

namespace ajn {
namespace gwc {

class ConnectorAppStatus {
  public:


    /**
     * Constructor - init must be called
     */
    ConnectorAppStatus() {}

    /**
     * init
     * @param returnArgs MsgArg containing the application info
     * @return {@link QStatus}
     */

    QStatus init(const ajn::MsgArg* returnArgs);

    /**
     * init
     * @param installStatus status of the installed Connector App
     * @param installDescription string describing the install of the Connector App
     * @param connectionStatus status of connection to Connector App
     * @param operationalStatus operational status of the Connector App
     * @return {@link QStatus}
     */
    QStatus init(InstallStatus installStatus, const qcc::String &installDescription, ConnectionStatus connectionStatus, OperationalStatus operationalStatus);

    /**
     * Destructor
     */
    virtual ~ConnectorAppStatus();

    /**
     * @return The installation status of the Connector App
     */
    InstallStatus getInstallStatus();

    /**
     * @return The installation description of the Connector App
     */
    const qcc::String &getInstallDescriptions();

    /**
     * @return Connection status of the Connector App to its cloud service
     */
    ConnectionStatus getConnectionStatus();

    /**
     * @return The state whether the Connector App is running
     */
    OperationalStatus getOperationalStatus();

  private:
    /**
     * Installation status
     */
    InstallStatus m_InstallStatus;

    /**
     * Installation description
     */
    qcc::String m_InstallDescription;

    /**
     * Connection status of the Connector App to its cloud service
     */
    ConnectionStatus m_ConnectionStatus;

    /**
     * The state whether the Connector App is working
     */
    OperationalStatus m_OperationalStatus;

};
}
}
#endif /* defined(ConnectorAppStatus_H) */
