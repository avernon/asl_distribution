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

#import "AJNSNotificationText.h"
#import "alljoyn/about/AJNConvertUtil.h"

@interface AJNSNotificationText ()
/** cpp notificationText Handler*/
@property (nonatomic) ajn::services::NotificationText *handle;
@end

@implementation AJNSNotificationText

- (AJNSNotificationText *)initWithLang:(NSString *)language andText:(NSString *)text
{
	self = [super init];
	if (self) {
		self.handle = new ajn::services::NotificationText([AJNConvertUtil convertNSStringToQCCString:language], [AJNConvertUtil convertNSStringToQCCString:text]);
	}
	return self;
}

/**
 * Set Language for Notification
 * @param language
 */
- (void)setLanguage:(NSString *)language
{
	self.handle->setLanguage([AJNConvertUtil convertNSStringToQCCString:language]);
}

/**
 * Get Language for Notification
 * @return language
 */
- (NSString *)getLanguage
{
	return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getLanguage()];
}

/**
 * Set Text for Notification
 * @param text the text to set
 */
- (void)setText:(NSString *)text
{
	self.handle->setText([AJNConvertUtil convertNSStringToQCCString:text]);
}

/**
 * Get Text for Notification
 * @return text
 */
- (NSString *)getText
{
	return [AJNConvertUtil convertQCCStringtoNSString:(self.handle->getText())];
}

@end
