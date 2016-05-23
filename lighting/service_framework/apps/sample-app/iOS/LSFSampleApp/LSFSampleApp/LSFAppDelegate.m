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
#import "LSFLampModelContainer.h"
#import "LSFGroupModelContainer.h"
#import "LSFPresetModelContainer.h"
#import "LSFMasterSceneModelContainer.h"
#import "LSFSceneModelContainer.h"
#import "LSFDispatchQueue.h"
#import "LSFConstants.h"
#import "LSFWifiMonitor.h"
#import "LSFTabManager.h"
#import "LSFAllJoynManager.h"

@implementation LSFAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    [LSFAllJoynManager getAllJoynManager];
    [LSFLampModelContainer getLampModelContainer];
    [LSFGroupModelContainer getGroupModelContainer];
    [LSFPresetModelContainer getPresetModelContainer];
    [LSFMasterSceneModelContainer getMasterSceneModelContainer];
    [LSFSceneModelContainer getSceneModelContainer];
    [LSFDispatchQueue getDispatchQueue];
    [LSFConstants getConstants];
    [LSFWifiMonitor getWifiMonitor];
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Called when the apps state will change to inactive. Use this method to pause the app.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // If your app supports background execution, use this method to release shared resources and save any data.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Undo the changes that were made when the app entered the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart tasks that were stopped when the app entered the background and refresh the UI.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Implement when app is about to terminate and save data, if needed.
}

@end
