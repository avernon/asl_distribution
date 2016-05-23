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

#import <Foundation/Foundation.h>
#import <LSFResponseCodes.h>
#import "LSFPulseEffectV2.h"

using namespace lsf;

@protocol LSFPulseEffectManagerCallbackDelegate <NSObject>

-(void)getPulseEffectReplyWithCode: (LSFResponseCode)rc pulseEffectID: (NSString *)pulseEffectID andPulseEffect: (LSFPulseEffectV2 *)pulseEffect;
-(void)applyPulseEffectOnLampsReplyWithCode: (LSFResponseCode)rc pulseEffectID: (NSString *)pulseEffectID andLampIDs: (NSArray *)lampIDs;
-(void)applyPulseEffectOnLampGroupsReplyWithCode: (LSFResponseCode)rc pulseEffectID: (NSString *)pulseEffectID andLampGroupIDs: (NSArray *)lampGroupIDs;
-(void)getAllPulseEffectIDsReplyWithCode: (LSFResponseCode)rc pulseEffectIDs: (NSArray *)pulseEffectIDs;
-(void)getPulseEffectNameReplyWithCode: (LSFResponseCode)rc pulseEffectID: (NSString *)pulseEffectID language: (NSString *)language andPulseEffectName: (NSString *)pulseEffectName;
-(void)setPulseEffectNameReplyWithCode: (LSFResponseCode)rc pulseEffectID: (NSString *)pulseEffectID andLanguage: (NSString *)language;
-(void)pulseEffectsNameChanged: (NSArray *)pulseEffectIDs;
-(void)createPulseEffectReplyWithCode: (LSFResponseCode)rc pulseEffectID: (NSString *)pulseEffectID andTrackingID: (unsigned int)trackingID;
-(void)pulseEffectsCreated: (NSArray *)pulseEffectIDs;
-(void)updatePulseEffectReplyWithCode: (LSFResponseCode)rc andPulseEffectID: (NSString *)pulseEffectID;
-(void)pulseEffectsUpdated: (NSArray *)pulseEffectIDs;
-(void)deletePulseEffectReplyWithCode: (LSFResponseCode)rc andPulseEffectID: (NSString *)pulseEffectID;
-(void)pulseEffectsDeleted: (NSArray *)pulseEffectIDs;

@end
