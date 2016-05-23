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

#import "LSFSDKLightingItemCollectionManager.h"
#import "LSFSDKLightingSystemManager.h"

@implementation LSFSDKLightingItemCollectionManager

-(id)initWithLightingSystemManager: (LSFSDKLightingSystemManager *)lightingSystemManager;
{
    self = [super initWithLightingSystemManager: lightingSystemManager];

    if (self)
    {
        itemAdapters = [[NSMutableDictionary alloc] init];
    }

    return self;
}

-(BOOL)hasID: (NSString *)itemID
{
    return ([itemAdapters objectForKey: itemID] != nil);
}

-(NSArray *)getIDArray
{
    return [itemAdapters allKeys];
}

-(unsigned int)size
{
    return (unsigned int)[itemAdapters count];
}

-(id)getAdapterForID: (NSString *)itemID
{
    return [itemAdapters valueForKey: itemID];
}

-(NSArray *)removeAllAdapters
{
    NSMutableArray *list = [[NSMutableArray alloc] initWithCapacity: [self size]];
    NSMutableArray *keysToDelete = [[NSMutableArray alloc] initWithCapacity: [itemAdapters count]];
    NSEnumerator *valueEnumerator = [itemAdapters objectEnumerator];

    id value;
    while ((value = [valueEnumerator nextObject]))
    {
        [list addObject: value];
        [self sendRemovedEvent: value];
        [keysToDelete addObjectsFromArray: [itemAdapters allKeysForObject: value]];
    }

    [itemAdapters removeObjectsForKeys: keysToDelete];

    return list;
}

-(id)removeAdapterWithID: (NSString *)itemID
{
    id item = [itemAdapters valueForKey: itemID];
    [itemAdapters removeObjectForKey: itemID];
    [self sendRemovedEvent: item];
    return item;
}

-(NSArray *)getAdapters
{
    return [itemAdapters allValues];
}

-(NSArray *)getAdaptersWithFilter: (id<LSFSDKLightingItemFilter>)filter
{
    if (filter != nil)
    {
        NSMutableArray *filteredArray = [[NSMutableArray alloc] init];

        for (id item in [itemAdapters allValues])
        {
            if ([filter passes: item])
            {
                [filteredArray addObject: item];
            }
        }

        return [NSArray arrayWithArray: filteredArray];
    }
    else
    {
        return [self getAdapters];
    }
}

-(void)sendInitializedEvent: (NSString *)itemID
{
    [self sendInitializedEvent: itemID withTrackingID: nil];
}

-(void)sendInitializedEvent: (NSString *)itemID withTrackingID: (LSFSDKTrackingID *)trackingID
{
    [self processPendingAdditions];
    [self processPendingRemovals];

    for (id<LSFSDKLightingDelegate> delegate in delegates)
    {
        [self sendInitializedEvent: delegate item: [self getAdapterForID: itemID] trackingID: trackingID];
    }
}

-(void)sendChangedEvent: (NSString *)itemID
{
    [self processPendingAdditions];
    [self processPendingRemovals];

    for (id<LSFSDKLightingDelegate> delegate in delegates)
    {
        [self sendChangedEvent: delegate item: [self getAdapterForID: itemID]];
    }
}

-(void)sendRemovedEvent: (id)item
{
    [self processPendingAdditions];
    [self processPendingRemovals];

    for (id<LSFSDKLightingDelegate> delegate in delegates)
    {
        [self sendRemovedEvent: delegate item: item];
    }
}

-(void)sendErrorEvent: (NSString *)errorName statusCode: (lsf::LSFResponseCode)responseCode
{
    [self sendErrorEvent: errorName statusCode: responseCode itemID: nil];
}

-(void)sendErrorEvent: (NSString *)errorName statusCode: (lsf::LSFResponseCode)responseCode itemID: (NSString *)itemID
{
    [self sendErrorEvent: [[LSFSDKLightingItemErrorEvent alloc] initWithName: errorName responseCode: responseCode itemID: itemID andTrackingID: nil]];
}

-(void)sendErrorEvent: (NSString *)errorName statusCode: (lsf::LSFResponseCode)responseCode itemID: (NSString *)itemID withTrackingID: (LSFSDKTrackingID *)trackingID
{
    [self sendErrorEvent: [[LSFSDKLightingItemErrorEvent alloc] initWithName: errorName responseCode: responseCode itemID: itemID andTrackingID: trackingID]];
}

-(void)sendErrorEvent: (LSFSDKLightingItemErrorEvent *)errorEvent
{
    [self processPendingAdditions];
    [self processPendingRemovals];

    for (id<LSFSDKLightingDelegate> delegate in delegates)
    {
        [self sendErrorEvent: delegate errorEvent: errorEvent];
    }
}

-(void)postSendErrorEvent: (id<LSFSDKLightingDelegate>)delegate errorEvent: (LSFSDKLightingItemErrorEvent *)errorEvent
{
    dispatch_async(manager.dispatchQueue, ^{
        [self sendErrorEvent: delegate errorEvent: errorEvent];
    });
}

-(void)sendInitializedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item trackingID: (LSFSDKTrackingID *)trackingID
{
    @throw [NSException exceptionWithName: NSInternalInconsistencyException reason: [NSString stringWithFormat:@"You must override %@ in a subclass", NSStringFromSelector(_cmd)] userInfo: nil];
}

-(void)sendChangedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item
{
    @throw [NSException exceptionWithName: NSInternalInconsistencyException reason: [NSString stringWithFormat:@"You must override %@ in a subclass", NSStringFromSelector(_cmd)] userInfo: nil];
}

-(void)sendRemovedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item
{
    @throw [NSException exceptionWithName: NSInternalInconsistencyException reason: [NSString stringWithFormat:@"You must override %@ in a subclass", NSStringFromSelector(_cmd)] userInfo: nil];
}

-(void)sendErrorEvent: (id<LSFSDKLightingDelegate>)delegate errorEvent: (LSFSDKLightingItemErrorEvent *)errorEvent
{
    @throw [NSException exceptionWithName: NSInternalInconsistencyException reason: [NSString stringWithFormat:@"You must override %@ in a subclass", NSStringFromSelector(_cmd)] userInfo: nil];
}

@end
