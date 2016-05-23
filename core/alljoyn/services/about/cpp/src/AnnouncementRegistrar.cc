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

#include <alljoyn/about/AnnouncementRegistrar.h>
#include <qcc/Debug.h>
#include <qcc/String.h>

#include "InternalAnnounceHandler.h"

#define QCC_MODULE "ALLJOYN_ABOUT_ANNOUNCEMENT_REGISTRAR"

using namespace ajn;
using namespace services;

static InternalAnnounceHandler* internalAnnounceHandler = NULL;

QStatus AnnouncementRegistrar::RegisterAnnounceHandler(ajn::BusAttachment& bus, AnnounceHandler& handler, const char** implementsInterfaces, size_t numberInterfaces) {
    QCC_DbgTrace(("AnnouncementRegistrar::%s", __FUNCTION__));
    QStatus status = ER_OK;
    // the only time number of interfaces should be zero is if implements
    // interfaces is a NULL pointer
    // If a valid pointer is passed in then the number of interfaces should not be
    // zero.
    if ((implementsInterfaces == NULL && numberInterfaces != 0) ||
        (implementsInterfaces != NULL && numberInterfaces == 0)) {
        return ER_BAD_ARG_4;
    }

    // we only need to register the internalAnnounceHandler once that it is
    // responsible for forwarding each Announce signal to the users AnnounceHandeler
    if (internalAnnounceHandler == NULL) {
        internalAnnounceHandler = new InternalAnnounceHandler(bus);

        const InterfaceDescription* getIface = NULL;
        // check to see if the org.alljoyn.About interface is already registered with
        // the bus.  If the call to GetInterface returns NULL we know the interface
        // is not found on the bus and it is created.
        getIface = bus.GetInterface("org.alljoyn.About");
        if (!getIface) {
            InterfaceDescription* createIface = NULL;
            status = bus.CreateInterface("org.alljoyn.About", createIface, false);
            if (status != ER_OK) {
                return status;
            }
            if (!createIface) {
                return ER_BUS_CANNOT_ADD_INTERFACE;
            }

            status = createIface->AddMethod("GetAboutData", "s", "a{sv}", "languageTag,aboutData");
            if (status != ER_OK) {
                return status;
            }
            status = createIface->AddMethod("GetObjectDescription", NULL, "a(oas)", "Control");
            if (status != ER_OK) {
                return status;
            }
            status = createIface->AddProperty("Version", "q", PROP_ACCESS_READ);
            if (status != ER_OK) {
                return status;
            }
            status = createIface->AddSignal("Announce", "qqa(oas)a{sv}", "version,port,objectDescription,aboutData", 0);
            if (status != ER_OK) {
                return status;
            }

            createIface->Activate();
            // Now that the interface has been activated get the Announce signal member
            internalAnnounceHandler->announceSignalMember = createIface->GetMember("Announce");
        } else {
            // Get the Announce signal member
            internalAnnounceHandler->announceSignalMember = getIface->GetMember("Announce");
        }

        status = bus.RegisterSignalHandler(internalAnnounceHandler,
                                           static_cast<MessageReceiver::SignalHandler>(&InternalAnnounceHandler::AnnounceSignalHandler),
                                           internalAnnounceHandler->announceSignalMember,
                                           0);
        if (status != ER_OK) {
            return status;
        }
        QCC_DbgPrintf(("AnnouncementRegistrar::%s Registered Signal Handler", __FUNCTION__));
    }

    // Add the user handler to the internal AnnounceHandler.
    status = internalAnnounceHandler->AddHandler(handler, implementsInterfaces, numberInterfaces);
    if (ER_OK != status) {
        return status;
    }

    QCC_DbgPrintf(("AnnouncementRegistrar::%s result %s", __FUNCTION__, QCC_StatusText(status)));
    return status;
}

QStatus AnnouncementRegistrar::RegisterAnnounceHandler(ajn::BusAttachment& bus, AnnounceHandler& handler) {
    QCC_LogError(ER_OK, ("Using deprecated version of RegisterAnnounceHandler. Network performance may be reduced."));
    return RegisterAnnounceHandler(bus, handler, NULL, 0);
}

QStatus AnnouncementRegistrar::UnRegisterAnnounceHandler(ajn::BusAttachment& bus, AnnounceHandler& handler, const char** implementsInterfaces, size_t numberInterfaces) {
    QCC_DbgTrace(("AnnouncementRegistrar::%s", __FUNCTION__));
    QStatus status = ER_OK;
    if (internalAnnounceHandler != NULL) {
        status = internalAnnounceHandler->RemoveHandler(handler, implementsInterfaces, numberInterfaces);
        if (status != ER_OK) {
            return status;
        }

        if (internalAnnounceHandler->announceMap.empty()) {
            status = bus.UnregisterSignalHandler(internalAnnounceHandler, static_cast<MessageReceiver::SignalHandler>(&InternalAnnounceHandler::AnnounceSignalHandler),
                                                 internalAnnounceHandler->announceSignalMember, NULL);
            if (status != ER_OK) {
                // if we fail to unregister the announce signal handler log the error
                // but continue to delete the internalAnnounceHandler.
                QCC_LogError(status, ("Failed to unregister the announce signal handler"));
            }
            QCC_DbgPrintf(("AnnouncementRegistrar::%s Internal signalHandler is empty. Free memory.", __FUNCTION__));
            delete internalAnnounceHandler;
            internalAnnounceHandler = NULL;
        }
    }

    QCC_DbgPrintf(("AnnouncementRegistrar::%s result %s", __FUNCTION__, QCC_StatusText(status)));
    return ER_OK;
}

QStatus AnnouncementRegistrar::UnRegisterAnnounceHandler(ajn::BusAttachment& bus, AnnounceHandler& handler) {
    return UnRegisterAnnounceHandler(bus, handler, NULL, 0);
}

QStatus AnnouncementRegistrar::UnRegisterAllAnnounceHandlers(ajn::BusAttachment& bus) {
    QCC_DbgTrace(("AnnouncementRegistrar::%s", __FUNCTION__));
    if (internalAnnounceHandler == NULL) {
        return ER_OK;
    }

    QStatus status = bus.UnregisterSignalHandler(internalAnnounceHandler, static_cast<MessageReceiver::SignalHandler>(&InternalAnnounceHandler::AnnounceSignalHandler),
                                                 internalAnnounceHandler->announceSignalMember, NULL);
    if (status != ER_OK) {
        // if we fail to unregister the announce signal handler log the error
        // but continue to delete the internalAnnounceHandler.
        QCC_LogError(status, ("Failed to unregister the announce signal handler"));
    }
    internalAnnounceHandler->RemoveAllHandlers();
    delete internalAnnounceHandler;
    internalAnnounceHandler = NULL;
    QCC_DbgPrintf(("AnnouncementRegistrar::%s Unregistered All Announce Handlers", __FUNCTION__));
    return ER_OK;
}
