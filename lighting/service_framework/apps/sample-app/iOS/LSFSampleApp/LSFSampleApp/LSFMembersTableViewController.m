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

#import "LSFMembersTableViewController.h"
#import "LSFLampModel.h"
#import "LSFGroupModel.h"

@interface LSFMembersTableViewController ()

-(void)modifyAllRows: (BOOL)isSelected;

@end

@implementation LSFMembersTableViewController

@synthesize dataArray = _dataArray;
@synthesize selectedRows = _selectedRows;

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    //Initialize selected rows array
    self.selectedRows = [[NSMutableArray alloc] init];

    //Load UI
    [self buildTableArray];
    [self.tableView reloadData];
}

/*
 * Table View Delegate Functions
 */
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [self.dataArray count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return nil;
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

/*
 * Public functions
 */
-(void)buildTableArray
{
    // Function meant to be overriden in subclass
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
    // Function meant to be overriden in subclass
}

-(void)sortDataArray
{
    NSSortDescriptor *sortDesc = [NSSortDescriptor sortDescriptorWithKey:@"name" ascending:YES comparator:^NSComparisonResult(id obj1, id obj2) {
        return [(NSString *)obj1 compare:(NSString *)obj2 options:NSCaseInsensitiveSearch];
    }];
    NSMutableArray *dataArraySorted = [[NSMutableArray alloc] initWithArray: [self.dataArray sortedArrayUsingDescriptors:[NSArray arrayWithObject:sortDesc]]];
    self.dataArray = dataArraySorted;
}
@end
