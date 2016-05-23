/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

#include <PresetManager.h>
#include <ControllerClient.h>
#include <qcc/Debug.h>

using namespace lsf;
using namespace ajn;

#define QCC_MODULE "PRESET_MANAGER"

PresetManager::PresetManager(ControllerClient& controllerClient, PresetManagerCallback& callback) :
    Manager(controllerClient),
    callback(callback)
{
    controllerClient.presetManagerPtr = this;
}

ControllerClientStatus PresetManager::GetAllPresetIDs(void)
{
    QCC_DbgPrintf(("%s", __func__));
    return controllerClient.MethodCallAsyncForReplyWithResponseCodeAndListOfIDs(
               ControllerServicePresetInterfaceName,
               "GetAllPresetIDs");
}

ControllerClientStatus PresetManager::GetPreset(const LSFString& presetID)
{
    QCC_DbgPrintf(("%s: presetID=%s", __func__, presetID.c_str()));
    MsgArg arg;
    arg.Set("s", presetID.c_str());

    ControllerClientStatus status = controllerClient.MethodCallAsync(
        ControllerServicePresetInterfaceName,
        "GetPreset",
        this,
        &PresetManager::GetPresetReply,
        &arg,
        1);

    return status;
}

void PresetManager::GetPresetReply(Message& message)
{
    QCC_DbgPrintf(("%s: Method Reply %s", __func__, (MESSAGE_METHOD_RET == message->GetType()) ? message->ToString().c_str() : "ERROR"));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerClient.CheckNumArgsInMessage(numArgs, 3) != LSF_OK) {
        return;
    }

    LSFResponseCode responseCode = static_cast<LSFResponseCode>(args[0].v_uint32);
    LSFString presetID = static_cast<LSFString>(args[1].v_string.str);
    LampState preset(args[2]);
    callback.GetPresetReplyCB(responseCode, presetID, preset);
}

ControllerClientStatus PresetManager::GetPresetName(const LSFString& presetID, const LSFString& language)
{
    QCC_DbgPrintf(("%s: presetID=%s", __func__, presetID.c_str()));
    MsgArg args[2];
    args[0].Set("s", presetID.c_str());
    args[1].Set("s", language.c_str());
    return controllerClient.MethodCallAsyncForReplyWithResponseCodeIDLanguageAndName(
               ControllerServicePresetInterfaceName,
               "GetPresetName",
               args,
               2);
}

ControllerClientStatus PresetManager::SetPresetName(const LSFString& presetID, const LSFString& presetName, const LSFString& language)
{
    QCC_DbgPrintf(("%s: presetID=%s presetName=%s language=%s", __func__, presetID.c_str(), presetName.c_str(), language.c_str()));

    MsgArg args[3];
    args[0].Set("s", presetID.c_str());
    args[1].Set("s", presetName.c_str());
    args[2].Set("s", language.c_str());

    return controllerClient.MethodCallAsyncForReplyWithResponseCodeIDAndName(
               ControllerServicePresetInterfaceName,
               "SetPresetName",
               args,
               3);
}

ControllerClientStatus PresetManager::CreatePreset(const LampState& preset, const LSFString& presetName, const LSFString& language)
{
    //QCC_DbgPrintf(("%s: preset=%s", __func__, preset.c_str()));

    MsgArg arg[3];
    preset.Get(&arg[0], true);
    arg[1].Set("s", presetName.c_str());
    arg[2].Set("s", language.c_str());

    return controllerClient.MethodCallAsyncForReplyWithResponseCodeAndID(
               ControllerServicePresetInterfaceName,
               "CreatePreset",
               arg,
               3);
}

ControllerClientStatus PresetManager::CreatePresetWithTracking(uint32_t& trackingID, const LampState& preset, const LSFString& presetName, const LSFString& language)
{
    //QCC_DbgPrintf(("%s: preset=%s", __func__, preset.c_str()));

    MsgArg arg[3];
    preset.Get(&arg[0], true);
    arg[1].Set("s", presetName.c_str());
    arg[2].Set("s", language.c_str());

    return controllerClient.MethodCallAsyncForReplyWithResponseCodeIDAndTrackingID(
               trackingID,
               ControllerServicePresetInterfaceName,
               "CreatePreset",
               arg,
               3);
}

ControllerClientStatus PresetManager::UpdatePreset(const LSFString& presetID, const LampState& preset)
{
    //QCC_DbgPrintf(("%s: presetID=%s preset=%s", __func__, presetID.c_str(), preset.c_str()));
    MsgArg args[2];
    args[0].Set("s", presetID.c_str());
    preset.Get(&args[1]);

    return controllerClient.MethodCallAsyncForReplyWithResponseCodeAndID(
               ControllerServicePresetInterfaceName,
               "UpdatePreset",
               args,
               2);
}

ControllerClientStatus PresetManager::DeletePreset(const LSFString& presetID)
{
    QCC_DbgPrintf(("%s: presetID=%s", __func__, presetID.c_str()));
    MsgArg arg;
    arg.Set("s", presetID.c_str());

    return controllerClient.MethodCallAsyncForReplyWithResponseCodeAndID(
               ControllerServicePresetInterfaceName,
               "DeletePreset",
               &arg,
               1);
}

ControllerClientStatus PresetManager::GetDefaultLampState(void)
{
    QCC_DbgPrintf(("%s", __func__));
    return controllerClient.MethodCallAsync(
               ControllerServicePresetInterfaceName,
               "GetDefaultLampState",
               this,
               &PresetManager::GetDefaultLampStateReply);
}

void PresetManager::GetDefaultLampStateReply(ajn::Message& message)
{
    QCC_DbgPrintf(("%s: Method Reply %s", __func__, (MESSAGE_METHOD_RET == message->GetType()) ? message->ToString().c_str() : "ERROR"));

    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerClient.CheckNumArgsInMessage(numArgs, 2) != LSF_OK) {
        return;
    }

    LSFResponseCode responseCode = static_cast<LSFResponseCode>(args[0].v_uint32);
    LampState defaultLampState(args[1]);

    callback.GetDefaultLampStateReplyCB(responseCode, defaultLampState);
}

ControllerClientStatus PresetManager::SetDefaultLampState(const LampState& defaultLampState)
{
    //QCC_DbgPrintf(("%s: defaultLampState=%s", __func__, defaultLampState.c_str()));

    MsgArg arg;
    defaultLampState.Get(&arg);

    return controllerClient.MethodCallAsyncForReplyWithUint32Value(
               ControllerServicePresetInterfaceName,
               "SetDefaultLampState",
               &arg,
               1);
}

ControllerClientStatus PresetManager::GetPresetDataSet(const LSFString& presetID, const LSFString& language)
{
    ControllerClientStatus status = CONTROLLER_CLIENT_OK;

    status = GetPreset(presetID);

    if (CONTROLLER_CLIENT_OK == status) {
        status = GetPresetName(presetID, language);
    }

    return status;
}
