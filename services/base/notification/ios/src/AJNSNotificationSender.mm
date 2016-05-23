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

#import "AJNSNotificationSender.h"

@interface AJNSNotificationSender ()
@property (nonatomic) ajn::services::AboutPropertyStoreImpl *propertyStore;

@end

@implementation AJNSNotificationSender

- (AJNSNotificationSender *)initWithPropertyStore:(AJNAboutPropertyStoreImpl *)propertyStore
{
	self = [super init];
	if (self) {
		self.propertyStore = [propertyStore getHandle];
		if (self.propertyStore) {
			self.senderHandle = new ajn::services::NotificationSender(self.propertyStore);
			return self;
		}
	}
	return nil;
}

/**
 * Send notification
 * @param notification
 * @param ttl message ttl
 * @return status
 */
- (QStatus)send:(AJNSNotification *)ajnsNotification ttl:(uint16_t)ttl
{
	return (self.senderHandle->send(*ajnsNotification.handle, ttl));
}

/**
 * Delete last message that was sent with given MessageType
 * @param messageType MessageType of message to be deleted
 * @return status
 */
- (QStatus)deleteLastMsg:(AJNSNotificationMessageType)messageType
{
	return(self.senderHandle->deleteLastMsg((ajn::services::NotificationMessageType)messageType));
}

- (ajn::services::AboutPropertyStoreImpl *)getPropertyStore
{
	return self.propertyStore;
}

@end
