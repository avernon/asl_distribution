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

#import "LSFSampleControllerClientCallback.h"
#import "LSFAllJoynManager.h"
#import "LSFDispatchQueue.h"
#import "LSFControllerModel.h"
#import "LSFEnums.h"
#import "LSFLampModelContainer.h"
#import "LSFGroupModelContainer.h"
#import "LSFSceneModelContainer.h"
#import "LSFMasterSceneModelContainer.h"
#import "LSFPresetModelContainer.h"
#import "LSFTabManager.h"

@interface LSFSampleControllerClientCallback()

@property (nonatomic, strong) dispatch_queue_t queue;

-(void)postUpdateControllerID: (NSString *)controllerID controllerName: (NSString *)controllerName;
-(void)postGetAllLampIDs;
-(void)postGetAllLampGroupIDs;
-(void)postGetAllPresetIDs;
-(void)postGetAllSceneIDs;
-(void)postGetAllMasterSceneIDs;
-(void)clearModels;

@end

@implementation LSFSampleControllerClientCallback

@synthesize queue = _queue;

-(id)init
{
    self = [super init];
    
    if (self)
    {
        self.queue = ([LSFDispatchQueue getDispatchQueue]).queue;
    }
    
    return self;
}

/*
 * Implementation of LSFControllerClientCallbackDelegate
 */
-(void)connectedToControllerServiceWithID: (NSString *)controllerServiceID andName: (NSString *)controllerServiceName
{
    NSLog(@"Connected to Controller Service with name: %@ and ID: %@", controllerServiceName, controllerServiceID);

    LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
    ajManager.isConnectedToController = YES;

    dispatch_async(dispatch_get_main_queue(), ^{
        NSNumber *controllerStatus = [[NSNumber alloc] initWithInt: Connected];
        NSDictionary *userInfoDict = [[NSDictionary alloc] initWithObjects: [[NSArray alloc] initWithObjects: controllerStatus, nil] forKeys: [[NSArray alloc] initWithObjects: @"status", nil]];
        [[NSNotificationCenter defaultCenter] postNotificationName: @"ControllerNotification" object: self userInfo: userInfoDict];
    });
    
    dispatch_async(self.queue, ^{
        [self postUpdateControllerID: controllerServiceID controllerName: controllerServiceName];
        [self postGetAllLampIDs];
        [self postGetAllLampGroupIDs];
        [self postGetAllPresetIDs];
        [self postGetAllSceneIDs];
        [self postGetAllMasterSceneIDs];
    });
}

-(void)connectToControllerServiceFailedForID: (NSString *)controllerServiceID andName: (NSString *)controllerServiceName
{
    NSLog(@"Connect to Controller Service with name: %@ and ID: %@ failed", controllerServiceName, controllerServiceID);
    ([LSFAllJoynManager getAllJoynManager]).isConnectedToController = NO;
}

-(void)disconnectedFromControllerServiceWithID: (NSString *)controllerServiceID andName: (NSString *)controllerServiceName
{
    NSLog(@"Disconnected from Controller Service with name: %@ and ID: %@", controllerServiceName, controllerServiceID);
    ([LSFAllJoynManager getAllJoynManager]).isConnectedToController = NO;

    [self clearModels];

    dispatch_async(dispatch_get_main_queue(), ^{
        NSNumber *controllerStatus = [[NSNumber alloc] initWithInt: Disconnected];
        NSDictionary *userInfoDict = [[NSDictionary alloc] initWithObjects: [[NSArray alloc] initWithObjects: controllerStatus, nil] forKeys: [[NSArray alloc] initWithObjects: @"status", nil]];
        [[NSNotificationCenter defaultCenter] postNotificationName: @"ControllerNotification" object: self userInfo: userInfoDict];
    });
}

-(void)controllerClientError: (NSArray *)ec
{
    NSLog(@"Controller client experienced the following errors: ");
    
    for (NSNumber *error in ec)
    {
        NSLog(@"%i", [error intValue]);
    }
}

/*
 * Private functions
 */
-(void)postUpdateControllerID: (NSString *)controllerID controllerName: (NSString *)controllerName
{
    LSFControllerModel *controllerModel = [LSFControllerModel getControllerModel];
    controllerModel.theID = controllerID;
    controllerModel.name = controllerName;
    controllerModel.timestamp = (long long)([[NSDate date] timeIntervalSince1970] * 1000);
}

-(void)postGetAllLampIDs
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.1 * NSEC_PER_SEC), ([LSFDispatchQueue getDispatchQueue]).queue, ^{
        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
        [ajManager.lsfLampManager getAllLampIDs];
    });
}

-(void)postGetAllLampGroupIDs
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.2 * NSEC_PER_SEC), ([LSFDispatchQueue getDispatchQueue]).queue, ^{
        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
        [ajManager.lsfLampGroupManager getAllLampGroupIDs];
    });
}

-(void)postGetAllPresetIDs
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.3 * NSEC_PER_SEC), ([LSFDispatchQueue getDispatchQueue]).queue, ^{
        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
        [ajManager.lsfPresetManager getAllPresetIDs];
    });
}

-(void)postGetAllSceneIDs
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.4 * NSEC_PER_SEC), ([LSFDispatchQueue getDispatchQueue]).queue, ^{
        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
        [ajManager.lsfSceneManager getAllSceneIDs];
    });
}

-(void)postGetAllMasterSceneIDs
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.5 * NSEC_PER_SEC), ([LSFDispatchQueue getDispatchQueue]).queue, ^{
        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
        [ajManager.lsfMasterSceneManager getAllMasterSceneIDs];
    });
}

-(void)clearModels
{
    LSFLampModelContainer *lampContainer = [LSFLampModelContainer getLampModelContainer];
    LSFGroupModelContainer *groupContainer = [LSFGroupModelContainer getGroupModelContainer];
    LSFSceneModelContainer *sceneContainer = [LSFSceneModelContainer getSceneModelContainer];
    LSFMasterSceneModelContainer *masterSceneContainer = [LSFMasterSceneModelContainer getMasterSceneModelContainer];
    LSFPresetModelContainer *presetContainer = [LSFPresetModelContainer getPresetModelContainer];

    [lampContainer.lampContainer removeAllObjects];
    [groupContainer.groupContainer removeAllObjects];
    [sceneContainer.sceneContainer removeAllObjects];
    [masterSceneContainer.masterScenesContainer removeAllObjects];
    [presetContainer.presetContainer removeAllObjects];

    LSFTabManager *tabManager = [LSFTabManager getTabManager];
    [tabManager updateLampsTab];
    [tabManager updateGroupsTab];
    [tabManager updateScenesTab];
}

@end
