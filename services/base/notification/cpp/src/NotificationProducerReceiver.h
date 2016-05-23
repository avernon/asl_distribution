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

#ifndef NOTIFICATIONPRODUCERRECEIVER_H_
#define NOTIFICATIONPRODUCERRECEIVER_H_

#include "NotificationProducer.h"
#include <queue>
#ifdef _WIN32
#include <Windows.h>
#define pthread_mutex_t CRITICAL_SECTION
#define pthread_cond_t CONDITION_VARIABLE
#else
#include <pthread.h>
#endif

namespace ajn {
namespace services {

/**
 * class MsgQueueContent
 *
 */
class MsgQueueContent {
  public:
    MsgQueueContent(uint32_t msgId) : m_MsgId(msgId) { }

    uint32_t m_MsgId;
};

/**
 * class NotificationProducerReceiver
 * Implements NotificationProducer interface at producer side
 */
class NotificationProducerReceiver : public ajn::services::NotificationProducer {

  public:
    /**
     * constructor of NotificationProducerReceiver
     * @param bus attachment
     * @param status
     */
    NotificationProducerReceiver(ajn::BusAttachment* bus, QStatus& status);

    /**
     * destructor of NotificationProducerReceiver
     */
    ~NotificationProducerReceiver();

    /**
     *  Handles  Dismiss method
     * @param[in]  member
     * @param[in]  msg reference of AllJoyn Message
     */
    void Dismiss(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);

    /**
     * SetAppIdArg
     * @param application id argument
     */
    void SetAppIdArg(MsgArg appIdArg) {
        m_AppIdArg = appIdArg;
    }
    /**
     * unregisterHandler
     * @param bus attachment
     */
    void unregisterHandler(BusAttachment* bus);
  private:
    /**
     * implement method calls from notification producer interface
     */
    void HandleMethodCall(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);

    /**
     * The thread responsible for receiving the notification
     */
#ifdef _WIN32
    HANDLE m_handle;
#else
    pthread_t m_ReceiverThread;
#endif

    /**
     * A Queue that holds the messages
     */
    std::queue<MsgQueueContent> m_MessageQueue;

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
    void Receiver();

    /**
     * sendDismissSignal
     */
    QStatus sendDismissSignal(int32_t msgId);

    /**
     * appIdArg
     */
    MsgArg m_AppIdArg;

};
} //namespace services
} //namespace ajn

#endif /* NOTIFICATIONPRODUCERRECEIVER_H_ */
