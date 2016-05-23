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

#include "ControllerNotificationReceiver.h"
#include "ControllerUtil.h"
#include <iostream>

using namespace ajn;
using namespace services;
using namespace qcc;

ControllerNotificationReceiver::ControllerNotificationReceiver(ControlPanelController* controlPanelController) :
    m_Controller(controlPanelController)
{

}

ControllerNotificationReceiver::~ControllerNotificationReceiver()
{

}

void ControllerNotificationReceiver::Receive(Notification const& notification)
{
    if (m_Controller && notification.getControlPanelServiceObjectPath()) {
        std::cout << "Received ControlPanelService object path: " << notification.getControlPanelServiceObjectPath() << std::endl;

        ControlPanelDevice* device = m_Controller->getControllableDevice(notification.getSenderBusName());
        if (!device) {
            std::cout << "Could not get a Controllable Device" << std::endl;
            return;
        }

        QStatus status = device->startSession();
        if (status != ER_OK) {
            std::cout << "Could not start a session with the device" << std::endl;
            return;
        }

        NotificationAction* notficationAction = device->addNotificationAction(notification.getControlPanelServiceObjectPath());
        if (!notficationAction) {
            std::cout << "Could not add the notificationAction" << std::endl;
            return;
        }

        std::cout << "Parsing the notificationAction received" << std::endl;
        std::vector<qcc::String> languages = notficationAction->getLanguageSet().getLanguages();
        for (size_t i = 0; i < languages.size(); i++) {

            std::vector<Action*> actionsToExecute;
            std::vector<Property*> propertiesToChange;
            std::vector<Dialog*> dialogsToExecute;

            std::cout << "Now parsing language: " << languages[i].c_str() << std::endl;
            RootWidget* rootWidget = notficationAction->getRootWidget(languages[i]);

            std::cout << "Finished loading widget: " << rootWidget->getWidgetName().c_str() << std::endl;
            ControllerUtil::printRootWidget(rootWidget);
        }

        std::cout << "Removing the notificationAction from the device" << std::endl;
        status = device->removeNotificationAction(notficationAction);
        std::cout << "    Removing NotificationAction " << (status == ER_OK ? "succeeded" : "failed") << std::endl;
    }
}

void ControllerNotificationReceiver::Dismiss(const int32_t msgId, const qcc::String appId)
{
    std::cout << "Got ControllerNotificationReceiver::DismissHandler with msgId=" << msgId << " appId=" << appId.c_str() << std::endl;
}
