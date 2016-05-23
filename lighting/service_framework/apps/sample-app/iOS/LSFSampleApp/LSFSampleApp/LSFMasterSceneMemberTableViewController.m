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
#import "LSFSceneModelContainer.h"
#import "LSFSceneDataModel.h"
#import "LSFAllJoynManager.h"
#import "LSFDispatchQueue.h"
#import "LSFEnums.h"

@interface LSFMasterSceneMembersTableViewController ()

@property (nonatomic, strong) UIBarButtonItem *cancelButton;

-(void)controllerNotificationReceived: (NSNotification *)notification;
-(void)masterSceneNotificationReceived: (NSNotification *)notification;
-(void)updateMasterSceneWithID: (NSString *)masterSceneID;
-(void)deleteMasterScenesWithIDs: (NSArray *)masterSceneIDs andNames: (NSArray *)masterSceneNames;
-(void)sortScenesByName: (NSArray *)scenes;

@end

@implementation LSFMasterSceneMembersTableViewController

@synthesize masterSceneModel = _masterSceneModel;
@synthesize usesCancel = _usesCancel;
@synthesize cancelButton = _cancelButton;

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    //Set master scenes notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(controllerNotificationReceived:) name: @"ControllerNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(masterSceneNotificationReceived:) name: @"MasterSceneNotification" object: nil];

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
 * ControllerNotification Handler
 */
-(void)controllerNotificationReceived: (NSNotification *)notification
{
    NSDictionary *userInfo = notification.userInfo;
    NSNumber *controllerStatus = [userInfo valueForKey: @"status"];

    if (controllerStatus.intValue == Disconnected)
    {
        [self dismissViewControllerAnimated: YES completion: nil];
    }
}

/*
 * MasterSceneNotification Handler
 */
-(void)masterSceneNotificationReceived: (NSNotification *)notification
{
    NSString *masterSceneID = [notification.userInfo valueForKey: @"masterSceneID"];
    NSNumber *callbackOp = [notification.userInfo valueForKey: @"operation"];
    NSArray *masterSceneIDs = [notification.userInfo valueForKey: @"masterSceneIDs"];
    NSArray *masterSceneNames = [notification.userInfo valueForKey: @"masterSceneNames"];

    if ([self.masterSceneModel.theID isEqualToString: masterSceneID] || [masterSceneIDs containsObject: self.masterSceneModel.theID])
    {
        switch (callbackOp.intValue)
        {
            case MasterSceneUpdated:
                [self updateMasterSceneWithID: masterSceneID];
                break;
            case MasterSceneDeleted:
                [self deleteMasterScenesWithIDs: masterSceneIDs andNames: masterSceneNames];
                break;
            default:
                break;
        }
    }
}

-(void)updateMasterSceneWithID: (NSString *)masterSceneID
{
    [self buildTableArray];
    [self.tableView reloadData];
}

-(void)deleteMasterScenesWithIDs: (NSArray *)masterSceneIDs andNames: (NSArray *)masterSceneNames
{
    int index = [masterSceneIDs indexOfObject: self.masterSceneModel.theID];

    [self dismissViewControllerAnimated: NO completion: nil];

    dispatch_async(dispatch_get_main_queue(), ^{
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Master Scene Not Found"
                                                        message: [NSString stringWithFormat: @"The master scene \"%@\" no longer exists.", [masterSceneNames objectAtIndex: index]]
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
    LSFSceneDataModel *model = [self.dataArray objectAtIndex: [indexPath row]];
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: @"SceneMembers" forIndexPath:indexPath];

    cell.textLabel.text = model.name;
    cell.imageView.image = [UIImage imageNamed:@"scene_set_icon.png"];

    if ([self.masterSceneModel.masterScene.sceneIDs containsObject: model.theID])
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
    LSFSceneModelContainer *scenesContainer = [LSFSceneModelContainer getSceneModelContainer];
    NSMutableDictionary *scenes = scenesContainer.sceneContainer;
    NSMutableArray *scenesArray = [NSMutableArray arrayWithArray: [scenes allValues]];

    [self sortScenesByName: [NSMutableArray arrayWithArray: scenesArray]];
}

-(void)processSelectedRows
{
    NSLog(@"LSFMasterSceneMembersTableViewController - processSelectedRows() executing");

    NSMutableArray *sceneIDs = [[NSMutableArray alloc] init];

    for (NSIndexPath *indexPath in self.selectedRows)
    {
        LSFSceneDataModel *sceneDataModel = [self.dataArray objectAtIndex: indexPath.row];
        [sceneIDs addObject: sceneDataModel.theID];
    }

    self.masterSceneModel.masterScene.sceneIDs = sceneIDs;

    if ([self.masterSceneModel.theID isEqualToString: @""])
    {
        dispatch_async(([LSFDispatchQueue getDispatchQueue]).queue, ^{
            LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
            [ajManager.lsfMasterSceneManager createMasterScene: self.masterSceneModel.masterScene withName: self.masterSceneModel.name];
        });
    }
    else
    {
        dispatch_async(([LSFDispatchQueue getDispatchQueue]).queue, ^{
            LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
            [ajManager.lsfMasterSceneManager updateMasterSceneWithID: self.masterSceneModel.theID andMasterScene: self.masterSceneModel.masterScene];
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
    NSMutableArray *sortedArray = [NSMutableArray arrayWithArray: [scenes sortedArrayUsingComparator: ^NSComparisonResult(id a, id b) {
        NSString *first = [(LSFModel *)a name];
        NSString *second = [(LSFModel *)b name];
        return [first localizedCaseInsensitiveCompare: second];
    }]];

    self.dataArray = sortedArray;
}

@end
