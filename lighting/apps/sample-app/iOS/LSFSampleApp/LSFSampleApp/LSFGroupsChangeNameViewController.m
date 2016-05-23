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

#import "LSFGroupsChangeNameViewController.h"
#import "LSFUtilityFunctions.h"
#import <LSFSDKLightingDirector.h>

@interface LSFGroupsChangeNameViewController ()

@property (nonatomic) BOOL doneButtonPressed;

-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification;
-(void)groupChangedNotificationReceived: (NSNotification *)notification;
-(void)groupRemovedNotificationReceived: (NSNotification *)notification;
-(void)reloadGroupName;

@end

@implementation LSFGroupsChangeNameViewController

@synthesize groupID = _groupID;
@synthesize groupNameTextField = _groupNameTextField;
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
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(groupChangedNotificationReceived:) name: @"LSFGroupChangedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(groupRemovedNotificationReceived:) name: @"LSFGroupRemovedNotification" object: nil];

    [self.groupNameTextField becomeFirstResponder];
    self.groupNameTextField.text = [[[LSFSDKLightingDirector getLightingDirector] getGroupWithID: self.groupID] name];
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

-(void)groupChangedNotificationReceived:(NSNotification *)notification
{
    LSFSDKGroup *group = [notification.userInfo valueForKey: @"group"];

    if ([self.groupID isEqualToString: [group theID]])
    {
        [self reloadGroupName];
    }
}

-(void)groupRemovedNotificationReceived:(NSNotification *)notification
{
    LSFSDKGroup *group = [notification.userInfo valueForKey: @"group"];

    if ([self.groupID isEqualToString: [group theID]])
    {
        [self alertGroupDeleted: group];
    }
}

/*
 * Private methods
 */
-(void)reloadGroupName
{
    self.groupNameTextField.text = [[[LSFSDKLightingDirector getLightingDirector] getGroupWithID: self.groupID] name];
}

-(void)alertGroupDeleted: (LSFSDKGroup *) group
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Group Not Found"
                                                    message: [NSString stringWithFormat: @"The group \"%@\" no longer exists.", [group name]]
                                                   delegate: nil
                                          cancelButtonTitle: @"OK"
                                          otherButtonTitles: nil];
    [alert show];

    [self.navigationController popToRootViewControllerAnimated: YES];
}

/*
 * UITextFieldDelegate Implementation
 */
-(BOOL)textFieldShouldReturn: (UITextField *)textField
{
    if (![LSFUtilityFunctions checkNameLength: self.groupNameTextField.text entity: @"Group Name"])
    {
        return NO;
    }

    if (![LSFUtilityFunctions checkWhiteSpaces:self.groupNameTextField.text entity: @"Group Name"])
    {
        return NO;
    }

    BOOL nameMatchFound = [[[[LSFSDKLightingDirector getLightingDirector] groups] valueForKeyPath: @"name"] containsObject: self.groupNameTextField.text];
    
    if (!nameMatchFound)
    {
        self.doneButtonPressed = YES;
        [textField resignFirstResponder];

        dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
            LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: self.groupID];
            [group rename: self.groupNameTextField.text];
        });
        
        return YES;
    }

    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Duplicate Name"
                                                    message: [NSString stringWithFormat: @"Warning: there is already a group named \"%@.\" Although it's possible to use the same name for more than one group, it's better to give each group a unique name.\n\nKeep duplicate group name \"%@\"?", self.groupNameTextField.text, self.groupNameTextField.text]
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
        [self.groupNameTextField resignFirstResponder];
        
        dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
            LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: self.groupID];
            [group rename: self.groupNameTextField.text];
        });
    }
}

@end
