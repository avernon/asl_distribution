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
#import <internal/LSFMasterSceneManagerCallbackDelegate.h>

@interface MockMasterSceneManagerCallbackDelegateHandler : NSObject <LSFMasterSceneManagerCallbackDelegate>

-(id)init;
-(NSArray *)getCallbackData;

//Delegate methods
-(void)getAllMasterSceneIDsReplyWithCode: (LSFResponseCode)rc andMasterSceneIDs: (NSArray *)masterSceneIDs;
-(void)getMasterSceneNameReplyWithCode: (LSFResponseCode)rc masterSceneID: (NSString *)masterSceneID language: (NSString *)language andName: (NSString *)masterSceneName;
-(void)setMasterSceneNameReplyWithCode: (LSFResponseCode)rc masterSceneID: (NSString *)masterSceneID andLanguage: (NSString *)language;
-(void)masterScenesNameChanged: (NSArray *)masterSceneIDs;
-(void)createMasterSceneReplyWithCode: (LSFResponseCode)rc andMasterSceneID: (NSString *)masterSceneID;
-(void)createMasterSceneTrackingReplyWithCode: (LSFResponseCode)rc masterSceneID: (NSString *)masterSceneID andTrackingID: (unsigned int)trackingID;
-(void)masterScenesCreated: (NSArray *)masterSceneIDs;
-(void)getMasterSceneReplyWithCode: (LSFResponseCode)rc masterSceneID: (NSString *)masterSceneID andMasterScene: (LSFMasterScene *)masterScene;
-(void)deleteMasterSceneReplyWithCode: (LSFResponseCode)rc andMasterSceneID: (NSString *)masterSceneID;
-(void)masterScenesDeleted: (NSArray *)masterSceneIDs;
-(void)updateMasterSceneReplyWithCode: (LSFResponseCode)rc andMasterSceneID: (NSString *)masterSceneID;
-(void)masterScenesUpdated: (NSArray *)masterSceneIDs;
-(void)applyMasterSceneReplyWithCode: (LSFResponseCode)rc andMasterSceneID: (NSString *)masterSceneID;
-(void)masterScenesApplied: (NSArray *)masterSceneIDs;

@end
