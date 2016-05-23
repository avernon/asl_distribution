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

#import "LSFSDKPresetCollectionManager.h"
#import "../initializer/LSFSDKPreset+Init.h"

@implementation LSFSDKPresetCollectionManager

-(id)initWithLightingSystemManager: (LSFSDKLightingSystemManager *)lightingSystemManager
{
    self = [super initWithLightingSystemManager: lightingSystemManager];

    if (self)
    {
        //Intentionally left blank
    }

    return self;
}

-(void)addPresetDelegate: (id<LSFSDKPresetDelegate>)presetDelegate
{
    [self addDelegate: presetDelegate];
}

-(void)removePresetDelegate: (id<LSFSDKPresetDelegate>)presetDelegate
{
    [self removeDelegate: presetDelegate];
}

-(LSFSDKPreset *)addPresetWithID: (NSString *)presetID
{
    LSFSDKPreset *newPreset = [[LSFSDKPreset alloc] initWithPresetID: presetID];
    return [self addPresetWithID: presetID preset: newPreset];
}

-(LSFSDKPreset *)addPresetWithID: (NSString *)presetID preset: (LSFSDKPreset *)preset
{
    [itemAdapters setValue: preset forKey: presetID];
    return preset;
}

-(LSFSDKPreset *)getPresetWithID: (NSString *)presetID
{
    return [self getAdapterForID: presetID];
}

-(NSArray *)getPresets
{
    return [self getAdapters];
}

-(NSArray *)getPresetsWithFilter: (id<LSFSDKLightingItemFilter>)filter
{
    return [self getPresetsCollectionWithFilter: filter];
}

-(NSArray *)getPresetsCollectionWithFilter: (id<LSFSDKLightingItemFilter>)filter
{
    return [self getAdaptersWithFilter: filter];
}

-(NSArray *)removeAllPresets
{
    return [self removeAllAdapters];
}

-(LSFSDKPreset *)removePresetWithID: (NSString *)presetID
{
    return [self removeAdapterWithID: presetID];
}

-(LSFPresetModel *)getModelWithID: (NSString *)presetID
{
    LSFSDKPreset *preset = [self getAdapterForID: presetID];
    return (preset != nil ? [preset getPresetDataModel] : nil);
}

/*
 * Overriden functions from base class
 */
-(void)sendInitializedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item trackingID: (LSFSDKTrackingID *)trackingID
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKPresetDelegate)] && [item isKindOfClass: [LSFSDKPreset class]])
    {
        id<LSFSDKPresetDelegate> presetDelegate = (id<LSFSDKPresetDelegate>)delegate;
        LSFSDKPreset *preset = (LSFSDKPreset *)item;
        [presetDelegate onPresetInitializedWithTrackingID: trackingID andPreset: preset];
    }
}

-(void)sendChangedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKPresetDelegate)] && [item isKindOfClass: [LSFSDKPreset class]])
    {
        id<LSFSDKPresetDelegate> presetDelegate = (id<LSFSDKPresetDelegate>)delegate;
        LSFSDKPreset *preset = (LSFSDKPreset *)item;
        [presetDelegate onPresetChanged: preset];
    }
}

-(void)sendRemovedEvent: (id<LSFSDKLightingDelegate>)delegate item: (id)item
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKPresetDelegate)] && [item isKindOfClass: [LSFSDKPreset class]])
    {
        id<LSFSDKPresetDelegate> presetDelegate = (id<LSFSDKPresetDelegate>)delegate;
        LSFSDKPreset *preset = (LSFSDKPreset *)item;
        [presetDelegate onPresetRemoved: preset];
    }
}

-(void)sendErrorEvent: (id<LSFSDKLightingDelegate>)delegate errorEvent: (LSFSDKLightingItemErrorEvent *)errorEvent
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKPresetDelegate)])
    {
        id<LSFSDKPresetDelegate> presetDelegate = (id<LSFSDKPresetDelegate>)delegate;
        [presetDelegate onPresetError: errorEvent];
    }
}

@end
