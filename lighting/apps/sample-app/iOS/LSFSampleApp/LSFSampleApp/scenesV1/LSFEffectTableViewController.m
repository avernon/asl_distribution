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

#import "LSFEffectTableViewController.h"
#import "LSFUtilityFunctions.h"
#import <LSFSDKLightingDirector.h>

@interface LSFEffectTableViewController ()

@property (nonatomic) BOOL isDimmable;
@property (nonatomic) BOOL hasColor;
@property (nonatomic) BOOL hasVariableColorTemp;

-(void)presetNotificationReceived: (NSNotification *)notification;
-(void)brightnessSliderTapped: (UIGestureRecognizer *)gr;
-(void)hueSliderTapped: (UIGestureRecognizer *)gr;
-(void)saturationSliderTapped: (UIGestureRecognizer *)gr;
-(void)colorTempSliderTapped: (UIGestureRecognizer *)gr;

@end

@implementation LSFEffectTableViewController

@synthesize presetButton = _presetButton;
@synthesize brightnessSlider = _brightnessSlider;
@synthesize brightnessSliderButton = _brightnessSliderButton;
@synthesize brightnessLabel = _brightnessLabel;
@synthesize hueSlider = _hueSlider;
@synthesize hueSliderButton = _hueSliderButton;
@synthesize hueLabel = _hueLabel;
@synthesize saturationSlider = _saturationSlider;
@synthesize saturationSliderButton = _saturationSliderButton;
@synthesize saturationLabel = _saturationLabel;
@synthesize colorTempSlider = _colorTempSlider;
@synthesize colorTempSliderButton = _colorTempSliderButton;
@synthesize colorTempLabel = _colorTempLabel;
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

    [self updateColorIndicator];
    [self updatePresetButtonTitle: self.presetButton];
    [self checkSaturationValue];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    //Set presets notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(presetNotificationReceived:) name: @"LSFPresetChangedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(presetNotificationReceived:) name: @"LSFPresetRemovedNotification" object: nil];
}

-(void)viewWillDisappear: (BOOL)animated
{
    [super viewWillDisappear: animated];

    //Clear groups notification handler
    [[NSNotificationCenter defaultCenter] removeObserver: self];
}

-(void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

/*
 * Notification Handler
 */
-(void)presetNotificationReceived: (NSNotification *)notification
{
    [self updatePresetButtonTitle: self.presetButton];
}

/*
 * Various event handlers
 */
-(IBAction)brightnessSliderValueChanged: (UISlider *)sender
{
    NSString *brightnessText = [NSString stringWithFormat: @"%i%%", (uint32_t)sender.value];
    self.brightnessLabel.text = brightnessText;
}

-(IBAction)brightnessSliderTouchUpInside:(UISlider *)sender
{
    [self updateColorIndicator];
    [self updatePresetButtonTitle: self.presetButton];
}

-(IBAction)brightnessSliderTouchUpOutside:(UISlider *)sender
{
    [self updateColorIndicator];
    [self updatePresetButtonTitle: self.presetButton];
}

-(IBAction)brightnessSliderTouchedWhileDisabled: (UIButton *)sender
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                    message: @"This Lamp is not able to change its brightness."
                                                   delegate: nil
                                          cancelButtonTitle: @"OK"
                                          otherButtonTitles: nil];
    [alert show];
}

-(IBAction)hueSliderValueChanged: (UISlider *)sender
{
    NSString *hueText = [NSString stringWithFormat: @"%i°", (uint32_t)sender.value];
    self.hueLabel.text = hueText;
}

-(IBAction)hueSliderTouchUpInside:(UISlider *)sender
{
    [self updateColorIndicator];
    [self updatePresetButtonTitle: self.presetButton];
}

-(IBAction)hueSliderTouchUpOutside:(UISlider *)sender
{
    [self updateColorIndicator];
    [self updatePresetButtonTitle: self.presetButton];
}

-(IBAction)hueSliderTouchedWhileDisabled: (UIButton *)sender
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                    message: @"Hue has no effect when saturation is zero. Set saturation to greater than zero to enable the hue slider."
                                                   delegate: nil
                                          cancelButtonTitle: @"OK"
                                          otherButtonTitles: nil];
    [alert show];
}

-(IBAction)saturationSliderValueChanged: (UISlider *)sender
{
    NSString *saturationText = [NSString stringWithFormat: @"%i%%", (uint32_t)sender.value];
    self.saturationLabel.text = saturationText;
    [self checkSaturationValue];
}

-(IBAction)saturationSliderTouchUpInside:(UISlider *)sender
{
    [self updateColorIndicator];
    [self updatePresetButtonTitle: self.presetButton];
    [self checkSaturationValue];
}

-(IBAction)saturationSliderTouchUpOutside:(UISlider *)sender
{
    [self updateColorIndicator];
    [self updatePresetButtonTitle: self.presetButton];
    [self checkSaturationValue];
}

-(IBAction)saturationSliderTouchedWhileDisabled: (UIButton *)sender
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                    message: @"This Lamp is not able to change its saturation."
                                                   delegate: nil
                                          cancelButtonTitle: @"OK"
                                          otherButtonTitles: nil];
    [alert show];
}

-(IBAction)colorTempSliderValueChanged: (UISlider *)sender
{
    NSString *colorTempText = [NSString stringWithFormat: @"%iK", (uint32_t)sender.value];
    self.colorTempLabel.text = colorTempText;
}

-(IBAction)colorTempSliderTouchUpInside:(UISlider *)sender
{
    [self updateColorIndicator];
    [self updatePresetButtonTitle: self.presetButton];
}

-(IBAction)colorTempSliderTouchUpOutside:(UISlider *)sender
{
    [self updateColorIndicator];
    [self updatePresetButtonTitle: self.presetButton];
}

-(IBAction)colorTempSliderTouchedWhileDisabled: (UIButton *)sender
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                    message: @"Color temperature has no effect when saturation is 100%. Set saturation to less than 100% to enable the color temperature slider."
                                                   delegate: nil
                                          cancelButtonTitle: @"OK"
                                          otherButtonTitles: nil];
    [alert show];
}

/*
 * Private functions
 */
-(void)updateColorIndicator
{
    // Function should be overriden by subclass
}

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

    NSString *brightnessText = [NSString stringWithFormat: @"%i%%", (uint32_t)value];
    self.brightnessLabel.text = brightnessText;
    self.brightnessSlider.value = value;

    [self updateColorIndicator];
    [self updatePresetButtonTitle: self.presetButton];
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

    NSString *hueText = [NSString stringWithFormat: @"%i°", (uint32_t)value];
    self.hueLabel.text = hueText;
    self.hueSlider.value = value;

    [self updateColorIndicator];
    [self updatePresetButtonTitle: self.presetButton];
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

    NSString *saturationText = [NSString stringWithFormat: @"%i%%", (uint32_t)value];
    self.saturationLabel.text = saturationText;
    self.saturationSlider.value = value;

    [self updateColorIndicator];
    [self updatePresetButtonTitle: self.presetButton];
    [self checkSaturationValue];
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

    NSString *colorTempText = [NSString stringWithFormat: @"%iK", (uint32_t)value];
    self.colorTempLabel.text = colorTempText;
    self.colorTempSlider.value = value;

    [self updateColorIndicator];
    [self updatePresetButtonTitle: self.presetButton];
}

-(void)updatePresetButtonTitle: (UIButton*)presetButton
{
    unsigned int brightness = (uint32_t)self.brightnessSlider.value;
    unsigned int hue = (uint32_t)self.hueSlider.value;
    unsigned int saturation = (uint32_t)self.saturationSlider.value;
    unsigned int colorTemp = (uint32_t)self.colorTempSlider.value;
    LSFSDKColor *color = [[LSFSDKColor alloc] initWithHue: hue saturation: saturation brightness: brightness colorTemp: colorTemp];

    NSMutableArray *presetsArray = [[NSMutableArray alloc] init];
    BOOL presetMatched = NO;
    for (LSFSDKPreset *preset in [[LSFSDKLightingDirector getLightingDirector] presets])
    {
        BOOL matchesPreset = [self checkIfPreset: preset matchesPower: (brightness == 0 ? ON : OFF) andColor: color];

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
        [self.presetButton setTitle: presetsMatched forState: UIControlStateNormal];
    }
    else
    {
        [self.presetButton setTitle: @"Save New Preset" forState: UIControlStateNormal];
    }
}
-(BOOL)checkIfPreset: (LSFSDKPreset *)preset matchesPower: (Power)power andColor: (LSFSDKColor *) color
{
    BOOL returnValue = NO;

    LSFSDKColor *presetColor = [preset getColor];

    if (power == [preset getPower] && [color hue] == [presetColor hue] &&
        [color saturation] == [presetColor saturation] && [color brightness] == [presetColor brightness] &&
        [color colorTemp] == [presetColor colorTemp])
    {
        returnValue = YES;
    }

    return returnValue;
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

-(NSString *)buildSectionTitleString: (LSFSceneElementDataModel *)sceneElement
{
    BOOL firstElementFound = NO;
    NSMutableString *titleString = [[NSMutableString alloc] initWithString: @""];

    for (int i = 0; !firstElementFound && i < sceneElement.members.lampGroups.count; i++)
    {
        NSString *lampGroupID = [sceneElement.members.lampGroups objectAtIndex: i];
        LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: lampGroupID];

        if (group != nil)
        {
            [titleString appendFormat: @"\"%@\"", group.name];
            firstElementFound = YES;
        }
    }

    for (int i = 0; !firstElementFound && i < sceneElement.members.lamps.count; i++)
    {
        NSString *lampID = [sceneElement.members.lamps objectAtIndex: i];
        LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID: lampID];

        if (lamp != nil)
        {
            [titleString appendFormat: @"\"%@\"", lamp.name];
            firstElementFound = YES;
        }
    }

    unsigned int remainingSceneMembers = (unsigned int)(sceneElement.members.lamps.count + sceneElement.members.lampGroups.count - 1);

    if (remainingSceneMembers > 0)
    {
        [titleString appendFormat: @" (and %u more)", remainingSceneMembers];
    }

    return [NSString stringWithString: titleString];
}

@end
