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

#ifndef APPMGMTBUSOBJECT_H_
#define APPMGMTBUSOBJECT_H_

#include <alljoyn/BusAttachment.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/gateway/GatewayConnectorAppManager.h>

namespace ajn {
namespace gw {

/**
 * AppMgmtBusObject - BusObject for App Mgmt
 */
class AppMgmtBusObject : public BusObject  {
  public:

    /**
     * Constructor for GatewayAclBusObject class
     * @param bus - the bus to create the interface
     * @param connectorAppManager - the connectorAppManager that contains this busObject
     * @param status - success/failure
     */
    AppMgmtBusObject(BusAttachment* bus, GatewayConnectorAppManager* connectorAppManager, QStatus* status);

    /**
     * Destructor for the BusObject
     */
    virtual ~AppMgmtBusObject();

    /**
     * Function callback for getInstalledApps
     * @param member - the member called
     * @param msg - the message of the method
     */
    void GetInstalledApps(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Get Property
     * @param interfaceName - name of the interface
     * @param propName - name of the property
     * @param val - msgArg to fill
     * @return status - success/failure
     */
    QStatus Get(const char* interfaceName, const char* propName, MsgArg& val);

    /**
     * Set Property
     * @param interfaceName - name of the interface
     * @param propName - name of the property
     * @param val - msgArg to fill
     * @return status - success/failure
     */
    QStatus Set(const char* interfaceName, const char* propName, MsgArg& val);

  private:

    /**
     * The ConnectorAppManager that contains this BusObject
     */
    GatewayConnectorAppManager* m_ConnectorAppManager;

};

} /* namespace gw */
} /* namespace ajn */

#endif /* APPMGMTBUSOBJECT_H_ */
