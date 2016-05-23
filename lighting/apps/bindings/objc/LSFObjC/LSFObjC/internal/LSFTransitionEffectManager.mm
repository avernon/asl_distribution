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

#import "LSFTransitionEffectManager.h"
#import "LSFTransitionEffectManagerCallback.h"
#import <TransitionEffectManager.h>

@interface LSFTransitionEffectManager()

@property (nonatomic, readonly) lsf::TransitionEffectManager *transitionEffectManager;
@property (nonatomic, assign) LSFTransitionEffectManagerCallback *transitionEffectManagerCallback;

@end

@implementation LSFTransitionEffectManager

-(id)initWithControllerClient: (LSFControllerClient *)controllerClient andTransitionEffectManagerCallbackDelegate: (id<LSFTransitionEffectManagerCallbackDelegate>)temDelegate
{
    self = [super init];

    if (self)
    {
        self.transitionEffectManagerCallback = new LSFTransitionEffectManagerCallback(temDelegate);
        self.handle = new lsf::TransitionEffectManager(*(static_cast<lsf::ControllerClient*>(controllerClient.handle)), *(self.transitionEffectManagerCallback));
    }

    return self;
}

-(ControllerClientStatus)getAllTransitionEffectIDs
{
    return self.transitionEffectManager->GetAllTransitionEffectIDs();
}

-(ControllerClientStatus)getTransitionEffectWithID: (NSString *)transitionEffectID
{
    std::string teid([transitionEffectID UTF8String]);
    return self.transitionEffectManager->GetTransitionEffect(teid);
}

-(ControllerClientStatus)applyTranstionEffectWithID: (NSString *)transitionEffectID onLamps: (NSArray *)lampIDs
{
    std::string teid([transitionEffectID UTF8String]);
    LSFStringList lids;

    for (NSString *lid in lampIDs)
    {
        lids.push_back([lid UTF8String]);
    }

    return self.transitionEffectManager->ApplyTransitionEffectOnLamps(teid, lids);
}

-(ControllerClientStatus)applyTranstionEffectWithID: (NSString *)transitionEffectID onLampGroups: (NSArray *)lampGroupIDs
{
    std::string teid([transitionEffectID UTF8String]);
    LSFStringList lgids;

    for (NSString *lgid in lampGroupIDs)
    {
        lgids.push_back([lgid UTF8String]);
    }

    return self.transitionEffectManager->ApplyTransitionEffectOnLampGroups(teid, lgids);
}

-(ControllerClientStatus)getTransitionEffectNameWithID: (NSString *)transitionEffectID
{
    std::string teid([transitionEffectID UTF8String]);
    return self.transitionEffectManager->GetTransitionEffectName(teid);
}

-(ControllerClientStatus)getTransitionEffectNameWithID: (NSString *)transitionEffectID andLanguage: (NSString *)language
{
    std::string teid([transitionEffectID UTF8String]);
    std::string lang([language UTF8String]);
    return self.transitionEffectManager->GetTransitionEffectName(teid, lang);
}

-(ControllerClientStatus)setTransitionEffectNameWithID: (NSString *)transitionEffectID transitionEffectName: (NSString *)transitionEffectName
{
    std::string teid([transitionEffectID UTF8String]);
    std::string name([transitionEffectName UTF8String]);
    return self.transitionEffectManager->SetTransitionEffectName(teid, name);
}

-(ControllerClientStatus)setTransitionEffectNameWithID: (NSString *)transitionEffectID transitionEffectName: (NSString *)transitionEffectName andLanguage: (NSString *)language
{
    std::string teid([transitionEffectID UTF8String]);
    std::string name([transitionEffectName UTF8String]);
    std::string lang([language UTF8String]);
    return self.transitionEffectManager->SetTransitionEffectName(teid, name, lang);
}

-(ControllerClientStatus)createTransitionEffectWithTracking: (uint32_t *)trackingID transitionEffect: (LSFTransitionEffectV2 *)transitionEffect andTransitionEffectName: (NSString *)transitionEffectName
{
    std::string name([transitionEffectName UTF8String]);
    return self.transitionEffectManager->CreateTransitionEffect(*trackingID, *(static_cast<lsf::TransitionEffect*>(transitionEffect.handle)), name);
}

-(ControllerClientStatus)createTransitionEffectWithTracking: (uint32_t *)trackingID transitionEffect: (LSFTransitionEffectV2 *)transitionEffect transitionEffectName: (NSString *)transitionEffectName andLanguage: (NSString *)language
{
    std::string name([transitionEffectName UTF8String]);
    std::string lang([language UTF8String]);
    return self.transitionEffectManager->CreateTransitionEffect(*trackingID, *(static_cast<lsf::TransitionEffect*>(transitionEffect.handle)), name, lang);
}

-(ControllerClientStatus)updateTransitionEffectWithID: (NSString *)transitionEffectID andTransitionEffect: (LSFTransitionEffectV2 *)transitionEffect
{
    std::string teid([transitionEffectID UTF8String]);
    return self.transitionEffectManager->UpdateTransitionEffect(teid, *(static_cast<lsf::TransitionEffect*>(transitionEffect.handle)));
}

-(ControllerClientStatus)deleteTransitionEffectWithID: (NSString *)transitionEffectID
{
    std::string teid([transitionEffectID UTF8String]);
    return self.transitionEffectManager->DeleteTransitionEffect(teid);
}

-(ControllerClientStatus)getTransitionEffectDataSetWithID: (NSString *)transitionEffectID
{
    std::string teid([transitionEffectID UTF8String]);
    return self.transitionEffectManager->GetTransitionEffectDataSet(teid);
}

-(ControllerClientStatus)getTransitionEffectDataSetWithID: (NSString *)transitionEffectID andLanguage: (NSString *)language
{
    std::string teid([transitionEffectID UTF8String]);
    std::string lang([language UTF8String]);
    return self.transitionEffectManager->GetTransitionEffectDataSet(teid, lang);
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
-(lsf::TransitionEffectManager *)transitionEffectManager
{
    return static_cast<lsf::TransitionEffectManager*>(self.handle);
}

@end
