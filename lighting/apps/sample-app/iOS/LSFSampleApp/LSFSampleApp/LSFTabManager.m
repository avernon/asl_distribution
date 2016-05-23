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

#import "LSFTabManager.h"
#import "LSFAppDelegate.h"
#include <LSFSDKLightingDirector.h>

@interface LSFTabManager()

@property (nonatomic, strong) UITabBarController *tabBarController;

-(void)lampNotificationReceived: (NSNotification *)notification;
-(void)groupNotificationRecieved: (NSNotification *)notification;
-(void)sceneNotificationReceived: (NSNotification *)notification;

@end

@implementation LSFTabManager

@synthesize tabBarController = _tabBarController;

+(id)getTabManager
{
    static LSFTabManager *tabManager = nil;
    static dispatch_once_t onceToken;

    dispatch_once(&onceToken, ^{
        tabManager = [[self alloc] init];
    });

    return tabManager;
}

-(id)init
{
    self = [super init];

    if (self)
    {
        LSFAppDelegate *appDelegate = (LSFAppDelegate *)[[UIApplication sharedApplication] delegate];
        self.tabBarController = (UITabBarController *)appDelegate.window.rootViewController;

        // register notifications
        [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(lampNotificationReceived:) name: @"LSFLampChangedNotification" object: nil];
        [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(groupNotificationRecieved:) name: @"LSFGroupChangedNotification" object: nil];
        [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(sceneNotificationReceived:) name: @"LSFSceneChangedNotification" object: nil];
        [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(sceneNotificationReceived:) name: @"LSFMasterSceneChangedNotification" object: nil];

        [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(lampNotificationReceived:) name: @"LSFLampRemovedNotification" object: nil];
        [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(groupNotificationRecieved:) name: @"LSFGroupRemovedNotification" object: nil];
        [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(sceneNotificationReceived:) name: @"LSFSceneRemovedNotification" object: nil];
        [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(sceneNotificationReceived:) name: @"LSFMasterRemovedNotification" object: nil];

        [self lampNotificationReceived: nil];
        [self groupNotificationRecieved: nil];
        [self sceneNotificationReceived: nil];
    }

    return self;
}

-(void)lampNotificationReceived: (NSNotification *)notification
{
    [[self.tabBarController.tabBar.items objectAtIndex: 0] setTitle: [NSString stringWithFormat: @"Lamps (%lu)", (unsigned long)[[LSFSDKLightingDirector getLightingDirector] lampCount]]];
}

-(void)groupNotificationRecieved: (NSNotification *)notification
{
    [[self.tabBarController.tabBar.items objectAtIndex: 1] setTitle: [NSString stringWithFormat: @"Groups (%lu)", (unsigned long) [[LSFSDKLightingDirector getLightingDirector] groupCount]]];
}

-(void)sceneNotificationReceived: (NSNotification *)notification
{
    unsigned long totalScenes = ([[LSFSDKLightingDirector getLightingDirector] sceneCount]) + [[LSFSDKLightingDirector getLightingDirector] masterSceneCount];

    [[self.tabBarController.tabBar.items objectAtIndex: 2] setTitle: [NSString stringWithFormat: @"Scenes (%lu)", totalScenes]];
}

@end
