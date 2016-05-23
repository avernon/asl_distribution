/******************************************************************************
 * Copyright (c) 2013 - 2014, AllSeen Alliance. All rights reserved.
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

#include <stdio.h>
#include <signal.h>
#include <fstream>
#include <map>
#include <stdint.h>

#include <SrpKeyXListener.h>
#include <CommonBusListener.h>
#include <PropertyStoreImpl.h>
#include <IniParser.h>
#include <CommonSampleUtil.h>
#include <OptParser.h>
#include "ConfigServiceListenerImpl.h"

#include <alljoyn/version.h>
#include <qcc/platform.h>
#include <qcc/Log.h>
#include <qcc/String.h>

#include <alljoyn/BusObject.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/Status.h>

#include <alljoyn/config/ConfigService.h>
#include <alljoyn/about/AboutIconService.h>
#include <alljoyn/about/PropertyStore.h>

#include <alljoyn/onboarding/Onboarding.h>
#include <alljoyn/onboarding/OnboardingService.h>
#include <OnboardingControllerImpl.h>
#include <alljoyn/about/AboutServiceApi.h>
#include <alljoyn/services_common/LogModulesNames.h>

using namespace ajn;
using namespace services;

#define SERVICE_EXIT_OK       0
#define SERVICE_OPTION_ERROR  1
#define SERVICE_CONFIG_ERROR  2

/** static variables need for sample */
static BusAttachment* msgBus = NULL;

static SrpKeyXListener* keyListener = NULL;

static ConfigService* configService = NULL;

static AboutIconService* aboutIconService = NULL;

static PropertyStoreImpl* propertyStore = NULL;

static ConfigServiceListenerImpl* configServiceListener = NULL;

static OnboardingControllerImpl* obController = NULL;

static CommonBusListener* busListener = NULL;

static SessionPort SERVICE_PORT;

static qcc::String configFile;

static volatile sig_atomic_t s_interrupt = false;

static void SigIntHandler(int sig) {
    s_interrupt = true;
}

static void cleanup() {

    if (AboutServiceApi::getInstance()) {
        AboutServiceApi::DestroyInstance();
    }

    if (configService) {
        delete configService;
        configService = NULL;
    }

    if (configServiceListener) {
        delete configServiceListener;
        configServiceListener = NULL;
    }

    if (keyListener) {
        delete keyListener;
        keyListener = NULL;
    }

    if (aboutIconService) {
        delete aboutIconService;
        aboutIconService = NULL;
    }

    if (propertyStore) {
        delete propertyStore;
        propertyStore = NULL;
    }

    if (obController) {
        delete obController;
        obController = NULL;
    }

    if (busListener) {
        msgBus->UnregisterBusListener(*busListener);
        delete busListener;
        busListener = NULL;
    }

    /* Clean up msg bus */
    delete msgBus;
    msgBus = NULL;

}

const char* readPassword() {
    std::map<std::string, std::string> data;
    if (!IniParser::ParseFile(configFile.c_str(), data)) {
        return NULL;
    }

    std::map<std::string, std::string>::iterator iter = data.find("passcode");
    if (iter == data.end()) {
        return NULL;
    }

    return iter->second.c_str();
}

/** Advertise the service name, report the result to stdout, and return the status code. */
QStatus AdvertiseName(TransportMask mask) {
    QStatus status = ER_BUS_ESTABLISH_FAILED;
    if (msgBus->IsConnected() && msgBus->GetUniqueName().size() > 0) {
        status = msgBus->AdvertiseName(msgBus->GetUniqueName().c_str(), mask);
        std::cout << "AdvertiseName for " << msgBus->GetUniqueName().c_str() << " = " << QCC_StatusText(status) << std::endl;
    }
    return status;
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

int main(int argc, char**argv, char**envArg) {
    QStatus status = ER_OK;
    std::cout << "AllJoyn Library version: " << ajn::GetVersion() << std::endl;
    std::cout << "AllJoyn Library build info: " << ajn::GetBuildInfo() << std::endl;
    QCC_SetLogLevels("ALLJOYN_ABOUT_SERVICE=7;");
    QCC_SetLogLevels("ALLJOYN_ABOUT_ICON_SERVICE=7;");

    OptParser opts(argc, argv);
    OptParser::ParseResultCode parseCode(opts.ParseResult());
    switch (parseCode) {
    case OptParser::PR_OK:
        break;

    case OptParser::PR_EXIT_NO_ERROR:
        return SERVICE_EXIT_OK;

    default:
        return SERVICE_OPTION_ERROR;
    }

    SERVICE_PORT = opts.GetPort();
    std::cout << "using port " << opts.GetPort() << std::endl;

    if (!opts.GetConfigFile().empty()) {
        std::cout << "using Config-file " << configFile.c_str() << std::endl;
        if (!opts.ParseExternalXML()) {
            return 1;
        }
    }

    if (!opts.GetAppId().empty()) {
        std::cout << "using appID " << opts.GetAppId().c_str() << std::endl;
    }

    /* Install SIGINT handler so Ctrl + C deallocates memory properly */
    signal(SIGINT, SigIntHandler);

    //set Daemon password only for bundled app
    #ifdef QCC_USING_BD
    PasswordManager::SetCredentials("ALLJOYN_PIN_KEYX", "000000");
    #endif

    /* Create message bus */
    keyListener = new SrpKeyXListener();
    msgBus = CommonSampleUtil::prepareBusAttachment(keyListener);
    if (msgBus == NULL) {
        std::cout << "Could not initialize BusAttachment." << std::endl;
        delete keyListener;
        return 1;
    }

    busListener = new CommonBusListener(msgBus);
    busListener->setSessionPort(SERVICE_PORT);

    propertyStore = new PropertyStoreImpl(opts.GetFactoryConfigFile().c_str(), opts.GetConfigFile().c_str());
    status = CommonSampleUtil::fillPropertyStore(propertyStore, opts.GetAppId(), opts.GetAppName(), opts.GetDeviceId(),
                                                 opts.GetDeviceName(), opts.GetDefaultLanguage());
    propertyStore->Initialize();
    if (status != ER_OK) {
        std::cout << "Could not fill PropertyStore." << std::endl;
        cleanup();
        return 1;
    }

    status = CommonSampleUtil::prepareAboutService(msgBus, propertyStore, busListener, SERVICE_PORT);
    if (status != ER_OK) {
        std::cout << "Could not set up the AboutService." << std::endl;
        cleanup();
        return 1;
    }

    AboutService* aboutService = AboutServiceApi::getInstance();
    if (!aboutService) {
        std::cout << "Could not set up the AboutService." << std::endl;
        cleanup();
        return 1;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //aboutIconService
    uint8_t aboutIconContent[] = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x0A,
                                   0x00, 0x00, 0x00, 0x0A, 0x08, 0x02, 0x00, 0x00, 0x00, 0x02, 0x50, 0x58, 0xEA, 0x00, 0x00, 0x00, 0x04, 0x67, 0x41, 0x4D, 0x41, 0x00, 0x00, 0xAF,
                                   0xC8, 0x37, 0x05, 0x8A, 0xE9, 0x00, 0x00, 0x00, 0x19, 0x74, 0x45, 0x58, 0x74, 0x53, 0x6F, 0x66, 0x74, 0x77, 0x61, 0x72, 0x65, 0x00, 0x41, 0x64,
                                   0x6F, 0x62, 0x65, 0x20, 0x49, 0x6D, 0x61, 0x67, 0x65, 0x52, 0x65, 0x61, 0x64, 0x79, 0x71, 0xC9, 0x65, 0x3C, 0x00, 0x00, 0x00, 0x18, 0x49, 0x44,
                                   0x41, 0x54, 0x78, 0xDA, 0x62, 0xFC, 0x3F, 0x95, 0x9F, 0x01, 0x37, 0x60, 0x62, 0xC0, 0x0B, 0x46, 0xAA, 0x34, 0x40, 0x80, 0x01, 0x00, 0x06, 0x7C,
                                   0x01, 0xB7, 0xED, 0x4B, 0x53, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82 };

    qcc::String mimeType("image/png");
    qcc::String url(""); //put your url here

    std::vector<qcc::String> interfaces;
    interfaces.push_back("org.alljoyn.Icon");
    aboutService->AddObjectDescription("/About/DeviceIcon", interfaces);

    aboutIconService = new AboutIconService(*msgBus, mimeType, url, aboutIconContent, sizeof(aboutIconContent) / sizeof(*aboutIconContent));
    status = aboutIconService->Register();
    if (status != ER_OK) {
        std::cout << "Could not register the AboutIconService." << std::endl;
        cleanup();
        return 1;
    }

    status = msgBus->RegisterBusObject(*aboutIconService);
    if (status != ER_OK) {
        std::cout << "Could not register the AboutIconService BusObject." << std::endl;
        cleanup();
        return 1;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //OnboardingService

    obController = new OnboardingControllerImpl(opts.GetScanFile(),
                                                opts.GetStateFile(),
                                                opts.GetErrorFile(),
                                                opts.GetConfigureCmd(),
                                                opts.GetConnectCmd(),
                                                opts.GetOffboardCmd(),
                                                (OBConcurrency)opts.GetConcurrency(),
                                                *msgBus);
    OnboardingService onboardingService(*msgBus, *obController);

    interfaces.clear();
    interfaces.push_back("org.alljoyn.Onboarding");
    aboutService->AddObjectDescription("/Onboarding", interfaces);

    status = onboardingService.Register();
    if (status != ER_OK) {
        std::cout << "Could not register the OnboardingService." << std::endl;
        cleanup();
        return 1;
    }

    status = msgBus->RegisterBusObject(onboardingService);
    if (status != ER_OK) {
        std::cout << "Could not register the OnboardingService BusObject." << std::endl;
        cleanup();
        return 1;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //ConfigService

    configServiceListener = new ConfigServiceListenerImpl(*propertyStore, *msgBus, *busListener, *obController);
    configService = new ConfigService(*msgBus, *propertyStore, *configServiceListener);
    configFile = opts.GetConfigFile().c_str();
    keyListener->setGetPassCode(readPassword);

    interfaces.clear();
    interfaces.push_back("org.alljoyn.Config");
    aboutService->AddObjectDescription("/Config", interfaces);

    status = configService->Register();
    if (status != ER_OK) {
        std::cout << "Could not register the ConfigService." << std::endl;
        cleanup();
        return 1;
    }

    status = msgBus->RegisterBusObject(*configService);
    if (status != ER_OK) {
        std::cout << "Could not register the ConfigService BusObject." << std::endl;
        cleanup();
        return 1;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const TransportMask SERVICE_TRANSPORT_TYPE = TRANSPORT_ANY;

    if (ER_OK == status) {
        status = AdvertiseName(SERVICE_TRANSPORT_TYPE);
    }

    if (ER_OK == status) {
        status = aboutService->Announce();
    }

    /* Perform the service asynchronously until the user signals for an exit. */
    if (ER_OK == status) {
        WaitForSigInt();
    }

    cleanup();

    return 0;
} /* main() */

