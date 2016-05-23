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
#import "LSFControllerModel.h"
#import "LSFDispatchQueue.h"
#import "LSFAllJoynManager.h"

@interface LSFSettingsTableViewController ()

-(void)controllerNameNotificationReceived: (NSNotification *)notification;

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
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(controllerNameNotificationReceived:) name: @"ControllerNameChanged" object: nil];

    [self.controllerNameLabel setText:([LSFControllerModel getControllerModel]).name];
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

/*
 * ControllerNotification Handler
 */
-(void)controllerNameNotificationReceived: (NSNotification *)notification
{
    [self.controllerNameLabel setText:([LSFControllerModel getControllerModel]).name];
}

/*
 * UITableViewDelegate Implementation
 */
-(void)tableView: (UITableView *)tableView didSelectRowAtIndexPath: (NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];

    switch (indexPath.section)
    {
        case 1:
            [self performSegueWithIdentifier: @"ScenesSettingInfo" sender: cell]; //reuseIdentifier = eulaInfoCell
            break;
        case 2:
            [self performSegueWithIdentifier: @"ScenesSettingInfo" sender: cell]; //reuseIdentifier = sourceCodeInfoCell
            break;
        case 3:
            [self performSegueWithIdentifier: @"ScenesSettingInfo" sender: cell]; //reuseIdentifier = teamInfoCell
            break;
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

        if ([cellIdentifier isEqualToString:@"eulaInfoCell"])
        {
            ssivc.title = @"EULA";
            ssivc.inputText = cellIdentifier; //TODO - forward the proper text per cellIdentifier
        }
        else if ([cellIdentifier isEqualToString:@"sourceCodeInfoCell"])
        {
            ssivc.title = @"Source Code";
            ssivc.inputText = cellIdentifier; //TODO - forward the proper text per cellIdentifier
        }
        else if ([cellIdentifier isEqualToString:@"teamInfoCell"])
        {
            ssivc.title = @"Team";
            ssivc.inputText = cellIdentifier; //TODO - forward the proper text per cellIdentifier
        }

    }
}

@end
