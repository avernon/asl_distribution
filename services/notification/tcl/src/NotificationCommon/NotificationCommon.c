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
 * The corresponding flag dbgAJNS is defined in ServicesCommon.h and implemented
 * in ServicesCommon.c.
 */
#define AJ_MODULE AJNS
#include <aj_debug.h>

#include <alljoyn/notification/NotificationCommon.h>
#include <alljoyn/services_common/ServicesCommon.h>

const char AJNS_NotificationInterfaceName[]   = "org.alljoyn.Notification";
const char AJNS_NotificationSignalName[]      = "!notify >q >i >q >s >s >ay >s >a{iv} >a{ss} >a(ss)";
const char AJNS_NotificationPropertyVersion[] = "@Version>q";

const uint16_t AJNS_NotificationVersion = 2;

const uint16_t AJNS_NOTIFICATION_TTL_MIN   = 30;
const uint16_t AJNS_NOTIFICATION_TTL_MAX   = 43200;

const char* AJNS_NotificationInterface[] = {
    AJNS_NotificationInterfaceName,               /**< The first entry is the interface name. */
    AJNS_NotificationSignalName,                  /**< Signal at index 0 - See above for signature */
    AJNS_NotificationPropertyVersion,             /**< Notification property version */
    NULL
};

/**
 * A NULL terminated collection of all interfaces.
 */
const AJ_InterfaceDescription AJNS_NotificationInterfaces[] = {
    AJ_PropertiesIface,
    AJNS_NotificationInterface,
    NULL
};

const uint16_t AJNS_NotificationDismisserVersion = 1;

// TODO: Change NotificationDismisserObjectPath to be 'const char []' when AJTCL adds the "DON'T COLLAPSE" flag
#define NOTIFICATION_DISMISSER_OBJECT_PATH_PREFIX "/notificationDismisser"
#define NOTIFICATION_DISMISSER_OBJECT_PATH_PREFIX_LENGTH 22
#define NOTIFICATION_DISMISSER_OBJECT_PATH_LENGTH (NOTIFICATION_DISMISSER_OBJECT_PATH_PREFIX_LENGTH + 1 + 2 * UUID_LENGTH + 1 + 10 + 1) // Prefix of NOTIFICATION_DISMISSER_OBJECT_PATH_PREFIX_LENGTH + '/' + AppId in 32 Hex chars + '/' + MsgId in 10 Ascii chars
char AJNS_NotificationDismisserObjectPath[NOTIFICATION_DISMISSER_OBJECT_PATH_LENGTH] = NOTIFICATION_DISMISSER_OBJECT_PATH_PREFIX; // /012345678901234567890123456789012/012345678";

const char* const AJNS_NotificationDismisserInterface[] = {
    "org.alljoyn.Notification.Dismisser",
    "!Dismiss >i >ay",
    "@Version>q",
    NULL
};

/**
 * A NULL terminated collection of all interfaces.
 */
const AJ_InterfaceDescription AJNS_NotificationDismisserInterfaces[] = {
    AJ_PropertiesIface,
    AJNS_NotificationDismisserInterface,
    NULL
};

AJ_Status AJNS_SendDismissSignal(AJ_BusAttachment* busAttachment, int32_t msgId, const char* appId)
{
    AJ_Status status;
    AJ_Message msg;

    AJ_InfoPrintf(("In SendDismiss\n"));

    if (appId == 0) {
        AJ_ErrPrintf(("AppId can not be NULL\n"));
        return AJ_ERR_DISALLOWED;
    }

    // TODO: Remove setting of temporary Dismisser ObjectPath when AJTCL adds the "DON'T COLLAPSE" flag
    AJNS_NotificationDismisserObjectPath[snprintf(AJNS_NotificationDismisserObjectPath, NOTIFICATION_DISMISSER_OBJECT_PATH_LENGTH, "%s/%s/%d", AJNS_NotificationDismisserObjectPath, appId, msgId)] = '\0';

    status = AJ_MarshalSignal(busAttachment, &msg, NOTIFICATION_DISMISSER_DISMISS_EMITTER, NULL, 0, ALLJOYN_FLAG_SESSIONLESS, AJNS_NOTIFICATION_TTL_MAX); // TODO: Add the "DON'T COLLAPSE" flag
    if (status != AJ_OK) {
        AJ_ErrPrintf(("Could not Marshal Signal\n"));
        return status;
    }

    status = AJ_MarshalArgs(&msg, "i", msgId);
    if (status != AJ_OK) {
        goto ErrorExit;
    }
    status = AJSVC_MarshalAppId(&msg, appId);
    if (status != AJ_OK) {
        goto ErrorExit;
    }
    status = AJ_DeliverMsg(&msg);
    if (status != AJ_OK) {
        goto ErrorExit;
    }
    status = AJ_CloseMsg(&msg);
    if (status != AJ_OK) {
        goto ErrorExit;
    }

    // TODO: Remove resetting of temporary Dismisser ObjectPath when AJTCL adds the "DON'T COLLAPSE" flag
    AJNS_NotificationDismisserObjectPath[NOTIFICATION_DISMISSER_OBJECT_PATH_PREFIX_LENGTH] = '\0';
    return status;

ErrorExit:

    AJ_ErrPrintf(("Could not Deliver Message\n"));
    return status;
}

const uint16_t AJNS_NotificationProducerPort = 1010;
const char AJNS_NotificationProducerObjectPath[] = "/notificationProducer";

const char* const AJNS_NotificationProducerInterface[] = {
    "org.alljoyn.Notification.Producer",
    "?Dismiss <i",
    "@Version>q",
    NULL
};

const uint16_t AJNS_NotificationProducerVersion = 1;

const AJ_InterfaceDescription AJNS_NotificationProducerInterfaces[] = {
    AJ_PropertiesIface,
    AJNS_NotificationProducerInterface,
    AJNS_NotificationDismisserInterface,
    NULL
};

