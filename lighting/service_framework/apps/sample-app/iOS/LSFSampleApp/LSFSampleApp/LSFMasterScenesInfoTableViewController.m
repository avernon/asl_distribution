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

#import "LSFMasterScenesInfoTableViewController.h"
#import "LSFMasterSceneMembersTableViewController.h"
#import "LSFMasterScenesChangeNameViewController.h"
#import "LSFMasterSceneDataModel.h"
#import "LSFMasterSceneModelContainer.h"
#import "LSFDispatchQueue.h"
#import "LSFAllJoynManager.h"
#import "LSFEnums.h"

@interface LSFMasterScenesInfoTableViewController ()

@property (nonatomic, strong) LSFMasterSceneDataModel *masterSceneModel;

-(void)controllerNotificationReceived: (NSNotification *)notification;
-(void)masterSceneNotificationReceived: (NSNotification *)notification;
-(void)reloadMasterSceneWithID: (NSString *)masterSceneID;
-(void)deleteMasterScenesWithIDs: (NSArray *)masterSceneIDs andNames: (NSArray *)masterSceneNames;

@end

@implementation LSFMasterScenesInfoTableViewController

@synthesize masterSceneID = _masterSceneID;
@synthesize masterSceneModel = _masterSceneModel;

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];

    if (!ajManager.isConnectedToController)
    {
        [self.navigationController popToRootViewControllerAnimated: NO];
    }

    //Set master scenes notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(controllerNotificationReceived:) name: @"ControllerNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(masterSceneNotificationReceived:) name: @"MasterSceneNotification" object: nil];

    [self reloadMasterSceneWithID: self.masterSceneID];
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
        [self.navigationController popToRootViewControllerAnimated: YES];
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

    if ([self.masterSceneID isEqualToString: masterSceneID] || [masterSceneIDs containsObject: self.masterSceneID])
    {
        switch (callbackOp.intValue)
        {
            case SceneNameUpdated:
                [self reloadMasterSceneWithID: masterSceneID];
                break;
            case SceneDeleted:
                [self deleteMasterScenesWithIDs: masterSceneIDs andNames: masterSceneNames];
                break;
            default:
                break;
        }
    }
}

-(void)reloadMasterSceneWithID: (NSString *)masterSceneID
{
    LSFMasterSceneModelContainer *container = [LSFMasterSceneModelContainer getMasterSceneModelContainer];
    NSMutableDictionary *masterSceneDictionary = container.masterScenesContainer;
    self.masterSceneModel = [masterSceneDictionary valueForKey: self.masterSceneID];

    if (self.masterSceneModel == nil)
    {
        [self.navigationController popToRootViewControllerAnimated: YES];
    }
    else
    {
        [self.tableView reloadData];
    }
}

-(void)deleteMasterScenesWithIDs: (NSArray *)masterSceneIDs andNames: (NSArray *)masterSceneNames
{
    if ([masterSceneIDs containsObject: self.masterSceneID])
    {
        int index = [masterSceneIDs indexOfObject: self.masterSceneID];

        [self.navigationController popToRootViewControllerAnimated: YES];

        dispatch_async(dispatch_get_main_queue(), ^{
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Master Scene Not Found"
                                                            message: [NSString stringWithFormat: @"The master scene \"%@\" no longer exists.", [masterSceneNames objectAtIndex: index]]
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
-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 2;
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return 1;
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.section == 0)
    {
        UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle: UITableViewCellStyleValue1 reuseIdentifier: nil];
        cell.textLabel.text = @"Master Scene Name";
        cell.detailTextLabel.text = self.masterSceneModel.name;
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        return cell;
    }
    else
    {
        UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle: UITableViewCellStyleDefault reuseIdentifier: nil];
        cell.textLabel.text = @"Scenes in the master scene";
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        return cell;
    }
}

-(void)tableView: (UITableView *)tableView didSelectRowAtIndexPath: (NSIndexPath *)indexPath
{
    if (indexPath.section == 0)
    {
        [self performSegueWithIdentifier: @"ChangeMasterSceneName" sender: nil];
    }
    else if (indexPath.section == 1)
    {
        [self performSegueWithIdentifier: @"ModifySceneMembers" sender: nil];
    }
}

/*
 * Segue Function
 */
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier isEqualToString: @"ModifySceneMembers"])
    {
        UINavigationController *nc = (UINavigationController *)[segue destinationViewController];
        LSFMasterSceneMembersTableViewController *msmtvc = (LSFMasterSceneMembersTableViewController *)nc.topViewController;
        msmtvc.masterSceneModel = self.masterSceneModel;
        msmtvc.usesCancel = YES;
    }
    else if ([segue.identifier isEqualToString: @"ChangeMasterSceneName"])
    {
        LSFMasterScenesChangeNameViewController *mscnvc = [segue destinationViewController];
        mscnvc.masterSceneID = self.masterSceneID;
    }
}

@end
