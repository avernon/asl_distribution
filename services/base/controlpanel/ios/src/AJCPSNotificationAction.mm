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

#import "AJCPSNotificationAction.h"
#import "alljoyn/about/AJNConvertUtil.h"
#import "AJCPSControlPanelDevice.h"

@interface AJCPSNotificationAction ()
@property (nonatomic) ajn::services::NotificationAction *handle;
@end


@implementation AJCPSNotificationAction

- (id)initWithHandle:(ajn::services::NotificationAction *)handle
{
	self = [super init];
	if (self) {
		self.handle = handle;
	}
	return self;
}

- (NSString *)getNotificationActionName
{
	return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getNotificationActionName()];
}

/**
 * Register the BusObjects for this Widget
 * @param bus - bus used to register the busObjects
 * @return status - success/failure
 */
- (QStatus)registerObjects:(AJNBusAttachment *)bus
{
	return self.handle->registerObjects((ajn::BusAttachment *)[bus handle]);
}

/**
 * Unregister the BusObjects of the NotificationAction class
 * @param bus - bus used to unregister the objects
 * @return status - success/failure
 */
- (QStatus)unregisterObjects:(AJNBusAttachment *)bus
{
	return self.handle->unregisterObjects((ajn::BusAttachment *)[bus handle]);
}

/**
 * Get the LanguageSet of the NotificationAction
 * @return
 */
- (AJCPSLanguageSet *)getLanguageSet
{
	return [[AJCPSLanguageSet alloc] initWithHandle:(ajn::services::LanguageSet *)&self.handle->getLanguageSet()];
}

/**
 * Get the Device of the NotificationAction
 * @return controlPanelDevice
 */
- (AJCPSControlPanelDevice *)getDevice
{
	return [[AJCPSControlPanelDevice alloc]initWithHandle:self.handle->getDevice()];
}

/**
 * Get the objectPath
 * @return
 */
- (NSString *)getObjectPath
{
	return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getObjectPath()];
}

/**
 * Get the RootWidget of the NotificationAction
 * @param Language - languageSet of RootWidget to retrieve
 * @return rootWidget
 */
- (AJCPSRootWidget *)getRootWidget:(NSString *)Language
{
	return [[AJCPSRootWidget alloc]initWithHandle:self.handle->getRootWidget([AJNConvertUtil convertNSStringToQCCString:Language])];
}

@end
