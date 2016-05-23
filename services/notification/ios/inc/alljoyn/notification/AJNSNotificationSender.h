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

#import <Foundation/Foundation.h>
#import "NotificationSender.h"
#import "Notification.h"
#import "NotificationEnums.h"
#import "AJNSNotificationEnums.h"
#import "AJNSNotification.h"
#import "alljoyn/about/AJNPropertyStore.h"
#import "alljoyn/about/AJNAboutPropertyStoreImpl.h"

/**
 AJNSNotificationSender class
 */
@interface AJNSNotificationSender : NSObject
///---------------------
/// @name Properties
///---------------------
/** NotificationSender Handler*/
@property (nonatomic)ajn::services::NotificationSender * senderHandle;


///---------------------
/// @name Initialization
///---------------------

/**
 * Designated initializer
 * @param propertyStore property store
 */
- (AJNSNotificationSender *)initWithPropertyStore:(AJNAboutPropertyStoreImpl *)propertyStore;

///---------------------
/// @name Instance methods
///---------------------

/**
 * Send notification
 * @param ajnsNotification `ajnsNotification` object
 * @param ttl message ttl
 * @return status
 */
- (QStatus)send:(AJNSNotification *)ajnsNotification ttl:(uint16_t)ttl;

/**
 * Delete last message that was sent with given MessageType
 * @param messageType MessageType of message to be deleted
 * @return status
 */
- (QStatus)deleteLastMsg:(AJNSNotificationMessageType)messageType;

/**
 * Get the property store in this sender
 * @return The property store
 */
- (ajn ::services ::AboutPropertyStoreImpl *)getPropertyStore;

@end
