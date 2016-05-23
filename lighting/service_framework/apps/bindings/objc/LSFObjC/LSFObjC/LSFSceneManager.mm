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

#import "LSFSceneManager.h"
#import "LSFSceneManagerCallback.h"

@interface LSFSceneManager()

@property (nonatomic, readonly) lsf::SceneManager *sceneManager;
@property (nonatomic, assign) LSFSceneManagerCallback *sceneManagerCallback;

@end

@implementation LSFSceneManager

@synthesize sceneManager = _sceneManager;
@synthesize sceneManagerCallback = _sceneManagerCallback;

-(id)initWithControllerClient: (LSFControllerClient *)controllerClient andSceneManagerCallbackDelegate: (id<LSFSceneManagerCallbackDelegate>)smDelegate
{
    self = [super init];
    
    if (self)
    {
        self.sceneManagerCallback = new LSFSceneManagerCallback(smDelegate);
        self.handle = new lsf::SceneManager(*(static_cast<lsf::ControllerClient*>(controllerClient.handle)), *(self.sceneManagerCallback));
    }
    
    return self;
}

-(ControllerClientStatus)getAllSceneIDs
{
    return self.sceneManager->GetAllSceneIDs();
}

-(ControllerClientStatus)getSceneNameWithID: (NSString *)sceneID
{
    std::string sid([sceneID UTF8String]);
    return self.sceneManager->GetSceneName(sid);
}

-(ControllerClientStatus)getSceneNameWithID: (NSString *)sceneID andLanguage: (NSString *)language
{
    std::string sid([sceneID UTF8String]);
    std::string lang([language UTF8String]);
    return self.sceneManager->GetSceneName(sid, lang);
}

-(ControllerClientStatus)setSceneNameWithID: (NSString *)sceneID andSceneName: (NSString *)sceneName
{
    std::string sid([sceneID UTF8String]);
    std::string name([sceneName UTF8String]);
    return self.sceneManager->SetSceneName(sid, name);
}

-(ControllerClientStatus)setSceneNameWithID: (NSString *)sceneID sceneName: (NSString *)sceneName andLanguage: (NSString *)language
{
    std::string sid([sceneID UTF8String]);
    std::string name([sceneName UTF8String]);
    std::string lang([language UTF8String]);
    return self.sceneManager->SetSceneName(sid, name, lang);
}

-(ControllerClientStatus)createScene: (LSFScene *)scene andSceneName: (NSString *)sceneName
{
    std::string name([sceneName UTF8String]);
    return self.sceneManager->CreateScene(*(static_cast<lsf::Scene*>(scene.handle)), name);
}

-(ControllerClientStatus)createScene: (LSFScene *)scene sceneName: (NSString *)sceneName andLanguage: (NSString *)language
{
    std::string name([sceneName UTF8String]);
    std::string lang([language UTF8String]);
    return self.sceneManager->CreateScene(*(static_cast<lsf::Scene*>(scene.handle)), name, lang);
}

-(ControllerClientStatus)updateSceneWithID: (NSString *)sceneID withScene: (LSFScene *)scene
{
    std::string sid([sceneID UTF8String]);
    return self.sceneManager->UpdateScene(sid, *(static_cast<lsf::Scene*>(scene.handle)));
}

-(ControllerClientStatus)deleteSceneWithID: (NSString *)sceneID
{
    std::string sid([sceneID UTF8String]);
    return self.sceneManager->DeleteScene(sid);
}

-(ControllerClientStatus)getSceneWithID: (NSString *)sceneID
{
    std::string sid([sceneID UTF8String]);
    return self.sceneManager->GetScene(sid);
}

-(ControllerClientStatus)applySceneWithID: (NSString *)sceneID
{
    std::string sid([sceneID UTF8String]);
    return self.sceneManager->ApplyScene(sid);
}

-(ControllerClientStatus)getSceneDataWithID: (NSString *)sceneID
{
    std::string sid([sceneID UTF8String]);
    return self.sceneManager->GetSceneDataSet(sid);
}

-(ControllerClientStatus)getSceneDataWithID: (NSString *)sceneID andLanguage: (NSString *)language
{
    std::string sid([sceneID UTF8String]);
    std::string lang([language UTF8String]);
    return self.sceneManager->GetSceneDataSet(sid, lang);
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
-(lsf::SceneManager *)sceneManager
{
    return static_cast<lsf::SceneManager*>(self.handle);
}

@end
