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
#import "LSFTransitionEffectV2.h"

using namespace lsf;

@protocol LSFTransitionEffectManagerCallbackDelegate <NSObject>

@required
-(void)getTransitionEffectReplyWithCode: (LSFResponseCode)rc transitionEffectID: (NSString *)transitionEffectID andTransitionEffect: (LSFTransitionEffectV2 *)transitionEffect;
-(void)applyTransitionEffectOnLampsReplyWithCode: (LSFResponseCode)rc transitionEffectID: (NSString *)transitionEffectID andLampIDs: (NSArray *)lampIDs;
-(void)applyTransitionEffectOnLampGroupsReplyWithCode: (LSFResponseCode)rc transitionEffectID: (NSString *)transitionEffectID andLampGroupIDs: (NSArray *)lampGroupIDs;
-(void)getAllTransitionEffectIDsReplyWithCode: (LSFResponseCode)rc transitionEffectIDs: (NSArray *)transitionEffectIDs;
-(void)getTransitionEffectNameReplyWithCode: (LSFResponseCode)rc transitionEffectID: (NSString *)transitionEffectID language: (NSString *)language andTransitionEffectName: (NSString *)transitionEffectName;
-(void)setTransitionEffectNameReplyWithCode: (LSFResponseCode)rc transitionEffectID: (NSString *)transitionEffectID andLanguage: (NSString *)language;
-(void)transitionEffectsNameChanged: (NSArray *)transitionEffectIDs;
-(void)createTransitionEffectReplyWithCode: (LSFResponseCode)rc transitionEffectID: (NSString *)transitionEffectID andTrackingID: (unsigned int)trackingID;
-(void)transitionEffectsCreated: (NSArray *)transitionEffectIDs;
-(void)updateTransitionEffectReplyWithCode: (LSFResponseCode)rc andTransitionEffectID: (NSString *)transitionEffectID;
-(void)transitionEffectsUpdated: (NSArray *)transitionEffectIDs;
-(void)deleteTransitionEffectReplyWithCode: (LSFResponseCode)rc andTransitionEffectID: (NSString *)transitionEffectID;
-(void)transitionEffectsDeleted: (NSArray *)transitionEffectIDs;

@end
