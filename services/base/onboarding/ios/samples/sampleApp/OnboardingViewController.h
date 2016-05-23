/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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
#import "ClientInformation.h"

static NSString * const AJ_AP_PREFIX = @"AJ_";
static NSString * const AJ_AP_SUFFIX = @"_AJ";

@interface OnboardingViewController : UIViewController
@property (strong, nonatomic) AJNBusAttachment *clientBusName;
@property (weak, nonatomic) ClientInformation *clientInformation;

@property (weak, nonatomic) IBOutlet UITextField *ssidTextField;
@property (weak, nonatomic) IBOutlet UITextField *ssidPassTextField;
@property (weak, nonatomic) IBOutlet UIButton *configureBtn;
@property (weak, nonatomic) IBOutlet UIButton *connectBtn;
@property (weak, nonatomic) IBOutlet UIButton *offBoardingBtn;
@property (weak, nonatomic) IBOutlet UILabel *onboardTitleLbl;
@property (weak, nonatomic) IBOutlet UILabel *ssidLbl;
@property (weak, nonatomic) IBOutlet UILabel *ssidPassLbl;
@property (weak, nonatomic) IBOutlet UILabel *statusLbl;
@property (weak, nonatomic) IBOutlet UILabel *instructLbl;

- (IBAction)configureBtnDidTouchUpInside:(id)sender;

- (IBAction)connectBtnDidTouchUpInside:(id)sender;

- (IBAction)offBoardingBtnDidTouchUpInside:(id)sender;

@end
