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

#import "LSFScenesChangeNameViewController.h"
#import "LSFDispatchQueue.h"
#import "LSFLampGroupManager.h"
#import "LSFAllJoynManager.h"
#import "LSFSceneModelContainer.h"
#import "LSFUtilityFunctions.h"
#import "LSFEnums.h"

@interface LSFScenesChangeNameViewController ()

@property (nonatomic) BOOL doneButtonPressed;
@property (nonatomic, strong) LSFSceneDataModel *sceneModel;

-(void)controllerNotificationReceived: (NSNotification *)notification;
-(void)sceneNotificationReceived: (NSNotification *)notification;
-(void)reloadSceneName;
-(void)deleteScenesWithIDs: (NSArray *)sceneIDs andNames: (NSArray *)sceneNames;
-(BOOL)checkForDuplicateName: (NSString *)name;

@end

@implementation LSFScenesChangeNameViewController

@synthesize sceneID = _sceneID;
@synthesize sceneModel = _sceneModel;
@synthesize sceneNameTextField = _sceneNameTextField;
@synthesize doneButtonPressed = _doneButtonPressed;

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    LSFSceneModelContainer *container = [LSFSceneModelContainer getSceneModelContainer];
    NSMutableDictionary *scenes = container.sceneContainer;
    self.sceneModel = [scenes valueForKey: self.sceneID];

    //Set notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(controllerNotificationReceived:) name: @"ControllerNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(sceneNotificationReceived:) name: @"SceneNotification" object: nil];

    [self.sceneNameTextField becomeFirstResponder];
    self.sceneNameTextField.text = self.sceneModel.name;
    self.doneButtonPressed = NO;
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
        [self.navigationController popToRootViewControllerAnimated: YES];
    }
}

/*
 * SceneNotification Handler
 */
-(void)sceneNotificationReceived: (NSNotification *)notification
{
    NSString *sceneID = [notification.userInfo valueForKey: @"sceneID"];
    NSNumber *callbackOp = [notification.userInfo valueForKey: @"operation"];
    NSArray *sceneIDs = [notification.userInfo valueForKey: @"sceneIDs"];
    NSArray *sceneNames = [notification.userInfo valueForKey: @"sceneNames"];

    if ([self.sceneID isEqualToString: sceneID] || [sceneIDs containsObject: self.sceneID])
    {
        switch (callbackOp.intValue)
        {
            case SceneNameUpdated:
                [self reloadSceneName];
                break;
            case SceneDeleted:
                [self deleteScenesWithIDs: sceneIDs andNames: sceneNames];
                break;
            default:
                break;
        }
    }
}

-(void)reloadSceneName
{
    LSFSceneModelContainer *scenesContainer = [LSFSceneModelContainer getSceneModelContainer];
    NSMutableDictionary *scenes = scenesContainer.sceneContainer;
    self.sceneModel = [scenes valueForKey: self.sceneID];

    self.sceneNameTextField.text = self.sceneModel.name;
}

-(void)deleteScenesWithIDs: (NSArray *)sceneIDs andNames: (NSArray *)sceneNames
{
    if ([sceneIDs containsObject: self.sceneID])
    {
        int index = [sceneIDs indexOfObject: self.sceneID];

        [self.navigationController popToRootViewControllerAnimated: YES];

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
 * UITextFieldDelegate implementation
 */
-(BOOL)textFieldShouldReturn: (UITextField *)textField
{
    if (![LSFUtilityFunctions checkNameLength: self.sceneNameTextField.text entity: @"Scene Name"])
    {
        return NO;
    }

    if (![LSFUtilityFunctions checkWhiteSpaces:self.sceneNameTextField.text entity: @"Scene Name"])
    {
        return NO;
    }

    BOOL nameMatchFound = [self checkForDuplicateName: self.sceneNameTextField.text];

    if (!nameMatchFound)
    {
        self.doneButtonPressed = YES;
        [textField resignFirstResponder];

        dispatch_async(([LSFDispatchQueue getDispatchQueue]).queue, ^{
            LSFSceneManager *sceneManager = ([LSFAllJoynManager getAllJoynManager]).lsfSceneManager;
            [sceneManager setSceneNameWithID: self.sceneID andSceneName: self.sceneNameTextField.text];
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
        [alertView dismissWithClickedButtonIndex: 0 animated: YES];
    }

    if (buttonIndex == 1)
    {
        [alertView dismissWithClickedButtonIndex: 1 animated: YES];

        self.doneButtonPressed = YES;
        [self.sceneNameTextField resignFirstResponder];

        dispatch_async(([LSFDispatchQueue getDispatchQueue]).queue, ^{
            LSFSceneManager *sceneManager = ([LSFAllJoynManager getAllJoynManager]).lsfSceneManager;
            [sceneManager setSceneNameWithID: self.sceneID andSceneName: self.sceneNameTextField.text];
        });
    }
}

/*
 * Private functions
 */
-(BOOL)checkForDuplicateName: (NSString *)name
{
    LSFSceneModelContainer *container = [LSFSceneModelContainer getSceneModelContainer];
    NSDictionary *scenes = container.sceneContainer;

    for (LSFSceneDataModel *model in [scenes allValues])
    {
        if ([name isEqualToString: model.name])
        {
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Duplicate Name"
                                                            message: [NSString stringWithFormat: @"Warning: there is already a scene named \"%@.\" Although it's possible to use the same name for more than one scene, it's better to give each scene a unique name.\n\nKeep duplicate scene name \"%@\"?", name, name]
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
