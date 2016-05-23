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

#import <Foundation/Foundation.h>
#import <LSFTypes.h>

@interface LSFUtils : NSObject

+(lsf::LSFStringList)convertNSArrayToStringList: (NSArray *)array;
+(NSArray *)convertStringListToNSArray: (lsf::LSFStringList)list;
+(lsf::TransitionLampsLampGroupsToStateList)convertNSArrayToStateTransitionEffects: (NSArray *)stateTransitionEffects;
+(lsf::TransitionLampsLampGroupsToPresetList)convertNSArrayToPresetTransitionEffects: (NSArray *)presetTransitionEffects;
+(lsf::PulseLampsLampGroupsWithStateList)convertNSArrayToStatePulseEffects: (NSArray *)statePulseEffects;
+(lsf::PulseLampsLampGroupsWithPresetList)convertNSArrayToPresetPulseEffects: (NSArray *)presetPulseEffects;
+(NSArray *)convertStateTransitionEffectsToNSArray: (lsf::TransitionLampsLampGroupsToStateList)stateTransitionEffects;
+(NSArray *)convertPresetTransitionEffectsToNSArray: (lsf::TransitionLampsLampGroupsToPresetList)presetTransitionEffects;
+(NSArray *)convertStatePulseEffectsToNSArray: (lsf::PulseLampsLampGroupsWithStateList)statePulseEffects;
+(NSArray *)convertPresetPulseEffectsToNSArray: (lsf::PulseLampsLampGroupsWithPresetList)presetPulseEffects;

@end
