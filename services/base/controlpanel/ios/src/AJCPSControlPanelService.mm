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

#import "AJCPSControlPanelService.h"
#import "AJSVCGenericLoggerAdapter.h"
#import "AJCPSControlPanelListenerAdapter.h"

@interface AJCPSControlPanelService ()
@property (nonatomic) ajn::services::ControlPanelService *handle;
@property (nonatomic) AJCPSControlPanelListenerAdapter *listenerAdapter;

@property id <AJSVCGenericLogger> currentLogger;
@property AJSVCGenericLoggerAdapter *genericLoggerAdapter;
@end


@implementation AJCPSControlPanelService

+ (AJCPSControlPanelService *)getInstance
{
	static AJCPSControlPanelService *aboutLogger;
	static dispatch_once_t donce;
	dispatch_once(&donce, ^{
	    aboutLogger = [[self alloc] init];
	});
	return aboutLogger;
}

- (id)init
{
	self = [super init];
	self.handle = ajn::services::ControlPanelService::getInstance();
	return self;
}

- (QStatus)initController:(AJNBusAttachment *)bus controlPanelController:(AJCPSControlPanelController *)controlPanelController
     controlPanelListener:(id <AJCPSControlPanelListener> )controlPanelListener
{
	self.listenerAdapter = new AJCPSControlPanelListenerAdapter(controlPanelListener);
    
	return self.handle->initController((ajn::BusAttachment *)[bus handle], [controlPanelController handle], self.listenerAdapter);
}

/**
 * Remove locally stored controller. Allows a new call to initController to be made
 * @return status
 */
- (QStatus)shutdownController
{
	return self.handle->shutdown();
}

- (AJNBusAttachment *)getBusAttachment
{
	return [[AJNBusAttachment alloc]initWithHandle:self.handle->getBusAttachment()];
}

/**
 * Get the ControlPanelListener
 * @return ControlPanelListener
 */
- (id <AJCPSControlPanelListener> )getControlPanelListener
{
	AJCPSControlPanelListenerAdapter *adapter = (AJCPSControlPanelListenerAdapter *)self.handle->getControlPanelListener();
    
	return adapter->getListener();
}

/**
 * Get the Version of the ControlPanelService
 * @return the ControlPanelService version
 */
- (uint16_t)getVersion
{
	return self.handle->getVersion();
}

#pragma mark - Logger methods
- (void)setLogger:(id <AJSVCGenericLogger> )logger
{
	if (logger) {
		// save current logger
		self.currentLogger = logger;
		// call setLoger with the adapter and save the prev Logger
	}
	else {
		[self.currentLogger warnTag:([NSString stringWithFormat:@"%@", [[self class] description]]) text:@"Failed set a logger"];
	}
}

- (id <AJSVCGenericLogger> )logger
{
	return self.currentLogger;
}

- (void)setLogLevel:(QLogLevel)newLogLevel
{
	[self.currentLogger setLogLevel:newLogLevel];
}

- (QLogLevel)logLevel
{
	return [self.currentLogger logLevel];
}

@end