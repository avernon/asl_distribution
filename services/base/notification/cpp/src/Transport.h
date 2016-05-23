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

#ifndef TRANSPORT_H_
#define TRANSPORT_H_

#include <map>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/notification/NotificationEnums.h>
#include "NotificationConstants.h"

namespace ajn {
namespace services {

class Notification;
class NotificationReceiver;
class NotificationProducerSender;
class NotificationProducerReceiver;
class NotificationProducerListener;
class NotificationDismisserSender;
class NotificationDismisserReceiver;
class NotificationConstants;
class NotificationTransportConsumer;
class NotificationTransportProducer;
/**
 * Class Used for all Transport related tasks including initializing and shutting
 * down the BusObjects of the services and sending and receiving messages
 */
class Transport {

  public:

    /**
     * Destructor of Transport
     */
    ~Transport();

    /**
     * static function to get an Instance of the Transport class
     * @return pointer to Transport instance
     */
    static Transport* getInstance();

    /**
     * Sets the internal NotificationReceiver to the one
     * provided in the parameter
     * @param notificationReceiver
     */
    void setNotificationReceiver(NotificationReceiver* notificationReceiver);

    /**
     * Start the Sender Transport:
     * Create a BusAttachment if one doesn't exist.
     * Create the NotificationTransportProducers (one per MessageType)
     * @param bus - The busAttachment to be used
     * @return status
     */
    QStatus startSenderTransport(ajn::BusAttachment* bus);

    /**
     * Start the Receiver Transport:
     * Create a BusAttachment if one doesn't exist.
     * create the NotificationTransportConsumer to handle the signals
     * @param bus - the busAttachment to be used
     * @return status
     */
    QStatus startReceiverTransport(ajn::BusAttachment* bus);

    /**
     * Send Notification
     * @param messageType
     * @param notificationArgs
     * @param ttl
     * @return status
     */
    QStatus sendNotification(NotificationMessageType messageType,
                             ajn::MsgArg const notificationArgs[nsConsts::AJ_NOTIFY_NUM_PARAMS],
                             uint16_t ttl);

    /**
     * Delete the last Signal sent off for this messageType
     * @param messageType
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
     * Get the notification id of the last message that was sent with given MessageType
     * @param messageType
     * @param messageId
     * @return status
     */
    QStatus getLastMsgId(NotificationMessageType messageType, int32_t* messageId);

    /**
     * Pass on the notification received to the NotificationReceiver
     * @param notification
     */
    void onReceivedNotification(Notification const& notification);

    /**
     * Called on shutdown. Cleans up Alljoyn objects and frees memory where necessary
     */
    void cleanup();

    /**
     * Cleanup the TransportConsumer objects. Also Unregisteres the BusObject depending on input param
     * @param unregister - should BusObject be Unregistered from Bus
     */
    void cleanupTransportConsumer(bool unregister = false);

    /**
     * Cleanup all Sender Transport objects. and Unregister the BusObject
     */
    void cleanupSenderTransport();

    /**
     * Cleanup all Receiver Transport objects. and Unregister the BusObject
     */
    void cleanupReceiverTransport();

    /**
     * Cleanup AnnouncementListener object. Also Unregisteres the listener from the aboutclient
     * @param unregister - should listener be Unregistered from aboutclient
     */
    void cleanupAnnouncementListener(bool unregister = false);
    /**
     * Cleanup cleanupNotificationProducerSender. and Unregister the BusObject.
     */
    void cleanupNotificationProducerSender();
    /**
     * getBusAttachment - returns BusObject
     */
    ajn::BusAttachment* getBusAttachment();

    /**
     * get function for NotificationProducerSender
     */
    NotificationProducerSender* getNotificationProducerSender();

    /**
     * get function for NotificationProducerReceiver
     */
    NotificationProducerReceiver* getNotificationProducerReceiver();

    /**
     * get function for NotificationDismisserSender
     */
    NotificationDismisserSender* getNotificationDismisserSender();

    /**
     * get function for NotificationReceiver
     */
    NotificationReceiver* getNotificationReceiver();


  private:

    /**
     * Private Constructor - singleton Class
     */
    Transport();

    /**
     * Sets the internal busAttachment to the one
     * provided in the parameter
     * @param bus
     * @return success/failure
     */
    QStatus setBusAttachment(ajn::BusAttachment* bus);

    /**
     * Cleanup the TransportProducer objects. Start from messageTypeIndx param and work backwards
     * Also Unregisters the BusObject depending on input param
     * @param messageTypeIndx - messageTypeIndx to start from
     * @param unregister - should BusObject be Unregistered from Bus
     */
    void cleanupTransportProducer(int32_t messageTypeIndx, bool unregister = false);
    /**
     * cleanupSenderProducerReceiver
     */
    void cleanupNotificationProducerReceiver();
    /**
     * cleanupSenderProducerReceiver
     */
    void cleanupNotificationProducerReceiverInternal();
    /**
     * cleanupNotificationDismisserSender
     */
    void cleanupNotificationDismisserSender();
    /**
     * cleanupNotificationDismisserSender
     */
    void cleanupNotificationDismisserSenderInternal();
    /**
     * cleanupNotificationDismisserReceiver
     */
    void cleanupNotificationDismisserReceiver();
    /**
     * cleanupNotificationDismisserReceiver
     */
    void cleanupNotificationDismisserReceiverInternal();
    /**
     * Cleanup cleanupNotificationProducerSender. and Unregister the BusObject.
     */
    void cleanupNotificationProducerSenderInternal();
    /**
     * Cleanup the TransportConsumer objects. Also Unregisteres the BusObject depending on input param
     * @param unregister - should BusObject be Unregistered from Bus
     */
    void cleanupTransportConsumerInternal(void);

    /**
     * Static instance of Transport. Makes Transport a singleton
     */
    static Transport* s_Instance;

    /**
     * Alljoyn BusAttachment that will be used to connect to Bus
     */
    ajn::BusAttachment* m_Bus;

    /**
     * NotificationReceiver that will receive the incoming notifications
     * Must be created external from library and passed in
     */
    NotificationReceiver* m_Receiver;

    /**
     * The BusObjects for the Producer. One per MessageType
     */
    NotificationTransportProducer* m_Producers[MESSAGE_TYPE_CNT];

    /**
     * The BusObjects for the Consumer.
     */
    NotificationTransportConsumer* m_Consumer;

    /**
     * Boolean to dictate whether we send notifications or swallow them
     */
    bool m_IsSendingDisabled;

    /**
     * Boolean to dictate whether we receive notifications or swallow them
     */
    bool m_IsReceivingDisabled;

    /**
     * NotificationProducerSender
     */
    NotificationProducerSender* m_NotificationProducerSender;
    /**
     * NotificationProducerReceiver
     */
    NotificationProducerReceiver* m_NotificationProducerReceiver;
    /**
     * NotificationProducerListener
     */
    NotificationProducerListener* m_NotificationProducerListener;
    /**
     * NotificationDismisserSender
     */
    NotificationDismisserSender* m_NotificationDismisserSender;
    /**
     * NotificationDismisserReceiver
     */
    NotificationDismisserReceiver* m_NotificationDismisserReceiver;

};
} //namespace services
} //namespace ajn

#endif /* TRANSPORT_H_ */
