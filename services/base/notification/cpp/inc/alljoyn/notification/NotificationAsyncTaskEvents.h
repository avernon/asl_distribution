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


#ifndef NOTIFICATION_ASYNCTASK_EVENTS_H_
#define NOTIFICATION_ASYNCTASK_EVENTS_H_

#include <queue>
#include <qcc/String.h>
#include <iostream>
#include <alljoyn/notification/NotificationService.h>
#include <alljoyn/services_common/AsyncTaskQueue.h>

namespace ajn {
namespace services {

/**
 * Notification async task events.
 * Class implementing callbacks fto handle messages.
 */
class NotificationAsyncTaskEvents : public AsyncTask {
  public:
    /**
     * constructor of NotificationAsyncTaskEvents
     */
    NotificationAsyncTaskEvents();
    /**
     * destructor of NotificationAsyncTaskEvents
     */
    virtual ~NotificationAsyncTaskEvents();
    /**
     * callback to handle the case of empty message queue.
     */
    virtual void OnEmptyQueue();
    /**
     * callback to handle the case of new message
     * @param taskdata - object to handle
     */
    virtual void OnTask(TaskData const* taskdata);

  private:
    /**
     * send dismiss signal
     * @param asyncTaskQueue - a template type of message
     */
    void sendDismissSignal(TaskData const* taskdata);

};

} //namespace services
} //namespace ajn



#endif /* NOTIFICATION_ASYNCTASK_EVENTS_H_ */
