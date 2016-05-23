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

#import "LSFLightInfoTableViewController.h"
#import "LSFLightDetailsTableViewController.h"
#import "LSFLightsPresetsTableViewController.h"
#import "LSFLightsChangeNameViewController.h"
#import "LSFUtilityFunctions.h"
#import <LSFSDKLightingDirector.h>

@interface LSFLightInfoTableViewController ()

@property (nonatomic) BOOL isDimmable;
@property (nonatomic) BOOL hasColor;
@property (nonatomic) BOOL hasVariableColorTemp;

-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification;
-(void)lampChangedNotificationReceived: (NSNotification *)notification;
-(void)lampRemovedNotificationReceived: (NSNotification *)notification;
-(void)reloadLampWithID: (NSString *)lampID;
-(void)deleteLampWithID: (NSString *)lampID andName: (NSString *)lampName;
-(void)presetNotificationReceived: (NSNotification *)notification;
-(BOOL)checkIfLamp: (LSFSDKLamp *) lamp matchesPreset: (LSFSDKPreset *) preset;
-(void)brightnessSliderTapped: (UIGestureRecognizer *)gr;
-(void)hueSliderTapped: (UIGestureRecognizer *)gr;
-(void)saturationSliderTapped: (UIGestureRecognizer *)gr;
-(void)colorTempSliderTapped: (UIGestureRecognizer *)gr;

@end

@implementation LSFLightInfoTableViewController

@synthesize lampID = _lampID;
@synthesize nameLabel = _nameLabel;
@synthesize powerSwitch = _powerSwitch;
@synthesize presetButton = _presetButton;
@synthesize brightnessSlider = _brightnessSlider;
@synthesize brightnessSliderButton = _brightnessSliderButton;
@synthesize brightnessLabel = _brightnessLabel;
@synthesize hueSlider = _hueSlider;
@synthesize hueSliderButton = _hueSliderButton;
@synthesize hueLabel = _huePercentageLabel;
@synthesize saturationSlider = _saturationSlider;
@synthesize saturationSliderButton = _saturationSliderButton;
@synthesize saturationLabel = _saturationLabel;
@synthesize colorTempSlider = _colorTempSlider;
@synthesize colorTempSliderButton = _colorTempSliderButton;
@synthesize colorTempLabel = _colorTempLabel;
@synthesize lumensLabel = _lumensLabel;
@synthesize energyUsageLabel = _energyUsageLabel;
@synthesize isDimmable = _isDimmable;
@synthesize hasColor = _hasColor;
@synthesize hasVariableColorTemp = _hasVariableColorTemp;

-(void)viewDidLoad
{
    [super viewDidLoad];
    
    UITapGestureRecognizer *brightnessTGR = [[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(brightnessSliderTapped:)];
    [self.brightnessSlider addGestureRecognizer: brightnessTGR];
    [self.brightnessSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
    [self.brightnessSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];

    UITapGestureRecognizer *hueTGR = [[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(hueSliderTapped:)];
    [self.hueSlider addGestureRecognizer: hueTGR];
    [self.hueSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
    [self.hueSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];

    UITapGestureRecognizer *saturationTGR = [[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(saturationSliderTapped:)];
    [self.saturationSlider addGestureRecognizer: saturationTGR];
    [self.saturationSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
    [self.saturationSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];

    UITapGestureRecognizer *colorTempTGR = [[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(colorTempSliderTapped:)];
    [self.colorTempSlider addGestureRecognizer: colorTempTGR];
    [self.colorTempSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
    [self.colorTempSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];

    self.colorIndicatorImage.layer.rasterizationScale = [UIScreen mainScreen].scale;
    self.colorIndicatorImage.layer.shouldRasterize = YES;
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    //Set notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(lampChangedNotificationReceived:) name: @"LSFLampChangedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(lampRemovedNotificationReceived:) name: @"LSFLampRemovedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(presetNotificationReceived:) name: @"LSFPresetChangedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(presetNotificationReceived:) name: @"LSFPresetRemovedNotification" object: nil];
    
    //Reload the table
    [self reloadLampWithID: self.lampID];
}

-(void)viewWillDisappear: (BOOL)animated
{
    [super viewWillDisappear: animated];

    //Clear notification handler
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

-(void)lampChangedNotificationReceived: (NSNotification *)notification
{
    NSString *lampID = [[notification.userInfo valueForKey: @"lamp"] theID];

    if ([lampID isEqualToString: self.lampID])
    {
        [self reloadLampWithID: lampID];
    }
}

-(void)lampRemovedNotificationReceived: (NSNotification *)notification
{
    LSFSDKLamp *lamp = [notification.userInfo valueForKey: @"lamp"];
    [self deleteLampWithID: [lamp theID] andName: [lamp name]];
}

-(void)presetNotificationReceived: (NSNotification *)notification
{
    //Reload the table
    [self reloadLampWithID: self.lampID];
}

-(void)reloadLampWithID: (NSString *)lampID
{
    LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID: lampID];

    self.nameLabel.text = [lamp name];
    self.powerSwitch.on = [lamp getPowerOn];

    if ([[lamp details] dimmable])
    {
        if ([lamp getPowerOn] && [[lamp getColor] brightness] == 0)
        {
            dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
                [lamp setPowerOn: NO];
            });
        }

        self.brightnessSlider.enabled = YES;
        self.brightnessSlider.value = [[lamp getColor] brightness];
        self.brightnessLabel.text = [NSString stringWithFormat: @"%i%%", [[lamp getColor] brightness]];
        self.brightnessSliderButton.enabled = NO;
        self.isDimmable = YES;
    }
    else
    {
        self.brightnessSlider.value = 0;
        self.brightnessSlider.enabled = NO;
        self.brightnessLabel.text = @"N/A";
        self.brightnessSliderButton.enabled = YES;
        self.isDimmable = NO;
    }

    if ([[lamp details] color])
    {
        if ([[lamp getColor] saturation] == 0)
        {
            self.hueSlider.value = [[lamp getColor] hue];
            self.hueSlider.enabled = NO;
            self.hueLabel.text = @"N/A";
            self.hueSliderButton.enabled = YES;
        }
        else
        {
            self.hueSlider.value = [[lamp getColor] hue];
            self.hueSlider.enabled = YES;
            self.hueLabel.text = [NSString stringWithFormat: @"%i°", [[lamp getColor] hue]];
            self.hueSliderButton.enabled = NO;
        }

        self.saturationSlider.enabled = YES;
        self.saturationSlider.value = [[lamp getColor] saturation];
        self.saturationLabel.text = [NSString stringWithFormat: @"%i%%", [[lamp getColor] saturation]];
        self.saturationSliderButton.enabled = NO;
        self.hasColor = YES;
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

        self.hasColor = NO;
    }

    if ([[lamp details] variableColorTemp])
    {
        if ([[lamp getColor] saturation] == 100)
        {
            self.colorTempSlider.value = [[lamp getColor] colorTemp];
            self.colorTempSlider.enabled = NO;
            self.colorTempLabel.text = @"N/A";
            self.colorTempSliderButton.enabled = YES;
        }
        else
        {
            self.colorTempSlider.value = [[lamp getColor] colorTemp];
            self.colorTempSlider.enabled = YES;
            self.colorTempLabel.text = [NSString stringWithFormat: @"%iK", [[lamp getColor] colorTemp]];
            self.colorTempSliderButton.enabled = NO;
        }

        self.colorTempSlider.minimumValue = [[lamp details] minTemperature];
        self.colorTempSlider.maximumValue = [[lamp details] maxTemperature];
        self.hasVariableColorTemp = YES;
    }
    else
    {
        self.colorTempSlider.value = 0;
        self.colorTempSlider.enabled = NO;
        self.colorTempLabel.text = @"N/A";
        self.colorTempSliderButton.enabled = YES;
        self.hasVariableColorTemp = NO;
    }

    self.presetButton.enabled = YES;

    NSArray *presets = [[LSFSDKLightingDirector getLightingDirector] presets];

    NSMutableArray *presetsArray = [[NSMutableArray alloc] init];
    BOOL presetMatched = NO;
    for (LSFSDKPreset *preset in presets)
    {
        if (![preset.name hasPrefix: PRESET_NAME_PREFIX])
        {
            BOOL matchesPreset = [self checkIfLamp: lamp matchesPreset: preset];

            if (matchesPreset)
            {
                [presetsArray addObject: [preset name]];
                presetMatched = YES;
            }
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
        [self.presetButton setTitle: presetsMatched forState: UIControlStateNormal];
    }
    else
    {
        [self.presetButton setTitle: @"Save New Preset" forState: UIControlStateNormal];
    }

    self.lumensLabel.text = [NSString stringWithFormat: @"%i", [[lamp parameters] lumens]];
    self.energyUsageLabel.text = [NSString stringWithFormat: @"%i mW", [[lamp parameters] energyUsageMilliwatts]];

    [LSFUtilityFunctions colorIndicatorSetup: self.colorIndicatorImage withColor: [lamp getColor] andCapabilityData: [lamp getCapabilities]];
}

-(void)deleteLampWithID: (NSString *)lampID andName: (NSString *)lampName
{
    if ([self.lampID isEqualToString: lampID])
    {
        [self.navigationController popToRootViewControllerAnimated: YES];

        dispatch_async(dispatch_get_main_queue(), ^{
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Connection Lost"
                                                            message: [NSString stringWithFormat: @"Unable to connect to \"%@\".", lampName]
                                                           delegate: nil
                                                  cancelButtonTitle: @"OK"
                                                  otherButtonTitles: nil];
            [alert show];
        });
    }
}

/*
 * Various event handlers
 */
-(IBAction)powerSwitchPressed: (UISwitch *)sender
{
    dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
        LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID: self.lampID];
        if (sender.isOn && self.isDimmable && [[lamp getColor] brightness] == 0)
        {
            LSFSDKColor *color = [lamp getColor];
            [color setBrightness: 25];
            [lamp setColor: color];
        }

        [lamp setPowerOn: sender.isOn];
    });
}

-(IBAction)brightnessSliderValueChanged: (UISlider *)sender
{
    NSString *brightnessText = [NSString stringWithFormat: @"%i%%", (uint32_t)sender.value];
    self.brightnessLabel.text = brightnessText;
}

-(IBAction)brightnessSliderTouchUpInside:(id)sender
{
    [self updateBrightnessValue: sender];
}

-(IBAction)brightnessSliderTouchUpOutside:(id)sender
{
    [self updateBrightnessValue: sender];
}

-(IBAction)hueSliderValueChanged: (UISlider *)sender
{
    NSString *hueText = [NSString stringWithFormat: @"%i°", (uint32_t)sender.value];
    self.hueLabel.text = hueText;
}

-(IBAction)hueSliderTouchUpInside:(id)sender
{
    [self updateHueValue: sender];
}

-(IBAction)hueSliderTouchUpOutside:(id)sender
{
    [self updateHueValue: sender];
}

-(IBAction)saturationSliderValueChanged: (UISlider *)sender
{
    NSString *saturationText = [NSString stringWithFormat: @"%i%%", (uint32_t)sender.value];
    self.saturationLabel.text = saturationText;
}

-(IBAction)saturationSliderTouchUpInside:(id)sender
{
    [self updateSaturationValue:sender];
}

-(IBAction)saturationSliderTouchUpOutside:(id)sender
{
    [self updateSaturationValue:sender];
}

-(IBAction)colorTempSliderValueChanged: (UISlider *)sender
{
    NSString *colorTempText = [NSString stringWithFormat: @"%iK", (uint32_t)sender.value];
    self.colorTempLabel.text = colorTempText;
}

-(IBAction)colorSliderTouchUpInside:(id)sender
{
    [self updateColorValue: sender];
}

-(IBAction)colorSliderTouchUpOutside:(id)sender
{
    [self updateColorValue: sender];
}

/*
 * Segue method
 */
-(void)prepareForSegue: (UIStoryboardSegue *)segue sender: (id)sender
{
    if ([segue.identifier isEqualToString: @"LampDetails"])
    {
        LSFLightDetailsTableViewController *ldtvc = [segue destinationViewController];
        ldtvc.lampID = self.lampID;
    }
    else if ([segue.identifier isEqualToString: @"ChangeLightName"])
    {
        LSFLightsChangeNameViewController *clnvc = [segue destinationViewController];
        clnvc.lampID = self.lampID;
    }
    else if ([segue.identifier isEqualToString: @"LampPresets"])
    {
        LSFLightsPresetsTableViewController *lptvc = [segue destinationViewController];
        lptvc.lampID = self.lampID;
    }
}

/*
 * Private functions
 */
-(void)brightnessSliderTapped: (UIGestureRecognizer *)gr
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
    
    dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
        LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID: self.lampID];
        LSFSDKColor *color = [lamp getColor];
        color.brightness = (uint32_t)value;
        [lamp setColor: color];

        if ([[lamp getColor] brightness] == 0)
        {
            [lamp setPowerOn: YES];
        }
    });
}

-(void)hueSliderTapped: (UIGestureRecognizer *)gr
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
    
    dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
        LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID: self.lampID];
        LSFSDKColor *color = [lamp getColor];
        color.hue = (uint32_t)value;
        [lamp setColor: color];
    });
}

-(void)saturationSliderTapped: (UIGestureRecognizer *)gr
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

    dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
        LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID: self.lampID];
        LSFSDKColor *color = [lamp getColor];
        color.saturation = (uint32_t)value;
        [lamp setColor: color];
    });
}

-(void)colorTempSliderTapped: (UIGestureRecognizer *)gr
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

    dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
        LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID: self.lampID];
        LSFSDKColor *color = [lamp getColor];
        color.colorTemp = (uint32_t)value;
        [lamp setColor: color];
    });
}

-(BOOL)checkIfLamp: (LSFSDKLamp *) lamp matchesPreset: (LSFSDKPreset *) preset
{
    BOOL returnValue = NO;

    LSFSDKColor *lampColor = [lamp getColor];
    LSFSDKColor *presetColor = [preset getColor];

    if ([lamp getPowerOn] == [preset getPowerOn] && [lampColor hue] == [presetColor hue] &&
        [lampColor saturation] == [presetColor saturation] && [lampColor brightness] == [presetColor brightness] &&
        [lampColor colorTemp] == [presetColor colorTemp])
    {
        returnValue = YES;
    }

    return returnValue;
}

-(void)updateBrightnessValue:(id)sender
{
    dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
        LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID: self.lampID];
        LSFSDKColor *color = [lamp getColor];
        color.brightness = (uint32_t)((UISlider *)sender).value;
        [lamp setColor: color];

        if ([[lamp getColor] brightness] == 0)
        {
            [lamp setPowerOn: YES];
        }
    });
}

-(void)updateHueValue:(id)sender
{
    dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
        LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID: self.lampID];

        LSFSDKColor *color = [lamp getColor];
        color.hue = (uint32_t)((UISlider *)sender).value;

        [lamp setColor: color];
    });
}

-(void)updateSaturationValue:(id)sender
{
    dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
        LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID: self.lampID];

        LSFSDKColor *color = [lamp getColor];
        color.saturation = (uint32_t)((UISlider *)sender).value;

        [lamp setColor: color];
    });
}

-(void)updateColorValue:(id)sender
{
    dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
        LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID: self.lampID];

        LSFSDKColor *color = [lamp getColor];
        color.colorTemp = (uint32_t)((UISlider *)sender).value;

        [lamp setColor: color];
    });
}

/*
 * Button event handlers
 */
-(IBAction)brightnessSliderTouchedWhileDisabled: (UIButton *)sender;
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                    message: @"This Lamp is not able to change its brightness."
                                                   delegate: nil
                                          cancelButtonTitle: @"OK"
                                          otherButtonTitles: nil];
    [alert show];
}

-(IBAction)hueSliderTouchedWhileDisabled: (UIButton *)sender;
{
    if (self.hasColor)
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                        message: @"Hue has no effect when saturation is zero. Set saturation to greater than zero to enable the hue slider."
                                                       delegate: nil
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];
    }
    else
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                        message: @"This Lamp is not able to change its hue."
                                                       delegate: nil
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];
    }
}

-(IBAction)saturationSliderTouchedWhileDisabled: (UIButton *)sender;
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                    message: @"This Lamp is not able to change its saturation."
                                                   delegate: nil
                                          cancelButtonTitle: @"OK"
                                          otherButtonTitles: nil];
    [alert show];
}

-(IBAction)colorTempSliderTouchedWhileDisabled: (UIButton *)sender;
{
    if (self.hasVariableColorTemp)
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                        message: @"Color temperature has no effect when saturation is 100%. Set saturation to less than 100% to enable the color temperature slider."
                                                       delegate: nil
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];
    }
    else
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                        message: @"This Lamp is not able to change its color temperature."
                                                       delegate: nil
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];
    }
}

@end
