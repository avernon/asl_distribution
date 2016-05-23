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

#import "LSFPresetManager.h"
#import "LSFPresetManagerCallback.h"

@interface LSFPresetManager()

@property (nonatomic, readonly) lsf::PresetManager *presetManager;
@property (nonatomic, assign) LSFPresetManagerCallback *presetManagerCallback;

@end

@implementation LSFPresetManager

@synthesize presetManager =_presetManager;
@synthesize presetManagerCallback = _presetManagerCallback;

-(id)initWithControllerClient: (LSFControllerClient *)controllerClient andPresetManagerCallbackDelegate: (id<LSFPresetManagerCallbackDelegate>)pmDelegate
{
    self = [super init];
    
    if (self)
    {
        self.presetManagerCallback = new LSFPresetManagerCallback(pmDelegate);
        self.handle = new lsf::PresetManager(*(static_cast<lsf::ControllerClient*>(controllerClient.handle)), *(self.presetManagerCallback));
    }
    
    return self;
}

-(ControllerClientStatus)getAllPresetIDs
{
    return self.presetManager->GetAllPresetIDs();
}

-(ControllerClientStatus)getPresetWithID: (NSString *)presetID
{
    std::string pid([presetID UTF8String]);
    return self.presetManager->GetPreset(pid);
}

-(ControllerClientStatus)getPresetNameWithID: (NSString *)presetID
{
    std::string pid([presetID UTF8String]);
    return self.presetManager->GetPresetName(pid);
}

-(ControllerClientStatus)getPresetNameWithID: (NSString *)presetID andLanguage: (NSString *)language
{
    std::string pid([presetID UTF8String]);
    std::string lang([language UTF8String]);
    return self.presetManager->GetPresetName(pid, lang);
}

-(ControllerClientStatus)setPresetNameWithID: (NSString *)presetID andPresetName: (NSString *)name
{
    std::string pid([presetID UTF8String]);
    std::string presetName([name UTF8String]);
    return self.presetManager->SetPresetName(pid, presetName);
}

-(ControllerClientStatus)setPresetNameWithID: (NSString *)presetID presetName: (NSString *)name andLanguage: (NSString *)language
{
    std::string pid([presetID UTF8String]);
    std::string presetName([name UTF8String]);
    std::string lang([language UTF8String]);
    return self.presetManager->SetPresetName(pid, presetName, lang);
}

-(ControllerClientStatus)createPresetWithState: (LSFLampState *)preset andPresetName: (NSString *)name
{
    std::string presetName([name UTF8String]);
    return self.presetManager->CreatePreset(*static_cast<lsf::LampState*>(preset.handle), presetName);
}

-(ControllerClientStatus)createPresetWithState: (LSFLampState *)preset presetName: (NSString *)name andLanguage: (NSString *)language
{
    std::string presetName([name UTF8String]);
    std::string lang([language UTF8String]);
    return self.presetManager->CreatePreset(*static_cast<lsf::LampState*>(preset.handle), presetName, lang);
}

-(ControllerClientStatus)updatePresetWithID: (NSString *)presetID andState: (LSFLampState *)preset
{
    std::string pid([presetID UTF8String]);
    return self.presetManager->UpdatePreset(pid, *static_cast<lsf::LampState*>(preset.handle));
}

-(ControllerClientStatus)deletePresetWithID: (NSString *)presetID
{
    std::string pid([presetID UTF8String]);
    return self.presetManager->DeletePreset(pid);
}

-(ControllerClientStatus)getDefaultLampState
{
    return self.presetManager->GetDefaultLampState();
}

-(ControllerClientStatus)setDefaultLampState: (LSFLampState *)defaultLampState
{
    return self.presetManager->SetDefaultLampState(*static_cast<lsf::LampState*>(defaultLampState.handle));
}

-(ControllerClientStatus)getPresetDataSetWithID: (NSString *)presetID
{
    std::string pid([presetID UTF8String]);
    return self.presetManager->GetPresetDataSet(pid);
}

-(ControllerClientStatus)getPresetDataSetWithID: (NSString *)presetID andLanguage: (NSString *)language
{
    std::string pid([presetID UTF8String]);
    std::string lang([language UTF8String]);
    return self.presetManager->GetPresetDataSet(pid, lang);
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
-(lsf::PresetManager *)presetManager
{
    return static_cast<lsf::PresetManager*>(self.handle);
}

@end
