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

#import "LSFSceneManagerCallback.h"
#import "LSFUtils.h"

LSFSceneManagerCallback::LSFSceneManagerCallback(id<LSFSceneManagerCallbackDelegate> delegate) : _smDelegate(delegate)
{
    //Empty Constructor
}

LSFSceneManagerCallback::~LSFSceneManagerCallback()
{
    _smDelegate = nil;
}

void LSFSceneManagerCallback::GetAllSceneIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& sceneIDs)
{
    NSMutableArray *sceneIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = sceneIDs.begin(); iter != sceneIDs.end(); ++iter)
    {
        [sceneIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_smDelegate != nil)
    {
        [_smDelegate getAllSceneIDsReplyWithCode: responseCode andSceneIDs: sceneIDsArray];
    }
}

void LSFSceneManagerCallback::GetSceneNameReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID, const LSFString& language, const LSFString& sceneName)
{
    if (_smDelegate != nil)
    {
        [_smDelegate getSceneNameReplyWithCode: responseCode sceneID: [NSString stringWithUTF8String: sceneID.c_str()] language: [NSString stringWithUTF8String: language.c_str()] andName: [NSString stringWithUTF8String: sceneName.c_str()]];
    }
}

void LSFSceneManagerCallback::SetSceneNameReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID, const LSFString& language)
{
    if (_smDelegate != nil)
    {
        [_smDelegate setSceneNameReplyWithCode: responseCode sceneID: [NSString stringWithUTF8String: sceneID.c_str()] andLanguage: [NSString stringWithUTF8String: language.c_str()]];
    }
}

void LSFSceneManagerCallback::ScenesNameChangedCB(const LSFStringList& sceneIDs)
{
    NSMutableArray *sceneIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = sceneIDs.begin(); iter != sceneIDs.end(); ++iter)
    {
        [sceneIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_smDelegate != nil)
    {
        [_smDelegate scenesNameChanged: sceneIDsArray];
    }
}

void LSFSceneManagerCallback::CreateSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID)
{
    if (_smDelegate != nil)
    {
        [_smDelegate createSceneReplyWithCode: responseCode andSceneID: [NSString stringWithUTF8String: sceneID.c_str()]];
    }
}

void LSFSceneManagerCallback::ScenesCreatedCB(const LSFStringList& sceneIDs)
{
    NSMutableArray *sceneIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = sceneIDs.begin(); iter != sceneIDs.end(); ++iter)
    {
        [sceneIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_smDelegate != nil)
    {
        [_smDelegate scenesCreated: sceneIDsArray];
    }
}

void LSFSceneManagerCallback::UpdateSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID)
{
    if (_smDelegate != nil)
    {
        [_smDelegate updateSceneReplyWithCode: responseCode andSceneID: [NSString stringWithUTF8String: sceneID.c_str()]];
    }
}

void LSFSceneManagerCallback::ScenesUpdatedCB(const LSFStringList& sceneIDs)
{
    NSMutableArray *sceneIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = sceneIDs.begin(); iter != sceneIDs.end(); ++iter)
    {
        [sceneIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_smDelegate != nil)
    {
        [_smDelegate scenesUpdated: sceneIDsArray];
    }
}

void LSFSceneManagerCallback::DeleteSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID)
{
    if (_smDelegate != nil)
    {
        [_smDelegate deleteSceneReplyWithCode: responseCode andSceneID: [NSString stringWithUTF8String: sceneID.c_str()]];
    }
}

void LSFSceneManagerCallback::ScenesDeletedCB(const LSFStringList& sceneIDs)
{
    NSMutableArray *sceneIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = sceneIDs.begin(); iter != sceneIDs.end(); ++iter)
    {
        [sceneIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_smDelegate != nil)
    {
        [_smDelegate scenesDeleted: sceneIDsArray];
    }
}

void LSFSceneManagerCallback::GetSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID, const Scene& data)
{
    NSArray *stateTransitionEffects = [LSFUtils convertStateTransitionEffectsToNSArray: data.transitionToStateComponent];
    NSArray *presetTransitionEffects = [LSFUtils convertPresetTransitionEffectsToNSArray: data.transitionToPresetComponent];
    NSArray *statePulseEffects = [LSFUtils convertStatePulseEffectsToNSArray: data.pulseWithStateComponent];
    NSArray *presetPulseEffects = [LSFUtils convertPresetPulseEffectsToNSArray: data.pulseWithPresetComponent];
    
    LSFScene *scene = [[LSFScene alloc] initWithStateTransitionEffects: stateTransitionEffects presetTransitionEffects: presetTransitionEffects statePulseEffects: statePulseEffects andPresetPulseEffects: presetPulseEffects];
    
    if (_smDelegate != nil)
    {
        [_smDelegate getSceneReplyWithCode: responseCode sceneID: [NSString stringWithUTF8String: sceneID.c_str()] andScene: scene];
    }
}

void LSFSceneManagerCallback::ApplySceneReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID)
{
    if (_smDelegate != nil)
    {
        [_smDelegate applySceneReplyWithCode: responseCode andSceneID: [NSString stringWithUTF8String: sceneID.c_str()]];
    }
}

void LSFSceneManagerCallback::ScenesAppliedCB(const LSFStringList& sceneIDs)
{
    NSMutableArray *sceneIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = sceneIDs.begin(); iter != sceneIDs.end(); ++iter)
    {
        [sceneIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_smDelegate != nil)
    {
        [_smDelegate scenesApplied: sceneIDsArray];
    }
}
