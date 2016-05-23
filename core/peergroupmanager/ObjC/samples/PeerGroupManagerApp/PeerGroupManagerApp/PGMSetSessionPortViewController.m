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

#import "PGMSetSessionPortViewController.h"

@interface PGMSetSessionPortViewController ()

@end

@implementation PGMSetSessionPortViewController

@synthesize peerGroupManager = _peerGroupManager;
@synthesize sessionPort = _sessionPort;
@synthesize setSessionPortButton = _setSessionPortButton;


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
	
    self.sessionPort.delegate = self;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)setSessionPortButtonPressed:(UIButton *)sender
{
    AJNSessionPort sessionPort = (uint16_t)[self.sessionPort.text integerValue];
    [self.peerGroupManager setSessionPort:sessionPort];
    
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Set Session Port" message:[NSString stringWithFormat:@"Setting Session Port to %@", self.sessionPort.text] delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
    [alert show];
    
    self.sessionPort.text = @"";
    [self.sessionPort resignFirstResponder];
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    // Support the backspace key
    if([string isEqualToString:@""]) {
        return YES;
    }
    
    // Ensure that all the characters are numeric
    NSCharacterSet *numericCharacters = [NSCharacterSet decimalDigitCharacterSet];
    int i;
    for(i=0; i < [string length]; i++)
    {
        unichar character = [string characterAtIndex:i];
        if([numericCharacters characterIsMember:character])
        {
            return YES;
        }
    }
    return NO;
}

- (BOOL) textFieldShouldReturn:(UITextField *)textField
{
    [self.sessionPort resignFirstResponder];
    return YES;
}

- (IBAction)hideKeyboard:(id)sender
{
    [self.sessionPort resignFirstResponder];
}

@end
