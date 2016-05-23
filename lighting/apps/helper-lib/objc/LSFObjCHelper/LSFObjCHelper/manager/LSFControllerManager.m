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

#import "LSFControllerManager.h"
#import "LSFSDKControllerDelegate.h"

@interface LSFControllerManager()

@property (nonatomic, strong) LSFSDKController *leader;

@end

@implementation LSFControllerManager

-(id)init
{
    self = [super init];

    if (self)
    {
        self.leader = [[LSFSDKController alloc] init];
    }

    return self;
}

-(LSFSDKController *)getLeader
{
    return self.leader;
}

-(void)sendLeaderStateChangedEvent
{
    [self processPendingAdditions];
    [self processPendingRemovals];

    for (id delegate in delegates)
    {
        if ([delegate conformsToProtocol: @protocol(LSFSDKControllerDelegate)])
        {
            id<LSFSDKControllerDelegate> controllerDelegate = (id<LSFSDKControllerDelegate>)delegate;
            [controllerDelegate onLeaderChange: [self getLeader]];
        }
        else
        {
            NSLog(@"LSFControllerManager - sendLeaderStateChangedEvent() delegate does not conform to \"LSFControllerListener\" protocol.");
        }
    }
}

-(void)sendErrorEventWithName: (NSString *)name andResonseCode: (LSFResponseCode)responseCode
{
    [self processPendingAdditions];
    [self processPendingRemovals];

    [self sendErrorEvent: [[LSFSDKControllerErrorEvent alloc] initWithName: name andResponseCode: responseCode]];
}

-(void)sendErrorEventWithName: (NSString *)name andErrorCodes: (NSArray *)errorCodes
{
    LSFSDKControllerErrorEvent *errorEvent = [[LSFSDKControllerErrorEvent alloc] initWithName: name andErrorCodes: errorCodes];
    [self sendErrorEvent: errorEvent];
}

-(void)sendErrorEvent: (LSFSDKControllerErrorEvent *)errorEvent
{
    for (id delegate in delegates)
    {
        if ([delegate conformsToProtocol: @protocol(LSFSDKControllerDelegate)])
        {
            id<LSFSDKControllerDelegate> controllerDelegate = (id<LSFSDKControllerDelegate>)delegate;
            [controllerDelegate onControllerError: errorEvent];
        }
        else
        {
            NSLog(@"LSFControllerManager - sendErrorEvent() delegate does not conform to \"LSFControllerListener\" protocol.");
        }
    }
}

@end
