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

#import "PGMListPeersViewController.h"

@interface PGMListPeersViewController ()

@property NSString *selectedGroup;

@end

@implementation PGMListPeersViewController

@synthesize peerTableView = _peerTableView;
@synthesize groupTableView = _groupTableView;
@synthesize peerGroupManager = _peerGroupManager;
@synthesize selectedGroup = _selectedGroup;

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
    
	self.peerTableView.delegate = self;
    self.peerTableView.dataSource = self;
    self.groupTableView.delegate = self;
    self.groupTableView.dataSource = self;
    
    [self.peerGroupManager addPeerGroupDelegate:self];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table View data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
     // Return the number of rows in the section.
    if(tableView == self.groupTableView)
    {
        NSInteger numRows = [self.peerGroupManager listJoinedGroupNames].count + [self.peerGroupManager listHostedGroupNames].count;
        if(numRows > 0)
        {
            return numRows;
        }
    }
    else if (tableView == self.peerTableView)
    {
        NSInteger numRows = [self.peerGroupManager getNumberOfPeersInGroup:self.selectedGroup];
        if(numRows > 0)
        {
            return numRows;
        }
    }
    return 1;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell;
    if(tableView == self.groupTableView)
    {
        static NSString *CellIdentifier = @"ListPeersGroupCell";
        cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier forIndexPath:indexPath];
        
        NSMutableArray *hostedAndJoinedGroups = [[self.peerGroupManager listHostedGroupNames] mutableCopy];
        [hostedAndJoinedGroups addObjectsFromArray:[self.peerGroupManager listJoinedGroupNames]];
        [hostedAndJoinedGroups sortUsingSelector:@selector(caseInsensitiveCompare:)];
        
        // Configure the cell...
        if (hostedAndJoinedGroups.count == 0 && indexPath.row == 0)
        {
            cell.textLabel.text = @"No hosted or joined groups";
        }
        else
        {
            cell.textLabel.text = [hostedAndJoinedGroups objectAtIndex:indexPath.row];
        }
    }
    else
    {
        static NSString *CellIdentifier = @"ListPeersCell";
        cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier forIndexPath:indexPath];
        
        NSArray *peers = [self.peerGroupManager getIdsOfPeersInGroup:self.selectedGroup];
        
        // Configure the cell...
        if (peers.count == 0 && indexPath.row == 0)
        {
            cell.textLabel.text = @"No group selected";
        }
        else
        {
            cell.textLabel.text = [peers objectAtIndex:indexPath.row];
        }
    }
    return cell;
}

#pragma mark - Table View delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if(tableView == self.groupTableView)
    {
        self.selectedGroup = [self.groupTableView cellForRowAtIndexPath:indexPath].textLabel.text;
        [self.peerTableView reloadData];
    }
}

#pragma mark - PeerGroupDelegate methods

- (void)didAddPeer:(NSString *)peerId toGroup:(NSString *)groupName forATotalOf:(int)numPeers
{
    NSLog(@"didAddPeer with peer %@ in group %@ while selected group is %@",peerId,groupName,self.selectedGroup);
   if([self.selectedGroup isEqualToString: groupName])
   {
       [self.peerTableView reloadData];
   }
}

- (void)didRemovePeer:(NSString *)peerId fromGroup:(NSString *)groupName forATotalOf:(int)numPeers
{
    if([self.selectedGroup isEqualToString: groupName])
    {
        [self.peerTableView reloadData];
    }
}

- (void)groupWasLost:(NSString *)groupName
{
    [self.groupTableView reloadData];
    if([self.selectedGroup isEqualToString: groupName])
    {
        [self.peerTableView reloadData];
    }
}

@end
