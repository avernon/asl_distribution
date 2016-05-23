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

#import "LSFGroupsCreatePresetViewController.h"
#import "LSFGroupsInfoTableViewController.h"
#import "LSFUtilityFunctions.h"
#import <LSFSDKLightingDirector.h>

@interface LSFGroupsCreatePresetViewController ()

@property (nonatomic) BOOL doneButtonPressed;

-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification;
-(void)groupRemovedNotificationReceived: (NSNotification *)notification;

@end

@implementation LSFGroupsCreatePresetViewController

@synthesize lampState = _lampState;
@synthesize presetNameTextField = _presetNameTextField;
@synthesize doneButtonPressed = _doneButtonPressed;

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    int numPresets = (int) [[[LSFSDKLightingDirector getLightingDirector] presets] count];

    [self.presetNameTextField becomeFirstResponder];
    self.presetNameTextField.text = [NSString stringWithFormat: @"Preset %i", ++numPresets];
    self.doneButtonPressed = NO;

    //Set notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(groupRemovedNotificationReceived:) name: @"LSFGroupRemovedNotification" object: nil];
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

-(void)groupRemovedNotificationReceived:(NSNotification *)notification
{
    LSFSDKGroup *group = [notification.userInfo valueForKey: @"group"];

    if ([self.groupID isEqualToString: [group theID]])
    {
        [self alertGroupDeleted: group];
    }
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
    if (![LSFUtilityFunctions checkNameLength: self.presetNameTextField.text entity: @"Preset Name"])
    {
        return NO;
    }

    if (![LSFUtilityFunctions checkWhiteSpaces: self.presetNameTextField.text entity: @"Preset Name"])
    {
        return NO;
    }

    BOOL nameMatchFound = [[[[LSFSDKLightingDirector getLightingDirector] presets] valueForKeyPath: @"name"] containsObject: self.presetNameTextField.text];
    if (!nameMatchFound)
    {
        self.doneButtonPressed = YES;
        [textField resignFirstResponder];

        dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
            NSString *presetName = self.presetNameTextField.text;

            [[LSFSDKLightingDirector getLightingDirector] createPresetWithPower: [self.lampState power] color: [self.lampState color] presetName:presetName];
        });
        
        return YES;
    }

    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Duplicate Name"
                                                    message: [NSString stringWithFormat: @"Warning: there is already a preset named \"%@.\" Although it's possible to use the same name for more than one preset, it's better to give each preset a unique name.\n\nKeep duplicate preset name \"%@\"?", self.presetNameTextField.text, self.presetNameTextField.text]
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
        for (UIViewController *vc in self.navigationController.viewControllers)
        {
            if ([vc isKindOfClass: [LSFGroupsInfoTableViewController class]])
            {
                [self.navigationController popToViewController: (LSFGroupsInfoTableViewController *)vc animated: YES];
            }
        }
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
        [self.presetNameTextField resignFirstResponder];

        dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
            NSString *presetName = self.presetNameTextField.text;

            [[LSFSDKLightingDirector getLightingDirector] createPresetWithPower: [self.lampState power] color: [self.lampState color] presetName:presetName];

        });
    }
}

@end
