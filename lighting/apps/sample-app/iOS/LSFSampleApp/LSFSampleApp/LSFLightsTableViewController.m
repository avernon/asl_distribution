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

#import "LSFLightsTableViewController.h"
#import "LSFLightInfoTableViewController.h"
#import "LSFLightsCell.h"
#import "LSFUtilityFunctions.h"
#import "LSFWifiMonitor.h"
#import <LSFSDKLightingDirector.h>

@interface LSFLightsTableViewController ()

-(void)lampChangedNotificationReceived: (NSNotification *)notification;
-(void)lampRemovedNotificationReceived: (NSNotification *)notification;
-(void)updateLamp: (LSFSDKLamp *) lamp;
-(void)removeLamp: (LSFSDKLamp *)lamp;
-(NSUInteger)checkIfLampModelExists: (LSFSDKLamp *)lamp;
-(NSUInteger)findInsertionIndexInArray: (LSFSDKLamp *)lamp;
-(void)sortLampsByName;
-(int)findIndexInModelOfID: (NSString *)theID;
-(void)addObjectToTableAtIndex: (NSUInteger)insertIndex;
-(void)moveObjectFromIndex: (NSUInteger)fromIndex toIndex: (NSUInteger)toIndex;
-(void)refreshRowInTableAtIndex: (NSUInteger)index;
-(void)deleteRowInTableAtIndex: (NSUInteger)index;

@end

@implementation LSFLightsTableViewController

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];
    [self.navigationItem setHidesBackButton:YES];

    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(lampChangedNotificationReceived:) name: @"LSFLampChangedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(lampRemovedNotificationReceived:) name: @"LSFLampRemovedNotification" object: nil];

    self.data = [[NSMutableArray alloc] initWithArray: [[LSFSDKLightingDirector getLightingDirector] lamps]];
    [self sortLampsByName];

    //Reload the table
    [self.tableView reloadData];
}

-(void)viewWillDisappear: (BOOL)animated
{
    [super viewWillDisappear: animated];

    //Clear lamps notification handler
    [[NSNotificationCenter defaultCenter] removeObserver: self];

    self.tableView.backgroundView = nil;
}

-(void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

/*
 * Notification Handlers
 */
-(void)lampChangedNotificationReceived: (NSNotification *)notification
{
    @synchronized(self.data)
    {
        if ([[[LSFSDKLightingDirector getLightingDirector] leadController] connected])
        {
            LSFSDKLamp *lamp = [notification.userInfo valueForKey: @"lamp"];
            [self updateLamp: lamp];
        }
    }
}

-(void)lampRemovedNotificationReceived: (NSNotification *)notification
{
    @synchronized(self.data)
    {
        if ([[[LSFSDKLightingDirector getLightingDirector] leadController] connected])
        {
            LSFSDKLamp *lamp = [notification.userInfo valueForKey: @"lamp"];
            [self removeLamp: lamp];
        }
    }
}

-(void)updateLamp: (LSFSDKLamp *) lamp
{
    NSUInteger existingIndex = [self findLampInUIWithModel: lamp];
    NSUInteger insertionIndex = [self findInsertionIndexInArray: lamp];

    if (existingIndex == NSNotFound)
    {
        // new lamp
        [self.data insertObject: lamp atIndex:insertionIndex];
        [self addObjectToTableAtIndex: insertionIndex];
    }
    else
    {
        // existing lamp
        if (existingIndex == insertionIndex)
        {
            NSLog(@"Just refresh, no need to move cell.");
            [self refreshRowInTableAtIndex: insertionIndex];
        }
        else
        {
            NSLog(@"Cell must be moved to preserve alphabetical order");

            if (existingIndex < insertionIndex)
            {
                insertionIndex--;
            }

            [self.data removeObjectAtIndex: existingIndex];
            [self.data insertObject: lamp atIndex: insertionIndex];
            [self moveObjectFromIndex: existingIndex toIndex: insertionIndex];
        }
    }
}

-(NSUInteger)findLampInUIWithModel: (LSFSDKLamp *) lamp
{
    return [self checkIfLampModelExists: lamp];
}

-(void)removeLamp: (LSFSDKLamp *)lamp
{
    int modelArrayIndex = [self findIndexInModelOfID: [lamp theID]];

    if (modelArrayIndex != -1)
    {
        [self.data removeObjectAtIndex: modelArrayIndex];
        [self deleteRowInTableAtIndex: modelArrayIndex];
    }
}

/*
 * UITableViewDataSource Protocol Implementation
 */
-(NSInteger)numberOfSectionsInTableView: (UITableView *)tableView
{
    return 1;
}

-(NSInteger)tableView: (UITableView *)tableView numberOfRowsInSection: (NSInteger)section
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
        if (self.data.count == 0)
        {
            CGRect frame = CGRectMake(0, 0, self.view.bounds.size.width, self.view.bounds.size.height);
            UIView *customView = [[UIView alloc] initWithFrame: frame];
            UILabel *messageLabel = [[UILabel alloc] init];
            [customView addSubview: messageLabel];

            frame.origin.x = 30;
            frame.size.width = self.view.bounds.size.width - frame.origin.x;

            messageLabel.frame = frame;
            messageLabel.text = [NSString stringWithFormat: @"No lamps have been detected on the network %@.\n\nSearching for lamps...", [LSFUtilityFunctions currentWifiSSID]];
            messageLabel.textColor = [UIColor blackColor];
            messageLabel.numberOfLines = 0;
            messageLabel.textAlignment = NSTextAlignmentLeft;

            self.tableView.backgroundView = customView;
        }
        else
        {
            self.tableView.backgroundView = nil;
        }

        return self.data.count;
    }
}

-(UITableViewCell *)tableView: (UITableView *)tableView cellForRowAtIndexPath: (NSIndexPath *)indexPath
{
    LSFSDKLamp *lamp = [self.data objectAtIndex: [indexPath row]];

    LSFLightsCell *cell = [tableView dequeueReusableCellWithIdentifier: @"LightCell" forIndexPath: indexPath];
    cell.lampID = lamp.theID;
    cell.nameLabel.text = lamp.name;

    [LSFUtilityFunctions colorIndicatorSetup: cell.colorIndicatorImage withColor: [lamp getColor] andCapabilityData: [lamp getCapabilities]];

    if ([[lamp details] dimmable])
    {
        if ([lamp getPowerOn] && [[lamp getColor] brightness] == 0)
        {
            dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
                LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID:cell.lampID];
                [lamp setPowerOn: NO];
            });
        }

        cell.brightnessSlider.enabled = YES;
        cell.brightnessSlider.value = [[lamp getColor] brightness];
        cell.brightnessSliderButton.enabled = NO;
    }
    else
    {
        cell.brightnessSlider.enabled = NO;
        cell.brightnessSlider.value = 0;
        cell.brightnessSliderButton.enabled = YES;
    }

    if ([lamp getPowerOn])
    {
        cell.powerImage.image = [UIImage imageNamed: @"light_power_btn_on.png"];
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

-(CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    return 0.00000000001f;
}

/*
 * Segue method
 */
-(void)prepareForSegue: (UIStoryboardSegue *)segue sender: (id)sender
{
    if ([segue.identifier isEqualToString: @"LampInfo"])
    {
        NSIndexPath *indexPath = [self.tableView indexPathForCell: sender];

        LSFLightInfoTableViewController *litvc = [segue destinationViewController];
        litvc.lampID = ((LSFSDKLamp *)[self.data objectAtIndex: [indexPath row]]).theID;
    }
}

/*
 * Private Functions
 */
-(NSUInteger)checkIfLampModelExists: (LSFSDKLamp *)lamp
{
    for (int i = 0; i < self.data.count; i++)
    {
        LSFSDKLamp *lampInUI = (LSFSDKLamp *)[self.data objectAtIndex: i];

        if ([lamp.theID isEqualToString: lampInUI.theID])
        {
            return i;
        }
    }

    return NSNotFound;
}

-(NSUInteger)findInsertionIndexInArray: (LSFSDKLamp *)lamp
{
    return [self.data indexOfObject: lamp inSortedRange: (NSRange){0, [self.data count]} options: (NSBinarySearchingFirstEqual | NSBinarySearchingInsertionIndex) usingComparator:
            ^NSComparisonResult(id a, id b) {
                NSString *first = [(LSFSDKLamp *)a name];
                NSString *second = [(LSFSDKLamp *)b name];

                NSComparisonResult result = [first localizedCaseInsensitiveCompare: second];
                if (result == NSOrderedSame)
                {
                    result = [((LSFSDKLamp *)a).theID localizedCaseInsensitiveCompare: ((LSFSDKLamp *)b).theID];
                }

                return result;
            }];
}

-(void)sortLampsByName
{
    NSMutableArray *sortedArray = [NSMutableArray arrayWithArray: [self.data sortedArrayUsingComparator: ^NSComparisonResult(id a, id b) {
        NSString *first = [(LSFSDKLamp *)a name];
        NSString *second = [(LSFSDKLamp *)b name];

        NSComparisonResult result = [first localizedCaseInsensitiveCompare: second];
        if (result == NSOrderedSame)
        {
            result = [((LSFSDKLamp *)a).theID localizedCaseInsensitiveCompare: ((LSFSDKLamp *)b).theID];
        }

        return result;
    }]];

    self.data = [NSMutableArray arrayWithArray: sortedArray];
}

-(int)findIndexInModelOfID: (NSString *)theID
{
    for (int i = 0; i < self.data.count; i++)
    {
        LSFSDKLamp *lamp = [self.data objectAtIndex: i];

        if ([theID isEqualToString: lamp.theID])
        {
            return i;
        }
    }

    return -1;
}

-(void)addObjectToTableAtIndex: (NSUInteger)insertIndex
{
    //NSLog(@"Add: Index = %u", insertIndex);
    NSArray *insertIndexPaths = [NSArray arrayWithObjects: [NSIndexPath indexPathForRow: insertIndex inSection:0], nil];

    [self.tableView beginUpdates];
    [self.tableView insertRowsAtIndexPaths: insertIndexPaths withRowAnimation: UITableViewRowAnimationFade];
    [self.tableView endUpdates];
}

-(void)moveObjectFromIndex: (NSUInteger)fromIndex toIndex: (NSUInteger)toIndex
{
    //NSLog(@"Move: FromIndex = %u; ToIndex = %u", fromIndex, toIndex);
    NSIndexPath *fromIndexPath = [NSIndexPath indexPathForRow: fromIndex inSection: 0];
    NSIndexPath *toIndexPath = [NSIndexPath indexPathForRow: toIndex inSection: 0];

    [self.tableView beginUpdates];
    [self.tableView moveRowAtIndexPath: fromIndexPath toIndexPath: toIndexPath];
    [self.tableView endUpdates];

    [self refreshRowInTableAtIndex: toIndex];
}

-(void)refreshRowInTableAtIndex: (NSUInteger)index
{
    //NSLog(@"Refresh: Index = %u", index);
    NSArray *refreshIndexPaths = [NSArray arrayWithObjects: [NSIndexPath indexPathForRow: index inSection:0], nil];

    [self.tableView beginUpdates];
    [self.tableView reloadRowsAtIndexPaths: refreshIndexPaths withRowAnimation: UITableViewRowAnimationNone];
    [self.tableView endUpdates];
}

-(void)deleteRowInTableAtIndex: (NSUInteger)index
{
    //NSLog(@"Delete Index = %u", index);
    NSArray *deleteIndexPaths = [NSArray arrayWithObjects: [NSIndexPath indexPathForRow: index inSection:0],nil];

    [self.tableView beginUpdates];
    [self.tableView deleteRowsAtIndexPaths: deleteIndexPaths withRowAnimation: UITableViewRowAnimationFade];
    [self.tableView endUpdates];
}

@end
