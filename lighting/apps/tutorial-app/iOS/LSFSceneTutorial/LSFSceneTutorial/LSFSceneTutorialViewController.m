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

#import "LSFSceneTutorialViewController.h"
#import "LSFSDKLightingDirector.h"
#import "LSFSDKLightingController.h"
#import "LSFSDKLightingControllerConfigurationBase.h"
#import "LSFSDKMyLampState.h"
#import "LSFSDKAllLightingItemDelegateBase.h"

/*
 * Global delegate that uses the initialization callbacks of various objects to sequentially
 * create the components of a Scene and apply it.
 */
@interface MyLightingDelegate : LSFSDKAllLightingItemDelegateBase

@end

@implementation MyLightingDelegate

-(void)onPulseEffectInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andPulseEffect: (LSFSDKPulseEffect *)pulseEffect
{
    // STEP 4: Using the Pulse Effect initialized callback as a trigger, create a Scene Element with the new Pulse Effect
    // and all lamps known to the Lighting Director.
    NSArray *members = [[LSFSDKLightingDirector getLightingDirector] lamps];
    [[LSFSDKLightingDirector getLightingDirector] createSceneElementWithEffect: pulseEffect groupMembers: members name: @"TutorialSceneElement"];
}

-(void)onPulseEffectError: (LSFSDKLightingItemErrorEvent *)error
{
    NSLog(@"onPulseEffectError - Error Name = %@", error.name);
}

-(void)onSceneElementInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andSceneElement: (LSFSDKSceneElement *)sceneElement
{
    // STEP 5: Using the Scene Element initialized callback as a trigger, create a Scene with the new Scene Element.
    NSArray *sceneElements = [NSArray arrayWithObjects: sceneElement, nil];
    [[LSFSDKLightingDirector getLightingDirector] createSceneWithSceneElements: sceneElements name: @"TutorialScene"];
}

-(void)onSceneElementError: (LSFSDKLightingItemErrorEvent *)error
{
    NSLog(@"onSceneElementError - Error Name = %@", error.name);
}

-(void)onSceneInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andScene: (LSFSDKScene *)scene
{
    // STEP 6: Using the Scene initialized callback as a trigger, apply the Scene.
    [scene apply];
}

-(void)onSceneError:(LSFSDKLightingItemErrorEvent *)error
{
    NSLog(@"onSceneError - Error Name = %@", error.name);
}

@end //End private inner classes

static unsigned int CONTROLLER_CONNECTION_DELAY = 5000;

@interface LSFSceneTutorialViewController ()

@property (nonatomic, strong) LSFSDKLightingDirector *lightingDirector;
@property (nonatomic, strong) MyLightingDelegate *myLightingDelegate;
@property (nonatomic, strong) LSFSDKLightingControllerConfigurationBase *config;

@end

@implementation LSFSceneTutorialViewController

@synthesize versionLabel = _versionLabel;
@synthesize lightingDirector = _lightingDirector;
@synthesize myLightingDelegate = _myLightingDelegate;
@synthesize config = _config;

-(void)viewDidLoad
{
    [super viewDidLoad];

    //Display the version number
    NSMutableString *appVersion = [NSMutableString stringWithFormat: @"Version: %@", [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"]];
    [appVersion appendString: [NSString stringWithFormat: @".%@", [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleVersion"]]];
    [self.versionLabel setText: appVersion];

    // STEP 1: Initialize a lighting controller with default configuration
    self.config = [[LSFSDKLightingControllerConfigurationBase alloc]initWithKeystorePath: @"Documents"];
    LSFSDKLightingController *lightingController = [LSFSDKLightingController getLightingController];
    [lightingController initializeWithControllerConfiguration: self.config];
    [lightingController start];

    // STEP 2: Instantiate the lighting director and wait for the connection, register a global delegate to
    // handle Lighting events
    self.myLightingDelegate = [[MyLightingDelegate alloc] init];
    self.lightingDirector = [LSFSDKLightingDirector getLightingDirector];
    [self.lightingDirector addDelegate: self.myLightingDelegate];
    [self.lightingDirector postOnNextControllerConnectionWithDelay: CONTROLLER_CONNECTION_DELAY delegate: self];
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
 * LSFSDKNextControllerConnectionDelegate implementation
 */
-(void)onNextControllerConnection
{
    // STEP 3: Create PulseEffect
    LSFSDKColor *pulseFromColor = [LSFSDKColor green];
    LSFSDKColor *pulseToColor = [LSFSDKColor blue];
    Power pulsePowerState = ON;
    unsigned int period = 1000;
    unsigned int duration = 500;
    unsigned int numPulses = 10;
    LSFSDKMyLampState *fromState = [[LSFSDKMyLampState alloc] initWithPower: pulsePowerState color: pulseFromColor];
    LSFSDKMyLampState *toState = [[LSFSDKMyLampState alloc] initWithPower: pulsePowerState color: pulseToColor];

    // boilerplate code, alter parameters above to change effect color, length, etc.
    [[LSFSDKLightingDirector getLightingDirector] createPulseEffectWithFromState: fromState toState: toState period: period duration: duration count: numPulses name: @"TutorialPulseEffect"];
}

@end