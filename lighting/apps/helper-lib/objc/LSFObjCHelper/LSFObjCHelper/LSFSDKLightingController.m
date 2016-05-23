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

#import "LSFSDKLightingController.h"

@implementation LSFSDKLightingController

+(LSFSDKLightingController *)getLightingController
{
    static LSFSDKLightingController *instance = nil;
    static dispatch_once_t onceToken;

    dispatch_once(&onceToken, ^{
        instance = [[self alloc] init];
    });

    return instance;
}

-(id)init
{
    self = [super init];

    if (self)
    {
        controllerRunning = NO;
        controllerService = nil;
    }

    return self;
}

-(LightingControllerStatus)initializeWithControllerConfiguration: (id<LSFSDKLightingControllerConfiguration>)configuration
{
    if (controllerRunning || configuration == nil)
    {
        return ERROR_INIT;
    }

    controllerService = [[LSFSDKBasicControllerService alloc] initWithControllerConfiguration: configuration];
    return OK;
}

-(LightingControllerStatus)start
{
    if (controllerService != nil && controllerService.controllerConfiguration == nil)
    {
        return ERROR_INIT;
    }
    else if (controllerRunning)
    {
        return ERROR_ALREADY_RUNNING;
    }

    controllerRunning = YES;

    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
        [controllerService startControllerWithKeyStoreFilePath: [controllerService.controllerConfiguration getKeystorePath]];
    });

    return OK;
}

-(LightingControllerStatus)stop
{
    controllerRunning = NO;

    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
        [controllerService stopController];
    });

    return OK;
}

-(LightingControllerStatus)factoryReset
{
    [self stop];
    [controllerService factoryResetController];
    return OK;
}

-(LightingControllerStatus)lightingReset
{
    [self stop];
    [controllerService lightingResetController];
    return OK;
}

-(BOOL)isRunning
{
    return controllerRunning;
}

-(BOOL)isLeader
{
    return [controllerService isLeader];
}

-(NSString *)name
{
    return [controllerService name];
}

-(void)sendNetworkConnected
{
    if (controllerRunning)
    {
        [controllerService sendNetworkConnected];
    }
}

-(void)sendNetworkDisconnected
{
    if (controllerRunning)
    {
        [controllerService sendNetworkDisconnected];
    }
}

@end
