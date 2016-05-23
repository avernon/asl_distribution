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

#import "LSFSceneElementManager.h"
#import "LSFSceneElementManagerCallback.h"

@interface LSFSceneElementManager()

@property (nonatomic, readonly) lsf::SceneElementManager *sceneElementManager;
@property (nonatomic, assign) LSFSceneElementManagerCallback *sceneElementManagerCallback;

@end

@implementation LSFSceneElementManager

@synthesize sceneElementManager = _sceneElementManager;
@synthesize sceneElementManagerCallback = _sceneElementManagerCallback;

-(id)initWithControllerClient: (LSFControllerClient *)controllerClient andSceneElementManagerCallbackDelegate: (id<LSFSceneElementManagerCallbackDelegate>)semDelegate
{
    self = [super init];

    if (self)
    {
        self.sceneElementManagerCallback = new LSFSceneElementManagerCallback(semDelegate);
        self.handle = new lsf::SceneElementManager(*(static_cast<lsf::ControllerClient*>(controllerClient.handle)), *(self.sceneElementManagerCallback));
    }

    return self;
}

-(ControllerClientStatus)getAllSceneElementIDs
{
    return self.sceneElementManager->GetAllSceneElementIDs();
}

-(ControllerClientStatus)getSceneElementNameWithID: (NSString *)sceneElementID
{
    std::string seid([sceneElementID UTF8String]);
    return self.sceneElementManager->GetSceneElementName(seid);
}

-(ControllerClientStatus)getSceneElementNameWithID: (NSString *)sceneElementID andLanguage: (NSString *)language
{
    std::string seid([sceneElementID UTF8String]);
    std::string lang([language UTF8String]);
    return self.sceneElementManager->GetSceneElementName(seid, lang);
}

-(ControllerClientStatus)setSceneElementNameWithID: (NSString *)sceneElementID andSceneElementName: (NSString *)sceneElementName
{
    std::string seid([sceneElementID UTF8String]);
    std::string name([sceneElementName UTF8String]);
    return self.sceneElementManager->SetSceneElementName(seid, name);
}

-(ControllerClientStatus)setSceneElementNameWithID: (NSString *)sceneElementID sceneElementName: (NSString *)sceneElementName andLanguage: (NSString *)language
{
    std::string seid([sceneElementID UTF8String]);
    std::string name([sceneElementName UTF8String]);
    std::string lang([language UTF8String]);
    return self.sceneElementManager->SetSceneElementName(seid, name, lang);
}

-(ControllerClientStatus)createSceneElementWithTracking: (uint32_t *)trackingID sceneElement: (LSFSceneElement *)sceneElement andSceneElementName: (NSString *)sceneElementName
{
    std::string name([sceneElementName UTF8String]);
    return self.sceneElementManager->CreateSceneElement(*trackingID, *(static_cast<lsf::SceneElement*>(sceneElement.handle)), name);
}

-(ControllerClientStatus)createSceneElementWithTracking: (uint32_t *)trackingID sceneElement: (LSFSceneElement *)sceneElement sceneElementName: (NSString *)sceneElementName andLanguage: (NSString *)language
{
    std::string name([sceneElementName UTF8String]);
    std::string lang([language UTF8String]);
    return self.sceneElementManager->CreateSceneElement(*trackingID, *(static_cast<lsf::SceneElement*>(sceneElement.handle)), name, lang);
}

-(ControllerClientStatus)updateSceneElementWithID: (NSString *)sceneElementID withSceneElement: (LSFSceneElement *)sceneElement
{
    std::string seid([sceneElementID UTF8String]);
    return self.sceneElementManager->UpdateSceneElement(seid, *(static_cast<lsf::SceneElement*>(sceneElement.handle)));
}

-(ControllerClientStatus)deleteSceneElementWithID: (NSString *)sceneElementID
{
    std::string seid([sceneElementID UTF8String]);
    return self.sceneElementManager->DeleteSceneElement(seid);
}

-(ControllerClientStatus)getSceneElementWithID: (NSString *)sceneElementID
{
    std::string seid([sceneElementID UTF8String]);
    return self.sceneElementManager->GetSceneElement(seid);
}

-(ControllerClientStatus)applySceneElementWithID: (NSString *)sceneElementID
{
    std::string seid([sceneElementID UTF8String]);
    return self.sceneElementManager->ApplySceneElement(seid);
}

-(ControllerClientStatus)getSceneElementDataWithID: (NSString *)sceneElementID
{
    std::string seid([sceneElementID UTF8String]);
    return self.sceneElementManager->GetSceneElementDataSet(seid);
}

-(ControllerClientStatus)getSceneElementDataWithID: (NSString *)sceneElementID andLanguage: (NSString *)language
{
    std::string seid([sceneElementID UTF8String]);
    std::string lang([language UTF8String]);
    return self.sceneElementManager->GetSceneElementDataSet(seid, lang);;
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
-(lsf::SceneElementManager *)sceneElementManager
{
    return static_cast<lsf::SceneElementManager*>(self.handle);
}

@end