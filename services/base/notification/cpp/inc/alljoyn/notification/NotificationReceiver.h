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

#ifndef NOTIFICATIONRECEIVER_H_
#define NOTIFICATIONRECEIVER_H_

#include <alljoyn/notification/Notification.h>

namespace ajn {
namespace services {

/**
 * An Abstract class with function receive. The implementation of this class
 * can be passed in to the initReceive function and will be the callback for
 * when notifications are received
 */
class NotificationReceiver {
  public:

    /**
     * Constructor for NotificationReceiver
     */
    NotificationReceiver() { };

    /**
     * Destructor for NotificationReceiver
     */
    virtual ~NotificationReceiver() { };

    /**
     * Pure abstract function that receives a notification
     * Consumer Application must override this method
     * @param notification the notification that is received
     */
    virtual void Receive(Notification const& notification) = 0;

    /**
     *   Dismiss handler
     */
    virtual void Dismiss(const int32_t msgId, const qcc::String appId) = 0;
};
} //namespace services
} //namespace ajn

#endif /* NOTIFICATIONRECEIVER_H_ */
