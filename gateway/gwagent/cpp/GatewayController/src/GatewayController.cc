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

#include <alljoyn/gateway/GatewayController.h>
#include "Constants.h"
#include <qcc/Debug.h>

namespace ajn {
namespace gwc {

using namespace gwcConsts;

GatewayController* GatewayController::m_instance = NULL;
BusAttachment* GatewayController::m_Bus = NULL;

GatewayController::GatewayController()
{

}

GatewayController*GatewayController::getInstance()
{
    if (!m_instance) {
        m_instance = new GatewayController();
    }
    return m_instance;
}

void GatewayController::init(BusAttachment*bus)
{
    m_Bus = bus;
}

void GatewayController::shutdown()
{
    release();

    if (m_instance) {
        delete m_instance;
        m_instance = NULL;
    }
}


BusAttachment* GatewayController::getBusAttachment()
{
    return m_Bus;
}


QStatus GatewayController::createGateway(const qcc::String& gatewayBusName, const ajn::services::AnnounceHandler::ObjectDescriptions& objectDescs, const ajn::services::AnnounceHandler::AboutData& aboutData, GatewayMgmtApp** gatewayMgmtApp)
{

    for (ajn::services::AboutClient::ObjectDescriptions::const_iterator it = objectDescs.begin(); it != objectDescs.end(); ++it) {
        qcc::String key = it->first;
        std::vector<qcc::String> vector = it->second;
        for (std::vector<qcc::String>::const_iterator itv = vector.begin(); itv != vector.end(); ++itv) {
            if (itv->compare(AJ_GATEWAYCONTROLLER_APPMGMT_INTERFACE) == 0) {
                if (key.compare(AJ_OBJECTPATH_PREFIX) == 0) {
                    *gatewayMgmtApp = new GatewayMgmtApp();
                    QStatus status = (*gatewayMgmtApp)->init(gatewayBusName, aboutData);

                    if (status != ER_OK) {
                        QCC_LogError(status, ("GatewayMgmtApp init failed"));
                        delete gatewayMgmtApp;
                        return status;
                    }
                    break;
                }
            }
        }
    }

    if (gatewayMgmtApp) {
        m_Gateways[gatewayBusName] = *gatewayMgmtApp;
    } else {
        return ER_FAIL;
    }

    return ER_OK;
}

GatewayMgmtApp* GatewayController::getGateway(const qcc::String& gatewayBusName)
{
    std::map<qcc::String, GatewayMgmtApp*>::const_iterator gateway = m_Gateways.find(gatewayBusName);

    if (gateway != m_Gateways.end()) {
        return gateway->second;
    }
    return NULL;
}

const std::map<qcc::String, GatewayMgmtApp*>& GatewayController::getGateways() const
{
    return m_Gateways;
}

void GatewayController::emptyMap()
{
    while (!m_Gateways.empty()) {
        std::map<qcc::String, GatewayMgmtApp*>::iterator itr = m_Gateways.begin();
        GatewayMgmtApp*gateway = (*itr).second;
        m_Gateways.erase(itr);
        gateway->release();
        delete gateway;
    }
}


QStatus GatewayController::release()
{
    emptyMap();

    // static member variables are being taken care of in ShutDown

    return ER_OK;

}
}
}