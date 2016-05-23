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

#import "LSFSDKPulseEffectCollectionManager.h"
#import "../initializer/LSFSDKPulseEffect+Init.h"

@implementation LSFSDKPulseEffectCollectionManager

-(id)initWithLightingSystemManager: (LSFSDKLightingSystemManager *)lightingSystemManager
{
    self = [super initWithLightingSystemManager: lightingSystemManager];

    if (self)
    {
        //Intentionally left blank
    }

    return self;
}

-(void)addPulseEffectDelegate: (id<LSFSDKPulseEffectDelegate>)pulseEffectDelegate
{
    [self addDelegate: pulseEffectDelegate];
}

-(void)removePulseEffectDelegate: (id<LSFSDKPulseEffectDelegate>)pulseEffectDelegate
{
    [self removeDelegate: pulseEffectDelegate];
}

-(LSFSDKPulseEffect *)addPulseEffectWithID: (NSString *)pulseEffectID
{
    LSFSDKPulseEffect *newPulseEffect = [[LSFSDKPulseEffect alloc] initWithPulseEffectID: pulseEffectID];
    return [self addPulseEffectWithID: pulseEffectID pulseEffect: newPulseEffect];
}

-(LSFSDKPulseEffect *)addPulseEffectWithID: (NSString *)pulseEffectID pulseEffect: (LSFSDKPulseEffect *)pulseEffect
{
    [itemAdapters setValue: pulseEffect forKey: pulseEffectID];
    return pulseEffect;
}

-(LSFSDKPulseEffect *)getPulseEffectWithID: (NSString *)pulseEffectID
{
    return [self getAdapterForID: pulseEffectID];
}

-(NSArray *)getPulseEffects
{
    return [self getAdapters];
}

-(NSArray *)getPulseEffectsWithFilter: (id<LSFSDKLightingItemFilter>)filter
{
    return [self getPulseEffectsCollectionWithFilter: filter];
}

-(NSArray *)getPulseEffectsCollectionWithFilter: (id<LSFSDKLightingItemFilter>)filter
{
    return [self getAdaptersWithFilter: filter];
}

-(NSArray *)removeAllPulseEffects
{
    return [self removeAllAdapters];
}

-(LSFSDKPulseEffect *)removePulseEffectWithID: (NSString *)pulseEffectID
{
    return [self removeAdapterWithID: pulseEffectID];
}

-(LSFPulseEffectDataModelV2 *)getModelWithID: (NSString *)pulseEffectID
{
    LSFSDKPulseEffect *pulseEffect = [self getAdapterForID: pulseEffectID];
    return (pulseEffect != nil ? [pulseEffect getPulseEffectDataModel] : nil);
}

/*
 * Overriden functions from base class
 */
-(void)sendInitializedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item trackingID: (LSFSDKTrackingID *)trackingID
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKPulseEffectDelegate)] && [item isKindOfClass: [LSFSDKPulseEffect class]])
    {
        id<LSFSDKPulseEffectDelegate> pulseEffectDelegate = (id<LSFSDKPulseEffectDelegate>)delegate;
        LSFSDKPulseEffect *pulseEffect = (LSFSDKPulseEffect *)item;
        [pulseEffectDelegate onPulseEffectInitializedWithTrackingID: trackingID andPulseEffect: pulseEffect];
    }
}

-(void)sendChangedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKPulseEffectDelegate)] && [item isKindOfClass: [LSFSDKPulseEffect class]])
    {
        id<LSFSDKPulseEffectDelegate> pulseEffectDelegate = (id<LSFSDKPulseEffectDelegate>)delegate;
        LSFSDKPulseEffect *pulseEffect = (LSFSDKPulseEffect *)item;
        [pulseEffectDelegate onPulseEffectChanged: pulseEffect];
    }
}

-(void)sendRemovedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKPulseEffectDelegate)] && [item isKindOfClass: [LSFSDKPulseEffect class]])
    {
        id<LSFSDKPulseEffectDelegate> pulseEffectDelegate = (id<LSFSDKPulseEffectDelegate>)delegate;
        LSFSDKPulseEffect *pulseEffect = (LSFSDKPulseEffect *)item;
        [pulseEffectDelegate onPulseEffectRemoved: pulseEffect];
    }
}

-(void)sendErrorEvent: (id<LSFSDKLightingDelegate>)delegate errorEvent: (LSFSDKLightingItemErrorEvent *)errorEvent
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKPulseEffectDelegate)])
    {
        id<LSFSDKPulseEffectDelegate> pulseEffectDelegate = (id<LSFSDKPulseEffectDelegate>)delegate;
        [pulseEffectDelegate onPulseEffectError: errorEvent];
    }
}

@end
