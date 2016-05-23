/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

@interface LSFGroupsInfoTableViewController : UITableViewController

@property (nonatomic, strong) NSString *groupID;
@property (nonatomic, weak) IBOutlet UILabel *nameLabel;
@property (nonatomic, weak) IBOutlet UISwitch *powerSwitch;
@property (nonatomic, weak) IBOutlet UIButton *presetButton;
@property (nonatomic, weak) IBOutlet UISlider *brightnessSlider;
@property (nonatomic, weak) IBOutlet UIButton *brightnessSliderButton;
@property (nonatomic, weak) IBOutlet UILabel *brightnessAsterisk;
@property (nonatomic, weak) IBOutlet UILabel *brightnessLabel;
@property (nonatomic, weak) IBOutlet UISlider *hueSlider;
@property (nonatomic, weak) IBOutlet UIButton *hueSliderButton;
@property (nonatomic, weak) IBOutlet UILabel *hueAsterisk;
@property (nonatomic, weak) IBOutlet UILabel *hueLabel;
@property (nonatomic, weak) IBOutlet UISlider *saturationSlider;
@property (nonatomic, weak) IBOutlet UIButton *saturationSliderButton;
@property (nonatomic, weak) IBOutlet UILabel *saturationAsterisk;
@property (nonatomic, weak) IBOutlet UILabel *saturationLabel;
@property (nonatomic, weak) IBOutlet UISlider *colorTempSlider;
@property (nonatomic, weak) IBOutlet UIButton *colorTempSliderButton;
@property (nonatomic, weak) IBOutlet UILabel *colorTempAsterisk;
@property (nonatomic, weak) IBOutlet UILabel *colorTempLabel;
@property (weak, nonatomic) IBOutlet UIImageView *colorIndicatorImage;

-(IBAction)powerSwitchPressed: (UISwitch *)sender;
-(IBAction)brightnessSliderValueChanged: (UISlider *)sender;
-(IBAction)brightnessSliderTouchedWhileDisabled: (UIButton *)sender;
-(IBAction)brightnessSliderTouchUpInside:(id)sender;
-(IBAction)brightnessSliderTouchUpOutside:(id)sender;
-(IBAction)hueSliderValueChanged: (UISlider *)sender;
-(IBAction)hueSliderTouchedWhileDisabled: (UIButton *)sender;
-(IBAction)hueSliderTouchUpInside:(id)sender;
-(IBAction)hueSliderTouchUpOutside:(id)sender;
-(IBAction)saturationSliderValueChanged: (UISlider *)sender;
-(IBAction)saturationSliderTouchedWhileDisabled: (UIButton *)sender;
-(IBAction)saturationSliderTouchUpInside:(id)sender;
-(IBAction)saturationSliderTouchUpOutside:(id)sender;
-(IBAction)colorTempSliderValueChanged: (UISlider *)sender;
-(IBAction)colorTempSliderTouchedWhileDisabled: (UIButton *)sender;
-(IBAction)colorSliderTouchUpInside:(id)sender;
-(IBAction)colorSliderTouchUpOutside:(id)sender;

@end
