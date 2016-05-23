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

#import "AJCPSWidget.h"
#import "alljoyn/about/AJNConvertUtil.h"
#import "AJCPSControlPanelDevice.h"

@interface AJCPSWidget ()
@property (nonatomic) ajn::services::Widget *handle;
@end


@implementation AJCPSWidget

- (id)init
{
	return Nil; // This is an abstract class. Do Not Instantiate.
}

- (id)initWithHandle:(ajn::services::Widget *)handle
{
	self = [super init];
	if (self) {
		self.handle = handle;
        
		if (!self.handle) {
			NSLog(@"Failed getting a pointer to a Widget subclass");
			return Nil;
		}
	}
	return self;
}

- (void)dealloc
{
    // it is very important not to delete anything using widget, this is all taken care of by lower layers
}

- (AJCPSWidgetType)getWidgetType
{
	return self.handle->getWidgetType();
}

- (NSString *)getWidgetName
{
	return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getWidgetName()];
}

- (AJCPSControlPanelMode)getControlPanelMode
{
	return (AJCPSControlPanelMode)self.handle->getControlPanelMode();
}

- (const AJCPSWidget *)getRootWidget
{
	return [[AJCPSWidget alloc]initWithHandle:self.handle->getRootWidget()];
}

- (const AJCPSControlPanelDevice *)getDevice
{
	return [[AJCPSControlPanelDevice alloc] initWithHandle:self.handle->getDevice()];
}

- (const uint16_t)getInterfaceVersion
{
	return self.handle->getInterfaceVersion();
}

- (bool)getIsSecured
{
	return self.handle->getIsSecured();
}

- (bool)getIsEnabled
{
	return self.handle->getIsEnabled();
}

- (bool)getIsWritable
{
	return self.handle->getIsWritable();
}

- (uint32_t)getStates
{
	return self.handle->getStates();
}

- (uint32_t)getBgColor
{
	return self.handle->getBgColor();
}

- (NSString *)getLabel
{
	return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getLabel()];
}

- (NSArray *)getHints
{
	const std::vector <uint16_t> cpp_hints = self.handle->getHints();
	NSMutableArray *hints = [[NSMutableArray alloc]init];
    
    if (cpp_hints.size()) {
        for (int i = 0; i != cpp_hints.size(); i++) {
            [hints addObject:[NSNumber numberWithShort:cpp_hints.at(i)]];
        }
    }
	return hints;
}

- (QStatus)registerObjects:(AJNBusAttachment *)bus atObjectPath:(NSString *)objectPath
{
	ajn::BusAttachment *cpp_bus = (ajn::BusAttachment *)[bus handle];
    
	return self.handle->registerObjects(cpp_bus, [AJNConvertUtil convertNSStringToQCCString:objectPath]);
}

- (QStatus)refreshObjects:(AJNBusAttachment *)bus
{
	ajn::BusAttachment *cpp_bus = (ajn::BusAttachment *)[bus handle];
    
	return self.handle->refreshObjects(cpp_bus);
}

- (QStatus)unregisterObjects:(AJNBusAttachment *)bus
{
	ajn::BusAttachment *cpp_bus = (ajn::BusAttachment *)[bus handle];
    
	return self.handle->unregisterObjects(cpp_bus);
}

@end
