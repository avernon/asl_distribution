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
#import "LSFUtilityFunctions.h"
#import <LSFSDKLightingDirector.h>

@interface LSFScenesChangeNameViewController ()

@property (nonatomic) BOOL doneButtonPressed;

-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification;
-(void)sceneChangedNotificationReceived:(NSNotification *)notification;
-(void)sceneRemovedNotificationReceived:(NSNotification *)notification;
-(void)alertSceneDeleted: (LSFSDKScene *)scene;

@end

@implementation LSFScenesChangeNameViewController

@synthesize sceneID = _sceneID;
@synthesize sceneNameTextField = _sceneNameTextField;
@synthesize doneButtonPressed = _doneButtonPressed;

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    //Set notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(sceneChangedNotificationReceived:) name: @"LSFSceneChangedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(sceneRemovedNotificationReceived:) name: @"LSFSceneRemovedNotification" object: nil];

    [self.sceneNameTextField becomeFirstResponder];
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

    if ([self.sceneID isEqualToString: scene.theID])
    {
        self.sceneNameTextField.text = [scene name];
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

-(void)alertSceneDeleted: (LSFSDKScene *)scene
{
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

    BOOL nameMatchFound = [[[[LSFSDKLightingDirector getLightingDirector] scenes] valueForKeyPath: @"name"] containsObject: self.sceneNameTextField.text];

    if (!nameMatchFound)
    {
        self.doneButtonPressed = YES;
        [textField resignFirstResponder];

        dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
            LSFSDKScene *scene = [[LSFSDKLightingDirector getLightingDirector] getSceneWithID: self.sceneID];
            [scene rename: self.sceneNameTextField.text];
        });


        return YES;
    }

    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Duplicate Name"
                                                  message: [NSString stringWithFormat: @"Warning: there is already a scene named \"%@.\" Although it's possible to use the same name for more than one scene, it's better to give each scene a unique name.\n\nKeep duplicate scene name \"%@\"?", self.sceneNameTextField.text, self.sceneNameTextField.text]
                                                 delegate: self
                                        cancelButtonTitle: @"NO"
                                        otherButtonTitles: @"YES", nil];
    [alert show];

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

        dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
            LSFSDKScene *scene = [[LSFSDKLightingDirector getLightingDirector] getSceneWithID: self.sceneID];
            [scene rename: self.sceneNameTextField.text];
        });
    }
}

@end
