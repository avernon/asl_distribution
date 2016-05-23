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

#import "LSFScenesMembersTableViewController.h"
#import "LSFSceneEffectsTableViewController.h"
#import "LSFNoEffectTableViewController.h"
#import <LSFSDKLightingDirector.h>

@interface LSFScenesMembersTableViewController ()

@property (nonatomic, strong) LSFSceneElementDataModel *sceneElement;
@property (nonatomic, strong) UIBarButtonItem *cancelButton;

-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification;
-(void)sceneRemovedNotificationReceived:(NSNotification *)notification;
-(void)alertSceneDeleted: (LSFSDKScene *)scene;
-(void)cancelButtonPressed;
-(BOOL)checkIfEffectsAreSupported;
-(void)getColorTempMinMax;
-(NSArray *)sortLampsGroupsData: (NSArray *)data;


@end

@implementation LSFScenesMembersTableViewController

@synthesize sceneModel = _sceneModel;
@synthesize sceneElement = _sceneElement;
@synthesize usesCancel = _usesCancel;
@synthesize cancelButton = _cancelButton;

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    //Set notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(sceneRemovedNotificationReceived:) name: @"LSFSceneRemovedNotification" object: nil];

    if (self.usesCancel)
    {
        [self.navigationItem setHidesBackButton:YES];

        self.cancelButton = [[UIBarButtonItem alloc]
                          initWithBarButtonSystemItem:UIBarButtonSystemItemCancel
                          target: self
                          action: @selector(cancelButtonPressed)];

        self.navigationItem.leftBarButtonItem = self.cancelButton;
    }
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

-(void)sceneRemovedNotificationReceived:(NSNotification *)notification
{
    LSFSDKScene *scene = [notification.userInfo valueForKey: @"scene"];

    if ([self.sceneModel.theID isEqualToString: scene.theID])
    {
        [self alertSceneDeleted: scene];
    }
}

-(void)alertSceneDeleted: (LSFSDKScene *)scene
{
    [self dismissViewControllerAnimated: NO completion: nil];

    dispatch_async(dispatch_get_main_queue(), ^{
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Scene Not Found"
                                                        message: [NSString stringWithFormat: @"The scene \"%@\" no longer exists.", [scene name]]
                                                       delegate: nil
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];
    });
}

/*
 * Override table view delegate method so the cell knows how to draw itself
 */
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    LSFSDKGroupMember *groupMember = [self.dataArray objectAtIndex: [indexPath row]];

    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: @"Members" forIndexPath:indexPath];

    if ([groupMember isKindOfClass: [LSFSDKGroup class]])
    {
        cell.textLabel.text = groupMember.name;
        cell.imageView.image = [UIImage imageNamed:@"groups_off_icon.png"];
        cell.accessoryType = UITableViewCellAccessoryNone;
    }
    if ([groupMember isKindOfClass: [LSFSDKLamp class]])
    {
        cell.textLabel.text = groupMember.name;
        cell.imageView.image = [UIImage imageNamed:@"lamps_off_icon.png"];
        cell.accessoryType = UITableViewCellAccessoryNone;
    }

    return cell;
}

-(NSString *)tableView: (UITableView *)tableView titleForHeaderInSection: (NSInteger)section
{
    return @"Select one or more lamps or groups to be in this scene element";
}

/*
 * Override public functions in LSFMembersTableViewController
 */
-(void)buildTableArray
{
    NSMutableArray *groupsArray = [[NSMutableArray alloc] init];

    for (LSFSDKGroup *group in [[LSFSDKLightingDirector getLightingDirector] groups])
    {
        if (![group isAllLampsGroup])
        {
            [groupsArray addObject: group];
        }
    }

    NSMutableArray *lampsArray = [[NSMutableArray alloc] init];

    for (LSFSDKLamp *lamp in [[LSFSDKLightingDirector getLightingDirector] lamps])
    {
        [lampsArray addObject: lamp];
    }

    [self.dataArray addObjectsFromArray: [self sortLampsGroupsData: groupsArray]];
    [self.dataArray addObjectsFromArray: [self sortLampsGroupsData: lampsArray]];
}

-(void)processSelectedRows
{
    //NSLog(@"LSFScenesMembersTableViewController - processSelectedRows() executing");

    LSFSDKCapabilityData *capabilityData = [[LSFSDKCapabilityData alloc] init];
    NSMutableArray *groupIDs = [[NSMutableArray alloc] init];
    NSMutableArray *lampIDs = [[NSMutableArray alloc] init];

    for (NSIndexPath *indexPath in self.selectedRows)
    {
        LSFSDKGroupMember *groupMember = [self.dataArray objectAtIndex: indexPath.row];

        if ([groupMember isKindOfClass: [LSFSDKLamp class]])
        {
            [lampIDs addObject: groupMember.theID];
            [capabilityData includeData: [groupMember getCapabilities]];
        }
        else if ([groupMember isKindOfClass: [LSFSDKGroup class]])
        {
            [groupIDs addObject: groupMember.theID];
            [capabilityData includeData: [groupMember getCapabilities]];
        }
    }

    LSFLampGroup *lampGroup = [[LSFLampGroup alloc] init];
    lampGroup.lamps = lampIDs;
    lampGroup.lampGroups = groupIDs;

    self.sceneElement = [[LSFSceneElementDataModel alloc] initWithEffectType: Unknown andName: @""];
    self.sceneElement.members = lampGroup;
    self.sceneElement.capability = capabilityData;

    [self getColorTempMinMax];
}

/*
 * Next Button Event Handler
 */
-(IBAction)nextButtonPressed: (UIBarButtonItem *)sender
{
    if ([self.selectedRows count] == 0)
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                        message: @"You must select at least one lamp or group to create a scene element."
                                                       delegate: nil
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];
        return;
    }

    [self processSelectedRows];

    if ([self checkIfEffectsAreSupported])
    {
        [self performSegueWithIdentifier: @"ChooseSceneEffect" sender: self];
    }
    else
    {
        [self performSegueWithIdentifier: @"JumpToNoEffect" sender: self];
    }
}

/*
 * Cancel Button Event Handler
 */
-(void)cancelButtonPressed
{
    [self dismissViewControllerAnimated: YES completion: nil];
}

-(BOOL)checkIfEffectsAreSupported
{
    for (NSString *lampID in self.sceneElement.members.lamps)
    {
        LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID: lampID];
        if (lamp.details.hasEffects)
        {
            return YES;
        }
    }

    for (NSString *groupID in self.sceneElement.members.lampGroups)
    {
        LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: groupID];

        for (NSString *lampID in [[group getLampGroupDataModel] lamps])
        {
            LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID: lampID];
            if (lamp.details.hasEffects)
            {
                return YES;
            }
        }
    }

    return NO;
}

-(void)getColorTempMinMax
{
    int colorTempGroupMin = -1;
    int colorTempGroupMax = -1;

    for (NSString *lampID in self.sceneElement.members.lamps)
    {
        LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID: lampID];

        int colorTempLampMin = lamp.details.minTemperature;
        int colorTempLampMax = lamp.details.maxTemperature;

        if ((colorTempGroupMin == -1) || (colorTempGroupMin > colorTempLampMin))
        {
            colorTempGroupMin = colorTempLampMin;
        }

        if ((colorTempGroupMax == -1) || (colorTempGroupMax < colorTempLampMax))
        {
            colorTempGroupMax = colorTempLampMax;
        }
    }

    for (NSString *groupID in self.sceneElement.members.lampGroups)
    {
        LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: groupID];

        for (NSString *lampID in [[group getLampGroupDataModel] lamps])
        {
            LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID: lampID];

            int colorTempLampMin = lamp.details.minTemperature;
            int colorTempLampMax = lamp.details.maxTemperature;

            if ((colorTempGroupMin == -1) || (colorTempGroupMin > colorTempLampMin))
            {
                colorTempGroupMin = colorTempLampMin;
            }

            if ((colorTempGroupMax == -1) || (colorTempGroupMax < colorTempLampMax))
            {
                colorTempGroupMax = colorTempLampMax;
            }
        }
    }

    self.sceneElement.colorTempMin = colorTempGroupMin != -1 ? colorTempGroupMin : [[LSFSDKLightingDirector getLightingDirector] COLORTEMP_MIN];
    self.sceneElement.colorTempMax = colorTempGroupMax != -1 ? colorTempGroupMax : [[LSFSDKLightingDirector getLightingDirector] COLORTEMP_MAX];
}

-(NSArray *)sortLampsGroupsData: (NSArray *)data
{
    NSSortDescriptor *sortDesc = [NSSortDescriptor sortDescriptorWithKey:@"name" ascending:YES comparator:^NSComparisonResult(id obj1, id obj2) {
        return [(NSString *)obj1 compare:(NSString *)obj2 options:NSCaseInsensitiveSearch];
    }];

    return [data sortedArrayUsingDescriptors:[NSArray arrayWithObject:sortDesc]];
}

/*
 * Segue functions
 */
-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier isEqualToString: @"ChooseSceneEffect"])
    {
        LSFSceneEffectsTableViewController *setvc = [segue destinationViewController];
        setvc.sceneModel = self.sceneModel;
        setvc.sceneElement = self.sceneElement;
    }
    else if ([segue.identifier isEqualToString: @"JumpToNoEffect"])
    {
        LSFNoEffectDataModel *nedm = [[LSFNoEffectDataModel alloc] init];
        nedm.members = self.sceneElement.members;
        nedm.capability = self.sceneElement.capability;
        nedm.colorTempMin = self.sceneElement.colorTempMin;
        nedm.colorTempMax = self.sceneElement.colorTempMax;

        LSFNoEffectTableViewController *netvc = [segue destinationViewController];
        netvc.sceneModel = self.sceneModel;
        netvc.nedm = nedm;
    }
}

@end
