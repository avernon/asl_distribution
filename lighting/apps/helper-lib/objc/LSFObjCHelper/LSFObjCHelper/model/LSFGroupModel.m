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

#import "LSFGroupModel.h"
#import "LSFConstants.h"

@interface LSFGroupModel()

@end

@implementation LSFGroupModel

@synthesize members = _members;
@synthesize lamps = _lamps;
@synthesize groups = _groups;
@synthesize duplicates = _duplicates;
@synthesize delay = _delay;
@synthesize groupColorTempMin = _groupColorTempMin;
@synthesize groupColorTempMax = _groupColorTempMax;

-(id)initWithGroupID: (NSString *)groupID
{
    return [self initWithGroupID: groupID andGroupName: @"[Loading group info...]"];
}

-(id)initWithGroupID: (NSString *)groupID andGroupName:(NSString *)groupName
{
    self = [super initWithID: groupID andName: groupName];
    
    if (self)
    {
        self.members = [[LSFLampGroup alloc] init];
        self.groupColorTempMin = [[LSFConstants getConstants] MIN_COLOR_TEMP];
        self.groupColorTempMax = [[LSFConstants getConstants] MAX_COLOR_TEMP];
    }
    
    return self;
}

-(BOOL)containsLamp:(NSString *)lampID
{
    NSArray *childIDs = [[self members] lamps];

    for (NSString* childID : childIDs)
    {
        if ([childID isEqualToString: lampID])
        {
            return true;
        }
    }

    return false;
}

-(BOOL)containsGroup: (NSString *)groupID
{
    NSArray *childIDs = [[self members] lampGroups];

    for (NSString* childID : childIDs)
    {
        if ([childID isEqualToString: groupID])
        {
            return true;
        }
    }

    return false;
}

-(void)setLamps: (NSSet *)lamps
{
    _lamps = lamps;
    self.capability = [[LSFCapabilityData alloc] init];
}

-(NSSet *)lamps
{
    return _lamps;
}

-(void)setGroups: (NSSet *)groups
{
    _groups = groups;
    self.capability = [[LSFCapabilityData alloc] init];
}

-(NSSet *)groups
{
    return _groups;
}

-(void)setMembers:  (LSFLampGroup *)members
{
    _members = members;
    stateInitialized = YES;
}

-(LSFLampGroup *)members
{
    return _members;
}

-(BOOL)isInitialized
{
    return [super isInitialized];
}

@end
