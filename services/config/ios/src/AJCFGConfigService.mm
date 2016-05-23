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

#import "AJCFGConfigService.h"
#import "AJNSessionOptions.h"
#import "alljoyn/config/ConfigService.h"
#import "alljoyn/services_common/AJSVCGenericLoggerAdapter.h"
#import "alljoyn/services_common/AJSVCGenericLoggerDefaultImpl.h"

@interface AJCFGConfigService ()

@property ajn::services::ConfigService *handle;
@property id <AJSVCGenericLogger> currentLogger;
@property AJSVCGenericLoggerAdapter *AJSVCGenericLoggerAdapter;

@end

@implementation AJCFGConfigService

- (id)initWithBus:(AJNBusAttachment *)bus propertyStore:(AJCFGPropertyStoreImpl *)propertyStore listener:(AJCFGConfigServiceListenerImpl *)listener
{
	self = [super init];
	if (self) {
		self.handle = new ajn::services::ConfigService((ajn::BusAttachment&)(*bus.handle), *propertyStore.getHandle, *[listener handle]);
		// Set a default logger
		self.currentLogger = [[AJSVCGenericLoggerDefaultImpl alloc] init];
		// Create and set a generic logger adapter adapter
		self.AJSVCGenericLoggerAdapter = new AJSVCGenericLoggerAdapter(self.currentLogger);
	}
	return self;
}

- (QStatus)registerService
{
	return self.handle->Register();
}

- (void)unregisterService
{
	//self.handle->Unregister();
}

#pragma mark - Logger methods
- (void)setLogger:(id <AJSVCGenericLogger> )logger
{
	if (logger) {
		// Save the current logger
		self.currentLogger = logger;
		// Call setLoger with the adapter and save the prev Logger
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
