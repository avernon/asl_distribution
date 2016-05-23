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

#ifndef NOTIFICATIONSENDER_H_
#define NOTIFICATIONSENDER_H_

#include <vector>
#include <map>
#include <alljoyn/Status.h>
#include <alljoyn/AboutData.h>
#include <alljoyn/notification/NotificationEnums.h>

#include <alljoyn/about/PropertyStore.h>

namespace ajn {
namespace services {

class Notification;

/**
 * The class used to send Notifications or delete the last sent Notification
 */
class NotificationSender {
  public:

    /**
     * Constructor for NotificationSenderImpl
     * @param aboutdata - AboutData that includes entries
     * for deviceId, deviceName, appId and appName
     */
    NotificationSender(ajn::AboutData* aboutdata);

    /**
     * Constructor for NotificationSenderImpl
     * @param propertyStore - propertyStoreImplementation that includes entries
     * for deviceId, deviceName, appId and appName
     * @deprecated see NotificationSender(ajn::AboutData*)
     */
    QCC_DEPRECATED(NotificationSender(ajn::services::PropertyStore* propertyStore));

    /**
     * Destructor for NotificationSenderImpl
     */
    ~NotificationSender() { };

    /**
     * Send notification
     * @param notification
     * @param ttl
     * @return
     */
    QStatus send(Notification const& notification, uint16_t ttl);

    /**
     * Delete last message that was sent with given MessageType
     * @param messageType MessageType of message to be deleted
     * @return success/failure
     */
    QStatus deleteLastMsg(NotificationMessageType messageType);

    /**
     * Get the notification id of the last message sent with the given MessageType
     * @param messageType type of message
     * @param messageId pointer to hold the notification id of the last message
     * @return success/failure
     */
    QStatus getLastMsgId(NotificationMessageType messageType, int32_t* messageId);

  private:

    /**
     * Pointer to AboutData implementing the storage.
     */
    ajn::AboutData* m_aboutdata;

    /**
     * Pointer to PropertyStore implementing the storage.
     */
    ajn::services::PropertyStore* m_PropertyStore;

};
} //namespace services
} //namespace ajn

#endif /* NOTIFICATIONSENDER_H_ */
