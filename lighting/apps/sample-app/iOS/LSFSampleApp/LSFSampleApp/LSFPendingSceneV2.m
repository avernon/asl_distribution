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

#import "LSFPendingSceneV2.h"
#import "LSFPendingSceneElement.h"
#import <LSFSDKLightingDirector.h>

@implementation LSFPendingSceneV2

@synthesize pendingSceneElements = _pendingSceneElements;

-(id)init
{
    self = [super init];

    if (self)
    {
        _pendingSceneElements = nil;
    }

    return self;
}

-(id)initFromSceneID: (NSString *)sceneID
{
    self = [super init];

    LSFSDKScene *scene = [[LSFSDKLightingDirector getLightingDirector] getSceneWithID: sceneID];

    if (scene && [scene isKindOfClass: [LSFSDKSceneV2 class]])
    {
        LSFSDKSceneV2 *sceneV2 = (LSFSDKSceneV2 *) scene;

        self.theID = sceneV2.theID;
        self.name = sceneV2.name;

        self.pendingSceneElements = [[NSMutableArray alloc] init];
        for (LSFSDKSceneElement *element in [sceneV2 getSceneElements])
        {
            NSString *elementID = element.theID;
            [self.pendingSceneElements addObject: [[LSFPendingSceneElement alloc] initFromSceneElementID: elementID]];
        }
    }
    else
    {
        NSLog(@"SceneV2 not found in Lighting Director. Returning default pending object");
    }

    return self;
}

-(BOOL)hasValidSceneElements
{
    if (self.pendingSceneElements)
    {
        for (LSFPendingSceneElement *elem in self.pendingSceneElements)
        {
            if (!elem.theID)
            {
                return NO;
            }
        }
    }

    return YES;
}

@end
