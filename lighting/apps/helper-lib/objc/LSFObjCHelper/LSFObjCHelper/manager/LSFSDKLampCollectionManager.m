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

#import "LSFSDKLampCollectionManager.h"
#import "../initializer/LSFSDKLamp+Init.h"

@implementation LSFSDKLampCollectionManager

-(id)initWithLightingSystemManager: (LSFSDKLightingSystemManager *)lightingSystemManager
{
    self = [super initWithLightingSystemManager: lightingSystemManager];

    if (self)
    {
        lampIDs = [[NSMutableArray alloc] init];
    }

    return self;
}

-(void)addLampDelegate: (id<LSFSDKLampDelegate>)lampDelegate
{
    [self addDelegate: lampDelegate];
}

-(void)removeLampDelegate: (id<LSFSDKLampDelegate>)lampDelegate
{
    [self removeDelegate: lampDelegate];
}

-(LSFSDKLamp *)addLampWithID: (NSString *)lampID
{
    LSFSDKLamp *newLamp = [[LSFSDKLamp alloc] initWithLampID: lampID];
    return [self addLampWithID: lampID lamp: newLamp];
}

-(LSFSDKLamp *)addLampWithID: (NSString *)lampID lamp: (LSFSDKLamp *)lamp
{
    [itemAdapters setValue: lamp forKey: lampID];
    [lampIDs addObject: lampID];
    return lamp;
}

-(LSFSDKLamp *)getLampWithID: (NSString *)lampID
{
    return [self getAdapterForID: lampID];
}

-(NSArray *)getLamps
{
    return [self getAdapters];
}

-(NSArray *)getLampsWithFilter: (id<LSFSDKLightingItemFilter>)filter
{
    return [self getLampsCollectionWithFilter: filter];
}

-(NSArray *)getLampsCollectionWithFilter: (id<LSFSDKLightingItemFilter>)filter
{
    return [self getAdaptersWithFilter: filter];
}

-(NSArray *)removeAllLamps
{
    return [self removeAllAdapters];
}

-(LSFSDKLamp *)removeLampWithID: (NSString *)lampID
{
    [lampIDs removeObject: lampID];
    return [self removeAdapterWithID: lampID];
}

-(LSFLampModel *)getModelWithID: (NSString *)lampID
{
    LSFSDKLamp *lamp = [self getAdapterForID: lampID];
    return (lamp != nil ? [lamp getLampDataModel] : nil);
}

/*
 * Overriden functions from base class
 */
-(void)sendInitializedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item trackingID: (LSFSDKTrackingID *)trackingID
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKLampDelegate)] && [item isKindOfClass: [LSFSDKLamp class]])
    {
        id<LSFSDKLampDelegate> lampDelegate = (id<LSFSDKLampDelegate>)delegate;
        LSFSDKLamp *lamp = (LSFSDKLamp *)item;
        [lampDelegate onLampInitialized: lamp];
    }
}

-(void)sendChangedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKLampDelegate)] && [item isKindOfClass: [LSFSDKLamp class]])
    {
        id<LSFSDKLampDelegate> lampDelegate = (id<LSFSDKLampDelegate>)delegate;
        LSFSDKLamp *lamp = (LSFSDKLamp *)item;
        [lampDelegate onLampChanged: lamp];
    }
}

-(void)sendRemovedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKLampDelegate)] && [item isKindOfClass: [LSFSDKLamp class]])
    {
        id<LSFSDKLampDelegate> lampDelegate = (id<LSFSDKLampDelegate>)delegate;
        LSFSDKLamp *lamp = (LSFSDKLamp *)item;
        [lampDelegate onLampRemoved: lamp];
    }
}

-(void)sendErrorEvent: (id<LSFSDKLightingDelegate>)delegate errorEvent: (LSFSDKLightingItemErrorEvent *)errorEvent
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKLampDelegate)])
    {
        id<LSFSDKLampDelegate> lampDelegate = (id<LSFSDKLampDelegate>)delegate;
        [lampDelegate onLampError: errorEvent];
    }
}

@end
