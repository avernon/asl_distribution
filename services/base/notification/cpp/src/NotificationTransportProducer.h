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

#ifndef NOTIFICATIONTRANSPORTPRODUCER_H_
#define NOTIFICATIONTRANSPORTPRODUCER_H_

#include <alljoyn/notification/NotificationEnums.h>

#include "NotificationTransport.h"
#include "NotificationConstants.h"

namespace ajn {
namespace services {

/**
 * Notification Transport Producer. Used to Create the Notification Interface
 * on the producers side and send the notify signals
 */
class NotificationTransportProducer : public NotificationTransport {

  public:

    /**
     * Constructor for TransportProducer. Creates Interface and prepares
     * infrastructure to be able to send Signal
     * @param bus            - BusAttachment that is used
     * @param servicePath    - servicePath of BusObject
     * @param status         - success/failure
     * @param m_serialNumber - serial number of the last successful message on the bus
     */
    NotificationTransportProducer(ajn::BusAttachment* bus,
                                  qcc::String const& servicePath, QStatus& status,
                                  qcc::String const& interfaceName = nsConsts::AJ_NOTIFICATION_INTERFACE_NAME, uint32_t serialNumber = 0);

    /**
     * Destructor for TransportProducer
     */
    ~NotificationTransportProducer() { };

    /**
     * Send Signal over Bus.
     * @param notificationArgs
     * @param ttl
     * @return status
     */
    QStatus sendSignal(ajn::MsgArg const notificationArgs[nsConsts::AJ_NOTIFY_NUM_PARAMS],
                       uint16_t ttl);

    /**
     * delete last message
     * @param type of message to delete
     * @return status
     */
    QStatus deleteLastMsg(NotificationMessageType messageType);

    /**
     * Delete Signal sent off for this messageType
     * @param messageId
     * @return status
     */
    QStatus deleteMsg(int32_t msgId);

    /**
     * get the notification id of the last message sent with the given MessageType
     * @param messageType type of message
     * @param messageId pointer to hold the notification id of the last message
     * @return status
     */
    QStatus getLastMsgId(NotificationMessageType messageType, int32_t* messageId);


  private:

    /**
     * Serial Number of the last message sent with this message type
     */
    uint32_t m_SerialNumber;

    /**
     * message Id of the last message sent with this message type
     */
    int32_t m_MsgId;

};
} //namespace services
} //namespace ajn

#endif /* NOTIFICATIONTRANSPORTPRODUCER_H_ */
