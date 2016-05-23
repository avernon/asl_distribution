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

#import "AJCPSControlPanelControllerUnit.h"
#import "alljoyn/about/AJNConvertUtil.h"
#import "AJCPSControlPanelDevice.h"
#import "AJCPSNotificationAction.h"
#import "AJCPSHttpControl.h"
#import "AJCPSControlPanel.h"

@interface AJCPSControlPanelControllerUnit ()

@property (nonatomic) ajn::services::ControlPanelControllerUnit *handle;

@end


@implementation AJCPSControlPanelControllerUnit

- (id)initWithHandle:(ajn::services::ControlPanelControllerUnit *)handle
{
	self = [super init];
	if (self) {
		self.handle = handle;
	}
	return self;
}

- (id)initControlPanelControllerUnit:(NSString *)unitName device:(AJCPSControlPanelDevice *)device
{
	self = [super init];
	if (self) {
		self.handle = new ajn::services::ControlPanelControllerUnit([AJNConvertUtil convertNSStringToQCCString:unitName], [device handle]);
	}
	return self;
}

- (QStatus)addHttpControl:(NSString *)objectPath
{
	return self.handle->addHttpControl([AJNConvertUtil convertNSStringToQCCString:objectPath]);
}

- (QStatus)addControlPanel:(NSString *)objectPath panelName:(NSString *)panelName
{
	return self.handle->addControlPanel([AJNConvertUtil convertNSStringToQCCString:objectPath], [AJNConvertUtil convertNSStringToQCCString:panelName]);
}

- (QStatus)addNotificationAction:(NSString *)objectPath actionName:(NSString *)actionName
{
	return self.handle->addNotificationAction([AJNConvertUtil convertNSStringToQCCString:objectPath], [AJNConvertUtil convertNSStringToQCCString:actionName]);
}

- (QStatus)removeNotificationAction:(NSString *)actionName
{
	return self.handle->removeNotificationAction([AJNConvertUtil convertNSStringToQCCString:actionName]);
}

- (QStatus)registerObjects
{
	return self.handle->registerObjects();
}

- (QStatus)shutdownUnit
{
	return self.handle->shutdownUnit();
}

- (AJCPSControlPanelDevice *)getDevice
{
	return [[AJCPSControlPanelDevice alloc] initWithHandle:self.handle->getDevice()];
}

- (NSString *)getUnitName
{
	return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getUnitName()];
}

- (NSDictionary *)getControlPanels
{
	const std::map <qcc::String, ajn::services::ControlPanel *> cpp_ControlPanels = self.handle->getControlPanels();
    
	NSMutableDictionary *controlPanels = [[NSMutableDictionary alloc]init];
    
	for (std::map <qcc::String, ajn::services::ControlPanel *>::const_iterator itr = cpp_ControlPanels.begin(); itr != cpp_ControlPanels.end(); itr++) {
		NSString *key = [AJNConvertUtil convertQCCStringtoNSString:itr->first];
		AJCPSControlPanel *value = [[AJCPSControlPanel alloc] initWithHandle:itr->second];
        
		[controlPanels setObject:value forKey:key];
	}
    
	return controlPanels;
}

- (NSDictionary *)getNotificationActions
{
	const std::map <qcc::String, ajn::services::NotificationAction *> cpp_NotificationActions = self.handle->getNotificationActions();
    
	NSMutableDictionary *notificationActions = [[NSMutableDictionary alloc]init];
    
	for (std::map <qcc::String, ajn::services::NotificationAction *>::const_iterator itr = cpp_NotificationActions.begin(); itr != cpp_NotificationActions.end(); itr++) {
		NSString *key = [AJNConvertUtil convertQCCStringtoNSString:itr->first];
		AJCPSNotificationAction *value = [[AJCPSNotificationAction alloc] initWithHandle:itr->second];
        
		[notificationActions setObject:value forKey:key];
	}
    
	return notificationActions;
}

- (AJCPSControlPanel *)getControlPanel:(NSString *)panelName
{
	return [[AJCPSControlPanel alloc]initWithHandle:self.handle->getControlPanel([AJNConvertUtil convertNSStringToQCCString:panelName])];
}

- (AJCPSNotificationAction *)getNotificationAction:(NSString *)actionName
{
	return [[AJCPSNotificationAction alloc]initWithHandle:self.handle->getNotificationAction([AJNConvertUtil convertNSStringToQCCString:actionName])];
}

- (AJCPSHttpControl *)getHttpControl
{
    if (!self.handle->getHttpControl()) {
        return nil;
    }
	return [[AJCPSHttpControl alloc] initWithHandle:self.handle->getHttpControl()];
}

@end