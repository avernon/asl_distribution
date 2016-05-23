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

#import "AnnouncementDelegate.h"

@interface AnnouncementDelegate()

@property (nonatomic, strong) UIImage *chosenImage;

-(void)showAlertView;

@end

@implementation AnnouncementDelegate

@synthesize chosenImage = _chosenImage;
@synthesize operationsDelegate = _operationsDelegate;

- (void)announceDirectoryWithPath: (NSString*)path
{
    if (self.operationsDelegate != nil)
    {
        [self.operationsDelegate announceFileWithPath: path];
    }
}

/*
 * Callback method for the UIImagePickerController thats extracts the image the user selected from
 * the image picker. This function stores the selected image in a property and then calls a private
 * method to allow the user to enter the file name.
 */
#pragma mark UIImagePickerController delegate methods
-(void)imagePickerController: (UIImagePickerController *)picker didFinishPickingMediaWithInfo: (NSDictionary *)info
{
    NSString *lastChosenMediaType = [[NSString alloc] initWithString: [info objectForKey: UIImagePickerControllerMediaType]];
    
    if ([lastChosenMediaType isEqual: (NSString *)kUTTypeImage])
    {
        self.chosenImage = [info objectForKey: UIImagePickerControllerOriginalImage];
        [self showAlertView];
    }
    else
    {
        NSLog(@"Unsupported type selected");
    }
    
    [picker dismissViewControllerAnimated: YES completion: nil];
}

/*
 * Callback method for the UIImagePickerController that dismisses the picker when the cancel button
 * is pressed and does not take any further action.
 */
-(void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
    [picker dismissViewControllerAnimated: YES completion: nil];
}

/*
 * Shows an alert view to the user and allows them to enter the name of the file they are announcing.
 */
-(void)showAlertView
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Stop" message: @"Please enter a name for the file:" delegate: self cancelButtonTitle: @"Continue" otherButtonTitles:
                          nil];
    alert.alertViewStyle = UIAlertViewStylePlainTextInput;
    UITextField *alertTextField = [alert textFieldAtIndex: 0];
    alertTextField.keyboardType = UIKeyboardTypeDefault;
    alertTextField.placeholder = @"Enter a file name";
    
    [alert show];
}

/*
 * Callback method from the UIAlertView that extracts the file name entered and delegates back to the
 * ViewController class so the announcement can be sent.
 */
#pragma mark UIAlertView delegate methods
-(void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    NSString *fileName = [[NSString alloc] initWithString: [alertView textFieldAtIndex: 0].text];
    fileName = ([fileName hasSuffix: @".png"]) ? fileName : [fileName stringByAppendingString: @".png"];
    
    NSString *path = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex: 0];
    path = [path stringByAppendingPathComponent: @"Sending"];
    path = [path stringByAppendingPathComponent: fileName];
    
    NSData *chosenImageData = UIImagePNGRepresentation(self.chosenImage);
    [chosenImageData writeToFile: path atomically: YES];
    
    if (self.operationsDelegate != nil)
    {
        [self.operationsDelegate announceFileWithPath: path];
    }
}

@end
