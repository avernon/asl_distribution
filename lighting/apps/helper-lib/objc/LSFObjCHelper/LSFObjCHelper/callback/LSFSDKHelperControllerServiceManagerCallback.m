/******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

#import "LSFSDKHelperControllerServiceManagerCallback.h"
#import "LSFSDKLightingSystemManager.h"
#import "LSFControllerModel.h"
#import "LSFSDKAllJoynManager.h"

@interface LSFSDKHelperControllerServiceManagerCallback()

@property (nonatomic, strong) LSFSDKLightingSystemManager *manager;

-(void)postSendControllerChanged;

@end

@implementation LSFSDKHelperControllerServiceManagerCallback

@synthesize manager = _manager;

-(id)initWithLightingSystemManager: (LSFSDKLightingSystemManager *)manager
{
    self = [super init];

    if (self)
    {
        self.manager = manager;
    }

    return self;
}

/*
 * Implementation of LSFControllerServiceManagerCallbackDelegate
 */
-(void)getControllerServiceVersionReply: (unsigned int)version
{
    dispatch_async(self.manager.dispatchQueue, ^{
        [LSFSDKAllJoynManager setControllerServiceLeaderVersion: version];
        [[[[self.manager controllerManager] getLeader] getControllerDataModel] setControllerVersion: version];
        [self postSendControllerChanged];
    });
}

-(void)lightingResetControllerServiceReplyWithCode: (LSFResponseCode)rc
{
    NSLog(@"LSFSampleControllerServiceManagerCallback - Lighting Controller Service Reset reply with code %i", rc);
}

-(void)controllerServiceLightingReset
{
    NSLog(@"LSFSampleControllerServiceManagerCallback - Controller Service Lighting Reset");
}

-(void)controllerServiceNameChangedForControllerID: (NSString *)controllerID andName: (NSString *)controllerName
{
    LSFControllerModel *leaderModel = [[self.manager.controllerManager getLeader] getControllerDataModel];

    if ([leaderModel.theID isEqualToString: controllerID])
    {
        leaderModel.name = controllerName;
    }

    [self postSendControllerChanged];
}

-(void)postSendControllerChanged
{
    dispatch_async(self.manager.dispatchQueue, ^{
        [[self.manager controllerManager] sendLeaderStateChangedEvent];
    });
}

@end
