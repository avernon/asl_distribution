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

#include <alljoyn/notification/Notification.h>
#include <alljoyn/notification/NotificationService.h>
#include <alljoyn/notification/NotificationText.h>
#include <alljoyn/controlpanel/ControlPanelService.h>
#include <alljoyn/controlpanel/ControlPanelControllee.h>
#include <SrpKeyXListener.h>
#include <CommonSampleUtil.h>
#include <ControlPanelGenerated.h>
#include <alljoyn/services_common/LogModulesNames.h>
#include <alljoyn/services_common/GuidUtil.h>
#include <alljoyn/AboutData.h>
#include <AJInitializer.h>

#define SERVICE_PORT 900

using namespace ajn;
using namespace services;
using namespace qcc;

AboutData* aboutData = NULL;
AboutObj* aboutObj = NULL;
CommonBusListener* controlpanelBusListener = 0;
BusAttachment* bus = 0;
ControlPanelService* controlPanelService = 0;
ControlPanelControllee* controlPanelControllee = 0;
SrpKeyXListener* srpKeyXListener = 0;

NotificationService* prodService = 0;
NotificationSender* sender = 0;

static volatile sig_atomic_t s_interrupt = false;

static volatile sig_atomic_t s_restart = false;

static void CDECL_CALL SigIntHandler(int sig)
{
    QCC_UNUSED(sig);
    s_interrupt = true;
}

static void daemonDisconnectCB()
{
    s_restart = true;
}

void cleanup()
{
    CommonSampleUtil::aboutServiceDestroy(bus, controlpanelBusListener);
    if (controlPanelService) {
        controlPanelService->shutdownControllee();
    }
    if (prodService) {
        prodService->shutdown();
        prodService = NULL;
    }
    ControlPanelGenerated::Shutdown();
    if (sender) {
        delete sender;
        sender = NULL;
    }
    if (controlPanelControllee) {
        delete controlPanelControllee;
        controlPanelControllee = NULL;
    }
    if (controlpanelBusListener) {
        delete controlpanelBusListener;
        controlpanelBusListener = NULL;
    }
    if (aboutData) {
        delete aboutData;
        aboutData = NULL;
    }
    if (aboutObj) {
        delete aboutObj;
        aboutObj = NULL;
    }
    if (controlPanelService) {
        delete controlPanelService;
        controlPanelService = NULL;
    }
    if (srpKeyXListener) {
        delete srpKeyXListener;
        srpKeyXListener = NULL;
    }
    if (bus) {
        delete bus;
        bus = NULL;
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
    std::cout << "Beginning ControlPanel Application. (Press CTRL+C and enter or CTRL+D to end application)" << std::endl;

    // Initialize Service objects

start:
    controlPanelService = ControlPanelService::getInstance();
    QCC_SetDebugLevel(logModules::CONTROLPANEL_MODULE_LOG_NAME, logModules::ALL_LOG_LEVELS);

    // Initialize Service object and Sender Object
    prodService = NotificationService::getInstance();

    srpKeyXListener = new SrpKeyXListener();

    /* Connect to the daemon */
    uint16_t retry = 0;
    do {
        bus = CommonSampleUtil::prepareBusAttachment(srpKeyXListener);
        if (bus == NULL) {
            std::cout << "Could not initialize BusAttachment. Retrying" << std::endl;
#ifdef _WIN32
            Sleep(1000);
#else
            sleep(1);
#endif
            retry++;
        }
    } while (bus == NULL && retry != 180 && !s_interrupt);

    if (bus == NULL) {
        std::cout << "Could not initialize BusAttachment." << std::endl;
        cleanup();
        return 1;
    }

    controlpanelBusListener = new CommonBusListener(bus, daemonDisconnectCB);

    qcc::String device_id, app_id;
    qcc::String app_name = "testappName";
    DeviceNamesType deviceNames;
    deviceNames.insert(std::pair<qcc::String, qcc::String>("en", "testDeviceName"));
    GuidUtil::GetInstance()->GetDeviceIdString(&device_id);
    GuidUtil::GetInstance()->GenerateGUID(&app_id);

    aboutData = new AboutData("en");
    status = CommonSampleUtil::fillAboutData(aboutData, app_id, app_name, device_id, deviceNames);
    if (status != ER_OK) {
        std::cout << "Could not fill About Data." << std::endl;
        cleanup();
        return 1;
    }
    aboutObj = new AboutObj(*bus, BusObject::ANNOUNCED);
    status = CommonSampleUtil::prepareAboutService(bus, aboutData, aboutObj,
                                                   controlpanelBusListener, SERVICE_PORT);
    if (status != ER_OK) {
        std::cout << "Could not register bus object." << std::endl;
        cleanup();
        return 1;
    }

    status = ControlPanelGenerated::PrepareWidgets(controlPanelControllee);
    if (status != ER_OK) {
        std::cout << "Could not prepare Widgets." << std::endl;
        cleanup();
        return 1;
    }

    status = controlPanelService->initControllee(bus, controlPanelControllee);
    if (status != ER_OK) {
        std::cout << "Could not initialize Controllee." << std::endl;
        cleanup();
        return 1;
    }

    sender = prodService->initSend(bus, aboutData);
    if (!sender) {
        std::cout << "Could not initialize Sender - exiting application" << std::endl;
        cleanup();
        return 1;
    }

    status = CommonSampleUtil::aboutServiceAnnounce();
    if (status != ER_OK) {
        std::cout << "Could not announce." << std::endl;
        cleanup();
        return 1;
    }

    std::cout << "Sent announce, waiting for Contollers" << std::endl;
    std::cout << "Enter in the ControlPanelService object path or press 'enter' to use default:" << std::endl;

    std::string input;
    qcc::String controlPanelServiceObjectPath;
    qcc::String defaultControlPanelServiceObjectPath = "/ControlPanel/MyDevice/areYouSure";

    getline(std::cin, input);
    while (s_interrupt == false && s_restart == false && !std::cin.eof()) {
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

    std::cout << "Cleaning up in 10 seconds" << std::endl;
#ifdef _WIN32
    Sleep(10 * 1000);
#else
    sleep(10);
#endif

    if (s_restart) {
        s_restart = false;
        goto start;
    }

    return 0;
}
