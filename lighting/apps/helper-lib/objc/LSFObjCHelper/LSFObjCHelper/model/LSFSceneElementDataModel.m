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

#import "LSFSceneElementDataModel.h"

static int nextID = 1;

@implementation LSFSceneElementDataModel

@synthesize type = _type;
@synthesize members = _members;
@synthesize colorTempMin = _colorTempMin;
@synthesize colorTempMax = _colorTempMax;

-(id)initWithEffectType: (EffectType)type andName: (NSString *)name
{
    self = [super initWithID: [NSString stringWithFormat: @"%i", nextID++] andName: name];

    if (self)
    {
        self.type = type;
        self.members = [[LSFLampGroup alloc] init];

        // Lamp state should always be set to "ON". Turning the lamp off as part
        // of an effect requires setting the brightness to zero.
        self.state.onOff = YES;

        self.capability.dimmable = ALL;
        self.capability.color = ALL;
        self.capability.temp = ALL;

        self.colorTempMin = -1;
        self.colorTempMax = -1;
    }

    return self;
}

-(BOOL)containsGroup: (NSString *)groupID
{
    NSArray *childIDs = [self.members lampGroups];

    for (NSString *childID in childIDs)
    {
        if ([childID isEqualToString: groupID])
        {
            return YES;
        }
    }

    return NO;
}

-(BOOL) containsPreset:(NSString *)presetID
{
    return NO;
}

@end
