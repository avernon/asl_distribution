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

#ifndef AJNSNOTIFICATIONENUMS_H_
#define AJNSNOTIFICATIONENUMS_H_

/**
 AJNSNotificationEnums class
 */
@interface AJNSNotificationEnums : NSObject

/**
 @enum AJNSNotificationMessageType enum
 @abstract AJNSNotificationMessageType DBus request status return values.
 */
typedef NS_ENUM (NSInteger, AJNSNotificationMessageType) {
	/** EMERGENCY - Urgent Message */
	EMERGENCY = 0,
	/** WARNING  - Warning Message */
	WARNING = 1,
	/** INFO - Informational Message */
	INFO = 2,
	/** MESSAGE_TYPE_CNT  - Number of Message Types Defined */
	MESSAGE_TYPE_CNT = 3,
	UNSET = 4
};

/**
 Convet AJNSNotificationMessageType to an NSString format
 @param ajnsNMessageType DBus request status
 @return message type in an NSString format(Capital letters)
 */
+ (NSString *)AJNSMessageTypeToString:(AJNSNotificationMessageType)msgType;

@end
#endif
