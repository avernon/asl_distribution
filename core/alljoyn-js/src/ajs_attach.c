/**
 * @file
 */
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

#include "ajs.h"
#include "ajs_services.h"
#include <ajtcl/aj_link_timeout.h>

static const char* sessionLostMatchRule = "type='signal',interface='org.alljoyn.Bus',member='SessionLostWithReason'";

static const char busNode[] = "org.alljoyn.BusNode";

#define ONBOARDING_PORT  (('O' << 8) | 'B')
#define CONNECT_TO       (1000 * 60 * 10)
#define CONNECT_PAUSE    (1000 * 2)
#define DISCONNECT_PAUSE (1000 * 2)

AJ_Status AJS_DetachAllJoyn(AJ_BusAttachment* aj, AJ_Status reason)
{
    AJ_Status status;
    uint8_t disconnectWiFi = (reason == AJ_ERR_RESTART);

    AJSVC_DisconnectHandler(aj);
    status = AJSVC_RoutingNodeDisconnect(aj, disconnectWiFi, DISCONNECT_PAUSE, DISCONNECT_PAUSE, NULL);
    if (disconnectWiFi && (status == AJ_ERR_RESTART_APP)) {
        AJ_Reboot();
    }
    AJ_InfoPrintf(("Detached from AllJoyn\n"));
    return AJ_OK;
}

#define MSG_TO   (2 * 1000)  /* Milliseconds */
#define LINK_TO  120         /* Seconds */

#ifdef ONBOARDING_SERVICE
/*
 * TODO - this string need to be provisioned
 */
static const char softAPSSID[] = "AJ_AllJoyn.js";

static AJOBS_Settings obSettings = AJOBS_DEFAULT_SETTINGS;
#endif
AJ_Status AJS_AttachAllJoyn(AJ_BusAttachment* aj)
{
    AJ_Status status;
    uint8_t isConnected = FALSE;
    uint32_t linkTO = LINK_TO;
    size_t sapSz;

    /*
     * Initialize the onboarding service
     */
#ifdef ONBOARDING_SERVICE
    sapSz = min(sizeof(obSettings.AJOBS_SoftAPSSID), sizeof(softAPSSID));
    memcpy((char*)obSettings.AJOBS_SoftAPSSID, softAPSSID, sapSz);
    status = AJOBS_Start(&obSettings);
    if (status != AJ_OK) {
        goto Exit;
    }
#endif
    AJ_InfoPrintf(("Attempting to attach to AllJoyn\n"));
    while (!isConnected) {
        status = AJSVC_RoutingNodeConnect(aj, busNode, CONNECT_TO, CONNECT_PAUSE, linkTO, &isConnected);
        if (status != AJ_ERR_TIMEOUT) {
            break;
        }
    }
    if (isConnected) {
        status = AJS_ServicesInit(aj);
        if (status != AJ_OK) {
            AJ_ErrPrintf(("Failed to initialize services"));
        }
    }
#ifdef ONBOARDING_SERVICE
    if (isConnected && (AJOBS_GetState() != AJOBS_STATE_CONFIGURED_VALIDATED)) {
        /*
         * Kick of onboarding
         */
        status = AJ_BusBindSessionPort(aj, ONBOARDING_PORT, NULL, 0);
        /*
         * Allow onboarding service to run its course
         */
        while (status == AJ_OK) {
            AJ_Message msg;
            status = AJ_UnmarshalMsg(aj, &msg, MSG_TO);
            if (status == AJ_ERR_NO_MATCH) {
                /*
                 * Discard unknown messages
                 */
                status = AJ_CloseMsg(&msg);
                continue;
            }
            if (status == AJ_ERR_TIMEOUT) {
                /*
                 * Check the link is still up
                 */
                status = AJ_BusLinkStateProc(aj);
                if (status == AJ_OK) {
                    continue;
                }
            }
            if (status != AJ_OK) {
                break;
            }
            switch (msg.msgId) {
            case AJ_REPLY_ID(AJ_METHOD_BIND_SESSION_PORT):
                AJ_AboutInit(aj, ONBOARDING_PORT);
                break;

            case AJ_METHOD_ACCEPT_SESSION:
                /*
                 * TODO - check that the port number is correct
                 */
                status = AJ_BusReplyAcceptSession(&msg, TRUE);
                if (status == AJ_OK) {
                    status = AJOBS_ConnectedHandler(aj);
                }
                break;

            default:
                /*
                 * Let the service message handlers have first dibs on the message
                 */
                status = AJS_ServicesMsgHandler(&msg);
                if (status == AJ_ERR_NO_MATCH) {
                    /*
                     * Pass the unhandled message to the standard bus handler
                     */
                    status = AJ_BusHandleBusMessage(&msg);
                    if (status == AJ_ERR_NO_MATCH) {
                        AJ_ErrPrintf(("Discarding unhandled message\n"));
                        status = AJ_OK;
                    }
                }
                break;
            }
            /*
             * Let the link monitor know we are receiving messages
             */
            AJ_NotifyLinkActive();
            /*
             * Free resources used by the message
             */
            AJ_CloseMsg(&msg);
            if (AJOBS_GetState() == AJOBS_STATE_CONFIGURED_VALIDATED) {
                AJ_InfoPrintf(("Onboarding completed\n"));
                break;
            }
            AJ_InfoPrintf(("Onboarding continuing\n"));
        }
        /*
         * If we got an error during onboarding we should restart
         */
        if (status != AJ_OK) {
            status = AJ_ERR_RESTART;
        }
    }
#else
    /*
     * Let the link monitor know we are receiving messages
     */
    AJ_NotifyLinkActive();
#endif
    /*
     * If all went well let the services know we are connected
     */
    if (isConnected && (status == AJ_OK)) {
        /*
         * Add match rules to subscribe to session related signals
         */
        status = AJ_BusSetSignalRuleFlags(aj, sessionLostMatchRule, AJ_BUS_SIGNAL_ALLOW, AJ_FLAG_NO_REPLY_EXPECTED);
        if (status == AJ_OK) {
            status = AJSVC_ConnectedHandler(aj);
        }
    }

Exit:
    return status;
}
