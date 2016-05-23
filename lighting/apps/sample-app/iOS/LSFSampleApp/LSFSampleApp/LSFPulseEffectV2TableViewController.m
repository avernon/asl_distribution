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

#import "LSFPulseEffectV2TableViewController.h"
#import "LSFUtilityFunctions.h"
#import "LSFEffectV2NumericPropertyViewController.h"
#import "LSFSelectPresetTableViewController.h"
#import <LSFSDKLightingDirector.h>

@interface LSFPulseEffectV2TableViewController ()

@end

@implementation LSFPulseEffectV2TableViewController

- (void)viewDidLoad
{
    [super viewDidLoad];

    [self.endBrightnessSlider addGestureRecognizer: [[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(onSliderTapped:)]];

    [self.endHueSlider addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(onSliderTapped:)]];

    [self.endSaturationSlider addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(onSliderTapped:)]];

    [self.endColorTempSlider addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(onSliderTapped:)]];

    [self.endBrightnessSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
    [self.endBrightnessSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];
    [self.endHueSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
    [self.endHueSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];
    [self.endSaturationSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
    [self.endSaturationSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];
    [self.endColorTempSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
    [self.endColorTempSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];

    self.endColorTempSlider.minimumValue = [LSFUtilityFunctions getBoundedMinColorTempForMembers: self.pendingSceneElement.members];
    self.endColorTempSlider.maximumValue = [LSFUtilityFunctions getBoundedMaxColorTempForMembers: self.pendingSceneElement.members];
    self.endColorTempSlider.value = self.endColorTempSlider.minimumValue;
    self.endColorTempLabel.text = [NSString stringWithFormat: @"%iK", (uint32_t)self.endColorTempSlider.value];

    self.endColorIndicatorImage.layer.rasterizationScale = [UIScreen mainScreen].scale;
    self.endColorIndicatorImage.layer.shouldRasterize = YES;
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear: animated];

    if (self.pendingEffect.endState != nil)
    {
        LSFSDKColor *color = [self.pendingEffect.endState color];
        [self updateSlider: self.endColorTempSlider withValue: color.colorTemp];
        [self updateSlider: self.endBrightnessSlider withValue: color.brightness];
        [self updateSlider: self.endHueSlider withValue: color.hue];
        [self updateSlider: self.endSaturationSlider withValue: color.saturation];
    }
    else
    {
        self.pendingEffect.endState = [[LSFSDKMyLampState alloc] init];
    }

    if (!self.pendingEffect.theID)
    {
        self.pendingEffect.name = [PULSE_NAME_PREFIX stringByAppendingString: [LSFUtilityFunctions generateRandomHexStringWithLength: 16]];
    }

    [self updatePresetButtonTitle: self.presetButton];
    [self updateEndPresetButtonTitle: self.endPresetButton];

    self.durationLabel.text = [NSString stringWithFormat:@"%@ seconds", [@(self.pendingEffect.duration / 1000.0) stringValue]];
    self.periodLabel.text = [NSString stringWithFormat:@"%@ seconds", [@(self.pendingEffect.period / 1000.0) stringValue]];
    self.numPulsesLabel.text = [NSString stringWithFormat:@"%@", [@(self.pendingEffect.pulses) stringValue]];
}

-(NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    return (section == 0) ? [NSString stringWithFormat: @"Select the start and end properties that %@ will cycle through", [LSFUtilityFunctions memberStringForPendingSceneElement: self.pendingSceneElement]] : @"";
}

-(IBAction)doneButtonPressed:(id)sender
{
    NSLog(@"Done Button Pressed for PulseEffect");

    // set the start state
    self.pendingEffect.state = self.startPropertiesSwitch.on ? [[LSFSDKMyLampState alloc] init] : [self getSlidersState];

    // set end state
    self.pendingEffect.endState = [self getEndSlidersState];

    [self handlePendingData];
    [self dismissViewControllerAnimated: YES completion: nil];
}

-(IBAction)onSliderTouchUpInside: (UISlider *)slider
{
    [super onSliderTouchUpInside: slider];
    [self updatePresetButtonTitle: self.presetButton];
    [self updateEndPresetButtonTitle: self.endPresetButton];
}

- (IBAction)startPropertiesSwitchValueChanged:(id)sender
{
    if (self.startPropertiesSwitch.on)
    {
        self.brightnessSlider.enabled = NO;
        self.hueSlider.enabled = NO;
        self.saturationSlider.enabled = NO;
        self.colorTempSlider.enabled = NO;

        self.brightnessSliderButton.enabled = YES;
        self.hueSliderButton.enabled = YES;
        self.saturationSliderButton.enabled = YES;
        self.colorTempSliderButton.enabled = YES;
    }
    else
    {
        self.brightnessSlider.enabled = YES;
        self.hueSlider.enabled = YES;
        self.saturationSlider.enabled = YES;
        self.colorTempSlider.enabled = YES;

        self.brightnessSliderButton.enabled = NO;
        self.hueSliderButton.enabled = NO;
        self.saturationSliderButton.enabled = NO;
        self.colorTempSliderButton.enabled = NO;

        [self checkSaturationValue];
    }
}

-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier isEqualToString: @"PulseDuration"])
    {
        LSFEffectV2NumericPropertyViewController *enpvc = [segue destinationViewController];
        enpvc.pendingEffect = self.pendingEffect;
        enpvc.effectType = PULSE;
        enpvc.effectProperty = DURATION;
    }
    else if ([segue.identifier isEqualToString: @"PulsePeriod"])
    {
        LSFEffectV2NumericPropertyViewController *enpvc = [segue destinationViewController];
        enpvc.pendingEffect = self.pendingEffect;
        enpvc.effectType = PULSE;
        enpvc.effectProperty = PERIOD;
    }
    else if ([segue.identifier isEqualToString: @"PulseNumPulses"])
    {
        LSFEffectV2NumericPropertyViewController *enpvc = [segue destinationViewController];
        enpvc.pendingEffect = self.pendingEffect;
        enpvc.effectType = PULSE;
        enpvc.effectProperty = NUM_PULSES;
    }
    else if ([segue.identifier isEqualToString: @"PulsePreset"])
    {
        // store the latest slider state into the pending effect
        self.pendingEffect.state = [self getSlidersState];
        self.pendingEffect.endState = [self getEndSlidersState];

        LSFSelectPresetTableViewController *sptvc = [segue destinationViewController];
        sptvc.state = self.pendingEffect.state;
    }
    else if ([segue.identifier isEqualToString: @"PulsePresetEnd"])
    {
        // store the latest slider state into the pending effect
        self.pendingEffect.state = [self getSlidersState];
        self.pendingEffect.endState = [self getEndSlidersState];

        LSFSelectPresetTableViewController *sptvc = [segue destinationViewController];
        sptvc.state = self.pendingEffect.endState;
    }
}

-(void)updateColorIndicator
{
    [super updateColorIndicator];

    LSFSDKColor *color = [[LSFSDKColor alloc] initWithHue: self.endHueSlider.value saturation: self.endSaturationSlider.value brightness: self.endBrightnessSlider.value colorTemp: self.endColorTempSlider.value];

    [LSFUtilityFunctions colorIndicatorSetup: self.endColorIndicatorImage withColor: color andCapabilityData: nil];
}

-(void)checkSaturationValue
{
    [super checkSaturationValue];

    if (self.endSaturationSlider.value == 0)
    {
        self.endHueSlider.enabled = NO;
        self.endHueLabel.text = @"N/A";
        self.endHueSliderButton.enabled = YES;
    }
    else
    {
        self.endHueSlider.enabled = YES;
        self.endHueSliderButton.enabled = NO;
        self.endHueLabel.text = [NSString stringWithFormat:  @"%i°", (uint32_t)self.endHueSlider.value];
    }

    if (self.endSaturationSlider.value == 100)
    {
        self.endColorTempSlider.enabled = NO;
        self.endColorTempLabel.text = @"N/A";
        self.endColorTempSliderButton.enabled = YES;
    }
    else
    {
        self.endColorTempSlider.enabled = YES;
        self.endColorTempSliderButton.enabled = NO;
        self.endColorTempLabel.text = [NSString stringWithFormat: @"%iK", (uint32_t)self.endColorTempSlider.value];
    }
}

-(IBAction)endBrightnessSliderValueChanged: (UISlider *)sender
{
    NSString *endbrightnessText = [NSString stringWithFormat: @"%i%%", (uint32_t)sender.value];
    self.endBrightnessLabel.text = endbrightnessText;
}

-(IBAction)endHueSliderValueChanged: (UISlider *)sender
{
    NSString *endHueText = [NSString stringWithFormat: @"%i°", (uint32_t)sender.value];
    self.endHueLabel.text = endHueText;
}

-(IBAction)endSaturationSliderValueChanged: (UISlider *)sender
{
    NSString *endSaturationText = [NSString stringWithFormat: @"%i%%", (uint32_t)sender.value];
    self.endSaturationLabel.text = endSaturationText;
    [self checkSaturationValue];
}

-(IBAction)endColorTempSliderValueChanged: (UISlider *)sender
{
    NSString *endColorTempText = [NSString stringWithFormat: @"%iK", (uint32_t)sender.value];
    self.endColorTempLabel.text = endColorTempText;
}

-(LSFSDKMyLampState *)getEndSlidersState
{
    Power power = (self.brightnessSlider.value == 0) ? OFF : ON;
    unsigned int brightness = self.endBrightnessSlider.value;
    unsigned int hue = self.endHueSlider.value;
    unsigned int saturation = self.endSaturationSlider.value;
    unsigned int colorTemp = self.endColorTempSlider.value;

    LSFSDKMyLampState *state = [[LSFSDKMyLampState alloc] initWithPower: power hue: hue saturation: saturation brightness: brightness colorTemp: colorTemp];

    NSLog(@"%@ - %u", @"End Brightness", brightness);
    NSLog(@"%@ - %u", @"End Hue", hue);
    NSLog(@"%@ - %u", @"End Saturation", saturation);
    NSLog(@"%@ - %u", @"End ColorTemp", colorTemp);

    return state;
}

-(void)updateEndPresetButtonTitle: (UIButton*)presetButton
{
    unsigned int brightness = (uint32_t)self.endBrightnessSlider.value;
    unsigned int hue = (uint32_t)self.endHueSlider.value;
    unsigned int saturation = (uint32_t)self.endSaturationSlider.value;
    unsigned int colorTemp = (uint32_t)self.endColorTempSlider.value;
    LSFSDKColor *color = [[LSFSDKColor alloc] initWithHue: hue saturation: saturation brightness: brightness colorTemp: colorTemp];

    NSMutableArray *presetsArray = [[NSMutableArray alloc] init];
    BOOL presetMatched = NO;
    for (LSFSDKPreset *preset in [[LSFSDKLightingDirector getLightingDirector] presets])
    {
        BOOL matchesPreset = [LSFUtilityFunctions preset: preset matchesMyLampState: [[LSFSDKMyLampState alloc] initWithPower: (brightness == 0 ? OFF : ON) color: color]];

        if (matchesPreset)
        {
            [presetsArray addObject: preset.name];
            presetMatched = YES;
        }
    }

    if (presetMatched)
    {
        NSArray *sortedArray = [presetsArray sortedArrayUsingSelector: @selector(localizedCaseInsensitiveCompare:)];
        NSMutableString *presetsMatched = [[NSMutableString alloc] init];

        for (NSString *presetName in sortedArray)
        {
            [presetsMatched appendString: [NSString stringWithFormat:@"%@, ", presetName]];
        }

        [presetsMatched deleteCharactersInRange: NSMakeRange(presetsMatched.length - 2, 2)];
        [presetButton setTitle: presetsMatched forState: UIControlStateNormal];
    }
    else
    {
        [presetButton setTitle: @"Save New Preset" forState: UIControlStateNormal];
    }
}

@end
