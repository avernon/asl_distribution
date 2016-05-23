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

#ifdef LSF_BINDINGS
#include <lsf/controllerservice/LampManager.h>
#include <lsf/controllerservice/OEM_CS_Config.h>
#include <lsf/controllerservice/ControllerService.h>
#else
#include <LampManager.h>
#include <OEM_CS_Config.h>
#include <ControllerService.h>
#endif

#include <LSFResponseCodes.h>
#include <alljoyn/Status.h>
#include <qcc/Debug.h>

#include <algorithm>

using namespace lsf;
using namespace ajn;

#ifdef LSF_BINDINGS
using namespace controllerservice;
#define QCC_MODULE "CONTROLLER_LAMP_MANAGER"
#else
#define QCC_MODULE "LAMP_MANAGER"
#endif

LampManager::LampManager(ControllerService& controllerSvc, PresetManager& presetMgr)
    : Manager(controllerSvc), lampClients(controllerSvc), presetManager(presetMgr)
{
    QCC_DbgTrace(("%s", __func__));
}

LampManager::~LampManager()
{
    QCC_DbgTrace(("%s", __func__));
}

QStatus LampManager::Start(const char* keyStoreFileLocation)
{
    QCC_DbgPrintf(("%s", __func__));
    /*
     * Start the Lamp Clients
     */
    QStatus status = lampClients.Start(keyStoreFileLocation);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: Failed to start the Lamp Clients", __func__));
    }

    return status;
}

void LampManager::Stop(void)
{
    QCC_DbgPrintf(("%s", __func__));
    lampClients.Stop();
}

void LampManager::Join(void)
{
    QCC_DbgPrintf(("%s", __func__));
    lampClients.Join();
}

void LampManager::GetAllLampIDs(ajn::Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));

    lampClients.RequestAllLampIDs(message);
}

void LampManager::GetLampFaults(ajn::Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 1)  != LSF_OK) {
        return;
    }

    LSFString lampID = static_cast<LSFString>(args[0].v_string.str);
    QCC_DbgPrintf(("lampID=%s", lampID.c_str()));

    lampClients.GetLampFaults(lampID, message);
}

void LampManager::ClearLampFault(ajn::Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 2)  != LSF_OK) {
        return;
    }

    LSFString lampID = static_cast<LSFString>(args[0].v_string.str);
    LampFaultCode faultCode = static_cast<LampFaultCode>(args[1].v_uint32);
    QCC_DbgPrintf(("lampID=%s faultCode=%d", lampID.c_str(), faultCode));

    lampClients.ClearLampFault(lampID, faultCode, message);
}

void LampManager::GetLampServiceVersion(ajn::Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 1)  != LSF_OK) {
        return;
    }

    LSFString lampID = static_cast<LSFString>(args[0].v_string.str);
    QCC_DbgPrintf(("lampID=%s", lampID.c_str()));

    lampClients.GetLampVersion(lampID, message);
}

void LampManager::GetLampSupportedLanguages(Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 1)  != LSF_OK) {
        return;
    }

    LSFString lampID = static_cast<LSFString>(args[0].v_string.str);
    QCC_DbgPrintf(("lampID=%s", lampID.c_str()));

    lampClients.GetLampSupportedLanguages(lampID, message);
}

void LampManager::GetLampManufacturer(Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 2)  != LSF_OK) {
        return;
    }

    LSFString lampID = static_cast<LSFString>(args[0].v_string.str);
    LSFString language = static_cast<LSFString>(args[1].v_string.str);
    QCC_DbgPrintf(("lampID=%s language=%s", lampID.c_str(), language.c_str()));

    lampClients.GetLampManufacturer(lampID, language, message);
}

void LampManager::GetLampName(Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 2)  != LSF_OK) {
        return;
    }

    LSFString lampID = static_cast<LSFString>(args[0].v_string.str);
    LSFString language = static_cast<LSFString>(args[1].v_string.str);

    QCC_DbgPrintf(("lampID=%s language=%s", lampID.c_str(), language.c_str()));

    lampClients.GetLampName(lampID, language, message);
}

void LampManager::SetLampName(ajn::Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 3)  != LSF_OK) {
        return;
    }

    LSFString lampID = static_cast<LSFString>(args[0].v_string.str);
    LSFString lampName = static_cast<LSFString>(args[1].v_string.str);
    LSFString language = static_cast<LSFString>(args[2].v_string.str);

    QCC_DbgPrintf(("lampID=%s lampName=%s language=%s", lampID.c_str(), lampName.c_str(), language.c_str()));

    lampClients.SetLampName(lampID, lampName, language, message);
}

void LampManager::GetLampDetails(ajn::Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 1)  != LSF_OK) {
        return;
    }

    LSFString lampID = static_cast<LSFString>(args[0].v_string.str);
    QCC_DbgPrintf(("lampID=%s", lampID.c_str()));

    lampClients.GetLampDetails(lampID, message);
}

void LampManager::GetLampParameters(ajn::Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 1)  != LSF_OK) {
        return;
    }

    LSFString lampID = static_cast<LSFString>(args[0].v_string.str);
    QCC_DbgPrintf(("lampID=%s", lampID.c_str()));


    lampClients.GetLampParameters(lampID, message);
}

void LampManager::GetLampParametersField(ajn::Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 2)  != LSF_OK) {
        return;
    }

    LSFString lampID = static_cast<LSFString>(args[0].v_string.str);
    LSFString fieldName = static_cast<LSFString>(args[1].v_string.str);
    QCC_DbgPrintf(("lampID=%s fieldName=%s", lampID.c_str(), fieldName.c_str()));

    lampClients.GetLampParametersField(lampID, fieldName, message);
}

void LampManager::GetLampState(ajn::Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 1)  != LSF_OK) {
        return;
    }

    LSFString lampID = static_cast<LSFString>(args[0].v_string.str);
    QCC_DbgPrintf(("lampID=%s", lampID.c_str()));

    lampClients.GetLampState(lampID, message);
}

void LampManager::GetLampStateField(ajn::Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 2)  != LSF_OK) {
        return;
    }

    LSFString lampID = static_cast<LSFString>(args[0].v_string.str);
    LSFString fieldName = static_cast<LSFString>(args[1].v_string.str);
    QCC_DbgPrintf(("lampID=%s fieldName=%s", lampID.c_str(), fieldName.c_str()));

    lampClients.GetLampStateField(lampID, fieldName, message);
}

void LampManager::TransitionLampStateToPreset(Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 3)  != LSF_OK) {
        return;
    }

    LSFString lampID = static_cast<LSFString>(args[0].v_string.str);
    LSFString presetID = static_cast<LSFString>(args[1].v_string.str);
    uint32_t transitionPeriod = static_cast<uint32_t>(args[2].v_uint32);
    QCC_DbgPrintf(("lampID=%s presetID=%s transitionPeriod=%d", lampID.c_str(), presetID.c_str(), transitionPeriod));

    if (0 == strcmp(presetID.c_str(), CurrentStateIdentifier.c_str())) {
        QCC_LogError(ER_FAIL, ("%s: Preset cannot be the current state", __func__));
        LSFResponseCode responseCode = LSF_ERR_INVALID_ARGS;
        controllerService.SendMethodReplyWithResponseCodeAndID(message, responseCode, lampID);
    } else {
        LSFStringList lampList;
        lampList.push_back(lampID);

        LampsAndStateList transitionToState;
        LampsAndPresetList transitionToPreset;
        LampsAndStateFieldList stateField;
        PulseLampsWithStateList pulseWithState;
        PulseLampsWithPresetList pulseWithPreset;

        LampsAndPreset transitionToPresetComponent(lampList, presetID, transitionPeriod);
        transitionToPreset.push_back(transitionToPresetComponent);

        ChangeLampStateAndField(message, transitionToState, transitionToPreset, stateField, pulseWithState, pulseWithPreset);
    }
}

void LampManager::TransitionLampStateField(ajn::Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 4)  != LSF_OK) {
        return;
    }

    LSFString lampID = static_cast<LSFString>(args[0].v_string.str);
    LSFString fieldName = static_cast<LSFString>(args[1].v_string.str);
    MsgArg* varArg;
    args[2].Get("v", &varArg);
    uint32_t transitionPeriod = static_cast<uint32_t>(args[3].v_uint32);
    QCC_DbgPrintf(("lampID=%s fieldName=%s transitionPeriod=%d", lampID.c_str(), fieldName.c_str(), transitionPeriod));

    LSFStringList lampList;
    lampList.push_back(lampID);

    LampsAndStateList transitionToState;
    LampsAndPresetList transitionToPreset;
    LampsAndStateFieldList stateField;
    PulseLampsWithStateList pulseWithState;
    PulseLampsWithPresetList pulseWithPreset;

    LampsAndStateField stateFieldComponent(lampList, fieldName, *varArg, transitionPeriod);
    stateField.push_back(stateFieldComponent);

    ChangeLampStateAndField(message, transitionToState, transitionToPreset, stateField, pulseWithState, pulseWithPreset);
}

void LampManager::ResetLampState(ajn::Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 1)  != LSF_OK) {
        return;
    }

    LSFString lampID = static_cast<LSFString>(args[0].v_string.str);
    QCC_DbgPrintf(("lampID=%s", lampID.c_str()));

    LSFStringList lampList;
    lampList.push_back(lampID);

    ResetLampStateInternal(message, lampList);
}

void LampManager::ResetLampStateField(ajn::Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 2)  != LSF_OK) {
        return;
    }

    LSFString lampID = static_cast<LSFString>(args[0].v_string.str);
    LSFString fieldName = static_cast<LSFString>(args[1].v_string.str);
    QCC_DbgPrintf(("%s: lampID=%s fieldName=%s", __func__, lampID.c_str(), fieldName.c_str()));

    LSFStringList lampList;
    lampList.push_back(lampID);

    ResetLampStateFieldInternal(message, lampList, fieldName);
}

void LampManager::GetLampDataSet(ajn::Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 2)  != LSF_OK) {
        return;
    }

    LSFString lampID = static_cast<LSFString>(args[0].v_string.str);
    LSFString language = static_cast<LSFString>(args[1].v_string.str);

    QCC_DbgPrintf(("lampID=%s language=%s", lampID.c_str(), language.c_str()));

    lampClients.GetLampDataSet(lampID, language, message);
}

void LampManager::ResetLampStateInternal(ajn::Message& message, LSFStringList lamps, bool groupOperation, bool allLamps)
{
    LampState defaultLampState;

    QCC_DbgPrintf(("%s: allLamps=%u", __func__, allLamps));

    LSFResponseCode responseCode = presetManager.GetDefaultLampStateInternal(defaultLampState);

    LampsAndStateList transitionToState;
    LampsAndPresetList transitionToPreset;
    LampsAndStateFieldList stateField;
    PulseLampsWithStateList pulseWithState;
    PulseLampsWithPresetList pulseWithPreset;

    if (LSF_OK == responseCode) {
        LampsAndState transitionToStateComponent(lamps, defaultLampState, 0);
        transitionToState.push_back(transitionToStateComponent);
        ChangeLampStateAndField(message, transitionToState, transitionToPreset, stateField, pulseWithState, pulseWithPreset, groupOperation, allLamps);
    } else {
        QCC_LogError(ER_FAIL, ("%s: Error getting the default lamp state", __func__));
        if (groupOperation) {
            size_t numArgs;
            const MsgArg* args;
            message->GetArgs(numArgs, args);

            if (controllerService.CheckNumArgsInMessage(numArgs, 1)  != LSF_OK) {
                return;
            }

            LSFString lampGroupId = static_cast<LSFString>(args[0].v_string.str);
            controllerService.SendMethodReplyWithResponseCodeAndID(message, responseCode, lampGroupId);
        } else {
            controllerService.SendMethodReplyWithResponseCodeAndID(message, responseCode, lamps.front());
        }
    }
}

void LampManager::ResetLampStateFieldInternal(ajn::Message& message, LSFStringList lamps, LSFString stateFieldName, bool groupOperation, bool allLamps)
{
    LampState defaultLampState;

    QCC_DbgPrintf(("%s: allLamps=%u", __func__, allLamps));

    LSFResponseCode responseCode = presetManager.GetDefaultLampStateInternal(defaultLampState);
    MsgArg arg;

    LampsAndStateList transitionToState;
    LampsAndPresetList transitionToPreset;
    LampsAndStateFieldList stateField;
    PulseLampsWithStateList pulseWithState;
    PulseLampsWithPresetList pulseWithPreset;

    if (LSF_OK == responseCode) {
        //QCC_DbgPrintf(("%s: defaultLampState=%s", __func__, defaultLampState.c_str()));
        if (0 == strcmp(stateFieldName.c_str(), "OnOff")) {
            arg.Set("b", defaultLampState.onOff);
        } else if (0 == strcmp(stateFieldName.c_str(), "Hue")) {
            arg.Set("u", defaultLampState.hue);
        } else if (0 == strcmp(stateFieldName.c_str(), "Saturation")) {
            arg.Set("u", defaultLampState.saturation);
        } else if (0 == strcmp(stateFieldName.c_str(), "Brightness")) {
            arg.Set("u", defaultLampState.brightness);
        } else if (0 == strcmp(stateFieldName.c_str(), "ColorTemp")) {
            arg.Set("u", defaultLampState.colorTemp);
        }

        LampsAndStateField stateFieldComponent(lamps, stateFieldName, arg, 0);
        stateField.push_back(stateFieldComponent);
        ChangeLampStateAndField(message, transitionToState, transitionToPreset, stateField, pulseWithState, pulseWithPreset, groupOperation, allLamps);
    } else {
        QCC_LogError(ER_FAIL, ("%s: Error getting the default lamp state", __func__));
        controllerService.SendMethodReplyWithResponseCodeIDAndName(message, responseCode, lamps.front(), stateFieldName);
        if (groupOperation) {
            size_t numArgs;
            const MsgArg* args;
            message->GetArgs(numArgs, args);

            if (controllerService.CheckNumArgsInMessage(numArgs, 1)  != LSF_OK) {
                return;
            }

            LSFString lampGroupId = static_cast<LSFString>(args[0].v_string.str);
            controllerService.SendMethodReplyWithResponseCodeIDAndName(message, responseCode, lampGroupId, stateFieldName);
        } else {
            controllerService.SendMethodReplyWithResponseCodeIDAndName(message, responseCode, lamps.front(), stateFieldName);
        }
    }
}

void LampManager::ChangeLampStateAndField(Message& message,
                                          LampsAndStateList& transitionToStateComponent,
                                          LampsAndPresetList& transitionToPresetComponent,
                                          LampsAndStateFieldList& stateFieldComponent,
                                          PulseLampsWithStateList& pulseWithStateComponent,
                                          PulseLampsWithPresetList& pulseWithPresetComponent,
                                          bool groupOperation,
                                          bool allLamps,
                                          bool sceneOperation,
                                          LSFString sceneOrMasterSceneId,
                                          bool effectOperation)
{
    LSFResponseCode responseCode = LSF_ERR_FAILURE;

    QCC_DbgPrintf(("%s: allLamps=%u", __func__, allLamps));

    uint64_t timestamp = 0;
    OEM_CS_GetSyncTimeStamp(timestamp);

    TransitionStateParamsList stateParamsList;
    TransitionStateFieldParamsList stateFieldParamsList;
    PulseStateParamsList pulseParamsList;

    stateParamsList.clear();
    stateFieldParamsList.clear();
    pulseParamsList.clear();

    while (transitionToStateComponent.size()) {
        LampsAndState transitionToStateComp = transitionToStateComponent.front();
        MsgArg state;
        transitionToStateComp.state.Get(&state, true);
        QCC_DbgPrintf(("%s: Applying transitionToStateComponent", __func__));
        TransitionStateParams params(transitionToStateComp.lamps, timestamp, state, transitionToStateComp.transitionPeriod);
        stateParamsList.push_back(params);
        transitionToStateComponent.pop_front();
    }

    while (transitionToPresetComponent.size()) {
        LampsAndPreset transitionToPresetComp = transitionToPresetComponent.front();
        LampState preset;
        responseCode = presetManager.GetPresetInternal(transitionToPresetComp.presetID, preset);
        if (LSF_OK == responseCode) {
            MsgArg state;
            preset.Get(&state, true);
            QCC_DbgPrintf(("%s: Applying transitionToPresetComponent", __func__));
            TransitionStateParams params(transitionToPresetComp.lamps, timestamp, state, transitionToPresetComp.transitionPeriod);
            stateParamsList.push_back(params);
        } else {
            if (groupOperation || effectOperation || (sceneOperation && ((0 == strcmp(ControllerServiceSceneInterfaceName, message->GetInterface())) || (0 == strcmp(ControllerServiceMasterSceneInterfaceName, message->GetInterface())) || (0 == strcmp(ControllerServiceSceneElementInterfaceName, message->GetInterface()))))) {
                size_t numArgs;
                const MsgArg* args;
                message->GetArgs(numArgs, args);

                if (effectOperation) {
                    if (controllerService.CheckNumArgsInMessage(numArgs, 2)  != LSF_OK) {
                        return;
                    }
                    MsgArg arg[3];
                    arg[0].Set("u", responseCode);
                    arg[1] = args[0];
                    arg[2] = args[1];
                    controllerService.SendMethodReply(message, arg, 3);
                } else {
                    if (controllerService.CheckNumArgsInMessage(numArgs, 1)  != LSF_OK) {
                        return;
                    }

                    LSFString uniqueID = static_cast<LSFString>(args[0].v_string.str);
                    controllerService.SendMethodReplyWithResponseCodeAndID(message, responseCode, uniqueID);
                }
            } else {
                controllerService.SendMethodReplyWithResponseCodeAndID(message, responseCode, transitionToPresetComp.lamps.front());
            }
            return;
        }
        transitionToPresetComponent.pop_front();
    }

    while (stateFieldComponent.size()) {
        LampsAndStateField stateFieldComp = stateFieldComponent.front();
        QCC_DbgPrintf(("%s: Applying stateFieldComponent", __func__));
        TransitionStateFieldParams params(stateFieldComp.lamps, timestamp, stateFieldComp.stateFieldName.c_str(),
                                          stateFieldComp.stateFieldValue, stateFieldComp.transitionPeriod);
        stateFieldParamsList.push_back(params);
        stateFieldComponent.pop_front();
    }

    while (pulseWithStateComponent.size()) {
        QCC_DbgPrintf(("%s: Applying pulseWithStateComponent", __func__));
        PulseLampsWithState pulseWithStateComp = pulseWithStateComponent.front();
        MsgArg fromState;
        MsgArg toState;
        pulseWithStateComp.fromState.Get(&fromState, true);
        pulseWithStateComp.toState.Get(&toState, true);
        PulseStateParams params(pulseWithStateComp.lamps, fromState, toState, pulseWithStateComp.period, pulseWithStateComp.duration,
                                pulseWithStateComp.numPulses, timestamp);
        pulseParamsList.push_back(params);
        pulseWithStateComponent.pop_front();
    }

    while (pulseWithPresetComponent.size()) {
        PulseLampsWithPreset pulseWithPresetComp = pulseWithPresetComponent.front();
        LampState fromPreset;
        LampState toPreset;
        responseCode = presetManager.GetPresetInternal(pulseWithPresetComp.fromPreset, fromPreset);
        if (LSF_OK == responseCode) {
            responseCode = presetManager.GetPresetInternal(pulseWithPresetComp.toPreset, toPreset);
            if (LSF_OK == responseCode) {
                MsgArg fromState;
                MsgArg toState;
                fromPreset.Get(&fromState, true);
                toPreset.Get(&toState, true);
                QCC_DbgPrintf(("%s: Applying pulseWithPresetComponent", __func__));
                PulseStateParams params(pulseWithPresetComp.lamps, fromState, toState, pulseWithPresetComp.period, pulseWithPresetComp.duration,
                                        pulseWithPresetComp.numPulses, timestamp);
                pulseParamsList.push_back(params);
            }
        } else {
            if (groupOperation || effectOperation || (sceneOperation && ((0 == strcmp(ControllerServiceSceneInterfaceName, message->GetInterface())) || (0 == strcmp(ControllerServiceMasterSceneInterfaceName, message->GetInterface())) || (0 == strcmp(ControllerServiceSceneElementInterfaceName, message->GetInterface()))))) {
                size_t numArgs;
                const MsgArg* args;
                message->GetArgs(numArgs, args);

                if (effectOperation) {
                    if (controllerService.CheckNumArgsInMessage(numArgs, 2)  != LSF_OK) {
                        return;
                    }
                    MsgArg arg[3];
                    arg[0].Set("u", responseCode);
                    arg[1] = args[0];
                    arg[2] = args[1];
                    controllerService.SendMethodReply(message, arg, 3);
                } else {
                    if (controllerService.CheckNumArgsInMessage(numArgs, 1)  != LSF_OK) {
                        return;
                    }

                    LSFString uniqueID = static_cast<LSFString>(args[0].v_string.str);
                    controllerService.SendMethodReplyWithResponseCodeAndID(message, responseCode, uniqueID);
                }
            } else {
                controllerService.SendMethodReplyWithResponseCodeAndID(message, responseCode, pulseWithPresetComp.lamps.front());
            }
            return;
        }
        pulseWithPresetComponent.pop_front();
    }

    lampClients.ChangeLampState(message, groupOperation, sceneOperation, effectOperation, stateParamsList, stateFieldParamsList, pulseParamsList, sceneOrMasterSceneId, allLamps);
}

void LampManager::TransitionLampState(ajn::Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 3)  != LSF_OK) {
        return;
    }

    LSFString lampID = static_cast<LSFString>(args[0].v_string.str);
    LampState state(args[1]);
    uint32_t transitionPeriod = static_cast<uint32_t>(args[2].v_uint32);
    //QCC_DbgPrintf(("lampID=%s state=%s transitionPeriod=%d", lampID.c_str(), state.c_str(), transitionPeriod));

    if (state.nullState) {
        QCC_LogError(ER_FAIL, ("%s: State cannot be NULL", __func__));
        LSFResponseCode responseCode = LSF_ERR_INVALID_ARGS;
        controllerService.SendMethodReplyWithResponseCodeAndID(message, responseCode, lampID);
    } else {
        LSFStringList lampList;
        lampList.push_back(lampID);

        LampsAndStateList transitionToState;
        LampsAndPresetList transitionToPreset;
        LampsAndStateFieldList stateField;
        PulseLampsWithStateList pulseWithState;
        PulseLampsWithPresetList pulseWithPreset;

        LampsAndState transitionToStateComponent(lampList, state, transitionPeriod);
        transitionToState.push_back(transitionToStateComponent);

        ChangeLampStateAndField(message, transitionToState, transitionToPreset, stateField, pulseWithState, pulseWithPreset);
    }
}

void LampManager::PulseLampWithState(ajn::Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 6)  != LSF_OK) {
        return;
    }

    LSFString lampID = static_cast<LSFString>(args[0].v_string.str);
    LampState fromLampState(args[1]);
    LampState toLampState(args[2]);
    uint32_t period = static_cast<uint32_t>(args[3].v_uint32);
    uint32_t duration = static_cast<uint32_t>(args[4].v_uint32);
    uint32_t numPulses = static_cast<uint32_t>(args[5].v_uint32);
    //QCC_DbgPrintf(("%s: lampID=%s, fromLampState=%s, period=%d, duration=%d, numPulses=%d",
    //__func__, lampID.c_str(), fromLampState.c_str(), period, duration, numPulses));
    //QCC_DbgPrintf(("%s: toLampState=%s", __func__, toLampState.c_str()));

    if (toLampState.nullState) {
        QCC_LogError(ER_FAIL, ("%s: ToLampState cannot be NULL", __func__));
        LSFResponseCode responseCode = LSF_ERR_INVALID_ARGS;
        controllerService.SendMethodReplyWithResponseCodeAndID(message, responseCode, lampID);
    } else {
        LSFStringList lampList;
        lampList.push_back(lampID);

        LampsAndStateList transitionToState;
        LampsAndPresetList transitionToPreset;
        LampsAndStateFieldList stateField;
        PulseLampsWithStateList pulseWithState;
        PulseLampsWithPresetList pulseWithPreset;

        PulseLampsWithState pulseWithStateComponent(lampList, fromLampState, toLampState, period, duration, numPulses);
        pulseWithState.push_back(pulseWithStateComponent);
        ChangeLampStateAndField(message, transitionToState, transitionToPreset, stateField, pulseWithState, pulseWithPreset);
    }
}

void LampManager::PulseLampWithPreset(ajn::Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 6)  != LSF_OK) {
        return;
    }

    LSFString lampID = static_cast<LSFString>(args[0].v_string.str);
    LSFString fromPresetID = static_cast<LSFString>(args[1].v_string.str);
    LSFString toPresetID = static_cast<LSFString>(args[2].v_string.str);
    uint32_t period = static_cast<uint32_t>(args[3].v_uint32);
    uint32_t duration = static_cast<uint32_t>(args[4].v_uint32);
    uint32_t numPulses = static_cast<uint32_t>(args[5].v_uint32);
    QCC_DbgPrintf(("%s: lampID=%s, fromPresetID=%s, toPresetID=%s, period=%d, duration=%d, numPulses=%d",
                   __func__, lampID.c_str(), fromPresetID.c_str(), toPresetID.c_str(), period, duration, numPulses));

    if (0 == strcmp(toPresetID.c_str(), CurrentStateIdentifier.c_str())) {
        QCC_LogError(ER_FAIL, ("%s: ToPreset cannot be the current state", __func__));
        LSFResponseCode responseCode = LSF_ERR_INVALID_ARGS;
        controllerService.SendMethodReplyWithResponseCodeAndID(message, responseCode, lampID);
    } else {
        LSFStringList lampList;
        lampList.push_back(lampID);

        LampsAndStateList transitionToState;
        LampsAndPresetList transitionToPreset;
        LampsAndStateFieldList stateField;
        PulseLampsWithStateList pulseWithState;
        PulseLampsWithPresetList pulseWithPreset;

        PulseLampsWithPreset pulseWithPresetComponent(lampList, fromPresetID, toPresetID, period, duration, numPulses);
        pulseWithPreset.push_back(pulseWithPresetComponent);
        ChangeLampStateAndField(message, transitionToState, transitionToPreset, stateField, pulseWithState, pulseWithPreset);
    }
}

uint32_t LampManager::GetControllerServiceLampInterfaceVersion(void)
{
    QCC_DbgPrintf(("%s: controllerLampInterfaceVersion=%d", __func__, ControllerServiceLampInterfaceVersion));
    return ControllerServiceLampInterfaceVersion;
}

uint32_t LampManager::GetControllerServiceDataSetInterfaceVersion(void)
{
    QCC_DbgPrintf(("%s: controllerDataSetInterfaceVersion=%d", __func__, ControllerServiceDataSetInterfaceVersion));
    return ControllerServiceDataSetInterfaceVersion;
}
