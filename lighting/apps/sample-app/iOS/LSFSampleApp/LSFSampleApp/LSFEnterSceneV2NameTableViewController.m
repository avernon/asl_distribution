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

#import "LSFEnterSceneV2NameTableViewController.h"
#import "LSFSceneElementV2TableViewController.h"
#import "LSFPendingSceneV2.h"
#import <LSFSDKLightingDirector.h>

@interface LSFEnterSceneV2NameTableViewController ()

@property (nonatomic) BOOL keyDonePressed;

@end

@implementation LSFEnterSceneV2NameTableViewController

@synthesize pendingScene = _pendingScene;
@synthesize keyDonePressed = _keyDonePressed;

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear: animated];
    self.keyDonePressed = NO;
    self.entity = @"Scene";

    if (self.pendingScene != nil)
    {
        self.nameTextField.text = self.pendingScene.name;
    }
    else
    {
        self.pendingScene = [[LSFPendingSceneV2 alloc] init];
    }
}

-(IBAction)nextButtonPressed:(id)sender
{
    [super nextButtonPressed: sender];

    self.pendingScene.name = self.nameTextField.text;

    if ([self validateNameAgainst: [[[LSFSDKLightingDirector getLightingDirector] scenes] valueForKeyPath: @"name"]])
    {
        [self doSegue];
    }
}

-(void)doSegue
{
    if (self.pendingScene.theID == nil)
    {
        [self performSegueWithIdentifier: @"SceneV2Members" sender: self];
    }
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier isEqualToString: @"SceneV2Members"])
    {
        LSFSceneElementV2TableViewController *semtvc = [segue destinationViewController];
        semtvc.pendingScene = self.pendingScene;
    }
}

-(BOOL)textFieldShouldReturn:(UITextField *)textField
{
    if (self.pendingScene.theID != nil)
    {
        if ([self validateNameAgainst: [[[LSFSDKLightingDirector getLightingDirector] scenes] valueForKeyPath: @"name"]])
        {
            self.pendingScene.name = self.nameTextField.text;
            LSFSDKScene *scene = [[LSFSDKLightingDirector getLightingDirector] getSceneWithID: self.pendingScene.theID];
            [scene rename: self.pendingScene.name];

            self.keyDonePressed = YES;
            [textField resignFirstResponder];
            return YES;
        }

        return NO;
    }
    else
    {
        return YES;
    }
}

- (IBAction)nameDidEndEditing:(id)sender
{
    // Only used when editing the name of an existing scene
    if (self.keyDonePressed)
    {
        [self.navigationController popViewControllerAnimated: YES];
    }
}

@end
