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
#import <internal/LSFLampGroupManagerCallbackDelegate.h>

@interface MockLampGroupManageCallbackDelegateHandler : NSObject <LSFLampGroupManagerCallbackDelegate>

-(id)init;
-(NSArray *)getCallbackData;

//Delegate methods
-(void)getAllLampGroupIDsReplyWithCode: (LSFResponseCode)rc andGroupIDs: (NSArray*)groupIDs;
-(void)getLampGroupNameReplyWithCode: (LSFResponseCode)rc groupID: (NSString*)groupID language: (NSString *)language andGroupName: (NSString*)name;
-(void)setLampGroupNameReplyWithCode: (LSFResponseCode)rc groupID: (NSString*)groupID andLanguage: (NSString *)language;
-(void)lampGroupsNameChanged: (NSArray *)groupIDs;
-(void)createLampGroupReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID;
-(void)createLampGroupTrackingReplyWithCode: (LSFResponseCode)rc groupID: (NSString *)groupID andTrackingID: (unsigned int)trackingID;
-(void)lampGroupsCreated: (NSArray *)groupIDs;
-(void)getLampGroupReplyWithCode: (LSFResponseCode)rc groupID: (NSString *)groupID andLampGroup: (LSFLampGroup *)group;
-(void)deleteLampGroupReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID;
-(void)lampGroupsDeleted: (NSArray *)groupIDs;
-(void)transitionLampGroupToStateReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID;
-(void)pulseLampGroupWithStateReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID;
-(void)pulseLampGroupWithPresetReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID;
-(void)transitionLampGroupStateOnOffFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID;
-(void)transitionLampGroupStateHueFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID;
-(void)transitionLampGroupStateSaturationFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID;
-(void)transitionLampGroupStateBrightnessFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID;
-(void)transitionLampGroupStateColorTempFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID;
-(void)resetLampGroupStateReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID;
-(void)resetLampGroupStateOnOffFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID;
-(void)resetLampGroupStateHueFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID;
-(void)resetLampGroupStateSaturationFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID;
-(void)resetLampGroupStateBrightnessFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID;
-(void)resetLampGroupStateColorTempFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID;
-(void)updateLampGroupReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID;
-(void)lampGroupsUpdated: (NSArray *)groupIDs;
-(void)transitionLampGroupStateToPresetReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID;
-(void)setLampGroupEffectReplyWithCode: (LSFResponseCode)rc groupID: (NSString *)groupID andEffectID: (NSString *)effectID;

@end
