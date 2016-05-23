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

#import <vector>
#import "alljoyn/notification/NotificationReceiver.h"
#import "alljoyn/notification/Notification.h"
#import "AJNSNotificationReceiver.h"

/**
 NotificationReceiverAdapter class
 */

class AJNSNotificationReceiverAdapter : public ajn::services::NotificationReceiver {
public:
	/**
     NotificationReceiverAdapter
     @param notificationReceiverHandler a AJNSNotificationReceiver handler
	 */
	AJNSNotificationReceiverAdapter(id <AJNSNotificationReceiver> notificationReceiverHandler);
    
	/**
     receive a notification
     @param notification the notification will be populated inside this param
	 */
	void Receive(ajn::services::Notification const& notification);
    
    /**
     Dismiss handler
     @param msgId message ID to dismiss
     @param appId app ID to use
     */
    void Dismiss(const int32_t msgId, const qcc::String appId);

    
	/**
     The handler of the receiver
	 */
	id <AJNSNotificationReceiver> ajnsNotificationReceiverHandler;
};
