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

#import "ConfigServiceListener.h"
#import "alljoyn/about/AJNAboutServiceApi.h"
#import "alljoyn/config/AJCFGConfigLogger.h"

@interface ConfigServiceListener ()

@property AJCFGPropertyStoreImpl *propertyStore;

@property AJNBusAttachment *bus;

@end

@implementation ConfigServiceListener

- (id)initWithPropertyStore:(AJCFGPropertyStoreImpl *)propertyStore andBus:(AJNBusAttachment *)bus
{
	self = [super init];
	if (self) {
		self.propertyStore = propertyStore;
		self.bus = bus;
	}
	return self;
}

- (QStatus)restart
{
	[[[AJCFGConfigLogger sharedInstance] logger] debugTag:[[self class] description] text:@"Restart has been called !"];
	return ER_OK;
}

- (QStatus)factoryReset
{
	[[[AJCFGConfigLogger sharedInstance] logger] debugTag:[[self class] description] text:@"Factory Reset called"];
    
	[self.propertyStore factoryReset];
    
	[self.bus clearKeyStore];
    
	return [[AJNAboutServiceApi sharedInstance] announce];
}

- (QStatus)setPassphrase:(NSString *)daemonRealm withPasscode:(NSString *)passcode
{
	QStatus status = [self.propertyStore setPasscode:passcode];
    
	[self.bus clearKeyStore];
    
	return status;
}

@end
