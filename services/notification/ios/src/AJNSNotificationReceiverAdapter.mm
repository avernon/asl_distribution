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

#import "AJNSNotificationReceiverAdapter.h"
#import "AJNSNotificationReceiver.h"
#import "alljoyn/about/AJNConvertUtil.h"

AJNSNotificationReceiverAdapter::AJNSNotificationReceiverAdapter(id <AJNSNotificationReceiver> notificationReceiverHandler)
{
	ajnsNotificationReceiverHandler = notificationReceiverHandler;
}

void AJNSNotificationReceiverAdapter::Receive(ajn::services::Notification const& notification)
{
    AJNSNotification *t_ajnsNotification = [[AJNSNotification alloc] initWithHandle:(new ajn::services::Notification(notification))];

	[t_ajnsNotification createAJNSNotificationTextArray];
	[ajnsNotificationReceiverHandler receive:t_ajnsNotification];
}

void AJNSNotificationReceiverAdapter::Dismiss(const int32_t msgId, const qcc::String appId)
{
    NSLog(@"Got Dissmiss of msgId %d and appId %@",msgId, [AJNConvertUtil convertQCCStringtoNSString:appId]);
    [ajnsNotificationReceiverHandler dismissMsgId:msgId appId:[AJNConvertUtil convertQCCStringtoNSString:appId]];
}