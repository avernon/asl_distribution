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

/**
 * Per-module definition of the current module for debug logging.  Must be defined
 * prior to first inclusion of aj_debug.h.
 * The corresponding flag dbgAJSVCAPP is defined below statically.
 */
#define AJ_MODULE AJSVCAPP
#include <aj_debug.h>

#include <alljoyn.h>
#include "AppHandlers.h"

#include <alljoyn/services_common/ServicesCommon.h>
#include <alljoyn/services_common/ServicesHandlers.h>
#include <alljoyn/services_common/PropertyStore.h>
#ifdef CONFIG_SERVICE
    #include "ConfigSample.h"
#endif
#ifdef ONBOARDING_SERVICE
    #include "OnboardingSample.h"
    #include <alljoyn/onboarding/OnboardingManager.h>
#endif
#ifdef NOTIFICATION_SERVICE_PRODUCER
    #include "NotificationProducerSample.h"
#endif
#ifdef CONTROLPANEL_SERVICE
    #include "ControlPanelSample.h"
#endif
#ifdef NOTIFICATION_SERVICE_CONSUMER
    #include "NotificationConsumerSample.h"
#endif

#include <aj_config.h>
#include <aj_link_timeout.h>

#ifndef NDEBUG
extern AJ_EXPORT uint8_t dbgAJSVCAPP;
#endif

/*
 * Define timeout/pause values. Values are in milli seconds.
 * The following may be tuned according to platform requirements such as battery usage.
 */
#define AJAPP_CONNECT_TIMEOUT     AJ_CONNECT_TIMEOUT
#define AJAPP_CONNECT_PAUSE       (1000 * 2) // Override AJ_CONNECT_PAUSE to be more responsive
#define AJAPP_SLEEP_TIME          (1000 * 2) // A little pause to let things settle

uint16_t servicePort = 0;

typedef enum {
    INIT_START = 0,
    INIT_SERVICES = INIT_START,
    INIT_SERVICES_PORT,
    INIT_ADVERTISE_NAME,
    INIT_ABOUT,
    INIT_CHECK_ANNOUNCE,
    INIT_FINISHED = INIT_CHECK_ANNOUNCE
} enum_init_state_t;

static const uint8_t MAX_INIT_RETRIES = 5;
static uint8_t init_retries = 0;

static uint32_t PasswordCallback(uint8_t* buffer, uint32_t bufLen)
{
    AJ_Status status = AJ_OK;
#ifdef CONFIG_SERVICE
    const char* hexPassword = AJSVC_PropertyStore_GetValue(AJSVC_PROPERTY_STORE_PASSCODE);
#else
    const char* hexPassword = "303030303030";
#endif
    size_t hexPasswordLen;
    uint32_t len = 0;

    if (hexPassword == NULL) {
        AJ_AlwaysPrintf(("Password is NULL!\n"));
        return len;
    }
    AJ_AlwaysPrintf(("Configured password=%s\n", hexPassword));
    hexPasswordLen = strlen(hexPassword);
    len = hexPasswordLen / 2;
    status = AJ_HexToRaw(hexPassword, hexPasswordLen, buffer, bufLen);
    if (status == AJ_ERR_RESOURCES) {
        len = 0;
    }

    return len;
}

AJ_Status AJServices_Init(uint16_t aboutServicePort, AJ_Object* appObjects, AJ_Object* proxyObjects, const char* deviceManufactureName, const char* deviceProductName)
{
    AJ_Status status = AJ_OK;

    servicePort = aboutServicePort;
#ifdef CONFIG_SERVICE
    status = Config_Init();
    if (status != AJ_OK) {
        goto Exit;
    }
#endif
#ifdef ONBOARDING_SERVICE
    status = Onboarding_Init(deviceManufactureName, deviceProductName);
    if (status != AJ_OK) {
        goto Exit;
    }
#endif
#ifdef NOTIFICATION_SERVICE_PRODUCER
    status = NotificationProducer_Init();
    if (status != AJ_OK) {
        goto Exit;
    }
#endif
#ifdef NOTIFICATION_SERVICE_CONSUMER
    status = NotificationConsumer_Init(proxyObjects);
    if (status != AJ_OK) {
        goto Exit;
    }
#endif
#ifdef CONTROLPANEL_SERVICE
    status = Controlee_Init();
    if (status != AJ_OK) {
        goto Exit;
    }
#endif

Exit:

    return status;
}

uint8_t AJRouter_Connect(AJ_BusAttachment* busAttachment, const char* routerName)
{
    AJ_Status status;
    const char* busUniqueName;

    while (TRUE) {
#ifdef ONBOARDING_SERVICE
        status = AJOBS_EstablishWiFi();
        if (status != AJ_OK) {
            AJ_AlwaysPrintf(("Failed to establish WiFi connectivity with status=%s\n", AJ_StatusText(status)));
            AJ_Sleep(AJAPP_CONNECT_PAUSE);
            return FALSE;
        }
#endif
        AJ_AlwaysPrintf(("Attempting to connect to bus '%s'\n", routerName));
        status = AJ_FindBusAndConnect(busAttachment, routerName, AJAPP_CONNECT_TIMEOUT);
        if (status != AJ_OK) {
            AJ_AlwaysPrintf(("Failed attempt to connect to bus, sleeping for %d seconds\n", AJAPP_CONNECT_PAUSE / 1000));
            AJ_Sleep(AJAPP_CONNECT_PAUSE);
#ifdef ONBOARDING_SERVICE
            if (status == AJ_ERR_DHCP) {
                AJOBS_SwitchToRetry();
            }
#endif
            continue;
        }
        busUniqueName = AJ_GetUniqueName(busAttachment);
        if (busUniqueName == NULL) {
            AJ_AlwaysPrintf(("Failed to GetUniqueName() from newly connected bus, retrying\n"));
            continue;
        }
        AJ_AlwaysPrintf(("Connected to router with BusUniqueName=%s\n", busUniqueName));
        break;
    }

    /* Setup password based authentication listener for secured peer to peer connections */
    AJ_BusSetPasswordCallback(busAttachment, PasswordCallback);

    /* Configure timeout for the link to the Router bus */
    AJ_SetBusLinkTimeout(busAttachment, 60);     // 60 seconds

    return TRUE;
}

static enum_init_state_t currentServicesInitializationState = INIT_START;
static enum_init_state_t nextServicesInitializationState = INIT_START;

AJ_Status AJApp_ConnectedHandler(AJ_BusAttachment* busAttachment)
{
    AJ_Status status = AJ_OK;

    if (AJ_GetUniqueName(busAttachment)) {
        if (currentServicesInitializationState == nextServicesInitializationState) {
            switch (currentServicesInitializationState) {
            case INIT_SERVICES:
                status = AJSVC_ConnectedHandler(busAttachment);
                if (status != AJ_OK) {
                    goto ErrorExit;
                }
                currentServicesInitializationState = nextServicesInitializationState = INIT_SERVICES_PORT;
                break;

            case INIT_SERVICES_PORT:
                status = AJ_BusBindSessionPort(busAttachment, servicePort, NULL, 0);
                if (status != AJ_OK) {
                    goto ErrorExit;
                }
                nextServicesInitializationState = INIT_ADVERTISE_NAME;
                break;

            case INIT_ADVERTISE_NAME:
                status = AJ_BusAdvertiseName(busAttachment, AJ_GetUniqueName(busAttachment), AJ_TRANSPORT_ANY, AJ_BUS_START_ADVERTISING, 0);
                if (status != AJ_OK) {
                    goto ErrorExit;
                }
                nextServicesInitializationState = INIT_ABOUT;
                break;

            case INIT_ABOUT:
                status = AJ_AboutInit(busAttachment, servicePort);
                if (status != AJ_OK) {
                    goto ErrorExit;
                }
                currentServicesInitializationState = nextServicesInitializationState = INIT_CHECK_ANNOUNCE;
                break;

            case INIT_CHECK_ANNOUNCE:
                status = AJ_AboutAnnounce(busAttachment);
                if (status != AJ_OK) {
                    goto ErrorExit;
                }
                break;

            default:
                break;
            }
        }
    }
    return status;

ErrorExit:

    AJ_ErrPrintf(("Application ConnectedHandler returned an error %s\n", (AJ_StatusText(status))));
    if (status == AJ_ERR_RESOURCES) {
        init_retries++;
        if (init_retries > MAX_INIT_RETRIES) {
            status = AJ_ERR_READ; // Force disconnect
        } else {
            AJ_ErrPrintf(("Application ConnectedHandler attempt %u of %u\n", init_retries, MAX_INIT_RETRIES));
            AJ_Sleep(AJAPP_SLEEP_TIME);
        }
    }
    return status;
}

AJSVC_ServiceStatus AJApp_MessageProcessor(AJ_BusAttachment* busAttachment, AJ_Message* msg, AJ_Status* status)
{
    AJSVC_ServiceStatus serviceStatus = AJSVC_SERVICE_STATUS_HANDLED;

    if (msg->msgId == AJ_METHOD_ACCEPT_SESSION) {    // Process all incoming request to join a session and pass request for acceptance by all services
        uint16_t port;
        char* joiner;
        uint32_t sessionId = 0;
        AJ_UnmarshalArgs(msg, "qus", &port, &sessionId, &joiner);
        uint8_t session_accepted = FALSE;

        session_accepted |= (port == servicePort);
        session_accepted |= AJSVC_CheckSessionAccepted(port, sessionId, joiner);

        *status = AJ_BusReplyAcceptSession(msg, session_accepted);
        AJ_AlwaysPrintf(("%s session session_id=%u joiner=%s for port %u\n", (session_accepted ? "Accepted" : "Rejected"), sessionId, joiner, port));
    } else {
        switch (currentServicesInitializationState) {
        case INIT_SERVICES_PORT:
            if (msg->msgId == AJ_REPLY_ID(AJ_METHOD_BIND_SESSION_PORT)) {
                currentServicesInitializationState = nextServicesInitializationState;
            }
            break;

        case INIT_ADVERTISE_NAME:
            if (msg->msgId == AJ_REPLY_ID(AJ_METHOD_ADVERTISE_NAME)) {
                currentServicesInitializationState = nextServicesInitializationState;
            }
            break;

        default:
            serviceStatus = AJSVC_MessageProcessorAndDispatcher(busAttachment, msg, status);
            break;
        }
    }

    return serviceStatus;
}

void AJApp_DoWork(AJ_BusAttachment* busAttachment)
{
#ifdef CONFIG_SERVICE
    Config_DoWork(busAttachment);
#endif
#ifdef ONBOARDING_SERVICE
    Onboarding_DoWork(busAttachment);
#endif
#ifdef NOTIFICATION_SERVICE_PRODUCER
    NotificationProducer_DoWork(busAttachment);
#endif
#ifdef NOTIFICATION_SERVICE_CONSUMER
    NotificationConsumer_DoWork(busAttachment);
#endif
#ifdef CONTROLPANEL_SERVICE
    Controlee_DoWork(busAttachment);
#endif
}

AJ_Status AJApp_DisconnectHandler(AJ_BusAttachment* busAttachment, uint8_t restart)
{
    AJ_Status status = AJ_OK;

    if (restart) {
        AJ_BusAdvertiseName(busAttachment, AJ_GetUniqueName(busAttachment), AJ_TRANSPORT_ANY, AJ_BUS_STOP_ADVERTISING, 0);
        AJ_BusUnbindSession(busAttachment, servicePort);
    }

    AJ_AboutSetShouldAnnounce();
    currentServicesInitializationState = nextServicesInitializationState = INIT_START;
    init_retries = 0;

    status = AJSVC_DisconnectHandler(busAttachment);
    return status;
}

uint8_t AJRouter_Disconnect(AJ_BusAttachment* busAttachment, uint8_t disconnectWiFi)
{
    AJ_AlwaysPrintf(("AllJoyn disconnect\n"));
    AJ_Sleep(AJAPP_SLEEP_TIME); // Sleep a little to let any pending requests to router to be sent
    AJ_Disconnect(busAttachment);
#ifdef ONBOARDING_SERVICE
    if (disconnectWiFi) {
        AJOBS_DisconnectWiFi();
    }
#endif
    AJ_Sleep(AJAPP_SLEEP_TIME); // Sleep a little while before trying to reconnect

    return TRUE;
}
