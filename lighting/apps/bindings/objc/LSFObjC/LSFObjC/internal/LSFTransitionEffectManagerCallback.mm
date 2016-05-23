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

#import "LSFTransitionEffectManagerCallback.h"

LSFTransitionEffectManagerCallback::LSFTransitionEffectManagerCallback(id<LSFTransitionEffectManagerCallbackDelegate> delegate) : _temDelegate(delegate)
{
    //Empty Constructor
}

LSFTransitionEffectManagerCallback::~LSFTransitionEffectManagerCallback()
{
    _temDelegate = nil;
}

void LSFTransitionEffectManagerCallback::GetTransitionEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const TransitionEffect& transitionEffect)
{
    LSFLampState *lampState;

    if (transitionEffect.state.nullState)
    {
        lampState = [[LSFLampState alloc] init];
    }
    else
    {
        lampState = [[LSFLampState alloc] initWithOnOff: transitionEffect.state.onOff brightness: transitionEffect.state.brightness hue: transitionEffect.state.hue saturation: transitionEffect.state.saturation colorTemp:transitionEffect.state.colorTemp];
    }

    LSFTransitionEffectV2 *myTransitionEffect = [[LSFTransitionEffectV2 alloc] initWithLampState: lampState transitionPeriod: transitionEffect.transitionPeriod];
    myTransitionEffect.presetID = [NSString stringWithUTF8String: transitionEffect.presetID.c_str()];

    if (_temDelegate != nil)
    {
        [_temDelegate getTransitionEffectReplyWithCode: responseCode transitionEffectID: [NSString stringWithUTF8String: transitionEffectID.c_str()] andTransitionEffect: myTransitionEffect];
    }
}

void LSFTransitionEffectManagerCallback::ApplyTransitionEffectOnLampsReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const LSFStringList& lampIDs)
{
    NSMutableArray *lampIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = lampIDs.begin(); iter != lampIDs.end(); ++iter)
    {
        [lampIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    if (_temDelegate != nil)
    {
        [_temDelegate applyTransitionEffectOnLampsReplyWithCode: responseCode transitionEffectID: [NSString stringWithUTF8String: transitionEffectID.c_str()] andLampIDs: lampIDsArray];
    }
}

void LSFTransitionEffectManagerCallback::ApplyTransitionEffectOnLampGroupsReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const LSFStringList& lampGroupIDs)
{
    NSMutableArray *groupIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = lampGroupIDs.begin(); iter != lampGroupIDs.end(); ++iter)
    {
        [groupIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    if (_temDelegate != nil)
    {
        [_temDelegate applyTransitionEffectOnLampGroupsReplyWithCode: responseCode transitionEffectID: [NSString stringWithUTF8String: transitionEffectID.c_str()] andLampGroupIDs: groupIDsArray];
    }
}

void LSFTransitionEffectManagerCallback::GetAllTransitionEffectIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& transitionEffectIDs)
{
    NSMutableArray *transitionEffectIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = transitionEffectIDs.begin(); iter != transitionEffectIDs.end(); ++iter)
    {
        [transitionEffectIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    if (_temDelegate != nil)
    {
        [_temDelegate getAllTransitionEffectIDsReplyWithCode: responseCode transitionEffectIDs: transitionEffectIDsArray];
    }
}

void LSFTransitionEffectManagerCallback::GetTransitionEffectNameReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const LSFString& language, const LSFString& transitionEffectName)
{
    if (_temDelegate != nil)
    {
        [_temDelegate getTransitionEffectNameReplyWithCode: responseCode transitionEffectID: [NSString stringWithUTF8String: transitionEffectID.c_str()] language: [NSString stringWithUTF8String: language.c_str()] andTransitionEffectName: [NSString stringWithUTF8String: transitionEffectName.c_str()]];
    }
}

void LSFTransitionEffectManagerCallback::SetTransitionEffectNameReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const LSFString& language)
{
    if (_temDelegate != nil)
    {
        [_temDelegate setTransitionEffectNameReplyWithCode: responseCode transitionEffectID: [NSString stringWithUTF8String: transitionEffectID.c_str()] andLanguage: [NSString stringWithUTF8String: language.c_str()]];
    }
}

void LSFTransitionEffectManagerCallback::TransitionEffectsNameChangedCB(const LSFStringList& transitionEffectIDs)
{
    NSMutableArray *transitionEffectIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = transitionEffectIDs.begin(); iter != transitionEffectIDs.end(); ++iter)
    {
        [transitionEffectIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    if (_temDelegate != nil)
    {
        [_temDelegate transitionEffectsNameChanged: transitionEffectIDsArray];
    }
}

void LSFTransitionEffectManagerCallback::CreateTransitionEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const uint32_t& trackingID)
{
    if (_temDelegate != nil)
    {
        [_temDelegate createTransitionEffectReplyWithCode: responseCode transitionEffectID: [NSString stringWithUTF8String: transitionEffectID.c_str()] andTrackingID: trackingID];
    }
}

void LSFTransitionEffectManagerCallback::TransitionEffectsCreatedCB(const LSFStringList& transitionEffectIDs)
{
    NSMutableArray *transitionEffectIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = transitionEffectIDs.begin(); iter != transitionEffectIDs.end(); ++iter)
    {
        [transitionEffectIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    if (_temDelegate != nil)
    {
        [_temDelegate transitionEffectsCreated: transitionEffectIDsArray];
    }
}

void LSFTransitionEffectManagerCallback::UpdateTransitionEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID)
{
    if (_temDelegate != nil)
    {
        [_temDelegate updateTransitionEffectReplyWithCode: responseCode andTransitionEffectID: [NSString stringWithUTF8String: transitionEffectID.c_str()]];
    }
}

void LSFTransitionEffectManagerCallback::TransitionEffectsUpdatedCB(const LSFStringList& transitionEffectIDs)
{
    NSMutableArray *transitionEffectIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = transitionEffectIDs.begin(); iter != transitionEffectIDs.end(); ++iter)
    {
        [transitionEffectIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    if (_temDelegate != nil)
    {
        [_temDelegate transitionEffectsUpdated: transitionEffectIDsArray];
    }
}

void LSFTransitionEffectManagerCallback::DeleteTransitionEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID)
{
    if (_temDelegate != nil)
    {
        [_temDelegate deleteTransitionEffectReplyWithCode: responseCode andTransitionEffectID: [NSString stringWithUTF8String: transitionEffectID.c_str()]];
    }
}

void LSFTransitionEffectManagerCallback::TransitionEffectsDeletedCB(const LSFStringList& transitionEffectIDs)
{
    NSMutableArray *transitionEffectIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = transitionEffectIDs.begin(); iter != transitionEffectIDs.end(); ++iter)
    {
        [transitionEffectIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    if (_temDelegate != nil)
    {
        [_temDelegate transitionEffectsDeleted: transitionEffectIDsArray];
    }
}
