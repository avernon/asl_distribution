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
#import "LSFObjC/LSFSceneManagerCallbackDelegate.h"

@interface MockSceneManagerCallbackDelegateHandler : NSObject <LSFSceneManagerCallbackDelegate>

-(id)init;
-(NSArray *)getCallbackData;

//Delegate methods
-(void)getAllSceneIDsReplyWithCode: (LSFResponseCode)rc andSceneIDs: (NSArray *)sceneIDs;
-(void)getSceneNameReplyWithCode: (LSFResponseCode)rc sceneID: (NSString *)sceneID language: (NSString *)language andName: (NSString *)sceneName;
-(void)setSceneNameReplyWithCode: (LSFResponseCode)rc sceneID: (NSString *)sceneID andLanguage: (NSString *)language;
-(void)scenesNameChanged: (NSArray *)sceneIDs;
-(void)createSceneReplyWithCode: (LSFResponseCode)rc andSceneID: (NSString *)sceneID;
-(void)scenesCreated: (NSArray *)sceneIDs;
-(void)updateSceneReplyWithCode: (LSFResponseCode)rc andSceneID: (NSString *)sceneID;
-(void)scenesUpdated: (NSArray *)sceneIDs;
-(void)deleteSceneReplyWithCode: (LSFResponseCode)rc andSceneID: (NSString *)sceneID;
-(void)scenesDeleted: (NSArray *)sceneIDs;
-(void)getSceneReplyWithCode: (LSFResponseCode)rc sceneID: (NSString *)sceneID andScene: (LSFScene *)scene;
-(void)applySceneReplyWithCode: (LSFResponseCode)rc andSceneID: (NSString *)sceneID;
-(void)scenesApplied: (NSArray *)sceneIDs;

@end
