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

#import "LSFSceneEffectsTableViewController.h"
#import "LSFNoEffectTableViewController.h"
#import "LSFTransitionEffectTableViewController.h"
#import "LSFPulseEffectTableViewController.h"
#import "LSFConstants.h"
#import "LSFLampModelContainer.h"
#import "LSFGroupModelContainer.h"
#import "LSFLampModel.h"
#import "LSFGroupModel.h"
#import "LSFUtilityFunctions.h"
#import "LSFEnums.h"

@interface LSFSceneEffectsTableViewController ()

@property (nonatomic, strong) NSIndexPath *selectedIndex;

-(void)controllerNotificationReceived: (NSNotification *)notification;
-(void)sceneNotificationReceived: (NSNotification *)notification;
-(void)deleteScenesWithIDs: (NSArray *)sceneIDs andNames: (NSArray *)sceneNames;

@end

@implementation LSFSceneEffectsTableViewController

@synthesize selectedIndex = _selectedIndex;
@synthesize sceneModel = _sceneModel;
@synthesize sceneElement = _sceneElement;

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

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
 * UITableViewDataSource Implementation
 */
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return 3;
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: @"EffectCells" forIndexPath:indexPath];
    cell.textLabel.text = [([LSFConstants getConstants]).supportedEffects objectAtIndex: [indexPath row]];
    cell.imageView.image = [UIImage imageNamed: [([LSFConstants getConstants]).effectImages objectAtIndex: [indexPath row]]];

    if (indexPath.row == 0)
    {
        cell.accessoryType = UITableViewCellAccessoryCheckmark;
        self.selectedIndex = indexPath;
    }
    else
    {
        cell.accessoryType = UITableViewCellAccessoryNone;
    }

    return cell;
}

-(void)tableView: (UITableView *)tableView didSelectRowAtIndexPath: (NSIndexPath *)indexPath
{
    if (![self.selectedIndex isEqual: indexPath])
    {
        UITableViewCell *previousSelectedCell = [tableView cellForRowAtIndexPath: self.selectedIndex];
        previousSelectedCell.accessoryType = UITableViewCellAccessoryNone;
        [self.tableView deselectRowAtIndexPath: self.selectedIndex animated: NO];
    }

    if ([self.selectedIndex isEqual: indexPath])
    {
        //self.selectedIndex = nil;
        [self.tableView deselectRowAtIndexPath: self.selectedIndex animated: NO];
    }
    else
    {
        UITableViewCell* cell = [tableView cellForRowAtIndexPath: indexPath];
        cell.accessoryType = UITableViewCellAccessoryCheckmark;
        [self.tableView deselectRowAtIndexPath: indexPath animated: NO];
        self.selectedIndex = indexPath;
    }
}

-(NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    return [NSString stringWithFormat: @"Choose an optional effect for %@", [LSFUtilityFunctions buildSectionTitleString: self.sceneElement]];
}

/*
 * Button event handler
 */
-(IBAction)nextButtonPressed: (id)sender
{
    switch (self.selectedIndex.row)
    {
        case 0:
            [self performSegueWithIdentifier: @"NoEffect" sender: self];
            break;
        case 1:
            [self performSegueWithIdentifier: @"TransitionEffect" sender: self];
            break;
        case 2:
            [self performSegueWithIdentifier: @"PulseEffect" sender: self];
            break;
    }
}

/*
 * Segue method
 */
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier isEqualToString: @"NoEffect"])
    {
        LSFNoEffectDataModel *nedm = [[LSFNoEffectDataModel alloc] init];
        nedm.members = self.sceneElement.members;
        nedm.capability = self.sceneElement.capability;

        LSFNoEffectTableViewController *netvc = [segue destinationViewController];
        netvc.sceneModel = self.sceneModel;
        netvc.nedm = nedm;
        netvc.shouldUpdateSceneAndDismiss = NO;
    }
    else if ([segue.identifier isEqualToString: @"TransitionEffect"])
    {
        LSFTransitionEffectDataModel *tedm = [[LSFTransitionEffectDataModel alloc] init];
        tedm.members = self.sceneElement.members;
        tedm.capability = self.sceneElement.capability;

        LSFTransitionEffectTableViewController *tetvc = [segue destinationViewController];
        tetvc.sceneModel = self.sceneModel;
        tetvc.tedm = tedm;
        tetvc.shouldUpdateSceneAndDismiss = NO;
    }
    else if ([segue.identifier isEqualToString: @"PulseEffect"])
    {
        LSFPulseEffectDataModel *pedm = [[LSFPulseEffectDataModel alloc] init];
        pedm.members = self.sceneElement.members;
        pedm.capability = self.sceneElement.capability;

        LSFPulseEffectTableViewController *petvc = [segue destinationViewController];
        petvc.sceneModel = self.sceneModel;
        petvc.pedm = pedm;
        petvc.shouldUpdateSceneAndDismiss = NO;
    }
}

@end