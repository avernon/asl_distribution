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
#import "LSFGroupModelContainer.h"
#import "LSFLampModelContainer.h"
#import "LSFLampModel.h"
#import "LSFGroupModel.h"
#import "LSFEnums.h"

@interface LSFScenesModifyMembersTableViewController ()

@property (nonatomic, strong) UIBarButtonItem *cancelButton;

-(void)controllerNotificationReceived: (NSNotification *)notification;
-(void)sceneNotificationReceived: (NSNotification *)notification;
-(void)deleteScenesWithIDs: (NSArray *)sceneIDs andNames: (NSArray *)sceneNames;
-(void)cancelButtonPressed;

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
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(controllerNotificationReceived:) name: @"ControllerNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(sceneNotificationReceived:) name: @"SceneNotification" object: nil];
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
 * ControllerNotification Handler
 */
-(void)controllerNotificationReceived: (NSNotification *)notification
{
    NSDictionary *userInfo = notification.userInfo;
    NSNumber *controllerStatus = [userInfo valueForKey: @"status"];

    if (controllerStatus.intValue == Disconnected)
    {
        [self dismissViewControllerAnimated: NO completion: nil];
    }
}

/*
 * SceneNotification Handler
 */
-(void)sceneNotificationReceived: (NSNotification *)notification
{
    NSNumber *callbackOp = [notification.userInfo valueForKey: @"operation"];
    NSArray *sceneIDs = [notification.userInfo valueForKey: @"sceneIDs"];
    NSArray *sceneNames = [notification.userInfo valueForKey: @"sceneNames"];

    if ([sceneIDs containsObject: self.sceneModel.theID])
    {
        switch (callbackOp.intValue)
        {
            case SceneDeleted:
                [self deleteScenesWithIDs: sceneIDs andNames: sceneNames];
                break;
            default:
                break;
        }
    }
}

-(void)deleteScenesWithIDs: (NSArray *)sceneIDs andNames: (NSArray *)sceneNames
{
    if ([sceneIDs containsObject: self.sceneModel.theID])
    {
        int index = [sceneIDs indexOfObject: self.sceneModel.theID];

        [self dismissViewControllerAnimated: NO completion: nil];

        dispatch_async(dispatch_get_main_queue(), ^{
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Scene Not Found"
                                                            message: [NSString stringWithFormat: @"The scene \"%@\" no longer exists.", [sceneNames objectAtIndex: index]]
                                                           delegate: nil
                                                  cancelButtonTitle: @"OK"
                                                  otherButtonTitles: nil];
            [alert show];
        });
    }
}

/*
 * Override table view delegate method so the cell knows how to draw itself
 */
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    id model = [self.dataArray objectAtIndex: [indexPath row]];
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: @"ModifyMembers" forIndexPath:indexPath];

    if ([model isKindOfClass: [LSFGroupModel class]])
    {
        LSFGroupModel *groupModel = (LSFGroupModel *)model;

        cell.textLabel.text = groupModel.name;
        cell.imageView.image = [UIImage imageNamed:@"groups_off_icon.png"];

        if ([self.sceneElement.members.lampGroups containsObject: groupModel.theID])
        {
            cell.accessoryType = UITableViewCellAccessoryCheckmark;
            [self.selectedRows addObject: indexPath];
        }
        else
        {
            cell.accessoryType = UITableViewCellAccessoryNone;
        }
    }
    if ([model isKindOfClass: [LSFLampModel class]])
    {
        LSFLampModel *lampModel = (LSFLampModel *)model;

        cell.textLabel.text = lampModel.name;
        cell.imageView.image = [UIImage imageNamed:@"lamps_off_icon.png"];

        if ([self.sceneElement.members.lamps containsObject: lampModel.theID])
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

    LSFCapabilityData *capabilityData = [[LSFCapabilityData alloc] init];
    NSMutableArray *groupIDs = [[NSMutableArray alloc] init];
    NSMutableArray *lampIDs = [[NSMutableArray alloc] init];

    for (NSIndexPath *indexPath in self.selectedRows)
    {
        id model = [self.dataArray objectAtIndex: indexPath.row];

        if ([model isKindOfClass: [LSFGroupModel class]])
        {
            [groupIDs addObject: ((LSFModel *)model).theID];
            [capabilityData includeData: ((LSFDataModel *)model).capability];
        }
        else if ([model isKindOfClass: [LSFLampModel class]])
        {
            [lampIDs addObject: ((LSFModel *)model).theID];
            [capabilityData includeData: ((LSFDataModel *)model).capability];
        }
    }

    LSFLampGroup *lampGroup = [[LSFLampGroup alloc] init];
    lampGroup.lamps = lampIDs;
    lampGroup.lampGroups = groupIDs;

    self.sceneElement.members = lampGroup;
    self.sceneElement.capability = capabilityData;

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
        netvc.shouldUpdateSceneAndDismiss = YES;
    }
    else if ([segue.identifier isEqualToString: @"ModifyTransition"])
    {
        LSFTransitionEffectTableViewController *tetvc = [segue destinationViewController];
        tetvc.sceneModel = self.sceneModel;
        tetvc.tedm = (LSFTransitionEffectDataModel *)self.sceneElement;
        tetvc.shouldUpdateSceneAndDismiss = YES;
    }
    else if ([segue.identifier isEqualToString: @"ModifyPulse"])
    {
        LSFPulseEffectTableViewController *petvc = [segue destinationViewController];
        petvc.sceneModel = self.sceneModel;
        petvc.pedm = (LSFPulseEffectDataModel *)self.sceneElement;
        petvc.shouldUpdateSceneAndDismiss = YES;
    }
}

@end
