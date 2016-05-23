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

#ifndef NOTIFICATIONTESTERIMPL_H_
#define NOTIFICATIONTESTERIMPL_H_

#include <alljoyn/notification/NotificationService.h>
#include "NotificationReceiverImpl.h"
#include <AboutDataStore.h>

/**
 * Class for testing notification functionality based on runtime configuration.
 * First call Initialize and ten call LoopHandler periodically based on the number of seconds returned.
 */
class NotificationTesterImpl {
  public:

    /**
     * Constructor
     */
    NotificationTesterImpl();

    /**
     * Destructor
     */
    ~NotificationTesterImpl();

    /**
     * Initialize - initializes the testing functionality
     * @param bus
     * @param store
     * @return true if initialization was successful
     */
    bool Initialize(ajn::BusAttachment* bus, AboutDataStore* store);

    /**
     * LoopHandler - function that executes the test functionality
     * @return maximum amount of time in seconds to wait before calling LoopHandler again
     */
    int32_t LoopHandler();

  private:

    enum NotificationRateType {
        RATE_FIXED, RATE_RANDOM
    };
    enum NotificationPriorityType {
        PRIORITY_FIXED, PRIORITY_RANDOM
    };

    void LoadConfiguration();
    void Cleanup();

    uint64_t nextMessageTime;
    uint64_t intervalOffset;
    ajn::services::NotificationService* prodService;
    NotificationReceiverImpl* receiver;
    ajn::services::NotificationSender* sender;

    bool notifProdEnabled;
    uint32_t notifInterval;
    uint32_t notifIntervalOffset;
    NotificationRateType notifRateType;
    uint16_t notifRatePriority;
    NotificationPriorityType notifRatePriorityType;
    qcc::String notifMsgText;
    qcc::String notifMsgLang;
    uint32_t notifTTL;
    bool notifCustEnabled;
};

#endif /* NOTIFICATIONTESTERIMPL_H_ */
