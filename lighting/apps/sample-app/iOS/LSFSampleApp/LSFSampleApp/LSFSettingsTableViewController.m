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

#import "LSFSettingsTableViewController.h"
#import "LSFSettingsInfoViewController.h"
#import "LSFScenesV1ModuleProxy.h"
#import <LSFSDKLightingDirector.h>
#import <LSFSDKLightingController.h>

@interface LSFSettingsTableViewController ()

-(void)leaderModelChangedNotificationReceived: (NSNotification *)notification;

@end

@implementation LSFSettingsTableViewController

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    //Set controller notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];

    // scenes v1 installed? label
    [self.scenesV1ModuleLabel setText: ([[[LSFScenesV1ModuleProxy getProxy] scenesV1Delegate] isInstalled] ? @"Installed" : @"Not Installed")];

    // controller label
    [self.controllerNameLabel setText: [NSString stringWithFormat: @"%@", [[[LSFSDKLightingDirector getLightingDirector] leadController] name]]];

    if ([[LSFSDKLightingController getLightingController] isRunning])
    {
        [self.controllerNameLabel setText: [NSString stringWithFormat: @"%@ (V%u)", self.controllerNameLabel.text, [[[LSFSDKLightingDirector getLightingDirector] leadController] version]]];

        self.controllerOnOffSwitch.on = YES;
    }
    else
    {
        self.controllerOnOffSwitch.on = NO;
    }

    self.isLeaderLabel.text = ([[LSFSDKLightingController getLightingController] isLeader]) ? @"true" : @"false";

    self.myControllerNameLabel.text = [[LSFSDKLightingController getLightingController] name];
}

-(void)viewWillDisappear: (BOOL)animated
{
    [super viewWillDisappear: animated];

    //Clear notification handler
    [[NSNotificationCenter defaultCenter] removeObserver: self];
}

-(void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

-(IBAction)controllerSwitchValueChanged: (id)sender
{
    if ([sender isOn])
    {
        NSLog(@"Starting Controller...");
        [[LSFSDKLightingController getLightingController] start];
    }
    else
    {
        NSLog(@"Stopping Controller...");
        [[LSFSDKLightingController getLightingController] stop];
    }
}

/*
 * ControllerNotification Handler
 */
-(void)leaderModelChangedNotificationReceived: (NSNotification *)notification
{
    LSFSDKController *leader = [notification.userInfo valueForKey: @"leader"];

    if ([leader connected])
    {
        [self.controllerNameLabel setText: [NSString stringWithFormat: @"%@ (V%u)", leader.name, leader.version]];
        self.isLeaderLabel.text = ([[LSFSDKLightingController getLightingController] isLeader]) ? @"true" : @"false";
    }
    else
    {
        [self.controllerNameLabel setText: [NSString stringWithFormat: @"%@", leader.name]];
        self.isLeaderLabel.text = @"false";
    }
}

/*
 * UITableViewDelegate Implementation
 */
-(void)tableView: (UITableView *)tableView didSelectRowAtIndexPath: (NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];

    switch (indexPath.section)
    {
        case 2:
        case 3:
        case 4:
            [self performSegueWithIdentifier: @"ScenesSettingInfo" sender: cell]; //reuseIdentifier = sourceCodeInfoCell
            break;
        case 5:
        default:
            break;
    }
}

/*
 * Segue Method Implementation
 */
-(void)prepareForSegue: (UIStoryboardSegue *)segue sender: (id)sender
{
    if ([segue.identifier isEqualToString: @"ScenesSettingInfo"])
    {
        NSString *cellIdentifier = [(UITableViewCell*)sender reuseIdentifier];
        LSFSettingsInfoViewController *ssivc = [segue destinationViewController];
        if ([cellIdentifier isEqualToString:@"sourceCodeInfoCell"])
        {
            ssivc.title = @"Source Code";
            ssivc.inputText = @"SourceCode";
        }
        else if ([cellIdentifier isEqualToString:@"teamInfoCell"])
        {
            ssivc.title = @"Team";
            ssivc.inputText = @"Team";
        }
        else if ([cellIdentifier isEqualToString:@"noticeInfoCell"])
        {
            ssivc.title = @"Notice";
            ssivc.inputText = @"Notice";
        }
    }
}

@end
