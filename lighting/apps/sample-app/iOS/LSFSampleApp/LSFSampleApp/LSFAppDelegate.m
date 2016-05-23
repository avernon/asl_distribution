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

#import "LSFAppDelegate.h"
#import "LSFWifiMonitor.h"
#import "LSFTabManager.h"

#import <LSFSDKLightingDirector.h>
#import "LSFLightingEventListener.h"

@implementation LSFAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    NSLog(@"LSFAppDelegate - applicationDidFinishLaunchingWithOptions()");

    LSFSDKLightingDirector *lightingDirector = [LSFSDKLightingDirector getLightingDirector];
    [lightingDirector addDelegate:[[LSFLightingEventListener alloc] init]];
    
    [lightingDirector startWithApplicationName: @"LightingDirector" dispatchQueue: dispatch_get_main_queue()];

    [LSFTabManager getTabManager];

    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    NSLog(@"LSFAppDelegate - applicationWillResignActive()");
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    NSLog(@"LSFAppDelegate - applicationDidEnterBackground()");

    //Close app when it enters the background
    exit(0);
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    NSLog(@"LSFAppDelegate - applicationWillEnterForeground()");

    [[LSFWifiMonitor getWifiMonitor] checkCurrentStatus];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    NSLog(@"LSFAppDelegate - applicationDidBecomeActive()");
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    NSLog(@"LSFAppDelegate - applicationWillTerminate()");
}

@end
