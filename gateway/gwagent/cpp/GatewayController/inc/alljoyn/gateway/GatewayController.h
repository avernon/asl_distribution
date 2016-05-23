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

#ifndef GatewayController_H
#define GatewayController_H

#include <vector>
#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/gateway/GatewayMgmtApp.h>
#include <alljoyn/about/AnnounceHandler.h>



namespace ajn {
namespace gwc {
/**
 * This class includes the main functionality for the Gateway Controller Application
 */
class GatewayController {
  public:

    /**
     * GetInstance
     * @return The {@link GatewayController} object
     */
    static GatewayController*getInstance();

    /**
     * Initialize the gateway controller. You must call this function before using GatewayController
     * @param bus {@link BusAttachment} to use
     */
    void init(BusAttachment*bus);

    /**
     * Shutdown the gateway controller
     */
    void shutdown();

    /**
     * @return {@link BusAttachment} that is used by the {@link GatewayController}
     */
    BusAttachment* getBusAttachment();


    /**
     * create a Gateway by parsing announce descriptions.
     * @param gatewayBusName - BusName of device received in announce
     * @param objectDescs - ObjectDescriptions received in announce
     * @param gatewayMgmtApp a GatewayMgmtApp
     * @return {@link QStatus}
     */
    QStatus createGateway(const qcc::String& gatewayBusName, const ajn::services::AnnounceHandler::ObjectDescriptions& objectDescs, const ajn::services::AnnounceHandler::AboutData& aboutData, GatewayMgmtApp** gatewayMgmtApp);

    /**
     * getGateway - get a Gateway using the busName
     * @param deviceBusName - gatewayBusName to get
     * @return GatewayMgmtApp* - returns the Gateway or NULL if not found
     */
    GatewayMgmtApp* getGateway(const qcc::String& gatewayBusName);

    /**
     * Get map of All Gateways
     * @return controllable Devices map
     */
    const std::map<qcc::String, GatewayMgmtApp*>& getGateways() const;

    /**
     * release allocations and empty object. must be called before deletion of object.
     * @return {@link QStatus}
     */
    QStatus release();

  private:

    /**
     * Constructor
     * @param bus
     * @param store
     */
    GatewayController();
    /**
     * Desctructor
     */
    virtual ~GatewayController() { }
    /**
     *  pointer to AboutServiceApi
     */
    static GatewayController* m_instance;

    /**
     * The BusAttachment to be used
     */
    static BusAttachment* m_Bus;


    std::map<qcc::String, GatewayMgmtApp*> m_Gateways;

    void emptyMap();
};
}
}
#endif /* defined(GatewayController_H) */
