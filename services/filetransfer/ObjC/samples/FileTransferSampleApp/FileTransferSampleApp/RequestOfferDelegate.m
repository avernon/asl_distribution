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

#import "RequestOfferDelegate.h"

@interface RequestOfferDelegate()

@property (nonatomic, strong) NSString *peer;

-(void)showRequestOfferAlertView;

@end

@implementation RequestOfferDelegate

@synthesize operationsDelegate = _operationsDelegate;

/*
 * Called when the user selects the peer name from the TableViewController. The selected peer
 * name is saved in a property and a private function is called to show the alert view.
 */
-(void)selectionMade: (NSString*)selectedString on: (TableViewController *)tableViewController
{
    self.peer = selectedString;
    [self showRequestOfferAlertView];
}

/*
 * Shows an alert view to the user and allows them to enter the relative path to the file they
 * are requesting.
 */
-(void)showRequestOfferAlertView
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Request Offer" message: @"Please enter a relative path for the file:" delegate: self cancelButtonTitle: @"Continue" otherButtonTitles: nil];
    alert.alertViewStyle = UIAlertViewStylePlainTextInput;
    UITextField *alertTextField = [alert textFieldAtIndex: 0];
    alertTextField.keyboardType = UIKeyboardTypeDefault;
    alertTextField.placeholder = @"Enter a realtive path";
    
    [alert show];
}

/*
 * Callback method from the UIAlertView that extracts the file path entered and delegates back to the
 * ViewController class so the offer request can be sent.
 */
#pragma mark UIAlertView delegate methods
-(void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    NSString *filePath = [[NSString alloc] initWithString: [alertView textFieldAtIndex: 0].text];
    
    if (self.operationsDelegate != nil)
    {
        [self.operationsDelegate sendOfferRequestForFileWithPath: filePath toPeer: self.peer];
    }
}

@end
