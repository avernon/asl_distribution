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

#import "LSFSceneInfoTableViewController.h"
#import "LSFScenesMembersTableViewController.h"
#import "LSFScenesModifyMembersTableViewController.h"
#import "LSFScenesChangeNameViewController.h"
#import <LSFSDKLightingDirector.h>

@interface LSFSceneInfoTableViewController ()

@property (nonatomic, strong) LSFSceneDataModel *sceneModel;
@property (nonatomic, strong) NSMutableArray *dataArray;
@property (nonatomic, strong) UIBarButtonItem *addButton;

-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification;
-(void)sceneChangedNotificationReceived:(NSNotification *)notification;
-(void)sceneRemovedNotificationReceived:(NSNotification *)notification;
-(void)alertSceneDeleted: (LSFSDKScene *)scene;
-(NSString *)buildMemberString: (LSFSceneElementDataModel *)sceneElement;
-(void)plusButtonPressed;

@end

@implementation LSFSceneInfoTableViewController

@synthesize sceneID = _sceneID;
@synthesize sceneModel = _sceneModel;
@synthesize dataArray = _dataArray;
@synthesize addButton = _addButton;

-(void)viewDidLoad
{
    [super viewDidLoad];

    self.dataArray = [[NSMutableArray alloc] init];

    self.addButton = [[UIBarButtonItem alloc]
                      initWithBarButtonSystemItem:UIBarButtonSystemItemAdd
                      target: self
                      action: @selector(plusButtonPressed)];

    NSArray *actionButtonItems = @[self.editButtonItem, self.addButton];
    self.navigationItem.rightBarButtonItems = actionButtonItems;
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    if (![[[LSFSDKLightingDirector getLightingDirector] leadController] connected])
    {
        [self.navigationController popToRootViewControllerAnimated: YES];
    }

    //Set notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(sceneChangedNotificationReceived:) name: @"LSFSceneChangedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(sceneRemovedNotificationReceived:) name: @"LSFSceneRemovedNotification" object: nil];

    LSFSDKScene *scene = [[LSFSDKLightingDirector getLightingDirector] getSceneWithID: self.sceneID];
    if ([scene isKindOfClass: [LSFSDKSceneV1 class]])
    {
        [self reloadScene: (LSFSDKSceneV1 *)scene];
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

-(void)sceneChangedNotificationReceived:(NSNotification *)notification
{
    LSFSDKScene *scene = [notification.userInfo valueForKey: @"scene"];

    if ([scene isKindOfClass: [LSFSDKSceneV1 class]] && [self.sceneID isEqualToString: scene.theID])
    {
        LSFSDKSceneV1 *sceneV1 = (LSFSDKSceneV1 *)scene;
        [self reloadScene: sceneV1];
    }
}

-(void)sceneRemovedNotificationReceived:(NSNotification *)notification
{
    LSFSDKScene *scene = [notification.userInfo valueForKey: @"scene"];

    if ([self.sceneID isEqualToString: scene.theID])
    {
        [self alertSceneDeleted: scene];
    }
}

-(void)reloadScene: (LSFSDKSceneV1 *)scene
{
    [self.dataArray removeAllObjects];

    self.sceneModel = [scene getSceneDataModel];

    if (self.sceneModel != nil)
    {
        [self.dataArray addObjectsFromArray: self.sceneModel.noEffects];
        [self.dataArray addObjectsFromArray: self.sceneModel.transitionEffects];
        [self.dataArray addObjectsFromArray: self.sceneModel.pulseEffects];
    }
    else
    {
        [self.navigationController popToRootViewControllerAnimated: YES];
    }

    [self.tableView reloadData];
}

-(void)alertSceneDeleted:(LSFSDKScene *)scene
{
    [self.navigationController popToRootViewControllerAnimated: YES];

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
 * UITableViewDataSource Implementation
 */
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
        return (self.sceneModel.noEffects.count + self.sceneModel.transitionEffects.count + self.sceneModel.pulseEffects.count);
    }
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.section == 0)
    {
        UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle: UITableViewCellStyleValue1 reuseIdentifier: nil];
        cell.textLabel.text = @"Scene Name";
        cell.detailTextLabel.text = self.sceneModel.name;
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        return cell;
    }
    else
    {
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: @"SceneElementCell" forIndexPath: indexPath];

        id sceneElement = [self.dataArray objectAtIndex: indexPath.row];
        cell.textLabel.text = [self buildMemberString: (LSFSceneElementDataModel *)sceneElement];

        if ([sceneElement isKindOfClass: [LSFNoEffectDataModel class]])
        {
            cell.imageView.image = [UIImage imageNamed: @"list_constant_icon.png"];
            cell.detailTextLabel.text = @"";
        }
        else if ([sceneElement isKindOfClass: [LSFTransitionEffectDataModel class]])
        {
            cell.imageView.image = [UIImage imageNamed: @"list_transition_icon.png"];
            cell.detailTextLabel.text = @"Transition";
        }
        else if ([sceneElement isKindOfClass: [LSFPulseEffectDataModel class]])
        {
            cell.imageView.image = [UIImage imageNamed: @"list_pulse_icon.png"];
            cell.detailTextLabel.text = @"Pulse";
        }

        return cell;
    }
}

-(NSString *)tableView: (UITableView *)tableView titleForHeaderInSection: (NSInteger)section
{
    if (section == 1)
    {
        return @"Scene Elements";
    }

    return @"";
}

-(BOOL)tableView: (UITableView *)tableView canEditRowAtIndexPath: (NSIndexPath *)indexPath
{
    if (indexPath.section == 1)
    {
        return YES;
    }
    else
    {
        return NO;
    }
}

-(void)tableView: (UITableView *)tableView commitEditingStyle: (UITableViewCellEditingStyle)editingStyle forRowAtIndexPath: (NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete)
    {
        LSFSceneElementDataModel *data = [self.dataArray objectAtIndex: indexPath.row];
        BOOL removeSuccessful = [self.sceneModel removeElement: data.theID];

        if (removeSuccessful)
        {
            //NSLog(@"Removing scene element for SceneDataModel was succesful");

            dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
                [[[[LSFSDKLightingDirector getLightingDirector] lightingManager] sceneManager] updateSceneWithID: self.sceneModel.theID withScene: [self.sceneModel toScene]];
            });

            // Delete the row from the data source
            [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation: UITableViewRowAnimationFade];
        }
    }
}

-(void)tableView: (UITableView *)tableView didSelectRowAtIndexPath: (NSIndexPath *)indexPath
{
    if (indexPath.section == 1)
    {
        [self performSegueWithIdentifier: @"ModifySceneElement" sender: indexPath];
    }
    else
    {
        [self performSegueWithIdentifier: @"ChangeSceneName" sender: self];
    }
}

-(NSString *)tableView: (UITableView *)tableView titleForFooterInSection: (NSInteger)section
{
    if (section == 1)
    {
        return @"Tap + to add a new scene element";
    }

    return @"";
}

/*
 * Segue Function
 */
-(void)prepareForSegue: (UIStoryboardSegue *)segue sender: (id)sender
{
    if ([segue.identifier isEqualToString: @"CreateSceneElement"])
    {
        UINavigationController *nc = (UINavigationController *)[segue destinationViewController];
        LSFScenesMembersTableViewController *smtvc = (LSFScenesMembersTableViewController *)nc.topViewController;
        smtvc.sceneModel = self.sceneModel;
        smtvc.usesCancel = YES;
    }
    else if ([segue.identifier isEqualToString: @"ModifySceneElement"])
    {
        NSIndexPath *indexPath = (NSIndexPath *)sender;

        UINavigationController *nc = (UINavigationController *)[segue destinationViewController];
        LSFScenesModifyMembersTableViewController *smmtvc = (LSFScenesModifyMembersTableViewController *)nc.topViewController;
        smmtvc.sceneModel = self.sceneModel;
        smmtvc.sceneElement = [self.dataArray objectAtIndex: indexPath.row];
    }
    else if ([segue.identifier isEqualToString: @"ChangeSceneName"])
    {
        LSFScenesChangeNameViewController *scnvc = [segue destinationViewController];
        scnvc.sceneID = self.sceneID;
    }
}

/*
 * Private Functions
 */
-(NSString *)buildMemberString: (LSFSceneElementDataModel *)sceneElement
{
    BOOL firstNameAdded = NO;
    NSMutableString *memberString = [[NSMutableString alloc] init];

    for (int i = 0; !firstNameAdded && i < sceneElement.members.lamps.count; i++)
    {
        NSString *lampID = [sceneElement.members.lamps objectAtIndex: i];
        LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID: lampID];

        if (lamp != nil)
        {
            [memberString appendString: lamp.name];
            firstNameAdded = YES;
        }
    }

    for (int i = 0; !firstNameAdded && i < sceneElement.members.lampGroups.count; i++)
    {
        NSString *groupID = [sceneElement.members.lampGroups objectAtIndex: i];
        LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: groupID];

        if (group != nil)
        {
            [memberString appendString: group.name];
            firstNameAdded = YES;
        }
    }

    unsigned long count = sceneElement.members.lamps.count + sceneElement.members.lampGroups.count - 1;

    if (count > 0)
    {
        [memberString appendString: [NSString stringWithFormat: @" (%lu more)", count]];
    }

    return memberString;
}

-(void)plusButtonPressed
{
    [self performSegueWithIdentifier: @"CreateSceneElement" sender: self];
}

@end
