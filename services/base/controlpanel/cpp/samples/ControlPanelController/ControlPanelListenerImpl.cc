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

#ifdef _WIN32
/* Disable deprecation warnings */
#pragma warning(disable: 4996)
#endif

#include "ControlPanelListenerImpl.h"
#include "ControllerUtil.h"
#include <alljoyn/controlpanel/ControlPanel.h>
#include <iostream>
#include <algorithm>

using namespace ajn;
using namespace services;

ControlPanelListenerImpl::ControlPanelListenerImpl(ControlPanelController* controller) : m_Controller(controller)
{
}

ControlPanelListenerImpl::~ControlPanelListenerImpl()
{
}

void ControlPanelListenerImpl::sessionEstablished(ControlPanelDevice* device)
{
    if (find(m_ConnectedDevices.begin(), m_ConnectedDevices.end(), device->getDeviceBusName()) != m_ConnectedDevices.end()) {
        std::cout << "Received session established for device which was already parsed - ignoring: " << device->getDeviceBusName().c_str() << std::endl;
        return;
    }

    std::map<qcc::String, ControlPanelControllerUnit*> units = device->getDeviceUnits();
    std::map<qcc::String, ControlPanelControllerUnit*>::iterator iter;
    std::map<qcc::String, ControlPanel*>::iterator it;

    std::cout << "Session has been established with device: " << device->getDeviceBusName().c_str() << std::endl;
    m_ConnectedDevices.push_back(device->getDeviceBusName());
    for (iter = units.begin(); iter != units.end(); iter++) {
        std::cout << "Now parsing unit: " << iter->first.c_str() << std::endl;
        HttpControl* httpControl = iter->second->getHttpControl();
        if (httpControl) {
            std::cout << "Unit has a HttpControl: " << std::endl;
            std::cout << "  HttpControl version: " << httpControl->getInterfaceVersion() << std::endl;
            std::cout << "  HttpControl url: " << httpControl->getUrl().c_str() << std::endl;
        }
        std::map<qcc::String, ControlPanel*> controlPanels = iter->second->getControlPanels();
        for (it = controlPanels.begin(); it != controlPanels.end(); it++) {
            std::cout << "Now parsing panelName: " << it->first.c_str() << std::endl;
            std::vector<qcc::String> languages = it->second->getLanguageSet().getLanguages();
            for (size_t i = 0; i < languages.size(); i++) {
                std::cout << "Now parsing language: " << languages[i].c_str() << std::endl;
                Container* rootContainer = it->second->getRootWidget(languages[i]);
                std::cout << "Finished loading widget: " << rootContainer->getWidgetName().c_str() << std::endl;
                ControllerUtil::printRootWidget(rootContainer);
            }
        }
    }
}

void ControlPanelListenerImpl::sessionLost(ControlPanelDevice* device)
{
    std::cout << "Received sessionLost for device " << device->getDeviceBusName().c_str() << std::endl;
    std::cout << "Sleeping 5 seconds before cleaning up device" << std::endl;
#ifdef _WIN32
    Sleep(5000);
#else
    sleep(5);
#endif

    std::vector<qcc::String>::iterator iter;
    iter = find(m_ConnectedDevices.begin(), m_ConnectedDevices.end(), device->getDeviceBusName());
    if (iter != m_ConnectedDevices.end()) {
        m_ConnectedDevices.erase(iter);
    }

    if (m_Controller) {
        QStatus status = m_Controller->deleteControllableDevice(device->getDeviceBusName());
        std::cout << "    Deleting Controllable Device " << (status == ER_OK ? "succeeded" : "failed") << std::endl;
    }
}

void ControlPanelListenerImpl::errorOccured(ControlPanelDevice* device, QStatus status, ControlPanelTransaction transaction,
                                            qcc::String const& error)
{
    QCC_UNUSED(status);
    QCC_UNUSED(transaction);
    std::cout << "Received an error from service for device " << device->getDeviceBusName().c_str() << std::endl;
    std::cout << "    Error Message: " << error.c_str() << std::endl;
}

void ControlPanelListenerImpl::signalPropertiesChanged(ControlPanelDevice* device, Widget* widget)
{
    QCC_UNUSED(device);
    std::cout << "Received PropertiesChanged Signal for Widget " << widget->getWidgetName().c_str() << std::endl;
}

void ControlPanelListenerImpl::signalPropertyValueChanged(ControlPanelDevice* device, Property* property)
{
    QCC_UNUSED(device);
    std::cout << "Received ValueChanged Signal for Widget " << property->getWidgetName().c_str() << std::endl;
    ControllerUtil::printPropertyValue(property->getPropertyValue(), property->getPropertyType());
}

void ControlPanelListenerImpl::signalDismiss(ControlPanelDevice* device, NotificationAction* notificationAction)
{
    QCC_UNUSED(device);
    QCC_UNUSED(notificationAction);
    std::cout << "Received Dismiss Signal for NotificationAction" << std::endl;
}
