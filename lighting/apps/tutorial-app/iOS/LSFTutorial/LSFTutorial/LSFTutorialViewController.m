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

#import "LSFTutorialViewController.h"
#import "LSFSDKLightingDirector.h"
#import "LSFSDKLightingController.h"
#import "LSFSDKLightingControllerConfigurationBase.h"
#import "LSFSDKLamp.h"
#import "LSFSDKGroup.h"
#import "LSFSDKScene.h"

@interface LSFTutorialViewController ()

@property (nonatomic, strong) LSFSDKLightingDirector *lightingDirector;
@property (nonatomic, strong) LSFSDKLightingControllerConfigurationBase *config;

@end

@implementation LSFTutorialViewController

@synthesize versionLabel = _versionLabel;
@synthesize lightingDirector = _lightingDirector;
@synthesize config = _config;

-(void)viewDidLoad
{
    [super viewDidLoad];

    //Display the version number
    NSMutableString *appVersion = [NSMutableString stringWithFormat: @"Version: %@", [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"]];
    [appVersion appendString: [NSString stringWithFormat: @".%@", [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleVersion"]]];
    [appVersion appendString: [NSString stringWithFormat: @" (%@)", ARCH_STR]];
    [self.versionLabel setText: appVersion];

    // STEP 1: Initialize a lighting controller with default configuration
    self.config = [[LSFSDKLightingControllerConfigurationBase alloc]initWithKeystorePath: @"Documents"];
    LSFSDKLightingController *lightingController = [LSFSDKLightingController getLightingController];
    [lightingController initializeWithControllerConfiguration: self.config];
    [lightingController start];

    // STEP 2: Instantiate the lighting director and wait for the connection
    self.lightingDirector = [LSFSDKLightingDirector getLightingDirector];
    [self.lightingDirector postOnNextControllerConnectionWithDelay: 5000 delegate: self];
    [self.lightingDirector start];
}

-(void)dealloc
{
    if (self.lightingDirector)
    {
        [self.lightingDirector stop];
        self.lightingDirector = nil;
    }
}

-(void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

/*
 * Some_Callback_Delegate implementation
 */
-(void)onNextControllerConnection
{
    NSLog(@"LSFTutorialViewController - onNextControllerConnection() executing");

    // Lamp operations
    NSArray *lamps = [self.lightingDirector lamps];

    for (LSFSDKLamp *lamp in lamps)
    {
        [lamp turnOn];
    }

    [NSThread sleepForTimeInterval: 2.0];

    for (LSFSDKLamp *lamp in lamps)
    {
        [lamp turnOff];
    }

    [NSThread sleepForTimeInterval: 2.0];

    for (int i = 0; i < lamps.count; i++)
    {
        LSFSDKLamp *lamp = [lamps objectAtIndex: i];
        [lamp setColorHsvtWithHue: 180 saturation: 100 brightness: 50 colorTemp: 4000];
    }

    // Group operations
    NSArray *groups = [self.lightingDirector groups];

    for (LSFSDKGroup *group in groups)
    {
        [group turnOn];
    }

    [NSThread sleepForTimeInterval: 2.0];

    for (LSFSDKGroup *group in groups)
    {
        [group turnOff];
    }

    [NSThread sleepForTimeInterval: 2.0];

    for (LSFSDKGroup *group in groups)
    {
        [group setColorHsvtWithHue: 280 saturation: 100 brightness: 100 colorTemp: 4000];
    }

    [NSThread sleepForTimeInterval: 2.0];

    // Scene operations
    NSArray *scenes = [self.lightingDirector scenes];

    for (int i = 0; i < scenes.count; i++)
    {
        LSFSDKScene *scene = [scenes objectAtIndex: i];
        [scene apply];
    }
}

@end
