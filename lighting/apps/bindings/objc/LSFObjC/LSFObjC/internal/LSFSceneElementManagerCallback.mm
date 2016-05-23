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

#import "LSFSceneElementManagerCallback.h"
#import "LSFUtils.h"

LSFSceneElementManagerCallback::LSFSceneElementManagerCallback(id<LSFSceneElementManagerCallbackDelegate> delegate) : _semDelegate(delegate)
{
    //Empty Constructor
}

LSFSceneElementManagerCallback::~LSFSceneElementManagerCallback()
{
    _semDelegate = nil;
}

void LSFSceneElementManagerCallback::GetAllSceneElementIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& sceneElementIDs)
{
    NSMutableArray *sceneElementIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = sceneElementIDs.begin(); iter != sceneElementIDs.end(); ++iter)
    {
        [sceneElementIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    if (_semDelegate != nil)
    {
        [_semDelegate getAllSceneElementIDsReplyWithCode: responseCode andSceneElementIDs: sceneElementIDsArray];
    }
}

void LSFSceneElementManagerCallback::GetSceneElementNameReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID, const LSFString& language, const LSFString& sceneElementName)
{
    if (_semDelegate != nil)
    {
        [_semDelegate getSceneElementNameReplyWithCode: responseCode sceneElementID: [NSString stringWithUTF8String: sceneElementID.c_str()] language: [NSString stringWithUTF8String: language.c_str()] andSceneElementName:[NSString stringWithUTF8String: sceneElementName.c_str()]];
    }
}

void LSFSceneElementManagerCallback::SetSceneElementNameReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID, const LSFString& language)
{
    if (_semDelegate != nil)
    {
        [_semDelegate setSceneElementNameReplyWithCode: responseCode sceneElementID: [NSString stringWithUTF8String: sceneElementID.c_str()] andLanguage: [NSString stringWithUTF8String: language.c_str()]];
    }
}

void LSFSceneElementManagerCallback::SceneElementsNameChangedCB(const LSFStringList& sceneElementIDs)
{
    NSMutableArray *sceneElementIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = sceneElementIDs.begin(); iter != sceneElementIDs.end(); ++iter)
    {
        [sceneElementIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    if (_semDelegate != nil)
    {
        [_semDelegate sceneElementsNameChanged: sceneElementIDsArray];
    }
}

void LSFSceneElementManagerCallback::CreateSceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID, const uint32_t& trackingID)
{
    if (_semDelegate != nil)
    {
        [_semDelegate createSceneElementReplyWithCode: responseCode sceneElementID: [NSString stringWithUTF8String: sceneElementID.c_str()] andTrackingID: trackingID];
    }
}

void LSFSceneElementManagerCallback::SceneElementsCreatedCB(const LSFStringList& sceneElementIDs)
{
    NSMutableArray *sceneElementIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = sceneElementIDs.begin(); iter != sceneElementIDs.end(); ++iter)
    {
        [sceneElementIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    if (_semDelegate != nil)
    {
        [_semDelegate sceneElementsCreated: sceneElementIDsArray];
    }
}

void LSFSceneElementManagerCallback::UpdateSceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID)
{
    if (_semDelegate != nil)
    {
        [_semDelegate updateSceneElementReplyWithCode: responseCode andSceneElementID: [NSString stringWithUTF8String: sceneElementID.c_str()]];
    }
}

void LSFSceneElementManagerCallback::SceneElementsUpdatedCB(const LSFStringList& sceneElementIDs)
{
    NSMutableArray *sceneElementIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = sceneElementIDs.begin(); iter != sceneElementIDs.end(); ++iter)
    {
        [sceneElementIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    if (_semDelegate != nil)
    {
        [_semDelegate sceneElementsUpdated: sceneElementIDsArray];
    }
}

void LSFSceneElementManagerCallback::DeleteSceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID)
{
    if (_semDelegate != nil)
    {
        [_semDelegate deleteSceneElementReplyWithCode: responseCode andSceneElementID: [NSString stringWithUTF8String: sceneElementID.c_str()]];
    }
}

void LSFSceneElementManagerCallback::SceneElementsDeletedCB(const LSFStringList& sceneElementIDs)
{
    NSMutableArray *sceneElementIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = sceneElementIDs.begin(); iter != sceneElementIDs.end(); ++iter)
    {
        [sceneElementIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    if (_semDelegate != nil)
    {
        [_semDelegate sceneElementsDeleted: sceneElementIDsArray];
    }
}

void LSFSceneElementManagerCallback::GetSceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID, const SceneElement& sceneElement)
{
    NSArray *lampIDs = [LSFUtils convertStringListToNSArray: sceneElement.lamps];
    NSArray *lampGroupIDs = [LSFUtils convertStringListToNSArray: sceneElement.lampGroups];
    LSFSceneElement *mySceneElement = [[LSFSceneElement alloc] initWithLampIDs: lampIDs lampGroupIDs: lampGroupIDs andEffectID: [NSString stringWithUTF8String: sceneElement.effectID.c_str()]];

    if (_semDelegate != nil)
    {
        [_semDelegate getSceneElementReplyWithCode: responseCode sceneElementID: [NSString stringWithUTF8String: sceneElementID.c_str()] andSceneElement: mySceneElement];
    }
}

void LSFSceneElementManagerCallback::ApplySceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID)
{
    if (_semDelegate != nil)
    {
        [_semDelegate applySceneElementReplyWithCode: responseCode andSceneElementID: [NSString stringWithUTF8String: sceneElementID.c_str()]];
    }
}

void LSFSceneElementManagerCallback::SceneElementsAppliedCB(const LSFStringList& sceneElementIDs)
{
    NSMutableArray *sceneElementIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = sceneElementIDs.begin(); iter != sceneElementIDs.end(); ++iter)
    {
        [sceneElementIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }

    if (_semDelegate != nil)
    {
        [_semDelegate sceneElementsApplied: sceneElementIDsArray];
    }
}