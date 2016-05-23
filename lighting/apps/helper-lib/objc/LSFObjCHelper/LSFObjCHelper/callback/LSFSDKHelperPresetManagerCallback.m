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

#import "LSFSDKHelperPresetManagerCallback.h"
#import "LSFSDKLightingSystemManager.h"
#import "LSFSDKAllJoynManager.h"
#import "LSFConstants.h"

@interface LSFSDKHelperPresetManagerCallback()

@property (nonatomic, strong) LSFSDKLightingSystemManager *manager;
@property (nonatomic, strong) NSMutableDictionary *creationTrackingIDs;

-(void)postProcessPresetID: (NSString *)presetID;
-(void)postUpdatePresetID: (NSString *)presetID;
-(void)postUpdatePresetNameForID: (NSString *)presetID andPresetName: (NSString *)presetName;
-(void)postUpdatePresetForID: (NSString *)presetID withPreset: (LSFLampState *)preset;
-(void)postDeletePresetWithIDs: (NSArray *)presetIDs;
-(void)postSendPresetChanged: (NSString *)presetID;
-(void)postSendPresetInitialized: (NSString *)presetID;

@end

@implementation LSFSDKHelperPresetManagerCallback

@synthesize manager = _manager;
@synthesize creationTrackingIDs = _creationTrackingIDs;

-(id)initWithLightingSystemManager: (LSFSDKLightingSystemManager *)manager
{
    self = [super init];

    if (self)
    {
        self.manager = manager;
        self.creationTrackingIDs = [[NSMutableDictionary alloc] init];
    }

    return self;
}

/*
 * Implementation of LSFPresetManagerCallbackDelegate
 */
-(void)getPresetReplyWithCode: (LSFResponseCode)rc presetID: (NSString *)presetID andPreset: (LSFLampState *)preset
{
    if (rc != LSF_OK)
    {
        [[self.manager presetCollectionManager] sendErrorEvent: @"getPresetReplyCB" statusCode: rc itemID: presetID];
    }

    [self postUpdatePresetForID: presetID withPreset: preset];
}

-(void)getAllPresetIDsReplyWithCode: (LSFResponseCode)rc andPresetIDs: (NSArray *)presetIDs
{
    if (rc != LSF_OK)
    {
        [[self.manager presetCollectionManager] sendErrorEvent: @"getAllPresetIDsReplyCB" statusCode: rc];
    }

    for (NSString *presetID in presetIDs)
    {
        [self postProcessPresetID: presetID];
    }
}

-(void)getPresetNameReplyWithCode: (LSFResponseCode)rc presetID: (NSString *)presetID language: (NSString *)language andPresetName: (NSString *)presetName
{
    if (rc != LSF_OK)
    {
        [[self.manager presetCollectionManager] sendErrorEvent: @"getPresetNameReplyCB" statusCode: rc itemID: presetID];
    }

    [self postUpdatePresetNameForID: presetID andPresetName: presetName];
}

-(void)setPresetNameReplyWithCode: (LSFResponseCode)rc presetID: (NSString *)presetID andLanguage: (NSString *)language
{
    if (rc != LSF_OK)
    {
        [[self.manager presetCollectionManager] sendErrorEvent: @"setPresetNameReplyCB" statusCode: rc itemID: presetID];
    }

    //Currently do nothing
}

-(void)presetsNameChanged: (NSArray *)presetIDs
{
    dispatch_async(self.manager.dispatchQueue, ^{
        BOOL containsNewIDs = NO;

        for (NSString *presetID in presetIDs)
        {
            if ([[self.manager presetCollectionManager] hasID: presetID])
            {
                [[LSFSDKAllJoynManager getPresetManager] getPresetNameWithID: presetID];
            }
            else
            {
                containsNewIDs = YES;
            }
        }

        if (containsNewIDs)
        {
            [[LSFSDKAllJoynManager getPresetManager] getAllPresetIDs];
        }
    });
}

-(void)createPresetReplyWithCode: (LSFResponseCode)rc andPresetID: (NSString *)presetID
{
    if (rc != LSF_OK)
    {
        [[self.manager presetCollectionManager] sendErrorEvent: @"createPresetReplyCB" statusCode: rc itemID: presetID];
    }

    //Currently do nothing
}

-(void)createPresetTrackingReplyWithCode: (LSFResponseCode)rc presetID: (NSString *)presetID andTrackingID: (unsigned int)trackingID
{
    if (rc != LSF_OK)
    {
        [[self.manager presetCollectionManager] sendErrorEvent: @"createPresetTrackingReplyCB" statusCode: rc itemID: presetID];
    }
    else
    {
        LSFSDKTrackingID *myTrackingID = [[LSFSDKTrackingID alloc] initWithValue: trackingID];
        [self.creationTrackingIDs setValue: myTrackingID forKey: presetID];
    }
}

-(void)presetsCreated: (NSArray *)presetIDs
{
    [[LSFSDKAllJoynManager getPresetManager] getAllPresetIDs];
}

-(void)updatePresetReplyWithCode: (LSFResponseCode)rc andPresetID: (NSString *)presetID
{
    if (rc != LSF_OK)
    {
        [[self.manager presetCollectionManager] sendErrorEvent: @"updatePresetReplyCB" statusCode: rc itemID: presetID];
    }

    //Currently do nothing
}

-(void)presetsUpdated: (NSArray *)presetIDs
{
    for (NSString *presetID in presetIDs)
    {
        [[LSFSDKAllJoynManager getPresetManager] getPresetWithID: presetID];
    }
}

-(void)deletePresetReplyWithCode: (LSFResponseCode)rc andPresetID: (NSString *)presetID
{
    if (rc != LSF_OK)
    {
        [[self.manager presetCollectionManager] sendErrorEvent: @"deletePresetReplyCB" statusCode: rc itemID: presetID];
    }

    //Currently do nothing
}

-(void)presetsDeleted: (NSArray *)presetIDs
{
    [self postDeletePresetWithIDs: presetIDs];
}

-(void)getDefaultLampStateReplyWithCode: (LSFResponseCode)rc andLampState: (LSFLampState *)defaultLampState
{
    if (rc != LSF_OK)
    {
        [[self.manager presetCollectionManager] sendErrorEvent: @"getDefaultLampStateReplyCB" statusCode: rc];
    }

    //Currently do nothing
}

-(void)setDefaultLampStateReplyWithCode: (LSFResponseCode)rc
{
    if (rc != LSF_OK)
    {
        [[self.manager presetCollectionManager] sendErrorEvent: @"setDefaultLampStateReplyCB" statusCode: rc];
    }

    //Currently do nothing
}

-(void)defaultLampStateChanged
{
    //Currently do nothing
}

/*
 * Private function implementations
 */
-(void)postProcessPresetID: (NSString *)presetID
{
    dispatch_async(self.manager.dispatchQueue, ^{
        BOOL hasPresetID = [self.manager.presetCollectionManager hasID: presetID];
        if (!hasPresetID)
        {
            [self postUpdatePresetID: presetID];
            [[LSFSDKAllJoynManager getPresetManager] getPresetNameWithID: presetID];
            [[LSFSDKAllJoynManager getPresetManager] getPresetWithID: presetID];
        }
    });
}

-(void)postUpdatePresetID: (NSString *)presetID
{
    dispatch_async(self.manager.dispatchQueue, ^{
        if (![self.manager.presetCollectionManager hasID: presetID])
        {
            [self.manager.presetCollectionManager addPresetWithID: presetID];
        }
    });

    [self postSendPresetChanged: presetID];
}

-(void)postUpdatePresetNameForID: (NSString *)presetID andPresetName: (NSString *)presetName
{
    dispatch_async(self.manager.dispatchQueue, ^{
        LSFPresetModel *presetModel = [self.manager.presetCollectionManager getModelWithID: presetID];

        if (presetModel != nil)
        {
            BOOL wasInitialized = [presetModel isInitialized];
            presetModel.name = [NSString stringWithString: presetName];

            if (wasInitialized != [presetModel isInitialized])
            {
                [self postSendPresetInitialized: presetID];
            }
        }
    });

    [self postSendPresetChanged: presetID];
}

-(void)postUpdatePresetForID: (NSString *)presetID withPreset: (LSFLampState *)preset
{
    dispatch_async(self.manager.dispatchQueue, ^{
        LSFConstants *constants = [LSFConstants getConstants];
        LSFPresetModel *presetModel = [self.manager.presetCollectionManager getModelWithID: presetID];

        if (presetModel != nil)
        {
            BOOL wasInitialized = [presetModel isInitialized];

            LSFLampState *newState = [[LSFLampState alloc] initWithOnOff: preset.onOff brightness: [constants unscaleLampStateValue: preset.brightness withMax: 100] hue: [constants unscaleLampStateValue: preset.hue withMax: 360] saturation: [constants unscaleLampStateValue: preset.saturation withMax: 100] colorTemp: [constants unscaleColorTemp: preset.colorTemp]];
            [presetModel setState: newState];

            if (wasInitialized != [presetModel isInitialized])
            {
                [self postSendPresetInitialized: presetID];
            }
        }
    });

    [self postSendPresetChanged: presetID];
}

-(void)postDeletePresetWithIDs: (NSArray *)presetIDs
{
    dispatch_async(self.manager.dispatchQueue, ^{
        for (NSString *presetID in presetIDs)
        {
            [self.manager.presetCollectionManager removePresetWithID: presetID];
        }
    });
}

-(void)postSendPresetChanged: (NSString *)presetID
{
    dispatch_async(self.manager.dispatchQueue, ^{
        [self.manager.presetCollectionManager sendChangedEvent: presetID];
    });
}

-(void)postSendPresetInitialized: (NSString *)presetID
{
    dispatch_async(self.manager.dispatchQueue, ^{
        LSFSDKTrackingID *trackingID = [self.creationTrackingIDs valueForKey: presetID];

        if (trackingID != nil)
        {
            [self.creationTrackingIDs removeObjectForKey: presetID];
        }

        [self.manager.presetCollectionManager sendInitializedEvent: presetID withTrackingID: trackingID];
    });
}

@end
