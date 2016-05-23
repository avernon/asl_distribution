/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#import "LSFPendingSceneV2.h"
#import "LSFPendingSceneElement.h"
#import <Foundation/Foundation.h>
#import <LSFSDKTrackingID.h>
#import <LSFSDKCapabilityData.h>
#import <LSFSDKLampDetails.h>
#import <LSFSDKColor.h>
#import <LSFSDKPreset.h>
#import <LSFSDKMyLampState.h>

@interface LSFUtilityFunctions : NSObject

extern NSString* const PRESET_NAME_PREFIX;
extern NSString* const TRANSITION_NAME_PREFIX;
extern NSString* const PULSE_NAME_PREFIX;
extern NSString* const SCENE_ELEMENT_NAME_PREFIX;

extern NSArray *const LAMP_DETAILS_FIELDS;
extern NSArray *const LAMP_ABOUT_FIELDS;

+(BOOL)checkNameEmpty: (NSString *)name entity: (NSString *)entity;
+(BOOL)checkNameLength: (NSString *)name entity: (NSString *)entity;
+(BOOL)checkWhiteSpaces: (NSString *)name entity: (NSString *)entity;
+(void)colorIndicatorSetup: (UIImageView *)colorIndicatorImage withColor: (LSFSDKColor *) color andCapabilityData: (LSFSDKCapabilityData *)capablity;
+(NSString *)currentWifiSSID;
+(NSArray *)getLampDetailsFields;
+(NSArray *)getLampAboutFields;
+(NSArray *)getSupportedEffects;
+(NSArray *)getEffectImages;
+(NSMutableAttributedString *)getSourceCodeText;
+(NSMutableAttributedString *)getTeamText;
+(NSMutableAttributedString *)getNoticeText;
+(BOOL)preset: (LSFSDKPreset *)preset matchesMyLampState: (LSFSDKMyLampState *)state;
+(NSArray *)getPresetsWithMyLampState: (LSFSDKMyLampState *)state;
+(NSArray *)sortLightingItemsByName: (NSArray *)items;
+(void)disableActionSheet: (UIActionSheet *)actionSheet buttonAtIndex: (NSInteger)index;
+(NSString *)memberStringForPendingSceneElement: (LSFPendingSceneElement *)sceneElement;
+(NSString *) generateRandomHexStringWithLength: (int)len;
+(LSFSDKTrackingID *)createEffectFromPendingItem: (LSFPendingEffect *)effect;
+(LSFSDKTrackingID *)createSceneElementFromPendingItem: (LSFPendingSceneElement *)sceneElement;
+(LSFSDKTrackingID *)createSceneFromPendingItem: (LSFPendingSceneV2 *)scene;
+(void)updateSceneElementWithID: (NSString *)elementID pendingItem: (LSFPendingSceneElement *)pendingElement;
+(void)updateEffectWithID: (NSString *)effectID pendingItem: (LSFPendingEffect *)pendingEffect;
+(int)getBoundedMinColorTempForMembers: (NSArray *)members;
+(int)getBoundedMaxColorTempForMembers: (NSArray *)members;

@end
