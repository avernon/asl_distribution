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

#import "LSFItemListTableViewController.h"
#import <LSFSDKLightingDirector.h>

@interface LSFItemListTableViewController ()

@end

@implementation LSFItemListTableViewController

@synthesize data = _data;
@synthesize selectedIndexPath = _selectedIndexPath;

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear: animated];

    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];

    if (self.allowCancel)
    {
        UIBarButtonItem *cancelButton = [[UIBarButtonItem alloc]
                                         initWithBarButtonSystemItem:UIBarButtonSystemItemCancel
                                         target: self
                                         action: @selector(cancelButtonPressed)];

        self.navigationItem.leftBarButtonItem = cancelButton;
    }

    self.data = [[NSMutableArray alloc] init];

    [self buildTable];
    [self.tableView reloadData];
}

-(void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear: animated];
    [[NSNotificationCenter defaultCenter] removeObserver: self];
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [self.data count];
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSIndexPath *previousSelectedIndexPath = self.selectedIndexPath;
    self.selectedIndexPath = indexPath;

    if (![self.selectedIndexPath isEqual: previousSelectedIndexPath])
    {
        // uncheck previous
        UITableViewCell *previousSelectedCell = [tableView cellForRowAtIndexPath: previousSelectedIndexPath];
        previousSelectedCell.accessoryType = UITableViewCellAccessoryNone;

        // checkmark current
        UITableViewCell* cell = [tableView cellForRowAtIndexPath: self.selectedIndexPath];
        cell.accessoryType = UITableViewCellAccessoryCheckmark;
    }

    [self.tableView deselectRowAtIndexPath: indexPath animated: NO];
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Method should be overriden by subclass so cell knows how to draw itself
    return nil;
}

-(void)buildTable
{
    // Method should be overriden by subclass and populate self.data array
}

-(void)cancelButtonPressed
{
    [self dismissViewControllerAnimated: YES completion: nil];
}

-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification
{
    LSFSDKController *leaderModel = [notification.userInfo valueForKey: @"leader"];
    if (![leaderModel connected])
    {
        [self dismissViewControllerAnimated: YES completion: nil];
        [self.navigationController popToRootViewControllerAnimated: YES];
    }
}

@end
