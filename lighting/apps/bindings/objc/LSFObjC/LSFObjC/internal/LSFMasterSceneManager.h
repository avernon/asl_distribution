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

#import "LSFObject.h"
#import "LSFControllerClient.h"
#import "LSFMasterSceneManagerCallbackDelegate.h"
#import "LSFMasterScene.h"
#import <MasterSceneManager.h>

@interface LSFMasterSceneManager : LSFObject

-(id)initWithControllerClient: (LSFControllerClient *)controllerClient andMasterSceneManagerCallbackDelegate: (id<LSFMasterSceneManagerCallbackDelegate>)msmDelegate;
-(ControllerClientStatus)getAllMasterSceneIDs;
-(ControllerClientStatus)getMasterSceneNameWithID: (NSString *)masterSceneID;
-(ControllerClientStatus)getMasterSceneNameWithID: (NSString *)masterSceneID andLanguage: (NSString *)language;
-(ControllerClientStatus)setMasterSceneNameWithID: (NSString *)masterSceneID andMasterSceneName: (NSString *)masterSceneName;
-(ControllerClientStatus)setMasterSceneNameWithID: (NSString *)masterSceneID masterSceneName: (NSString *)masterSceneName andLanguage: (NSString *)language;
-(ControllerClientStatus)createMasterScene: (LSFMasterScene *)masterScene withName: (NSString *)masterSceneName;
-(ControllerClientStatus)createMasterScene: (LSFMasterScene *)masterScene withName: (NSString *)masterSceneName andLanguage: (NSString *)language;
-(ControllerClientStatus)createMasterSceneWithTracking: (uint32_t *)trackingID masterScene: (LSFMasterScene *)masterScene withName: (NSString *)masterSceneName;
-(ControllerClientStatus)createMasterSceneWithTracking: (uint32_t *)trackingID masterScene: (LSFMasterScene *)masterScene withName: (NSString *)masterSceneName andLanguage: (NSString *)language;
-(ControllerClientStatus)updateMasterSceneWithID: (NSString *)masterSceneID andMasterScene: (LSFMasterScene *)masterScene;
-(ControllerClientStatus)getMasterSceneWithID: (NSString *)masterSceneID;
-(ControllerClientStatus)deleteMasterSceneWithID: (NSString *)masterSceneID;
-(ControllerClientStatus)applyMasterSceneWithID: (NSString *)masterSceneID;
-(ControllerClientStatus)getMasterSceneDataWithID: (NSString *)masterSceneID;
-(ControllerClientStatus)getMasterSceneDataWithID: (NSString *)masterSceneID andLanguage: (NSString *)language;

@end
