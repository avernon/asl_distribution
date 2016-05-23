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
#ifdef LSF_SCENES_V1_MODULE

#import "LSFEffectTableViewController.h"
#import <model/LSFSceneDataModel.h>
#import <model/LSFPulseEffectDataModel.h>

@interface LSFPulseEffectTableViewController : LSFEffectTableViewController

@property (nonatomic, weak) IBOutlet UISwitch *startPropertiesSwitch;
@property (nonatomic, weak) IBOutlet UIButton *endPresetButton;
@property (nonatomic, weak) IBOutlet UISlider *endBrightnessSlider;
@property (nonatomic, weak) IBOutlet UIButton *endBrightnessButton;
@property (nonatomic, weak) IBOutlet UILabel *endBrightnessLabel;
@property (nonatomic, weak) IBOutlet UISlider *endHueSlider;
@property (nonatomic, weak) IBOutlet UIButton *endHueButton;
@property (nonatomic, weak) IBOutlet UILabel *endHueLabel;
@property (nonatomic, weak) IBOutlet UISlider *endSaturationSlider;
@property (nonatomic, weak) IBOutlet UIButton *endSaturationButton;
@property (nonatomic, weak) IBOutlet UILabel *endSaturationLabel;
@property (nonatomic, weak) IBOutlet UISlider *endColorTempSlider;
@property (nonatomic, weak) IBOutlet UIButton *endColorTempButton;
@property (nonatomic, weak) IBOutlet UILabel *endColorTempLabel;
@property (nonatomic, weak) IBOutlet UILabel *durationLabel;
@property (nonatomic, weak) IBOutlet UILabel *periodLabel;
@property (nonatomic, weak) IBOutlet UILabel *numPulsesLabel;
@property (weak, nonatomic) IBOutlet UIImageView *endColorIndicatorImage;
@property (nonatomic, strong) LSFSceneDataModel *sceneModel;
@property (nonatomic, strong) LSFPulseEffectDataModel *pedm;
@property (nonatomic) BOOL shouldUpdateSceneAndDismiss;

-(IBAction)endBrightnessSliderValueChanged: (UISlider *)sender;
-(IBAction)endBrightnessSliderTouchUpInside: (UISlider *)sender;
-(IBAction)endBrightnessSliderTouchUpOutside: (UISlider *)sender;
-(IBAction)endHueSliderValueChanged: (UISlider *)sender;
-(IBAction)endHueSliderTouchUpInside: (UISlider *)sender;
-(IBAction)endHueSliderTouchUpOutside: (UISlider *)sender;
-(IBAction)endSaturationSliderValueChanged: (UISlider *)sender;
-(IBAction)endSaturationSliderTouchUpInside: (UISlider *)sender;
-(IBAction)endSaturationSliderTouchUpOutside: (UISlider *)sender;
-(IBAction)endColorTempSliderValueChanged: (UISlider *)sender;
-(IBAction)endColorTempSliderTouchUpInside: (UISlider *)sender;
-(IBAction)endColorTempSliderTouchUpOutside: (UISlider *)sender;
-(IBAction)doneButtonPressed: (id)sender;
-(IBAction)startPropertiesSwitchValueChanged: (UISwitch *)sender;
-(IBAction)startBrightnessSliderTouchedWhileDisabled: (UIButton *)sender;
-(IBAction)startHueSliderTouchedWhileDisabled: (UIButton *)sender;
-(IBAction)startSaturationSliderTouchedWhileDisabled: (UIButton *)sender;
-(IBAction)startColorTempSliderTouchedWhileDisabled: (UIButton *)sender;
-(IBAction)endBrightnessSliderTouchedWhileDisabled: (UIButton *)sender;
-(IBAction)endHueSliderTouchedWhileDisabled: (UIButton *)sender;
-(IBAction)endSaturationSliderTouchedWhileDisabled: (UIButton *)sender;
-(IBAction)endColorTempSliderTouchedWhileDisabled: (UIButton *)sender;


@end

#endif
