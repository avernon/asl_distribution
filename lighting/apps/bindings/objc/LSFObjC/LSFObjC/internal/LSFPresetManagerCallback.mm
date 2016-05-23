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

#import "LSFPresetManagerCallback.h"

LSFPresetManagerCallback::LSFPresetManagerCallback(id<LSFPresetManagerCallbackDelegate> delegate) : _pmDelegate(delegate)
{
    //Empty Constructor
}

LSFPresetManagerCallback::~LSFPresetManagerCallback()
{
    _pmDelegate = nil;
}

void LSFPresetManagerCallback::GetPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const LampState& preset)
{
    LSFLampState *presetState = [[LSFLampState alloc] init];
    presetState.onOff = preset.onOff;
    presetState.brightness = preset.brightness;
    presetState.hue = preset.hue;
    presetState.saturation = preset.saturation;
    presetState.colorTemp = preset.colorTemp;
    
    if (_pmDelegate != nil)
    {
        [_pmDelegate getPresetReplyWithCode: responseCode presetID: [NSString stringWithUTF8String: presetID.c_str()] andPreset: presetState];
    }
}

void LSFPresetManagerCallback::GetAllPresetIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& presetIDs)
{
    NSMutableArray *presetIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = presetIDs.begin(); iter != presetIDs.end(); ++iter)
    {
        [presetIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_pmDelegate != nil)
    {
        [_pmDelegate getAllPresetIDsReplyWithCode: responseCode andPresetIDs: presetIDsArray];
    }
}

void LSFPresetManagerCallback::GetPresetNameReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const LSFString& language, const LSFString& presetName)
{
    if (_pmDelegate != nil)
    {
        [_pmDelegate getPresetNameReplyWithCode: responseCode presetID: [NSString stringWithUTF8String: presetID.c_str()] language: [NSString stringWithUTF8String: language.c_str()] andPresetName: [NSString stringWithUTF8String: presetName.c_str()]];
    }
}

void LSFPresetManagerCallback::SetPresetNameReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const LSFString& language)
{
    if (_pmDelegate != nil)
    {
        [_pmDelegate setPresetNameReplyWithCode: responseCode presetID: [NSString stringWithUTF8String: presetID.c_str()] andLanguage: [NSString stringWithUTF8String: language.c_str()]];
    }
}

void LSFPresetManagerCallback::PresetsNameChangedCB(const LSFStringList& presetIDs)
{
    NSMutableArray *presetIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = presetIDs.begin(); iter != presetIDs.end(); ++iter)
    {
        [presetIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_pmDelegate != nil)
    {
        [_pmDelegate presetsNameChanged: presetIDsArray];
    }
}

void LSFPresetManagerCallback::CreatePresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID)
{
    if (_pmDelegate != nil)
    {
        [_pmDelegate createPresetReplyWithCode: responseCode andPresetID: [NSString stringWithUTF8String: presetID.c_str()]];
    }
}

void LSFPresetManagerCallback::CreatePresetWithTrackingReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const uint32_t& trackingID)
{
    if (_pmDelegate != nil)
    {
        [_pmDelegate createPresetTrackingReplyWithCode: responseCode presetID: [NSString stringWithUTF8String: presetID.c_str()] andTrackingID: trackingID];
    }
}

void LSFPresetManagerCallback::PresetsCreatedCB(const LSFStringList& presetIDs)
{
    NSMutableArray *presetIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = presetIDs.begin(); iter != presetIDs.end(); ++iter)
    {
        [presetIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_pmDelegate != nil)
    {
        [_pmDelegate presetsCreated: presetIDsArray];
    }
}

void LSFPresetManagerCallback::UpdatePresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID)
{
    if (_pmDelegate != nil)
    {
        [_pmDelegate updatePresetReplyWithCode: responseCode andPresetID: [NSString stringWithUTF8String: presetID.c_str()]];
    }
}

void LSFPresetManagerCallback::PresetsUpdatedCB(const LSFStringList& presetIDs)
{
    NSMutableArray *presetIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = presetIDs.begin(); iter != presetIDs.end(); ++iter)
    {
        [presetIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_pmDelegate != nil)
    {
        [_pmDelegate presetsUpdated: presetIDsArray];
    }
}

void LSFPresetManagerCallback::DeletePresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID)
{
    if (_pmDelegate != nil)
    {
        [_pmDelegate deletePresetReplyWithCode: responseCode andPresetID: [NSString stringWithUTF8String: presetID.c_str()]];
    }
}

void LSFPresetManagerCallback::PresetsDeletedCB(const LSFStringList& presetIDs)
{
    NSMutableArray *presetIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = presetIDs.begin(); iter != presetIDs.end(); ++iter)
    {
        [presetIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_pmDelegate != nil)
    {
        [_pmDelegate presetsDeleted: presetIDsArray];
    }
}

void LSFPresetManagerCallback::GetDefaultLampStateReplyCB(const LSFResponseCode& responseCode, const LampState& defaultLampState)
{
    LSFLampState *defaultState = [[LSFLampState alloc] init];
    defaultState.onOff = defaultLampState.onOff;
    defaultState.brightness = defaultLampState.brightness;
    defaultState.hue = defaultLampState.hue;
    defaultState.saturation = defaultLampState.saturation;
    defaultState.colorTemp = defaultLampState.colorTemp;
    
    if (_pmDelegate != nil)
    {
        [_pmDelegate getDefaultLampStateReplyWithCode: responseCode andLampState: defaultState];
    }
}

void LSFPresetManagerCallback::SetDefaultLampStateReplyCB(const LSFResponseCode& responseCode)
{
    if (_pmDelegate != nil)
    {
        [_pmDelegate setDefaultLampStateReplyWithCode: responseCode];
    }
}

void LSFPresetManagerCallback::DefaultLampStateChangedCB(void)
{
    if (_pmDelegate != nil)
    {
        [_pmDelegate defaultLampStateChanged];
    }
}
