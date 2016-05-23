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

#import "AJNAboutServiceApi.h"
#import "AboutServiceApi.h"
#import "PropertyStore.h"
#import "AJNPropertyStore.h"

@interface AJNAboutServiceApi ()
@property (nonatomic) ajn::services::AboutPropertyStoreImpl *handle;

- (id)init;

@end

@implementation AJNAboutServiceApi

// Destroy the instance after finished
- (void)destroyInstance
{
	[super unregister];
	ajn::services::AboutServiceApi::DestroyInstance();
	if (self.handle) {
		delete self.handle;
		self.handle = NULL;
	}
}

+ (id)sharedInstance
{
	static AJNAboutServiceApi *ajnAboutServiceApi;
	static dispatch_once_t donce;
	dispatch_once(&donce, ^{
	    ajnAboutServiceApi = [[self alloc] init];
	});
	return ajnAboutServiceApi;
}

- (id)init
{
	if (self = [super init]) {
	}
	return self;
}

- (void)startWithBus:(AJNBusAttachment *)bus
    andPropertyStore:(AJNAboutPropertyStoreImpl *)store
{
	if (self.isServiceStarted) {
         NSLog(@"[%@] [%@] Service already started", @"DEBUG", [[self class] description]);

		return;
	}
	self.handle =  [store getHandle];
	[super registerBus:bus andPropertystore:store];
	ajn::services::AboutServiceApi::Init(*(ajn::BusAttachment *)bus.handle, *self.handle);
	ajn::services::AboutServiceApi::getInstance();
}

- (ajn::services::AboutPropertyStoreImpl *)getPropertyStore
{
	return self.handle;
}

@end
