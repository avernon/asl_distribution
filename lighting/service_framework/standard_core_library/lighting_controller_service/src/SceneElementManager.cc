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
#include <lsf/controllerservice/ControllerService.h>
#include <lsf/controllerservice/SceneElementManager.h>
#include <lsf/controllerservice/LampGroupManager.h>
#include <lsf/controllerservice/TransitionEffectManager.h>
#include <lsf/controllerservice/PulseEffectManager.h>
#include <lsf/controllerservice/OEM_CS_Config.h>
#include <lsf/controllerservice/FileParser.h>
#else
#include <ControllerService.h>
#include <SceneElementManager.h>
#include <LampGroupManager.h>
#include <TransitionEffectManager.h>
#include <PulseEffectManager.h>
#include <OEM_CS_Config.h>
#include <FileParser.h>
#endif

#include <qcc/atomic.h>
#include <qcc/Debug.h>

using namespace lsf;
using namespace ajn;

#ifdef LSF_BINDINGS
using namespace controllerservice;
#define QCC_MODULE "CONTROLLER_SCENE_ELEMENT_MANAGER"
#else
#define QCC_MODULE "SCENE_ELEMENT_MANAGER"
#endif

SceneElementManager::SceneElementManager(ControllerService& controllerSvc, LampGroupManager* lampGroupManager, TransitionEffectManager* transistionEffectMgr, PulseEffectManager* pulseEffectMgr, SceneManager* sceneMgr, const std::string& sceneElementFile) :
    Manager(controllerSvc, sceneElementFile), lampGroupManagerPtr(lampGroupManager), transitionEffectManagerPtr(transistionEffectMgr), pulseEffectManagerPtr(pulseEffectMgr), sceneManagerPtr(sceneMgr)
{
    QCC_DbgPrintf(("%s", __func__));
    sceneElements.clear();
}

LSFResponseCode SceneElementManager::Reset(void)
{
    QCC_DbgPrintf(("%s", __func__));
    LSFResponseCode responseCode = LSF_OK;

    if (!controllerService.UpdatesAllowed()) {
        return LSF_ERR_BUSY;
    }

    QStatus tempStatus = sceneElementsLock.Lock();
    if (ER_OK == tempStatus) {
        /*
         * Record the IDs of all the SceneElements that are being deleted
         */
        LSFStringList sceneElementsList;
        for (SceneElementMap::iterator it = sceneElements.begin(); it != sceneElements.end(); ++it) {
            sceneElementsList.push_back(it->first);
        }

        /*
         * Clear the SceneElements
         */
        sceneElements.clear();
        blobLength = 0;

        ScheduleFileWrite();

        tempStatus = sceneElementsLock.Unlock();
        if (ER_OK != tempStatus) {
            QCC_LogError(tempStatus, ("%s: sceneElementsLock.Unlock() failed", __func__));
        }

        /*
         * Send the SceneElements deleted signal
         */
        if (sceneElementsList.size()) {
            tempStatus = controllerService.SendSignal(ControllerServiceSceneElementInterfaceName, "SceneElementsDeleted", sceneElementsList);
            if (ER_OK != tempStatus) {
                QCC_LogError(tempStatus, ("%s: Unable to send SceneElementsDeleted signal", __func__));
            }
        }
    } else {
        responseCode = LSF_ERR_BUSY;
        QCC_LogError(tempStatus, ("%s: sceneElementsLock.Lock() failed", __func__));
    }

    return responseCode;
}

LSFResponseCode SceneElementManager::IsDependentOnLampGroup(LSFString& lampGroupID)
{
    QCC_DbgTrace(("%s", __func__));
    LSFResponseCode responseCode = LSF_OK;

    QStatus status = sceneElementsLock.Lock();
    if (ER_OK == status) {
        for (SceneElementMap::iterator it = sceneElements.begin(); it != sceneElements.end(); ++it) {
            responseCode = it->second.second.IsDependentOnLampGroup(lampGroupID);
            if (LSF_OK != responseCode) {
                break;
            }
        }
        status = sceneElementsLock.Unlock();
        if (ER_OK != status) {
            QCC_LogError(status, ("%s: sceneElementsLock.Unlock() failed", __func__));
        }
    } else {
        responseCode = LSF_ERR_BUSY;
        QCC_LogError(status, ("%s: sceneElementsLock.Lock() failed", __func__));
    }

    return responseCode;
}

LSFResponseCode SceneElementManager::IsDependentOnEffect(LSFString& effectId)
{
    QCC_DbgTrace(("%s", __func__));
    LSFResponseCode responseCode = LSF_OK;

    QStatus status = sceneElementsLock.Lock();
    if (ER_OK == status) {
        for (SceneElementMap::iterator it = sceneElements.begin(); it != sceneElements.end(); ++it) {
            responseCode = it->second.second.IsDependentOnEffect(effectId);
            if (LSF_OK != responseCode) {
                break;
            }
        }
        status = sceneElementsLock.Unlock();
        if (ER_OK != status) {
            QCC_LogError(status, ("%s: sceneElementsLock.Unlock() failed", __func__));
        }
    } else {
        responseCode = LSF_ERR_BUSY;
        QCC_LogError(status, ("%s: sceneElementsLock.Lock() failed", __func__));
    }

    return responseCode;
}

LSFResponseCode SceneElementManager::GetAllSceneElements(SceneElementMap& sceneElementMap)
{
    QCC_DbgTrace(("%s", __func__));
    LSFResponseCode responseCode = LSF_OK;

    QStatus status = sceneElementsLock.Lock();
    if (ER_OK == status) {
        sceneElementMap = sceneElements;
        status = sceneElementsLock.Unlock();
        if (ER_OK != status) {
            QCC_LogError(status, ("%s: sceneElementsLock.Unlock() failed", __func__));
        }
    } else {
        responseCode = LSF_ERR_BUSY;
        QCC_LogError(status, ("%s: sceneElementsLock.Lock() failed", __func__));
    }

    return responseCode;
}

void SceneElementManager::GetAllSceneElementIDs(Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));

    LSFStringList idList;
    LSFResponseCode responseCode = LSF_OK;

    QStatus status = sceneElementsLock.Lock();
    if (ER_OK == status) {
        for (SceneElementMap::iterator it = sceneElements.begin(); it != sceneElements.end(); ++it) {
            idList.push_back(it->first.c_str());
        }
        status = sceneElementsLock.Unlock();
        if (ER_OK != status) {
            QCC_LogError(status, ("%s: sceneElementsLock.Unlock() failed", __func__));
        }
    } else {
        responseCode = LSF_ERR_BUSY;
        QCC_LogError(status, ("%s: sceneElementsLock.Lock() failed", __func__));
    }

    controllerService.SendMethodReplyWithResponseCodeAndListOfIDs(message, responseCode, idList);
}

void SceneElementManager::GetSceneElementName(Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    LSFString name;
    LSFResponseCode responseCode = LSF_ERR_NOT_FOUND;

    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 2)  != LSF_OK) {
        return;
    }

    const char* uniqueId;
    args[0].Get("s", &uniqueId);

    LSFString sceneElementID(uniqueId);

    LSFString language = static_cast<LSFString>(args[1].v_string.str);
    if (0 != strcmp("en", language.c_str())) {
        QCC_LogError(ER_FAIL, ("%s: Language %s not supported", __func__, language.c_str()));
        responseCode = LSF_ERR_INVALID_ARGS;
    } else {
        QStatus status = sceneElementsLock.Lock();
        if (ER_OK == status) {
            SceneElementMap::iterator it = sceneElements.find(uniqueId);
            if (it != sceneElements.end()) {
                name = it->second.first;
                responseCode = LSF_OK;
            }
            status = sceneElementsLock.Unlock();
            if (ER_OK != status) {
                QCC_LogError(status, ("%s: sceneElementsLock.Unlock() failed", __func__));
            }
        } else {
            responseCode = LSF_ERR_BUSY;
            QCC_LogError(status, ("%s: sceneElementsLock.Lock() failed", __func__));
        }
    }

    controllerService.SendMethodReplyWithResponseCodeIDLanguageAndName(message, responseCode, sceneElementID, language, name);
}

void SceneElementManager::SetSceneElementName(Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    LSFResponseCode responseCode = LSF_ERR_NOT_FOUND;

    bool nameChanged = false;
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 3)  != LSF_OK) {
        return;
    }

    const char* uniqueId;
    args[0].Get("s", &uniqueId);

    LSFString sceneElementID(uniqueId);

    const char* name;
    args[1].Get("s", &name);

    LSFString language = static_cast<LSFString>(args[2].v_string.str);

    if (!controllerService.UpdatesAllowed()) {
        controllerService.SendMethodReplyWithResponseCodeIDAndName(message, LSF_ERR_BUSY, sceneElementID, language);
        return;
    }

    if (0 != strcmp("en", language.c_str())) {
        QCC_LogError(ER_FAIL, ("%s: Language %s not supported", __func__, language.c_str()));
        responseCode = LSF_ERR_INVALID_ARGS;
    } else if (name[0] == '\0') {
        QCC_LogError(ER_FAIL, ("%s: scene element name is empty", __func__));
        responseCode = LSF_ERR_EMPTY_NAME;
    } else {
        if (strlen(name) > LSF_MAX_NAME_LENGTH) {
            responseCode = LSF_ERR_INVALID_ARGS;
            QCC_LogError(ER_FAIL, ("%s: strlen(name) > LSF_MAX_NAME_LENGTH", __func__));
        } else {
            QStatus status = sceneElementsLock.Lock();
            if (ER_OK == status) {
                SceneElementMap::iterator it = sceneElements.find(uniqueId);
                if (it != sceneElements.end()) {
                    LSFString newName = name;
                    size_t newlen = blobLength - it->second.first.length() + newName.length();

                    if (newlen < MAX_FILE_LEN) {
                        blobLength = newlen;
                        it->second.first = newName;
                        responseCode = LSF_OK;
                        nameChanged = true;
                        ScheduleFileWrite();
                    } else {
                        QCC_LogError(ER_FAIL, ("%s: blob too big: %d >= %d", __func__, newlen, MAX_FILE_LEN));
                        responseCode = LSF_ERR_RESOURCES;
                    }
                }
                status = sceneElementsLock.Unlock();
                if (ER_OK != status) {
                    QCC_LogError(status, ("%s: sceneElementsLock.Unlock() failed", __func__));
                }
            } else {
                responseCode = LSF_ERR_BUSY;
                QCC_LogError(status, ("%s: sceneElementsLock.Lock() failed", __func__));
            }
        }
    }

    controllerService.SendMethodReplyWithResponseCodeIDAndName(message, responseCode, sceneElementID, language);

    if (nameChanged) {
        LSFStringList idList;
        idList.push_back(sceneElementID);
        controllerService.SendSignal(ControllerServiceSceneElementInterfaceName, "SceneElementsNameChanged", idList);
    }
}

void SceneElementManager::CreateSceneElement(Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));

    LSFResponseCode responseCode = LSF_OK;
    LSFString sceneElementID;

    if (!controllerService.UpdatesAllowed()) {
        controllerService.SendMethodReplyWithResponseCodeAndID(message, LSF_ERR_BUSY, sceneElementID);
        return;
    }

    const ajn::MsgArg* inputArgs;
    size_t numInputArgs;
    message->GetArgs(numInputArgs, inputArgs);

    if (controllerService.CheckNumArgsInMessage(numInputArgs, 5)  != LSF_OK) {
        return;
    }

    SceneElement sceneElement(inputArgs[0], inputArgs[1], inputArgs[2]);
    LSFString name = static_cast<LSFString>(inputArgs[3].v_string.str);
    LSFString language = static_cast<LSFString>(inputArgs[4].v_string.str);

    responseCode = CreateSceneElementInternal(sceneElement, name, language, sceneElementID);

    controllerService.SendMethodReplyWithResponseCodeAndID(message, responseCode, sceneElementID);

    if (responseCode == LSF_OK) {
        LSFStringList idList;
        idList.push_back(sceneElementID);
        SendSceneElementsCreatedSignal(idList);
    }
}

void SceneElementManager::UpdateSceneElement(Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    LSFResponseCode responseCode = LSF_ERR_NOT_FOUND;

    bool updated = false;

    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 4)  != LSF_OK) {
        return;
    }

    const char* sceneElementId;
    args[0].Get("s", &sceneElementId);

    LSFString sceneElementID(sceneElementId);
    SceneElement sceneElement(args[1], args[2], args[3]);

    if (!controllerService.UpdatesAllowed()) {
        controllerService.SendMethodReplyWithResponseCodeAndID(message, LSF_ERR_BUSY, sceneElementID);
        return;
    }

    if (sceneElement.lamps.empty() && sceneElement.lampGroups.empty()) {
        QCC_LogError(ER_FAIL, ("%s: Empty Lamps and LampGroups list", __func__));
        responseCode = LSF_ERR_INVALID_ARGS;
    } else {
        QStatus status = sceneElementsLock.Lock();
        if (ER_OK == status) {
            SceneElementMap::iterator it = sceneElements.find(sceneElementId);
            if (it != sceneElements.end()) {

                size_t newlen = blobLength;
                // sub len of old element, add len of new element
                newlen -= GetString(it->second.first, sceneElementID, it->second.second).length();
                newlen += GetString(it->second.first, sceneElementID, sceneElement).length();

                if (newlen < MAX_FILE_LEN) {
                    blobLength = newlen;
                    it->second.second = sceneElement;
                    responseCode = LSF_OK;
                    updated = true;
                    ScheduleFileWrite();
                } else {
                    QCC_LogError(ER_FAIL, ("%s: blob too big: %d >= %d", __func__, newlen, MAX_FILE_LEN));
                    responseCode = LSF_ERR_RESOURCES;
                }
            }
            status = sceneElementsLock.Unlock();
            if (ER_OK != status) {
                QCC_LogError(status, ("%s: sceneElementsLock.Unlock() failed", __func__));
            }
        } else {
            responseCode = LSF_ERR_BUSY;
            QCC_LogError(status, ("%s: sceneElementsLock.Lock() failed", __func__));
        }
    }

    controllerService.SendMethodReplyWithResponseCodeAndID(message, responseCode, sceneElementID);

    if (updated) {
        LSFStringList idList;
        idList.push_back(sceneElementID);
        controllerService.SendSignal(ControllerServiceSceneElementInterfaceName, "SceneElementsUpdated", idList);
        responseCode = sceneManagerPtr->IsDependentOnSceneElement(sceneElementID);
        if (LSF_ERR_DEPENDENCY == responseCode) {
            controllerService.GetSceneManager().RefreshSceneData();
        }
    }
}

void SceneElementManager::DeleteSceneElement(Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    LSFResponseCode responseCode = LSF_OK;

    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 1)  != LSF_OK) {
        return;
    }

    const char* sceneElementId;
    args[0].Get("s", &sceneElementId);

    LSFString sceneElementID(sceneElementId);

    if (!controllerService.UpdatesAllowed()) {
        controllerService.SendMethodReplyWithResponseCodeAndID(message, LSF_ERR_BUSY, sceneElementID);
        return;
    }

    responseCode = DeleteSceneElementInternal(sceneElementID);

    controllerService.SendMethodReplyWithResponseCodeAndID(message, responseCode, sceneElementID);

    if (responseCode == LSF_OK) {
        LSFStringList idList;
        idList.push_back(sceneElementID);
        controllerService.SendSignal(ControllerServiceSceneElementInterfaceName, "SceneElementsDeleted", idList);
    }
}

void SceneElementManager::GetSceneElement(Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));

    LSFResponseCode responseCode = LSF_ERR_NOT_FOUND;

    MsgArg outArgs[5];

    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 1)  != LSF_OK) {
        return;
    }

    const char* sceneElementId;
    args[0].Get("s", &sceneElementId);

    LSFString sceneElementID(sceneElementId);
    SceneElement sceneElement;

    responseCode = GetSceneElementInternal(sceneElementID, sceneElement);
    if (responseCode == LSF_OK) {
        sceneElement.Get(&outArgs[2], &outArgs[3], &outArgs[4]);
    } else {
        outArgs[2].Set("as", 0, NULL);
        outArgs[3].Set("as", 0, NULL);
        outArgs[4].Set("s", 0, NULL);
    }

    outArgs[0].Set("u", responseCode);
    outArgs[1].Set("s", sceneElementId);

    controllerService.SendMethodReply(message, outArgs, 5);
}

void SceneElementManager::ApplySceneElement(ajn::Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    LSFResponseCode responseCode = LSF_ERR_NOT_FOUND;

    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 1) != LSF_OK) {
        return;
    }

    const char* sceneElementId;
    args[0].Get("s", &sceneElementId);

    LSFString uniqueId(sceneElementId);
    LSFStringList sceneElementIDs;
    sceneElementIDs.push_back(uniqueId);

    responseCode = ApplySceneElementInternal(message, sceneElementIDs, uniqueId);

    if (LSF_OK != responseCode) {
        controllerService.SendMethodReplyWithResponseCodeAndID(message, responseCode, uniqueId);
    }
}

LSFResponseCode SceneElementManager::ApplySceneElementInternal(ajn::Message& message, LSFStringList& sceneElementIDs, LSFString sceneOrMasterSceneId)
{
    QCC_DbgPrintf(("%s: sceneElementIDs.size() = %d", __func__, sceneElementIDs.size()));
    LSFResponseCode responseCode = LSF_ERR_NOT_FOUND;
    std::list<SceneElement> sceneElementList;
    uint8_t notfound = 0;

    QStatus status = sceneElementsLock.Lock();
    if (ER_OK == status) {
        for (LSFStringList::iterator it = sceneElementIDs.begin(); it != sceneElementIDs.end(); it++) {
            SceneElementMap::iterator it2 = sceneElements.find(*it);
            if (it2 != sceneElements.end()) {
                QCC_DbgPrintf(("%s: Found sceneElementID=%s", __func__, it->c_str()));
                sceneElementList.push_back(it2->second.second);
                responseCode = LSF_OK;
            } else {
                QCC_DbgPrintf(("%s: Missing sceneElementID=%s", __func__, it->c_str()));
                notfound++;
            }
        }
        status = sceneElementsLock.Unlock();
        if (ER_OK != status) {
            QCC_LogError(status, ("%s: sceneElementsLock.Unlock() failed", __func__));
        }
    } else {
        responseCode = LSF_ERR_BUSY;
        QCC_LogError(status, ("%s: sceneElementsLock.Lock() failed", __func__));
    }

    if (LSF_OK == responseCode) {

        TransitionLampsLampGroupsToStateList transitionToStateComponent;
        TransitionLampsLampGroupsToPresetList transitionToPresetComponent;
        PulseLampsLampGroupsWithStateList pulseWithStateComponent;
        PulseLampsLampGroupsWithPresetList pulseWithPresetComponent;

        uint8_t expectedNumOfCommands = sceneElementList.size();
        uint8_t notFoundCount = 0;

        while (sceneElementList.size()) {
            TransitionEffect transitionEffect;
            PulseEffect pulseEffect;
            LampState preset;

            LSFStringList lamps;
            LSFStringList lampGroups;
            lamps.clear();
            lampGroups.clear();

            CreateUniqueList(lamps, sceneElementList.front().lamps);
            CreateUniqueList(lampGroups, sceneElementList.front().lampGroups);

            QCC_DbgPrintf(("%s: Applying sceneElementID with effectID=%s", __func__, sceneElementList.front().effectID.c_str()));
            if (sceneElementList.front().effectID.find("TRANSITION_EFFECT") != std::string::npos) {
                if (transitionEffectManagerPtr->GetTransitionEffectInternal(sceneElementList.front().effectID, transitionEffect) == LSF_OK) {
                    if (transitionEffect.state.nullState) {
                        TransitionLampsLampGroupsToPreset component(lamps, lampGroups, transitionEffect.presetID, transitionEffect.transitionPeriod);
                        transitionToPresetComponent.push_back(component);
                    } else {
                        TransitionLampsLampGroupsToState component(lamps, lampGroups, transitionEffect.state, transitionEffect.transitionPeriod);
                        transitionToStateComponent.push_back(component);
                    }
                } else {
                    notFoundCount++;
                }
            } else if (sceneElementList.front().effectID.find("PULSE_EFFECT") != std::string::npos) {
                if (pulseEffectManagerPtr->GetPulseEffectInternal(sceneElementList.front().effectID, pulseEffect) == LSF_OK) {
                    if (pulseEffect.toState.nullState) {
                        PulseLampsLampGroupsWithPreset component(lamps, lampGroups, pulseEffect.fromPreset, pulseEffect.toPreset, pulseEffect.pulsePeriod, pulseEffect.pulseDuration, pulseEffect.numPulses);
                        pulseWithPresetComponent.push_back(component);
                    } else {
                        PulseLampsLampGroupsWithState component(lamps, lampGroups, pulseEffect.fromState, pulseEffect.toState, pulseEffect.pulsePeriod, pulseEffect.pulseDuration, pulseEffect.numPulses);
                        pulseWithStateComponent.push_back(component);
                    }
                } else {
                    notFoundCount++;
                }
            } else if (sceneElementList.front().effectID.find("PRESET") != std::string::npos) {
                const LSFString presetID = sceneElementList.front().effectID;
                if (controllerService.GetPresetManager().GetPresetInternal(presetID, preset) == LSF_OK) {
                    TransitionLampsLampGroupsToPreset component(lamps, lampGroups, sceneElementList.front().effectID);
                    transitionToPresetComponent.push_back(component);
                } else {
                    notFoundCount++;
                }
            }

            sceneElementList.pop_front();
        }

        if (notFoundCount == expectedNumOfCommands) {
            responseCode = LSF_ERR_FAILURE;
        } else {
            LSFResponseCode tempResponseCode = lampGroupManagerPtr->ChangeLampGroupStateAndField(message, transitionToStateComponent, transitionToPresetComponent,
                                                                                                 pulseWithStateComponent, pulseWithPresetComponent,
                                                                                                 false, false, (sceneOrMasterSceneId.empty() ? false : true), sceneOrMasterSceneId, (sceneOrMasterSceneId.empty() ? true : false));
            if (LSF_ERR_NOT_FOUND == tempResponseCode) {
                responseCode = LSF_ERR_FAILURE;
            }
        }
    }

    return responseCode;
}

void SceneElementManager::ReadWriteFile()
{
    QCC_DbgPrintf(("%s", __func__));

    if (filePath.empty()) {
        return;
    }

    std::string output;
    uint32_t checksum;
    uint64_t timestamp;
    bool status = false;

    status = GetString(output, checksum, timestamp);

    if (status) {
        WriteFileWithChecksumAndTimestamp(output, checksum, timestamp);
        if (timestamp != 0UL) {
            uint64_t currentTime = GetTimestampInMs();
            controllerService.SendBlobUpdate(LSF_SCENE_ELEMENT, output, checksum, (currentTime - timestamp));
        }
    }

    std::list<ajn::Message> tempMessageList;

    readMutex.Lock();
    if (read) {
        tempMessageList = readBlobMessages;
        readBlobMessages.clear();
        read = false;
    }
    readMutex.Unlock();

    if ((tempMessageList.size() || sendUpdate) && !status) {
        std::istringstream stream;
        status = ValidateFileAndReadInternal(checksum, timestamp, stream);
        if (status) {
            output = stream.str();
        } else {
            QCC_LogError(ER_FAIL, ("%s: Scene element persistent store corrupted", __func__));
        }
    }

    if (status) {
        while (!tempMessageList.empty()) {
            uint64_t currentTime = GetTimestampInMs();
            controllerService.SendGetBlobReply(tempMessageList.front(), LSF_SCENE_ELEMENT, output, checksum, (currentTime - timestamp));
            tempMessageList.pop_front();
        }
    }

    if (sendUpdate) {
        sendUpdate = false;
        uint64_t currentTime = GetTimestampInMs();
        controllerService.GetLeaderElectionObj().SendBlobUpdate(LSF_SCENE_ELEMENT, output, checksum, (currentTime - timestamp));
    }
}

void SceneElementManager::ReadSavedData()
{
    QCC_DbgTrace(("%s", __func__));
    std::istringstream stream;
    if (!ValidateFileAndRead(stream)) {
        /*
         * If there is no file present / CRC check failed on the file create a new
         * file with initialState entry
         */
        sceneElementsLock.Lock();
        ScheduleFileWrite(false, true);
        sceneElementsLock.Unlock();
        return;
    }

    blobLength = stream.str().size();
    ReplaceMap(stream);
}

LSFResponseCode SceneElementManager::CreateSceneElementInternal(SceneElement& sceneElement, LSFString& name, LSFString& language, LSFString& sceneElementID)
{
    QCC_DbgTrace(("%s", __func__));
    LSFResponseCode responseCode = LSF_OK;

    sceneElementID = GenerateUniqueID("SCENE_ELEMENT");
    bool created = false;

    if (0 != strcmp("en", language.c_str())) {
        QCC_LogError(ER_FAIL, ("%s: Language %s not supported", __func__, language.c_str()));
        responseCode = LSF_ERR_INVALID_ARGS;
    } else if (name.empty()) {
        QCC_LogError(ER_FAIL, ("%s: scene element name is empty", __func__));
        responseCode = LSF_ERR_EMPTY_NAME;
    } else if (name.length() > LSF_MAX_NAME_LENGTH) {
        QCC_LogError(ER_FAIL, ("%s: name length exceeds %d", __func__, LSF_MAX_NAME_LENGTH));
        responseCode = LSF_ERR_INVALID_ARGS;
    } else if (sceneElement.lamps.empty() && sceneElement.lampGroups.empty()) {
        QCC_LogError(ER_FAIL, ("%s: Empty Lamps and LampGroups list", __func__));
        responseCode = LSF_ERR_INVALID_ARGS;
    } else if (sceneElement.effectID.empty()) {
        QCC_LogError(ER_FAIL, ("%s: effect ID is empty", __func__));
        responseCode = LSF_ERR_INVALID_ARGS;
    } else {
        QStatus status = sceneElementsLock.Lock();
        if (ER_OK == status) {
            if (sceneElements.size() < OEM_CS_MAX_SUPPORTED_NUM_LSF_ENTITY) {
                std::string newElementStr = GetString(name, sceneElementID, sceneElement);
                size_t newlen = blobLength + newElementStr.length();
                if (newlen < MAX_FILE_LEN) {
                    blobLength = newlen;
                    sceneElements[sceneElementID].first = name;
                    sceneElements[sceneElementID].second = sceneElement;
                    created = true;
                    ScheduleFileWrite();
                } else {
                    QCC_LogError(ER_FAIL, ("%s: blob too big: %d >= %d", __func__, newlen, MAX_FILE_LEN));
                    responseCode = LSF_ERR_RESOURCES;
                }
            } else {
                QCC_LogError(ER_FAIL, ("%s: No slot for new SceneElement", __func__));
                responseCode = LSF_ERR_NO_SLOT;
            }
            status = sceneElementsLock.Unlock();
            if (ER_OK != status) {
                QCC_LogError(status, ("%s: sceneElementLock.Unlock() failed", __func__));
            }
        } else {
            responseCode = LSF_ERR_BUSY;
            QCC_LogError(status, ("%s: sceneElementLock.Lock() failed", __func__));
        }
    }

    if (!created) {
        sceneElementID.clear();
    }

    return responseCode;
}

void SceneElementManager::SendSceneElementsCreatedSignal(LSFStringList& sceneElementIds)
{
    QCC_DbgTrace(("%s", __func__));
    controllerService.SendSignal(ControllerServiceSceneElementInterfaceName, "SceneElementsCreated", sceneElementIds);
}

LSFResponseCode SceneElementManager::DeleteSceneElementInternal(LSFString& sceneElementID)
{
    QCC_DbgTrace(("%s", __func__));
    LSFResponseCode responseCode = LSF_OK;

    responseCode = sceneManagerPtr->IsDependentOnSceneElement(sceneElementID);

    if (LSF_OK == responseCode) {
        QStatus status = sceneElementsLock.Lock();
        if (ER_OK == status) {
            SceneElementMap::iterator it = sceneElements.find(sceneElementID);
            if (it != sceneElements.end()) {
                blobLength -= GetString(it->second.first, sceneElementID, it->second.second).length();

                sceneElements.erase(it);
                ScheduleFileWrite();
            } else {
                responseCode = LSF_ERR_NOT_FOUND;
            }
            status = sceneElementsLock.Unlock();
            if (ER_OK != status) {
                QCC_LogError(status, ("%s: sceneElementsLock.Unlock() failed", __func__));
            }
        } else {
            responseCode = LSF_ERR_BUSY;
            QCC_LogError(status, ("%s: sceneElementsLock.Lock() failed", __func__));
        }
    }

    return responseCode;
}

LSFResponseCode SceneElementManager::GetSceneElementInternal(LSFString& sceneElementID, SceneElement& sceneElement)
{
    QCC_DbgTrace(("%s", __func__));
    LSFResponseCode responseCode = LSF_ERR_NOT_FOUND;

    QStatus status = sceneElementsLock.Lock();
    if (ER_OK == status) {
        SceneElementMap::iterator it = sceneElements.find(sceneElementID);
        if (it != sceneElements.end()) {
            sceneElement = it->second.second;
            responseCode = LSF_OK;
        }
        status = sceneElementsLock.Unlock();
        if (ER_OK != status) {
            QCC_LogError(status, ("%s: sceneElementsLock.Unlock() failed", __func__));
        }
    } else {
        responseCode = LSF_ERR_BUSY;
        QCC_LogError(status, ("%s: sceneElementsLock.Lock() failed", __func__));
    }

    return responseCode;
}

void SceneElementManager::ReplaceMap(std::istringstream& stream)
{
    QCC_DbgTrace(("%s", __func__));
    bool firstIteration = true;
    while (!stream.eof()) {
        std::string token = ParseString(stream);

        if (token == resetID) {
            QCC_DbgPrintf(("The file has a reset entry. Clearing the map"));
            sceneElements.clear();
        } else if (token == "SceneElement") {
            std::string id = ParseString(stream);
            std::string name = ParseString(stream);

            if (0 == strcmp(id.c_str(), resetID.c_str())) {
                QCC_DbgPrintf(("The file has a reset entry. Clearing the map"));
                sceneElements.clear();
            } else if (0 == strcmp(id.c_str(), initialStateID.c_str())) {
                QCC_DbgPrintf(("The file has a initialState entry. So we ignore it"));
            } else {
                if (firstIteration) {
                    sceneElements.clear();
                    firstIteration = false;
                }
                SceneElement sceneElement;
                do {
                    token = ParseString(stream);

                    if (token == "Lamp") {
                        std::string member = ParseString(stream);
                        sceneElement.lamps.push_back(member);
                    } else if (token == "LampGroup") {
                        std::string member = ParseString(stream);
                        sceneElement.lampGroups.push_back(member);
                    } else if (token == "Effect") {
                        sceneElement.effectID = ParseString(stream);
                    } else {
                        break;
                    }
                } while (token != "EndSceneElement");

                std::pair<LSFString, SceneElement> thePair(name, sceneElement);
                sceneElements[id] = thePair;
            }
        }
    }
}

void SceneElementManager::HandleReceivedBlob(const std::string& blob, uint32_t checksum, uint64_t timestamp)
{
    QCC_DbgPrintf(("%s", __func__));
    uint64_t currentTimestamp = GetTimestampInMs();
    sceneElementsLock.Lock();
    if (((timeStamp == 0) || ((currentTimestamp - timeStamp) > timestamp)) && (checkSum != checksum)) {
        std::istringstream stream(blob.c_str());
        ReplaceMap(stream);
        timeStamp = currentTimestamp;
        checkSum = checksum;
        ScheduleFileWrite(true);
    }
    sceneElementsLock.Unlock();
}

uint32_t SceneElementManager::GetControllerServiceSceneElementInterfaceVersion(void)
{
    QCC_DbgPrintf(("%s: controllerSceneElementInterfaceVersion=%d", __func__, ControllerServiceSceneElementInterfaceVersion));
    return ControllerServiceSceneElementInterfaceVersion;
}

bool SceneElementManager::GetString(std::string& output, uint32_t& checksum, uint64_t& timestamp)
{
    QCC_DbgTrace(("%s", __func__));
    SceneElementMap mapCopy;
    mapCopy.clear();
    bool ret = false;
    output.clear();

    sceneElementsLock.Lock();
    // we can't hold this lock for the entire time!
    if (updated) {
        mapCopy = sceneElements;
        updated = false;
        ret = true;
    }
    sceneElementsLock.Unlock();

    if (ret) {
        output = GetString(mapCopy);
        sceneElementsLock.Lock();
        if (blobUpdateCycle) {
            timestamp = timeStamp;
            blobUpdateCycle = false;
        } else {
            if (initialState) {
                timeStamp = timestamp = 0UL;
                initialState = false;
            } else {
                timeStamp = timestamp = GetTimestampInMs();
            }
        }
        checkSum = checksum = GetChecksum(output);
        sceneElementsLock.Unlock();
    }

    return ret;
}

std::string SceneElementManager::GetString(const SceneElementMap& items)
{
    QCC_DbgTrace(("%s", __func__));

    std::ostringstream stream;
    if (0 == items.size()) {
        if (initialState) {
            QCC_DbgPrintf(("%s: This is the initial state entry", __func__));
            const LSFString& id = initialStateID;
            const LSFString& name = initialStateID;

            stream << "SceneElement " << id << " \"" << name << "\"";
            stream << " EndSceneElement" << std::endl;
        } else {
            QCC_DbgPrintf(("%s: File is being reset", __func__));
            const LSFString& id = resetID;
            const LSFString& name = resetID;

            stream << "SceneElement " << id << " \"" << name << "\"";
            stream << " EndSceneElement" << std::endl;
        }
    } else {
        for (SceneElementMap::const_iterator it = items.begin(); it != items.end(); ++it) {
            const LSFString& id = it->first;
            const LSFString& name = it->second.first;
            const SceneElement& sceneElement = it->second.second;

            stream << GetString(name, id, sceneElement);
        }
    }

    return stream.str();
}

std::string SceneElementManager::GetString(const std::string& name, const std::string& id, const SceneElement& sceneElement)
{
    std::ostringstream stream;
    stream << "SceneElement " << id << " \"" << name << "\"";

    for (LSFStringList::const_iterator lit = sceneElement.lamps.begin(); lit != sceneElement.lamps.end(); ++lit) {
        stream << " Lamp " << *lit;
    }
    for (LSFStringList::const_iterator lit = sceneElement.lampGroups.begin(); lit != sceneElement.lampGroups.end(); ++lit) {
        stream << " LampGroup " << *lit;
    }

    stream << " Effect " << sceneElement.effectID;

    stream << " EndSceneElement" << std::endl;
    return stream.str();
}

void SceneElementManager::SendSceneElementAppliedSignal(LSFString& sceneElementId)
{
    QCC_DbgPrintf(("%s: %s", __func__, sceneElementId.c_str()));
    bool found = false;
    sceneElementsLock.Lock();
    SceneElementMap::iterator it = sceneElements.find(sceneElementId);
    if (it != sceneElements.end()) {
        found = true;
    }
    sceneElementsLock.Unlock();

    if (found) {
        LSFStringList sceneElementList;
        sceneElementList.push_back(sceneElementId);
        controllerService.SendSignal(ControllerServiceSceneElementInterfaceName, "SceneElementsApplied", sceneElementList);
    }
}
