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
#include <alljoyn/about/AnnouncementRegistrar.h>
#include <alljoyn/notification/NotificationService.h>
#include <alljoyn/controlpanel/ControlPanelService.h>
#include <alljoyn/controlpanel/ControlPanelController.h>
#include "ControlPanelListenerImpl.h"
#include "ControllerNotificationReceiver.h"
#include <SrpKeyXListener.h>
#include <CommonSampleUtil.h>
#include <AnnounceHandlerImpl.h>
#include <alljoyn/services_common/LogModulesNames.h>

#define SERVICE_PORT 900

using namespace ajn;
using namespace services;
using namespace qcc;

BusAttachment* bus = 0;
ControlPanelService* controlPanelService = 0;
ControlPanelController* controlPanelController = 0;
ControlPanelListenerImpl* controlPanelListener = 0;
SrpKeyXListener* srpKeyXListener = 0;
AnnounceHandlerImpl* announceHandler = 0;
NotificationService* conService = 0;
ControllerNotificationReceiver* receiver = 0;
qcc::String ControlPanelPrefix = "/ControlPanel/";

void exitApp(int32_t signum)
{
    std::cout << "Program Finished" << std::endl;

    if (bus && announceHandler) {
        AnnouncementRegistrar::UnRegisterAnnounceHandler(*bus, *announceHandler);
    }

    if (controlPanelService) {
        controlPanelService->shutdownController();
        delete controlPanelService;
    }
    if (controlPanelController) {
        delete controlPanelController;
    }
    if (controlPanelListener) {
        delete controlPanelListener;
    }
    if (announceHandler) {
        delete announceHandler;
    }
    if (srpKeyXListener) {
        delete srpKeyXListener;
    }
    if (conService) {
        conService->shutdown();
    }
    if (receiver) {
        delete receiver;
    }
    if (bus) {
        delete bus;
    }

    std::cout << "Goodbye!" << std::endl;
    exit(signum);
}

static void announceHandlerCallback(qcc::String const& busName, unsigned short version, unsigned short port,
                                    const AnnounceHandler::ObjectDescriptions& objectDescs, const AnnounceHandler::AboutData& aboutData)
{
    controlPanelController->createControllableDevice(busName, objectDescs);
}

int main()
{
    QStatus status;

    // Allow CTRL+C to end application
    signal(SIGINT, exitApp);
    std::cout << "Beginning ControlPanel Application. (Press CTRL+C to end application)" << std::endl;

    // Initialize Service objects
#ifdef QCC_USING_BD
    PasswordManager::SetCredentials("ALLJOYN_PIN_KEYX", "000000");
#endif

    controlPanelService = ControlPanelService::getInstance();
    QCC_SetDebugLevel(logModules::CONTROLPANEL_MODULE_LOG_NAME, logModules::ALL_LOG_LEVELS);

    srpKeyXListener = new SrpKeyXListener();

    bus = CommonSampleUtil::prepareBusAttachment(srpKeyXListener);
    if (bus == NULL) {
        std::cout << "Could not initialize BusAttachment." << std::endl;
        exitApp(1);
    }

    controlPanelController = new ControlPanelController();
    controlPanelListener = new ControlPanelListenerImpl(controlPanelController);

    status = controlPanelService->initController(bus, controlPanelController, controlPanelListener);
    if (status != ER_OK) {
        std::cout << "Could not initialize Controllee." << std::endl;
        exitApp(1);
    }

    announceHandler = new AnnounceHandlerImpl(NULL, announceHandlerCallback);
    AnnouncementRegistrar::RegisterAnnounceHandler(*bus, *announceHandler);

    conService = NotificationService::getInstance();
    receiver = new ControllerNotificationReceiver(controlPanelController);
    status = conService->initReceive(bus, receiver);
    if (status != ER_OK) {
        std::cout << "Could not initialize receiver." << std::endl;
        exitApp(1);
    }

    status = CommonSampleUtil::addSessionlessMatch(bus);
    if (status != ER_OK) {
        std::cout << "Could not add Sessionless Match" << std::endl;
        exitApp(1);
    }

    std::cout << "Finished setup. Waiting for Contollees" << std::endl;
    while (1) {
        sleep(1);
    }
}


