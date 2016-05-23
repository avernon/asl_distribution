/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

#include <algorithm>
#include <sstream>

#ifdef _WIN32
/* Disable deprecation warnings */
#pragma warning(disable: 4996)
#endif

#include <qcc/Debug.h>
#include <alljoyn/controlpanel/ControlPanelService.h>
#include "ControlPanelConstants.h"
#include <alljoyn/controlpanel/LogModule.h>

namespace ajn {
namespace services {

using namespace qcc;
using namespace cpsConsts;

ControlPanelService* ControlPanelService::s_Instance(0);
uint16_t const ControlPanelService::CONTROLPANEL_SERVICE_VERSION = 1;

ControlPanelService* ControlPanelService::getInstance()
{
    if (!s_Instance) {
        s_Instance = new ControlPanelService();
    }

    return s_Instance;
}

ControlPanelService::ControlPanelService() :
    m_Bus(0), m_BusListener(0), m_ControlPanelControllee(0),
    m_ControlPanelController(0), m_ControlPanelListener(0)
{
}

ControlPanelService::~ControlPanelService()
{
    QCC_DbgPrintf(("Shutting down"));

    if (m_BusListener) {
        if (m_Bus) {
            m_Bus->UnregisterBusListener(*m_BusListener);
        }
        delete m_BusListener;
        m_BusListener = 0;
    }

    if (this == s_Instance) {
        s_Instance = 0;
    }
}

uint16_t ControlPanelService::getVersion()
{
    return CONTROLPANEL_SERVICE_VERSION;
}

QStatus ControlPanelService::initControllee(BusAttachment* bus, ControlPanelControllee* controlPanelControllee)
{
    QCC_DbgPrintf(("Initializing Controllee"));

    if (!bus) {
        QCC_DbgHLPrintf(("Bus cannot be NULL"));
        return ER_BAD_ARG_1;
    }

    if (!bus->IsStarted()) {
        QCC_DbgHLPrintf(("Bus is not started"));
        return ER_BAD_ARG_1;
    }

    if (!bus->IsConnected()) {
        QCC_DbgHLPrintf(("Bus is not connected"));
        return ER_BAD_ARG_1;
    }

    if (m_Bus && m_Bus->GetUniqueName().compare(bus->GetUniqueName()) != 0) {
        QCC_DbgHLPrintf(("Bus is already set to different BusAttachment"));
        return ER_BAD_ARG_1;
    }

    if (!controlPanelControllee) {
        QCC_DbgHLPrintf(("ControlPanelControllee cannot be null"));
        return ER_BAD_ARG_2;
    }

    if (m_ControlPanelControllee) {
        QCC_DbgHLPrintf(("ControlPanelControllee already initialized"));
        return ER_BUS_OBJ_ALREADY_EXISTS;
    }

    if (m_BusListener) {
        QCC_DbgHLPrintf(("BusListener already initialized"));
        return ER_BUS_OBJ_ALREADY_EXISTS;
    }

    m_Bus = bus;
    m_ControlPanelControllee = controlPanelControllee;

    QStatus status = controlPanelControllee->registerObjects(bus);
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not register the BusObjects"));
        return status;
    }

    m_BusListener = new ControlPanelBusListener();
    m_BusListener->setSessionPort(CONTROLPANELSERVICE_PORT);
    m_Bus->RegisterBusListener(*m_BusListener);

    SessionPort servicePort = CONTROLPANELSERVICE_PORT;
    SessionOpts sessionOpts(SessionOpts::TRAFFIC_MESSAGES, true, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);

    status = m_Bus->BindSessionPort(servicePort, sessionOpts, *m_BusListener);
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not bind Session Port successfully"));
        return status;
    }
    QCC_DbgPrintf(("Initialized Controllee successfully"));
    return status;
}

QStatus ControlPanelService::shutdownControllee()
{
    if (!m_ControlPanelControllee) {
        QCC_DbgHLPrintf(("ControlPanelControllee not initialized. Returning"));
        return ER_OK;
    }

    if (!m_Bus) {
        QCC_DbgHLPrintf(("Bus not set."));
        return ER_BUS_BUS_NOT_STARTED;
    }

    if (m_BusListener) {
        m_Bus->UnregisterBusListener(*m_BusListener);
        delete m_BusListener;
        m_BusListener = 0;
    }

    TransportMask transportMask = TRANSPORT_ANY;
    SessionPort sp = CONTROLPANELSERVICE_PORT;
    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, transportMask);

    QStatus returnStatus = ER_OK;
    QStatus status = m_Bus->UnbindSessionPort(sp);
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not unbind the SessionPort"));
        returnStatus = status;
    }

    status = m_ControlPanelControllee->unregisterObjects(m_Bus);
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not unregister the BusObjects"));
        returnStatus = status;
    }

    m_ControlPanelControllee = 0;
    return returnStatus;
}

QStatus ControlPanelService::initController(BusAttachment* bus, ControlPanelController* controlPanelController,
                                            ControlPanelListener* controlPanelListener)
{
    QCC_DbgTrace(("Initializing Controller"));

    if (!bus) {
        QCC_DbgHLPrintf(("Bus cannot be NULL"));
        return ER_BAD_ARG_1;
    }

    if (!bus->IsStarted()) {
        QCC_DbgHLPrintf(("Bus is not started"));
        return ER_BAD_ARG_1;
    }

    if (!bus->IsConnected()) {
        QCC_DbgHLPrintf(("Bus is not connected"));
        return ER_BAD_ARG_1;
    }

    if (m_Bus && m_Bus->GetUniqueName().compare(bus->GetUniqueName()) != 0) {
        QCC_DbgHLPrintf(("Bus is already set to different BusAttachment"));
        return ER_BAD_ARG_1;
    }

    if (!controlPanelController) {
        QCC_DbgHLPrintf(("ControlPanelController cannot be null"));
        return ER_BAD_ARG_2;
    }

    if (m_ControlPanelController) {
        QCC_DbgHLPrintf(("ControlPanelController already initialized"));
        return ER_BUS_OBJ_ALREADY_EXISTS;
    }

    if (!controlPanelListener) {
        QCC_DbgHLPrintf(("ControlPanelListener cannot be null"));
        return ER_BAD_ARG_3;
    }

    if (m_ControlPanelListener) {
        QCC_DbgHLPrintf(("m_ControlPanelListener already initialized"));
        return ER_BUS_OBJ_ALREADY_EXISTS;
    }

    m_Bus = bus;
    m_ControlPanelController = controlPanelController;
    m_ControlPanelListener = controlPanelListener;

    QCC_DbgPrintf(("Initialized Controller successfully"));
    return ER_OK;
}

QStatus ControlPanelService::shutdownController()
{
    if (!m_ControlPanelController) {
        QCC_DbgHLPrintf(("ControlPanelControllee not initialized. Returning"));
        return ER_OK;
    }

    if (!m_Bus) {
        QCC_DbgHLPrintf(("Bus not set."));
        return ER_BUS_BUS_NOT_STARTED;
    }

    QStatus status = m_ControlPanelController->deleteAllControllableDevices();
    if (status != ER_OK) {
        QCC_DbgHLPrintf(("Could not stop all Controllable Devices"));
    }

    m_ControlPanelController = 0;
    m_ControlPanelListener = 0;

    return status;
}

QStatus ControlPanelService::shutdown()
{
    QStatus returnStatus = ER_OK;

    QStatus status = shutdownController();
    if (status != ER_OK) {
        returnStatus = status;
        QCC_DbgHLPrintf(("Could not shutdown Controller successfully"));
    }

    status = shutdownControllee();
    if (status != ER_OK) {
        returnStatus = status;
        QCC_DbgHLPrintf(("Could not shutdown Controllee successfully"));
    }

    m_Bus = 0;
    return returnStatus;
}

BusAttachment* ControlPanelService::getBusAttachment()
{
    return m_Bus;
}

ControlPanelBusListener* ControlPanelService::getBusListener() const
{
    return m_BusListener;
}

ControlPanelListener* ControlPanelService::getControlPanelListener() const
{
    return m_ControlPanelListener;
}

std::vector<qcc::String> ControlPanelService::SplitObjectPath(qcc::String const& objectPath)
{
    std::vector<qcc::String> results;

    size_t prev = 0;
    size_t next = 0;

    while ((next = objectPath.find_first_of("/", prev)) != qcc::String::npos) {
        if (next - prev != 0) {
            results.push_back(objectPath.substr(prev, next - prev));
        }
        prev = next + 1;
    }

    if (prev < objectPath.size()) {
        results.push_back(objectPath.substr(prev));
    }

    return results;
}

} /* namespace services */
} /* namespace ajn */
