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

#import "LSFLightsPresetsTableViewController.h"
#import "LSFLightsCreatePresetViewController.h"
#import "LSFUtilityFunctions.h"
#import <LSFSDKLightingDirector.h>

@interface LSFLightsPresetsTableViewController ()

@property (nonatomic, strong) NSArray *presetData;
@property (nonatomic, strong) NSMutableArray *presetDataSorted;

-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification;
-(void)lampChangedNotificationReceived: (NSNotification *) notification;
-(void)lampRemovedNotificationReceived: (NSNotification *) notification;
-(void)deleteLampWithID: (NSString *)lampID andName: (NSString *)lampName;
-(void)presetNotificationReceived: (NSNotification *)notification;
-(BOOL)checkIfLamp: (LSFSDKLamp *) lamp matchesPreset: (LSFSDKPreset *) preset;
-(void)reloadPresets;
-(void)sortPresetData;
-(void)filterPresetData;

@end

@implementation LSFLightsPresetsTableViewController

@synthesize lampID = _lampID;
@synthesize presetData = _presetData;

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];
    self.navigationItem.rightBarButtonItem = self.editButtonItem;

    //Set notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(lampChangedNotificationReceived:) name: @"LSFLampChangedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(lampRemovedNotificationReceived:) name: @"LSFLampRemovedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(presetNotificationReceived:) name: @"LSFPresetChangedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(presetNotificationReceived:) name: @"LSFPresetRemovedNotification" object: nil];
    
    [self reloadPresets];
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

-(void)lampChangedNotificationReceived: (NSNotification *) notification
{
    NSString *lampID = [[notification.userInfo valueForKey: @"lamp"] theID];

    if ([self.lampID isEqualToString: lampID])
    {
        [self reloadPresets];
    }
}

-(void)lampRemovedNotificationReceived: (NSNotification *) notification
{
    LSFSDKLamp *lamp = [notification.userInfo valueForKey: @"lamp"];

    if ([self.lampID isEqualToString: [lamp theID]])
    {
        [self deleteLampWithID: [lamp theID] andName: [lamp name]];
    }
}

-(void)presetNotificationReceived: (NSNotification *)notification
{
    [self reloadPresets];
}

-(void)deleteLampWithID: (NSString *)lampID andName: (NSString *)lampName
{
    if ([self.lampID isEqualToString: lampID])
    {
        [self.navigationController popToRootViewControllerAnimated: YES];

        dispatch_async(dispatch_get_main_queue(), ^{
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Connection Lost"
                                                            message: [NSString stringWithFormat: @"Unable to connect to \"%@\".", lampName]
                                                           delegate: nil
                                                  cancelButtonTitle: @"OK"
                                                  otherButtonTitles: nil];
            [alert show];
        });
    }
}

-(void)reloadPresets
{
    self.presetData = [[LSFSDKLightingDirector getLightingDirector] presets];
    [self sortPresetData];
    [self filterPresetData];

    [self.tableView reloadData];
}

/*
 * UITableViewDataSource Implementation
 */
-(UITableViewCell *)tableView: (UITableView *)tableView cellForRowAtIndexPath: (NSIndexPath *)indexPath
{
    if (indexPath.section == 0)
    {
        UITableViewCell *cell = [[UITableViewCell alloc] init];
        cell.textLabel.text = @"Save New Preset";
        cell.textLabel.textColor = [UIColor colorWithRed: 0 green: 0.478431 blue: 1.0 alpha: 1.0];
        return cell;
    }
    else
    {
        LSFSDKPreset *preset = [self.presetDataSorted objectAtIndex: [indexPath row]];
        BOOL stateMatchesPreset = [self checkIfLamp: [[LSFSDKLightingDirector getLightingDirector] getLampWithID: self.lampID]  matchesPreset: preset];

        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: @"PresetCell" forIndexPath: indexPath];
        cell.textLabel.text = [preset name];

        if (stateMatchesPreset)
        {
            cell.accessoryType = UITableViewCellAccessoryCheckmark;
        }
        else
        {
            cell.accessoryType = UITableViewCellAccessoryNone;
        }

        return cell;
    }
}

-(void)tableView: (UITableView *)tableView didSelectRowAtIndexPath: (NSIndexPath *)indexPath
{
    if (indexPath.section == 0)
    {
        [self performSegueWithIdentifier: @"SavePreset" sender: nil];
        return;
    }

    UITableViewCell *cell = [tableView cellForRowAtIndexPath: indexPath];

    if (cell != nil)
    {
        if (cell.accessoryType == UITableViewCellAccessoryNone)
        {
            cell.accessoryType = UITableViewCellAccessoryCheckmark;

            dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
                LSFSDKPreset *preset = [self.presetDataSorted objectAtIndex: [indexPath row]];
                LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID: self.lampID];
                [lamp applyPreset: preset];
            });

            [self.navigationController popViewControllerAnimated: YES];
        }
        else
        {
            [self.navigationController popViewControllerAnimated: YES];
        }
    }
}

-(NSInteger)numberOfSectionsInTableView: (UITableView *)tableView
{
    return 2;
}

-(NSInteger)tableView: (UITableView *)tableView numberOfRowsInSection: (NSInteger)section
{
    if (section == 0)
    {
        return 1;
    }
    else
    {
        return self.presetDataSorted.count;
    }
}

-(NSString *)tableView: (UITableView *)tableView titleForHeaderInSection: (NSInteger)section
{
    if (section == 1)
    {
        if (![self tableView:self.tableView numberOfRowsInSection:1])
        {
            return @"No presets have been saved yet";
        }
        else
        {
            return @"Presets";
        }
    }

    return @" ";
}

-(BOOL)tableView: (UITableView *)tableView canEditRowAtIndexPath: (NSIndexPath *)indexPath
{
    return indexPath.section == 1 ? YES : NO;
}

-(void)tableView: (UITableView *)tableView commitEditingStyle: (UITableViewCellEditingStyle)editingStyle forRowAtIndexPath: (NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete)
    {
        LSFSDKPreset *preset = [self.presetDataSorted objectAtIndex: [indexPath row]];

        [self.presetDataSorted removeObjectAtIndex: indexPath.row];
        
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
        
        dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
            [preset deleteItem];
        });
    }
}

-(CGFloat)tableView: (UITableView *)tableView heightForHeaderInSection: (NSInteger)section
{
    if (section == 0)
    {
        return 20.0f;
    }

    return UITableViewAutomaticDimension;
}

/*
 * Private functions
 */
-(BOOL)checkIfLamp: (LSFSDKLamp *) lamp matchesPreset: (LSFSDKPreset *) preset
{
    BOOL returnValue = NO;

    LSFSDKColor *lampColor = [lamp getColor];
    LSFSDKColor *presetColor = [preset getColor];

    if ([lamp getPowerOn] == [preset getPowerOn] && [lampColor hue] == [presetColor hue] &&
        [lampColor saturation] == [presetColor saturation] && [lampColor brightness] == [presetColor brightness] &&
        [lampColor colorTemp] == [presetColor colorTemp])
    {
        returnValue = YES;
    }

    return returnValue;
}


-(void)sortPresetData
{
    NSSortDescriptor *sortDesc = [NSSortDescriptor sortDescriptorWithKey:@"name" ascending:YES comparator:^NSComparisonResult(id obj1, id obj2) {
        return [(NSString *)obj1 compare:(NSString *)obj2 options:NSCaseInsensitiveSearch];
    }];
    self.presetDataSorted = [[NSMutableArray alloc] initWithArray: [self.presetData sortedArrayUsingDescriptors:[NSArray arrayWithObject:sortDesc]]];
}

-(void)filterPresetData
{
    NSMutableArray *presetsToRemove = [[NSMutableArray alloc] init];

    for (LSFSDKPreset *preset in self.presetDataSorted)
    {
        if ([preset.name hasPrefix: PRESET_NAME_PREFIX])
        {
            [presetsToRemove addObject: preset];
        }
    }

    for (LSFSDKPreset *preset in presetsToRemove)
    {
        [self.presetDataSorted removeObject: preset];
    }
}

/*
 * Segue Function
 */
- (void)prepareForSegue: (UIStoryboardSegue *)segue sender: (id)sender
{
    if ([segue.identifier isEqualToString: @"SavePreset"])
    {
        LSFLightsCreatePresetViewController *lcpvc = [segue destinationViewController];
        lcpvc.lampID = self.lampID;
    }
}

@end
