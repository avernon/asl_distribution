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

#include <iostream>
#include <sstream>
#include <cstdio>
#include <signal.h>
#include <alljoyn/notification/Notification.h>
#include <alljoyn/notification/NotificationService.h>
#include <alljoyn/notification/NotificationText.h>
#include <alljoyn/controlpanel/ControlPanelService.h>
#include <alljoyn/controlpanel/ControlPanelControllee.h>
#include <SrpKeyXListener.h>
#include <GuidUtil.h>
#include <CommonSampleUtil.h>
#include <ControlPanelGenerated.h>
#include <alljoyn/services_common/LogModulesNames.h>

#define SERVICE_PORT 900

using namespace ajn;
using namespace services;
using namespace qcc;

AboutPropertyStoreImpl* propertyStoreImpl = 0;
CommonBusListener* controlpanelBusListener = 0;
BusAttachment* bus = 0;
ControlPanelService* controlPanelService = 0;
ControlPanelControllee* controlPanelControllee = 0;
SrpKeyXListener* srpKeyXListener = 0;

NotificationService* prodService = 0;
NotificationSender* sender = 0;

void exitApp(int32_t signum)
{
    std::cout << "Program Finished" << std::endl;

    CommonSampleUtil::aboutServiceDestroy(bus, controlpanelBusListener);
    if (controlPanelService) {
        controlPanelService->shutdownControllee();
    }
    if (prodService) {
        prodService->shutdown();
    }
    ControlPanelGenerated::Shutdown();
    if (sender) {
        delete sender;
    }
    if (controlPanelControllee) {
        delete controlPanelControllee;
    }
    if (controlpanelBusListener) {
        delete controlpanelBusListener;
    }
    if (propertyStoreImpl) {
        delete (propertyStoreImpl);
    }
    if (controlPanelService) {
        delete controlPanelService;
    }
    if (srpKeyXListener) {
        delete srpKeyXListener;
    }
    if (bus) {
        delete bus;
    }

    std::cout << "Goodbye!" << std::endl;
    exit(signum);
}

int32_t main()
{
    QStatus status;

    // Allow CTRL+C to end application
    signal(SIGINT, exitApp);
    std::cout << "Beginning ControlPanel Application. (Press CTRL+C to end application)" << std::endl;

    // Initialize Service objects
#ifdef QCC_USING_BD
    PasswordManager::SetCredentials("ALLJOYN_PIN_KEYX", "000000");
#endif

    controlpanelBusListener = new CommonBusListener();;
    controlPanelService = ControlPanelService::getInstance();
    QCC_SetDebugLevel(logModules::CONTROLPANEL_MODULE_LOG_NAME, logModules::ALL_LOG_LEVELS);

    // Initialize Service object and Sender Object
    prodService = NotificationService::getInstance();


    srpKeyXListener = new SrpKeyXListener();

    bus = CommonSampleUtil::prepareBusAttachment(srpKeyXListener);
    if (bus == NULL) {
        std::cout << "Could not initialize BusAttachment." << std::endl;
        exitApp(1);
    }

    qcc::String device_id, app_id;
    qcc::String app_name = "testappName", device_name = "testdeviceName";
    GuidUtil::GetInstance()->GetDeviceIdString(&device_id);
    GuidUtil::GetInstance()->GenerateGUID(&app_id);

    propertyStoreImpl = new AboutPropertyStoreImpl();
    status = CommonSampleUtil::fillPropertyStore(propertyStoreImpl, app_id, app_name, device_id, device_name);
    if (status != ER_OK) {
        std::cout << "Could not fill PropertyStore." << std::endl;
        exitApp(1);
    }

    status = CommonSampleUtil::prepareAboutService(bus, propertyStoreImpl,
                                                   controlpanelBusListener, SERVICE_PORT);
    if (status != ER_OK) {
        std::cout << "Could not register bus object." << std::endl;
        exitApp(1);
    }

    status = ControlPanelGenerated::PrepareWidgets(controlPanelControllee);
    if (status != ER_OK) {
        std::cout << "Could not prepare Widgets." << std::endl;
        exitApp(1);
    }

    status = controlPanelService->initControllee(bus, controlPanelControllee);
    if (status != ER_OK) {
        std::cout << "Could not initialize Controllee." << std::endl;
        exitApp(1);
    }

    sender = prodService->initSend(bus, propertyStoreImpl);
    if (!sender) {
        std::cout << "Could not initialize Sender - exiting application" << std::endl;
        exitApp(1);
    }

    status = CommonSampleUtil::aboutServiceAnnounce();
    if (status != ER_OK) {
        std::cout << "Could not announce." << std::endl;
        exitApp(1);
    }

    std::cout << "Sent announce, waiting for Contollers" << std::endl;
    std::cout << "Enter in the ControlPanelService object path or press 'enter' to use default:" << std::endl;

    std::string input;
    qcc::String controlPanelServiceObjectPath;
    qcc::String defaultControlPanelServiceObjectPath = "/ControlPanel/MyDevice/areYouSure";

    getline(std::cin, input);
    while (!std::cin.eof()) {
        controlPanelServiceObjectPath = input.length() ? input.c_str() : defaultControlPanelServiceObjectPath;

        NotificationMessageType messageType = INFO;
        NotificationText textToSend("en", "Sending CPS ObjectPath");
        std::vector<NotificationText> vecMessages;
        vecMessages.push_back(textToSend);
        Notification notification(messageType, vecMessages);
        notification.setControlPanelServiceObjectPath(controlPanelServiceObjectPath.c_str());

        status = sender->send(notification, 7200);
        if (status != ER_OK) {
            std::cout << "Notification was not sent successfully" << std::endl;
        } else {
            std::cout << "Notification sent successfully" << std::endl;
        }

        std::cout << "Enter in the ControlPanelService object path or press 'enter' to use default:" << std::endl;
        getline(std::cin, input);
    }
    std::cout << "Exiting in 10 seconds" << std::endl;
    sleep(10);
    exitApp(0);
}
