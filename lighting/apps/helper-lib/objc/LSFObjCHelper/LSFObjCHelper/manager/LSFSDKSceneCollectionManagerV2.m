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

#import "LSFSDKSceneCollectionManagerV2.h"
#import "../initializer/LSFSDKSceneV2+Init.h"

@implementation LSFSDKSceneCollectionManagerV2

-(id)initWithLightingSystemManager: (LSFSDKLightingSystemManager *)lightingSystemManager
{
    self = [super initWithLightingSystemManager: lightingSystemManager];

    if (self)
    {
        //Intentionally left blank
    }

    return self;
}

-(void)addSceneDelegate: (id<LSFSDKSceneDelegate>)sceneDelegate
{
    [self addDelegate: sceneDelegate];
}

-(void)removeSceneDelegate: (id<LSFSDKSceneDelegate>)sceneDelegate
{
    [self removeDelegate: sceneDelegate];
}

-(LSFSDKSceneV2 *)addSceneWithID: (NSString *)sceneID
{
    LSFSDKSceneV2 *scene = [[LSFSDKSceneV2 alloc] initWithSceneID: sceneID];
    return [self addSceneWithID: sceneID scene: scene];
}

-(LSFSDKSceneV2 *)addSceneWithModel: (LSFSceneDataModelV2 *)sceneModel
{
    LSFSDKSceneV2 *scene = [[LSFSDKSceneV2 alloc] initWithSceneDataModel: sceneModel];
    return [self addSceneWithID: sceneModel.theID scene: scene];
}

-(LSFSDKSceneV2 *)addSceneWithID: (NSString *)sceneID scene: (LSFSDKSceneV2 *)scene
{
    [itemAdapters setValue: scene forKey: sceneID];
    return scene;
}

-(LSFSDKSceneV2 *)getSceneWithID: (NSString *)sceneID
{
    return [self getAdapterForID: sceneID];
}

-(NSArray *)getScenes
{
    return [self getAdapters];
}

-(NSArray *)getScenesWithFilter: (id<LSFSDKLightingItemFilter>)filter
{
    return [self getScenesCollectionWithFilter: filter];
}

-(NSArray *)getScenesCollectionWithFilter: (id<LSFSDKLightingItemFilter>)filter
{
    return [self getAdaptersWithFilter: filter];
}

-(NSArray *)removeAllScenes
{
    return [self removeAllAdapters];
}

-(LSFSDKSceneV2 *)removeSceneWithID: (NSString *)sceneID
{
    return [self removeAdapterWithID: sceneID];
}

-(LSFSceneDataModelV2 *)getModelWithID: (NSString *)sceneID
{
    LSFSDKSceneV2 *scene = [self getAdapterForID: sceneID];
    return (scene != nil ? [scene getSceneDataModel] : nil);
}

/*
 * Overriden functions from base class
 */
-(void)sendInitializedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item trackingID: (LSFSDKTrackingID *)trackingID
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKSceneDelegate)] && [item isKindOfClass: [LSFSDKSceneV2 class]])
    {
        id<LSFSDKSceneDelegate> sceneDelegate = (id<LSFSDKSceneDelegate>)delegate;
        LSFSDKSceneV2 *scene = (LSFSDKSceneV2 *)item;
        [sceneDelegate onSceneInitializedWithTrackingID: trackingID andScene: scene];
    }
}

-(void)sendChangedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKSceneDelegate)] && [item isKindOfClass: [LSFSDKSceneV2 class]])
    {
        id<LSFSDKSceneDelegate> sceneDelegate = (id<LSFSDKSceneDelegate>)delegate;
        LSFSDKSceneV2 *scene = (LSFSDKSceneV2 *)item;
        [sceneDelegate onSceneChanged: scene];
    }
}

-(void)sendRemovedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKSceneDelegate)] && [item isKindOfClass: [LSFSDKSceneV2 class]])
    {
        id<LSFSDKSceneDelegate> sceneDelegate = (id<LSFSDKSceneDelegate>)delegate;
        LSFSDKSceneV2 *scene = (LSFSDKSceneV2 *)item;
        [sceneDelegate onSceneRemoved: scene];
    }
}

-(void)sendErrorEvent: (id<LSFSDKLightingDelegate>)delegate errorEvent: (LSFSDKLightingItemErrorEvent *)errorEvent
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKSceneDelegate)])
    {
        id<LSFSDKSceneDelegate> sceneDelegate = (id<LSFSDKSceneDelegate>)delegate;
        [sceneDelegate onSceneError: errorEvent];
    }
}

@end
