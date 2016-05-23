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

#import <UIKit/UIKit.h>
#import "LSFPendingSceneV2.h"
#import "LSFPendingSceneElement.h"
#import "LSFPendingEffect.h"

@interface LSFEffectV2PropertiesTableViewController : UITableViewController

@property (nonatomic, strong) LSFPendingSceneV2 *pendingScene;
@property (nonatomic, strong) LSFPendingSceneElement *pendingSceneElement;
@property (nonatomic, strong) LSFPendingEffect *pendingEffect;

@property (weak, nonatomic) IBOutlet UIImageView *colorIndicatorImage;

@property (weak, nonatomic) IBOutlet UISlider *brightnessSlider;
@property (weak, nonatomic) IBOutlet UISlider *hueSlider;
@property (weak, nonatomic) IBOutlet UISlider *saturationSlider;
@property (weak, nonatomic) IBOutlet UISlider *colorTempSlider;

@property (weak, nonatomic) IBOutlet UIButton *brightnessSliderButton;
@property (weak, nonatomic) IBOutlet UIButton *hueSliderButton;
@property (weak, nonatomic) IBOutlet UIButton *saturationSliderButton;
@property (weak, nonatomic) IBOutlet UIButton *colorTempSliderButton;

@property (weak, nonatomic) IBOutlet UILabel *brightnessLabel;
@property (weak, nonatomic) IBOutlet UILabel *hueLabel;
@property (weak, nonatomic) IBOutlet UILabel *saturationLabel;
@property (weak, nonatomic) IBOutlet UILabel *colorTempLabel;

-(void)updateColorIndicator;
-(void)updatePresetButtonTitle: (UIButton*)presetButton;
-(void)updateSlider: (UISlider *)slider withValue: (int)value;
-(void)checkSaturationValue;
-(LSFSDKMyLampState *)getSlidersState;
-(void)handlePendingData;

-(void)onSliderTapped: (UIGestureRecognizer *)gr;
-(IBAction)onSliderTouchUpInside: (UISlider *)slider;

-(IBAction)brightnessSliderValueChanged: (UISlider *)sender;
-(IBAction)brightnessSliderTouchDisabled: (UIButton *)sender;

-(IBAction)hueSliderValueChanged: (UISlider *)sender;
-(IBAction)hueSliderTouchDisabled: (UIButton *)sender;

-(IBAction)saturationSliderValueChanged: (UISlider *)sender;
-(IBAction)saturationSliderTouchDisabled: (UIButton *)sender;

-(IBAction)colorTempSliderValueChanged: (UISlider *)sender;
-(IBAction)colorTempSliderTouchDisabled: (UIButton *)sender;

-(IBAction)doneButtonPressed:(id)sender;

@end
