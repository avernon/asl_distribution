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

#import "LSFGroupsAddNameViewController.h"
#import "LSFGroupsAddLampsTableViewController.h"
#import "LSFUtilityFunctions.h"
#import <LSFSDKLightingDirector.h>

@interface LSFGroupsAddNameViewController ()

@property (nonatomic) BOOL doneButtonPressed;

-(void)leaderModelChangedNotificationReceived: (NSNotification *)notification;

@end

@implementation LSFGroupsAddNameViewController

@synthesize groupNameTextField = _groupNameTextField;
@synthesize doneButtonPressed = _doneButtonPressed;

-(void)viewDidLoad
{
    [super viewDidLoad];

    [self.groupNameTextField becomeFirstResponder];
    self.doneButtonPressed = NO;
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    //Set notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];

    //Hide toolbar because it is not needed
    [self.navigationController.toolbar setHidden: YES];
}

-(void)viewWillDisappear: (BOOL)animated
{
    [super viewWillDisappear: animated];

    //Clear notification handler
    [[NSNotificationCenter defaultCenter] removeObserver: self];

    //Unhide toolbar because it is not needed
    [self.navigationController.toolbar setHidden: NO];
}

-(void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

/*
 * Notification handlers
 */
-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification
{
    LSFSDKController *leaderModel = [notification.userInfo valueForKey: @"leader"];
    if (![leaderModel connected])
    {
        [self dismissViewControllerAnimated: YES completion: nil];
    }
}

/*
 * UITextFieldDelegate implementation
 */
-(BOOL)textFieldShouldReturn: (UITextField *)textField
{
    if ([self.groupNameTextField.text isEqualToString: @""])
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"No Group Name"
                                                        message: @"You need to provide a group name in order to proceed."
                                                       delegate: self
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];

        return NO;
    }

    if (![LSFUtilityFunctions checkNameLength: self.groupNameTextField.text entity: @"Group Name"])
    {
        return NO;
    }

    if (![LSFUtilityFunctions checkWhiteSpaces:self.groupNameTextField.text entity: @"Group Name"])
    {
        return NO;
    }

    BOOL nameMatchFound = [[[[LSFSDKLightingDirector getLightingDirector] groups] valueForKey: @"name"] containsObject: self.groupNameTextField.text];

    if (!nameMatchFound)
    {
        self.doneButtonPressed = YES;
        [textField resignFirstResponder];

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
        [alertView dismissWithClickedButtonIndex: 1 animated: NO];

        self.doneButtonPressed = YES;
        [self.groupNameTextField resignFirstResponder];

        [self performSegueWithIdentifier: @"ChooseGroupLamps" sender: nil];
    }
}

/*
 * Cancel Button Handler
 */
-(IBAction)cancelGroupCreate: (id)sender
{
    [self dismissViewControllerAnimated: YES completion: nil];
}

/*
 * Next Button Handler
 */
-(IBAction)nextButtonPressed: (id)sender
{
    if ([self.groupNameTextField.text isEqualToString: @""])
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"No Group Name"
                                                        message: @"You need to provide a group name in order to proceed."
                                                       delegate: self
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];

        return;
    }

    if (![LSFUtilityFunctions checkNameLength: self.groupNameTextField.text entity: @"Group Name"])
    {
        return;
    }

    if (![LSFUtilityFunctions checkWhiteSpaces:self.groupNameTextField.text entity: @"Group Name"])
    {
        return;
    }

    BOOL nameMatchFound = [[[[LSFSDKLightingDirector getLightingDirector] groups] valueForKey: @"name"] containsObject: self.groupNameTextField.text];

    if (!nameMatchFound)
    {
        self.doneButtonPressed = YES;
        [self.groupNameTextField resignFirstResponder];

        [self performSegueWithIdentifier: @"ChooseGroupLamps" sender: nil];

        return;
    }

    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Duplicate Name"
                                                    message: [NSString stringWithFormat: @"Warning: there is already a group named \"%@.\" Although it's possible to use the same name for more than one group, it's better to give each group a unique name.\n\nKeep duplicate group name \"%@\"?", self.groupNameTextField.text, self.groupNameTextField.text]
                                                   delegate: self
                                          cancelButtonTitle: @"NO"
                                          otherButtonTitles: @"YES", nil];
    [alert show];
}

/*
 * Segue Methods
 */
-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier isEqualToString: @"ChooseGroupLamps"])
    {
        LSFGroupsAddLampsTableViewController *galtvc = [segue destinationViewController];
        galtvc.groupName = [NSString stringWithFormat: @"%@", self.groupNameTextField.text];
    }
}

@end
