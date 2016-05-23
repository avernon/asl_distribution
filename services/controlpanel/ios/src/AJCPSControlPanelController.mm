/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#import "AJCPSControlPanelController.h"
#import "alljoyn/about/AJNConvertUtil.h"

@interface AJCPSControlPanelController ()
@property (nonatomic) ajn::services::ControlPanelController *handle;
@end

@implementation AJCPSControlPanelController

- (id)init {
    self = [super init];
	if (self) {
		self.handle = new ajn::services::ControlPanelController();
	}
	return self;
}

- (id)initWithHandle:(ajn::services::ControlPanelController *)handle
{
	self = [super init];
	if (self) {
		self.handle = handle;
	}
	return self;
}

- (AJCPSControlPanelDevice *)createControllableDevice:(NSString *)deviceBusName ObjectDescs:(NSDictionary *)objectDescs
{
	ajn::services::AnnounceHandler::ObjectDescriptions *cpp_ObjectDescs = new ajn::services::AnnounceHandler::ObjectDescriptions;
    
	for (NSString *key in objectDescs) {
		NSArray *strings = [objectDescs objectForKey:key];
        
		std::vector <qcc::String> cpp_strings;
        
		for (NSString *string in strings) {
			cpp_strings.push_back([AJNConvertUtil convertNSStringToQCCString:string]);
		}
        
		cpp_ObjectDescs->insert(std::make_pair([AJNConvertUtil convertNSStringToQCCString:key], cpp_strings));
	}
    
    
	return [[AJCPSControlPanelDevice alloc]initWithHandle:self.handle->createControllableDevice([AJNConvertUtil convertNSStringToQCCString:deviceBusName], *cpp_ObjectDescs)];
}

- (AJCPSControlPanelDevice *)getControllableDevice:(NSString *)deviceBusName
{
	return [[AJCPSControlPanelDevice alloc]initWithHandle:self.handle->getControllableDevice([AJNConvertUtil convertNSStringToQCCString:deviceBusName])];
}

- (QStatus)deleteControllableDevice:(NSString *)deviceBusName
{
	return self.handle->deleteControllableDevice([AJNConvertUtil convertNSStringToQCCString:deviceBusName]);
}

- (QStatus)deleteAllControllableDevices
{
	return self.handle->deleteAllControllableDevices();
}

- (NSDictionary *)getControllableDevices
{
	std::map <qcc::String, ajn::services::ControlPanelDevice *> cpp_ControllableDevices =  self.handle->getControllableDevices();
    
	NSMutableDictionary *controllableDevices = [[NSMutableDictionary alloc]init];
    
	for (std::map <qcc::String, ajn::services::ControlPanelDevice *>::const_iterator itr = cpp_ControllableDevices.begin(); itr != cpp_ControllableDevices.end(); itr++) {
		NSString *key = [AJNConvertUtil convertQCCStringtoNSString:itr->first];
		AJCPSControlPanelDevice *value = [[AJCPSControlPanelDevice alloc] initWithHandle:itr->second];
        
		[controllableDevices setObject:value forKey:key];
	}
    
	return controllableDevices;
}

@end