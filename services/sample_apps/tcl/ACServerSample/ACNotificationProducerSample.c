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
 * The corresponding flag dbgAJSVCAPP is defined in the containing sample app.
 */
#define AJ_MODULE AJSVCAPP
#include <aj_debug.h>

#include <alljoyn.h>
#include <NotificationProducerSample.h>
#include <alljoyn/notification/NotificationProducer.h>

#include "ControlPanelProvided.h"

#ifndef NDEBUG
extern AJ_EXPORT uint8_t dbgAJSVCAPP;
#endif

#define NUM_CUSTOMS 0
#define NUM_TEXTS   1
#define NUM_RICH_AUDIO 0

/**
 * Static non consts - sample application specirfic
 */
const static char* langEng  = "en";
const static char* helloEng = "Hello AJL World";
static AJNS_DictionaryEntry textToSend[NUM_TEXTS];
static AJNS_NotificationContent notificationContent;

/**
 * Initial the Notifications that will be used during this sample app
 */
static void InitNotificationContent()
{
    notificationContent.numCustomAttributes = NUM_CUSTOMS;

    notificationContent.numTexts = NUM_TEXTS;
    textToSend[0].key   = langEng;
    textToSend[0].value = helloEng;
    notificationContent.texts = textToSend;

    notificationContent.numAudioUrls = NUM_RICH_AUDIO;

}

/**
 * Initialize service
 */
AJ_Status NotificationProducer_Init()
{
    InitNotificationContent();
    return AJ_OK;
}

/**
 * Meant to simulate scenario where sometimes Notifications are set when
 * Send Notification is called and sometimes not.
 */
void NotificationProducer_DoWork(AJ_BusAttachment* busAttachment)
{
    if (isThereANotificationToSend() > 0) {
        notificationContent.numTexts = NUM_TEXTS;
        textToSend[0].key   = langEng;
        textToSend[0].value = getNotificationString();

        AJ_AlwaysPrintf(("About to send Notification ==> %s \n", textToSend[0].value));
        AJNS_Producer_SendNotification(busAttachment, &notificationContent, AJNS_NOTIFICATION_MESSAGE_TYPE_INFO, 20000, NULL);
    }
}

AJ_Status NotificationProducer_Finish(AJ_BusAttachment* busAttachment)
{
    return AJ_OK;
}
