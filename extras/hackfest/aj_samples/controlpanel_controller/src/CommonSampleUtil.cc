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

#include <algorithm>
#include "CommonSampleUtil.h"
#include <alljoyn/about/AboutServiceApi.h>
#include <alljoyn/about/AnnouncementRegistrar.h>

using namespace ajn;
using namespace services;

#define CHECK_RETURN(x) if ((status = x) != ER_OK) { return status; }

BusAttachment* CommonSampleUtil::prepareBusAttachment(ajn::AuthListener* authListener)
{
    BusAttachment* bus = new BusAttachment("CommonServiceApp", true);

    /* Start the BusAttachment */
    QStatus status = bus->Start();
    if (status != ER_OK) {
        delete bus;
        return NULL;
    }

    /* Connect to the daemon using address provided*/
    status = bus->Connect();
    if (status != ER_OK) {
        delete bus;
        return NULL;
    }

    if (authListener) {
        status = CommonSampleUtil::EnableSecurity(bus, authListener);
        if (status != ER_OK) {
            delete bus;
            return NULL;
        }
    }

    return bus;
}

QStatus CommonSampleUtil::fillPropertyStore(AboutPropertyStoreImpl* propertyStore, qcc::String const& appIdHex,
                                            qcc::String const& appName, qcc::String const& deviceId, qcc::String const& deviceName,
                                            qcc::String const& defaultLanguage)
{
    if (!propertyStore) {
        return ER_BAD_ARG_1;
    }

    QStatus status = ER_OK;

    CHECK_RETURN(propertyStore->setDeviceId(deviceId))
    CHECK_RETURN(propertyStore->setDeviceName(deviceName))
    CHECK_RETURN(propertyStore->setAppId(appIdHex))
    CHECK_RETURN(propertyStore->setAppName(appName))

    std::vector<qcc::String> languages(3);
    languages[0] = "en";
    languages[1] = "sp";
    languages[2] = "fr";
    CHECK_RETURN(propertyStore->setSupportedLangs(languages))
    CHECK_RETURN(propertyStore->setDefaultLang(defaultLanguage))

    CHECK_RETURN(propertyStore->setModelNumber("Wxfy388i"))
    CHECK_RETURN(propertyStore->setDateOfManufacture("10/1/2199"))
    CHECK_RETURN(propertyStore->setSoftwareVersion("12.20.44 build 44454"))
    CHECK_RETURN(propertyStore->setAjSoftwareVersion(ajn::GetVersion()))
    CHECK_RETURN(propertyStore->setHardwareVersion("355.499. b"))

    CHECK_RETURN(propertyStore->setDescription("This is an Alljoyn Application", "en"))
    CHECK_RETURN(propertyStore->setDescription("Esta es una Alljoyn aplicacion", "sp"))
    CHECK_RETURN(propertyStore->setDescription("C'est une Alljoyn application", "fr"))

    CHECK_RETURN(propertyStore->setManufacturer("Company", "en"))
    CHECK_RETURN(propertyStore->setManufacturer("Empresa", "sp"))
    CHECK_RETURN(propertyStore->setManufacturer("Entreprise", "fr"))

    CHECK_RETURN(propertyStore->setSupportUrl("http://www.alljoyn.org"))

    return status;
}

QStatus CommonSampleUtil::prepareAboutService(BusAttachment* bus, AboutPropertyStoreImpl* propertyStore,
                                              CommonBusListener* busListener, uint16_t port)
{
    if (!bus) {
        return ER_BAD_ARG_1;
    }

    if (!propertyStore) {
        return ER_BAD_ARG_2;
    }

    if (!busListener) {
        return ER_BAD_ARG_3;
    }

    AboutServiceApi::Init(*bus, *propertyStore);
    AboutServiceApi* aboutService = AboutServiceApi::getInstance();
    if (!aboutService) {
        return ER_BUS_NOT_ALLOWED;
    }

    busListener->setSessionPort(port);
    bus->RegisterBusListener(*busListener);

    TransportMask transportMask = TRANSPORT_ANY;
    SessionPort sp = port;
    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, transportMask);

    QStatus status = bus->BindSessionPort(sp, opts, *busListener);
    if (status != ER_OK) {
        return status;
    }

    status = aboutService->Register(port);
    if (status != ER_OK) {
        return status;
    }

    return (bus->RegisterBusObject(*aboutService));
}

QStatus CommonSampleUtil::aboutServiceAnnounce()
{
    AboutServiceApi* aboutService = AboutServiceApi::getInstance();
    if (!aboutService) {
        return ER_BUS_NOT_ALLOWED;
    }

    return (aboutService->Announce());
}

void CommonSampleUtil::aboutServiceDestroy(BusAttachment* bus,
                                           CommonBusListener* busListener)
{
    if (bus && busListener) {
        bus->UnregisterBusListener(*busListener);
        bus->UnbindSessionPort(busListener->getSessionPort());
    }

    AboutServiceApi::DestroyInstance();
    return;
}

QStatus CommonSampleUtil::addSessionlessMatch(BusAttachment*bus)
{
    if (!bus) {
        return ER_BAD_ARG_1;
    }

    return bus->AddMatch("sessionless='t',type='error'");
}

QStatus CommonSampleUtil::EnableSecurity(BusAttachment* bus, AuthListener* authListener)
{
    QStatus status = bus->EnablePeerSecurity("ALLJOYN_PIN_KEYX ALLJOYN_SRP_KEYX", authListener);
    return status;
}
