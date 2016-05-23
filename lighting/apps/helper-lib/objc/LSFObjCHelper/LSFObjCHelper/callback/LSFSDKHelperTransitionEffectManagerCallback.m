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

#import "LSFSDKHelperTransitionEffectManagerCallback.h"
#import "LSFSDKLightingSystemManager.h"
#import "LSFSDKAllJoynManager.h"
#import "LSFConstants.h"

@interface LSFSDKHelperTransitionEffectManagerCallback()

@property (nonatomic, strong) LSFSDKLightingSystemManager *manager;
@property (nonatomic, strong) NSMutableDictionary *creationTrackingIDs;

-(void)postProcessTransitionEffectID: (NSString *)transitionEffectID;
-(void)postUpdateTransitionEffectID: (NSString *)transitionEffectID;
-(void)postUpdateTransitionEffectNameForID: (NSString *)transitionEffectID transitionEffectName: (NSString *)transitionEffectName;
-(void)postUpdateTransitionEffectID: (NSString *)transitionEffectID transitionEffect: (LSFTransitionEffectV2 *)transitionEffect;
-(void)postDeleteTransitionEffectIDs: (NSArray *)transitionEffectIDs;
-(void)postSendTransitionEffectChanged: (NSString *)transitionEffectID;
-(void)postSendTransitionEffectInitialized: (NSString *)transitionEffectID;

@end

@implementation LSFSDKHelperTransitionEffectManagerCallback

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
 * Implementation of LSFTransitionEffectManagerCallbackDelegate
 */
-(void)getTransitionEffectReplyWithCode: (LSFResponseCode)rc transitionEffectID: (NSString *)transitionEffectID andTransitionEffect: (LSFTransitionEffectV2 *)transitionEffect
{
    if (rc != LSF_OK)
    {
        [self.manager.transitionEffectCollectionManager sendErrorEvent: @"getTransitionEffectReplyCB" statusCode: rc itemID: transitionEffectID];
    }

    [self postUpdateTransitionEffectID: transitionEffectID transitionEffect: transitionEffect];
}

-(void)applyTransitionEffectOnLampsReplyWithCode: (LSFResponseCode)rc transitionEffectID: (NSString *)transitionEffectID andLampIDs: (NSArray *)lampIDs
{
    if (rc != LSF_OK)
    {
        [self.manager.transitionEffectCollectionManager sendErrorEvent: @"applyTransitionEffectOnLampsReplyCB" statusCode: rc itemID: transitionEffectID];
    }
}

-(void)applyTransitionEffectOnLampGroupsReplyWithCode: (LSFResponseCode)rc transitionEffectID: (NSString *)transitionEffectID andLampGroupIDs: (NSArray *)lampGroupIDs
{
    if (rc != LSF_OK)
    {
        [self.manager.transitionEffectCollectionManager sendErrorEvent: @"applyTransitionEffectOnLampGroupsReplyCB" statusCode: rc itemID: transitionEffectID];
    }
}

-(void)getAllTransitionEffectIDsReplyWithCode: (LSFResponseCode)rc transitionEffectIDs: (NSArray *)transitionEffectIDs
{
    if (rc != LSF_OK)
    {
        [self.manager.transitionEffectCollectionManager sendErrorEvent: @"getAllTransitionEffectIDsReplyCB" statusCode: rc];
    }

    for (NSString *transitionEffectID in transitionEffectIDs)
    {
        [self postProcessTransitionEffectID: transitionEffectID];
    }
}

-(void)getTransitionEffectNameReplyWithCode: (LSFResponseCode)rc transitionEffectID: (NSString *)transitionEffectID language: (NSString *)language andTransitionEffectName: (NSString *)transitionEffectName
{
    if (rc != LSF_OK)
    {
        [self.manager.transitionEffectCollectionManager sendErrorEvent: @"getTransitionEffectNameReplyCB" statusCode: rc itemID: transitionEffectID];
    }

    [self postUpdateTransitionEffectNameForID: transitionEffectID transitionEffectName: transitionEffectName];
}

-(void)setTransitionEffectNameReplyWithCode: (LSFResponseCode)rc transitionEffectID: (NSString *)transitionEffectID andLanguage: (NSString *)language
{
    if (rc != LSF_OK)
    {
        [self.manager.transitionEffectCollectionManager sendErrorEvent: @"setTransitionEffectNameReplyCB" statusCode: rc itemID: transitionEffectID];
    }

    [[LSFSDKAllJoynManager getTransitionEffectManager] getTransitionEffectNameWithID: transitionEffectID andLanguage: self.manager.defaultLanguage];
}

-(void)transitionEffectsNameChanged: (NSArray *)transitionEffectIDs
{
    dispatch_async(self.manager.dispatchQueue, ^{
        BOOL containsNewIDs = NO;

        for (NSString *transitionEffectID in transitionEffectIDs)
        {
            if ([self.manager.transitionEffectCollectionManager hasID: transitionEffectID])
            {
                [[LSFSDKAllJoynManager getTransitionEffectManager] getTransitionEffectNameWithID: transitionEffectID andLanguage: self.manager.defaultLanguage];
            }
            else
            {
                containsNewIDs = YES;
            }
        }

        if (containsNewIDs)
        {
            [[LSFSDKAllJoynManager getTransitionEffectManager] getAllTransitionEffectIDs];
        }
    });
}

-(void)createTransitionEffectReplyWithCode: (LSFResponseCode)rc transitionEffectID: (NSString *)transitionEffectID andTrackingID: (unsigned int)trackingID
{
    if (rc != LSF_OK)
    {
        [self.manager.transitionEffectCollectionManager sendErrorEvent: @"createTransitionEffectReplyCB" statusCode: rc itemID: transitionEffectID withTrackingID: [[LSFSDKTrackingID alloc] initWithValue:trackingID]];
    }
    else
    {
        LSFSDKTrackingID *myTrackingID = [[LSFSDKTrackingID alloc] initWithValue: trackingID];
        [self.creationTrackingIDs setValue: myTrackingID forKey: transitionEffectID];
    }
}

-(void)transitionEffectsCreated: (NSArray *)transitionEffectIDs
{
    [[LSFSDKAllJoynManager getTransitionEffectManager] getAllTransitionEffectIDs];
}

-(void)updateTransitionEffectReplyWithCode: (LSFResponseCode)rc andTransitionEffectID: (NSString *)transitionEffectID
{
    if (rc != LSF_OK)
    {
        [self.manager.transitionEffectCollectionManager sendErrorEvent: @"updateTransitionEffectReplyCB" statusCode: rc itemID: transitionEffectID];
    }
}

-(void)transitionEffectsUpdated: (NSArray *)transitionEffectIDs
{
    for (NSString *transitionEffectID in transitionEffectIDs)
    {
        [[LSFSDKAllJoynManager getTransitionEffectManager] getTransitionEffectWithID: transitionEffectID];
    }
}

-(void)deleteTransitionEffectReplyWithCode: (LSFResponseCode)rc andTransitionEffectID: (NSString *)transitionEffectID
{
    if (rc != LSF_OK)
    {
        [self.manager.transitionEffectCollectionManager sendErrorEvent: @"deleteTransitionEffectReplyCB" statusCode: rc itemID: transitionEffectID];
    }
}

-(void)transitionEffectsDeleted: (NSArray *)transitionEffectIDs
{
    [self postDeleteTransitionEffectIDs: transitionEffectIDs];
}

/*
 * Private function implementations
 */
-(void)postProcessTransitionEffectID: (NSString *)transitionEffectID
{
    dispatch_async(self.manager.dispatchQueue, ^{
        BOOL hasID = [self.manager.transitionEffectCollectionManager hasID: transitionEffectID];
        if (!hasID)
        {
            [self postUpdateTransitionEffectID: transitionEffectID];
            [[LSFSDKAllJoynManager getTransitionEffectManager] getTransitionEffectDataSetWithID: transitionEffectID andLanguage: self.manager.defaultLanguage];
        }
    });
}

-(void)postUpdateTransitionEffectID: (NSString *)transitionEffectID
{
    dispatch_async(self.manager.dispatchQueue, ^{
        BOOL hasID = [self.manager.transitionEffectCollectionManager hasID: transitionEffectID];
        if (!hasID)
        {
            [self.manager.transitionEffectCollectionManager addTransitionEffectWithID: transitionEffectID];
        }
    });

    [self postSendTransitionEffectChanged: transitionEffectID];
}

-(void)postUpdateTransitionEffectNameForID: (NSString *)transitionEffectID transitionEffectName: (NSString *)transitionEffectName
{
    dispatch_async(self.manager.dispatchQueue, ^{
        LSFTransitionEffectDataModelV2 *transitionEffectDataModel = [self.manager.transitionEffectCollectionManager getModelWithID: transitionEffectID];

        if (transitionEffectDataModel != nil)
        {
            BOOL wasInitialized = [transitionEffectDataModel isInitialized];
            transitionEffectDataModel.name = [NSString stringWithString: transitionEffectName];

            if (wasInitialized != [transitionEffectDataModel isInitialized])
            {
                [self postSendTransitionEffectInitialized: transitionEffectID];
            }
        }
    });

    [self postSendTransitionEffectChanged: transitionEffectID];
}

-(void)postUpdateTransitionEffectID: (NSString *)transitionEffectID transitionEffect: (LSFTransitionEffectV2 *)transitionEffect
{
    dispatch_async(self.manager.dispatchQueue, ^{
        LSFConstants *constants = [LSFConstants getConstants];
        LSFTransitionEffectDataModelV2 *transitionEffectDataModel = [self.manager.transitionEffectCollectionManager getModelWithID: transitionEffectID];

        if (transitionEffectDataModel != nil)
        {
            BOOL wasInitialized = [transitionEffectDataModel isInitialized];

            LSFLampState *newState = [[LSFLampState alloc] initWithOnOff: transitionEffect.lampState.onOff brightness: [constants unscaleLampStateValue: transitionEffect.lampState.brightness withMax: 100] hue: [constants unscaleLampStateValue: transitionEffect.lampState.hue withMax: 360] saturation: [constants unscaleLampStateValue: transitionEffect.lampState.saturation withMax: 100] colorTemp: [constants unscaleColorTemp: transitionEffect.lampState.colorTemp]];
            [transitionEffectDataModel setState: newState];
            [transitionEffectDataModel setPresetID: transitionEffect.presetID];
            [transitionEffectDataModel setDuration: transitionEffect.transitionPeriod];


            if (wasInitialized != [transitionEffectDataModel isInitialized])
            {
                [self postSendTransitionEffectInitialized: transitionEffectID];
            }
        }
    });

    [self postSendTransitionEffectChanged: transitionEffectID];
}

-(void)postDeleteTransitionEffectIDs: (NSArray *)transitionEffectIDs
{
    dispatch_async(self.manager.dispatchQueue, ^{
        for (NSString *transitionEffectID in transitionEffectIDs)
        {
            [self.manager.transitionEffectCollectionManager removeTransitionEffectWithID: transitionEffectID];
        }
    });
}

-(void)postSendTransitionEffectChanged: (NSString *)transitionEffectID
{
    dispatch_async(self.manager.dispatchQueue, ^{
        [self.manager.transitionEffectCollectionManager sendChangedEvent: transitionEffectID];
    });
}

-(void)postSendTransitionEffectInitialized: (NSString *)transitionEffectID
{
    dispatch_async(self.manager.dispatchQueue, ^{
        LSFSDKTrackingID *trackingID = [self.creationTrackingIDs valueForKey: transitionEffectID];

        if (trackingID != nil)
        {
            [self.creationTrackingIDs removeObjectForKey: transitionEffectID];
        }

        [self.manager.transitionEffectCollectionManager sendInitializedEvent: transitionEffectID withTrackingID: trackingID];
    });
}

@end
