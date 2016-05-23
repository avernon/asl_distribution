/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

#import "ViewController.h"
#import "LSFSDKLightingDirector.h"
#import "LSFSDKLightingController.h"
#import "LSFSDKLightingControllerConfigurationBase.h"
#import "LSFSDKAllLightingItemDelegateBase.h"
#import "LSFSDKScene.h"

/*
 * Global delegate that updates the table using the Scene Initialized and
 * Scene Removed callbacks.
 */
@interface MyLightingDelegate : LSFSDKAllLightingItemDelegateBase

@property (nonatomic, strong) NSMutableArray *localSceneList;
@property (nonatomic, strong) UITableView *localTableView;

@end

@implementation MyLightingDelegate

@synthesize localSceneList = _localSceneList;
@synthesize localTableView = _localTableView;

-(id)initWithSceneList: (NSMutableArray *)sceneList andTableView: (UITableView *)tableView
{
    self = [super init];

    if (self)
    {
        self.localSceneList = sceneList;
        self.localTableView = tableView;
    }

    return self;
}

-(void)onSceneInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andScene: (LSFSDKScene *) scene
{
    //Update UI when Scene is initialized
    [self.localSceneList addObject: scene];

    dispatch_async(dispatch_get_main_queue(), ^{
        [self.localTableView reloadData];
    });
}

-(void)onSceneRemoved: (LSFSDKScene *)scene
{
    //Update UI when Scene is removed
    [self.localSceneList removeObject: scene];

    dispatch_async(dispatch_get_main_queue(), ^{
        [self.localTableView reloadData];
    });
}

-(void)onSceneChanged: (LSFSDKScene *)scene
{
    //Update UI when Scene is changed
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.localTableView reloadData];
    });
}
@end

@interface ViewController ()

@property (nonatomic, strong) NSMutableArray *sceneList;
@property (nonatomic, strong) LSFSDKLightingDirector *lightingDirector;
@property (nonatomic, strong) MyLightingDelegate *myLightingDelegate;
@property (nonatomic, strong) LSFSDKLightingControllerConfigurationBase *config;

@end

@implementation ViewController

@synthesize sceneList = _sceneList;
@synthesize lightingDirector = _lightingDirector;
@synthesize myLightingDelegate = _myLightingDelegate;
@synthesize config = _config;

-(void)viewDidLoad
{
    [super viewDidLoad];

    // STEP 1: Create array used by UITableView
    self.sceneList = [[NSMutableArray alloc] init];

    // STEP 2: Initialize a lighting controller with default configuration
    self.config = [[LSFSDKLightingControllerConfigurationBase alloc]initWithKeystorePath: @"Documents"];
    LSFSDKLightingController *lightingController = [LSFSDKLightingController getLightingController];
    [lightingController initializeWithControllerConfiguration: self.config];
    [lightingController start];

    // STEP 3: Instantiate the lighting director, add custom delegate, and start
    self.myLightingDelegate = [[MyLightingDelegate alloc] initWithSceneList: self.sceneList andTableView: self.tableView];
    self.lightingDirector = [LSFSDKLightingDirector getLightingDirector];
    [self.lightingDirector addDelegate: self.myLightingDelegate];
    [self.lightingDirector start];

}

-(void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

-(NSInteger)tableView: (UITableView *)tableView numberOfRowsInSection: (NSInteger)section
{
    return [self.sceneList count];
}

-(UITableViewCell *)tableView: (UITableView *)tableView cellForRowAtIndexPath: (NSIndexPath *)indexPath
{
    static NSString *simpleTableIdentifier = @"SimpleTableCell";

    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: simpleTableIdentifier];

    if (cell == nil)
    {
        cell = [[UITableViewCell alloc] initWithStyle: UITableViewCellStyleDefault reuseIdentifier: simpleTableIdentifier];
    }

    LSFSDKScene * scene = (LSFSDKScene *)[self.sceneList objectAtIndex: indexPath.row];
    cell.textLabel.text = scene.name;

    return cell;
}

-(void)tableView: (UITableView *)tableView didSelectRowAtIndexPath: (NSIndexPath *)indexPath
{
    // Apply the Scene
    LSFSDKScene * scene = (LSFSDKScene *)[self.sceneList objectAtIndex: indexPath.row];
    [scene apply];

    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

@end
