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

#import "LSFSDKTransitionEffectCollectionManager.h"
#import "../initializer/LSFSDKTransitionEffect+Init.h"

@implementation LSFSDKTransitionEffectCollectionManager

-(id)initWithLightingSystemManager: (LSFSDKLightingSystemManager *)lightingSystemManager
{
    self = [super initWithLightingSystemManager: lightingSystemManager];

    if (self)
    {
        //Intentionally left blank
    }

    return self;
}

-(void)addTransitionEffectDelegate: (id<LSFSDKTransitionEffectDelegate>)transitionEffectDelegate
{
    [self addDelegate: transitionEffectDelegate];
}

-(void)removeTransitionEffectDelegate: (id<LSFSDKTransitionEffectDelegate>)transitionEffectDelegate
{
    [self removeDelegate: transitionEffectDelegate];
}

-(LSFSDKTransitionEffect *)addTransitionEffectWithID: (NSString *)transitionEffectID
{
    LSFSDKTransitionEffect *newTransitionEffect = [[LSFSDKTransitionEffect alloc] initWithTransitionEffectID: transitionEffectID];
    return [self addTransitionEffectWithID: transitionEffectID transitionEffect: newTransitionEffect];
}

-(LSFSDKTransitionEffect *)addTransitionEffectWithID: (NSString *)transitionEffectID transitionEffect: (LSFSDKTransitionEffect *)transitionEffect
{
    [itemAdapters setValue: transitionEffect forKey: transitionEffectID];
    return transitionEffect;
}

-(LSFSDKTransitionEffect *)getTransitionEffectWithID: (NSString *)transitionEffectID
{
    return [self getAdapterForID: transitionEffectID];
}

-(NSArray *)getTransitionEffects
{
    return [self getAdapters];
}

-(NSArray *)getTransitionEffectsWithFilter: (id<LSFSDKLightingItemFilter>)filter
{
    return [self getTransitionEffectCollectionWithFilter: filter];
}

-(NSArray *)getTransitionEffectCollectionWithFilter: (id<LSFSDKLightingItemFilter>)filter
{
    return [self getAdaptersWithFilter: filter];
}

-(NSArray *)removeAllTransitionEffects
{
    return [self removeAllAdapters];
}

-(LSFSDKTransitionEffect *)removeTransitionEffectWithID: (NSString *)transitionEffectID
{
    return [self removeAdapterWithID: transitionEffectID];
}

-(LSFTransitionEffectDataModelV2 *)getModelWithID: (NSString *)transitionEffectID
{
    LSFSDKTransitionEffect *transitionEffect = [self getAdapterForID: transitionEffectID];
    return (transitionEffect != nil ? [transitionEffect getTransitionEffectDataModel] : nil);
}

/*
 * Overriden functions from base class
 */
-(void)sendInitializedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item trackingID: (LSFSDKTrackingID *)trackingID
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKTransitionEffectDelegate)] && [item isKindOfClass: [LSFSDKTransitionEffect class]])
    {
        id<LSFSDKTransitionEffectDelegate> transitionEffectDelegate = (id<LSFSDKTransitionEffectDelegate>)delegate;
        LSFSDKTransitionEffect *transitionEffect = (LSFSDKTransitionEffect *)item;
        [transitionEffectDelegate onTransitionEffectInitializedWithTrackingID: trackingID andTransitionEffect: transitionEffect];
    }
}

-(void)sendChangedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKTransitionEffectDelegate)] && [item isKindOfClass: [LSFSDKTransitionEffect class]])
    {
        id<LSFSDKTransitionEffectDelegate> transitionEffectDelegate = (id<LSFSDKTransitionEffectDelegate>)delegate;
        LSFSDKTransitionEffect *transitionEffect = (LSFSDKTransitionEffect *)item;
        [transitionEffectDelegate onTransitionEffectChanged: transitionEffect];
    }
}

-(void)sendRemovedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKTransitionEffectDelegate)] && [item isKindOfClass: [LSFSDKTransitionEffect class]])
    {
        id<LSFSDKTransitionEffectDelegate> transitionEffectDelegate = (id<LSFSDKTransitionEffectDelegate>)delegate;
        LSFSDKTransitionEffect *transitionEffect = (LSFSDKTransitionEffect *)item;
        [transitionEffectDelegate onTransitionEffectRemoved: transitionEffect];
    }
}

-(void)sendErrorEvent: (id<LSFSDKLightingDelegate>)delegate errorEvent: (LSFSDKLightingItemErrorEvent *)errorEvent
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKTransitionEffectDelegate)])
    {
        id<LSFSDKTransitionEffectDelegate> transitionEffectDelegate = (id<LSFSDKTransitionEffectDelegate>)delegate;
        [transitionEffectDelegate onTransitionEffectError: errorEvent];
    }
}

@end
