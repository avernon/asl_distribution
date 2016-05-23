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
#import "LSFEnums.h"
#import "LSFLightsTableViewController.h"

@interface LSFRootTableViewController ()

-(void)controllerNotificationReceived: (NSNotification *)notification;
-(void)wifiNotificationReceived: (NSNotification *)notification;

@end

@implementation LSFRootTableViewController

@synthesize data = _data;

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(controllerNotificationReceived:) name: @"ControllerNotification" object: nil];
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
 * ControllerNotification Handler
 */
-(void)controllerNotificationReceived: (NSNotification *)notification
{
    NSDictionary *userInfo = notification.userInfo;
    NSNumber *controllerStatus = [userInfo valueForKey: @"status"];

    if (controllerStatus.intValue == Connected)
    {
        NSLog(@"Controller is now connected");
    }
    else if (controllerStatus.intValue == Disconnected)
    {
        NSLog(@"Controller is now disconnected");
    }

    [self.data removeAllObjects];
    [self.tableView reloadData];
}

/*
 * WifiNotification Handler
 */
-(void)wifiNotificationReceived: (NSNotification *)notification
{
    NSLog(@"LSFRootTableViewController - wifiNotificationReceived() executing");

    [self.data removeAllObjects];
    [self.tableView reloadData];
}

@end
