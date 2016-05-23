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

#import "AJNSNotificationService.h"
#import "alljoyn/services_common/AJSVCGenericLogger.h"
#import "alljoyn/services_common/AJSVCGenericLoggerDefaultImpl.h"

@interface AJNSNotificationService ()

@property AJSVCGenericLoggerAdapter *genericLoggerAdapter;
@property id <AJSVCGenericLogger> currentLogger;
@property (strong, nonatomic) AJNSNotificationSender *ajnsSender;

//@property QLogLevel currentLogLevel;

@end

@implementation AJNSNotificationService

/**
 * Get Instance of NotificationServiceImpl - singleton implementation
 * @return instance
 */

+ (id)sharedInstance
{
	static AJNSNotificationService *ajnsNotificationService;
	static dispatch_once_t donce;
	dispatch_once(&donce, ^{
	    ajnsNotificationService = [[self alloc] init];
	});
	return ajnsNotificationService;
}

- (id)init
{
	if (self = [super init]) {
	}
	return self;
}

/**
 *  Initialize Producer side via Transport. Create and
 *  return NotificationSender.
 * @param bus
 * @param store
 * @return NotificationSender instance
 */
- (AJNSNotificationSender *)startSendWithBus:(AJNBusAttachment *)bus andPropertyStore:(AJNAboutPropertyStoreImpl *)store
{
	self.ajnsSender = [[AJNSNotificationSender alloc] initWithPropertyStore:store];
    
	//NotificationSender* NotificationService::initSend(BusAttachment* bus, PropertyStore* store)
	if (self.ajnsSender) {
		self.ajnsSender.senderHandle = ajn::services::NotificationService::getInstance()->initSend((ajn::BusAttachment *)bus.handle, [self.ajnsSender getPropertyStore]);
	}
    
	return self.ajnsSender.senderHandle ? self.ajnsSender : nil;
}

/**
 * Initialize Consumer side via Transport.
 * Set NotificationReceiver to given receiver
 * @param bus
 * @param notificationReceiver
 * @return status
 */
- (QStatus)startReceive:(AJNBusAttachment *)bus withReceiver:(id <AJNSNotificationReceiver> )ajnsNotificationReceiver
{
	if (!bus) {
		return ER_BAD_ARG_1;
	}
    
	if (!ajnsNotificationReceiver) {
		return ER_BAD_ARG_2;
	}
    
	AJNSNotificationReceiverAdapter *notificationReceiverAdapter = new AJNSNotificationReceiverAdapter(ajnsNotificationReceiver);
	if (!notificationReceiverAdapter) {
		if (self.logger)
			[self.logger warnTag:[NSString stringWithFormat:@"%@", [[self class] description]] text:@"Failed to create adapter."];
		return ER_FAIL;
	}
    
	return (ajn::services::NotificationService::getInstance()->initReceive((ajn::BusAttachment *)bus.handle, notificationReceiverAdapter));
}

/**
 * Stops sender but leaves bus and other objects alive
 */
- (void)shutdownSender
{
	ajn::services::NotificationService::getInstance()->shutdownSender();
}

/**
 * Stops receiving but leaves bus and other objects alive
 */
- (void)shutdownReceiver
{
	ajn::services::NotificationService::getInstance()->shutdownReceiver();
}

/**
 * Cleanup and get ready for shutdown
 */
- (void)shutdown
{
	ajn::services::NotificationService::getInstance()->shutdown();
}

/** @deprecated SuperAgent was deprecated in May 2015 for 15.04
 * release
 * Disabling superagent mode. 
 * Needs to be called before
 * starting receiver
 * @return status
 */
- (QStatus)disableSuperAgent
{
	return ER_OK;
}

#pragma mark *** Logger methods ***

/**
 * Get the currently-configured logger implementation
 * @return logger Implementation of GenericLogger
 */
- (id <AJSVCGenericLogger> )logger
{
	return self.currentLogger;
}

/**
 * Set log level filter for subsequent logging messages
 * @param newLogLevel enum value
 * @return logLevel enum value that was in effect prior to this change
 */
- (void)setLogLevel:(QLogLevel)newLogLevel;
{
	[self.currentLogger setLogLevel:newLogLevel];
}

/**
 * Get log level filter value currently in effect
 * @return logLevel enum value currently in effect
 */
- (QLogLevel)logLevel;
{
	return [self.currentLogger logLevel];
}

#pragma mark *** ***
/**
 * Virtual method to get the busAttachment used in the service.
 */
- (AJNBusAttachment *)busAttachment
{
	AJNBusAttachment *ajnBusAttachment;
	ajnBusAttachment = [[AJNBusAttachment alloc] initWithHandle:ajn::services::NotificationService::getInstance()->getBusAttachment()];
	return ajnBusAttachment;
}

/**
 * Get the Version of the NotificationService
 * @return the NotificationService version
 */
- (uint16_t)version
{
	return ajn::services::NotificationService::getInstance()->getVersion();
}

@end
