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

#import "LSFRootTableViewController.h"
#import "LSFLightsTableViewController.h"
#import <LSFSDKLightingDirector.h>

@interface LSFRootTableViewController ()

@property (nonatomic) BOOL wasControllerConnected;

-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification;
-(void)wifiNotificationReceived: (NSNotification *)notification;

@end

@implementation LSFRootTableViewController

@synthesize data = _data;
@synthesize wasControllerConnected = _wasControllerConnected;

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];
    self.wasControllerConnected = [[[LSFSDKLightingDirector getLightingDirector] leadController] connected];

    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(wifiNotificationReceived:) name: @"WifiNotification" object: nil];
}

-(void)viewWillDisappear: (BOOL)animated
{
    [super viewWillDisappear: animated];

    [[NSNotificationCenter defaultCenter] removeObserver: self];
}

-(void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

/*
 * Notification Handlers
 */
-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification
{
    LSFSDKController *leaderModel = [notification.userInfo valueForKey: @"leader"];
    BOOL connected = leaderModel.connected;

    if (connected != self.wasControllerConnected)
    {
        self.wasControllerConnected = connected;
        [self.data removeAllObjects];
        [self.tableView reloadData];
    }
}

-(void)wifiNotificationReceived: (NSNotification *)notification
{
    NSLog(@"LSFRootTableViewController - wifiNotificationReceived() executing");

    [self.data removeAllObjects];
    [self.tableView reloadData];
}

@end
