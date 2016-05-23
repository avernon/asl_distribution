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
#import "LSFUtilityFunctions.h"
#import <LSFSDKLightingDirector.h>

@interface LSFMasterScenesChangeNameViewController ()

@property (nonatomic) BOOL doneButtonPressed;

-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification;
-(void)masterSceneChangedNotificationReceived: (NSNotification *)notification;
-(void)masterSceneRemovedNotificationReceived: (NSNotification *)notification;
-(void)reloadMasterSceneName: (NSString *)masterSceneName;
-(void)alertMasterSceneDeleted: (LSFSDKMasterScene *)masterScene;

@end

@implementation LSFMasterScenesChangeNameViewController

@synthesize masterSceneID = _masterSceneID;
@synthesize masterSceneNameTextField = _masterSceneNameTextField;
@synthesize doneButtonPressed = _doneButtonPressed;

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    //Set master scenes notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(masterSceneChangedNotificationReceived:) name: @"LSFMasterSceneChangedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(masterSceneRemovedNotificationReceived:) name: @"LSFMasterSceneRemovedNotification" object: nil];

    LSFSDKMasterScene *masterScene = [[LSFSDKLightingDirector getLightingDirector] getMasterSceneWithID: self.masterSceneID];

    [self.masterSceneNameTextField becomeFirstResponder];
    self.masterSceneNameTextField.text = [masterScene name];
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
 * Notification Handlers
 */
-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification
{
//    LSFSDKController *leaderModel = [notification.userInfo valueForKey: @"leader"];
    LSFSDKController *leader = [notification.userInfo valueForKey: @"leader"];
    if (![leader connected])
    {
        [self dismissViewControllerAnimated: YES completion: nil];
    }
}

-(void)masterSceneChangedNotificationReceived: (NSNotification *)notification
{
    LSFSDKMasterScene *masterScene = [notification.userInfo valueForKey: @"masterScene"];

    if ([self.masterSceneID isEqualToString: [masterScene name]])
    {
        [self reloadMasterSceneName: [masterScene name]];
    }
}

-(void)masterSceneRemovedNotificationReceived: (NSNotification *)notification
{
    LSFSDKMasterScene *masterScene = [notification.userInfo valueForKey: @"masterScene"];

    if ([self.masterSceneID isEqualToString: [masterScene name]])
    {
        [self alertMasterSceneDeleted: masterScene];
    }
}

-(void)reloadMasterSceneName: (NSString*)masterSceneName;
{
    self.masterSceneNameTextField.text = masterSceneName;
}

-(void)alertMasterSceneDeleted: (LSFSDKMasterScene *)masterScene
{
    [self.navigationController popToRootViewControllerAnimated: YES];

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

    BOOL nameMatchFound = [[[[LSFSDKLightingDirector getLightingDirector] masterScenes] valueForKeyPath: @"name"] containsObject: self.masterSceneNameTextField.text];

    if (!nameMatchFound)
    {
        self.doneButtonPressed = YES;
        [textField resignFirstResponder];

        dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
            LSFSDKMasterScene *masterScene = [[LSFSDKLightingDirector getLightingDirector] getMasterSceneWithID: self.masterSceneID];
            [masterScene rename: self.masterSceneNameTextField.text];
        });

        return YES;
    }

    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Duplicate Name"
                                                    message: [NSString stringWithFormat: @"Warning: there is already a master scene named \"%@.\" Although it's possible to use the same name for more than one master scene, it's better to give each master scene a unique name.\n\nKeep duplicate master scene name \"%@\"?", self.masterSceneNameTextField.text, self.masterSceneNameTextField.text]
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
        [alertView dismissWithClickedButtonIndex: 0 animated: NO];
    }

    if (buttonIndex == 1)
    {
        [alertView dismissWithClickedButtonIndex: 1 animated: NO];

        self.doneButtonPressed = YES;
        [self.masterSceneNameTextField resignFirstResponder];

        dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
            LSFSDKMasterScene *masterScene = [[LSFSDKLightingDirector getLightingDirector] getMasterSceneWithID: self.masterSceneID];
            [masterScene rename: self.masterSceneNameTextField.text];
        });
    }
}

@end
