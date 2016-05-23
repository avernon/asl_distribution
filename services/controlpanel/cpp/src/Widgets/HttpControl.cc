/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

#include <alljoyn/controlpanel/HttpControl.h>
#include <alljoyn/controlpanel/ControlPanelService.h>
#include <alljoyn/about/AboutServiceApi.h>
#include "../ControlPanelConstants.h"
#include "../BusObjects/HttpControlBusObject.h"
#include <alljoyn/controlpanel/LogModule.h>

namespace ajn {
namespace services {
using namespace cpsConsts;

HttpControl::HttpControl(qcc::String const& url) : m_Url(url), m_ObjectPath(""),
    m_HttpControlBusObject(0), m_Device(0), m_ControlPanelMode(CONTROLLEE_MODE), m_Version(0)
{
}

HttpControl::HttpControl(qcc::String const& objectPath, ControlPanelDevice* device) : m_Url(""), m_ObjectPath(objectPath),
    m_HttpControlBusObject(0), m_Device(device), m_ControlPanelMode(CONTROLLER_MODE), m_Version(0)
{
}

HttpControl::HttpControl(const HttpControl& httpControl)
{

}

HttpControl& HttpControl::operator=(const HttpControl& httpControl)
{
    return *this;
}

HttpControl::~HttpControl()
{
}

const uint16_t HttpControl::getInterfaceVersion() const
{
    if (!m_HttpControlBusObject) {
        return 1;
    }

    return m_ControlPanelMode == CONTROLLEE_MODE ? m_HttpControlBusObject->getInterfaceVersion() : m_Version;
}

QStatus HttpControl::registerObjects(BusAttachment* bus, qcc::String const& unitName)
{
    if (m_HttpControlBusObject) {
        QCC_DbgHLPrintf(("Could not register Object. BusObject already exists"));
        return ER_BUS_OBJ_ALREADY_EXISTS;
    }

    if (!bus) {
        QCC_DbgHLPrintf(("Could not register Object. Bus is NULL"));
        return ER_BAD_ARG_1;
    }

    if (!(bus->IsStarted() && bus->IsConnected())) {
        QCC_DbgHLPrintf(("Could not register Object. Bus is not started or not connected"));
        return ER_BAD_ARG_1;
    }

    AboutServiceApi* aboutService = AboutServiceApi::getInstance();
    if (!aboutService) {
        QCC_DbgHLPrintf(("Could not retrieve AboutService. It has not been initialized"));
        return ER_FAIL;
    }

    QStatus status = ER_OK;
    qcc::String objectPath = AJ_OBJECTPATH_PREFIX + unitName + AJ_HTTP_OBJECTPATH_SUFFIX;
    m_HttpControlBusObject = new HttpControlBusObject(bus, objectPath.c_str(), status, this);
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not create HttpControlBusObject"));
        return status;
    }
    status = bus->RegisterBusObject(*m_HttpControlBusObject);
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not register HttpControlBusObject."));
        return status;
    }

    std::vector<qcc::String> interfaces;
    interfaces.push_back(AJ_HTTPCONTROL_INTERFACE);
    aboutService->AddObjectDescription(objectPath, interfaces);

    return status;
}

QStatus HttpControl::registerObjects(BusAttachment* bus)
{
    if (m_HttpControlBusObject) {
        QCC_DbgPrintf(("BusObject already exists - refreshing widget"));
        return refreshObjects(bus);
    }

    if (!bus) {
        QCC_DbgHLPrintf(("Could not register Object. Bus is NULL"));
        return ER_BAD_ARG_1;
    }

    if (!(bus->IsStarted() && bus->IsConnected())) {
        QCC_DbgHLPrintf(("Could not register Object. Bus is not started or not connected"));
        return ER_BAD_ARG_1;
    }

    QStatus status;
    m_HttpControlBusObject = new HttpControlBusObject(bus, m_ObjectPath.c_str(), status, this);
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not create HttpControlBusObject"));
        return status;
    }

    status = m_HttpControlBusObject->setRemoteController(bus, m_Device->getDeviceBusName(), m_Device->getSessionId());
    if (status != ER_OK) {
        QCC_LogError(status, ("Call to SetRemoteController failed"));
        return status;
    }

    status = m_HttpControlBusObject->checkVersions();
    if (status != ER_OK) {
        QCC_LogError(status, ("Call to CheckVersions failed"));
        return status;
    }

    status = m_HttpControlBusObject->GetUrl(bus);
    if (status != ER_OK) {
        QCC_LogError(status, ("Call to GetUrl failed"));
        return status;
    }

    return status;
}

QStatus HttpControl::refreshObjects(BusAttachment* bus)
{
    if (!m_HttpControlBusObject) {
        QCC_DbgHLPrintf(("BusObject does not exist - exiting"));
        return ER_BUS_OBJECT_NOT_REGISTERED;
    }

    if (!bus) {
        QCC_DbgHLPrintf(("Could not register Object. Bus is NULL"));
        return ER_BAD_ARG_1;
    }

    if (!(bus->IsStarted() && bus->IsConnected())) {
        QCC_DbgHLPrintf(("Could not register Object. Bus is not started or not connected"));
        return ER_BAD_ARG_1;
    }

    QStatus status;
    status = m_HttpControlBusObject->setRemoteController(bus, m_Device->getDeviceBusName(), m_Device->getSessionId());
    if (status != ER_OK) {
        QCC_LogError(status, ("Call to SetRemoteController failed"));
        return status;
    }

    status = m_HttpControlBusObject->checkVersions();
    if (status != ER_OK) {
        QCC_LogError(status, ("Call to CheckVersions failed"));
        return status;
    }

    status = m_HttpControlBusObject->GetUrl(bus);
    if (status != ER_OK) {
        QCC_LogError(status, ("Call to GetUrl failed"));
        return status;
    }

    return status;

}

QStatus HttpControl::unregisterObjects(BusAttachment* bus)
{
    if (!m_HttpControlBusObject) {
        QCC_DbgHLPrintf(("Can not unregister. HttpControlBusObject does not exist"));
        return ER_OK; //this does not need to fail
    }

    if (!bus) {
        QCC_DbgHLPrintf(("Could not unregister Object. Bus is NULL"));
        return ER_BAD_ARG_1;
    }

    bus->UnregisterBusObject(*m_HttpControlBusObject);
    delete m_HttpControlBusObject;
    m_HttpControlBusObject = 0;
    return ER_OK;
}

QStatus HttpControl::fillUrlArg(MsgArg& val)
{
    return val.Set(AJPARAM_STR.c_str(), m_Url.c_str());
}

QStatus HttpControl::readUrlArg(MsgArg const& val)
{
    char* url;
    QStatus status = val.Get(AJPARAM_STR.c_str(), &url);
    if (status == ER_OK) {
        m_Url = url;
    }
    return status;
}

QStatus HttpControl::readVersionArg(MsgArg const& val)
{
    return val.Get(AJPARAM_UINT16.c_str(), &m_Version);
}

ControlPanelDevice* HttpControl::getDevice() const
{
    return m_Device;
}

const qcc::String& HttpControl::getUrl() const
{
    return m_Url;
}

ControlPanelMode HttpControl::getControlPanelMode() const
{
    return m_ControlPanelMode;
}

} /* namespace services */
} /* namespace ajn */
