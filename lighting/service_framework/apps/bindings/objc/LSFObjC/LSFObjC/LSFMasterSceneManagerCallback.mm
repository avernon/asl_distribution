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

#import "LSFMasterSceneManagerCallback.h"
#import "LSFUtils.h"

LSFMasterSceneManagerCallback::LSFMasterSceneManagerCallback(id<LSFMasterSceneManagerCallbackDelegate> delegate) : _msmDelegate(delegate)
{
    //Empty Constructor
}

LSFMasterSceneManagerCallback::~LSFMasterSceneManagerCallback()
{
    _msmDelegate = nil;
}

void LSFMasterSceneManagerCallback::GetAllMasterSceneIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& masterSceneList)
{
    NSMutableArray *masterSceneIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = masterSceneList.begin(); iter != masterSceneList.end(); ++iter)
    {
        [masterSceneIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_msmDelegate != nil)
    {
        [_msmDelegate getAllMasterSceneIDsReplyWithCode: responseCode andMasterSceneIDs: masterSceneIDsArray];
    }
}

void LSFMasterSceneManagerCallback::GetMasterSceneNameReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const LSFString& language, const LSFString& masterSceneName)
{
    if (_msmDelegate != nil)
    {
        [_msmDelegate getMasterSceneNameReplyWithCode: responseCode masterSceneID: [NSString stringWithUTF8String: masterSceneID.c_str()] language: [NSString stringWithUTF8String: language.c_str()] andName: [NSString stringWithUTF8String: masterSceneName.c_str()]];
    }
}

void LSFMasterSceneManagerCallback::SetMasterSceneNameReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const LSFString& language)
{
    if (_msmDelegate != nil)
    {
        [_msmDelegate setMasterSceneNameReplyWithCode: responseCode masterSceneID: [NSString stringWithUTF8String: masterSceneID.c_str()] andLanguage: [NSString stringWithUTF8String: language.c_str()]];
    }
}

void LSFMasterSceneManagerCallback::MasterScenesNameChangedCB(const LSFStringList& masterSceneIDs)
{
    NSMutableArray *masterSceneIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = masterSceneIDs.begin(); iter != masterSceneIDs.end(); ++iter)
    {
        [masterSceneIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_msmDelegate != nil)
    {
        [_msmDelegate masterScenesNameChanged: masterSceneIDsArray];
    }
}

void LSFMasterSceneManagerCallback::CreateMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID)
{
    if (_msmDelegate != nil)
    {
        [_msmDelegate createMasterSceneReplyWithCode: responseCode andMasterSceneID: [NSString stringWithUTF8String: masterSceneID.c_str()]];
    }
}

void LSFMasterSceneManagerCallback::MasterScenesCreatedCB(const LSFStringList& masterSceneIDs)
{
    NSMutableArray *masterSceneIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = masterSceneIDs.begin(); iter != masterSceneIDs.end(); ++iter)
    {
        [masterSceneIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_msmDelegate != nil)
    {
        [_msmDelegate masterScenesCreated: masterSceneIDsArray];
    }
}

void LSFMasterSceneManagerCallback::GetMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const MasterScene& masterScene)
{
    LSFMasterScene *ms = [[LSFMasterScene alloc] initWithSceneIDs: [LSFUtils convertStringListToNSArray: masterScene.scenes]];
    
    if (_msmDelegate != nil)
    {
        [_msmDelegate getMasterSceneReplyWithCode: responseCode masterSceneID: [NSString stringWithUTF8String: masterSceneID.c_str()] andMasterScene: ms];
    }
}

void LSFMasterSceneManagerCallback::DeleteMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID)
{
    if (_msmDelegate != nil)
    {
        [_msmDelegate deleteMasterSceneReplyWithCode: responseCode andMasterSceneID: [NSString stringWithUTF8String: masterSceneID.c_str()]];
    }
}

void LSFMasterSceneManagerCallback::MasterScenesDeletedCB(const LSFStringList& masterSceneIDs)
{
    NSMutableArray *masterSceneIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = masterSceneIDs.begin(); iter != masterSceneIDs.end(); ++iter)
    {
        [masterSceneIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_msmDelegate != nil)
    {
        [_msmDelegate masterScenesDeleted: masterSceneIDsArray];
    }
}

void LSFMasterSceneManagerCallback::UpdateMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID)
{
    if (_msmDelegate != nil)
    {
        [_msmDelegate updateMasterSceneReplyWithCode: responseCode andMasterSceneID: [NSString stringWithUTF8String: masterSceneID.c_str()]];
    }
}

void LSFMasterSceneManagerCallback::MasterScenesUpdatedCB(const LSFStringList& masterSceneIDs)
{
    NSMutableArray *masterSceneIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = masterSceneIDs.begin(); iter != masterSceneIDs.end(); ++iter)
    {
        [masterSceneIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_msmDelegate != nil)
    {
        [_msmDelegate masterScenesUpdated: masterSceneIDsArray];
    }
}

void LSFMasterSceneManagerCallback::ApplyMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID)
{
    if (_msmDelegate != nil)
    {
        [_msmDelegate applyMasterSceneReplyWithCode: responseCode andMasterSceneID: [NSString stringWithUTF8String: masterSceneID.c_str()]];
    }
}

void LSFMasterSceneManagerCallback::MasterScenesAppliedCB(const LSFStringList& masterSceneIDs)
{
    NSMutableArray *masterSceneIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = masterSceneIDs.begin(); iter != masterSceneIDs.end(); ++iter)
    {
        [masterSceneIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_msmDelegate != nil)
    {
        [_msmDelegate masterScenesApplied: masterSceneIDsArray];
    }
}