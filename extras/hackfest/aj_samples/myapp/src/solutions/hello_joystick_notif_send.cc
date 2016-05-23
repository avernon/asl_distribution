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

#include <algorithm>
#include <iostream>
#include <signal.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/notification/NotificationService.h>
#include <alljoyn/notification/NotificationSender.h>
#include <alljoyn/notification/NotificationText.h>
#include <alljoyn/notification/RichAudioUrl.h>
#include <alljoyn/notification/NotificationEnums.h>
#include <alljoyn/about/AboutPropertyStoreImpl.h>
#include <alljoyn/about/AboutServiceApi.h>
#include <alljoyn/about/AnnouncementRegistrar.h>
#include <alljoyn/notification/Notification.h>
#include <qcc/String.h>
#include <alljoyn/services_common/LogModulesNames.h>

#include <aj_tutorial/joystick.h>

using namespace qcc;
using namespace ajn;

#define CHECK_RETURN(x) if ((status = x) != ER_OK) { return status; }

// Set application constants
#define DEVICE_NAME "testdeviceName"
#define APP_NAME "testappName"
#define LANG1  "en"
#define TEXT1 "Hello World"
#define LANG2  "es_SP"
#define TEXT2 "Hola Mundo"
#define KEY1 "On"
#define VAL1 "Hello"
#define KEY2 "Off"
#define VAL2 "Goodbye"
#define URL1 "http://url1.com"
#define URL2 "http://url2.com"
#define RICH_ICON_URL "http://iconurl.com"
#define CONTROL_PANEL_SERVICE_OBJECT_PATH "/ControlPanel/MyDevice/areYouSure"
#define RICH_ICON_OBJECT_PATH "/icon/objectPath"
#define RICH_AUDIO_OBJECT_PATH "/Audio/objectPath"
#define SERVICE_PORT 900

using namespace ajn;
using namespace services;

class BusListenerImpl : public ajn::BusListener, public ajn::SessionPortListener {
private:
  /**
   * The port used as part of the join session request
   */
  ajn::SessionPort m_SessionPort;

public:
    BusListenerImpl() : BusListener(), SessionPortListener(), m_SessionPort(0) {}

    /**
     * @param sessionPort - port of listener
     */
    BusListenerImpl(ajn::SessionPort sessionPort) : BusListener(), SessionPortListener(), m_SessionPort(sessionPort) {}

    ~BusListenerImpl() {}

    /**
     * AcceptSessionJoiner - Receive request to join session and decide whether to accept it or not
     * @param sessionPort - the port of the request
     * @param joiner - the name of the joiner
     * @param opts - the session options
     * @return true/false
     */
    bool AcceptSessionJoiner(ajn::SessionPort sessionPort, const char* joiner, const ajn::SessionOpts& opts)
    {
        if (sessionPort != m_SessionPort) {
            std::cout << "Rejecting join attempt on unexpected session port " << sessionPort << std::endl;
            return false;
        }

        std::cout << "Accepting JoinSessionRequest from " << joiner << " (opts.proximity= " << opts.proximity
                  << ", opts.traffic=" << opts.traffic << ", opts.transports=" << opts.transports << ")." << std::endl;
        return true;
    }

    /**
     * Set the Value of the SessionPort associated with this SessionPortListener
     * @param sessionPort
     */
    void setSessionPort(ajn::SessionPort sessionPort)
    {
        m_SessionPort = sessionPort;
    }

    /**
     * Get the SessionPort of the listener
     * @return
     */
    ajn::SessionPort getSessionPort()
    {
        return m_SessionPort;
    }

};

NotificationService* notificationService = 0;
NotificationSender* notificationSender = 0;
BusAttachment* busAttachment = 0;
AboutPropertyStoreImpl* aboutPropertyStore = 0;
BusListenerImpl*  busListener = 0;

void cleanup()
{
    // Clean up
    if (notificationService) {
        notificationService->shutdown();
        notificationService = NULL;
    }
    if (busAttachment && busListener) {
        if (busAttachment && busListener) {
        	busAttachment->UnregisterBusListener(*busListener);
        	busAttachment->UnbindSessionPort(busListener->getSessionPort());
        }
        AboutServiceApi::DestroyInstance();
    }
    if (busListener) {
        delete busListener;
        busListener = NULL;
    }
    if (aboutPropertyStore) {
        delete (aboutPropertyStore);
        aboutPropertyStore = NULL;
    }
    if (busAttachment) {
        delete busAttachment;
        busAttachment = NULL;
    }
    std::cout << "Goodbye!" << std::endl;
}

void signal_callback_handler(int32_t signum)
{
    cleanup();
    exit(signum);
}

QStatus FillAboutPropertyStoreImplData(AboutPropertyStoreImpl* propStore)
{
    QStatus status = ER_OK;

    // a platform-specific unique device id - ex. could be the Mac address
    CHECK_RETURN(propStore->setDeviceId("1231232145667745675477"))
    CHECK_RETURN(propStore->setDeviceName("MyDeviceName"))
    // the globally unique identifier for the application - recommend to use an online GUID generator to create
    CHECK_RETURN(propStore->setAppId("000102030405060708090A0B0C0D0E0C"))

    std::vector<qcc::String> languages(1);
    languages[0] = "en";
    CHECK_RETURN(propStore->setSupportedLangs(languages))
    CHECK_RETURN(propStore->setDefaultLang("en"))

    CHECK_RETURN(propStore->setAppName("NotificationProducer"))
    CHECK_RETURN(propStore->setModelNumber("Tutorial5000"))
    CHECK_RETURN(propStore->setDateOfManufacture("10/1/2013"))
    CHECK_RETURN(propStore->setSoftwareVersion("11.19.43 build 44454"))
    CHECK_RETURN(propStore->setAjSoftwareVersion(ajn::GetVersion()))
    CHECK_RETURN(propStore->setHardwareVersion("355.499. b"))

    CHECK_RETURN(propStore->setDescription("This is the NotificationProducer sample", "en"))
    CHECK_RETURN(propStore->setManufacturer("Company", "en"))

    CHECK_RETURN(propStore->setSupportUrl("http://www.allseenalliance.org"))
    return status;
}

/** Create the session, report the result to stdout, and return the status code. */
QStatus BindSession(BusListenerImpl& busListener) {
    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
    SessionPort sp = SERVICE_PORT;
    QStatus status = busAttachment->BindSessionPort(sp, opts, busListener);

    if (ER_OK == status) {
        std::cout << "BindSessionPort succeeded." << std::endl;
    } else {
        std::cout << "BindSessionPort failed (" << QCC_StatusText(status) << ")." << std::endl;
    }

    return status;
}

int main()
{
    // Allow CTRL+C to end application
    signal(SIGINT, signal_callback_handler);

    // Initialize Service object and Sender Object
    notificationService = NotificationService::getInstance();

    QCC_SetDebugLevel(logModules::NOTIFICATION_MODULE_LOG_NAME, logModules::ALL_LOG_LEVELS);

    busAttachment = new BusAttachment("NotificationProducer", true);

    /* Start the BusAttachment */
	QStatus status = busAttachment->Start();
	if (ER_OK != status) {
		delete busAttachment;
		busAttachment = NULL;
	}

	status = busAttachment->Connect();
	if (ER_OK != status) {
		delete busAttachment;
		busAttachment = NULL;
	}

    if (busAttachment == NULL) {
        std::cout << "Could not initialize BusAttachment." << std::endl;
        return EXIT_FAILURE;
    }

	if (ER_OK == status) {
		aboutPropertyStore = new AboutPropertyStoreImpl();
		status = FillAboutPropertyStoreImplData(aboutPropertyStore);
	}

	busListener = new BusListenerImpl();
	busListener->setSessionPort(SERVICE_PORT);
	busAttachment->RegisterBusListener(*busListener);

	if (ER_OK == status) {
		AboutServiceApi::Init(*busAttachment, *aboutPropertyStore);
		if (!AboutServiceApi::getInstance()) {
			std::cout << "Could not set up the AboutService." << std::endl;
			cleanup();
			return EXIT_FAILURE;
		}
	}

	if (ER_OK == status) {
		status = AboutServiceApi::getInstance()->Register(SERVICE_PORT);
	}
	if (ER_OK == status) {
		status = busAttachment->RegisterBusObject(*AboutServiceApi::getInstance());
	}
	if (ER_OK == status) {
		BindSession(*busListener);
	}
	if (ER_OK != status) {
		std::cout << "Bad status (" << QCC_StatusText(status) << ")." << std::endl;
		cleanup();
		return EXIT_FAILURE;
	}

    notificationSender = notificationService->initSend(busAttachment, aboutPropertyStore);
    if (!notificationSender) {
        std::cout << "Could not initialize Sender - exiting application" << std::endl;
        cleanup();
        return EXIT_FAILURE;
    }

    status = AboutServiceApi::getInstance()->Announce();
    if (ER_OK != status) {
        std::cout << "Could not announce." << std::endl;
        cleanup();
        return EXIT_FAILURE;
    }

    // Prepare message type
    NotificationMessageType messageType = INFO;

    int done = 0;
    Joystick js;
    uint16_t oldbuttons = 0;


    #define BUTTON_A 0x10
    #define BUTTON_B 0x08
    #define BUTTON_C 0x40
    #define BUTTON_D 0x20

    while (!done) {
        uint16_t buttons;
        int16_t x, y;

        if (js.ReadJoystick(buttons, x, y)) {
            uint16_t delta = oldbuttons ^ buttons;

            qcc::String button_str;

            if (delta & buttons & BUTTON_A) {
                printf("Button A pressed\n");
                button_str = "Button A pressed";
            } else if (delta & buttons & BUTTON_B) {
                printf("Button B pressed\n");
                button_str = "Button B pressed";
            } else if (delta & buttons & BUTTON_C) {
                printf("Button C pressed\n");
                button_str = "Button C pressed";
            } else if (delta & buttons & BUTTON_D) {
                printf("Button D pressed\n");
                button_str = "Button D pressed";
            } else {
                continue;
            }

            NotificationText textToSend(LANG1, button_str);
            std::vector<NotificationText> vecMessages;
            vecMessages.push_back(textToSend);

            Notification notification(messageType, vecMessages);

            status = notificationSender->send(notification, 7200);
            oldbuttons = buttons;
        }
    }
    cleanup();
    return 0;
}
