/******************************************************************************
 * Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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

#import "PGMJoinOrCreateViewController.h"

@interface PGMJoinOrCreateViewController ()

@end

@implementation PGMJoinOrCreateViewController

@synthesize peerGroupManager = _peerGroupManager;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	   
    [self.groupName setDelegate:self];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)joinOrCreateButtonPressed:(UIButton *)sender
{
    NSString * groupName = self.groupName.text;
    PGMJoinOrCreateReturn *jocReturn = [self.peerGroupManager joinOrCreateGroupWithName:groupName];
    
    NSString *alertTitle = jocReturn.isJoiner ? @"Joined Group" : @"Created Group";
    
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:alertTitle message:[NSString stringWithFormat:@"%@ - %s", groupName, QCC_StatusText(jocReturn.status)] delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
    [alert show];
}

- (IBAction)hideKeyboard:(id)sender
{
    [self.groupName resignFirstResponder];
}

- (BOOL) textFieldShouldReturn:(UITextField *)textField
{
    [self.groupName resignFirstResponder];
    return YES;
}

@end
