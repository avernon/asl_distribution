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

#import "LSFGroupsTableViewController.h"
#import "LSFGroupsInfoTableViewController.h"
#import "LSFGroupsAddNameViewController.h"
#import "LSFGroupsCell.h"
#import "LSFWifiMonitor.h"
#import "LSFUtilityFunctions.h"
#import <LSFSDKLightingDirector.h>

@interface LSFGroupsTableViewController ()

@property (nonatomic, strong) UIBarButtonItem *myEditButton;
@property (nonatomic, strong) UIBarButtonItem *settingsButton;
@property (nonatomic, strong) UIBarButtonItem *addButton;

-(void)groupChangedNotificationReceived: (NSNotification *)notification;
-(void)groupRemovedNotificationReceived: (NSNotification *)notification;
-(void)updateGroup: (LSFSDKGroup *)group;
-(void)removeGroup: (LSFSDKGroup *)group;
-(void)plusButtonPressed;
-(void)settingsButtonPressed;
-(NSUInteger)findInsertionIndexInArray: (LSFSDKGroup *)group;
-(void)sortGroupsByName;
-(void)refreshRowInTableAtIndex: (NSUInteger)index;
-(NSArray *)isGroupContainedInGroupsOrScenes: (NSString *)groupID;

@end

@implementation LSFGroupsTableViewController

@synthesize myEditButton = _myEditButton;
@synthesize settingsButton = _settingsButton;
@synthesize addButton = _addButton;

-(void)viewDidLoad
{
    [super viewDidLoad];
    [self.navigationItem setHidesBackButton:YES];

    self.addButton = [[UIBarButtonItem alloc]
                      initWithBarButtonSystemItem:UIBarButtonSystemItemAdd
                      target: self
                      action: @selector(plusButtonPressed)];

    self.settingsButton = [[UIBarButtonItem alloc]
                           initWithImage: [UIImage imageNamed: @"nav_settings_regular_icon.png"]
                           style:UIBarButtonItemStylePlain
                           target: self
                           action: @selector(settingsButtonPressed)];

    NSArray *actionButtonItems = @[self.settingsButton, self.addButton];
    self.navigationItem.rightBarButtonItems = actionButtonItems;
    self.navigationItem.leftBarButtonItem = self.editButtonItem;
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    //Set groups notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(groupChangedNotificationReceived:) name: @"LSFGroupChangedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(groupRemovedNotificationReceived:) name: @"LSFGroupRemovedNotification" object: nil];

    //Set the content of the default group data array
    self.data = [[NSMutableArray alloc] initWithArray: [[LSFSDKLightingDirector getLightingDirector] groups]];

    if (self.data.count > 0)
    {
        [self sortGroupsByName];
    }

    //Reload the table
    [self.tableView reloadData];
}

-(void)viewWillDisappear: (BOOL)animated
{
    [super viewWillDisappear: animated];

    //Clear groups notification handler
    [[NSNotificationCenter defaultCenter] removeObserver: self];
}

-(void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

/*
 * Notification Handlers
 */
-(void)groupChangedNotificationReceived: (NSNotification *)notification
{
    @synchronized(self.data)
    {
        LSFSDKGroup *group = [notification.userInfo valueForKey: @"group"];
        [self updateGroup: group];
    }
}

-(void)groupRemovedNotificationReceived: (NSNotification *)notification
{
    @synchronized(self.data)
    {
        LSFSDKGroup *group = [notification.userInfo valueForKey: @"group"];
        [self removeGroup: group];
    }
}

-(void)updateGroup: (LSFSDKGroup *)group
{
    if (![self.data containsObject: group])
    {
        // new group
        [self.data addObject: group];
        [self sortGroupsByName];
        [self.tableView reloadData];
    }
    else
    {
        NSUInteger existingIndex = [self findIndexInModelOfID: [group theID]];
        NSUInteger insertionIndex = [self findInsertionIndexInArray: group];

        if (existingIndex == insertionIndex)
        {
            if (existingIndex != -1)
            {
                [self refreshRowInTableAtIndex: existingIndex];
                [self.tableView reloadData];
            }
        }
        else
        {
            [self sortGroupsByName];
            [self.tableView reloadData];
        }
    }
}

-(void) removeGroup:(LSFSDKGroup *)group
{
    int modelArrayIndex = [self findIndexInModelOfID: [group theID]];

    if (modelArrayIndex != -1)
    {
        [self.data removeObjectAtIndex: modelArrayIndex];
        [self.tableView reloadData];
    }
}

/*
 * UITableViewDataSource Protocol Implementation
 */
-(NSInteger)numberOfSectionsInTableView: (UITableView *)tableView
{
    return 1;
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    LSFWifiMonitor *wifiMonitor = [LSFWifiMonitor getWifiMonitor];

    if (!wifiMonitor.isWifiConnected)
    {
        CGRect frame = CGRectMake(0, 0, self.view.bounds.size.width, self.view.bounds.size.height);
        UIView *customView = [[UIView alloc] initWithFrame: frame];
        UILabel *messageLabel = [[UILabel alloc] init];
        [customView addSubview: messageLabel];

        frame.origin.x = 30;
        frame.size.width = self.view.bounds.size.width - frame.origin.x;

        messageLabel.frame = frame;
        messageLabel.text = [NSString stringWithFormat: @"No Wi-Fi Connection.\n\nPlease check that Wi-Fi is enabled in this device's settings and that the device is connected to a Wi-Fi network.\n\nWaiting for Wi-Fi to become available..."];
        messageLabel.textColor = [UIColor blackColor];
        messageLabel.numberOfLines = 0;
        messageLabel.textAlignment = NSTextAlignmentLeft;

        self.tableView.backgroundView = customView;
        return 0;
    }
    else if (![[[LSFSDKLightingDirector getLightingDirector] leadController] connected])
    {
        CGRect frame = CGRectMake(0, 0, self.view.bounds.size.width, self.view.bounds.size.height);
        UIView *customView = [[UIView alloc] initWithFrame: frame];
        UILabel *messageLabel = [[UILabel alloc] init];
        [customView addSubview: messageLabel];

        frame.origin.x = 30;
        frame.size.width = self.view.bounds.size.width - frame.origin.x;

        messageLabel.frame = frame;
        messageLabel.text = [NSString stringWithFormat: @"No controller service is available on the network %@.\n\nSearching for controller service...", [LSFUtilityFunctions currentWifiSSID]];
        messageLabel.textColor = [UIColor blackColor];
        messageLabel.numberOfLines = 0;
        messageLabel.textAlignment = NSTextAlignmentLeft;

        self.tableView.backgroundView = customView;
        return 0;
    }
    else
    {
        self.tableView.backgroundView = nil;
        return self.data.count;
    }
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    LSFSDKGroup *group = [self.data objectAtIndex: [indexPath row]];

    LSFGroupsCell *cell = [tableView dequeueReusableCellWithIdentifier: @"GroupCell" forIndexPath:indexPath];
    cell.groupID = [group theID];
    cell.nameLabel.text = [group name];

    if ([[group getCapabilities] dimmable] > NONE)
    {
        if ([group getPowerOn] && [[group getColor] brightness] == 0)
        {
            dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
                [group setPowerOn: NO];
            });
        }

        cell.brightnessSlider.enabled = YES;
        cell.brightnessSlider.value = [[group getColor] brightness];
        cell.brightnessSliderButton.enabled = NO;

        if ([[group getUniformity] brightness])
        {
            [cell.brightnessSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
            [cell.brightnessSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];
        }
        else
        {
            [cell.brightnessSlider setThumbImage: [UIImage imageNamed: @"power_slider_midstate_icon.png"] forState: UIControlStateNormal];
            [cell.brightnessSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];
        }
    }
    else
    {
        cell.brightnessSlider.enabled = NO;
        cell.brightnessSlider.value = 0;
        cell.brightnessSliderButton.enabled = YES;
    }

    if ([group getPowerOn])
    {
        if ([[group getUniformity] power])
        {
            cell.powerImage.image = [UIImage imageNamed: @"light_power_btn_on.png"];
        }
        else
        {
            cell.powerImage.image = [UIImage imageNamed: @"light_power_btn_other.png"];
        }
    }
    else
    {
        cell.powerImage.image = [UIImage imageNamed: @"light_power_btn_off.png"];
    }

    cell.selectionStyle = UITableViewCellSelectionStyleNone;

    return cell;
}

-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 70;
}

-(CGFloat) tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    return 0.00000000001f;
}

-(BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    if ([indexPath row] == 0)
    {
        return NO;
    }
    else
    {
        return YES;
    }
}

-(UITableViewCellEditingStyle)tableView: (UITableView *)tableView editingStyleForRowAtIndexPath: (NSIndexPath *)indexPath
{
    if (self.tableView.editing)
    {
        return UITableViewCellEditingStyleDelete;
    }

    return UITableViewCellEditingStyleNone;
}

-(void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete)
    {
        LSFSDKGroup *group = [self.data objectAtIndex: [indexPath row]];

        NSArray *names = [self isGroupContainedInGroupsOrScenes: [group theID]];
        if (names.count > 0)
        {
            NSMutableString *nameString = [[NSMutableString alloc] init];

            for (int i = 0; i < names.count; i++)
            {
                [nameString appendString: [NSString stringWithFormat: @"\"%@\", ", [names objectAtIndex: i]]];

                if (i == (names.count - 2))
                {
                    [nameString appendString: @"and "];
                }
            }

            [nameString deleteCharactersInRange: NSMakeRange(nameString.length - 2, 2)];

            UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Can't Delete Group"
                                                            message: [NSString stringWithFormat: @"The group \"%@\" is being used by the following groups or scenes: %@. It cannot be deleted until it is removed from those items, or those items are deleted.", [group name], nameString]
                                                           delegate: nil
                                                  cancelButtonTitle: @"OK"
                                                  otherButtonTitles: nil];
            [alert show];
        }
        else
        {
            int modelArrayIndex = [self findIndexInModelOfID: [group theID]];
            [self.data removeObjectAtIndex: modelArrayIndex];

            // Delete the row from the data source
            [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];

            dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
                [group deleteItem];
            });
        }
    }
}

/*
 * Segue method
 */
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier isEqualToString: @"GroupInfo"])
    {
        NSIndexPath *indexPath = [self.tableView indexPathForCell: sender];

        LSFGroupsInfoTableViewController *gitvc = [segue destinationViewController];
        gitvc.groupID = [NSString stringWithString: ((LSFSDKGroup *)[self.data objectAtIndex: [indexPath row]]).theID];
    }
}

/*
 * Private functions
 */
-(void)plusButtonPressed
{
    LSFWifiMonitor *wifiMonitor = [LSFWifiMonitor getWifiMonitor];

//    if (wifiMonitor.isWifiConnected && [[[[[LSFSDKLightingDirector getLightingDirector] lightingManager] controllerManager] getLeadControllerModel] connected])
    if (wifiMonitor.isWifiConnected && [[[LSFSDKLightingDirector getLightingDirector] leadController] connected])
    {
        [self performSegueWithIdentifier: @"AddGroup" sender: nil];
    }
    else
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                        message: @"Must be connected to a controller before creating a group."
                                                       delegate: nil
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];
    }
};

-(void)settingsButtonPressed
{
    [self performSegueWithIdentifier: @"GroupsSettings" sender: self];
}

-(NSUInteger)findInsertionIndexInArray: (LSFSDKGroup *)group
{
    return [self.data indexOfObject: group inSortedRange: (NSRange){0, [self.data count]} options: (NSBinarySearchingFirstEqual | NSBinarySearchingInsertionIndex) usingComparator:
            ^NSComparisonResult(id a, id b) {
                NSString *first = [(LSFSDKGroup *)a name];
                NSString *second = [(LSFSDKGroup *)b name];

                NSComparisonResult result = [first localizedCaseInsensitiveCompare: second];
                if (result == NSOrderedSame)
                {
                    result = [((LSFSDKGroup *)a).theID localizedCaseInsensitiveCompare: ((LSFSDKGroup *)b).theID];
                }

                return result;
            }];
}

-(void)sortGroupsByName
{
    NSMutableArray *sortedArray = [NSMutableArray arrayWithArray: [self.data sortedArrayUsingComparator: ^NSComparisonResult(id a, id b) {
        NSString *first = [(LSFSDKGroup *)a name];
        NSString *second = [(LSFSDKGroup *)b name];

        NSComparisonResult result = [first localizedCaseInsensitiveCompare: second];
        if (result == NSOrderedSame)
        {
            result = [((LSFSDKGroup *)a).theID localizedCaseInsensitiveCompare: ((LSFSDKGroup *)b).theID];
        }

        return result;
    }]];

    LSFSDKGroup *allLampsGroup;
    for (LSFSDKGroup *group in sortedArray)
    {
        if ([group.name isEqualToString: @"All Lamps"])
        {
            allLampsGroup = group;
            [sortedArray removeObject: group];
            break;
        }
    }

    if (allLampsGroup != nil)
    {
        [sortedArray insertObject: allLampsGroup atIndex: 0];
    }

    self.data = [NSMutableArray arrayWithArray: sortedArray];
}

-(int)findIndexInModelOfID: (NSString *)theID
{
    for (int i = 0; i < self.data.count; i++)
    {
        LSFSDKGroup *group = [self.data objectAtIndex: i];

        if ([theID isEqualToString: group.theID])
        {
            return i;
        }
    }

    return -1;
}

-(void)refreshRowInTableAtIndex: (NSUInteger)index
{
    //NSLog(@"Refresh: Index = %u", index);
    NSArray *refreshIndexPaths = [NSArray arrayWithObjects: [NSIndexPath indexPathForRow: index inSection:0], nil];

    [self.tableView beginUpdates];
    [self.tableView reloadRowsAtIndexPaths: refreshIndexPaths withRowAnimation: UITableViewRowAnimationNone];
    [self.tableView endUpdates];
}

-(NSArray *)isGroupContainedInGroupsOrScenes: (NSString *)groupID
{
    NSMutableArray *names = [[NSMutableArray alloc] init];
    LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: groupID];
    NSArray *lightingDependents = [group dependents];

    for (LSFSDKLightingItem *item in lightingDependents)
    {
        [names addObject: [NSString stringWithString: item.name]];
    }

    return names;
}

@end
