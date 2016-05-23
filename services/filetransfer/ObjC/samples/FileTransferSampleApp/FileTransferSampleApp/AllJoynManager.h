/******************************************************************************
 * Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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
#import "AllJoynFramework/AJNBusAttachment.h"
#import "AllJoynFramework/AJNStatus.h"
#import "ConnectionSateChangedDelegate.h"

/*
 * This class handles everything associated with AllJoyn by creating sessions, joining exisiting sessions,
 * leaving sessions, and keeping tracked of peers that join the session. This class is also responsible for
 * notifying the ViewController class of any connection state change events that occur so they can be shown
 * to the user.
 */
@interface AllJoynManager : NSObject <AJNSessionPortListener, AJNSessionListener, AJNBusListener>

@property (nonatomic, strong) id<ConnectionSateChangedDelegate>connectionStateChangedDelegate;
@property (nonatomic, strong) NSMutableArray *peers;
@property (nonatomic, strong) AJNBusAttachment *bus;
@property (nonatomic) AJNSessionId sessionID;

-(id)init;
-(void)createSession;
-(void)joinSession;
-(void)disconnect;
-(void)didAddMemberNamed:(NSString *)memberName toSession:(AJNSessionId)sessionId;
-(void)sessionWasLost:(AJNSessionId)sessionId;

@end
