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

#import "LSFGroupsInfoTableViewController.h"
#import "LSFGroupsChangeNameViewController.h"
#import "LSFGroupsPresetsTableViewController.h"
#import "LSFGroupsMembersTableViewController.h"
#import "LSFUtilityFunctions.h"
#import <LSFSDKLightingDirector.h>
#import <LSFSDKCapabilityData.h>

@interface LSFGroupsInfoTableViewController ()

@property (nonatomic) BOOL isDimmable;
@property (nonatomic) BOOL hasColor;
@property (nonatomic) BOOL hasVariableColorTemp;
@property (nonatomic) long long timestamp;
@property (nonatomic) unsigned int delay;

-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification;
-(void)groupChangedNotificationReceived: (NSNotification *)notification;
-(void)groupRemovedNotificationReceived: (NSNotification *)notification;
-(void)reloadGroupWithID: (NSString *)groupID;
-(void)presetNotificationReceived: (NSNotification *)notification;
-(void)brightnessSliderTapped: (UIGestureRecognizer *)gr;
-(void)hueSliderTapped: (UIGestureRecognizer *)gr;
-(void)saturationSliderTapped: (UIGestureRecognizer *)gr;
-(void)colorTempSliderTapped: (UIGestureRecognizer *)gr;
-(void)showAlertDialog: (NSString *)text;

@end

@implementation LSFGroupsInfoTableViewController

@synthesize groupID = _groupID;
@synthesize nameLabel = _nameLabel;
@synthesize powerSwitch = _powerSwitch;
@synthesize presetButton = _presetButton;
@synthesize brightnessSlider = _brightnessSlider;
@synthesize brightnessLabel = _brightnessLabel;
@synthesize hueSlider = _hueSlider;
@synthesize hueLabel = _huePercentageLabel;
@synthesize saturationSlider = _saturationSlider;
@synthesize saturationLabel = _saturationLabel;
@synthesize colorTempSlider = _colorTempSlider;
@synthesize colorTempLabel = _colorTempLabel;
@synthesize isDimmable = _isDimmable;
@synthesize hasColor = _hasColor;
@synthesize hasVariableColorTemp = _hasVariableColorTemp;
@synthesize timestamp = _timestamp;
@synthesize delay = _delay;

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

    if (![[[LSFSDKLightingDirector getLightingDirector] leadController] connected])
    {
        [self.navigationController popToRootViewControllerAnimated: YES];
    }

    //Set notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(groupChangedNotificationReceived:) name: @"LSFGroupChangedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(groupRemovedNotificationReceived:) name: @"LSFGroupRemovedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(presetNotificationReceived:) name: @"LSFPresetChangedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(presetNotificationReceived:) name: @"LSFPresetRemovedNotification" object: nil];

    //Reload the table
    [self reloadGroupWithID: self.groupID];
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

-(void)groupChangedNotificationReceived:(NSNotification *)notification
{
    LSFSDKGroup *group = [notification.userInfo valueForKey: @"group"];

    if ([self.groupID isEqualToString: [group theID]])
    {
        [self reloadGroupWithID: [group theID]];
    }
}

-(void)groupRemovedNotificationReceived:(NSNotification *)notification
{
    LSFSDKGroup *group = [notification.userInfo valueForKey: @"group"];

    if ([self.groupID isEqualToString: [group theID]])
    {
        [self showGroupDeleted: group];
    }
}

-(void)presetNotificationReceived: (NSNotification *)notification
{
    //Reload the table
    [self reloadGroupWithID: self.groupID];
}

-(void)reloadGroupWithID: (NSString *)groupID
{
    UIColor *uniformPowerGreen = [[UIColor alloc] initWithRed: (CGFloat)(205.0 / 255.0) green: (CGFloat)(245.0 / 255) blue: (CGFloat)(78.0 / 255.0) alpha: 1.0];
    UIColor *midstatePowerOrange = [[UIColor alloc] initWithRed: (CGFloat)(249.0 / 255.0) green: (CGFloat)(233.0 / 255) blue: (CGFloat)(55.0 / 255.0) alpha: 1.0];

    LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: self.groupID];

    if (group == nil)
    {
        [self.navigationController popToRootViewControllerAnimated: NO];
    }

    self.nameLabel.text = [group name];
    self.powerSwitch.on = [group getPowerOn];

    if ([[group getUniformity] power])
    {
        self.powerSwitch.onTintColor = uniformPowerGreen;
    }
    else
    {
        self.powerSwitch.onTintColor = midstatePowerOrange;
    }

    if ([[group getCapabilities] dimmable] >= SOME)
    {
        if ([group getPowerOn] && [[group getColor] brightness] == 0)
        {
            dispatch_async([[[LSFSDKLightingDirector getLightingDirector] lightingManager] dispatchQueue], ^{
                [group setPowerOn: NO];
            });
        }

        self.brightnessSlider.enabled = YES;
        self.brightnessSlider.value = [[group getColor] brightness];
        self.brightnessLabel.text = [NSString stringWithFormat: @"%i%%", [[group getColor] brightness]];
        self.brightnessSliderButton.enabled = NO;
        self.isDimmable = YES;

        if ([[group getUniformity] brightness])
        {
            [self.brightnessSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
            [self.brightnessSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];
        }
        else
        {
            [self.brightnessSlider setThumbImage: [UIImage imageNamed: @"power_slider_midstate_icon.png"] forState: UIControlStateNormal];
            [self.brightnessSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];
        }

        if ([[group getCapabilities] dimmable] == SOME)
        {
            self.brightnessAsterisk.hidden = NO;
            [self performSelectorOnMainThread:@selector(updateNotSupportedLabel) withObject:nil waitUntilDone:NO];
        }
    }
    else
    {
        self.brightnessSlider.value = 0;
        self.brightnessSlider.enabled = NO;
        self.brightnessLabel.text = @"N/A";
        self.brightnessSliderButton.enabled = YES;
        self.isDimmable = NO;
        self.brightnessAsterisk.hidden = YES;
    }

    if ([[group getCapabilities] color] >= SOME)
    {
        if ([[group getColor] saturation] == 0)
        {
            self.hueSlider.value = [[group getColor] hue];
            self.hueSlider.enabled = NO;
            self.hueLabel.text = @"N/A";
            self.hueSliderButton.enabled = YES;
        }
        else
        {
            self.hueSlider.value = [[group getColor] hue];
            self.hueSlider.enabled = YES;
            self.hueLabel.text = [NSString stringWithFormat: @"%i°", [[group getColor] hue]];
            self.hueSliderButton.enabled = NO;
        }

        if ([[group getCapabilities] color] == SOME)
        {
            self.hueAsterisk.hidden = NO;
            self.saturationAsterisk.hidden = NO;
            [self performSelectorOnMainThread:@selector(updateNotSupportedLabel) withObject:nil waitUntilDone:NO];
        }

        self.saturationSlider.enabled = YES;
        self.saturationSlider.value = [[group getColor] saturation];
        self.saturationLabel.text = [NSString stringWithFormat: @"%i%%", [[group getColor] saturation]];
        self.saturationSliderButton.enabled = NO;
        self.hasColor = YES;

        if ([[group getUniformity] hue])
        {
            [self.hueSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
            [self.hueSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];
        }
        else
        {
            [self.hueSlider setThumbImage: [UIImage imageNamed: @"power_slider_midstate_icon.png"] forState: UIControlStateNormal];
            [self.hueSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];
        }

        if ([[group getUniformity] saturation])
        {
            [self.saturationSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
            [self.saturationSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];
        }
        else
        {
            [self.saturationSlider setThumbImage: [UIImage imageNamed: @"power_slider_midstate_icon.png"] forState: UIControlStateNormal];
            [self.saturationSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];
        }
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
        self.hueAsterisk.hidden = YES;
        self.saturationAsterisk.hidden = YES;
    }

    if ([[group getCapabilities] temp] >= SOME)
    {
        if ([[group getColor] saturation] == 100)
        {
            self.colorTempSlider.value = [[group getColor] colorTemp];
            self.colorTempSlider.enabled = NO;
            self.colorTempLabel.text = @"N/A";
            self.colorTempSliderButton.enabled = YES;
        }
        else
        {
            self.colorTempSlider.value = [[group getColor] colorTemp];
            self.colorTempSlider.enabled = YES;
            self.colorTempLabel.text = [NSString stringWithFormat: @"%iK", [[group getColor] colorTemp]];
            self.colorTempSliderButton.enabled = NO;
        }

        if ([[group getCapabilities] temp])
        {
            [self.colorTempSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
            [self.colorTempSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];
        }
        else
        {
            [self.colorTempSlider setThumbImage: [UIImage imageNamed: @"power_slider_midstate_icon.png"] forState: UIControlStateNormal];
            [self.colorTempSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];
        }

        if ([[group getCapabilities] temp] == SOME)
        {
            self.colorTempAsterisk.hidden = NO;
            [self performSelectorOnMainThread:@selector(updateNotSupportedLabel) withObject:nil waitUntilDone:NO];
        }

        self.colorTempSlider.minimumValue = [group colorTempMin];
        self.colorTempSlider.maximumValue = [group colorTempMax];
        self.hasVariableColorTemp = YES;
    }
    else
    {
        self.colorTempSlider.value = 0;
        self.colorTempSlider.enabled = NO;
        self.colorTempLabel.text = @"N/A";
        self.colorTempSliderButton.enabled = YES;
        self.hasVariableColorTemp = NO;
        self.colorTempAsterisk.hidden = YES;
    }

    self.presetButton.enabled = YES;

    NSMutableArray *presetsArray = [[NSMutableArray alloc] init];
    BOOL presetMatched = NO;

    for (LSFSDKPreset *preset in [[LSFSDKLightingDirector getLightingDirector] presets])
    {
        if (![preset.name hasPrefix: PRESET_NAME_PREFIX])
        {
            BOOL matchesPreset = [self checkIfGroup: group matchesPreset: preset];

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

    [LSFUtilityFunctions colorIndicatorSetup: self.colorIndicatorImage withColor: [group getColor] andCapabilityData: [group getCapabilities]];
}

-(void)showGroupDeleted: (LSFSDKGroup *)group
{
    [self dismissViewControllerAnimated: YES completion: nil];

    dispatch_async(dispatch_get_main_queue(), ^{
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Group Not Found"
                                                        message: [NSString stringWithFormat: @"The group \"%@\" no longer exists.", [group name]]
                                                       delegate: nil
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];
    });
}

/*
 * Various Event Handlers
 */
-(IBAction)powerSwitchPressed: (UISwitch *)sender
{

    dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{

        LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: self.groupID];
        LSFSDKColor *color = [group getColor];
        if (sender.isOn && self.isDimmable && [color brightness] == 0)
        {
            [group setBrightness: 25];
        }

        [group setPowerOn: sender.isOn];
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

-(IBAction)brightnessSliderTouchedWhileDisabled: (UIButton *)sender
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                    message: @"This group is not able to change its brightness."
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

-(IBAction)hueSliderTouchUpInside:(id)sender
{
    [self updateHueValue: sender];
}

-(IBAction)hueSliderTouchUpOutside:(id)sender
{
    [self updateHueValue: sender];
}

-(IBAction)hueSliderTouchedWhileDisabled: (UIButton *)sender
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
                                                        message: @"This group is not able to change its hue."
                                                       delegate: nil
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];
    }
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

-(IBAction)saturationSliderTouchedWhileDisabled: (UIButton *)sender
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                    message: @"This group is not able to change its saturation."
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

-(IBAction)colorSliderTouchUpInside:(id)sender
{
    [self updateColorValue: sender];
}

-(IBAction)colorSliderTouchUpOutside:(id)sender
{
    [self updateColorValue: sender];
}

-(IBAction)colorTempSliderTouchedWhileDisabled: (UIButton *)sender
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
                                                        message: @"This group is not able to change its color temperature."
                                                       delegate: nil
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];
    }
}

/*
 * Segue method
 */
-(BOOL)shouldPerformSegueWithIdentifier: (NSString *)identifier sender: (id)sender
{
    LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: self.groupID];

    if ([identifier isEqualToString: @"ChangeGroupName"])
    {
        if ([group isAllLampsGroup])
        {
            UITableViewCell *cell = (UITableViewCell *)sender;
            cell.selectionStyle = UITableViewCellSelectionStyleNone;
            cell.selectionStyle = UITableViewCellSelectionStyleBlue;

            [self showAlertDialog: @"name"];
            return NO;
        }
        else
        {
            return YES;
        }
    }
    else if ([identifier isEqualToString: @"ChangeGroupMembers"])
    {
        if ([group isAllLampsGroup])
        {
            UITableViewCell *cell = (UITableViewCell *)sender;
            cell.selectionStyle = UITableViewCellSelectionStyleNone;
            cell.selectionStyle = UITableViewCellSelectionStyleBlue;

            [self showAlertDialog: @"members"];
            return NO;
        }
        else
        {
            return YES;
        }
    }
    else
    {
        return YES;
    }
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier isEqualToString: @"ChangeGroupName"])
    {
        LSFGroupsChangeNameViewController *gcnvc = [segue destinationViewController];
        gcnvc.groupID = self.groupID;
    }
    else if ([segue.identifier isEqualToString: @"GroupPresets"])
    {
        LSFGroupsPresetsTableViewController *gptvc = [segue destinationViewController];
        gptvc.groupID = self.groupID;
    }
    else if ([segue.identifier isEqualToString: @"ChangeGroupMembers"])
    {
        UINavigationController *nc = (UINavigationController *)[segue destinationViewController];
        LSFGroupsMembersTableViewController *gmtvc = (LSFGroupsMembersTableViewController *)nc.topViewController;
        gmtvc.groupID = [NSString stringWithString: self.groupID];
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
        LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: self.groupID];

        [group setBrightness: (uint32_t)value];

        if ([[group getColor] brightness] == 0)
        {
            [group setPowerOn: YES];
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
        LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: self.groupID];
        [group setHue: (uint32_t)value];
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
        LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: self.groupID];
        [group setSaturation: (uint32_t)value];
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
        LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: self.groupID];
        [group setColorTemp: (uint32_t)value];
    });
}

-(BOOL)checkIfGroup: (LSFSDKGroup *) group matchesPreset: (LSFSDKPreset *) preset
{
    BOOL returnValue = NO;

    LSFSDKColor *groupColor = [group getColor];
    LSFSDKColor *presetColor = [preset getColor];

    if ([group getPowerOn] == [preset getPowerOn] && [groupColor hue] == [presetColor hue] &&
        [groupColor saturation] == [presetColor saturation] && [groupColor brightness] == [presetColor brightness] &&
        [groupColor colorTemp] == [presetColor colorTemp])
    {
        returnValue = YES;
    }

    return returnValue;
}

-(void)showAlertDialog: (NSString *)text
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                    message: [NSString stringWithFormat: @"Cannot change the %@ of the \"All Lamps\" group", text]
                                                   delegate: nil
                                          cancelButtonTitle: @"OK"
                                          otherButtonTitles: nil];
    [alert show];
}

-(void)updateBrightnessValue:(id)sender
{
    dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
        LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: self.groupID];
        [group setBrightness: (uint32_t)((UISlider *)sender).value];

        if ([[group getColor] brightness] == 0)
        {
            [group setPowerOn: YES];
        }
    });
}

-(void)updateHueValue:(id)sender
{
    dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
        LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: self.groupID];
        [group setHue: (uint32_t)((UISlider *)sender).value];
    });
}

-(void)updateSaturationValue:(id)sender
{
    dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
        LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: self.groupID];
        [group setSaturation: (uint32_t)((UISlider *)sender).value];
    });
}

-(void)updateColorValue:(id)sender
{
    dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
        LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: self.groupID];
        [group setColorTemp: (uint32_t)((UISlider *)sender).value];
    });
}

-(void)updateNotSupportedLabel
{
    [self.tableView footerViewForSection:1].textLabel.text = @"* Not supported by some lamps in this group";
}

@end
