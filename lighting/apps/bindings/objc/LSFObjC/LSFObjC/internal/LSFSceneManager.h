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
#import "LSFObject.h"
#import "LSFControllerClient.h"
#import "LSFSceneManagerCallbackDelegate.h"
#import "LSFScene.h"
#import "LSFSceneWithSceneElements.h"
#import <SceneManager.h>

@interface LSFSceneManager : LSFObject

-(id)initWithControllerClient: (LSFControllerClient *)controllerClient andSceneManagerCallbackDelegate: (id<LSFSceneManagerCallbackDelegate>)smDelegate;
-(ControllerClientStatus)getAllSceneIDs;
-(ControllerClientStatus)getSceneNameWithID: (NSString *)sceneID;
-(ControllerClientStatus)getSceneNameWithID: (NSString *)sceneID andLanguage: (NSString *)language;
-(ControllerClientStatus)setSceneNameWithID: (NSString *)sceneID andSceneName: (NSString *)sceneName;
-(ControllerClientStatus)setSceneNameWithID: (NSString *)sceneID sceneName: (NSString *)sceneName andLanguage: (NSString *)language;
-(ControllerClientStatus)createScene: (LSFScene *)scene andSceneName: (NSString *)sceneName;
-(ControllerClientStatus)createScene: (LSFScene *)scene sceneName: (NSString *)sceneName andLanguage: (NSString *)language;
-(ControllerClientStatus)createSceneWithTracking: (uint32_t *)trackingID scene: (LSFScene *)scene andSceneName: (NSString *)sceneName;
-(ControllerClientStatus)createSceneWithTracking: (uint32_t *)trackingID scene: (LSFScene *)scene sceneName: (NSString *)sceneName andLanguage: (NSString *)language;
-(ControllerClientStatus)createSceneWithSceneElementsWithTracking: (uint32_t *)trackingID sceneWithSceneElements: (LSFSceneWithSceneElements *)sceneWithSceneElements andSceneName: (NSString *)sceneName;
-(ControllerClientStatus)createSceneWithSceneElementsWithTracking: (uint32_t *)trackingID sceneWithSceneElements: (LSFSceneWithSceneElements *)sceneWithSceneElements sceneName: (NSString *)sceneName andLanguage: (NSString *)language;
-(ControllerClientStatus)updateSceneWithID: (NSString *)sceneID withScene: (LSFScene *)scene;
-(ControllerClientStatus)updateSceneWithSceneElementsWithID: (NSString *)sceneID withSceneWithSceneElements: (LSFSceneWithSceneElements *)sceneWithSceneElements;
-(ControllerClientStatus)deleteSceneWithID: (NSString *)sceneID;
-(ControllerClientStatus)getSceneWithID: (NSString *)sceneID;
-(ControllerClientStatus)getSceneWithSceneElementsWithID: (NSString *)sceneID;
-(ControllerClientStatus)applySceneWithID: (NSString *)sceneID;
-(ControllerClientStatus)getSceneDataWithID: (NSString *)sceneID;
-(ControllerClientStatus)getSceneDataWithID: (NSString *)sceneID andLanguage: (NSString *)language;
-(ControllerClientStatus)getSceneWithSceneElementsDataWithID: (NSString *)sceneID;
-(ControllerClientStatus)getSceneWithSceneElementsDataWithID: (NSString *)sceneID andLanguage: (NSString *)language;

@end
