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

#if defined (QCC_OS_GROUP_WINDOWS)
#define _CRT_RAND_S
#endif

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
/* Disable deprecation warnings */
#pragma warning(disable: 4996)
#endif

#include <alljoyn/notification/NotificationText.h>
#include <alljoyn/notification/RichAudioUrl.h>
#include <alljoyn/Status.h>
#include "NotificationTesterImpl.h"

using namespace ajn;
using namespace services;
using namespace qcc;

#include <qcc/Debug.h>

static char const* const QCC_MODULE = "ServerSample";

NotificationTesterImpl::NotificationTesterImpl() {
    notifProdEnabled = true;
    notifInterval = 30000;
    notifIntervalOffset = 2000;
    notifRateType = RATE_RANDOM;
    notifRatePriority = 0;
    notifRatePriorityType = PRIORITY_FIXED;
    notifTTL = 30;
    notifCustEnabled = false;
    notifMsgText.assign("Notification Text");
    notifMsgLang.assign("en");

    nextMessageTime = 0;
    intervalOffset = 0;
    prodService = NULL;
    receiver = NULL;
    sender = NULL;
}

NotificationTesterImpl::~NotificationTesterImpl() {
    Cleanup();
}

void NotificationTesterImpl::Cleanup() {
    if (prodService) {
        prodService->shutdown();
        prodService = NULL;
    }
    if (sender) {
        delete sender;
        sender = NULL;
    }
    if (receiver) {
        delete receiver;
        receiver = NULL;
    }
}

void NotificationTesterImpl::LoadConfiguration() {
    const char* value = getenv("AJNS_PRODUCER_ENABLED");
    if (value != NULL) {
        notifProdEnabled = (0 == strcmp(value, "true"));
        std::cout << "Read AJNS_PRODUCER_ENABLED from environment: " << (notifProdEnabled ? "true" : "false") << std::endl;
    }
    value = getenv("AJNS_MSG_INTERVAL");
    if (value != NULL) {
        notifInterval = atoi(value);
        std::cout << "Read AJNS_MSG_INTERVAL from environment: " << notifInterval << "ms" << std::endl;
    }
    value = getenv("AJNS_MSG_INTERVAL_OFFSET");
    if (value != NULL) {
        notifIntervalOffset = (uint32_t)atoi(value);
        std::cout << "Read AJNS_MSG_INTERVAL_OFFSET from environment: " << notifIntervalOffset << "ms" << std::endl;
    }
    value = getenv("AJNS_MSG_INTERVAL_TYPE");
    if (value != NULL) {
        notifRateType = (0 == strcmp("random", value)) ? RATE_RANDOM : RATE_FIXED;
        std::cout << "Read AJNS_MSG_INTERVAL_TYPE from environment: " << (notifRateType == RATE_RANDOM ? "random" : "fixed") << std::endl;
    }
    value = getenv("AJNS_MSG_PRIORITY");
    if (value != NULL) {
        notifRatePriority = atoi(value);
        std::cout << "Read AJNS_MSG_PRIORITY from environment: " << notifRatePriority << std::endl;
    }
    value = getenv("AJNS_MSG_PRIORITY_TYPE");
    if (value != NULL) {
        notifRatePriorityType = (0 == strcmp("random", value)) ? PRIORITY_RANDOM : PRIORITY_FIXED;
        std::cout << "Read AJNS_MSG_PRIORITY_TYPE from environment: " << (notifRatePriorityType == PRIORITY_RANDOM ? "random" : "fixed") << std::endl;
    }
    value = getenv("AJNS_MSG_TEXT");
    if (value != NULL) {
        notifMsgText = value;
        std::cout << "Read AJNS_MSG_TEXT from environment: " << notifMsgText << std::endl;
    }
    value = getenv("AJNS_MSG_LANG");
    if (value != NULL) {
        notifMsgLang = value;
        std::cout << "Read AJNS_MSG_LANG from environment: " << notifMsgLang << std::endl;
    }
    value = getenv("AJNS_MSG_TTL");
    if (value != NULL) {
        notifTTL = atoi(value);
        std::cout << "Read AJNS_MSG_TTL from environment: " << notifTTL << " secs" << std::endl;
    }
    value = getenv("AJNS_CONSUMER_ENABLED");
    if (value != NULL) {
        notifCustEnabled = (0 == strcmp(value, "true"));
        std::cout << "Read AJNS_CONSUMER_ENABLED from environment: " << (notifCustEnabled ? "true" : "false") << std::endl;
    }
}

bool NotificationTesterImpl::Initialize(ajn::BusAttachment* bus, AboutDataStore* store)
{
    LoadConfiguration();

    std::cout << "---------------------" << std::endl;
    std::cout << "Notification parameters" << std::endl;
    if (notifProdEnabled) {
        std::cout << "Producer:     enabled" << std::endl;
        std::cout << "Interval:     " << notifInterval << " ms" << std::endl;
        std::cout << "Offset:       " << notifIntervalOffset << " ms" << std::endl;
        std::cout << "IntervalType: " << (notifRateType == RATE_RANDOM ? "random" : "fixed") << std::endl;
        std::cout << "Priority:     " << notifRatePriority << std::endl;
        std::cout << "PriorityType: " << ((notifRatePriorityType == PRIORITY_RANDOM) ? "random" : "fixed") << std::endl;
        std::cout << "TTL:          " << notifTTL << std::endl;
        std::cout << "MsgLang:      " << notifMsgLang << std::endl;
        std::cout << "MsgText:      " << notifMsgText << std::endl;
    } else {
        std::cout << "Producer:     disabled" << std::endl;
    }
    if (notifCustEnabled) {
        std::cout << "Consumer:     enabled" << std::endl;
    } else {
        std::cout << "Consumer:     disabled" << std::endl;
    }
    std::cout << "---------------------" << std::endl;

    prodService = NotificationService::getInstance();

    if (notifProdEnabled) {
        sender = prodService->initSend(bus, store);
        if (!sender) {
            std::cout << "Could not initialize Sender - exiting application" << std::endl;
            Cleanup();
            return false;
        }
    }

    if (notifCustEnabled) {
        receiver = new NotificationReceiverImpl();
        if (prodService->initReceive(bus, receiver) != ER_OK) {
            std::cout << "Could not initialize receiver." << std::endl;
            Cleanup();
            return false;
        }
    }
    return true;
}

// Generate a "good enough" random number for testing purposes. We want the
// distribution to be random and the likelihood of collisions to be very low.
// We can't use rand() as it is being seeded elsewhere based on the current
// time in seconds and since we're potentially running many instances on
// devices with closely synchronized clocks, we could end up with multiple
// devices generating the same random number sequences. On windows, we'll use
// rand_s() and on Linux we'll use /dev/urandom.
uint32_t GetRandomNumber() {
    uint32_t randomNumber;
#if defined (QCC_OS_GROUP_WINDOWS)
    errno_t err = rand_s(&randomNumber);
    if (err != 0) {
        QCC_LogError(ER_FAIL, ("rand_s() returned error: %d", err));
    }
#endif
#if defined (QCC_OS_GROUP_POSIX)
    FILE* f = fopen("/dev/urandom", "r");
    if (f != NULL) {
        uint32_t size = fread(&randomNumber, 1, sizeof(uint32_t), f);
        if (size != sizeof(uint32_t)) {
            QCC_LogError(ER_FAIL, ("Unable to read enough data from /dev/urandom. Wanted: %d; Got: %d", sizeof(uint32_t), size));
        }
        fclose(f);
    } else {
        QCC_LogError(ER_FAIL, ("Unable to open /dev/urandom"));
    }
#endif
    return randomNumber;
}

uint64_t GetTimestamp() {
    uint64_t timestamp;

#if defined (QCC_OS_GROUP_WINDOWS)
    static const uint64_t startingOffset = ::GetTickCount64();
    timestamp = (::GetTickCount64() - startingOffset);
#endif

#if defined (QCC_OS_GROUP_POSIX)
    struct timespec ts;
    static uint64_t startingOffset = 0;

    clock_gettime(CLOCK_MONOTONIC, &ts);
    if (startingOffset == 0) {
        startingOffset = ts.tv_sec;
    }
    timestamp = ((uint64_t)(ts.tv_sec - startingOffset)) * 1000;
    timestamp += (uint64_t)ts.tv_nsec / 1000000;
#endif

    return timestamp;
}

int32_t NotificationTesterImpl::LoopHandler() {
    int32_t sleepTime = 5;

    if (notifProdEnabled) {
        uint64_t currentTimestamp = GetTimestamp();
        if ((nextMessageTime == 0) || (currentTimestamp > nextMessageTime)) {
            if (nextMessageTime == 0) {
                if (notifIntervalOffset > 0) {
                    // add the initial offset to the notification time
                    intervalOffset = notifIntervalOffset;
                    QCC_LogMsg(("First notification will be offset by: %dms", intervalOffset));
                }
            } else {
                // send a message
                NotificationMessageType messageType = NotificationMessageType(INFO);
                std::vector<NotificationText> vecMessages;

                // setup for the next interval
                if (notifRatePriorityType == PRIORITY_RANDOM) {
                    // random priority type
                    uint32_t randomNum = GetRandomNumber();
                    messageType = NotificationMessageType(
                        (randomNum % NotificationMessageType::MESSAGE_TYPE_CNT));
                } else {
                    messageType = NotificationMessageType(notifRatePriority);
                }

                NotificationText textToSend(notifMsgLang, notifMsgText);
                vecMessages.push_back(textToSend);

                Notification notification(messageType, vecMessages);
                QStatus status = sender->send(notification, notifTTL);
                if (status != ER_OK) {
                    QCC_LogError(status, ("Could not send the message successfully."));
                } else {
                    int32_t messageId;
                    sender->getLastMsgId(messageType, &messageId);
                    QCC_LogMsg(("Sent Message with Type: %d; TTL: %d sec and id: %d", messageType, notifTTL, messageId));
                }
            }

            // determine next message time
            int intervalInMsecs = notifInterval;
            if (intervalInMsecs <= 0) {
                std::cout << "Invalid Notification Interval, using 10 seconds instead" << std::endl;
                intervalInMsecs = 10000;
            }
            if (notifRateType == RATE_RANDOM) {
                // random rate type
                uint32_t randomNum = GetRandomNumber();
                uint64_t nextMessageInterval = (randomNum % intervalInMsecs);
                nextMessageTime = currentTimestamp + (nextMessageInterval) + intervalOffset;
                intervalOffset = intervalInMsecs - nextMessageInterval;
            } else {
                nextMessageTime = currentTimestamp + intervalInMsecs + intervalOffset;
                intervalOffset = 0;
            }

            sleepTime = ((nextMessageTime - currentTimestamp) + 999) / 1000;
            QCC_LogMsg(("Next message will be sent in %d sec", sleepTime));
        }
    }
    return sleepTime;
}

