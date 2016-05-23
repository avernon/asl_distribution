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

#include <iostream>
#include <sstream>
#include <cstdio>
#include <signal.h>

#ifdef _WIN32
/* Disable deprecation warnings */
#pragma warning(disable: 4996)
#endif

#include <alljoyn/notification/NotificationService.h>
#include <alljoyn/controlpanel/ControlPanelService.h>
#include <alljoyn/controlpanel/ControlPanelController.h>
#include "ControlPanelListenerImpl.h"
#include "ControllerNotificationReceiver.h"
#include <SrpKeyXListener.h>
#include <CommonSampleUtil.h>
#include <AnnounceHandlerImpl.h>
#include <alljoyn/services_common/LogModulesNames.h>
#include <AJInitializer.h>

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
static volatile sig_atomic_t s_interrupt = false;

static void CDECL_CALL SigIntHandler(int sig)
{
    QCC_UNUSED(sig);
    s_interrupt = true;
}

void cleanup()
{
    if (bus && announceHandler) {
        const char* interfaces[] = { "*" };
        bus->CancelWhoImplements(interfaces, sizeof(interfaces) / sizeof(interfaces[0]));
        bus->UnregisterAboutListener(*announceHandler);
    }

    if (controlPanelService) {
        controlPanelService->shutdownController();
        delete controlPanelService;
        controlPanelService = NULL;
    }
    if (controlPanelController) {
        delete controlPanelController;
        controlPanelController = NULL;
    }
    if (controlPanelListener) {
        delete controlPanelListener;
        controlPanelListener = NULL;
    }
    if (announceHandler) {
        delete announceHandler;
        announceHandler = NULL;
    }
    if (srpKeyXListener) {
        delete srpKeyXListener;
        srpKeyXListener = NULL;
    }
    if (conService) {
        conService->shutdown();
        conService = NULL;
    }
    if (receiver) {
        delete receiver;
        receiver = NULL;
    }
    if (bus) {
        delete bus;
        bus = NULL;
    }
}

static void announceHandlerCallback(qcc::String const& busName, unsigned short version,
                                    unsigned short port, const ajn::AboutObjectDescription& objectDescription,
                                    const ajn::AboutData& aboutData)
{

    QCC_UNUSED(version);
    QCC_UNUSED(port);
    QCC_UNUSED(aboutData);
    std::cout << "Got announceHandlerCallback" << std::endl;
    controlPanelController->createControllableDevice(busName, objectDescription);
}

void WaitForSigInt(void) {
    while (s_interrupt == false) {
#ifdef _WIN32
        Sleep(100);
#else
        usleep(100 * 1000);
#endif
    }
}

int main()
{
    // Initialize AllJoyn
    AJInitializer ajInit;
    if (ajInit.Initialize() != ER_OK) {
        return 1;
    }

    QStatus status;

    // Allow CTRL+C to end application
    signal(SIGINT, SigIntHandler);
    std::cout << "Beginning ControlPanel Application. (Press CTRL+C to end application)" << std::endl;

    // Initialize Service objects

    controlPanelService = ControlPanelService::getInstance();
    QCC_SetDebugLevel(logModules::CONTROLPANEL_MODULE_LOG_NAME, logModules::ALL_LOG_LEVELS);

    srpKeyXListener = new SrpKeyXListener();

    bus = CommonSampleUtil::prepareBusAttachment(srpKeyXListener);
    if (bus == NULL) {
        std::cout << "Could not initialize BusAttachment." << std::endl;
        cleanup();
        return 1;
    }

    controlPanelController = new ControlPanelController();
    controlPanelListener = new ControlPanelListenerImpl(controlPanelController);

    status = controlPanelService->initController(bus, controlPanelController, controlPanelListener);
    if (status != ER_OK) {
        std::cout << "Could not initialize Controllee." << std::endl;
        cleanup();
        return 1;
    }

    announceHandler = new AnnounceHandlerImpl(NULL, announceHandlerCallback);
    bus->RegisterAboutListener(*announceHandler);

    const char* interfaces[] = { "*" };
    status = bus->WhoImplements(interfaces, sizeof(interfaces) / sizeof(interfaces[0]));
    if (ER_OK == status) {
        std::cout << "WhoImplements called." << std::endl;
    } else {
        std::cout << "ERROR - WhoImplements failed." << std::endl;
    }

    conService = NotificationService::getInstance();
    receiver = new ControllerNotificationReceiver(controlPanelController);
    status = conService->initReceive(bus, receiver);
    if (status != ER_OK) {
        std::cout << "Could not initialize receiver." << std::endl;
        cleanup();
        return 1;
    }

    std::cout << "Finished setup. Waiting for Contollees" << std::endl;

    WaitForSigInt();
    cleanup();

    return 0;
}


