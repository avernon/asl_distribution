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

#import "LSFPendingSceneElement.h"
#import <LSFSDKLightingDirector.h>

@implementation LSFPendingSceneElement

@synthesize members = _members;
@synthesize pendingEffect = _pendingEffect;
@synthesize capability = _capability;
@synthesize hasEffect = _hasEffect;

-(id)init
{
    self = [super init];

    if (self)
    {
        _members = nil;
        _pendingEffect = nil;
        _capability = nil;
        _hasEffect = NO;
    }

    return self;
}

-(id)initFromSceneElementID: (NSString *)sceneElementID
{
    self = [self init];

    LSFSDKSceneElement *element = [[LSFSDKLightingDirector getLightingDirector] getSceneElementWithID: sceneElementID];

    if (element)
    {
        self.theID = element.theID;
        self.name = element.name;

        self.pendingEffect = [[LSFPendingEffect alloc] initFromEffectID: [[element getEffect] theID]];

        self.members = [NSMutableArray arrayWithArray: [element getGroups]];
        [self.members addObjectsFromArray: [element getLamps]];

        self.capability = [[LSFSDKCapabilityData alloc] init];

        for (LSFSDKGroupMember *member in self.members)
        {
            [self.capability includeData: [member getCapabilities]];

            if ([member isKindOfClass: [LSFSDKLamp class]])
            {
                self.hasEffect = self.hasEffect || ((LSFSDKLamp *)member).details.hasEffects;
            }
            else if ([member isKindOfClass: [LSFSDKGroup class]])
            {
                for (LSFSDKLamp *lamp in [((LSFSDKGroup *) member) getLamps])
                {
                    self.hasEffect = self.hasEffect || lamp.details.hasEffects;
                }
            }
        }
    }
    else
    {
        NSLog(@"SceneElement not found in Lighting Director. Returning default pending object");
    }

    return self;
}

@end
