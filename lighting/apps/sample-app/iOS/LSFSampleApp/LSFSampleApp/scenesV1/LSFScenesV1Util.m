/******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

#import "LSFScenesV1Util.h"
#import "LSFScenesEnterNameViewController.h"
#import <LSFSDKLightingDirector.h>

@implementation LSFScenesV1Util

+(NSString *)buildSceneDetailsString: (LSFSceneDataModel *)sceneModel
{
    NSMutableString *detailsString = [[NSMutableString alloc] init];

    for (LSFNoEffectDataModel *nedm in sceneModel.noEffects)
    {
        [self appendLampNames: nedm.members.lamps toString: detailsString];
        [self appendGroupNames: nedm.members.lampGroups toString: detailsString];
    }

    for (LSFTransitionEffectDataModel *tedm in sceneModel.transitionEffects)
    {
        [self appendLampNames: tedm.members.lamps toString: detailsString];
        [self appendGroupNames: tedm.members.lampGroups toString: detailsString];
    }

    for (LSFPulseEffectDataModel *pedm in sceneModel.pulseEffects)
    {
        [self appendLampNames: pedm.members.lamps toString: detailsString];
        [self appendGroupNames: pedm.members.lampGroups toString: detailsString];
    }

    NSString *finalString;
    if (detailsString.length > 0)
    {
        finalString = [detailsString substringToIndex: detailsString.length - 2];
    }

    return finalString;
}

+(void)appendLampNames: (NSArray *)lampIDs toString: (NSMutableString *)detailsString
{
    for (NSString *lampID in lampIDs)
    {
        LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID: lampID];

        if (lamp != nil)
        {
            [detailsString appendString: [NSString stringWithFormat: @"%@, ", lamp.name]];
        }
    }
}

+(void)appendGroupNames: (NSArray *)groupIDs toString: (NSMutableString *)detailsString
{
    for (NSString *groupID in groupIDs)
    {
        LSFSDKGroup *group = [[LSFSDKLightingDirector getLightingDirector] getGroupWithID: groupID];

        if (group != nil)
        {
            [detailsString appendString: [NSString stringWithFormat: @"%@, ", group.name]];
        }
    }
}

+(void)doSegueCreateSceneV1: (UIStoryboardSegue *)segue
{
    // Set the top ViewController to the entry point for SceneV1 creation within separate Storyboard
    UINavigationController *nc = (UINavigationController *)[segue destinationViewController];

    UIStoryboard *scenesV1StoryBoard = [UIStoryboard storyboardWithName:@"ScenesV1Storyboard" bundle: nil];
    UIViewController *rootViewController = (UIViewController *)[scenesV1StoryBoard instantiateViewControllerWithIdentifier:@"CreateSceneV1"];
    [nc setViewControllers: [NSArray arrayWithObjects: rootViewController, nil] animated: YES];

    LSFScenesEnterNameViewController *senvc = (LSFScenesEnterNameViewController *)nc.topViewController;
    senvc.sceneModel = [[LSFSceneDataModel alloc] init];
}

@end
