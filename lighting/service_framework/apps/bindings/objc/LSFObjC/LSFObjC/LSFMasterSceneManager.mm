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

#import "LSFMasterSceneManager.h"
#import "LSFMasterSceneManagerCallback.h"

@interface LSFMasterSceneManager()

@property (nonatomic, readonly) lsf::MasterSceneManager *masterSceneManager;
@property (nonatomic, assign) LSFMasterSceneManagerCallback *masterSceneManagerCallback;

@end

@implementation LSFMasterSceneManager

@synthesize masterSceneManager = _masterSceneManager;
@synthesize masterSceneManagerCallback = _masterSceneManagerCallback;

-(id)initWithControllerClient: (LSFControllerClient *)controllerClient andMasterSceneManagerCallbackDelegate: (id<LSFMasterSceneManagerCallbackDelegate>)msmDelegate
{
    self = [super init];
    
    if (self)
    {
        self.masterSceneManagerCallback = new LSFMasterSceneManagerCallback(msmDelegate);
        self.handle = new lsf::MasterSceneManager(*(static_cast<lsf::ControllerClient*>(controllerClient.handle)), *(self.masterSceneManagerCallback));
    }
    
    return self;
}

-(ControllerClientStatus)getAllMasterSceneIDs
{
    return self.masterSceneManager->GetAllMasterSceneIDs();
}

-(ControllerClientStatus)getMasterSceneNameWithID: (NSString *)masterSceneID
{
    std::string msid([masterSceneID UTF8String]);
    return self.masterSceneManager->GetMasterSceneName(msid);
}

-(ControllerClientStatus)getMasterSceneNameWithID: (NSString *)masterSceneID andLanguage: (NSString *)language
{
    std::string msid([masterSceneID UTF8String]);
    std::string lang([language UTF8String]);
    return self.masterSceneManager->GetMasterSceneName(msid, lang);
}

-(ControllerClientStatus)setMasterSceneNameWithID: (NSString *)masterSceneID andMasterSceneName: (NSString *)masterSceneName
{
    std::string msid([masterSceneID UTF8String]);
    std::string name([masterSceneName UTF8String]);
    return self.masterSceneManager->SetMasterSceneName(msid, name);
}

-(ControllerClientStatus)setMasterSceneNameWithID: (NSString *)masterSceneID masterSceneName: (NSString *)masterSceneName andLanguage: (NSString *)language
{
    std::string msid([masterSceneID UTF8String]);
    std::string name([masterSceneName UTF8String]);
    std::string lang([language UTF8String]);
    return self.masterSceneManager->SetMasterSceneName(msid, name, lang);
}

-(ControllerClientStatus)createMasterScene: (LSFMasterScene *)masterScene withName: (NSString *)masterSceneName
{
    std::string name([masterSceneName UTF8String]);
    return self.masterSceneManager->CreateMasterScene(*(static_cast<lsf::MasterScene*>(masterScene.handle)), name);
}

-(ControllerClientStatus)createMasterScene: (LSFMasterScene *)masterScene withName: (NSString *)masterSceneName andLanguage: (NSString *)language
{
    std::string name([masterSceneName UTF8String]);
    std::string lang([language UTF8String]);
    return self.masterSceneManager->CreateMasterScene(*(static_cast<lsf::MasterScene*>(masterScene.handle)), name, lang);
}

-(ControllerClientStatus)updateMasterSceneWithID: (NSString *)masterSceneID andMasterScene: (LSFMasterScene *)masterScene
{
    std::string msid([masterSceneID UTF8String]);
    return self.masterSceneManager->UpdateMasterScene(msid, *(static_cast<lsf::MasterScene*>(masterScene.handle)));
}

-(ControllerClientStatus)getMasterSceneWithID: (NSString *)masterSceneID
{
    std::string msid([masterSceneID UTF8String]);
    return self.masterSceneManager->GetMasterScene(msid);
}

-(ControllerClientStatus)deleteMasterSceneWithID: (NSString *)masterSceneID
{
    std::string msid([masterSceneID UTF8String]);
    return self.masterSceneManager->DeleteMasterScene(msid);
}

-(ControllerClientStatus)applyMasterSceneWithID: (NSString *)masterSceneID
{
    std::string msid([masterSceneID UTF8String]);
    return self.masterSceneManager->ApplyMasterScene(msid);
}

-(ControllerClientStatus)getMasterSceneDataWithID: (NSString *)masterSceneID
{
    std::string msid([masterSceneID UTF8String]);
    return self.masterSceneManager->GetMasterSceneDataSet(msid);
}

-(ControllerClientStatus)getMasterSceneDataWithID: (NSString *)masterSceneID andLanguage: (NSString *)language
{
    std::string msid([masterSceneID UTF8String]);
    std::string lang([language UTF8String]);
    return self.masterSceneManager->GetMasterSceneDataSet(msid, lang);
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
-(lsf::MasterSceneManager *)masterSceneManager
{
    return static_cast<lsf::MasterSceneManager*>(self.handle);
}

@end
