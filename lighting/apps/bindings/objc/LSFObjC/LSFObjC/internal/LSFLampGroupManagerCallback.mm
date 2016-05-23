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

#import "LSFLampGroupManagerCallback.h"

LSFLampGroupManagerCallback::LSFLampGroupManagerCallback(id<LSFLampGroupManagerCallbackDelegate> delegate) : _lgmDelegate(delegate)
{
    //Empty Constructor
}

LSFLampGroupManagerCallback::~LSFLampGroupManagerCallback()
{
    _lgmDelegate = nil;
}

void LSFLampGroupManagerCallback::GetAllLampGroupIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& lampGroupIDs)
{
    NSMutableArray *groupIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = lampGroupIDs.begin(); iter != lampGroupIDs.end(); ++iter)
    {
        [groupIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate getAllLampGroupIDsReplyWithCode: responseCode andGroupIDs: groupIDsArray];
    }
}

void LSFLampGroupManagerCallback::GetLampGroupNameReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID, const LSFString& language, const LSFString& lampGroupName)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate getLampGroupNameReplyWithCode: responseCode groupID: [NSString stringWithUTF8String: lampGroupID.c_str()] language: [NSString stringWithUTF8String: language.c_str()] andGroupName: [NSString stringWithUTF8String: lampGroupName.c_str()]];
    }
}

void LSFLampGroupManagerCallback::SetLampGroupNameReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID, const LSFString& language)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate setLampGroupNameReplyWithCode: responseCode groupID: [NSString stringWithUTF8String: lampGroupID.c_str()] andLanguage: [NSString stringWithUTF8String: language.c_str()]];
    }
}

void LSFLampGroupManagerCallback::LampGroupsNameChangedCB(const LSFStringList& lampGroupIDs)
{
    NSMutableArray *groupIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = lampGroupIDs.begin(); iter != lampGroupIDs.end(); ++iter)
    {
        [groupIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate lampGroupsNameChanged: groupIDsArray];
    }
}

void LSFLampGroupManagerCallback::CreateLampGroupReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate createLampGroupReplyWithCode: responseCode andGroupID: [NSString stringWithUTF8String: lampGroupID.c_str()]];
    }
}

void LSFLampGroupManagerCallback::CreateLampGroupWithTrackingReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID, const uint32_t& trackingID)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate createLampGroupTrackingReplyWithCode: responseCode groupID: [NSString stringWithUTF8String: lampGroupID.c_str()] andTrackingID: trackingID];
    }
}

void LSFLampGroupManagerCallback::LampGroupsCreatedCB(const LSFStringList& lampGroupIDs)
{
    NSMutableArray *groupIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = lampGroupIDs.begin(); iter != lampGroupIDs.end(); ++iter)
    {
        [groupIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate lampGroupsCreated: groupIDsArray];
    }
}

void LSFLampGroupManagerCallback::GetLampGroupReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID, const LampGroup& lampGroup)
{
    LSFStringList lamps = lampGroup.lamps;
    NSMutableArray *lampIDsArray = [[NSMutableArray alloc] init];

    for (std::list<LSFString>::const_iterator iter = lamps.begin(); iter != lamps.end(); ++iter)
    {
        [lampIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    LSFStringList groups = lampGroup.lampGroups;
    NSMutableArray *groupIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = groups.begin(); iter != groups.end(); ++iter)
    {
        [groupIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    LSFLampGroup *lsfLampGroup = [[LSFLampGroup alloc] init];
    [lsfLampGroup setLamps: lampIDsArray];
    [lsfLampGroup setLampGroups: groupIDsArray];
    
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate getLampGroupReplyWithCode: responseCode groupID: [NSString stringWithUTF8String: lampGroupID.c_str()] andLampGroup: lsfLampGroup];
    }
}

void LSFLampGroupManagerCallback::DeleteLampGroupReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate deleteLampGroupReplyWithCode: responseCode andGroupID: [NSString stringWithUTF8String: lampGroupID.c_str()]];
    }
}

void LSFLampGroupManagerCallback::LampGroupsDeletedCB(const LSFStringList& lampGroupIDs)
{
    NSMutableArray *groupIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = lampGroupIDs.begin(); iter != lampGroupIDs.end(); ++iter)
    {
        [groupIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate lampGroupsDeleted: groupIDsArray];
    }
}

void LSFLampGroupManagerCallback::TransitionLampGroupStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate transitionLampGroupToStateReplyWithCode: responseCode andGroupID: [NSString stringWithUTF8String: lampGroupID.c_str()]];
    }
}

void LSFLampGroupManagerCallback::PulseLampGroupWithStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate pulseLampGroupWithStateReplyWithCode: responseCode andGroupID: [NSString stringWithUTF8String: lampID.c_str()]];
    }
}

void LSFLampGroupManagerCallback::PulseLampGroupWithPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate pulseLampGroupWithPresetReplyWithCode: responseCode andGroupID: [NSString stringWithUTF8String: lampID.c_str()]];
    }
}

void LSFLampGroupManagerCallback::TransitionLampGroupStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate transitionLampGroupStateOnOffFieldReplyWithCode: responseCode andGroupID: [NSString stringWithUTF8String: lampGroupID.c_str()]];
    }
}

void LSFLampGroupManagerCallback::TransitionLampGroupStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate transitionLampGroupStateHueFieldReplyWithCode: responseCode andGroupID: [NSString stringWithUTF8String: lampGroupID.c_str()]];
    }
}

void LSFLampGroupManagerCallback::TransitionLampGroupStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate transitionLampGroupStateSaturationFieldReplyWithCode: responseCode andGroupID: [NSString stringWithUTF8String: lampGroupID.c_str()]];
    }
}

void LSFLampGroupManagerCallback::TransitionLampGroupStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate transitionLampGroupStateBrightnessFieldReplyWithCode: responseCode andGroupID: [NSString stringWithUTF8String: lampGroupID.c_str()]];
    }
}

void LSFLampGroupManagerCallback::TransitionLampGroupStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate transitionLampGroupStateColorTempFieldReplyWithCode: responseCode andGroupID: [NSString stringWithUTF8String: lampGroupID.c_str()]];
    }
}

void LSFLampGroupManagerCallback::ResetLampGroupStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate resetLampGroupStateReplyWithCode: responseCode andGroupID: [NSString stringWithUTF8String: lampGroupID.c_str()]];
    }
}

void LSFLampGroupManagerCallback::ResetLampGroupStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate resetLampGroupStateOnOffFieldReplyWithCode: responseCode andGroupID: [NSString stringWithUTF8String: lampGroupID.c_str()]];
    }
}

void LSFLampGroupManagerCallback::ResetLampGroupStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate resetLampGroupStateHueFieldReplyWithCode: responseCode andGroupID: [NSString stringWithUTF8String: lampGroupID.c_str()]];
    }
}

void LSFLampGroupManagerCallback::ResetLampGroupStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate resetLampGroupStateSaturationFieldReplyWithCode: responseCode andGroupID: [NSString stringWithUTF8String: lampGroupID.c_str()]];
    }
}

void LSFLampGroupManagerCallback::ResetLampGroupStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate resetLampGroupStateBrightnessFieldReplyWithCode: responseCode andGroupID: [NSString stringWithUTF8String: lampGroupID.c_str()]];
    }
}

void LSFLampGroupManagerCallback::ResetLampGroupStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate resetLampGroupStateColorTempFieldReplyWithCode: responseCode andGroupID: [NSString stringWithUTF8String: lampGroupID.c_str()]];
    }
}

void LSFLampGroupManagerCallback::UpdateLampGroupReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate updateLampGroupReplyWithCode: responseCode andGroupID: [NSString stringWithUTF8String: lampGroupID.c_str()]];
    }
}

void LSFLampGroupManagerCallback::LampGroupsUpdatedCB(const LSFStringList& lampGroupIDs)
{
    NSMutableArray *groupIDsArray = [[NSMutableArray alloc] init];
    
    for (std::list<LSFString>::const_iterator iter = lampGroupIDs.begin(); iter != lampGroupIDs.end(); ++iter)
    {
        [groupIDsArray addObject: [NSString stringWithUTF8String: (*iter).c_str()]];
    }
    
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate lampGroupsUpdated: groupIDsArray];
    }
}

void LSFLampGroupManagerCallback::TransitionLampGroupStateToPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate transitionLampGroupStateToPresetReplyWithCode: responseCode andGroupID: [NSString stringWithUTF8String: lampGroupID.c_str()]];
    }
}

void LSFLampGroupManagerCallback::SetLampGroupEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID, const LSFString& effectID)
{
    if (_lgmDelegate != nil)
    {
        [_lgmDelegate setLampGroupEffectReplyWithCode: responseCode groupID: [NSString stringWithUTF8String: lampGroupID.c_str()] andEffectID: [NSString stringWithUTF8String: effectID.c_str()]];
    }
}
