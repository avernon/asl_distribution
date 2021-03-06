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

#import <Foundation/Foundation.h>
#import <MobileCoreServices/UTCoreTypes.h>
#import <UIKit/UIKit.h>
#import "AllJoynManager.h"
#import "TableViewController.h"
#import "ConnectionSateChangedDelegate.h"
#import "SelectionMadeDelegate.h"
#import "FileTransferModule/FTMFileTransferModule.h"
#import "FTMFileAnnouncementReceivedDelegate.h"
#import "FTMFileDescriptor.h"
#import "FileTransferOperationsDelegate.h"
#import "AnnouncementDelegate.h"
#import "UnannounceFileDelegate.h"
#import "RequestFileDelegate.h"
#import "OfferFileDelegate.h"
#import "RequestOfferDelegate.h"
#import "AnnounceViewController.h"

/*
 * This class specifies the public properties and functions that are associated with the sample applications 
 * main view. 
 */
@interface ViewController : UIViewController <ConnectionSateChangedDelegate, FTMFileAnnouncementReceivedDelegate, FTMFileCompletedDelegate, FTMRequestDataReceivedDelegate, FTMOfferReceivedDelegate, FTMUnannouncedFileRequestDelegate, FileTransferOperationsDelegate>

@property (weak, nonatomic) IBOutlet UIButton *hostButton;
@property (weak, nonatomic) IBOutlet UIButton *joinButton;
@property (weak, nonatomic) IBOutlet UIButton *announceButton;
@property (weak, nonatomic) IBOutlet UIButton *unannounceButton;
@property (weak, nonatomic) IBOutlet UIButton *requestButton;
@property (weak, nonatomic) IBOutlet UIButton *offerButton;
@property (weak, nonatomic) IBOutlet UIButton *requestOfferButton;
@property (weak, nonatomic) IBOutlet UITextView *textView;
@property (weak, nonatomic) IBOutlet UIProgressView *receiveProgressBar;
@property (weak, nonatomic) IBOutlet UIProgressView *sendProgressBar;
@property (weak, nonatomic) IBOutlet UIButton *pauseReceiveButton;
@property (weak, nonatomic) IBOutlet UIButton *cancelReceiveButton;
@property (weak, nonatomic) IBOutlet UIButton *cancelSendButton;

-(IBAction)hostSessionClicked: (id)sender;
-(IBAction)joinSessionClicked: (id)sender;
-(IBAction)pauseReceiveButtonClicked:(id)sender;
-(IBAction)cancelReceiveButtonClicked:(id)sender;
-(IBAction)cancelSendButtonClicked:(id)sender;

@end
