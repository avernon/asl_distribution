/******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

#import "LSFSceneV2InfoTableViewController.h"
#import "LSFEnterSceneV2NameTableViewController.h"
#import "LSFPendingSceneElement.h"
#import "LSFSceneElementV2MembersTableViewController.h"
#import "LSFUtilityFunctions.h"
#import <LSFSDKLightingDirector.h>

@interface LSFSceneV2InfoTableViewController ()

@end

@implementation LSFSceneV2InfoTableViewController

@synthesize pendingScene = _pendingScene;

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear: animated];

    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(sceneChangedNotificationReceived:) name: @"LSFSceneChangedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(sceneRemovedNotificationReceived:) name: @"LSFSceneRemovedNotification" object: nil];

    UIBarButtonItem *addButton = [[UIBarButtonItem alloc]
                                  initWithBarButtonSystemItem:UIBarButtonSystemItemAdd
                                  target: self
                                  action: @selector(plusButtonPressed)];

    self.navigationItem.rightBarButtonItems = @[self.editButtonItem, addButton];

    [self.tableView reloadData];
}

-(void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear: animated];
    [[NSNotificationCenter defaultCenter] removeObserver: self];
}

-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 2;
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return (section == 0) ? 1 : self.pendingScene.pendingSceneElements.count;
}

-(NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    return (section == 1) ? @"Scene Element" : @"";
}

-(NSString *)tableView: (UITableView *)tableView titleForFooterInSection: (NSInteger)section
{
    return (section == 1) ? @"Tap + to add a new scene element" : @"";
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.section == 0)
    {
        UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle: UITableViewCellStyleValue1 reuseIdentifier: nil];
        cell.textLabel.text = @"Scene Name";
        cell.detailTextLabel.text = self.pendingScene.name;
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        return cell;
    }
    else
    {
        UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle: UITableViewCellStyleDefault reuseIdentifier: nil];

        LSFPendingSceneElement *sceneElement = [self.pendingScene.pendingSceneElements objectAtIndex: indexPath.row];

        cell.textLabel.text = [LSFUtilityFunctions memberStringForPendingSceneElement: sceneElement];

        switch (sceneElement.pendingEffect.type)
        {
            case PRESET:
                cell.imageView.image = [UIImage imageNamed: @"list_constant_icon.png"];
                cell.detailTextLabel.text = @"Preset";
                break;
            case TRANSITION:
                cell.imageView.image = [UIImage imageNamed: @"list_transition_icon.png"];
                cell.detailTextLabel.text = @"Transition Effect";
                break;
            case PULSE:
                cell.imageView.image = [UIImage imageNamed: @"list_pulse_icon.png"];
                cell.detailTextLabel.text = @"Pulse Effect";
                break;
            default:
                NSLog(@"Unknown effect type");
                break;
        }

        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;

        return cell;
    }
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.section == 0)
    {
        [self performSegueWithIdentifier: @"ChangeSceneName" sender: nil];
    }
    else if (indexPath.section == 1)
    {
        [self performSegueWithIdentifier: @"SceneElementV2" sender: indexPath];
    }
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier isEqualToString: @"ChangeSceneName"])
    {
        LSFEnterSceneV2NameTableViewController *esnvc = [segue destinationViewController];
        esnvc.pendingScene = self.pendingScene;
    }
    else if ([segue.identifier isEqualToString: @"SceneElementV2"])
    {
        UINavigationController *nc = [segue destinationViewController];
        LSFSceneElementV2MembersTableViewController *semtvc = (LSFSceneElementV2MembersTableViewController *)[nc topViewController];
        semtvc.pendingScene = self.pendingScene;
        semtvc.pendingSceneElement = (sender) ? [self.pendingScene.pendingSceneElements objectAtIndex: ((NSIndexPath *)sender).row] : [[LSFPendingSceneElement alloc] init];
        semtvc.hasNextButton = YES;
        semtvc.allowCancel = YES;
    }
}

-(BOOL)tableView: (UITableView *)tableView canEditRowAtIndexPath: (NSIndexPath *)indexPath
{
    return indexPath.section == 1 && self.pendingScene.pendingSceneElements.count > 1;
}

-(void)tableView: (UITableView *)tableView commitEditingStyle: (UITableViewCellEditingStyle)editingStyle forRowAtIndexPath: (NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete)
    {
        NSLog(@"Delete button pressed");

        NSString *sceneElementID = [[self.pendingScene.pendingSceneElements objectAtIndex: indexPath.row] theID];
        NSString *effectID = [[[self.pendingScene.pendingSceneElements objectAtIndex: indexPath.row] pendingEffect] theID];
        [self.pendingScene.pendingSceneElements removeObjectAtIndex: indexPath.row];

        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation: UITableViewRowAnimationFade];

        dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{

            LSFSDKScene *scene = [[LSFSDKLightingDirector getLightingDirector] getSceneWithID: self.pendingScene.theID];
            if ([scene isKindOfClass: [LSFSDKSceneV2 class]])
            {
                LSFSDKSceneV2 *sceneV2 = (LSFSDKSceneV2 *)scene;

                NSMutableArray *elementsInScene = [[NSMutableArray alloc] init];
                for (LSFPendingSceneElement *pendingElem in self.pendingScene.pendingSceneElements)
                {
                    LSFSDKSceneElement *elem = [[LSFSDKLightingDirector getLightingDirector] getSceneElementWithID: pendingElem.theID];
                    if (elem)
                    {
                        [elementsInScene addObject: elem];
                    }
                }

                [sceneV2 modify: elementsInScene];
            }

            dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
                [[[LSFSDKLightingDirector getLightingDirector] getSceneElementWithID: sceneElementID] deleteItem];
                [[[LSFSDKLightingDirector getLightingDirector] getEffectWithID: effectID] deleteItem];
            });
        });

    }
}

-(void)plusButtonPressed
{
    NSLog(@"Plus button pressed");
    [self performSegueWithIdentifier: @"SceneElementV2" sender: nil];
}

-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification
{
    LSFSDKController *leaderModel = [notification.userInfo valueForKey: @"leader"];
    if (![leaderModel connected])
    {
        [self dismissViewControllerAnimated: YES completion: nil];
        [self.navigationController popToRootViewControllerAnimated: YES];
    }
}

-(void)sceneChangedNotificationReceived: (NSNotification *)notification
{
    LSFSDKScene *scene = [notification.userInfo valueForKey: @"scene"];

    if ([scene.theID isEqualToString: self.pendingScene.theID])
    {
        self.pendingScene.name = scene.name;
        [self.tableView reloadData];
    }
}

-(void)sceneRemovedNotificationReceived: (NSNotification *)notification
{
    LSFSDKScene *scene = [notification.userInfo valueForKey: @"scene"];

    if ([scene.theID isEqualToString: self.pendingScene.theID])
    {
        [self dismissViewControllerAnimated: YES completion: nil];

        dispatch_async(dispatch_get_main_queue(), ^{
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Scene Not Found"
                                                            message: [NSString stringWithFormat: @"The scene \"%@\" no longer exists.", [scene name]]
                                                           delegate: nil
                                                  cancelButtonTitle: @"OK"
                                                  otherButtonTitles: nil];
            [alert show];
        });
    }
}

@end
