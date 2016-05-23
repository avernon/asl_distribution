/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

#ifndef NOTIFICATIONDISMISSERRECEIVER_H_
#define NOTIFICATIONDISMISSERRECEIVER_H_

#include <queue>
#include <pthread.h>
#include <qcc/String.h>
#include "NotificationDismisser.h"

namespace ajn {
namespace services {

/**
 * Notification Dismisser Receiver
 */
class NotificationDismisserReceiver : public NotificationDismisser {
  public:

    /**
     * Constructor for TransportConsumer
     * @param bus         - BusAttachment that is used
     * @param servicePath - servicePath of BusObject
     * @param status      - success/failure
     */
    NotificationDismisserReceiver(ajn::BusAttachment* bus, QStatus& status);

    /**
     * Destructor of TransportConsumer
     */
    ~NotificationDismisserReceiver() { };

    /**
     * Callback when Signal arrives
     * @param member    Method or signal interface member entry.
     * @param srcPath   Object path of signal emitter.
     * @param message   The received message.
     */
    void Signal(const ajn::InterfaceDescription::Member* member,
                const char* srcPath, ajn::Message& msg);

    /**
     * To stop thread processing of messages
     * @param - bus attachment
     */
    void unregisterHandler(ajn::BusAttachment* bus);

  private:

    /**
     * The thread responsible for receiving the notification
     */
    pthread_t m_ReceiverThread;

    /**
     * A Queue that holds the messages
     */
    std::queue<ajn::Message> m_MessageQueue;

    /**
     * The mutex Lock
     */
    pthread_mutex_t m_Lock;

    /**
     * The Queue Changed thread condition
     */
    pthread_cond_t m_QueueChanged;

    /**
     * is the thread in the process of shutting down
     */
    bool m_IsStopping;

    /**
     * A wrapper for the receiver Thread
     * @param context
     */
    static void* ReceiverThreadWrapper(void* context);

    /**
     * The function run in the ReceiverThread
     */
    void ReceiverThread();

    /**
     * unmarshal dismisser message
     */
    QStatus UnmarshalMessage(Message& in_message, int32_t& messageId, qcc::String& appId);
};
} //namespace services
} //namespace ajn

#endif /* NOTIFICATIONDISMISSERRECEIVER_H_ */
