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

#import "AJCPSControlPanel.h"
#import "alljoyn/about/AJNConvertUtil.h"

@interface AJCPSControlPanel ()

@property (nonatomic) ajn::services::ControlPanel *handle;

@end

@implementation AJCPSControlPanel


- (id)initWithHandle:(ajn ::services ::ControlPanel *)handle
{
	self = [super init];
	if (self) {
		self.handle = handle;
	}
	return self;
}

// original cpp constructor: ControlPanel(LanguageSet const& languageSet, qcc::String objectPath, ControlPanelDevice* device);

- (NSString *)getPanelName
{
	return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getPanelName()];
}

- (QStatus)registerObjects:(AJNBusAttachment *)bus
{
	return self.handle->registerObjects((ajn::BusAttachment *)[bus handle]);
}

- (QStatus)unregisterObjects:(AJNBusAttachment *)bus
{
	return self.handle->unregisterObjects((ajn::BusAttachment *)[bus handle]);
}

- (AJCPSLanguageSet *)getLanguageSet
{
	return [[AJCPSLanguageSet alloc]initWithHandle:(ajn::services::LanguageSet *)&self.handle->getLanguageSet()];
}

- (AJCPSControlPanelDevice *)getDevice
{
	return [[AJCPSControlPanelDevice alloc]initWithHandle:self.handle->getDevice()];
}

- (NSString *)getObjectPath
{
	return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getObjectPath()];
}

- (AJCPSContainer *)getRootWidget:(NSString *)Language
{
    return [[AJCPSContainer alloc]initWithHandle:self.handle->getRootWidget([AJNConvertUtil convertNSStringToQCCString:Language])];
}

@end
