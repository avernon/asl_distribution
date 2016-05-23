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

#import "MockPulseEffectManagerCallbackDelegateHandler.h"

@interface MockPulseEffectManagerCallbackDelegateHandler()

@property (nonatomic) NSMutableArray *dataArray;

@end

@implementation MockPulseEffectManagerCallbackDelegateHandler

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
-(void)getPulseEffectReplyWithCode: (LSFResponseCode)rc pulseEffectID: (NSString *)pulseEffectID andPulseEffect: (LSFPulseEffectV2 *)pulseEffect
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithUnsignedInt: rc];
    NSNumber *period = [[NSNumber alloc] initWithUnsignedInt: pulseEffect.pulsePeriod];
    NSNumber *duration = [[NSNumber alloc] initWithUnsignedInt: pulseEffect.pulseDuration];
    NSNumber *numPulses = [[NSNumber alloc] initWithUnsignedInt: pulseEffect.numPulses];
    [self.dataArray addObject: @"getPulseEffect"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: pulseEffectID];
    [self.dataArray addObject: pulseEffect.fromPreset];
    [self.dataArray addObject: pulseEffect.toPreset];
    [self.dataArray addObject: period];
    [self.dataArray addObject: duration];
    [self.dataArray addObject: numPulses];
}

-(void)applyPulseEffectOnLampsReplyWithCode: (LSFResponseCode)rc pulseEffectID: (NSString *)pulseEffectID andLampIDs: (NSArray *)lampIDs
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithUnsignedInt: rc];
    [self.dataArray addObject: @"applyPulseEffectOnLamps"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: pulseEffectID];
    [self.dataArray addObject: lampIDs];
}

-(void)applyPulseEffectOnLampGroupsReplyWithCode: (LSFResponseCode)rc pulseEffectID: (NSString *)pulseEffectID andLampGroupIDs: (NSArray *)lampGroupIDs
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithUnsignedInt: rc];
    [self.dataArray addObject: @"applyPulseEffectOnLampGroups"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: pulseEffectID];
    [self.dataArray addObject: lampGroupIDs];
}

-(void)getAllPulseEffectIDsReplyWithCode: (LSFResponseCode)rc pulseEffectIDs: (NSArray *)pulseEffectIDs
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithUnsignedInt: rc];
    [self.dataArray addObject: @"getAllPulseEffectIDs"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: pulseEffectIDs];
}

-(void)getPulseEffectNameReplyWithCode: (LSFResponseCode)rc pulseEffectID: (NSString *)pulseEffectID language: (NSString *)language andPulseEffectName: (NSString *)pulseEffectName
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithUnsignedInt: rc];
    [self.dataArray addObject: @"getPulseEffectName"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: pulseEffectID];
    [self.dataArray addObject: language];
    [self.dataArray addObject: pulseEffectName];
}

-(void)setPulseEffectNameReplyWithCode: (LSFResponseCode)rc pulseEffectID: (NSString *)pulseEffectID andLanguage: (NSString *)language
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithUnsignedInt: rc];
    [self.dataArray addObject: @"setPulseEffectName"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: pulseEffectID];
    [self.dataArray addObject: language];
}

-(void)pulseEffectsNameChanged: (NSArray *)pulseEffectIDs
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"pulseEffectsNameChanged"];
    [self.dataArray addObject: pulseEffectIDs];
}

-(void)createPulseEffectReplyWithCode: (LSFResponseCode)rc pulseEffectID: (NSString *)pulseEffectID andTrackingID: (unsigned int)trackingID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithUnsignedInt: rc];
    NSNumber *tid = [[NSNumber alloc] initWithUnsignedInt: trackingID];
    [self.dataArray addObject: @"createPulseEffect"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: pulseEffectID];
    [self.dataArray addObject: tid];
}

-(void)pulseEffectsCreated: (NSArray *)pulseEffectIDs
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"pulseEffectsCreated"];
    [self.dataArray addObject: pulseEffectIDs];
}

-(void)updatePulseEffectReplyWithCode: (LSFResponseCode)rc andPulseEffectID: (NSString *)pulseEffectID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithUnsignedInt: rc];
    [self.dataArray addObject: @"updatePulseEffect"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: pulseEffectID];
}

-(void)pulseEffectsUpdated: (NSArray *)pulseEffectIDs
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"pulseEffectsUpdated"];
    [self.dataArray addObject: pulseEffectIDs];
}

-(void)deletePulseEffectReplyWithCode: (LSFResponseCode)rc andPulseEffectID: (NSString *)pulseEffectID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithUnsignedInt: rc];
    [self.dataArray addObject: @"deletePulseEffect"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: pulseEffectID];
}

-(void)pulseEffectsDeleted: (NSArray *)pulseEffectIDs
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"pulseEffectsDeleted"];
    [self.dataArray addObject: pulseEffectIDs];
}

@end
