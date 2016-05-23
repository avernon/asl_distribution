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
#import "LSFLampModelContainer.h"
#import "LSFGroupModelContainer.h"
#import "LSFSceneModelContainer.h"
#import "LSFMasterSceneModelContainer.h"

@interface LSFTabManager()

@property (nonatomic, strong) UITabBarController *tabBarController;

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

        [self updateLampsTab];
        [self updateGroupsTab];
        [self updateScenesTab];
    }

    return self;
}

-(void)updateLampsTab
{
    LSFLampModelContainer *container = [LSFLampModelContainer getLampModelContainer];
    NSMutableDictionary *lamps = container.lampContainer;

    dispatch_async(dispatch_get_main_queue(), ^{
        [[self.tabBarController.tabBar.items objectAtIndex: 0] setTitle: [NSString stringWithFormat: @"Lamps (%i)", lamps.count]];
    });
}

-(void)updateGroupsTab
{
    LSFGroupModelContainer *container = [LSFGroupModelContainer getGroupModelContainer];
    NSMutableDictionary *groups = container.groupContainer;

    dispatch_async(dispatch_get_main_queue(), ^{
        [[self.tabBarController.tabBar.items objectAtIndex: 1] setTitle: [NSString stringWithFormat: @"Groups (%i)", groups.count]];
    });
}

-(void)updateScenesTab
{
    LSFSceneModelContainer *sceneContainer = [LSFSceneModelContainer getSceneModelContainer];
    LSFMasterSceneModelContainer *masterScenesContainer = [LSFMasterSceneModelContainer getMasterSceneModelContainer];
    NSMutableDictionary *scenes = sceneContainer.sceneContainer;
    NSMutableDictionary *masterScenes = masterScenesContainer.masterScenesContainer;

    dispatch_async(dispatch_get_main_queue(), ^{
        [[self.tabBarController.tabBar.items objectAtIndex: 2] setTitle: [NSString stringWithFormat: @"Scenes (%i)", (scenes.count + masterScenes.count)]];
    });
}

@end