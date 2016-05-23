/******************************************************************************
 * Copyright (c) 2015, AllSeen Alliance. All rights reserved.
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

#import "LSFControllerSystemManager.h"
#import "LSFController.h"

@interface LSFControllerSystemManager()

@property (nonatomic, strong) LSFController *controller;
@property (nonatomic, strong) NSString *DEVICE_ID_KEY;
@property (nonatomic, strong) NSString *APP_ID_KEY;

@end

@implementation LSFControllerSystemManager

@synthesize controllerStarted = _controllerStarted;
@synthesize controller = _controller;
@synthesize DEVICE_ID_KEY = _DEVICE_ID_KEY;
@synthesize APP_ID_KEY = _APP_ID_KEY;

+(LSFControllerSystemManager *)getControllerSystemManager
{
    static LSFControllerSystemManager *cssManager = nil;
    static dispatch_once_t onceToken;

    dispatch_once(&onceToken, ^{
        cssManager = [[self alloc] init];
    });

    return cssManager;
}

-(id)init
{
    self = [super init];

    if (self)
    {
        self.controllerStarted = NO;
        self.controller = [[LSFController alloc] initWithControllerServiceDelegate: self];
        self.DEVICE_ID_KEY = @"CONTROLLER_DEVICE_ID";
        self.APP_ID_KEY = @"CONTROLLER_APP_ID";
    }

    return self;
}

-(void)startController
{
    self.controllerStarted = YES;

    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
        [self.controller startControllerWithKeyStoreFilePath: @"Documents"];
    });
}

-(void)stopController
{
    self.controllerStarted = NO;

    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
        [self.controller stopController];
    });
}

/*
 * LSFControllerServiceDelegate implementation
 */
-(NSString *)getControllerDefaultDeviceID: (NSString *)randomDeviceID
{
    NSLog(@"ViewController - getControllerDefaultDeviceID() executing");

    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSString *savedDeviceID = [userDefaults stringForKey: self.DEVICE_ID_KEY];
    NSLog(@"savedDeviceID returned from NSUserDefaults = %@", savedDeviceID);

    if (savedDeviceID == nil)
    {
        NSLog(@"savedDeviceID not found in NSUserDefaults");
        savedDeviceID = randomDeviceID;
        [userDefaults setObject: savedDeviceID forKey: self.DEVICE_ID_KEY];
        NSLog(@"savedDeviceID = %@", savedDeviceID);
    }

    return savedDeviceID;
}

-(NSString *)getControllerDefaultAppID: (NSString *)randomAppID
{
    NSLog(@"ViewController - getControllerDefaultAppID() executing");

    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSString *savedAppID = [userDefaults stringForKey: self.APP_ID_KEY];
    NSLog(@"savedAppID returned from NSUserDefaults = %@", savedAppID);

    if (savedAppID == nil)
    {
        NSLog(@"savedAppID not found in NSUserDefaults");
        savedAppID = randomAppID;
        [userDefaults setObject: savedAppID forKey: self.APP_ID_KEY];
        NSLog(@"savedAppID = %@", savedAppID);
    }

    return savedAppID;
}

-(uint64_t)getMacAddress
{
    NSLog(@"ViewController - getMacAddress() executing");

    uint64_t returnValue = 0;

    for (int i = 0; i < 6; i++)
    {
        uint64_t val = arc4random_uniform(255);
        returnValue = ((returnValue << 8) | val);
    }
    
    return returnValue;
}

@end

