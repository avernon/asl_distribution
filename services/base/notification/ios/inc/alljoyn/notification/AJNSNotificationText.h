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

#import <Foundation/Foundation.h>
#import "alljoyn/notification/NotificationText.h"

/**
 AJNSNotificationText class.
 */
@interface AJNSNotificationText : NSObject

///---------------------
/// @name Properties
///---------------------

/**
 Initialize notification text with language and text
 @param language The language of this notification text
 @param text The text of the notification text
 @return pointer to the noficiation text object
 */
- (AJNSNotificationText *)initWithLang:(NSString *)language andText:(NSString *)text;

/**
 * Set Language for Notification
 * @param language set the language of the notification text
 */
- (void)setLanguage:(NSString *)language;

/**
 * Get Language for Notification
 * @return language of this notification text
 */
- (NSString *)getLanguage;

/**
 * Set Text for Notification
 * @param text set the text for this notification text
 */
- (void)setText:(NSString *)text;

/**
 * Get Text for Notification
 * @return text
 */
- (NSString *)getText;

@property (nonatomic, readonly)ajn::services::NotificationText * handle;

@end
