/******************************************************************************
 * Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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

#import "PGMUnlockAndLockGroupsViewController.h"

@interface PGMUnlockAndLockGroupsViewController ()

@end

@implementation PGMUnlockAndLockGroupsViewController

@synthesize tableView = _tableView;
@synthesize peerGroupManager = _peerGroupManager;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	
    self.tableView.delegate = self;
    self.tableView.dataSource = self;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    // Return the number of rows in the section.
    NSInteger numRows = [self.peerGroupManager listHostedGroupNames].count;
    if(numRows > 0)
    {
        return numRows;
    }
    
    return 1;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"LockGroupCell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier forIndexPath:indexPath];
    NSArray *hostedGroups = [self.peerGroupManager listHostedGroupNames];
    NSArray *lockedGroups = [self.peerGroupManager listLockedGroupNames];
    // Configure the cell...
    if (hostedGroups.count == 0 && indexPath.row == 0)
    {
        cell.textLabel.text = @"No hosted groups";
    }
    else
    {
        cell.textLabel.text = [hostedGroups objectAtIndex:indexPath.row];
        if([lockedGroups containsObject:cell.textLabel.text])
        {
            cell.accessoryView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"locked.png"]];
        }
        else
        {
             cell.accessoryView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"unlocked.png"]];
        }
    }
    return cell;
}


#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSArray *lockedGroups = [self.peerGroupManager listLockedGroupNames];
    NSString *groupName = [self.tableView cellForRowAtIndexPath:indexPath].textLabel.text;
    if([lockedGroups containsObject:groupName])
    {
        [self.peerGroupManager unlockGroupWithName:groupName];
    }
    else
    {
        [self.peerGroupManager lockGroupWithName:groupName];
    }

    [self.tableView reloadData];
}


#pragma mark - Button Actions

- (IBAction)unlockAllGroupsButtonPressed:(id)sender
{
    NSArray *lockedGroups = [self.peerGroupManager listLockedGroupNames];
    for (NSString *groupName in lockedGroups)
    {
        [self.peerGroupManager unlockGroupWithName:groupName];
    }
    
    [self.tableView reloadData];
}

- (IBAction)lockAllGroupsButtonPressed:(id)sender
{
    NSArray *hostedGroups = [self.peerGroupManager listHostedGroupNames];
    NSArray *lockedGroups = [self.peerGroupManager listLockedGroupNames];
    for (NSString *groupName in hostedGroups)
    {
        if(![lockedGroups containsObject:groupName])
        {
            [self.peerGroupManager lockGroupWithName:groupName];
        }
    }
    
    [self.tableView reloadData];
}
@end
