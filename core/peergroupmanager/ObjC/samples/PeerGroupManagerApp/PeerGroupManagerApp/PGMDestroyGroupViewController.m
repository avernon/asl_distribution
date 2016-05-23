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

#import "PGMDestroyGroupViewController.h"

@interface PGMDestroyGroupViewController ()

- (void)alertScreen:(NSMutableString*)string;

@end


@implementation PGMDestroyGroupViewController

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
    
    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
 
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
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
    static NSString *CellIdentifier = @"DestroyGroupCell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier forIndexPath:indexPath];
    NSArray *hostedGroups = [self.peerGroupManager listHostedGroupNames];
    
    // Configure the cell...
    if (hostedGroups.count == 0 && indexPath.row == 0)
    {
        cell.textLabel.text = @"No hosted groups";
    }
    else
    {
        cell.textLabel.text = [hostedGroups objectAtIndex:indexPath.row];
    }
    return cell;
}



#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didDeselectRowAtIndexPath:(NSIndexPath *)indexPath
{

}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{

}

- (void)tableView:(UITableView *)tableView didHighlightRowAtIndexPath:(NSIndexPath *)indexPath
{
}

- (void)tableView:(UITableView *)tableView didUnhighlightRowAtIndexPath:(NSIndexPath *)indexPath
{
}

#pragma mark - Button Actions

- (IBAction)destroySelectedGroupsButtonPressed:(id)sender
{
    NSArray *selectedRows = self.tableView.indexPathsForSelectedRows;
    NSMutableString *destroyedGroups = [[NSMutableString alloc] init];
    for (NSIndexPath *indexPath in selectedRows)
    {
        UITableViewCell *cell = [self.tableView cellForRowAtIndexPath:indexPath];
        QStatus status = [self.peerGroupManager destroyGroupWithName:cell.textLabel.text];
        [destroyedGroups appendString:[NSString stringWithFormat:@"%@ - %s\n",cell.textLabel.text,QCC_StatusText(status)]];
    }
    [self.tableView reloadData];
    
    [self alertScreen:destroyedGroups];
}

- (IBAction)destroyAllGroupsButtonPressed:(id)sender
{
    NSArray *hostedGroups = [self.peerGroupManager listHostedGroupNames];
    NSMutableString *destroyedGroups = [[NSMutableString alloc] init];
    for (NSString *groupName in hostedGroups)
    {
        QStatus status = [self.peerGroupManager destroyGroupWithName:groupName];
        [destroyedGroups appendString:[NSString stringWithFormat:@"%@ - %s\n",groupName,QCC_StatusText(status)]];
        
    }
    [self.tableView reloadData];
    
    [self alertScreen:destroyedGroups];
}

- (void)alertScreen:(NSMutableString*)string
{
    if(string.length > 0)
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Destroyed Groups" message:string delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [alert show];
    }
}

@end
