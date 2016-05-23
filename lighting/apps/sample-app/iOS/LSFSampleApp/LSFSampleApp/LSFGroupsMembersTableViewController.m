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

#import "LSFGroupsMembersTableViewController.h"
#import <LSFSDKLightingDirector.h>

@interface LSFGroupsMembersTableViewController ()

@property (nonatomic, strong) NSArray *members;
@property (nonatomic, strong) NSMutableArray *lampsGroupsArray;
@property (nonatomic, strong) NSMutableArray *selectedRows;

-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification;
-(void)groupChangedNotificationReceived: (NSNotification *)notification;
-(void)groupRemovedNotificationReceived: (NSNotification *)notification;
-(void)buildTableArray;
-(void)modifyAllRows: (BOOL)isSelected;
-(void)processSelectedRows;
-(void)checkGroupCapability: (LSFSDKCapabilityData *)capability;
-(void)createLampGroup;
-(BOOL)isParentGroup: (LSFSDKGroup *)group;

@end

@implementation LSFGroupsMembersTableViewController

@synthesize groupID = _groupID;
@synthesize lampsGroupsArray = _lampsGroupsArray;
@synthesize selectedRows = _selectedRows;

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    //Initialize selected rows array
    self.selectedRows = [[NSMutableArray alloc] init];

    //Set notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(groupChangedNotificationReceived:) name: @"LSFGroupChangedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(groupRemovedNotificationReceived:) name: @"LSFGroupRemovedNotification" object: nil];

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
 * Notification Handlers
 */
-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification
{
    LSFSDKController *leaderModel = [notification.userInfo valueForKey: @"leader"];
    if (![leaderModel connected])
    {
        [self dismissViewControllerAnimated: YES completion: nil];
    }
}

-(void)groupChangedNotificationReceived:(NSNotification *)notification
{
    LSFSDKGroup *group = [notification.userInfo valueForKey: @"group"];

    if ([self.groupID isEqualToString: [group theID]])
    {
        [self reloadGroup: group];
    }
}

-(void)groupRemovedNotificationReceived:(NSNotification *)notification
{
    LSFSDKGroup *group = [notification.userInfo valueForKey: @"group"];

    if ([self.groupID isEqualToString: [group theID]])
    {
        [self showGroupDeleted: group];
    }
}

-(void) reloadGroup: (LSFSDKGroup *)group
{
    // load UI
    [self buildTableArray];
    [self.tableView reloadData];
}

-(void)showGroupDeleted: (LSFSDKGroup *)group
{
    [self dismissViewControllerAnimated: YES completion: nil];

    dispatch_async(dispatch_get_main_queue(), ^{
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Group Not Found"
                                                        message: [NSString stringWithFormat: @"The group \"%@\" no longer exists.", [group name]]
                                                       delegate: nil
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];
    });
}

/*
 * UITableViewDataSource Protocol Implementation
 */
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [self.lampsGroupsArray count];
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    LSFSDKGroupMember *member = [self.lampsGroupsArray objectAtIndex: [indexPath row]];
    LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: self.groupID];
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: @"ModifyLampsGroup" forIndexPath:indexPath];

    if ([member isKindOfClass: [LSFSDKGroup class]])
    {
        cell.textLabel.text = [member name];
        cell.imageView.image = [UIImage imageNamed:@"groups_off_icon.png"];

        if ([group hasGroup: (LSFSDKGroup *)member])
        {
            cell.accessoryType = UITableViewCellAccessoryCheckmark;
            [self.selectedRows addObject: indexPath];
        }
        else
        {
            cell.accessoryType = UITableViewCellAccessoryNone;
        }

    }
    if ([member isKindOfClass: [LSFSDKLamp class]])
    {
        cell.textLabel.text = [member name];
        cell.imageView.image = [UIImage imageNamed:@"lamps_off_icon.png"];

        if ([group hasLamp: (LSFSDKLamp *)member])
        {
            cell.accessoryType = UITableViewCellAccessoryCheckmark;
            [self.selectedRows addObject: indexPath];
        }
        else
        {
            cell.accessoryType = UITableViewCellAccessoryNone;
        }
    }

    return cell;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath: (NSIndexPath *)indexPath
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
 * Button Event Handlers
 */
-(IBAction)cancelButtonPressed: (id)sender
{
    [self dismissViewControllerAnimated: YES completion: nil];
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

-(IBAction)selectAllButtonPressed: (id)sender
{
    [self modifyAllRows: YES];
}

-(IBAction)clearAllButtonPressed: (id)sender
{
    [self modifyAllRows: NO];
}

/*
 * Private functions
 */
-(void)buildTableArray
{
    NSMutableArray *groupsArray = [[NSMutableArray alloc] init];

    for (LSFSDKGroup *group in [[LSFSDKLightingDirector getLightingDirector] groups])
    {
        [groupsArray addObject: group];
    }

    for (LSFSDKGroup *group in [groupsArray copy])
    {
        if ([[group theID] isEqualToString: self.groupID] || [group isAllLampsGroup] || [self isParentGroup:group])
        {
            [groupsArray removeObject: group];
        }
    }

    NSMutableArray *lampsArray = [[NSMutableArray alloc] init];

    for (LSFSDKLamp *lamp in [[LSFSDKLightingDirector getLightingDirector] lamps])
    {
        [lampsArray addObject: lamp];
    }

    self.lampsGroupsArray = [NSMutableArray arrayWithArray: [self sortGroupMembersByName: groupsArray]];
    [self.lampsGroupsArray addObjectsFromArray: [self sortGroupMembersByName: lampsArray]];
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
    NSLog(@"Creating lampgroup");
    dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
        LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: self.groupID];
        [group modify: self.members];
    });

    [self dismissViewControllerAnimated: YES completion: nil];
}

-(BOOL)isParentGroup: (LSFSDKGroup *)group
{
    if (!([[group theID] isEqualToString: self.groupID]) && [group hasGroup: [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: self.groupID]])
    {
        NSLog(@"%@ is a parent of %@", [group name], [[[LSFSDKLightingDirector getLightingDirector] getGroupWithID: self.groupID] name]);
        return YES;
    }
    return NO;
}

-(NSArray*) sortGroupMembersByName: (NSArray *)data
{
    return [data sortedArrayUsingComparator: ^NSComparisonResult(id obj1, id obj2) {
        LSFSDKGroupMember *member1 = (LSFSDKGroupMember *)obj1;
        LSFSDKGroupMember *member2 = (LSFSDKGroupMember *)obj1;
        return [(NSString *)[member1 name] compare: (NSString *)[member2 name] options:NSCaseInsensitiveSearch];
    }];
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
