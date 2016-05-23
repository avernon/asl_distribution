/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

#import "LSFPresetTutorialViewController.h"
#import "LSFSDKLightingDirector.h"
#import "LSFSDKLightingController.h"
#import "LSFSDKLightingControllerConfigurationBase.h"
#import "LSFSDKAllLightingItemDelegateBase.h"

/*
 * Global Lighting event listener. Responsible for handling any callbacks that
 * the user is interested in acting on.
 */
@interface MyLightingDelegate : LSFSDKAllLightingItemDelegateBase

// Intentionally left blank

@end

@implementation MyLightingDelegate

-(void)onLampInitialized: (LSFSDKLamp *)lamp
{
     // STEP 3: Use the discovery of the Lamp as a trigger for creating a Preset. We define a
     // preset that changes the color to red.
    [[LSFSDKLightingDirector getLightingDirector] createPresetWithPower: ON color: [LSFSDKColor red] presetName: @"TutorialPreset"];
}

-(void)onLampError: (LSFSDKLightingItemErrorEvent *)error
{
    NSLog(@"onLampError - ErrorName = %@", error.name);
}

-(void)onPresetInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andPreset: (LSFSDKPreset *)preset
{
    // STEP 4: After the Preset is created, apply the Preset to all lamps on the network
    for (LSFSDKLamp *lamp in [[LSFSDKLightingDirector getLightingDirector] lamps])
    {
        [preset applyToGroupMember: lamp];
    }
}

-(void)onPresetError: (LSFSDKLightingItemErrorEvent *)error
{
    NSLog(@"onPresetError - ErrorName = %@", error.name);
}

@end //End private class

@interface LSFPresetTutorialViewController ()

@property (nonatomic, strong) LSFSDKLightingDirector *lightingDirector;
@property (nonatomic, strong) LSFSDKLightingControllerConfigurationBase *config;

@end

@implementation LSFPresetTutorialViewController

@synthesize versionLabel = _versionLabel;
@synthesize lightingDirector = _lightingDirector;
@synthesize config = _config;

-(void)viewDidLoad
{
    [super viewDidLoad];

    // Display the version number
    NSMutableString *appVersion = [NSMutableString stringWithFormat: @"Version: %@", [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"]];
    [appVersion appendString: [NSString stringWithFormat: @".%@", [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleVersion"]]];
    [self.versionLabel setText: appVersion];

    // STEP 1: Initialize a lighting controller with default configuration
    self.config = [[LSFSDKLightingControllerConfigurationBase alloc]initWithKeystorePath: @"Documents"];
    LSFSDKLightingController *lightingController = [LSFSDKLightingController getLightingController];
    [lightingController initializeWithControllerConfiguration: self.config];
    [lightingController start];

    // STEP 2: Instantiate the lighting director and wait for the connection, register a global delegate
    // to handle Lighting events
    self.lightingDirector = [LSFSDKLightingDirector getLightingDirector];
    MyLightingDelegate *lightingDelegate = [[MyLightingDelegate alloc] init];
    [self.lightingDirector addDelegate: lightingDelegate];
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

@end