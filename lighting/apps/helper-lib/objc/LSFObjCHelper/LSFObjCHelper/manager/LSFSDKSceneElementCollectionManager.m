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

#import "LSFSDKSceneElementCollectionManager.h"
#import "../initializer/LSFSDKSceneElement+Init.h"

@implementation LSFSDKSceneElementCollectionManager

-(id)initWithLightingSystemManager: (LSFSDKLightingSystemManager *)lightingSystemManager
{
    self = [super initWithLightingSystemManager: lightingSystemManager];

    if (self)
    {
        //Intentionally left blank
    }

    return self;
}

-(void)addSceneElementDelegate: (id<LSFSDKSceneElementDelegate>)sceneElementDelegate
{
    [self addDelegate: sceneElementDelegate];
}

-(void)removeSceneElementDelegate: (id<LSFSDKSceneElementDelegate>)sceneElementDelegate
{
    [self removeDelegate: sceneElementDelegate];
}

-(LSFSDKSceneElement *)addSceneElementWithID: (NSString *)sceneElementID
{
    LSFSDKSceneElement *sceneElement = [[LSFSDKSceneElement alloc] initWithSceneElementID: sceneElementID];
    return [self addSceneElementWithID: sceneElementID sceneElement: sceneElement];
}

-(LSFSDKSceneElement *)addSceneElementWithID: (NSString *)sceneElementID sceneElement: (LSFSDKSceneElement *)sceneElement
{
    [itemAdapters setValue: sceneElement forKey: sceneElementID];
    return sceneElement;
}

-(LSFSDKSceneElement *)getSceneElementWithID: (NSString *)sceneElementID
{
    return [self getAdapterForID: sceneElementID];
}

-(NSArray *)getSceneElements
{
    return [self getAdapters];
}

-(NSArray *)getSceneElementsWithFilter: (id<LSFSDKLightingItemFilter>)filter
{
    return [self getSceneElementsCollectionWithFilter: filter];
}

-(NSArray *)getSceneElementsCollectionWithFilter: (id<LSFSDKLightingItemFilter>)filter
{
    return [self getAdaptersWithFilter: filter];
}

-(NSArray *)removeAllSceneElements
{
    return [self removeAllAdapters];
}

-(LSFSDKSceneElement *)removeSceneElementWithID: (NSString *)sceneElementID
{
    return [self removeAdapterWithID: sceneElementID];
}

-(LSFSceneElementDataModelV2 *)getModelWithID: (NSString *)sceneElementID
{
    LSFSDKSceneElement *sceneElement = [self getAdapterForID: sceneElementID];
    return (sceneElement != nil ? [sceneElement getSceneElementDataModel] : nil);
}

/*
 * Overriden functions from base class
 */
-(void)sendInitializedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item trackingID: (LSFSDKTrackingID *)trackingID
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKSceneElementDelegate)] && [item isKindOfClass: [LSFSDKSceneElement class]])
    {
        id<LSFSDKSceneElementDelegate> sceneElementDelegate = (id<LSFSDKSceneElementDelegate>)delegate;
        LSFSDKSceneElement *sceneElement = (LSFSDKSceneElement *)item;
        [sceneElementDelegate onSceneElementInitializedWithTrackingID: trackingID andSceneElement: sceneElement];
    }
}

-(void)sendChangedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKSceneElementDelegate)] && [item isKindOfClass: [LSFSDKSceneElement class]])
    {
        id<LSFSDKSceneElementDelegate> sceneElementDelegate = (id<LSFSDKSceneElementDelegate>)delegate;
        LSFSDKSceneElement *sceneElement = (LSFSDKSceneElement *)item;
        [sceneElementDelegate onSceneElementChanged: sceneElement];
    }
}

-(void)sendRemovedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKSceneElementDelegate)] && [item isKindOfClass: [LSFSDKSceneElement class]])
    {
        id<LSFSDKSceneElementDelegate> sceneElementDelegate = (id<LSFSDKSceneElementDelegate>)delegate;
        LSFSDKSceneElement *sceneElement = (LSFSDKSceneElement *)item;
        [sceneElementDelegate onSceneElementRemoved: sceneElement];
    }
}

-(void)sendErrorEvent: (id<LSFSDKLightingDelegate>)delegate errorEvent: (LSFSDKLightingItemErrorEvent *)errorEvent
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKSceneElementDelegate)])
    {
        id<LSFSDKSceneElementDelegate> sceneElementDelegate = (id<LSFSDKSceneElementDelegate>)delegate;
        [sceneElementDelegate onSceneElementError: errorEvent];
    }
}

@end
