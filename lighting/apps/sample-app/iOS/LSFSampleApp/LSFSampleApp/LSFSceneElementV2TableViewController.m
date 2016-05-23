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

#import "LSFSceneElementV2TableViewController.h"
#import "LSFSceneElementV2MembersTableViewController.h"
#import "LSFUtilityFunctions.h"
#import "LSFPendingEffect.h"
#import "LSFLightingListenerUtil.h"
#import <LSFSDKLightingDirector.h>

@interface LSFSceneElementV2TableViewController ()

@end

@implementation LSFSceneElementV2TableViewController

@synthesize pendingScene = _pendingScene;

-(void)viewDidLoad
{
    [super viewDidLoad];

    UIBarButtonItem *addButton = [[UIBarButtonItem alloc]
                      initWithBarButtonSystemItem:UIBarButtonSystemItemAdd
                      target: self
                      action: @selector(plusButtonPressed)];

    UIBarButtonItem *saveButton = [[UIBarButtonItem alloc]
                       initWithBarButtonSystemItem: UIBarButtonSystemItemSave
                       target: self
                       action: @selector(saveButtonPressed)];

    self.navigationItem.rightBarButtonItems = @[saveButton, addButton];

    if (self.pendingScene.pendingSceneElements == nil)
    {
        self.pendingScene.pendingSceneElements = [[NSMutableArray alloc] init];
    }
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];
    [self.tableView reloadData];
}

-(NSInteger)numberOfSectionsInTableView: (UITableView *)tableView
{
    return 1;
}

-(NSInteger)tableView: (UITableView *)tableView numberOfRowsInSection: (NSInteger)section
{
    return self.pendingScene.pendingSceneElements.count;
}

-(NSString *)tableView: (UITableView *)tableView titleForHeaderInSection: (NSInteger)section
{
    return @"Tap + to add a new scene element";
}

-(UITableViewCell *)tableView: (UITableView *)tableView cellForRowAtIndexPath: (NSIndexPath *)indexPath
{
    LSFPendingSceneElement *sceneElement = [self.pendingScene.pendingSceneElements objectAtIndex: indexPath.row];

    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"SceneElement" forIndexPath:indexPath];

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

    return cell;
}

-(void)prepareForSegue: (UIStoryboardSegue *)segue sender: (id)sender
{
    if ([segue.identifier isEqualToString: @"SceneElementV2Members"])
    {
        UINavigationController *nc = [segue destinationViewController];
        LSFSceneElementV2MembersTableViewController *semtvc = (LSFSceneElementV2MembersTableViewController *) [nc topViewController];
        semtvc.hasNextButton = YES;
        semtvc.allowCancel = YES;
        semtvc.pendingScene = self.pendingScene;
        semtvc.pendingSceneElement = [[LSFPendingSceneElement alloc] init];
    }
}

-(void)plusButtonPressed
{
    NSLog(@"%s", __FUNCTION__);
    [self performSegueWithIdentifier: @"SceneElementV2Members" sender: self];
}

-(void)saveButtonPressed
{
    NSLog(@"%s", __FUNCTION__);
    [self processPendingScene: self.pendingScene];
    [self.navigationController dismissViewControllerAnimated: YES completion: nil];
}

-(void)processPendingScene: (LSFPendingSceneV2 *)pendingScene
{
    for (LSFPendingSceneElement *elem in pendingScene.pendingSceneElements)
    {
        [LSFLightingListenerUtil listenForTrackingID: [LSFUtilityFunctions createEffectFromPendingItem: elem.pendingEffect] perform: ^(id item) {

            elem.pendingEffect.theID = ((id<LSFSDKEffect>)item).theID;

            [LSFLightingListenerUtil listenForTrackingID: [LSFUtilityFunctions createSceneElementFromPendingItem: elem] perform: ^(id item) {

                elem.theID = ((LSFSDKSceneElement *)item).theID;

                    if ([self.pendingScene hasValidSceneElements])
                    {
                        [LSFUtilityFunctions createSceneFromPendingItem: pendingScene];
                    }
            }];
        }];
    }
}

@end
