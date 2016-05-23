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

#ifndef CONTROLLERNOTIFICATIONRECEIVER_H_
#define CONTROLLERNOTIFICATIONRECEIVER_H_

#include <vector>
#include <alljoyn/controlpanel/ControlPanelController.h>
#include <alljoyn/notification/NotificationReceiver.h>
#include <alljoyn/notification/Notification.h>

/**
 * Class that will receive Notifications. Implements NotificationReceiver
 * Receives list of applications to filter by and will only display notifications
 * from those applications
 */
class ControllerNotificationReceiver : public ajn::services::NotificationReceiver {
  public:

    /**
     * Constructor
     */
    ControllerNotificationReceiver(ajn::services::ControlPanelController* controlPanelController);

    /**
     * Destructor
     */
    ~ControllerNotificationReceiver();

    /**
     * Receive - function that receives a notification
     * @param notification
     */
    void Receive(ajn::services::Notification const& notification);

    /**
     * receive Dismiss signal
     * @param message id
     * @param application id
     */
    void Dismiss(const int32_t msgId, const qcc::String appId);
  private:

    ajn::services::ControlPanelController* m_Controller;

};

#endif /* CONTROLLERNOTIFICATIONRECEIVER_H_ */
