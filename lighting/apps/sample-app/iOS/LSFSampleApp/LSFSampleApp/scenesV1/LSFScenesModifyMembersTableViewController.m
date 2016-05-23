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

#import "LSFScenesModifyMembersTableViewController.h"
#import "LSFNoEffectTableViewController.h"
#import "LSFTransitionEffectTableViewController.h"
#import "LSFPulseEffectTableViewController.h"
#import <LSFSDKLightingDirector.h>
#import <model/LSFConstants.h>

@interface LSFScenesModifyMembersTableViewController ()

@property (nonatomic, strong) UIBarButtonItem *cancelButton;

-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification;
-(void)sceneRemovedNotificationReceived:(NSNotification *)notification;
-(void)alertSceneDeleted: (LSFSDKScene *)scene;
-(void)cancelButtonPressed;
-(void)getColorTempMinMax;

@end

@implementation LSFScenesModifyMembersTableViewController

@synthesize sceneModel = _sceneModel;
@synthesize sceneElement = _sceneElement;

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];
    [self.navigationItem setHidesBackButton:YES];

    self.cancelButton = [[UIBarButtonItem alloc]
                         initWithBarButtonSystemItem:UIBarButtonSystemItemCancel
                         target: self
                         action: @selector(cancelButtonPressed)];

    self.navigationItem.leftBarButtonItem = self.cancelButton;

    //Set notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(sceneRemovedNotificationReceived:) name: @"LSFSceneRemovedNotification" object: nil];
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

-(void)alertSceneDeleted:(LSFSDKScene *)scene
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
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: @"ModifyMembers" forIndexPath:indexPath];

    if ([groupMember isKindOfClass: [LSFSDKGroup class]])
    {
        cell.textLabel.text = groupMember.name;
        cell.imageView.image = [UIImage imageNamed:@"groups_off_icon.png"];

        if ([self.sceneElement.members.lampGroups containsObject: groupMember.theID])
        {
            cell.accessoryType = UITableViewCellAccessoryCheckmark;
            [self.selectedRows addObject: indexPath];
        }
        else
        {
            cell.accessoryType = UITableViewCellAccessoryNone;
        }
    }
    if ([groupMember isKindOfClass: [LSFSDKLamp class]])
    {
        cell.textLabel.text = groupMember.name;
        cell.imageView.image = [UIImage imageNamed:@"lamps_off_icon.png"];

        if ([self.sceneElement.members.lamps containsObject: groupMember.theID])
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

/*
 * Override public functions in LSFMembersTableViewController
 */
-(void)processSelectedRows
{
    //NSLog(@"LSFScenesMembersTableViewController - processSelectedRows() executing");

    LSFSDKCapabilityData *capabilityData = [[LSFSDKCapabilityData alloc] init];
    NSMutableArray *groupIDs = [[NSMutableArray alloc] init];
    NSMutableArray *lampIDs = [[NSMutableArray alloc] init];

    for (NSIndexPath *indexPath in self.selectedRows)
    {
        LSFSDKGroupMember *groupMember = [self.dataArray objectAtIndex: indexPath.row];

        if ([groupMember isKindOfClass: [LSFSDKGroup class]])
        {
            [groupIDs addObject: groupMember.theID];
            [capabilityData includeData: groupMember.getCapabilities];
        }
        else if ([groupMember isKindOfClass: [LSFSDKLamp class]])
        {
            [lampIDs addObject: groupMember.theID];
            [capabilityData includeData: groupMember.getCapabilities];
        }
    }

    LSFLampGroup *lampGroup = [[LSFLampGroup alloc] init];
    lampGroup.lamps = lampIDs;
    lampGroup.lampGroups = groupIDs;

    self.sceneElement.members = lampGroup;
    self.sceneElement.capability = capabilityData;

    [self getColorTempMinMax];

    if ([self.sceneElement isKindOfClass: [LSFNoEffectDataModel class]])
    {
        [self performSegueWithIdentifier: @"ModifyNoEffect" sender: nil];
    }
    else if ([self.sceneElement isKindOfClass: [LSFTransitionEffectDataModel class]])
    {
        [self performSegueWithIdentifier: @"ModifyTransition" sender: nil];
    }
    else if ([self.sceneElement isKindOfClass: [LSFPulseEffectDataModel class]])
    {
        [self performSegueWithIdentifier: @"ModifyPulse" sender: nil];
    }
}

/*
 * Cancel Button Event Handler
 */
-(void)cancelButtonPressed
{
    [self dismissViewControllerAnimated: YES completion: nil];
}

/*
 * Next Button Clicked Handler
 */
-(IBAction)nextButtonPressed: (id)sender
{
    if ([self.selectedRows count] == 0)
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                        message: @"You must select at least one lamp or group to modify a scene element."
                                                       delegate: nil
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];
        return;
    }
    else
    {
        [self processSelectedRows];
    }
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

/*
 * Segue Function
 */
-(void)prepareForSegue: (UIStoryboardSegue *)segue sender: (id)sender
{
    if ([segue.identifier isEqualToString: @"ModifyNoEffect"])
    {
        LSFNoEffectTableViewController *netvc = [segue destinationViewController];
        netvc.sceneModel = self.sceneModel;
        netvc.nedm = (LSFNoEffectDataModel *)self.sceneElement;
        // unscale lamp state values as *EffectTableViewControllers are expecting them to not be scaled
        netvc.nedm.state = [self unscaleLampState: netvc.nedm.state];
        netvc.shouldUpdateSceneAndDismiss = YES;
    }
    else if ([segue.identifier isEqualToString: @"ModifyTransition"])
    {
        LSFTransitionEffectTableViewController *tetvc = [segue destinationViewController];
        tetvc.sceneModel = self.sceneModel;
        tetvc.tedm = (LSFTransitionEffectDataModel *)self.sceneElement;
        // unscale lamp state values as *EffectTableViewControllers are expecting them to not be scaled
        tetvc.tedm.state = [self unscaleLampState: tetvc.tedm.state];
        tetvc.shouldUpdateSceneAndDismiss = YES;
    }
    else if ([segue.identifier isEqualToString: @"ModifyPulse"])
    {
        LSFPulseEffectTableViewController *petvc = [segue destinationViewController];
        petvc.sceneModel = self.sceneModel;
        petvc.pedm = (LSFPulseEffectDataModel *)self.sceneElement;
        // unscale lamp state values as *EffectTableViewControllers are expecting them to not be scaled
        petvc.pedm.state = [self unscaleLampState: petvc.pedm.state];
        petvc.pedm.endState = [self unscaleLampState: petvc.pedm.endState];
        petvc.shouldUpdateSceneAndDismiss = YES;
    }
}

-(LSFLampState *)unscaleLampState: (LSFLampState *)state
{
    LSFConstants *constants = [LSFConstants getConstants];

    unsigned int brightness = [constants unscaleLampStateValue: state.brightness withMax: 100];
    unsigned int hue = [constants unscaleLampStateValue: state.hue withMax: 360];
    unsigned int saturation = [constants unscaleLampStateValue: state.saturation withMax: 100];
    unsigned int colorTemp = [constants unscaleColorTemp: state.colorTemp];

    LSFLampState *unscaledState = [[LSFLampState alloc] initWithOnOff: state.onOff brightness: brightness hue: hue saturation: saturation colorTemp: colorTemp];
    return unscaledState;
}

@end
