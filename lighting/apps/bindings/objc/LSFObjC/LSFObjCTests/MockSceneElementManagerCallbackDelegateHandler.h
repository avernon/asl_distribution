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
#import <internal/LSFSceneElementManagerCallbackDelegate.h>

@interface MockSceneElementManagerCallbackDelegateHandler : NSObject <LSFSceneElementManagerCallbackDelegate>

-(id)init;
-(NSArray *)getCallbackData;

//Delegate methods
-(void)getAllSceneElementIDsReplyWithCode: (LSFResponseCode)rc andSceneElementIDs: (NSArray *)sceneElementIDs;
-(void)getSceneElementNameReplyWithCode: (LSFResponseCode)rc sceneElementID: (NSString *)sceneElementID language: (NSString *)language andSceneElementName: (NSString *)sceneElementName;
-(void)setSceneElementNameReplyWithCode: (LSFResponseCode)rc sceneElementID: (NSString *)sceneElementID andLanguage: (NSString *)language;
-(void)sceneElementsNameChanged: (NSArray *)sceneElementIDs;
-(void)createSceneElementReplyWithCode: (LSFResponseCode)rc sceneElementID: (NSString *)sceneElementID andTrackingID: (unsigned int)trackingID;
-(void)sceneElementsCreated: (NSArray *)sceneElementIDs;
-(void)updateSceneElementReplyWithCode: (LSFResponseCode)rc andSceneElementID: (NSString *)sceneElementID;
-(void)sceneElementsUpdated: (NSArray *)sceneElementIDs;
-(void)deleteSceneElementReplyWithCode: (LSFResponseCode)rc andSceneElementID: (NSString *)sceneElementID;
-(void)sceneElementsDeleted: (NSArray *)sceneElementIDs;
-(void)getSceneElementReplyWithCode: (LSFResponseCode)rc sceneElementID: (NSString *)sceneElementID andSceneElement: (LSFSceneElement *)sceneElement;
-(void)applySceneElementReplyWithCode: (LSFResponseCode)rc andSceneElementID: (NSString *)sceneElementID;
-(void)sceneElementsApplied: (NSArray *)sceneElementIDs;

@end
