/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

#import <UIKit/UIKit.h>
#import "AJNBusAttachment.h"
#import "alljoyn/services_common/AJSVCGenericLoggerDefaultImpl.h"

@interface ProducerViewController : UIViewController <UITextFieldDelegate>

@property (weak, nonatomic) UIViewController *mainVC;

@property (weak, nonatomic) IBOutlet UITextField *notificationEnTextField;
@property (weak, nonatomic) IBOutlet UITextField *notificationLangTextField;
@property (weak, nonatomic) IBOutlet UITextField *ttlTextField;
@property (weak, nonatomic) IBOutlet UITextField *audioTextField;
@property (weak, nonatomic) IBOutlet UITextField *iconTextField;

@property (weak, nonatomic) IBOutlet UILabel *defaultLangLabel;
@property (weak, nonatomic) IBOutlet UILabel *ttlLabel;
@property (weak, nonatomic) IBOutlet UILabel *audioLabel;
@property (weak, nonatomic) IBOutlet UILabel *iconLabel;
@property (weak, nonatomic) IBOutlet UILabel *messageTypeLabel;

@property (weak, nonatomic) IBOutlet UISwitch *audioSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *iconSwitch;

@property (weak, nonatomic) IBOutlet UIButton *messageTypeButton;
@property (weak, nonatomic) IBOutlet UIButton *sendNotificationButton;
@property (weak, nonatomic) IBOutlet UIButton *deleteButton;
@property (weak, nonatomic) IBOutlet UIButton *langButton;

// Shared properties
@property (strong, nonatomic) AJNBusAttachment *busAttachment;
@property (strong, nonatomic) AJSVCGenericLoggerDefaultImpl *logger;
@property (strong, nonatomic) NSString *appName;

- (IBAction)didTouchSendNotificationButton:(id)sender;

- (IBAction)didChangeAudioSwitchValue:(id)sender;

- (IBAction)didChangeIconSwitchValue:(id)sender;

- (IBAction)didTouchDeleteButton:(id)sender;

- (QStatus)startProducer;

- (void)stopProducer:(bool) isConsumerOn;
@end
