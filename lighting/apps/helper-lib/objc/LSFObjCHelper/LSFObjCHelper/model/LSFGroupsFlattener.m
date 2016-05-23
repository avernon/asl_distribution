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

#import "LSFGroupsFlattener.h"
#import "LSFSDKGroup.h"

@interface LSFGroupsFlattener()

@property (nonatomic, strong) NSMutableSet *lampIDSet;
@property (nonatomic, strong) NSMutableSet *groupIDSet;
@property (nonatomic) int duplicates;

-(void)walkGroups: (NSMutableDictionary *)groups groupDataModel: (LSFGroupModel *)parentModel;
-(void)walkLamps: (NSMutableDictionary *)groups;

@end

@implementation LSFGroupsFlattener

@synthesize groupIDSet = _groupIDSet;
@synthesize lampIDSet = _lampIDSet;
@synthesize duplicates = _duplicates;

-(id)init
{
    self = [super init];
    
    if (self)
    {
        //Do Nothing
    }
    
    return self;
}

-(void)flattenGroups: (NSMutableDictionary *)groups
{
    for (LSFSDKGroup *group in [groups allValues])
    {
        [self flattenGroups: groups withGroup: group];
    }
}

-(void)flattenGroups: (NSMutableDictionary *)groups withGroup: (LSFSDKGroup *)group;
{
    LSFGroupModel *groupModel = [group getLampGroupDataModel];

    self.groupIDSet = [[NSMutableSet alloc] init];
    self.lampIDSet = [[NSMutableSet alloc] init];
    self.duplicates = 0;

    [self walkGroups: groups groupDataModel: groupModel];
    [self walkLamps: groups];

//    NSLog(@"LSFGroupsFlattener - Printing groups and lamps sets");
//
//    for (NSString *groupID in self.groupIDSet)
//    {
//        NSLog(@"%@", groupID);
//    }
//
//    for (NSString *lampID in self.lampIDSet)
//    {
//        NSLog(@"%@", lampID);
//    }

    groupModel.groups = self.groupIDSet;
    groupModel.lamps = self.lampIDSet;
    groupModel.duplicates = self.duplicates;
}

-(void)walkGroups: (NSMutableDictionary *)groups groupDataModel: (LSFGroupModel *)parentModel
{
    if (![self.groupIDSet containsObject: parentModel.theID])
    {
        [self.groupIDSet addObject: parentModel.theID];

        for (NSString *childGroupID in parentModel.members.lampGroups)
        {
            LSFGroupModel *childModel = [[groups valueForKey: childGroupID] getLampGroupDataModel];

            if (childModel != nil)
            {
                [self walkGroups: groups groupDataModel: childModel];
            }
        }
    }
    else
    {
        self.duplicates++;
    }

}

-(void)walkLamps: (NSMutableDictionary *)groups
{
    for (NSString *groupID in self.groupIDSet)
    {
        LSFGroupModel *groupModel = [[groups valueForKey: groupID] getLampGroupDataModel];

        if (groupModel != nil)
        {
            [self.lampIDSet addObjectsFromArray: groupModel.members.lamps];
        }
    }

}

@end
