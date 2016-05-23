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

#import "MockTransitionEffectManagerCallbackDelegateHandler.h"

@interface MockTransitionEffectManagerCallbackDelegateHandler()

@property (nonatomic) NSMutableArray *dataArray;

@end

@implementation MockTransitionEffectManagerCallbackDelegateHandler

@synthesize dataArray = _dataArray;

-(id)init
{
    self = [super init];

    if (self)
    {
        self.dataArray = [[NSMutableArray alloc] init];
    }

    return self;
}

-(NSArray *)getCallbackData
{
    return self.dataArray;
}

//Delegate methods
-(void)getTransitionEffectReplyWithCode: (LSFResponseCode)rc transitionEffectID: (NSString *)transitionEffectID andTransitionEffect: (LSFTransitionEffectV2 *)transitionEffect
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    NSNumber *tp = [[NSNumber alloc] initWithUnsignedInt: transitionEffect.transitionPeriod];
    [self.dataArray addObject: @"getTransitionEffect"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: transitionEffectID];
    [self.dataArray addObject: transitionEffect.presetID];
    [self.dataArray addObject: tp];
}

-(void)applyTransitionEffectOnLampsReplyWithCode: (LSFResponseCode)rc transitionEffectID: (NSString *)transitionEffectID andLampIDs: (NSArray *)lampIDs
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"applyTransitionEffectOnLamps"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: transitionEffectID];
    [self.dataArray addObject: lampIDs];
}

-(void)applyTransitionEffectOnLampGroupsReplyWithCode: (LSFResponseCode)rc transitionEffectID: (NSString *)transitionEffectID andLampGroupIDs: (NSArray *)lampGroupIDs
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"applyTransitionEffectOnLampGroups"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: transitionEffectID];
    [self.dataArray addObject: lampGroupIDs];
}

-(void)getAllTransitionEffectIDsReplyWithCode: (LSFResponseCode)rc transitionEffectIDs: (NSArray *)transitionEffectIDs
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getAllTransitionEffectIDs"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: transitionEffectIDs];
}

-(void)getTransitionEffectNameReplyWithCode: (LSFResponseCode)rc transitionEffectID: (NSString *)transitionEffectID language: (NSString *)language andTransitionEffectName: (NSString *)transitionEffectName
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getTransitionEffectName"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: transitionEffectID];
    [self.dataArray addObject: language];
    [self.dataArray addObject: transitionEffectName];
}

-(void)setTransitionEffectNameReplyWithCode: (LSFResponseCode)rc transitionEffectID: (NSString *)transitionEffectID andLanguage: (NSString *)language
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"setTransitionEffectName"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: transitionEffectID];
    [self.dataArray addObject: language];
}

-(void)transitionEffectsNameChanged: (NSArray *)transitionEffectIDs
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"transitionEffectsNameChanged"];
    [self.dataArray addObject: transitionEffectIDs];
}

-(void)createTransitionEffectReplyWithCode: (LSFResponseCode)rc transitionEffectID: (NSString *)transitionEffectID andTrackingID: (unsigned int)trackingID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    NSNumber *tid = [[NSNumber alloc] initWithUnsignedInt: trackingID];
    [self.dataArray addObject: @"createTransitionEffect"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: transitionEffectID];
    [self.dataArray addObject: tid];
}

-(void)transitionEffectsCreated: (NSArray *)transitionEffectIDs
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"transitionEffectsCreated"];
    [self.dataArray addObject: transitionEffectIDs];
}

-(void)updateTransitionEffectReplyWithCode: (LSFResponseCode)rc andTransitionEffectID: (NSString *)transitionEffectID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"updateTransitionEffect"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: transitionEffectID];
}

-(void)transitionEffectsUpdated: (NSArray *)transitionEffectIDs
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"transitionEffectsUpdated"];
    [self.dataArray addObject: transitionEffectIDs];
}

-(void)deleteTransitionEffectReplyWithCode: (LSFResponseCode)rc andTransitionEffectID: (NSString *)transitionEffectID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"deleteTransitionEffect"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: transitionEffectID];
}

-(void)transitionEffectsDeleted: (NSArray *)transitionEffectIDs
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"transitionEffectsDeleted"];
    [self.dataArray addObject: transitionEffectIDs];
}

@end
