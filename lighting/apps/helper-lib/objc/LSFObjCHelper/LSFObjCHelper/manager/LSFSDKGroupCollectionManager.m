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

#import "LSFSDKGroupCollectionManager.h"
#import "../initializer/LSFSDKGroup+Init.h"

@implementation LSFSDKGroupCollectionManager

-(id)initWithLightingSystemManager: (LSFSDKLightingSystemManager *)lightingSystemManager
{
    self = [super initWithLightingSystemManager: lightingSystemManager];

    if (self)
    {
        groupFlattener = [[LSFGroupsFlattener alloc] init];
    }

    return self;
}

-(void)addGroupDelegate: (id<LSFSDKGroupDelegate>)groupDelegate
{
    [self addDelegate: groupDelegate];
}

-(void)removeGroupDelegate: (id<LSFSDKGroupDelegate>)groupDelegate
{
    [self removeDelegate: groupDelegate];
}

-(LSFSDKGroup *)addGroupWithID: (NSString *)groupID
{
    LSFSDKGroup *newGroup = [[LSFSDKGroup alloc] initWithGroupID: groupID];
    return [self addGroupWithID: groupID group: newGroup];
}

-(LSFSDKGroup *)addGroupWithID: (NSString *)groupID group: (LSFSDKGroup *)group
{
    [itemAdapters setValue: group forKey: groupID];
    return group;
}

-(LSFSDKGroup *)getGroupWithID: (NSString *)groupID
{
    return [self getAdapterForID: groupID];
}

-(NSArray *)getGroups
{
    return [self getAdapters];
}

-(NSArray *)getGroupsWithFilter: (id<LSFSDKLightingItemFilter>)filter
{
    return [self getGroupsCollectionWithFilter:filter];
}

-(NSArray *)getGroupsCollectionWithFilter: (id<LSFSDKLightingItemFilter>)filter
{
    return [self getAdaptersWithFilter: filter];
}

-(void)flattenGroups
{
    [groupFlattener flattenGroups: itemAdapters];
}

-(void)flattenGroup: (LSFSDKGroup *)group
{
    [groupFlattener flattenGroups: itemAdapters withGroup: group];
}

-(NSArray *)removeAllGroups
{
    return [self removeAllAdapters];
}

-(LSFSDKGroup *)removeGroupWithID: (NSString *)groupID
{
    return [self removeAdapterWithID: groupID];
}

-(LSFGroupModel *)getModelWithID: (NSString *)groupID
{
    LSFSDKGroup *group = [self getAdapterForID: groupID];
    return (group != nil ? [group getLampGroupDataModel] : nil);
}

/*
 * Overriden functions from base class
 */
-(void)sendInitializedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item trackingID: (LSFSDKTrackingID *)trackingID
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKGroupDelegate)] && [item isKindOfClass: [LSFSDKGroup class]])
    {
        id<LSFSDKGroupDelegate> groupDelegate = (id<LSFSDKGroupDelegate>)delegate;
        LSFSDKGroup *group = (LSFSDKGroup *)item;
        [groupDelegate onGroupInitializedWithTrackingID: trackingID andGroup: group];
    }
}

-(void)sendChangedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKGroupDelegate)] && [item isKindOfClass: [LSFSDKGroup class]])
    {
        id<LSFSDKGroupDelegate> groupDelegate = (id<LSFSDKGroupDelegate>)delegate;
        LSFSDKGroup *group = (LSFSDKGroup *)item;
        [groupDelegate onGroupChanged: group];
    }
}

-(void)sendRemovedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKGroupDelegate)] && [item isKindOfClass: [LSFSDKGroup class]])
    {
        id<LSFSDKGroupDelegate> groupDelegate = (id<LSFSDKGroupDelegate>)delegate;
        LSFSDKGroup *group = (LSFSDKGroup *)item;
        [groupDelegate onGroupRemoved: group];
    }
}

-(void)sendErrorEvent: (id<LSFSDKLightingDelegate>)delegate errorEvent: (LSFSDKLightingItemErrorEvent *)errorEvent
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKGroupDelegate)])
    {
        id<LSFSDKGroupDelegate> groupDelegate = (id<LSFSDKGroupDelegate>)delegate;
        [groupDelegate onGroupError: errorEvent];
    }
}

@end
