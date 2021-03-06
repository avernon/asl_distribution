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

#import "LSFSDKAllLampsLampGroup.h"

@implementation LSFSDKAllLampsLampGroup

+(LSFSDKAllLampsLampGroup *)getInstance
{
    static LSFSDKAllLampsLampGroup *instance = nil;
    static dispatch_once_t onceToken;

    dispatch_once(&onceToken, ^{
        instance = [[self alloc] init];
    });

    return instance;
}

-(id)init
{
    self = [super init];

    if (self)
    {
        manager = nil;
        emptyArray = [[NSArray alloc] init];
    }

    return self;
}

/*
 *
 */
-(void)setLightingSystemManager: (LSFSDKLightingSystemManager *)lsm
{
    manager = lsm;
}

/*
 * Override base class functions
 */
-(void)setLamps: (NSArray *)lamps
{
    NSLog(@"LSFAllLampsLampGroup - Invalid attempt to set lamp members of the all-lamps lamp group");
}

-(NSArray *)lamps
{
    if (manager != nil)
    {
        NSArray *lamps = [manager.lampCollectionManager getLamps];
        NSMutableArray *lampIDs = [[NSMutableArray alloc] init];

        for (LSFSDKLamp *lamp in lamps)
        {
            [lampIDs addObject: [lamp theID]];
        }

        return lampIDs;
    }

    return emptyArray;
}

-(void)setLampGroups: (NSArray *)lampGroups
{
    NSLog(@"LSFAllLampsLampGroup - Invalid attempt to set group members of the all-lamps lamp group");
}

-(NSArray *)lampGroups
{
    return emptyArray;
}

-(LSFResponseCode)isDependentLampGroup: (NSString *)groupID
{
    return [super isDependentLampGroup: groupID];
}

@end
