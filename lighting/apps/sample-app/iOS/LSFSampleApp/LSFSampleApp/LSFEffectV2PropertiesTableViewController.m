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
#import "LSFUtilityFunctions.h"
#import "LSFLightingListenerUtil.h"
#import <LSFSDKLightingDirector.h>

@interface LSFEffectV2PropertiesTableViewController ()

@end

@implementation LSFEffectV2PropertiesTableViewController

@synthesize pendingScene = _pendingScene;
@synthesize pendingSceneElement = _pendingSceneElement;
@synthesize pendingEffect = _pendingEffect;

-(void)viewDidLoad
{
    [super viewDidLoad];

    [self.brightnessSlider addGestureRecognizer: [[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(onSliderTapped:)]];

    [self.hueSlider addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(onSliderTapped:)]];

    [self.saturationSlider addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(onSliderTapped:)]];

    [self.colorTempSlider addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(onSliderTapped:)]];

    [self.brightnessSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
    [self.brightnessSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];
    [self.hueSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
    [self.hueSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];
    [self.saturationSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
    [self.saturationSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];
    [self.colorTempSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
    [self.colorTempSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];

    self.colorTempSlider.minimumValue = [LSFUtilityFunctions getBoundedMinColorTempForMembers: self.pendingSceneElement.members];
    self.colorTempSlider.maximumValue = [LSFUtilityFunctions getBoundedMaxColorTempForMembers: self.pendingSceneElement.members];
    self.colorTempSlider.value = self.colorTempSlider.minimumValue;
    self.colorTempLabel.text = [NSString stringWithFormat: @"%iK", (uint32_t)self.colorTempSlider.value];

    self.colorIndicatorImage.layer.rasterizationScale = [UIScreen mainScreen].scale;
    self.colorIndicatorImage.layer.shouldRasterize = YES;

    [self updateColorIndicator];
    [self checkSaturationValue];
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear: animated];

    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];

    if (self.pendingEffect.state != nil)
    {
        LSFSDKColor *color = [self.pendingEffect.state color];
        [self updateSlider: self.colorTempSlider withValue: color.colorTemp];
        [self updateSlider: self.brightnessSlider withValue: color.brightness];
        [self updateSlider: self.hueSlider withValue: color.hue];
        [self updateSlider: self.saturationSlider withValue: color.saturation];
    }
    else
    {
        self.pendingEffect.state = [[LSFSDKMyLampState alloc] init];
    }
}

-(void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear: animated];
    [[NSNotificationCenter defaultCenter] removeObserver: self];
}

-(void)showErrorAlert: (NSString *)message
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                    message: message
                                                   delegate: nil
                                          cancelButtonTitle: @"OK"
                                          otherButtonTitles: nil];
    [alert show];
}

-(void)checkSaturationValue
{
    if (self.saturationSlider.value == 0)
    {
        self.hueSlider.enabled = NO;
        self.hueLabel.text = @"N/A";
        self.hueSliderButton.enabled = YES;
    }
    else
    {
        self.hueSlider.enabled = YES;
        self.hueSliderButton.enabled = NO;
        self.hueLabel.text = [NSString stringWithFormat:  @"%i°", (uint32_t)self.hueSlider.value];
    }

    if (self.saturationSlider.value == 100)
    {
        self.colorTempSlider.enabled = NO;
        self.colorTempLabel.text = @"N/A";
        self.colorTempSliderButton.enabled = YES;
    }
    else
    {
        self.colorTempSlider.enabled = YES;
        self.colorTempSliderButton.enabled = NO;
        self.colorTempLabel.text = [NSString stringWithFormat: @"%iK", (uint32_t)self.colorTempSlider.value];
    }
}

-(int) calculateSliderValueOnTap: (UIGestureRecognizer *)gr
{
    UISlider *slider = (UISlider *)gr.view;;

    if (slider.highlighted)
    {
        //tap on thumb, let slider deal with it
        return -1;
    }

    CGPoint pt = [gr locationInView: slider];
    CGFloat percentage = pt.x / slider.bounds.size.width;
    CGFloat delta = percentage * (slider.maximumValue - slider.minimumValue);
    CGFloat value = round(slider.minimumValue + delta);

    return value;
}

-(void)onSliderTapped: (UIGestureRecognizer *)gr
{
    int value = [self calculateSliderValueOnTap: gr];

    if (value != -1)
    {
        [self updateSlider: (UISlider *)gr.view withValue: value];
    }
}

-(void)updateSlider: (UISlider *)slider withValue: (int)value
{
    slider.value = value;
    [slider sendActionsForControlEvents: UIControlEventValueChanged];
    [slider sendActionsForControlEvents: UIControlEventTouchUpInside];
}

-(IBAction)onSliderTouchUpInside: (UISlider *)slider
{
    [self updateColorIndicator];
}

-(void)updateColorIndicator
{
    // Function should be overriden by subclass
    LSFSDKColor *color = [[LSFSDKColor alloc] initWithHue: self.hueSlider.value saturation: self.saturationSlider.value brightness: self.brightnessSlider.value colorTemp: self.colorTempSlider.value];

    [LSFUtilityFunctions colorIndicatorSetup: self.colorIndicatorImage withColor: color andCapabilityData: nil];
}

-(void)updatePresetButtonTitle: (UIButton*)presetButton
{
    unsigned int brightness = (uint32_t)self.brightnessSlider.value;
    unsigned int hue = (uint32_t)self.hueSlider.value;
    unsigned int saturation = (uint32_t)self.saturationSlider.value;
    unsigned int colorTemp = (uint32_t)self.colorTempSlider.value;
    LSFSDKColor *color = [[LSFSDKColor alloc] initWithHue: hue saturation: saturation brightness: brightness colorTemp: colorTemp];

    NSArray *presetsArray = [LSFUtilityFunctions getPresetsWithMyLampState: [[LSFSDKMyLampState alloc] initWithPower: (brightness == 0 ? OFF : ON) color: color]];

    if (presetsArray.count > 0)
    {
        NSArray *sortedArray = [[presetsArray valueForKeyPath: @"name"] sortedArrayUsingSelector: @selector(localizedCaseInsensitiveCompare:)];
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

/*
 * Slider Event Handlers
 */

-(IBAction)brightnessSliderValueChanged: (UISlider *)sender
{
    NSString *brightnessText = [NSString stringWithFormat: @"%i%%", (uint32_t)sender.value];
    self.brightnessLabel.text = brightnessText;
}

-(IBAction)brightnessSliderTouchDisabled:(UIButton *)sender
{
    [self showErrorAlert: @"This Lamp is not able to change its brightness."];
}

-(IBAction)hueSliderValueChanged: (UISlider *)sender
{
    NSString *hueText = [NSString stringWithFormat: @"%i°", (uint32_t)sender.value];
    self.hueLabel.text = hueText;
}

-(IBAction)hueSliderTouchDisabled: (UIButton *)sender
{
    [self showErrorAlert: @"Hue has no effect when saturation is zero. Set saturation to greater than zero to enable the hue slider."];
}

-(IBAction)saturationSliderValueChanged: (UISlider *)sender
{
    NSString *saturationText = [NSString stringWithFormat: @"%i%%", (uint32_t)sender.value];
    self.saturationLabel.text = saturationText;
    [self checkSaturationValue];
}

-(IBAction)saturationSliderTouchDisabled: (UIButton *)sender
{
    [self showErrorAlert: @"This Lamp is not able to change its saturation."];
}

-(IBAction)colorTempSliderValueChanged: (UISlider *)sender
{
    NSString *colorTempText = [NSString stringWithFormat: @"%iK", (uint32_t)sender.value];
    self.colorTempLabel.text = colorTempText;
}

-(IBAction)colorTempSliderTouchDisabled: (UIButton *)sender
{
    [self showErrorAlert: @"Color temperature has no effect when saturation is 100%. Set saturation to less than 100% to enable the color temperature slider."];
}

- (IBAction)doneButtonPressed:(id)sender
{
    NSLog(@"Done button pressed");

    self.pendingEffect.state = [self getSlidersState];
    [self handlePendingData];
}

-(LSFSDKMyLampState *)getSlidersState
{
    Power power = (self.brightnessSlider.value == 0) ? OFF : ON;
    unsigned int brightness = self.brightnessSlider.value;
    unsigned int hue = self.hueSlider.value;
    unsigned int saturation = self.saturationSlider.value;
    unsigned int colorTemp = self.colorTempSlider.value;

    LSFSDKMyLampState *state = [[LSFSDKMyLampState alloc] initWithPower: power hue: hue saturation: saturation brightness: brightness colorTemp: colorTemp];

    NSLog(@"%@ - %u", @"Brightness", brightness);
    NSLog(@"%@ - %u", @"Hue", hue);
    NSLog(@"%@ - %u", @"Saturation", saturation);
    NSLog(@"%@ - %u", @"ColorTemp", colorTemp);

    return state;
}

-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification
{
    LSFSDKController *leaderModel = [notification.userInfo valueForKey: @"leader"];
    if (![leaderModel connected])
    {
        [self dismissViewControllerAnimated: YES completion: nil];
    }
}

-(void)handlePendingData
{
    self.pendingSceneElement.pendingEffect = self.pendingEffect;

    if (!self.pendingSceneElement.theID)
    {
        [self.pendingScene.pendingSceneElements addObject: self.pendingSceneElement];

        if (self.pendingScene.theID)
        {
            [LSFLightingListenerUtil listenForTrackingID: [LSFUtilityFunctions createEffectFromPendingItem: self.pendingEffect] perform: ^(id item){
                self.pendingEffect.theID = ((id<LSFSDKEffect>)item).theID;

                [LSFLightingListenerUtil listenForTrackingID: [LSFUtilityFunctions createSceneElementFromPendingItem: self.pendingSceneElement] perform: ^(id item) {

                    self.pendingSceneElement.theID = ((LSFSDKSceneElement *)item).theID;

                    LSFSDKSceneV2 *scene = (LSFSDKSceneV2 *) [[LSFSDKLightingDirector getLightingDirector] getSceneWithID: self.pendingScene.theID];

                    NSMutableArray *elementIDs = [NSMutableArray arrayWithArray: [scene getSceneElementIDs]];
                    [elementIDs addObject: self.pendingSceneElement.theID];

                    [scene modify: self.pendingScene.pendingSceneElements];
                }];
            }];
        }
    }
    else
    {
        // update effect
        [LSFUtilityFunctions updateEffectWithID: self.pendingEffect.theID pendingItem: self.pendingEffect];
        // update sceneElement
        [LSFUtilityFunctions updateSceneElementWithID: self.pendingSceneElement.theID pendingItem: self.pendingSceneElement];
    }
}

@end
