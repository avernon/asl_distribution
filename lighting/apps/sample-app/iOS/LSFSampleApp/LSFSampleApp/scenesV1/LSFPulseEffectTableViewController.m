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

#import "LSFPulseEffectTableViewController.h"
#import "LSFSceneElementEffectPropertiesViewController.h"
#import "LSFScenesPresetsTableViewController.h"
#import "LSFUtilityFunctions.h"
#import <LSFSDKLightingDirector.h>
#import <model/LSFConstants.h>

@interface LSFPulseEffectTableViewController ()

-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification;
-(void)sceneRemovedNotificationReceived:(NSNotification *)notification;
-(void)alertSceneDeleted: (LSFSDKScene *)scene;
-(void)presetNotificationReceived: (NSNotification *)notification;
-(void)endBrightnessSliderTapped: (UIGestureRecognizer *)gr;
-(void)endHueSliderTapped: (UIGestureRecognizer *)gr;
-(void)endSaturationSliderTapped: (UIGestureRecognizer *)gr;
-(void)endColorTempSliderTapped: (UIGestureRecognizer *)gr;
-(void)showWarning;

@end

@implementation LSFPulseEffectTableViewController

@synthesize startPropertiesSwitch = _startPropertiesSwitch;
@synthesize endPresetButton = _endPresetButton;
@synthesize endBrightnessSlider = _endBrightnessSlider;
@synthesize endBrightnessButton = _endBrightnessButton;
@synthesize endBrightnessLabel = _endBrightnessLabel;
@synthesize endHueSlider = _endHueSlider;
@synthesize endHueButton = _endHueButton;
@synthesize endHueLabel = _endHueLabel;
@synthesize endSaturationSlider = _endSaturationSlider;
@synthesize endSaturationButton = _endSaturationButton;
@synthesize endSaturationLabel = _endSaturationLabel;
@synthesize endColorTempSlider = _endColorTempSlider;
@synthesize endColorTempButton = _endColorTempButton;
@synthesize endColorTempLabel = _endColorTempLabel;
@synthesize durationLabel = _durationLabel;
@synthesize periodLabel = _periodLabel;
@synthesize numPulsesLabel = _numPulsesLabel;
@synthesize sceneModel = _sceneModel;
@synthesize pedm = _pedm;
@synthesize shouldUpdateSceneAndDismiss = _shouldUpdateSceneAndDismiss;


-(void)viewDidLoad
{
    [super viewDidLoad];

    UITapGestureRecognizer *endBrightnessTGR = [[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(endBrightnessSliderTapped:)];
    [self.endBrightnessSlider addGestureRecognizer: endBrightnessTGR];
    [self.endBrightnessSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
    [self.endBrightnessSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];

    UITapGestureRecognizer *endHueTGR = [[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(endHueSliderTapped:)];
    [self.endHueSlider addGestureRecognizer: endHueTGR];
    [self.endHueSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
    [self.endHueSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];

    UITapGestureRecognizer *endSaturationTGR = [[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(endSaturationSliderTapped:)];
    [self.endSaturationSlider addGestureRecognizer: endSaturationTGR];
    [self.endSaturationSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
    [self.endSaturationSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];

    UITapGestureRecognizer *endColorTempTGR = [[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(endColorTempSliderTapped:)];
    [self.endColorTempSlider addGestureRecognizer: endColorTempTGR];
    [self.endColorTempSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
    [self.endColorTempSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];

    self.endColorIndicatorImage.layer.rasterizationScale = [UIScreen mainScreen].scale;
    self.endColorIndicatorImage.layer.shouldRasterize = YES;
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    //Set notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(sceneRemovedNotificationReceived:) name: @"LSFSceneRemovedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(presetNotificationReceived:) name: @"LSFPresetChangedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(presetNotificationReceived:) name: @"LSFPresetRemovedNotification" object: nil];

    NSLog(@"LSFPulseEffectTableViewController - viewWillAppear() executing");
    NSLog(@"Power = %@", self.pedm.state.onOff ? @"On" : @"Off");
    NSLog(@"Brightness = %u", self.pedm.state.brightness);
    NSLog(@"Hue = %u", self.pedm.state.hue);
    NSLog(@"Saturation = %u", self.pedm.state.saturation);
    NSLog(@"Color Temp = %u", self.pedm.state.colorTemp);
    NSLog(@"End Power = %@", self.pedm.endState.onOff ? @"On" : @"Off");
    NSLog(@"End Brightness = %u", self.pedm.endState.brightness);
    NSLog(@"End Hue = %u", self.pedm.endState.hue);
    NSLog(@"End Saturation = %u", self.pedm.endState.saturation);
    NSLog(@"End Color Temp = %u", self.pedm.endState.colorTemp);
    NSLog(@"Capability = [%@, %@, %@]", self.pedm.capability.dimmable ? @"Dimmable" : @"Not Dimmable", self.pedm.capability.color ? @"Color" : @"No Color", self.pedm.capability.temp ? @"Variable Color Temp" : @"No Variable Color Temp");
    NSLog(@"Color Temp Min = %u", self.pedm.colorTempMin);
    NSLog(@"Color Temp Max = %u", self.pedm.colorTempMax);

    if (self.pedm != nil)
    {
        NSNumberFormatter *fmt = [[NSNumberFormatter alloc] init];
        [fmt setPositiveFormat: @"0.########"];

        self.durationLabel.text = [NSString stringWithFormat: @"%@ seconds", [fmt stringFromNumber: [NSNumber numberWithDouble: ((double)self.pedm.duration / 1000.0)]]];
        self.periodLabel.text = [NSString stringWithFormat: @"%@ seconds", [fmt stringFromNumber: [NSNumber numberWithDouble: ((double)self.pedm.period / 1000.0)]]];
        self.numPulsesLabel.text = [NSString stringWithFormat: @"%u", self.pedm.numPulses];

        self.startPropertiesSwitch.on = NO;

        if (self.pedm.capability.dimmable >= SOME)
        {
            unsigned int brightness = self.pedm.state.brightness;
            self.brightnessSlider.value = brightness;
            self.brightnessSlider.enabled = YES;
            self.brightnessLabel.text = [NSString stringWithFormat: @"%u%%", brightness];
            self.brightnessSliderButton.enabled = NO;
        }
        else
        {
            self.brightnessSlider.value = 0;
            self.brightnessSlider.enabled = NO;
            self.brightnessLabel.text = @"N/A";
            self.brightnessSliderButton.enabled = YES;
        }

        if (self.pedm.capability.color >= SOME)
        {
            unsigned int hue = self.pedm.state.hue;
            self.hueSlider.value = hue;

            if (self.pedm.state.saturation == 0)
            {
                self.hueSlider.enabled = NO;
                self.hueLabel.text = @"N/A";
                self.hueSliderButton.enabled = YES;
            }
            else
            {
                self.hueSlider.enabled = YES;
                self.hueLabel.text = [NSString stringWithFormat: @"%u°", hue];
                self.hueSliderButton.enabled = NO;
            }

            unsigned int saturation = self.pedm.state.saturation;
            self.saturationSlider.value = saturation;
            self.saturationSlider.enabled = YES;
            self.saturationLabel.text = [NSString stringWithFormat: @"%u%%", saturation];
            self.saturationSliderButton.enabled = NO;
        }
        else
        {
            self.hueSlider.value = 0;
            self.hueSlider.enabled = NO;
            self.hueLabel.text = @"N/A";
            self.hueSliderButton.enabled = YES;

            self.saturationSlider.value = 0;
            self.saturationSlider.enabled = NO;
            self.saturationLabel.text = @"N/A";
            self.saturationSliderButton.enabled = YES;
        }

        self.colorTempSlider.minimumValue = self.pedm.colorTempMin;
        self.colorTempSlider.maximumValue = self.pedm.colorTempMax;
        self.colorTempSlider.value = self.pedm.colorTempMin;

        if (self.pedm.capability.temp >= SOME)
        {
            if (self.pedm.state.saturation == 100)
            {
                self.colorTempSlider.enabled = NO;
                self.colorTempLabel.text = @"N/A";
                self.colorTempSliderButton.enabled = YES;
            }
            else
            {
                self.colorTempSlider.enabled = YES;
                self.colorTempLabel.text = [NSString stringWithFormat: @"%iK", (uint32_t)self.colorTempSlider.value];
                self.colorTempSliderButton.enabled = NO;
            }
        }
        else
        {
            self.colorTempSlider.enabled = NO;
            self.colorTempLabel.text = @"N/A";
            self.colorTempSliderButton.enabled = YES;
        }

        [self checkSaturationValueForStartState];
    }

    if (self.pedm.capability.dimmable >= SOME)
    {
        unsigned int endBrightness = self.pedm.endState.brightness;
        self.endBrightnessSlider.value = endBrightness;
        self.endBrightnessSlider.enabled = YES;
        self.endBrightnessLabel.text = [NSString stringWithFormat: @"%u%%", endBrightness];
        self.endBrightnessButton.enabled = NO;
    }
    else
    {
        self.endBrightnessSlider.value = 0;
        self.endBrightnessSlider.enabled = NO;
        self.endBrightnessLabel.text = @"N/A";
        self.endBrightnessButton.enabled = YES;
    }

    if (self.pedm.capability.color >= SOME)
    {
        unsigned int endHue = self.pedm.endState.hue;
        self.endHueSlider.value = endHue;

        if (self.pedm.endState.saturation == 0)
        {
            self.endHueSlider.enabled = NO;
            self.endHueLabel.text = @"N/A";
            self.endHueButton.enabled = YES;
        }
        else
        {
            self.endHueSlider.enabled = YES;
            self.endHueLabel.text = [NSString stringWithFormat: @"%u°", endHue];
            self.endHueButton.enabled = NO;
        }

        unsigned int endSaturation = self.pedm.endState.saturation;
        self.endSaturationSlider.value = endSaturation;
        self.endSaturationSlider.enabled = YES;
        self.endSaturationLabel.text = [NSString stringWithFormat: @"%u%%", endSaturation];
        self.endSaturationButton.enabled = NO;
    }
    else
    {
        self.endHueSlider.value = 0;
        self.endHueSlider.enabled = NO;
        self.endHueLabel.text = @"N/A";
        self.endHueButton.enabled = YES;

        self.endSaturationSlider.value = 0;
        self.endSaturationSlider.enabled = NO;
        self.endSaturationLabel.text = @"N/A";
        self.endSaturationButton.enabled = YES;
    }

    self.endColorTempSlider.minimumValue = self.pedm.colorTempMin;
    self.endColorTempSlider.maximumValue = self.pedm.colorTempMax;
    self.endColorTempSlider.value = self.pedm.colorTempMin;

    if (self.pedm.capability.temp >= SOME)
    {
        if (self.pedm.endState.saturation == 100)
        {
            self.endColorTempSlider.enabled = NO;
            self.endColorTempLabel.text = @"N/A";
            self.endColorTempButton.enabled = YES;
        }
        else
        {
            self.endColorTempSlider.enabled = YES;
            self.endColorTempLabel.text = [NSString stringWithFormat: @"%iK", (int)self.endColorTempSlider.value];
            self.endColorTempButton.enabled = NO;
        }
    }
    else
    {
        self.endColorTempSlider.enabled = NO;
        self.endColorTempLabel.text = @"N/A";
        self.endColorTempButton.enabled = YES;
    }

    [self checkSaturationValueForEndState];

    unsigned int brightness = self.pedm.state.brightness;
    unsigned int hue = self.pedm.state.hue;
    unsigned int saturation = self.pedm.state.saturation;
    unsigned int colorTemp = self.pedm.state.colorTemp;

    LSFSDKColor *lStartColor = [[LSFSDKColor alloc] initWithHue: hue saturation: saturation brightness: brightness colorTemp: colorTemp];

    [LSFUtilityFunctions colorIndicatorSetup: self.colorIndicatorImage withColor: lStartColor andCapabilityData: [[LSFSDKCapabilityData alloc] initWithCapabilityData: self.pedm.capability]];

    brightness = self.pedm.endState.brightness;
    hue = self.pedm.endState.hue;
    saturation = self.pedm.endState.saturation;
    colorTemp = self.pedm.endState.colorTemp;

    LSFSDKColor *lEndColor = [[LSFSDKColor alloc] initWithHue: hue saturation: saturation brightness: brightness colorTemp: colorTemp];

    [LSFUtilityFunctions colorIndicatorSetup: self.endColorIndicatorImage withColor: lEndColor andCapabilityData: [[LSFSDKCapabilityData alloc] initWithCapabilityData: self.pedm.capability]];

    [self presetButtonSetup: self.presetButton state: self.pedm.state];
    [self presetButtonSetup: self.endPresetButton state: self.pedm.endState];
}

-(void)viewWillDisappear: (BOOL)animated
{
    [super viewWillDisappear: animated];

    if (self.isMovingFromParentViewController)
    {
        LSFConstants *constants = [LSFConstants getConstants];
        self.pedm.state.brightness = [constants scaleLampStateValue:self.pedm.state.brightness withMax:100];
        self.pedm.state.hue = [constants scaleLampStateValue:self.pedm.state.hue withMax:360];
        self.pedm.state.saturation = [constants scaleLampStateValue:self.pedm.state.saturation withMax:100];
        self.pedm.state.colorTemp = [constants scaleColorTemp:self.pedm.state.colorTemp];

        self.pedm.endState.brightness = [constants scaleLampStateValue:self.pedm.endState.brightness withMax:100];
        self.pedm.endState.hue = [constants scaleLampStateValue:self.pedm.endState.hue withMax:360];
        self.pedm.endState.saturation = [constants scaleLampStateValue:self.pedm.endState.saturation withMax:100];
        self.pedm.endState.colorTemp = [constants scaleColorTemp:self.pedm.endState.colorTemp];
    }

    //Clear groups notification handler
    [[NSNotificationCenter defaultCenter] removeObserver: self];
}

-(void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

/*
 * Notification Handlers
 */
-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification
{
    LSFSDKController *leaderModel = [notification.userInfo valueForKey: @"leader"];
    if (![leaderModel connected])
    {
        [self dismissViewControllerAnimated: YES completion: nil];
    }
}

-(void)sceneRemovedNotificationReceived:(NSNotification *)notification
{
    LSFSDKScene *scene = [notification.userInfo valueForKey: @"scene"];

    if ([self.sceneModel.theID isEqualToString: scene.theID])
    {
        [self alertSceneDeleted: scene];
    }
}

-(void)alertSceneDeleted: (LSFSDKScene *)scene
{
    [self dismissViewControllerAnimated: NO completion: nil];

    dispatch_async(dispatch_get_main_queue(), ^{
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Scene Not Found"
                                                        message: [NSString stringWithFormat: @"The scene \"%@\" no longer exists.", [scene name]]
                                                       delegate: nil
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];
    });
}

-(void)presetNotificationReceived: (NSNotification *)notification
{
    [self updatePresetButtonTitle: self.presetButton];
    [self presetButtonSetup: self.endPresetButton state: [self getCurrentEndLampState]];
}

/*
 * Table View Data Source Methods
 */
-(NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    if (section == 0)
    {
        return [NSString stringWithFormat: @"Select the start and end properties that %@ will cycle through", [self buildSectionTitleString: self.pedm]];
    }

    return @"";
}

/*
 * Various event handlers
 */
-(IBAction)endBrightnessSliderValueChanged: (UISlider *)sender
{
    NSString *endBrightnessText = [NSString stringWithFormat: @"%i%%", (uint32_t)sender.value];
    self.endBrightnessLabel.text = endBrightnessText;
}

-(IBAction)endBrightnessSliderTouchUpInside: (UISlider *)sender
{
    [self presetButtonSetup: self.endPresetButton state: [self getCurrentEndLampState]];
    [self updateEndColorIndicator];
}

-(IBAction)endBrightnessSliderTouchUpOutside: (UISlider *)sender
{
    [self presetButtonSetup: self.endPresetButton state: [self getCurrentEndLampState]];
    [self updateEndColorIndicator];
}

-(IBAction)endHueSliderValueChanged: (UISlider *)sender
{
    NSString *endHueText = [NSString stringWithFormat: @"%i°", (uint32_t)sender.value];
    self.endHueLabel.text = endHueText;
}

-(IBAction)endHueSliderTouchUpInside: (UISlider *)sender
{
    [self presetButtonSetup: self.endPresetButton state: [self getCurrentEndLampState]];
    [self updateEndColorIndicator];
}

-(IBAction)endHueSliderTouchUpOutside: (UISlider *)sender
{
    [self presetButtonSetup: self.endPresetButton state: [self getCurrentEndLampState]];
    [self updateEndColorIndicator];
}

-(IBAction)endSaturationSliderValueChanged: (UISlider *)sender
{
    NSString *endSaturationText = [NSString stringWithFormat: @"%i%%", (uint32_t)sender.value];
    self.endSaturationLabel.text = endSaturationText;
    [self checkSaturationValueForEndState];
}

-(IBAction)endSaturationSliderTouchUpInside: (UISlider *)sender
{
    [self presetButtonSetup: self.endPresetButton state: [self getCurrentEndLampState]];
    [self updateEndColorIndicator];
    [self checkSaturationValueForEndState];
}

-(IBAction)endSaturationSliderTouchUpOutside: (UISlider *)sender
{
    [self presetButtonSetup: self.endPresetButton state: [self getCurrentEndLampState]];
    [self updateEndColorIndicator];
    [self checkSaturationValueForEndState];
}

-(IBAction)endColorTempSliderValueChanged: (UISlider *)sender
{
    NSString *endColorTempText = [NSString stringWithFormat: @"%iK", (uint32_t)sender.value];
    self.endColorTempLabel.text = endColorTempText;
}

-(IBAction)endColorTempSliderTouchUpInside: (UISlider *)sender
{
    [self presetButtonSetup: self.endPresetButton state: [self getCurrentEndLampState]];
    [self updateEndColorIndicator];
}

-(IBAction)endColorTempSliderTouchUpOutside: (UISlider *)sender
{
    [self presetButtonSetup: self.endPresetButton state: [self getCurrentEndLampState]];
    [self updateEndColorIndicator];
}

-(IBAction)startPropertiesSwitchValueChanged: (UISwitch *)sender
{
    if (sender.on)
    {
        self.brightnessSlider.enabled = NO;
        self.hueSlider.enabled = NO;
        self.saturationSlider.enabled = NO;
        self.colorTempSlider.enabled = NO;

        self.brightnessLabel.text = @"N/A";
        self.hueLabel.text = @"N/A";
        self.saturationLabel.text = @"N/A";
        self.colorTempLabel.text = @"N/A";

        self.brightnessSliderButton.enabled = YES;
        self.hueSliderButton.enabled = YES;
        self.saturationSliderButton.enabled = YES;
        self.colorTempSliderButton.enabled = YES;
    }
    else
    {
        if (self.pedm.capability.dimmable >= SOME)
        {
            self.brightnessSlider.enabled = YES;
            self.brightnessLabel.text = [NSString stringWithFormat: @"%i%%", (uint32_t)self.brightnessSlider.value];
            self.brightnessSliderButton.enabled = NO;
        }
        else
        {
            self.brightnessSlider.enabled = NO;
            self.brightnessLabel.text = @"N/A";
            self.brightnessSliderButton.enabled = YES;
        }

        if (self.pedm.capability.color >= SOME)
        {
            self.hueSlider.enabled = YES;
            self.hueLabel.text = [NSString stringWithFormat: @"%i°", (uint32_t)self.hueSlider.value];
            self.hueSliderButton.enabled = NO;

            self.saturationSlider.enabled = YES;
            self.saturationLabel.text = [NSString stringWithFormat: @"%i%%", (uint32_t)self.saturationSlider.value];
            self.saturationSliderButton.enabled = NO;
        }
        else
        {
            self.hueSlider.enabled = NO;
            self.hueLabel.text = @"N/A";
            self.hueSliderButton.enabled = YES;

            self.saturationSlider.enabled = NO;
            self.saturationLabel.text = @"N/A";
            self.saturationSliderButton.enabled = YES;
        }

        if (self.pedm.capability.temp >= SOME)
        {
            self.colorTempSlider.enabled = YES;
            self.colorTempLabel.text = [NSString stringWithFormat: @"%iK", (uint32_t)self.colorTempSlider.value];
            self.colorTempSliderButton.enabled = NO;
        }
        else
        {
            self.colorTempSlider.enabled = NO;
            self.colorTempLabel.text = @"N/A";
            self.colorTempSliderButton.enabled = YES;
        }

        [self checkSaturationValueForStartState];
    }
}

-(IBAction)startBrightnessSliderTouchedWhileDisabled: (UIButton *)sender
{
    if (self.startPropertiesSwitch.on)
    {
        [self showWarning];
    }
    else
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error" message: @"This Lamp is not able to change its brightness." delegate: nil cancelButtonTitle: @"OK" otherButtonTitles: nil];
        [alert show];
    }
}

-(IBAction)startHueSliderTouchedWhileDisabled: (UIButton *)sender
{
    if (self.startPropertiesSwitch.on)
    {
        [self showWarning];
    }
    else
    {
        if (self.pedm.capability.color == NONE)
        {
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error" message: @"This Lamp is not able to change its hue." delegate: nil cancelButtonTitle: @"OK" otherButtonTitles: nil];
            [alert show];
        }
        else
        {
            [self showHueAlert];
        }
    }
}

-(IBAction)startSaturationSliderTouchedWhileDisabled: (UIButton *)sender
{
    if (self.startPropertiesSwitch.on)
    {
        [self showWarning];
    }
    else
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error" message: @"This Lamp is not able to change its saturation." delegate: nil cancelButtonTitle: @"OK" otherButtonTitles: nil];
        [alert show];
    }
}

-(IBAction)startColorTempSliderTouchedWhileDisabled: (UIButton *)sender
{
    if (self.startPropertiesSwitch.on)
    {
        [self showWarning];
    }
    else
    {
        if (self.pedm.capability.color == NONE)
        {
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error" message: @"This Lamp is not able to change its color temp." delegate: nil cancelButtonTitle: @"OK" otherButtonTitles: nil];
            [alert show];
        }
        else
        {
            [self showColorTempAlert];
        }
    }
}

-(IBAction)endBrightnessSliderTouchedWhileDisabled: (UIButton *)sender
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error" message: @"This Lamp is not able to change its brightness." delegate: nil cancelButtonTitle: @"OK" otherButtonTitles: nil];
    [alert show];
}

-(IBAction)endHueSliderTouchedWhileDisabled: (UIButton *)sender
{
    if (self.pedm.capability.color == NONE)
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error" message: @"This Lamp is not able to change its hue." delegate: nil cancelButtonTitle: @"OK" otherButtonTitles: nil];
        [alert show];
    }
    else
    {
        [self showHueAlert];
    }
}

-(IBAction)endSaturationSliderTouchedWhileDisabled: (UIButton *)sender
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error" message: @"This Lamp is not able to change its saturation." delegate: nil cancelButtonTitle: @"OK" otherButtonTitles: nil];
    [alert show];
}

-(IBAction)endColorTempSliderTouchedWhileDisabled: (UIButton *)sender
{
    if (self.pedm.capability.color == NONE)
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error" message: @"This Lamp is not able to change its color temp." delegate: nil cancelButtonTitle: @"OK" otherButtonTitles: nil];
        [alert show];
    }
    else
    {
        [self showColorTempAlert];
    }
}

-(IBAction)doneButtonPressed: (id)sender
{
    LSFConstants *constants = [LSFConstants getConstants];

    //Get Lamp State
    if (!self.startPropertiesSwitch.on)
    {
        unsigned int scaledBrightness = [constants scaleLampStateValue: (uint32_t)self.brightnessSlider.value withMax: 100];
        unsigned int scaledHue = [constants scaleLampStateValue: (uint32_t)self.hueSlider.value withMax: 360];
        unsigned int scaledSaturation = [constants scaleLampStateValue: (uint32_t)self.saturationSlider.value withMax: 100];
        unsigned int scaledColorTemp = [constants scaleColorTemp: (uint32_t)self.colorTempSlider.value];

        if (self.pedm.capability.dimmable == NONE && self.pedm.capability.color == NONE && self.pedm.capability.temp == NONE)
        {
            self.pedm.state.onOff = YES;
            self.pedm.state.brightness = [constants scaleLampStateValue: 100 withMax: 100];
        }
        else
        {
            self.pedm.state.onOff = YES;
            self.pedm.state.brightness = scaledBrightness;
        }

        self.pedm.state.hue = scaledHue;
        self.pedm.state.saturation = scaledSaturation;
        self.pedm.state.colorTemp = scaledColorTemp;
        self.pedm.state.isNull = NO;
    }
    else
    {
        self.pedm.state = [[LSFLampState alloc] init];
    }

    unsigned int scaledEndBrightness = [constants scaleLampStateValue: (uint32_t)self.endBrightnessSlider.value withMax: 100];
    unsigned int scaledEndHue = [constants scaleLampStateValue: (uint32_t)self.endHueSlider.value withMax: 360];
    unsigned int scaledEndSaturation = [constants scaleLampStateValue: (uint32_t)self.endSaturationSlider.value withMax: 100];
    unsigned int scaledEndColorTemp = [constants scaleColorTemp: (uint32_t)self.endColorTempSlider.value];

    if (self.pedm.capability.dimmable == NONE && self.pedm.capability.color == NONE && self.pedm.capability.temp == NONE)
    {
        self.pedm.endState.onOff = YES;
        self.pedm.endState.brightness = [constants scaleLampStateValue: 100 withMax: 100];
    }
    else
    {
        self.pedm.endState.onOff = YES;
        self.pedm.endState.brightness = scaledEndBrightness;
    }

    self.pedm.endState.hue = scaledEndHue;
    self.pedm.endState.saturation = scaledEndSaturation;
    self.pedm.endState.colorTemp = scaledEndColorTemp;
    self.pedm.endState.isNull = NO;

    [self.sceneModel updatePulseEffect: self.pedm];

    if (self.shouldUpdateSceneAndDismiss)
    {
        [[[[LSFSDKLightingDirector getLightingDirector] lightingManager] sceneManager] updateSceneWithID: self.sceneModel.theID withScene: [self.sceneModel toScene]];
    }

    [self dismissViewControllerAnimated: YES completion: nil];
}

/*
 * Override public function from LSFEffectTableViewController
 */
-(void)updateColorIndicator
{
    LSFSDKColor *lcolor = [[LSFSDKColor alloc] initWithHue: self.hueSlider.value saturation: self.saturationSlider.value brightness: self.brightnessSlider.value colorTemp: self.colorTempSlider.value];
    [LSFUtilityFunctions colorIndicatorSetup: self.colorIndicatorImage withColor: lcolor andCapabilityData: [[LSFSDKCapabilityData alloc] initWithCapabilityData: self.pedm.capability]];
}

/*
 * Private functions
 */
-(void)updateEndColorIndicator
{
    LSFSDKColor *lcolor = [[LSFSDKColor alloc] initWithHue: self.endHueSlider.value saturation: self.endSaturationSlider.value brightness: self.endBrightnessSlider.value colorTemp: self.endColorTempSlider.value];
    [LSFUtilityFunctions colorIndicatorSetup: self.endColorIndicatorImage withColor: lcolor andCapabilityData: [[LSFSDKCapabilityData alloc] initWithCapabilityData: self.pedm.capability]];
}

-(void)endBrightnessSliderTapped: (UIGestureRecognizer *)gr
{
    UISlider *s = (UISlider *)gr.view;

    if (s.highlighted)
    {
        //tap on thumb, let slider deal with it
        return;
    }

    CGPoint pt = [gr locationInView: s];
    CGFloat percentage = pt.x / s.bounds.size.width;
    CGFloat delta = percentage * (s.maximumValue - s.minimumValue);
    CGFloat value = round(s.minimumValue + delta);

    NSString *endBrightnessText = [NSString stringWithFormat: @"%i%%", (uint32_t)value];
    self.endBrightnessLabel.text = endBrightnessText;
    self.endBrightnessSlider.value = value;

    [self updateEndColorIndicator];

    LSFLampState *currState = [[LSFLampState alloc] initWithOnOff: YES brightness: self.endBrightnessSlider.value hue: self.endHueSlider.value saturation: self.endSaturationSlider.value colorTemp: self.endColorTempSlider.value];
    [self presetButtonSetup: self.endPresetButton state:currState];
}

-(void)endHueSliderTapped: (UIGestureRecognizer *)gr
{
    UISlider *s = (UISlider *)gr.view;

    if (s.highlighted)
    {
        //tap on thumb, let slider deal with it
        return;
    }

    CGPoint pt = [gr locationInView: s];
    CGFloat percentage = pt.x / s.bounds.size.width;
    CGFloat delta = percentage * (s.maximumValue - s.minimumValue);
    CGFloat value = round(s.minimumValue + delta);

    NSString *endHueText = [NSString stringWithFormat: @"%i°", (uint32_t)value];
    self.endHueLabel.text = endHueText;
    self.endHueSlider.value = value;

    [self updateEndColorIndicator];

    LSFLampState *currState = [[LSFLampState alloc] initWithOnOff: YES brightness: self.endBrightnessSlider.value hue: self.endHueSlider.value saturation: self.endSaturationSlider.value colorTemp: self.endColorTempSlider.value];
    [self presetButtonSetup: self.endPresetButton state:currState];
}

-(void)endSaturationSliderTapped: (UIGestureRecognizer *)gr
{
    UISlider *s = (UISlider *)gr.view;

    if (s.highlighted)
    {
        //tap on thumb, let slider deal with it
        return;
    }

    CGPoint pt = [gr locationInView: s];
    CGFloat percentage = pt.x / s.bounds.size.width;
    CGFloat delta = percentage * (s.maximumValue - s.minimumValue);
    CGFloat value = round(s.minimumValue + delta);

    NSString *endSaturationText = [NSString stringWithFormat: @"%i%%", (uint32_t)value];
    self.endSaturationLabel.text = endSaturationText;
    self.endSaturationSlider.value = value;

    [self updateEndColorIndicator];

    LSFLampState *currState = [[LSFLampState alloc] initWithOnOff: YES brightness: self.endBrightnessSlider.value hue: self.endHueSlider.value saturation: self.endSaturationSlider.value colorTemp: self.endColorTempSlider.value];
    [self presetButtonSetup: self.endPresetButton state:currState];
    [self checkSaturationValueForEndState];
}

-(void)endColorTempSliderTapped: (UIGestureRecognizer *)gr
{
    UISlider *s = (UISlider *)gr.view;

    if (s.highlighted)
    {
        //tap on thumb, let slider deal with it
        return;
    }

    CGPoint pt = [gr locationInView: s];
    CGFloat percentage = pt.x / s.bounds.size.width;
    CGFloat delta = percentage * (s.maximumValue - s.minimumValue);
    CGFloat value = round(s.minimumValue + delta);

    NSString *endColorTempText = [NSString stringWithFormat: @"%iK", (uint32_t)value];
    self.endColorTempLabel.text = endColorTempText;
    self.endColorTempSlider.value = value;

    [self updateEndColorIndicator];


    LSFLampState *currState = [[LSFLampState alloc] initWithOnOff: YES brightness: self.endBrightnessSlider.value hue: self.endHueSlider.value saturation: self.endSaturationSlider.value colorTemp: self.endColorTempSlider.value];
    [self presetButtonSetup: self.endPresetButton state:currState];
}

-(void)showWarning
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                    message: @"You must switch the start properties switch off if you want to specify a start state."
                                                   delegate: nil
                                          cancelButtonTitle: @"OK"
                                          otherButtonTitles: nil];
    [alert show];
}

-(void)presetButtonSetup:(UIButton *)presetButton state:(LSFLampState*)state
{
    Power power = state.onOff? ON : OFF;
    LSFSDKColor *color = [[LSFSDKColor alloc] initWithHue: state.hue saturation: state.saturation brightness: state.brightness colorTemp: state.colorTemp];

    NSMutableArray *presetsArray = [[NSMutableArray alloc] init];
    BOOL presetMatched = NO;
    for (LSFSDKPreset *preset in [[LSFSDKLightingDirector getLightingDirector] presets])
    {
        BOOL matchesPreset = [self checkIfPreset: preset matchesPower: power andColor: color];

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

-(LSFLampState *)getCurrentEndLampState
{
    unsigned int brightness = (uint32_t)self.endBrightnessSlider.value;
    unsigned int hue = (uint32_t)self.endHueSlider.value;
    unsigned int saturation = (uint32_t)self.endSaturationSlider.value;
    unsigned int colorTemp = (uint32_t)self.endColorTempSlider.value;

    return [[LSFLampState alloc] initWithOnOff: (brightness == 0 ? NO : YES) brightness: brightness hue: hue saturation: saturation colorTemp: colorTemp];
}

/*
 * Segue Methods
 */
-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    unsigned int startBrightness = (uint32_t)self.brightnessSlider.value;
    unsigned int startHue = (uint32_t)self.hueSlider.value;
    unsigned int startSaturation = (uint32_t)self.saturationSlider.value;
    unsigned int startColorTemp = (uint32_t)self.colorTempSlider.value;

    unsigned int endBrightness = (uint32_t)self.endBrightnessSlider.value;
    unsigned int endHue = (uint32_t)self.endHueSlider.value;
    unsigned int endSaturation = (uint32_t)self.endSaturationSlider.value;
    unsigned int endColorTemp = (uint32_t)self.endColorTempSlider.value;

    self.pedm.endState = [[LSFLampState alloc] initWithOnOff: (endBrightness? YES : NO) brightness: endBrightness hue: endHue saturation: endSaturation colorTemp: endColorTemp];

    if ([segue.destinationViewController isKindOfClass:[LSFSceneElementEffectPropertiesViewController class]])
    {
        LSFSceneElementEffectPropertiesViewController *seepvc = [segue destinationViewController];
        seepvc.pedm = self.pedm;

        if ([segue.identifier isEqualToString: @"PulseDuration"])
        {
            seepvc.effectProperty = PulseDuration;
        }
        else if ([segue.identifier isEqualToString: @"PulsePeriod"])
        {
            seepvc.effectProperty = PulsePeriod;
        }
        else if ([segue.identifier isEqualToString: @"PulseNumPulses"])
        {
            seepvc.effectProperty = PulseNumPulses;
        }

        seepvc.effectSender = self;
        seepvc.sceneID = self.sceneModel.theID;
    }
    else if ([segue.destinationViewController isKindOfClass:[LSFScenesPresetsTableViewController class]])
    {
        LSFScenesPresetsTableViewController *sptvc = [segue destinationViewController];

        if ([segue.identifier isEqualToString: @"ScenePresetsStart"])
        {
            sptvc.myLampState = [[LSFSDKMyLampState alloc] initWithPower: (startBrightness == 0 ? ON : OFF) hue: startHue saturation:startSaturation brightness: startBrightness colorTemp: startColorTemp];
        }
        else if ([segue.identifier isEqualToString: @"ScenePresetsStop"])
        {
            sptvc.myLampState = [[LSFSDKMyLampState alloc] initWithPower: (startBrightness == 0 ? ON : OFF) hue: endHue saturation: endSaturation brightness: endBrightness colorTemp: endColorTemp];
            sptvc.endStateFlag = YES;
        }

        sptvc.effectSender = self;
        sptvc.sceneID = self.sceneModel.theID;
    }
}

-(void)checkSaturationValueForStartState
{
    if (self.pedm.capability.color >= SOME && self.pedm.capability.temp >= SOME)
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
            unsigned int hue = self.pedm.state.hue;
            self.hueLabel.text = [NSString stringWithFormat: @"%i°", hue];
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
}

-(void)checkSaturationValueForEndState
{
    if (self.pedm.capability.color >= SOME && self.pedm.capability.temp >= SOME)
    {
        if (self.endSaturationSlider.value == 0)
        {
            self.endHueSlider.enabled = NO;
            self.endHueLabel.text = @"N/A";
            self.endHueButton.enabled = YES;
        }
        else
        {
            self.endHueSlider.enabled = YES;
            self.endHueButton.enabled = NO;
            unsigned int endHue = self.pedm.endState.hue;
            self.endHueLabel.text = [NSString stringWithFormat: @"%i°", endHue];
        }

        if (self.endSaturationSlider.value == 100)
        {
            self.endColorTempSlider.enabled = NO;
            self.endColorTempLabel.text = @"N/A";
            self.endColorTempButton.enabled = YES;
        }
        else
        {
            self.endColorTempSlider.enabled = YES;
            self.endColorTempButton.enabled = NO;
            self.endColorTempLabel.text = [NSString stringWithFormat: @"%iK", (uint32_t)self.endColorTempSlider.value];
        }
    }
}

-(void)showHueAlert
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                    message: @"Hue has no effect when saturation is zero. Set saturation to greater than zero to enable the hue slider."
                                                   delegate: nil
                                          cancelButtonTitle: @"OK"
                                          otherButtonTitles: nil];
    [alert show];
}

-(void)showColorTempAlert
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                    message: @"Color temperature has no effect when saturation is 100%. Set saturation to less than 100% to enable the color temperature slider."
                                                   delegate: nil
                                          cancelButtonTitle: @"OK"
                                          otherButtonTitles: nil];
    [alert show];
}

@end
