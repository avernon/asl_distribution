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

#import "LSFLampGroup.h"
#import "LSFTypes.h"

@interface LSFLampGroup()

@property (nonatomic, readonly) lsf::LampGroup *lampGroup;

@end

@implementation LSFLampGroup

@synthesize lampGroup = _lampGroup;

-(id)init
{
    self = [super init];
    
    if (self)
    {
        self.handle = new lsf::LampGroup();
    }
    
    return self;
}

-(void)setLamps: (NSArray *)lampIDs
{
    LSFStringList lids;
    
    for (NSString *lid in lampIDs)
    {
        lids.push_back([lid UTF8String]);
    }
    
    self.lampGroup->lamps = lids;
}

-(NSArray *)lamps
{
    LSFStringList lamps = self.lampGroup->lamps;
    NSMutableArray *lampIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = lamps.begin(); iter != lamps.end(); ++iter)
    {
        [lampIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    return lampIDsArray;
}

-(void)setLampGroups: (NSArray *)groupIDs
{
    LSFStringList gids;
    
    for (NSString *gid in groupIDs)
    {
        gids.push_back([gid UTF8String]);
    }
    
    self.lampGroup->lampGroups = gids;
}

-(NSArray *)lampGroups
{
    LSFStringList lampGroups = self.lampGroup->lampGroups;
    NSMutableArray *groupIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = lampGroups.begin(); iter != lampGroups.end(); ++iter)
    {
        [groupIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    return groupIDsArray;
}

-(LSFResponseCode)isDependentLampGroup: (NSString *)groupID
{
    std::string gid([groupID UTF8String]);
    return self.lampGroup->IsDependentLampGroup(gid);
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
- (lsf::LampGroup *)lampGroup
{
    return static_cast<lsf::LampGroup*>(self.handle);
}

@end
