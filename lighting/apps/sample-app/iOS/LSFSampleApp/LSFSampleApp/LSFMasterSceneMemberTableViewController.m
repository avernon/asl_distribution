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

#import "LSFMasterSceneMembersTableViewController.h"
#import <LSFSDKLightingDirector.h>

@interface LSFMasterSceneMembersTableViewController ()

@property (nonatomic, strong) UIBarButtonItem *cancelButton;

-(void)leaderModelChangedNotificationReceived: (NSNotification *)notification;
-(void)masterSceneChangedNotificationReceived: (NSNotification *)notification;
-(void)masterSceneRemovedNotificationReceived: (NSNotification *)notification;
-(void)alertMasterSceneDeleted: (LSFSDKMasterScene *)masterScene;
-(void)sortScenesByName: (NSArray *)scenes;

@end

@implementation LSFMasterSceneMembersTableViewController

@synthesize pendingMasterScene = _pendingMasterScene;
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
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(masterSceneChangedNotificationReceived:) name: @"LSFMasterSceneChangedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(masterSceneRemovedNotificationReceived:) name: @"LSFMasterSceneRemovedNotification" object: nil];

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

    //Clear scenes and master scenes notification handler
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

-(void)masterSceneChangedNotificationReceived: (NSNotification *) notification
{
    LSFSDKMasterScene *masterScene = [notification.userInfo valueForKey: @"masterScene"];

    if ([self.pendingMasterScene.theID isEqualToString: [masterScene theID]])
    {
        [self buildTableArray];
        [self.tableView reloadData];
    }
}

-(void)masterSceneRemovedNotificationReceived: (NSNotification *) notification
{
    LSFSDKMasterScene *masterScene = [notification.userInfo valueForKey: @"masterScene"];

    if ([self.pendingMasterScene.theID isEqualToString: [masterScene theID]])
    {
        [self alertMasterSceneDeleted: masterScene];
    }
}

-(void)alertMasterSceneDeleted: (LSFSDKMasterScene *)masterScene
{
    [self dismissViewControllerAnimated: NO completion: nil];

    dispatch_async(dispatch_get_main_queue(), ^{
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Master Scene Not Found"
                                                        message: [NSString stringWithFormat: @"The master scene \"%@\" no longer exists.", [masterScene name]]
                                                       delegate: nil
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];
    });
}

/*
 * Override table view delegate method so the cell knows how to draw itself
 */
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    LSFSDKScene *basicScene = [self.dataArray objectAtIndex: [indexPath row]];
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: @"SceneMembers" forIndexPath:indexPath];

    cell.textLabel.text = [basicScene name];
    cell.imageView.image = [UIImage imageNamed:@"scene_set_icon.png"];

    if ([self.pendingMasterScene.memberIDs containsObject: [basicScene theID]])
    {
        cell.accessoryType = UITableViewCellAccessoryCheckmark;
        [self.selectedRows addObject: indexPath];
    }
    else
    {
        cell.accessoryType = UITableViewCellAccessoryNone;
    }

    return cell;
}

-(NSString *)tableView: (UITableView *)tableView titleForHeaderInSection: (NSInteger)section
{
    return @"Select the scenes in this master scene";
}

/*
 * Override public functions in LSFMembersTableViewController
 */
-(void)buildTableArray
{
    NSArray *scenes = [[LSFSDKLightingDirector getLightingDirector] scenes];
    [self sortScenesByName: scenes];
}

-(void)processSelectedRows
{
    NSLog(@"LSFMasterSceneMembersTableViewController - processSelectedRows() executing");

    NSMutableArray *sceneIDs = [[NSMutableArray alloc] init];

    for (NSIndexPath *indexPath in self.selectedRows)
    {
        LSFSDKScene *basicScene = [self.dataArray objectAtIndex: indexPath.row];
        [sceneIDs addObject: basicScene.theID];
    }

    self.pendingMasterScene.memberIDs = sceneIDs;

    if (!self.pendingMasterScene.theID.length) // if nil or empty
    {
        dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
            NSMutableArray *scenes = [[NSMutableArray alloc] init];

            for (NSString* memberID in self.pendingMasterScene.memberIDs)
            {
                LSFSDKScene* scene = [[LSFSDKLightingDirector getLightingDirector] getSceneWithID: memberID];
                [scenes addObject: scene];
            }

            [[LSFSDKLightingDirector getLightingDirector] createMasterSceneWithScenes: scenes name: self.pendingMasterScene.name];
        });
    }
    else
    {
        dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
            NSMutableArray *scenes = [[NSMutableArray alloc] init];

            for (NSString* memberID in self.pendingMasterScene.memberIDs)
            {
                LSFSDKScene* scene = [[LSFSDKLightingDirector getLightingDirector] getSceneWithID: memberID];
                [scenes addObject: scene];
            }

            LSFSDKMasterScene *masterScene = [[LSFSDKLightingDirector getLightingDirector] getMasterSceneWithID: self.pendingMasterScene.theID];
            [masterScene modify: scenes];
        });
    }

    [self dismissViewControllerAnimated: YES completion: nil];
}

/*
 * Done Button Pressed Handler
 */
-(IBAction)doneButtonPressed: (id)sender
{
    NSLog(@"Done button pressed");

    if ([self.selectedRows count] == 0)
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                        message: @"You must select at least one scene to create a master scene."
                                                       delegate: nil
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];
    }
    else
    {
        [self processSelectedRows];
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
 * Private Functions
 */
-(void)sortScenesByName: (NSArray *)scenes
{
    NSMutableArray *sortedArray = [NSMutableArray arrayWithArray: [scenes sortedArrayUsingComparator: ^NSComparisonResult(id obj1, id obj2) {
        LSFSDKScene *scene1 = (LSFSDKScene *)obj1;
        LSFSDKScene *scene2 = (LSFSDKScene *)obj1;
        return [(NSString *)[scene1 name] compare: (NSString *)[scene2 name] options:NSCaseInsensitiveSearch];
    }]];

    self.dataArray = sortedArray;
}

@end
