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

#import "AnnounceViewController.h"

@interface AnnounceViewController()

@end

@implementation AnnounceViewController

- (id)initWithNibName: (NSString *)nibNameOrNil bundle: (NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName: nibNameOrNil bundle: nibBundleOrNil];
    return self;
}

- (void)viewWillAppear: (BOOL)animated
{
    [self.navigationController setNavigationBarHidden: NO animated: animated];
    [super viewWillAppear: animated];
}

- (void)viewWillDisappear: (BOOL)animated
{
    [self.navigationController setNavigationBarHidden: YES animated: animated];
    [super viewWillDisappear: animated];
}

- (IBAction)announceFileClicked: (id)sender
{
    [self showPicturePicker: self.announcementController];
}

- (IBAction)announceDocsClicked: (id)sender
{
    NSString *path = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents"];
    [self.announcementController announceDirectoryWithPath: path];
}

/*
 * Private helper function that displays an image picker for the user. This function is called when the user wishes
 * to announce or offer a file and the image picker allows them to select the file they want to announce or offer.
 */
-(void)showPicturePicker: (id<UINavigationControllerDelegate, UIImagePickerControllerDelegate>)delegate
{
    UIImagePickerControllerSourceType sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    NSArray *mediaTypes = [UIImagePickerController availableMediaTypesForSourceType: sourceType];
    
    if ([UIImagePickerController isSourceTypeAvailable: sourceType] && [mediaTypes count] > 0)
    {
        UIImagePickerController *picker = [[UIImagePickerController alloc] init];
        picker.mediaTypes = mediaTypes;
        picker.delegate = delegate;
        picker.sourceType = sourceType;
        
        [self presentViewController: picker animated: YES completion: nil];
    }
    else
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error accessing media" message: @"Device doesn't support that media source" delegate: nil cancelButtonTitle: @"Cancel" otherButtonTitles: nil];
        [alert show];
    }
}
@end
