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

#ifndef GATEWAYMANAGEMENT_H_
#define GATEWAYMANAGEMENT_H_

#include <alljoyn/BusAttachment.h>
#include <alljoyn/gateway/GatewayBusListener.h>
#include <map>

#define GW_WELLKNOWN_NAME "org.alljoyn.GWAgent.GMApp"

namespace ajn {
namespace gw {

class GatewayRouterPolicyManager;
class GatewayConnectorAppManager;
class GatewayMetadataManager;

/**
 * GatewayMgmt class. Used to initialize and shutdown the GatewayMgmt instance
 */
class GatewayMgmt {

  public:

    /**
     * Get Instance of GatewayMgmt - singleton implementation
     * @return instance
     */
    static GatewayMgmt* getInstance();

    /**
     * Callback when child dies
     * @param signum
     */
    static void sigChildCallback(int32_t signum);

    /**
     * Destructor for GatewayMgmt
     */
    ~GatewayMgmt();

    /**
     * Initialize the GatewayMgmt instance
     * @param bus - bus used for GatewayMgmt
     * @return status
     */
    QStatus initGatewayMgmt(BusAttachment* bus);

    /**
     * Shutdown the GatewayMgmt instance. Allows a new call to initGatewayMgmt to be made
     * @return status
     */
    QStatus shutdownGatewayMgmt();

    /**
     * Get the Version of the GatewayMgmt instance
     * @return the GatewayMgmt version
     */
    static uint16_t getVersion();

    /**
     * Get the BusAttachment of the GatewayMgmt
     * @return the BusAttachment
     */
    BusAttachment* getBusAttachment() const;

    /**
     * Get the RouterPolicyManager of the GatewayMgmt
     * @return the routerPolicyManager
     */
    GatewayRouterPolicyManager* getRouterPolicyManager() const;

    /**
     * Get the ConnectorAppManager of the GatewayMgmt
     * @return the ConnectorAppManager
     */
    GatewayConnectorAppManager* getConnectorAppManager() const;

    /**
     * Get the MetadataManager of the GatewayMgmt
     * @return metadataManager
     */
    GatewayMetadataManager* getMetadataManager() const;

    /**
     * Get the BusListener of the GatewayMgmt
     * @return bus Listener
     */
    GatewayBusListener* getBusListener() const;

    /**
     * Set the name of the gateway default policy file
     * @param gatewayPoliciesFile
     */
    void setGatewayPolicyFile(const char* gatewayPolicyFile);

    /**
     * Set the directory where application policy files will be written
     * @param appPoliciesDirectory
     */
    void setAppPolicyDir(const char* appPolicyDirectory);

  private:

    /**
     * Default constructor for GatewayMgmt
     * Private to allow for singleton implementation
     */
    GatewayMgmt();

    /**
     * Instance variable - GatewayMgmt is a singleton
     */
    static GatewayMgmt* s_Instance;

    /**
     * BusAttachement used in GatewayMgmt instance
     */
    BusAttachment* m_Bus;

    /**
     * The Buslistener of the GatewayMgmt instance
     */
    GatewayBusListener* m_BusListener;

    /**
     * The RouterPolicyManager of the GatewayMgmt instance
     */
    GatewayRouterPolicyManager* m_RouterPolicyManager;

    /**
     * The GatewayConnectorAppManager of the GatewayMgmt instance
     */
    GatewayConnectorAppManager* m_ConnectorAppManager;

    /**
     * The MetadataManager of the GatewayMgmt instance
     */
    GatewayMetadataManager* m_MetadataManager;

    /**
     * Filename for the gateway agent default policies file
     */
    qcc::String m_gatewayPolicyFile;

    /**
     * Directory containing the policies for the applications
     */
    qcc::String m_appPolicyDirectory;

};

} //namespace gw
} //namespace ajn

#endif /* GATEWAYMANAGEMENT_H_ */
