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

#import "LSFNoEffectTableViewController.h"
#import "LSFScenesPresetsTableViewController.h"
#import "LSFUtilityFunctions.h"
#import <LSFSDKLightingDirector.h>
#import <model/LSFConstants.h>

@interface LSFNoEffectTableViewController()

-(void)leaderModelChangedNotificationReceived: (NSNotification *)notification;
-(void)sceneRemovedNotificationReceived: (NSNotification *)notification;
-(void) alertSceneDeleted: (LSFSDKScene *)scene;

@end

@implementation LSFNoEffectTableViewController

@synthesize sceneModel = _sceneModel;
@synthesize nedm = _nedm;
@synthesize shouldUpdateSceneAndDismiss = _shouldUpdateSceneAndDismiss;

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    //Set notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(sceneRemovedNotificationReceived:) name: @"LSFSceneRemovedNotification" object: nil];

    NSLog(@"LSFNoEffectTableViewController - viewWillAppear() executing");
    NSLog(@"Power = %@", self.nedm.state.onOff ? @"On" : @"Off");
    NSLog(@"Brightness = %u", self.nedm.state.brightness);
    NSLog(@"Hue = %u", self.nedm.state.hue);
    NSLog(@"Saturation = %u", self.nedm.state.saturation);
    NSLog(@"Color Temp = %u", self.nedm.state.colorTemp);
    NSLog(@"Capability = [%@, %@, %@]", self.nedm.capability.dimmable ? @"Dimmable" : @"Not Dimmable", self.nedm.capability.color ? @"Color" : @"No Color", self.nedm.capability.temp ? @"Variable Color Temp" : @"No Variable Color Temp");
    NSLog(@"Color Temp Min = %u", self.nedm.colorTempMin);
    NSLog(@"Color Temp Max = %u", self.nedm.colorTempMax);

    if (self.nedm != nil)
    {
        if (self.nedm.capability.dimmable >= SOME)
        {
            unsigned int brightness = self.nedm.state.brightness;
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

        if (self.nedm.capability.color >= SOME)
        {
            unsigned int hue = self.nedm.state.hue;
            self.hueSlider.value = hue;

            if (self.nedm.state.saturation == 0)
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

            unsigned int saturation = self.nedm.state.saturation;
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

        self.colorTempSlider.minimumValue = self.nedm.colorTempMin;
        self.colorTempSlider.maximumValue = self.nedm.colorTempMax;
        self.colorTempSlider.value = self.nedm.colorTempMin;

        if (self.nedm.capability.temp >= SOME)
        {
            if (self.nedm.state.saturation == 100)
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
    }

    LSFSDKColor *lcolor = [[LSFSDKColor alloc] initWithHue: self.hueSlider.value saturation: self.saturationSlider.value brightness: self.brightnessSlider.value colorTemp: self.colorTempSlider.value];

    [LSFUtilityFunctions colorIndicatorSetup: self.colorIndicatorImage withColor: lcolor andCapabilityData: [[LSFSDKCapabilityData alloc] initWithCapabilityData: self.nedm.capability]];

    [self presetButtonSetup: self.nedm];
}

-(void)viewWillDisappear: (BOOL)animated
{
    [super viewWillDisappear: animated];

    if (self.isMovingFromParentViewController)
    {
        LSFConstants *constants = [LSFConstants getConstants];
        self.nedm.state.brightness = [constants scaleLampStateValue:self.nedm.state.brightness withMax:100];
        self.nedm.state.hue = [constants scaleLampStateValue:self.nedm.state.hue withMax:360];
        self.nedm.state.saturation = [constants scaleLampStateValue:self.nedm.state.saturation withMax:100];
        self.nedm.state.colorTemp = [constants scaleColorTemp:self.nedm.state.colorTemp];
    }

    //Clear scenes notification handler
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

-(void) alertSceneDeleted: (LSFSDKScene *)scene
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

/*
 * Table View Data Source Methods
 */
-(NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    if (section == 0)
    {
        return [NSString stringWithFormat: @"Set the properties that %@ will change to", [self buildSectionTitleString: self.nedm]];
    }

    return @"";
}

/*
 * Button Event Handlers
 */
-(IBAction)doneButtonPressed: (id)sender
{
    // Still need to continue to scale the values for SceneV1 as the SceneManager is used directly
    // and there does not exist a SDK level create mechanism to handle SceneV1 creation.
    LSFConstants *constants = [LSFConstants getConstants];

    unsigned int scaledBrightness = 0;
    if (self.nedm.capability.dimmable == NONE && self.nedm.capability.color == NONE && self.nedm.capability.temp == NONE)
    {
        scaledBrightness = [constants scaleLampStateValue: 100 withMax: 100];
    }
    else
    {
        scaledBrightness = [constants scaleLampStateValue: (uint32_t)self.brightnessSlider.value withMax: 100];
    }

    unsigned int scaledHue = [constants scaleLampStateValue: (uint32_t)self.hueSlider.value withMax: 360];
    unsigned int scaledSaturation = [constants scaleLampStateValue: (uint32_t)self.saturationSlider.value withMax: 100];
    unsigned int scaledColorTemp = [constants scaleColorTemp: (uint32_t)self.colorTempSlider.value];

    self.nedm.state = [[LSFLampState alloc] initWithOnOff: YES brightness: scaledBrightness hue: scaledHue saturation: scaledSaturation colorTemp: scaledColorTemp];
    [self.sceneModel updateNoEffect: self.nedm];

    if (self.shouldUpdateSceneAndDismiss)
    {
        [[[[LSFSDKLightingDirector getLightingDirector] lightingManager] sceneManager] updateSceneWithID: self.sceneModel.theID withScene: [self.sceneModel toScene]];
    }

    [self dismissViewControllerAnimated: YES completion: nil];
}

-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Update lamp state
    unsigned int brightness = (uint32_t)self.brightnessSlider.value;
    unsigned int hue = (uint32_t)self.hueSlider.value;
    unsigned int saturation = (uint32_t)self.saturationSlider.value;
    unsigned int colorTemp = (uint32_t)self.colorTempSlider.value;

    if (brightness == 0)
    {
        self.nedm.state.onOff = NO;
    }

    self.nedm.state = [[LSFLampState alloc] initWithOnOff: self.nedm.state.onOff brightness: brightness hue: hue saturation: saturation colorTemp: colorTemp];

    if ([segue.identifier isEqualToString: @"ScenePresets"])
    {
        LSFScenesPresetsTableViewController *sptvc = [segue destinationViewController];

        sptvc.myLampState = [[LSFSDKMyLampState alloc] initWithPower: (self.nedm.state.onOff ? ON : OFF) color: [[LSFSDKColor alloc] initWithHue: hue saturation: saturation brightness: brightness colorTemp: colorTemp]];
        sptvc.effectSender = self;
        sptvc.sceneID = self.sceneModel.theID;
    }
}

-(void)presetButtonSetup: (LSFNoEffectDataModel *)noEffectDataModel
{
    Power nedmPower = noEffectDataModel.state.onOff ? ON : OFF;
    LSFSDKColor *nedmColor = [[LSFSDKColor alloc] initWithHue: noEffectDataModel.state.hue saturation:noEffectDataModel.state.saturation brightness:noEffectDataModel.state.brightness colorTemp: noEffectDataModel.state.colorTemp];

    NSMutableArray *presetsArray = [[NSMutableArray alloc] init];
    BOOL presetMatched = NO;
    for (LSFSDKPreset *preset in [[LSFSDKLightingDirector getLightingDirector] presets])
    {
        BOOL matchesPreset = [self checkIfPreset: preset matchesPower: nedmPower andColor: nedmColor];
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

/*
 * Override public function from LSFEffectTableViewController
 */
-(void)updateColorIndicator
{
    LSFSDKColor *lcolor = [[LSFSDKColor alloc] initWithHue: self.hueSlider.value saturation: self.saturationSlider.value brightness: self.brightnessSlider.value colorTemp: self.colorTempSlider.value];

    [LSFUtilityFunctions colorIndicatorSetup: self.colorIndicatorImage withColor: lcolor andCapabilityData: [[LSFSDKCapabilityData alloc] initWithCapabilityData: self.nedm.capability]];
}

-(IBAction)hueSliderTouchedWhileDisabled: (UIButton *)sender
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error" message: @"" delegate: nil cancelButtonTitle: @"OK" otherButtonTitles: nil];

    if (self.nedm.capability.color == NONE)
    {
        alert.message = @"This Lamp is not able to change its hue.";
    }
    else
    {
        alert.message = @"Hue has no effect when saturation is zero. Set saturation to greater than zero to enable the hue slider.";
    }

    [alert show];
}

-(IBAction)colorTempSliderTouchedWhileDisabled: (UIButton *)sender
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error" message: @"" delegate: nil cancelButtonTitle: @"OK" otherButtonTitles: nil];

    if (self.nedm.capability.color == NONE)
    {
        alert.message = @"This Lamp is not able to change its color temp.";
    }
    else
    {
        alert.message = @"Color temperature has no effect when saturation is 100%. Set saturation to less than 100% to enable the color temperature slider.";
    }

    [alert show];
}

@end
