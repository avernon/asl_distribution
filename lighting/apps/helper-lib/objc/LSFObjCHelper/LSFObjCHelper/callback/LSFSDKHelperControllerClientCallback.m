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

#import "LSFSDKHelperControllerClientCallback.h"
#import "LSFSDKLightingSystemManager.h"
#import "LSFSDKAllJoynManager.h"

@interface LSFSDKHelperControllerClientCallback()

@property (nonatomic, strong) LSFSDKLightingSystemManager *manager;

-(void)postOnConnectedControllerID: (NSString *)controllerID controllerName: (NSString *)controllerName withDelay: (int)delay;
-(void)postOnDisconnectedControllerID: (NSString *)controllerID controllerName: (NSString *)controllerName withDelay: (int)delay;
-(void)postGetAllLampIDs;
-(void)postGetAllLampGroupIDs;
-(void)postGetAllPresetIDs;
-(void)postGetAllSceneElementIDs;
-(void)postGetAllSceneIDs;
-(void)postGetAllMasterSceneIDs;
-(void)postGetAllTransitionEffectIDs;
-(void)postGetAllPulseEffectIDs;
-(void)postSendControllerChanged;

@end

@implementation LSFSDKHelperControllerClientCallback

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
 * Implementation of LSFControllerClientCallbackDelegate
 */
-(void)connectedToControllerServiceWithID: (NSString *)controllerServiceID andName: (NSString *)controllerServiceName
{
    NSLog(@"Connected to Controller Service with name: %@ and ID: %@", controllerServiceName, controllerServiceID);

    [LSFSDKAllJoynManager setControllerConnected: YES];
    [[LSFSDKAllJoynManager getControllerServiceManager] getControllerServiceVersion];

    [self postOnConnectedControllerID:controllerServiceID controllerName:controllerServiceName withDelay:0];

    [self postGetAllLampIDs];
    [self postGetAllLampGroupIDs];
    [self postGetAllPresetIDs];
    [self postGetAllTransitionEffectIDs];
    [self postGetAllPulseEffectIDs];
    [self postGetAllSceneElementIDs];
    [self postGetAllSceneIDs];
    [self postGetAllMasterSceneIDs];
}

-(void)connectToControllerServiceFailedForID: (NSString *)controllerServiceID andName: (NSString *)controllerServiceName
{
    NSLog(@"Connect to Controller Service with name: %@ and ID: %@ failed", controllerServiceName, controllerServiceID);
    [LSFSDKAllJoynManager setControllerConnected: NO];
    [self postOnDisconnectedControllerID:controllerServiceID controllerName:controllerServiceName withDelay:0];
}

-(void)disconnectedFromControllerServiceWithID: (NSString *)controllerServiceID andName: (NSString *)controllerServiceName
{
    NSLog(@"Disconnected from Controller Service with name: %@ and ID: %@", controllerServiceName, controllerServiceID);
    [LSFSDKAllJoynManager setControllerConnected: NO];
    [self postOnDisconnectedControllerID:controllerServiceID controllerName:controllerServiceName withDelay:0];
}

-(void)controllerClientError: (NSArray *)ec
{
    NSLog(@"Controller client experienced the following errors: ");

    for (NSNumber *error in ec)
    {
        NSLog(@"%i", [error intValue]);
    }

    dispatch_async(self.manager.dispatchQueue, ^{
        [[self.manager controllerManager] sendErrorEventWithName: @"controllerClientErrorCB" andErrorCodes: ec];
    });
}

/*
 * Private functions
 */
-(void)postOnConnectedControllerID: (NSString *)controllerID controllerName: (NSString *)controllerName withDelay: (int)delay
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delay * NSEC_PER_SEC)), self.manager.dispatchQueue, ^{
        LSFControllerModel *leaderModel = [[self.manager.controllerManager getLeader] getControllerDataModel];

        if  (![leaderModel.theID isEqualToString: controllerID] || !leaderModel.connected)
        {
            leaderModel.theID = controllerID;
            leaderModel.name = controllerName;
            leaderModel.connected = YES;
            leaderModel.timestamp = (long long)([[NSDate date] timeIntervalSince1970] * 1000);

            [self postSendControllerChanged];
        }
    });
}

-(void)postOnDisconnectedControllerID: (NSString *)controllerID controllerName: (NSString *)controllerName withDelay: (int)delay
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delay * NSEC_PER_SEC)), self.manager.dispatchQueue, ^{
        [LSFSDKAllJoynManager setControllerServiceLeaderVersion: 0];

        LSFControllerModel *leaderModel = [[self.manager.controllerManager getLeader] getControllerDataModel];

        if ([leaderModel.theID isEqualToString: controllerID] && leaderModel.connected)
        {
            leaderModel.name = @"[Controller not found]";
            leaderModel.controllerVersion = 0;
            leaderModel.connected = NO;
            leaderModel.timestamp = (long long)([[NSDate date] timeIntervalSince1970] * 1000);

            [self postSendControllerChanged];
        }
    });
}

-(void)postGetAllLampIDs
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.1 * NSEC_PER_SEC), self.manager.dispatchQueue, ^{
        [[LSFSDKAllJoynManager getLampManager] getAllLampIDs];
    });
}

-(void)postGetAllLampGroupIDs
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.2 * NSEC_PER_SEC), self.manager.dispatchQueue, ^{
        [[LSFSDKAllJoynManager getGroupManager] getAllLampGroupIDs];
    });
}

-(void)postGetAllPresetIDs
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.3 * NSEC_PER_SEC), self.manager.dispatchQueue, ^{
        [[LSFSDKAllJoynManager getPresetManager] getAllPresetIDs];
    });
}

-(void)postGetAllSceneElementIDs
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.4 * NSEC_PER_SEC), self.manager.dispatchQueue, ^{
        [[LSFSDKAllJoynManager getSceneElementManager] getAllSceneElementIDs];
    });
}

-(void)postGetAllSceneIDs
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.5 * NSEC_PER_SEC), self.manager.dispatchQueue, ^{
        [self doGetAllSceneIDs];
    });
}

-(void)doGetAllSceneIDs
{
    // only get Scenes after the Controller version is known
    if ([LSFSDKAllJoynManager getControllerServiceLeaderVersion] > 0)
    {
        [[LSFSDKAllJoynManager getSceneManager] getAllSceneIDs];
    }
    else
    {
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.3 * NSEC_PER_SEC), self.manager.dispatchQueue, ^{
            [self doGetAllSceneIDs];
        });
    }
}

-(void)postGetAllMasterSceneIDs
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.6 * NSEC_PER_SEC), self.manager.dispatchQueue, ^{
        [[LSFSDKAllJoynManager getMasterSceneManager] getAllMasterSceneIDs];
    });
}

-(void)postGetAllTransitionEffectIDs
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.7 * NSEC_PER_SEC), self.manager.dispatchQueue, ^{
        [[LSFSDKAllJoynManager getTransitionEffectManager] getAllTransitionEffectIDs];
    });
}

-(void)postGetAllPulseEffectIDs
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.8 * NSEC_PER_SEC), self.manager.dispatchQueue, ^{
        [[LSFSDKAllJoynManager getPulseEffectManager] getAllPulseEffectIDs];
    });
}

-(void)postSendControllerChanged
{
    dispatch_async(self.manager.dispatchQueue, ^{
        [[self.manager controllerManager] sendLeaderStateChangedEvent];
    });
}

@end
