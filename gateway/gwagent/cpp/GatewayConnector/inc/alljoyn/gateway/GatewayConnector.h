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

#ifndef GATEWAY_CONNECTOR_H_
#define GATEWAY_CONNECTOR_H_

#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <qcc/String.h>
#include "alljoyn/gateway/GatewayEnums.h"

#include <list>

#include "GatewayMergedAcl.h"

namespace ajn {
namespace gw {

/**
 * GatewayConnector class - abstract class that needs to be implemented to receive signal callbacks
 */
class GatewayConnector : public MessageReceiver {

  public:

    /**
     * Constructor of GatewayConnector class
     * @param bus - bus used to initialize GatewayConnector
     * @param appName - name of Connector Application
     */
    GatewayConnector(BusAttachment* bus, qcc::String const& connectorAppName);

    /**
     * Destructor of GatewayConnector class
     */
    virtual ~GatewayConnector();

    /**
     * initialize the Connector class
     * @return status - success/failure
     */
    QStatus init();

    /**
     * update the ConnectionStatus of the ConnectorApp
     * @param connStatus - connStatus to update to
     * @return status - success/failure
     */
    QStatus updateConnectionStatus(ConnectionStatus connStatus);

    /**
     * Get the merged Acl from the GatewayMgmtApp
     * @param response - MergedAcl response
     * @return status - success/failure
     */
    QStatus getMergedAcl(GatewayMergedAcl* response);

    /**
     * Async method to get the merged Acl from the GatewayMgmtApp
     * @param response - MergedAcl response
     * @return status - success/failure
     */
    QStatus getMergedAclAsync(GatewayMergedAcl* response);

  protected:

    /**
     * Receive the response of the AsyncGetMergedAcl call
     * @param unmarshalStatus - status of unmarshalling ( success/failure)
     * @param response - the response of the call
     */
    virtual void receiveGetMergedAclAsync(QStatus unmarshalStatus, GatewayMergedAcl* response) { }

    /**
     * Handler for the mergedAcl signal
     */
    virtual void mergedAclUpdated() = 0;

    /**
     * Handler for the shutdown signal
     */
    virtual void shutdown() = 0;

  private:

    /**
     * Private function to initialize the interface
     * @param status - success/failure
     * @return interfaceDescription
     */
    const InterfaceDescription* initInterface(QStatus& status);

    /**
     * ReplyHandler for getMergedAcl
     * @param msg - message of reply
     * @param mergedAcl - context
     */
    void getMergedAclReplyHandler(Message& msg, void* mergedAcl);

    /**
     * SignalHandler for mergedAcl signal
     * @param member - interface member
     * @param sourcePath - objectPath of signal
     * @param msg - content of signal
     */
    void mergedAclUpdatedSignalHandler(const InterfaceDescription::Member* member, const char* sourcePath, Message& msg);

    /**
     * SignalHandler for shutdown signal
     * @param member - interface member
     * @param sourcePath - objectPath of signal
     * @param msg - content of signal
     */
    void shutdownSignalHandler(const InterfaceDescription::Member* member, const char* sourcePath, Message& msg);

    /**
     * The busAttachment to use
     */
    BusAttachment* m_Bus;

    /**
     * The objectPath of the busObject
     */
    qcc::String m_ObjectPath;

    /**
     * The wellknownName of the ConnectorApp
     */
    qcc::String m_WellKnownName;

    /**
     * The proxyBusObject used for Remote methods
     */
    ProxyBusObject* m_RemoteAppAccess;
};

} //namespace gw
} //namespace ajn

#endif
