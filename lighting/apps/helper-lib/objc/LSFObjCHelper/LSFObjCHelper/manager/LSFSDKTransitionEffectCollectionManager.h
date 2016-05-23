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
#import "LSFSDKTransitionEffect.h"
#import "LSFSDKTransitionEffectDelegate.h"

@interface LSFSDKTransitionEffectCollectionManager : LSFSDKLightingItemCollectionManager

-(id)initWithLightingSystemManager: (LSFSDKLightingSystemManager *)lightingSystemManager;
-(void)addTransitionEffectDelegate: (id<LSFSDKTransitionEffectDelegate>)transitionEffectDelegate;
-(void)removeTransitionEffectDelegate: (id<LSFSDKTransitionEffectDelegate>)transitionEffectDelegate;
-(LSFSDKTransitionEffect *)addTransitionEffectWithID: (NSString *)transitionEffectID;
-(LSFSDKTransitionEffect *)addTransitionEffectWithID: (NSString *)transitionEffectID transitionEffect: (LSFSDKTransitionEffect *)transitionEffect;
-(LSFSDKTransitionEffect *)getTransitionEffectWithID: (NSString *)transitionEffectID;
-(NSArray *)getTransitionEffects;
-(NSArray *)getTransitionEffectsWithFilter: (id<LSFSDKLightingItemFilter>)filter;
-(NSArray *)getTransitionEffectCollectionWithFilter: (id<LSFSDKLightingItemFilter>)filter;
-(NSArray *)removeAllTransitionEffects;
-(LSFSDKTransitionEffect *)removeTransitionEffectWithID: (NSString *)transitionEffectID;
-(LSFTransitionEffectDataModelV2 *)getModelWithID: (NSString *)transitionEffectID;

@end
