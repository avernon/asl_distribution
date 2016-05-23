/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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
#import <internal/LSFLampState.h>
#import <internal/LSFLampGroup.h>
#import <internal/LSFTransitionEffectV2.h>
#import <internal/LSFPulseEffectV2.h>
#import <internal/LSFSceneElement.h>
#import <internal/LSFMasterScene.h>
#import <internal/LSFSceneWithSceneElements.h>
#import "LSFSDKPreset.h"

@interface LSFSDKLightingItemUtil : NSObject

+(LSFLampState *)createLampStateFromPower: (BOOL)powerOn hue: (unsigned int)hue saturation: (unsigned int)saturation brightness: (unsigned int)brightness colorTemp: (unsigned int)colorTemp;
+(LSFLampGroup *)createLampGroupFromGroupMembers: (NSArray *)groupMembers;
+(LSFLampGroup *)createLampGroupFromLampIDs: (NSArray *)lampIDs groupIDs: (NSArray *)groupIDs;
+(LSFTransitionEffectV2 *)createTransitionEffectFromPower: (BOOL)powerOn hsvt: (NSArray *)hsvt duration: (unsigned int)duration;
+(LSFTransitionEffectV2 *)createTransitionEffectFromLampState: (LSFLampState *)lampState duration: (unsigned int)duration;
+(LSFTransitionEffectV2 *)createTransitionEffectFromPreset: (LSFSDKPreset *)preset duration: (unsigned int)duration;
+(LSFPulseEffectV2 *)createPulseEffectWithFromPowerOn: (BOOL)fromPowerOn fromColorHsvt: (NSArray *)fromColorHsvt toPowerOn: (BOOL)toPowerOn toColorHsvt: (NSArray *)toColorHsvt period: (unsigned int)period duration: (unsigned int)duration count: (unsigned int)count;
+(LSFPulseEffectV2 *)createPulseEffectFromLampState: (LSFLampState *)fromState toLampState: (LSFLampState *)toState period: (unsigned int)period duration: (unsigned int)duration count: (unsigned int)count;
+(LSFPulseEffectV2 *)createPulseeffectFromPreset: (LSFSDKPreset *)fromPreset toPreset: (LSFSDKPreset *)toPreset period: (unsigned int)period duration: (unsigned int)duration count: (unsigned int)count;
+(LSFSceneElement *)createSceneElementWithEffectID: (NSString *)effectID groupMembers: (NSArray *)members;
+(LSFSceneElement *)createSceneElementWithEffectID: (NSString *)effectID lampIDs: (NSArray *)lampIDs groupIDs: (NSArray *)groupIDs;
+(LSFMasterScene *)createMasterSceneFromSceneID: (NSArray *)sceneIDs;
+(LSFSceneWithSceneElements *)createSceneWithSceneElements: (NSArray *)sceneElementIDs;

@end
