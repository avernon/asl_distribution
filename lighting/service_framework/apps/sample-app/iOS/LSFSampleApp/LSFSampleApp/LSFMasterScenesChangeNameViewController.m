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

#import "LSFMasterScenesChangeNameViewController.h"
#import "LSFMasterSceneModelContainer.h"
#import "LSFMasterSceneDataModel.h"
#import "LSFDispatchQueue.h"
#import "LSFAllJoynManager.h"
#import "LSFUtilityFunctions.h"
#import "LSFEnums.h"

@interface LSFMasterScenesChangeNameViewController ()

@property (nonatomic) BOOL doneButtonPressed;
@property (nonatomic, strong) LSFMasterSceneDataModel *masterSceneModel;

-(void)controllerNotificationReceived: (NSNotification *)notification;
-(void)masterSceneNotificationReceived: (NSNotification *)notification;
-(void)reloadMasterSceneName;
-(void)deleteMasterScenesWithIDs: (NSArray *)sceneIDs andNames: (NSArray *)sceneNames;
-(BOOL)checkForDuplicateName: (NSString *)name;

@end

@implementation LSFMasterScenesChangeNameViewController

@synthesize masterSceneID = _masterSceneID;
@synthesize masterSceneNameTextField = _masterSceneNameTextField;
@synthesize doneButtonPressed = _doneButtonPressed;
@synthesize masterSceneModel = _masterSceneModel;

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

    LSFMasterSceneModelContainer *container = [LSFMasterSceneModelContainer getMasterSceneModelContainer];
    NSMutableDictionary *masterScenes = container.masterScenesContainer;
    self.masterSceneModel = [masterScenes objectForKey: self.masterSceneID];

    [self.masterSceneNameTextField becomeFirstResponder];
    self.masterSceneNameTextField.text = self.masterSceneModel.name;
    self.doneButtonPressed = NO;
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
                [self reloadMasterSceneName];
                break;
            case SceneDeleted:
                [self deleteMasterScenesWithIDs: masterSceneIDs andNames: masterSceneNames];
                break;
            default:
                break;
        }
    }
}

-(void)reloadMasterSceneName
{
    LSFMasterSceneModelContainer *container = [LSFMasterSceneModelContainer getMasterSceneModelContainer];
    NSMutableDictionary *masterScenes = container.masterScenesContainer;
    self.masterSceneModel = [masterScenes objectForKey: self.masterSceneID];

    self.masterSceneNameTextField.text = self.masterSceneModel.name;
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
 * UITextFieldDelegate implementation
 */
-(BOOL)textFieldShouldReturn: (UITextField *)textField
{
    if ([self.masterSceneNameTextField.text isEqualToString: @""])
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"No Master Scene Name"
                                                        message: @"You need to provide a master scene name in order to proceed."
                                                       delegate: nil
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];

        return NO;
    }

    if (![LSFUtilityFunctions checkNameLength: self.masterSceneNameTextField.text entity: @"Master Scene Name"])
    {
        return NO;
    }

    if (![LSFUtilityFunctions checkWhiteSpaces: self.masterSceneNameTextField.text entity:@"Master Scene Name"])
    {
        return NO;
    }

    BOOL nameMatchFound = [self checkForDuplicateName: self.masterSceneNameTextField.text];

    if (!nameMatchFound)
    {
        self.doneButtonPressed = YES;
        [textField resignFirstResponder];

        dispatch_async(([LSFDispatchQueue getDispatchQueue]).queue, ^{
            LSFMasterSceneManager *masterSceneManager = ([LSFAllJoynManager getAllJoynManager]).lsfMasterSceneManager;
            [masterSceneManager setMasterSceneNameWithID: self.masterSceneID andMasterSceneName: self.masterSceneNameTextField.text];
        });

        return YES;
    }

    return NO;
}

-(void)textFieldDidEndEditing: (UITextField *)textField
{
    if (self.doneButtonPressed)
    {
        [self.navigationController popViewControllerAnimated: YES];
    }
}

/*
 * UIAlertViewDelegate implementation
 */
-(void)alertView: (UIAlertView *)alertView clickedButtonAtIndex: (NSInteger)buttonIndex
{
    if (buttonIndex == 0)
    {
        [alertView dismissWithClickedButtonIndex: 0 animated: NO];
    }

    if (buttonIndex == 1)
    {
        [alertView dismissWithClickedButtonIndex: 1 animated: NO];

        self.doneButtonPressed = YES;
        [self.masterSceneNameTextField resignFirstResponder];

        dispatch_async(([LSFDispatchQueue getDispatchQueue]).queue, ^{
            LSFMasterSceneManager *masterSceneManager = ([LSFAllJoynManager getAllJoynManager]).lsfMasterSceneManager;
            [masterSceneManager setMasterSceneNameWithID: self.masterSceneID andMasterSceneName: self.masterSceneNameTextField.text];
        });
    }
}

/*
 * Private functions
 */
-(BOOL)checkForDuplicateName: (NSString *)name
{
    LSFMasterSceneModelContainer *container = [LSFMasterSceneModelContainer getMasterSceneModelContainer];
    NSDictionary *masterScenes = container.masterScenesContainer;

    for (LSFMasterSceneDataModel *model in [masterScenes allValues])
    {
        if ([name isEqualToString: model.name])
        {
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Duplicate Name"
                                                            message: [NSString stringWithFormat: @"Warning: there is already a master scene named \"%@.\" Although it's possible to use the same name for more than one master scene, it's better to give each master scene a unique name.\n\nKeep duplicate master scene name \"%@\"?", name, name]
                                                           delegate: self
                                                  cancelButtonTitle: @"NO"
                                                  otherButtonTitles: @"YES", nil];
            [alert show];

            return YES;
        }
    }

    return NO;
}

@end
