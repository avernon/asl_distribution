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

#import "LSFPulseEffectManager.h"
#import "LSFPulseEffectManagerCallback.h"
#import <PulseEffectManager.h>

@interface LSFPulseEffectManager()

@property (nonatomic, readonly) lsf::PulseEffectManager *pulseEffectManager;
@property (nonatomic, assign) LSFPulseEffectManagerCallback *pulseEffectManagerCallback;

@end

@implementation LSFPulseEffectManager

-(id)initWithControllerClient: (LSFControllerClient *)controllerClient andPulseEffectManagerCallbackDelegate: (id<LSFPulseEffectManagerCallbackDelegate>)pemDelegate
{
    self = [super init];

    if (self)
    {
        self.pulseEffectManagerCallback = new LSFPulseEffectManagerCallback(pemDelegate);
        self.handle = new lsf::PulseEffectManager(*(static_cast<lsf::ControllerClient*>(controllerClient.handle)), *(self.pulseEffectManagerCallback));
    }

    return self;
}

-(ControllerClientStatus)getAllPulseEffectIDs
{
    return self.pulseEffectManager->GetAllPulseEffectIDs();
}

-(ControllerClientStatus)getPulseEffectWithID: (NSString *)pulseEffectID
{
    std::string peid([pulseEffectID UTF8String]);
    return self.pulseEffectManager->GetPulseEffect(peid);
}

-(ControllerClientStatus)applyPulseEffectWithID: (NSString *)pulseEffectID onLamps: (NSArray *)lampIDs
{
    std::string peid([pulseEffectID UTF8String]);
    LSFStringList lids;

    for (NSString *lid in lampIDs)
    {
        lids.push_back([lid UTF8String]);
    }

    return self.pulseEffectManager->ApplyPulseEffectOnLamps(peid, lids);
}

-(ControllerClientStatus)applyPulseEffectWithID: (NSString *)pulseEffectID onLampGroups: (NSArray *)lampGroupIDs
{
    std::string peid([pulseEffectID UTF8String]);
    LSFStringList lgids;

    for (NSString *lgid in lampGroupIDs)
    {
        lgids.push_back([lgid UTF8String]);
    }

    return self.pulseEffectManager->ApplyPulseEffectOnLampGroups(peid, lgids);
}

-(ControllerClientStatus)getPulseEffectNameWithID: (NSString *)pulseEffectID
{
    std::string peid([pulseEffectID UTF8String]);
    return self.pulseEffectManager->GetPulseEffectName(peid);
}

-(ControllerClientStatus)getPulseEffectNameWithID: (NSString *)pulseEffectID andLanguage: (NSString *)language
{
    std::string peid([pulseEffectID UTF8String]);
    std::string lang([language UTF8String]);
    return self.pulseEffectManager->GetPulseEffectName(peid, lang);
}

-(ControllerClientStatus)setPulseEffectNameWithID: (NSString *)pulseEffectID pulseEffectName: (NSString *)pulseEffectName
{
    std::string peid([pulseEffectID UTF8String]);
    std::string name([pulseEffectName UTF8String]);
    return self.pulseEffectManager->SetPulseEffectName(peid, name);
}

-(ControllerClientStatus)setPulseEffectNameWithID: (NSString *)pulseEffectID pulseEffectName: (NSString *)pulseEffectName andLanguage: (NSString *)language
{
    std::string peid([pulseEffectID UTF8String]);
    std::string name([pulseEffectName UTF8String]);
    std::string lang([language UTF8String]);
    return self.pulseEffectManager->SetPulseEffectName(peid, name, lang);
}

-(ControllerClientStatus)createPulseEffectWithTracking: (uint32_t *)trackingID pulseEffect: (LSFPulseEffectV2 *)pulseEffect andPulseEffectName: (NSString *)pulseEffectName
{
    std::string name([pulseEffectName UTF8String]);
    return self.pulseEffectManager->CreatePulseEffect(*trackingID, *static_cast<lsf::PulseEffect*>(pulseEffect.handle), name);
}

-(ControllerClientStatus)createPulseEffectWithTracking: (uint32_t *)trackingID pulseEffect: (LSFPulseEffectV2 *)pulseEffect pulseEffectName: (NSString *)pulseEffectName andLanguage: (NSString *)language
{
    std::string name([pulseEffectName UTF8String]);
    std::string lang([language UTF8String]);
    return self.pulseEffectManager->CreatePulseEffect(*trackingID, *static_cast<lsf::PulseEffect*>(pulseEffect.handle), name, lang);
}

-(ControllerClientStatus)updatePulseEffectWithID: (NSString *)pulseEffectID andPulseEffect: (LSFPulseEffectV2 *)pulseEffect
{
    std::string peid([pulseEffectID UTF8String]);
    return self.pulseEffectManager->UpdatePulseEffect(peid, *static_cast<lsf::PulseEffect*>(pulseEffect.handle));
}

-(ControllerClientStatus)deletePulseEffectWithID: (NSString *)pulseEffectID
{
    std::string peid([pulseEffectID UTF8String]);
    return self.pulseEffectManager->DeletePulseEffect(peid);
}

-(ControllerClientStatus)getPulseEffectDataSetWithID: (NSString *)pulseEffectID
{
    std::string peid([pulseEffectID UTF8String]);
    return self.pulseEffectManager->GetPulseEffectDataSet(peid);
}

-(ControllerClientStatus)getPulseEffectDataSetWithID: (NSString *)pulseEffectID andLanguage: (NSString *)language
{
    std::string peid([pulseEffectID UTF8String]);
    std::string lang([language UTF8String]);
    return self.pulseEffectManager->GetPulseEffectDataSet(peid, lang);
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
-(lsf::PulseEffectManager *)pulseEffectManager
{
    return static_cast<lsf::PulseEffectManager*>(self.handle);
}

@end
