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

#import "LSFPulseEffectManagerCallback.h"

LSFPulseEffectManagerCallback::LSFPulseEffectManagerCallback(id<LSFPulseEffectManagerCallbackDelegate> delegate) : _pemDelegate(delegate)
{
    //Empty Constructor
}

LSFPulseEffectManagerCallback::~LSFPulseEffectManagerCallback()
{
    _pemDelegate = nil;
}

void LSFPulseEffectManagerCallback::GetPulseEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const PulseEffect& pulseEffect)
{
    LSFLampState *toLampState;
    LSFLampState *fromLampState;

    if (pulseEffect.toState.nullState)
    {
        toLampState = [[LSFLampState alloc] init];
    }
    else
    {
        toLampState = [[LSFLampState alloc] initWithOnOff: pulseEffect.toState.onOff brightness: pulseEffect.toState.brightness hue: pulseEffect.toState.hue saturation: pulseEffect.toState.saturation colorTemp:pulseEffect.toState.colorTemp];
    }

    if (pulseEffect.fromState.nullState)
    {
        fromLampState = [[LSFLampState alloc] init];
    }
    else
    {
        fromLampState = [[LSFLampState alloc] initWithOnOff: pulseEffect.fromState.onOff brightness: pulseEffect.fromState.brightness hue: pulseEffect.fromState.hue saturation: pulseEffect.fromState.saturation colorTemp:pulseEffect.fromState.colorTemp];
    }

    LSFPulseEffectV2 *myPulseEffect = [[LSFPulseEffectV2 alloc] initWithToLampState: toLampState period: pulseEffect.pulsePeriod duration: pulseEffect.pulseDuration numPulses: pulseEffect.numPulses fromLampState: fromLampState];
    myPulseEffect.toPreset = [NSString stringWithUTF8String: pulseEffect.toPreset.c_str()];
    myPulseEffect.fromPreset = [NSString stringWithUTF8String: pulseEffect.fromPreset.c_str()];

    if (_pemDelegate != nil)
    {
        [_pemDelegate getPulseEffectReplyWithCode: responseCode pulseEffectID: [NSString stringWithUTF8String: pulseEffectID.c_str()] andPulseEffect: myPulseEffect];
    }
}

void LSFPulseEffectManagerCallback::ApplyPulseEffectOnLampsReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const LSFStringList& lampIDs)
{
    NSMutableArray *lampIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = lampIDs.begin(); iter != lampIDs.end(); ++iter)
    {
        [lampIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    if (_pemDelegate != nil)
    {
        [_pemDelegate applyPulseEffectOnLampsReplyWithCode: responseCode pulseEffectID: [NSString stringWithUTF8String: pulseEffectID.c_str()] andLampIDs: lampIDsArray];
    }
}

void LSFPulseEffectManagerCallback::ApplyPulseEffectOnLampGroupsReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const LSFStringList& lampGroupIDs)
{
    NSMutableArray *groupIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = lampGroupIDs.begin(); iter != lampGroupIDs.end(); ++iter)
    {
        [groupIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    if (_pemDelegate != nil)
    {
        [_pemDelegate applyPulseEffectOnLampGroupsReplyWithCode: responseCode pulseEffectID: [NSString stringWithUTF8String: pulseEffectID.c_str()] andLampGroupIDs: groupIDsArray];
    }
}

void LSFPulseEffectManagerCallback::GetAllPulseEffectIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& pulseEffectIDs)
{
    NSMutableArray *pulseEffectIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = pulseEffectIDs.begin(); iter != pulseEffectIDs.end(); ++iter)
    {
        [pulseEffectIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    if (_pemDelegate != nil)
    {
        [_pemDelegate getAllPulseEffectIDsReplyWithCode: responseCode pulseEffectIDs: pulseEffectIDsArray];
    }
}

void LSFPulseEffectManagerCallback::GetPulseEffectNameReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const LSFString& language, const LSFString& pulseEffectName)
{
    if (_pemDelegate != nil)
    {
        [_pemDelegate getPulseEffectNameReplyWithCode: responseCode pulseEffectID: [NSString stringWithUTF8String: pulseEffectID.c_str()] language: [NSString stringWithUTF8String: language.c_str()] andPulseEffectName:[NSString stringWithUTF8String: pulseEffectName.c_str()]];
    }
}

void LSFPulseEffectManagerCallback::SetPulseEffectNameReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const LSFString& language)
{
    if (_pemDelegate != nil)
    {
        [_pemDelegate setPulseEffectNameReplyWithCode: responseCode pulseEffectID: [NSString stringWithUTF8String: pulseEffectID.c_str()] andLanguage: [NSString stringWithUTF8String: language.c_str()]];
    }
}

void LSFPulseEffectManagerCallback::PulseEffectsNameChangedCB(const LSFStringList& pulseEffectIDs)
{
    NSMutableArray *pulseEffectIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = pulseEffectIDs.begin(); iter != pulseEffectIDs.end(); ++iter)
    {
        [pulseEffectIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    if (_pemDelegate != nil)
    {
        [_pemDelegate pulseEffectsNameChanged: pulseEffectIDsArray];
    }
}

void LSFPulseEffectManagerCallback::CreatePulseEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const uint32_t& trackingID)
{
    if (_pemDelegate != nil)
    {
        [_pemDelegate createPulseEffectReplyWithCode: responseCode pulseEffectID: [NSString stringWithUTF8String: pulseEffectID.c_str()] andTrackingID: trackingID];
    }
}

void LSFPulseEffectManagerCallback::PulseEffectsCreatedCB(const LSFStringList& pulseEffectIDs)
{
    NSMutableArray *pulseEffectIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = pulseEffectIDs.begin(); iter != pulseEffectIDs.end(); ++iter)
    {
        [pulseEffectIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    if (_pemDelegate != nil)
    {
        [_pemDelegate pulseEffectsCreated: pulseEffectIDsArray];
    }
}

void LSFPulseEffectManagerCallback::UpdatePulseEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID)
{
    if (_pemDelegate != nil)
    {
        [_pemDelegate updatePulseEffectReplyWithCode: responseCode andPulseEffectID: [NSString stringWithUTF8String: pulseEffectID.c_str()]];
    }
}

void LSFPulseEffectManagerCallback::PulseEffectsUpdatedCB(const LSFStringList& pulseEffectIDs)
{
    NSMutableArray *pulseEffectIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = pulseEffectIDs.begin(); iter != pulseEffectIDs.end(); ++iter)
    {
        [pulseEffectIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    if (_pemDelegate != nil)
    {
        [_pemDelegate pulseEffectsUpdated: pulseEffectIDsArray];
    }
}

void LSFPulseEffectManagerCallback::DeletePulseEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID)
{
    if (_pemDelegate != nil)
    {
        [_pemDelegate deletePulseEffectReplyWithCode: responseCode andPulseEffectID: [NSString stringWithUTF8String: pulseEffectID.c_str()]];
    }
}

void LSFPulseEffectManagerCallback::PulseEffectsDeletedCB(const LSFStringList& pulseEffectIDs)
{
    NSMutableArray *pulseEffectIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = pulseEffectIDs.begin(); iter != pulseEffectIDs.end(); ++iter)
    {
        [pulseEffectIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    if (_pemDelegate != nil)
    {
        [_pemDelegate pulseEffectsDeleted: pulseEffectIDsArray];
    }
}