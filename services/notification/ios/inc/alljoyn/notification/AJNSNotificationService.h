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
#import "NotificationService.h"
#import "AJNSNotificationReceiverAdapter.h"
#import "AJNSNotificationReceiver.h"
#import "AJNSNotificationSender.h"
#import "AJNBusAttachment.h"
#import "alljoyn/services_common/AJSVCGenericLoggerAdapter.h"

/**
 AJNSNotificationService class
 */
@interface AJNSNotificationService : NSObject

///---------------------
/// @name Properties
///---------------------

/**
 * Get Instance of AJNSNotificationServiceImpl
 * @return instance
 */
+ (id)sharedInstance;

/**
 *  Initialize Producer side via Transport. Create and
 *  return NotificationSender.
 *  @param bus ajn bus
 *  @param store property store
 *  @return NotificationSender instance
 */

- (AJNSNotificationSender *)startSendWithBus:(AJNBusAttachment *)bus andPropertyStore:(AJNAboutPropertyStoreImpl *)store;
/**
 * Initialize Consumer side via Transport.
 * Set NotificationReceiver to given receiver
 * @param bus ajn bus
 * @param ajnsNotificationReceiver notification receiver
 * @return status
 */
- (QStatus)startReceive:(AJNBusAttachment *)bus withReceiver:(id <AJNSNotificationReceiver> )ajnsNotificationReceiver;

/**
 * Stops sender but leaves bus and other objects alive
 */
- (void)shutdownSender;

/**
 * Stops receiving but leaves bus and other objects alive
 */
- (void)shutdownReceiver;

/**
 * Cleanup and get ready for shutdown
 */
- (void)shutdown;

/**
 * Disabling superagent mode. Needs to be called before
 * starting receiver
 * @return status
 */
- (QStatus)disableSuperAgent;

/**
 * Get the currently-configured logger implementation
 * @return logger Implementation of GenericLogger
 */
- (id <AJSVCGenericLogger> )logger;



/**
 * Set log level filter for subsequent logging messages
 * @param newLogLevel enum value
 * @return logLevel enum value that was in effect prior to this change
 */
- (void)setLogLevel:(QLogLevel)newLogLevel;

/**
 * Get log level filter value currently in effect
 * @return logLevel enum value currently in effect
 */
- (QLogLevel)logLevel;

/**
 * Virtual method to get the busAttachment used in the service.
 */
- (AJNBusAttachment *)busAttachment;

/**
 * Get the Version of the NotificationService
 * @return the NotificationService version
 */
- (uint16_t)version;

@end
