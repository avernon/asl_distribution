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

#import "LSFSDKMasterSceneCollectionManager.h"
#import "../initializer/LSFSDKMasterScene+Init.h"

@implementation LSFSDKMasterSceneCollectionManager

-(id)initWithLightingSystemManager: (LSFSDKLightingSystemManager *)lightingSystemManager
{
    self = [super initWithLightingSystemManager: lightingSystemManager];

    if (self)
    {
        //Intentionally left blank
    }

    return self;
}

-(void)addMasterSceneDelegate: (id<LSFSDKMasterSceneDelegate>)masterSceneDelegate
{
    [self addDelegate: masterSceneDelegate];
}

-(void)removeMasterSceneDelegate: (id<LSFSDKMasterSceneDelegate>)masterSceneDelegate
{
    [self removeDelegate: masterSceneDelegate];
}

-(LSFSDKMasterScene *)addMasterSceneWithID: (NSString *)masterSceneID
{
    LSFSDKMasterScene *newMasterScene = [[LSFSDKMasterScene alloc] initWithMasterSceneID: masterSceneID];
    return [self addMasterSceneWithID: masterSceneID masterScene: newMasterScene];
}

-(LSFSDKMasterScene *)addMasterSceneWithID: (NSString *)masterSceneID masterScene: (LSFSDKMasterScene *)masterScene
{
    [itemAdapters setValue: masterScene forKey: masterSceneID];
    return masterScene;
}

-(LSFSDKMasterScene *)getMasterSceneWithID: (NSString *)masterSceneID
{
    return [self getAdapterForID: masterSceneID];
}

-(NSArray *)getMasterScenes
{
    return [self getAdapters];
}

-(NSArray *)getMasterScenesWithFilter: (id<LSFSDKLightingItemFilter>)filter
{
    return [self getMasterScenesCollectionWithFilter:filter];
}

-(NSArray *)getMasterScenesCollectionWithFilter: (id<LSFSDKLightingItemFilter>)filter;
{
    return [self getAdaptersWithFilter: filter];
}

-(NSArray *)removeAllMasterScenes
{
    return [self removeAllAdapters];
}
-(LSFSDKMasterScene *)removeMasterSceneWithID: (NSString *)masterSceneID
{
    return [self removeAdapterWithID: masterSceneID];
}

-(LSFMasterSceneDataModel *)getModelWithID: (NSString *)masterSceneID
{
    LSFSDKMasterScene *masterScene = [self getAdapterForID: masterSceneID];
    return (masterScene != nil ? [masterScene getMasterSceneDataModel] : nil);
}

/*
 * Overriden functions from base class
 */
-(void)sendInitializedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item trackingID: (LSFSDKTrackingID *)trackingID
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKMasterSceneDelegate)] && [item isKindOfClass: [LSFSDKMasterScene class]])
    {
        id<LSFSDKMasterSceneDelegate> masterSceneDelegate = (id<LSFSDKMasterSceneDelegate>)delegate;
        LSFSDKMasterScene *masterScene = (LSFSDKMasterScene *)item;
        [masterSceneDelegate onMasterSceneInitializedWithTrackingID: trackingID andMasterScene: masterScene];
    }
}

-(void)sendChangedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKMasterSceneDelegate)] && [item isKindOfClass: [LSFSDKMasterScene class]])
    {
        id<LSFSDKMasterSceneDelegate> masterSceneDelegate = (id<LSFSDKMasterSceneDelegate>)delegate;
        LSFSDKMasterScene *masterScene = (LSFSDKMasterScene *)item;
        [masterSceneDelegate onMasterSceneChanged: masterScene];
    }
}

-(void)sendRemovedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKMasterSceneDelegate)] && [item isKindOfClass: [LSFSDKMasterScene class]])
    {
        id<LSFSDKMasterSceneDelegate> masterSceneDelegate = (id<LSFSDKMasterSceneDelegate>)delegate;
        LSFSDKMasterScene *masterScene = (LSFSDKMasterScene *)item;
        [masterSceneDelegate onMasterSceneRemoved: masterScene];
    }
}

-(void)sendErrorEvent: (id<LSFSDKLightingDelegate>)delegate errorEvent: (LSFSDKLightingItemErrorEvent *)errorEvent
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKMasterSceneDelegate)])
    {
        id<LSFSDKMasterSceneDelegate> masterSceneDelegate = (id<LSFSDKMasterSceneDelegate>)delegate;
        [masterSceneDelegate onMasterSceneError: errorEvent];
    }
}

@end
