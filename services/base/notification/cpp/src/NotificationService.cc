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

#ifdef _WIN32
/* Disable deprecation warnings */
#pragma warning(disable: 4996)
#endif

#include <algorithm>
#include <alljoyn/notification/NotificationSender.h>
#include <alljoyn/notification/NotificationService.h>
#include "NotificationConstants.h"
#include "Transport.h"
#include "NotificationProducerReceiver.h"
#include <alljoyn/notification/LogModule.h>

using namespace ajn;
using namespace services;
using namespace qcc;
using namespace nsConsts;

NotificationService* NotificationService::s_Instance(NULL);
uint16_t const NotificationService::NOTIFICATION_SERVICE_VERSION = 2;

NotificationService* NotificationService::getInstance()
{
    if (!s_Instance) {
        s_Instance = new NotificationService();
    }
    return s_Instance;
}

NotificationService::NotificationService()
{
}

NotificationService::~NotificationService()
{

}

uint16_t NotificationService::getVersion()
{
    return NOTIFICATION_SERVICE_VERSION;
}

NotificationSender* NotificationService::initSend(BusAttachment* bus, AboutData* store)
{
    QCC_DbgTrace(("NotificationService::initSend"));

    if (!bus) {
        QCC_DbgHLPrintf(("BusAttachment cannot be NULL"));
        return NULL;
    }

    if (!store) {
        QCC_DbgHLPrintf(("PropertyStore cannot be NULL"));
        return NULL;
    }

    Transport* transport = Transport::getInstance();
    if (transport->startSenderTransport(bus) != ER_OK) {
        return NULL;
    }

    MsgArg configArgs;
    MsgArg* configEntries;
    size_t configNum = 0;
    QStatus status;

    if ((status = store->GetAboutData(&configArgs))) {
        QCC_LogError(status, ("Error reading all in configuration data"));
        return NULL;
    }

    if ((status = configArgs.Get(AJPARAM_ARR_DICT_STR_VAR.c_str(), &configNum, &configEntries))) {
        QCC_LogError(status, ("Error reading in configuration data"));
        return NULL;
    }

    MsgArg appIdArg;
    for (size_t i = 0; i < configNum; i++) {
        char* keyChar;
        String key;
        MsgArg* variant;

        status = configEntries[i].Get(AJPARAM_DICT_STR_VAR.c_str(), &keyChar, &variant);
        if (status != ER_OK) {
            QCC_LogError(status, ("Error reading in configuration data"));
            return NULL;
        }

        key = keyChar;

        if (key.compare("AppId") == 0) {
            appIdArg = *variant;
        }
    }

    if (status != ER_OK) {
        QCC_LogError(status, ("Something went wrong unmarshalling the propertystore."));
        return NULL;
    }

    if (appIdArg.typeId != ALLJOYN_BYTE_ARRAY) {
        QCC_DbgHLPrintf(("ApplicationId argument is not correct type."));
        return NULL;
    }

    transport->getNotificationProducerReceiver()->SetAppIdArg(appIdArg);

    return new NotificationSender(store);
}

NotificationSender* NotificationService::initSend(BusAttachment* bus, PropertyStore* store)
{
    QCC_DbgTrace(("NotificationService::initSend"));

    if (!bus) {
        QCC_DbgHLPrintf(("BusAttachment cannot be NULL"));
        return NULL;
    }

    if (!store) {
        QCC_DbgHLPrintf(("PropertyStore cannot be NULL"));
        return NULL;
    }

    Transport* transport = Transport::getInstance();
    if (transport->startSenderTransport(bus) != ER_OK) {
        return NULL;
    }

    MsgArg configArgs[1];
    MsgArg* configEntries;
    size_t configNum = 0;
    QStatus status;

    if ((status = store->ReadAll(0, PropertyStore::READ, configArgs[0]))) {
        QCC_LogError(status, ("Error reading all in configuration data"));
        return NULL;
    }

    if ((status = configArgs[0].Get(AJPARAM_ARR_DICT_STR_VAR.c_str(), &configNum, &configEntries))) {
        QCC_LogError(status, ("Error reading in configuration data"));
        return NULL;
    }

    MsgArg appIdArg;
    for (size_t i = 0; i < configNum; i++) {
        char* keyChar;
        String key;
        MsgArg* variant;

        status = configEntries[i].Get(AJPARAM_DICT_STR_VAR.c_str(), &keyChar, &variant);
        if (status != ER_OK) {
            QCC_LogError(status, ("Error reading in configuration data"));
            return NULL;
        }

        key = keyChar;

        if (key.compare("AppId") == 0) {
            appIdArg = *variant;
        }
    }

    if (status != ER_OK) {
        QCC_LogError(status, ("Something went wrong unmarshalling the propertystore."));
        return NULL;
    }

    if (appIdArg.typeId != ALLJOYN_BYTE_ARRAY) {
        QCC_DbgHLPrintf(("ApplicationId argument is not correct type."));
        return NULL;
    }

    transport->getNotificationProducerReceiver()->SetAppIdArg(appIdArg);

    return new NotificationSender(store);
}

QStatus NotificationService::initReceive(ajn::BusAttachment* bus, NotificationReceiver* notificationReceiver)
{
    if (!bus) {
        QCC_LogError(ER_BAD_ARG_1, ("BusAttachment cannot be NULL."));
        return ER_BAD_ARG_1;
    }

    if (!notificationReceiver) {
        QCC_LogError(ER_BAD_ARG_2, ("Could not set NotificationReceiver to null pointer"));
        return ER_BAD_ARG_2;
    }

    QCC_DbgPrintf(("Init receive"));

    Transport* transport = Transport::getInstance();
    transport->setNotificationReceiver(notificationReceiver);

    QStatus status;
    if ((status = transport->startReceiverTransport(bus)) != ER_OK) {
        transport->setNotificationReceiver(0);
    }

    return status;
}

void NotificationService::shutdownSender()
{
    QCC_DbgTrace(("Stop Sender"));
    Transport* transport = Transport::getInstance();
    transport->cleanupSenderTransport();
}

void NotificationService::shutdownReceiver()
{
    QCC_DbgTrace(("Stop Receiver"));
    Transport* transport = Transport::getInstance();
    transport->cleanupReceiverTransport();
}

void NotificationService::shutdown()
{
    QCC_DbgTrace(("Shutdown"));
    Transport* transport = Transport::getInstance();
    transport->cleanup();

    s_Instance = 0;
    delete this;
}


BusAttachment* NotificationService::getBusAttachment()
{
    QCC_DbgTrace(("In Get BusAttachment"));
    Transport* transport = Transport::getInstance();
    return transport->getBusAttachment();
}
