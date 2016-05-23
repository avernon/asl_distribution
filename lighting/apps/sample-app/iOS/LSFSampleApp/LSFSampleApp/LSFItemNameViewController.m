/******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

#import "LSFItemNameViewController.h"
#import "LSFUtilityFunctions.h"
#import <LSFSDKLightingDirector.h>

@interface LSFItemNameViewController ()

@end

@implementation LSFItemNameViewController

@synthesize entity = _entity;

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear: animated];
    [self.nameTextField becomeFirstResponder];
    [self.navigationController.toolbar setHidden: YES];

    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];

    self.entity = @"";
}

-(void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear: animated];
    [[NSNotificationCenter defaultCenter] removeObserver: self];
}


-(IBAction)cancelButtonPressed:(id)sender
{
    [self dismissViewControllerAnimated: YES completion: nil];
}

-(IBAction)nextButtonPressed:(id)sender
{
    // Override in subclass if necessary
    NSLog(@"Next button pressed");
}

-(BOOL)validateNameAgainst: (NSArray *)names
{
    NSString *name = self.nameTextField.text;

    return  [LSFUtilityFunctions checkNameEmpty: name entity: self.entity]      &&
            [LSFUtilityFunctions checkNameLength: name entity: self.entity]     &&
            [LSFUtilityFunctions checkWhiteSpaces: name entity: self.entity]    &&
            ![self checkForDuplicateNameAgainst: names];
}

-(void)alertView: (UIAlertView *)alertView clickedButtonAtIndex: (NSInteger)buttonIndex
{
    if (buttonIndex == 0)
    {
        [alertView dismissWithClickedButtonIndex: 0 animated: YES];
    }

    if (buttonIndex == 1)
    {
        [alertView dismissWithClickedButtonIndex: 1 animated: NO];
        [self.nameTextField resignFirstResponder];
        [self doSegue];
    }
}

-(void)doSegue
{
    // meant to be overriden
}


-(BOOL)checkForDuplicateNameAgainst: (NSArray *)names
{
    NSString *name = self.nameTextField.text;

    BOOL duplicate = [names containsObject: name];

    if (duplicate)
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Duplicate Name"
                                                  message: [NSString stringWithFormat: @"Warning: there is already a %1$@ named \"%2$@.\" Although it's possible to use the same name for more than one %1$@, it's better to give each %1$@ a unique name.\n\nKeep duplicate %1$@ name \"%2$@\"?", self.entity, name]
                                                 delegate: self
                                        cancelButtonTitle: @"NO"
                                        otherButtonTitles: @"YES", nil];
        [alert show];
    }

    return duplicate;
}

-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification
{
    LSFSDKController *leaderModel = [notification.userInfo valueForKey: @"leader"];
    if (![leaderModel connected])
    {
        [self dismissViewControllerAnimated: YES completion: nil];
        [self.navigationController popToRootViewControllerAnimated: YES];
    }
}

@end
