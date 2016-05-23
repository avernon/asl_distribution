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

#import "LSFEffectV2PropertiesTableViewController.h"

@interface LSFPulseEffectV2TableViewController : LSFEffectV2PropertiesTableViewController

@property (weak, nonatomic) IBOutlet UIButton *presetButton;
@property (weak, nonatomic) IBOutlet UISwitch *startPropertiesSwitch;

@property (weak, nonatomic) IBOutlet UIButton *endPresetButton;
@property (weak, nonatomic) IBOutlet UIImageView *endColorIndicatorImage;

@property (weak, nonatomic) IBOutlet UISlider *endBrightnessSlider;
@property (weak, nonatomic) IBOutlet UISlider *endHueSlider;
@property (weak, nonatomic) IBOutlet UISlider *endSaturationSlider;
@property (weak, nonatomic) IBOutlet UISlider *endColorTempSlider;

@property (weak, nonatomic) IBOutlet UIButton *endBrightnessSliderButton;
@property (weak, nonatomic) IBOutlet UIButton *endHueSliderButton;
@property (weak, nonatomic) IBOutlet UIButton *endSaturationSliderButton;
@property (weak, nonatomic) IBOutlet UIButton *endColorTempSliderButton;

@property (weak, nonatomic) IBOutlet UILabel *endBrightnessLabel;
@property (weak, nonatomic) IBOutlet UILabel *endHueLabel;
@property (weak, nonatomic) IBOutlet UILabel *endSaturationLabel;
@property (weak, nonatomic) IBOutlet UILabel *endColorTempLabel;

@property (weak, nonatomic) IBOutlet UILabel *durationLabel;
@property (weak, nonatomic) IBOutlet UILabel *periodLabel;
@property (weak, nonatomic) IBOutlet UILabel *numPulsesLabel;


-(IBAction)startPropertiesSwitchValueChanged: (id)sender;

-(IBAction)endBrightnessSliderValueChanged: (UISlider *)sender;
-(IBAction)endHueSliderValueChanged: (UISlider *)sender;
-(IBAction)endSaturationSliderValueChanged: (UISlider *)sender;
-(IBAction)endColorTempSliderValueChanged: (UISlider *)sender;

@end
