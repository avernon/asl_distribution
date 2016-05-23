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

#import "LSFGroupsAddLampsTableViewController.h"
#import "LSFUtilityFunctions.h"
#import <LSFSDKLightingDirector.h>

@interface LSFGroupsAddLampsTableViewController ()

@property (nonatomic, strong) NSArray *members;
@property (nonatomic, strong) NSMutableArray *lampsGroupsArray;
@property (nonatomic, strong) NSMutableArray *selectedRows;

-(void)leaderModelChangedNotificationReceived: (NSNotification *)notification;
-(void)buildTableArray;
-(void)modifyAllRows: (BOOL)isSelected;
-(void)processSelectedRows;
-(void)checkGroupCapability: (LSFSDKCapabilityData *)capability;
-(void)createLampGroup;

@end

@implementation LSFGroupsAddLampsTableViewController

@synthesize groupName = _groupName;
@synthesize members = _members;
@synthesize lampsGroupsArray = _lampsGroupsArray;
@synthesize selectedRows = _selectedRows;

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    //Set notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];

    //Initialize selected rows array
    self.selectedRows = [[NSMutableArray alloc] init];

    //Load UI
    [self buildTableArray];
    [self.tableView reloadData];
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
 * Notification Handler
 */
-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification
{
    LSFSDKController *leaderModel = [notification.userInfo valueForKey: @"leader"];
    if (![leaderModel connected])
    {
        [self dismissViewControllerAnimated: YES completion: nil];
    }
}

/*
 * UITableViewDatasource Protocol Implementation
 */
-(NSInteger)tableView: (UITableView *)tableView numberOfRowsInSection: (NSInteger)section
{
    return [self.lampsGroupsArray count];
}

-(UITableViewCell *)tableView: (UITableView *)tableView cellForRowAtIndexPath: (NSIndexPath *)indexPath
{
    LSFSDKGroupMember *member = [self.lampsGroupsArray objectAtIndex: [indexPath row]];
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: @"AddLampsGroup" forIndexPath:indexPath];

    if ([member isKindOfClass: [LSFSDKGroup class]])
    {
        cell.textLabel.text = [member name];
        cell.imageView.image = [UIImage imageNamed:@"groups_off_icon.png"];
        cell.accessoryType = UITableViewCellAccessoryNone;
    }
    if ([member isKindOfClass: [LSFSDKLamp class]])
    {
        cell.textLabel.text = [member name];
        cell.imageView.image = [UIImage imageNamed:@"lamps_off_icon.png"];
        cell.accessoryType = UITableViewCellAccessoryNone;
    }

    return cell;
}

-(void)tableView: (UITableView *)tableView didSelectRowAtIndexPath: (NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];

    if (cell.accessoryType == UITableViewCellAccessoryCheckmark)
    {
        cell.accessoryType = UITableViewCellAccessoryNone;
        [self.selectedRows removeObject: indexPath];
    }
    else
    {
        cell.accessoryType = UITableViewCellAccessoryCheckmark;
        [self.selectedRows addObject: indexPath];
    }

    [self.tableView deselectRowAtIndexPath: indexPath animated: YES];
}

-(NSString *)tableView: (UITableView *)tableView titleForHeaderInSection: (NSInteger)section
{
    return @"Select the lamps in this group";
}

/*
 * Button action handlers
 */
-(IBAction)selectAllButtonPressed: (id)sender
{
    [self modifyAllRows: YES];
}

-(IBAction)clearAllButtonPressed: (id)sender
{
    [self modifyAllRows: NO];
}

-(IBAction)doneButtonPressed: (id)sender
{
    if ([self.selectedRows count] == 0)
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                        message: @"You must select at least one lamp or group to create a group."
                                                       delegate: nil
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];
    }
    else
    {
        [self processSelectedRows];
    }
}

/*
 * Private functions
 */
-(void)buildTableArray
{
    NSMutableArray *groupsArray = [[NSMutableArray alloc] initWithArray: [[LSFSDKLightingDirector getLightingDirector] groups]];

    for (LSFSDKGroup *group in groupsArray)
    {
        if ([group isAllLampsGroup])
        {
            [groupsArray removeObject: group];
            break;
        }
    }

    NSMutableArray *lampsArray = [[NSMutableArray alloc] initWithArray: [[LSFSDKLightingDirector getLightingDirector] lamps]];

    self.lampsGroupsArray = [NSMutableArray arrayWithArray: [LSFUtilityFunctions sortLightingItemsByName: groupsArray]];
    [self.lampsGroupsArray addObjectsFromArray: [LSFUtilityFunctions sortLightingItemsByName:lampsArray]];
}

-(void)modifyAllRows: (BOOL)isSelected
{
    [self.selectedRows removeAllObjects];

    for (int i = 0; i < [self.tableView numberOfSections]; i++)
    {
        for (int j = 0; j < [self.tableView numberOfRowsInSection: i]; j++)
        {
            NSUInteger ints[2] = {i, j};
            NSIndexPath *indexPath = [NSIndexPath indexPathWithIndexes: ints length: 2];

            UITableViewCell *cell = [self.tableView cellForRowAtIndexPath: indexPath];

            if (isSelected)
            {
                cell.accessoryType = UITableViewCellAccessoryCheckmark;
                [self.selectedRows addObject: indexPath];
            }
            else
            {
                cell.accessoryType = UITableViewCellAccessoryNone;
            }
        }
    }
}

-(void)processSelectedRows
{
    LSFSDKCapabilityData *capabilityData = [[LSFSDKCapabilityData alloc] init];
    NSMutableArray *groupMembers = [[NSMutableArray alloc] init];

    for (NSIndexPath *indexPath in self.selectedRows)
    {
        LSFSDKGroupMember *groupMember = [self.lampsGroupsArray objectAtIndex: indexPath.row];

        [groupMembers addObject: groupMember];
        [capabilityData includeData: [groupMember getCapabilities]];

    }

    self.members = [[NSArray alloc] initWithArray: groupMembers];
    [self checkGroupCapability: capabilityData];
}

-(void)checkGroupCapability: (LSFSDKCapabilityData *)capability
{
    if ([capability isMixed])
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Mixing Lamp Types"
                                                        message: @"Warning! You are creating a group that contains lamps of different types. Some properties may not be supported for all lamps in the group.\n\nFor example, you may add both color and white lamps to a group. The Sample App will allow you to set the color for the group, but this won't have any effect on the white lamps."
                                                       delegate: self
                                              cancelButtonTitle: @"No"
                                              otherButtonTitles: @"Yes", nil];
        [alert show];
    }
    else
    {
        [self createLampGroup];
    }
}

-(void)createLampGroup
{
    dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
        [[LSFSDKLightingDirector getLightingDirector] createGroupWithMembers: self.members groupName: self.groupName];
    });

    [self dismissViewControllerAnimated: YES completion: nil];
}

/*
 * UIAlertViewDelegate implementation
 */
-(void)alertView: (UIAlertView *)alertView clickedButtonAtIndex: (NSInteger)buttonIndex
{
    if (buttonIndex == 0)
    {
        [alertView dismissWithClickedButtonIndex: 0 animated: NO];
    }

    if (buttonIndex == 1)
    {
        [alertView dismissWithClickedButtonIndex: 1 animated: NO];
        [self createLampGroup];
    }
}

@end
