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
#include <lsf/controllerservice/MasterSceneManager.h>
#include <lsf/controllerservice/ControllerService.h>
#include <lsf/controllerservice/OEM_CS_Config.h>
#include <lsf/controllerservice/FileParser.h>
#else
#include <MasterSceneManager.h>
#include <ControllerService.h>
#include <OEM_CS_Config.h>
#include <FileParser.h>
#endif

#include <qcc/Debug.h>

using namespace lsf;
using namespace ajn;

#ifdef LSF_BINDINGS
using namespace controllerservice;
#define QCC_MODULE "CONTROLLER_MASTER_SCENE_MANAGER"
#else
#define QCC_MODULE "MASTER_SCENE_MANAGER"
#endif

MasterSceneManager::MasterSceneManager(ControllerService& controllerSvc, SceneManager& sceneMgr, const std::string& masterSceneFile) :
    Manager(controllerSvc, masterSceneFile), sceneManager(sceneMgr), blobLength(0)
{
    QCC_DbgTrace(("%s", __func__));
    masterScenes.clear();
    masterSceneUpdates.clear();
}

LSFResponseCode MasterSceneManager::GetAllMasterScenes(MasterSceneMap& masterSceneMap)
{
    QCC_DbgTrace(("%s", __func__));
    LSFResponseCode responseCode = LSF_OK;

    QStatus status = masterScenesLock.Lock();
    if (ER_OK == status) {
        masterSceneMap = masterScenes;
        status = masterScenesLock.Unlock();
        if (ER_OK != status) {
            QCC_LogError(status, ("%s: masterScenesLock.Unlock() failed", __func__));
        }
    } else {
        responseCode = LSF_ERR_BUSY;
        QCC_LogError(status, ("%s: masterScenesLock.Lock() failed", __func__));
    }

    return responseCode;
}

LSFResponseCode MasterSceneManager::Reset(void)
{
    QCC_DbgPrintf(("%s", __func__));
    LSFResponseCode responseCode = LSF_OK;
    if (!controllerService.UpdatesAllowed()) {
        return LSF_ERR_BUSY;
    }

    QStatus tempStatus = masterScenesLock.Lock();
    if (ER_OK == tempStatus) {
        /*
         * Record the IDs of all the MasterScenes that are being deleted
         */
        LSFStringList masterScenesList;
        for (MasterSceneMap::iterator it = masterScenes.begin(); it != masterScenes.end(); ++it) {
            masterScenesList.push_back(it->first);
        }

        /*
         * Clear the MasterScenes
         */
        masterScenes.clear();
        masterSceneUpdates.clear();
        blobLength = 0;
        ScheduleFileWrite();
        tempStatus = masterScenesLock.Unlock();
        if (ER_OK != tempStatus) {
            QCC_LogError(tempStatus, ("%s: masterScenesLock.Unlock() failed", __func__));
        }

        /*
         * Send the MasterScenes deleted signal
         */
        if (masterScenesList.size()) {
            tempStatus = controllerService.SendSignal(ControllerServiceMasterSceneInterfaceName, "MasterScenesDeleted", masterScenesList);
            if (ER_OK != tempStatus) {
                QCC_LogError(tempStatus, ("%s: Unable to send MasterScenesDeleted signal", __func__));
            }
        }
    } else {
        responseCode = LSF_ERR_BUSY;
        QCC_LogError(tempStatus, ("%s: masterScenesLock.Lock() failed", __func__));
    }

    return responseCode;
}

LSFResponseCode MasterSceneManager::IsDependentOnScene(LSFString& sceneID)
{
    QCC_DbgTrace(("%s", __func__));
    LSFResponseCode responseCode = LSF_OK;

    QStatus status = masterScenesLock.Lock();
    if (ER_OK == status) {
        for (MasterSceneMap::iterator it = masterScenes.begin(); it != masterScenes.end(); ++it) {
            responseCode = it->second.second.IsDependentOnScene(sceneID);
            if (LSF_OK != responseCode) {
                break;
            }
        }
        status = masterScenesLock.Unlock();
        if (ER_OK != status) {
            QCC_LogError(status, ("%s: masterScenesLock.Unlock() failed", __func__));
        }
    } else {
        responseCode = LSF_ERR_BUSY;
        QCC_LogError(status, ("%s: masterScenesLock.Lock() failed", __func__));
    }

    return responseCode;
}

void MasterSceneManager::GetAllMasterSceneIDs(Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));

    LSFStringList idList;
    LSFResponseCode responseCode = LSF_OK;

    QStatus status = masterScenesLock.Lock();
    if (ER_OK == status) {
        for (MasterSceneMap::iterator it = masterScenes.begin(); it != masterScenes.end(); ++it) {
            idList.push_back(it->first.c_str());
        }
        status = masterScenesLock.Unlock();
        if (ER_OK != status) {
            QCC_LogError(status, ("%s: masterScenesLock.Unlock() failed", __func__));
        }
    } else {
        responseCode = LSF_ERR_BUSY;
        QCC_LogError(status, ("%s: masterScenesLock.Lock() failed", __func__));
    }

    controllerService.SendMethodReplyWithResponseCodeAndListOfIDs(message, responseCode, idList);
}

void MasterSceneManager::SendMasterSceneAppliedSignal(LSFString& sceneorMasterSceneId)
{
    QCC_DbgPrintf(("%s: %s", __func__, sceneorMasterSceneId.c_str()));
    bool found = false;
    masterScenesLock.Lock();
    MasterSceneMap::iterator it = masterScenes.find(sceneorMasterSceneId);
    if (it != masterScenes.end()) {
        found = true;
    }
    masterScenesLock.Unlock();

    if (found) {
        LSFStringList masterSceneList;
        masterSceneList.push_back(sceneorMasterSceneId);
        controllerService.SendSignal(ControllerServiceMasterSceneInterfaceName, "MasterScenesApplied", masterSceneList);
    } else {
        controllerService.GetSceneElementManager().SendSceneElementAppliedSignal(sceneorMasterSceneId);
    }
}

void MasterSceneManager::GetMasterSceneName(Message& message)
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

    LSFString masterSceneID(uniqueId);

    LSFString language = static_cast<LSFString>(args[1].v_string.str);
    if (0 != strcmp("en", language.c_str())) {
        QCC_LogError(ER_FAIL, ("%s: Language %s not supported", __func__, language.c_str()));
        responseCode = LSF_ERR_INVALID_ARGS;
    } else {
        QStatus status = masterScenesLock.Lock();
        if (ER_OK == status) {
            MasterSceneMap::iterator it = masterScenes.find(uniqueId);
            if (it != masterScenes.end()) {
                name = it->second.first;
                responseCode = LSF_OK;
            }
            status = masterScenesLock.Unlock();
            if (ER_OK != status) {
                QCC_LogError(status, ("%s: masterScenesLock.Unlock() failed", __func__));
            }
        } else {
            responseCode = LSF_ERR_BUSY;
            QCC_LogError(status, ("%s: masterScenesLock.Lock() failed", __func__));
        }
    }

    controllerService.SendMethodReplyWithResponseCodeIDLanguageAndName(message, responseCode, masterSceneID, language, name);
}

void MasterSceneManager::SetMasterSceneName(Message& message)
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

    LSFString masterSceneID(uniqueId);

    const char* name;
    args[1].Get("s", &name);

    LSFString language = static_cast<LSFString>(args[2].v_string.str);

    if (!controllerService.UpdatesAllowed()) {
        controllerService.SendMethodReplyWithResponseCodeIDAndName(message, LSF_ERR_BUSY, masterSceneID, language);
        return;
    }

    if (0 != strcmp("en", language.c_str())) {
        QCC_LogError(ER_FAIL, ("%s: Language %s not supported", __func__, language.c_str()));
        responseCode = LSF_ERR_INVALID_ARGS;
    } else if (name[0] == '\0') {
        QCC_LogError(ER_FAIL, ("%s: master scene name is empty", __func__));
        responseCode = LSF_ERR_EMPTY_NAME;
    } else {
        if (strlen(name) > LSF_MAX_NAME_LENGTH) {
            responseCode = LSF_ERR_INVALID_ARGS;
            QCC_LogError(ER_FAIL, ("%s: strlen(name) > LSF_MAX_NAME_LENGTH", __func__));
        } else {
            QStatus status = masterScenesLock.Lock();
            if (ER_OK == status) {
                MasterSceneMap::iterator it = masterScenes.find(uniqueId);
                if (it != masterScenes.end()) {
                    LSFString newName = name;
                    size_t newlen = blobLength - it->second.first.length() + newName.length();

                    if (newlen < MAX_FILE_LEN) {
                        it->second.first = newName;
                        responseCode = LSF_OK;
                        nameChanged = true;
                        ScheduleFileWrite();
                    } else {
                        responseCode = LSF_ERR_RESOURCES;
                    }
                }
                status = masterScenesLock.Unlock();
                if (ER_OK != status) {
                    QCC_LogError(status, ("%s: masterScenesLock.Unlock() failed", __func__));
                }
            } else {
                responseCode = LSF_ERR_BUSY;
                QCC_LogError(status, ("%s: masterScenesLock.Lock() failed", __func__));
            }
        }
    }

    controllerService.SendMethodReplyWithResponseCodeIDAndName(message, responseCode, masterSceneID, language);

    if (nameChanged) {
        LSFStringList idList;
        idList.push_back(masterSceneID);
        controllerService.SendSignal(ControllerServiceMasterSceneInterfaceName, "MasterScenesNameChanged", idList);
    }
}

void MasterSceneManager::CreateMasterScene(Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));

    LSFResponseCode responseCode = LSF_OK;

    LSFString masterSceneID;

    if (!controllerService.UpdatesAllowed()) {
        controllerService.SendMethodReplyWithResponseCodeAndID(message, LSF_ERR_BUSY, masterSceneID);
        return;
    }

    masterSceneID = GenerateUniqueID("MASTER_SCENE");

    bool created = false;

    const ajn::MsgArg* inputArgs;
    size_t numInputArgs;
    message->GetArgs(numInputArgs, inputArgs);

    if (controllerService.CheckNumArgsInMessage(numInputArgs, 3)  != LSF_OK) {
        return;
    }

    MasterScene masterScene(inputArgs[0]);

    LSFString name = static_cast<LSFString>(inputArgs[1].v_string.str);
    LSFString language = static_cast<LSFString>(inputArgs[2].v_string.str);

    if (0 != strcmp("en", language.c_str())) {
        QCC_LogError(ER_FAIL, ("%s: Language %s not supported", __func__, language.c_str()));
        responseCode = LSF_ERR_INVALID_ARGS;
    } else if (name.empty()) {
        QCC_LogError(ER_FAIL, ("%s: master scene name is empty", __func__));
        responseCode = LSF_ERR_EMPTY_NAME;
    } else if (name.length() > LSF_MAX_NAME_LENGTH) {
        QCC_LogError(ER_FAIL, ("%s: name length exceeds %d", __func__, LSF_MAX_NAME_LENGTH));
        responseCode = LSF_ERR_INVALID_ARGS;
    } else if (masterScene.scenes.empty()) {
        QCC_LogError(ER_FAIL, ("%s: Empty Scenes list", __func__));
        responseCode = LSF_ERR_INVALID_ARGS;
    } else {
        QStatus status = masterScenesLock.Lock();
        if (ER_OK == status) {
            if (masterScenes.size() < OEM_CS_MAX_SUPPORTED_NUM_LSF_ENTITY) {
                std::string newMasterSceneStr = GetString(name, masterSceneID, masterScene);
                /*
                 * We have to add the masterSceneID length because we need to store
                 * the IDs of the updated master scenes to the updates file
                 */
                size_t newlen = blobLength + newMasterSceneStr.length() + masterSceneID.length();
                if (newlen < MAX_FILE_LEN) {
                    blobLength = newlen;
                    masterScenes[masterSceneID].first = name;
                    masterScenes[masterSceneID].second = masterScene;
                    created = true;
                    ScheduleFileWrite();
                } else {
                    responseCode = LSF_ERR_RESOURCES;
                }
            } else {
                QCC_LogError(ER_FAIL, ("%s: No slot for new MasterScene", __func__));
                responseCode = LSF_ERR_NO_SLOT;
            }
            status = masterScenesLock.Unlock();
            if (ER_OK != status) {
                QCC_LogError(status, ("%s: masterScenesLock.Unlock() failed", __func__));
            }
        } else {
            responseCode = LSF_ERR_BUSY;
            QCC_LogError(status, ("%s: masterScenesLock.Lock() failed", __func__));
        }
    }

    if (!created) {
        masterSceneID.clear();
    }

    controllerService.SendMethodReplyWithResponseCodeAndID(message, responseCode, masterSceneID);

    if (created) {
        LSFStringList idList;
        idList.push_back(masterSceneID);
        controllerService.SendSignal(ControllerServiceMasterSceneInterfaceName, "MasterScenesCreated", idList);
    }
}

void MasterSceneManager::UpdateMasterScene(Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    LSFResponseCode responseCode = LSF_ERR_NOT_FOUND;

    bool updated = false;

    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 2)  != LSF_OK) {
        return;
    }

    const char* uniqueId;
    args[0].Get("s", &uniqueId);

    LSFString masterSceneID(uniqueId);

    if (!controllerService.UpdatesAllowed()) {
        controllerService.SendMethodReplyWithResponseCodeAndID(message, LSF_ERR_BUSY, masterSceneID);
        return;
    }

    MasterScene masterScene(args[1]);

    if (masterScene.scenes.empty()) {
        QCC_LogError(ER_FAIL, ("%s: Empty Scenes list", __func__));
        responseCode = LSF_ERR_INVALID_ARGS;
    } else {
        QStatus status = masterScenesLock.Lock();
        if (ER_OK == status) {
            MasterSceneMap::iterator it = masterScenes.find(uniqueId);
            if (it != masterScenes.end()) {
                size_t newlen = blobLength;
                // sub len of old master scene, add len of new master scene
                newlen -= GetString(it->second.first, masterSceneID, it->second.second).length();
                newlen += GetString(it->second.first, masterSceneID, masterScene).length();

                if (newlen < MAX_FILE_LEN) {
                    blobLength = newlen;
                    masterScenes[masterSceneID].second = masterScene;
                    responseCode = LSF_OK;
                    if (masterSceneUpdates.find(masterSceneID) == masterSceneUpdates.end()) {
                        masterSceneUpdates.insert(masterSceneID);
                    }
                    updated = true;
                    ScheduleFileWrite();
                } else {
                    responseCode = LSF_ERR_RESOURCES;
                }
            }
            status = masterScenesLock.Unlock();
            if (ER_OK != status) {
                QCC_LogError(status, ("%s: masterScenesLock.Unlock() failed", __func__));
            }
        } else {
            responseCode = LSF_ERR_BUSY;
            QCC_LogError(status, ("%s: masterScenesLock.Lock() failed", __func__));
        }
    }

    controllerService.SendMethodReplyWithResponseCodeAndID(message, responseCode, masterSceneID);

    if (updated) {
        LSFStringList idList;
        idList.push_back(masterSceneID);
        controllerService.SendSignal(ControllerServiceMasterSceneInterfaceName, "MasterScenesUpdated", idList);
    }
}

void MasterSceneManager::DeleteMasterScene(Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    LSFString name;
    LSFResponseCode responseCode = LSF_ERR_NOT_FOUND;

    bool deleted = false;

    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 1)  != LSF_OK) {
        return;
    }

    const char* uniqueId;
    args[0].Get("s", &uniqueId);

    LSFString masterSceneID(uniqueId);

    if (!controllerService.UpdatesAllowed()) {
        controllerService.SendMethodReplyWithResponseCodeAndID(message, LSF_ERR_BUSY, masterSceneID);
        return;
    }

    QStatus status = masterScenesLock.Lock();
    if (ER_OK == status) {
        MasterSceneMap::iterator it = masterScenes.find(uniqueId);
        if (it != masterScenes.end()) {
            blobLength -= GetString(it->second.first, uniqueId, it->second.second).length();
            blobLength -= ((GetString(it->second.first, uniqueId, it->second.second).length()) + masterSceneID.length());
            masterScenes.erase(it);
            if (masterSceneUpdates.find(masterSceneID) != masterSceneUpdates.end()) {
                masterSceneUpdates.erase(masterSceneID);
            }

            responseCode = LSF_OK;
            deleted = true;
            ScheduleFileWrite();
        }
        status = masterScenesLock.Unlock();
        if (ER_OK != status) {
            QCC_LogError(status, ("%s: masterScenesLock.Unlock() failed", __func__));
        }
    } else {
        responseCode = LSF_ERR_BUSY;
        QCC_LogError(status, ("%s: masterScenesLock.Lock() failed", __func__));
    }

    controllerService.SendMethodReplyWithResponseCodeAndID(message, responseCode, masterSceneID);

    if (deleted) {
        LSFStringList idList;
        idList.push_back(masterSceneID);
        controllerService.SendSignal(ControllerServiceMasterSceneInterfaceName, "MasterScenesDeleted", idList);
    }
}

void MasterSceneManager::GetMasterScene(Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));

    LSFResponseCode responseCode = LSF_ERR_NOT_FOUND;

    MsgArg outArgs[3];

    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 1)  != LSF_OK) {
        return;
    }

    const char* uniqueId;
    args[0].Get("s", &uniqueId);

    QStatus status = masterScenesLock.Lock();
    if (ER_OK == status) {
        MasterSceneMap::iterator it = masterScenes.find(uniqueId);
        if (it != masterScenes.end()) {
            it->second.second.Get(&outArgs[2]);
            responseCode = LSF_OK;
        } else {
            outArgs[2].Set("as", 0, NULL);
        }
        status = masterScenesLock.Unlock();
        if (ER_OK != status) {
            QCC_LogError(status, ("%s: masterScenesLock.Unlock() failed", __func__));
        }
    } else {
        responseCode = LSF_ERR_BUSY;
        QCC_LogError(status, ("%s: masterScenesLock.Lock() failed", __func__));
    }

    outArgs[0].Set("u", responseCode);
    outArgs[1].Set("s", uniqueId);

    controllerService.SendMethodReply(message, outArgs, 3);
}

void MasterSceneManager::ApplyMasterScene(ajn::Message& message)
{
    QCC_DbgPrintf(("%s: %s", __func__, message->ToString().c_str()));
    LSFResponseCode responseCode = LSF_ERR_NOT_FOUND;

    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerService.CheckNumArgsInMessage(numArgs, 1)  != LSF_OK) {
        return;
    }

    const char* masterSceneId;
    args[0].Get("s", &masterSceneId);

    LSFString uniqueId(masterSceneId);

    LSFStringList scenes;
    LSFStringList appliedList;
    appliedList.push_back(uniqueId);

    QStatus status = masterScenesLock.Lock();
    if (ER_OK == status) {
        MasterSceneMap::iterator it = masterScenes.find(uniqueId);
        if (it != masterScenes.end()) {
            scenes = it->second.second.scenes;
            responseCode = LSF_OK;
        }
        status = masterScenesLock.Unlock();
        if (ER_OK != status) {
            QCC_LogError(status, ("%s: masterScenesLock.Unlock() failed", __func__));
        }
    } else {
        responseCode = LSF_ERR_BUSY;
        QCC_LogError(status, ("%s: masterScenesLock.Lock() failed", __func__));
    }

    if (LSF_OK == responseCode) {
        responseCode = sceneManager.ApplySceneNestedInternal(message, scenes, uniqueId);
    }

    if (LSF_OK != responseCode) {
        controllerService.SendMethodReplyWithResponseCodeAndID(message, responseCode, uniqueId);
    }
}

// Saved scenes have the format:
// (MasterScene id "name" (Scene id)* EndMasterScene)*
void MasterSceneManager::ReadSavedData()
{
    QCC_DbgTrace(("%s", __func__));
    std::istringstream stream;
    if (!ValidateFileAndRead(stream)) {
        /*
         * If there is no file present / CRC check failed on the file create a new
         * file with initialState entry
         */
        masterScenesLock.Lock();
        ScheduleFileWrite(false, true);
        masterScenesLock.Unlock();
        return;
    }

    blobLength = stream.str().size();
    ReplaceMap(stream);

    std::istringstream updateStream;
    if (ValidateUpdateFileAndRead(updateStream)) {
        ReplaceUpdatesList(updateStream);
    }
}

void MasterSceneManager::ReplaceMap(std::istringstream& stream)
{
    QCC_DbgTrace(("%s", __func__));
    bool firstIteration = true;
    while (!stream.eof()) {
        std::string token = ParseString(stream);

        if (token == resetID) {
            QCC_DbgPrintf(("The file has a reset entry. Clearing the map"));
            masterScenes.clear();
        } else if (token == "MasterScene") {
            std::string id = ParseString(stream);
            std::string name = ParseString(stream);
            if (0 == strcmp(id.c_str(), resetID.c_str())) {
                QCC_DbgPrintf(("The file has a reset entry. Clearing the map"));
                masterScenes.clear();
            } else if (0 == strcmp(id.c_str(), initialStateID.c_str())) {
                QCC_DbgPrintf(("The file has a initialState entry. So we ignore it"));
            } else {
                if (firstIteration) {
                    masterScenes.clear();
                    firstIteration = false;
                }
                blobLength += id.length();
                LSFStringList subScenes;

                do {
                    token = ParseString(stream);

                    if (token == "Scene") {
                        std::string scene = ParseString(stream);
                        subScenes.push_back(scene);
                    }
                } while (token != "EndMasterScene");

                MasterScene msc(subScenes);
                std::pair<LSFString, MasterScene> thePair(name, msc);
                masterScenes[id] = thePair;
            }
        }
    }
}

void MasterSceneManager::ReplaceUpdatesList(std::istringstream& stream)
{
    QCC_DbgTrace(("%s", __func__));
    bool firstIteration = true;
    while (!stream.eof()) {
        std::string id = ParseString(stream);
        if (0 == strcmp(id.c_str(), resetID.c_str())) {
            QCC_DbgPrintf(("The file has a reset entry. Clearing the list"));
            masterSceneUpdates.clear();
        } else if (0 == strcmp(id.c_str(), initialStateID.c_str())) {
            QCC_DbgPrintf(("The file has a initialState entry. So we ignore it"));
        } else {
            if (firstIteration) {
                masterSceneUpdates.clear();
                firstIteration = false;
            }
            if (!id.empty()) {
                masterSceneUpdates.insert(id);
                QCC_DbgPrintf(("%s: Add %s to updates list", __func__, id.c_str()));
            }
        }
    }
}

std::string MasterSceneManager::GetString(const std::string& name, const std::string& id, const MasterScene& msc)
{
    std::ostringstream stream;
    stream << "MasterScene " << id << " \"" << name << "\"";

    for (LSFStringList::const_iterator sit = msc.scenes.begin(); sit != msc.scenes.end(); ++sit) {
        stream << " Scene " << *sit;
    }

    stream << " EndMasterScene" << std::endl;
    return stream.str();
}

std::string MasterSceneManager::GetString(const MasterSceneMap& items)
{
    QCC_DbgTrace(("%s", __func__));
    std::ostringstream stream;
    // (MasterScene id "name" (Scene id)* EndMasterScene)*
    if (0 == items.size()) {
        if (initialState) {
            QCC_DbgPrintf(("%s: This is the initial state entry", __func__));
            const LSFString& id = initialStateID;
            const LSFString& name = initialStateID;

            stream << "MasterScene " << id << " \"" << name << "\"";
            stream << " EndMasterScene" << std::endl;
        } else {
            const LSFString& id = resetID;
            const LSFString& name = resetID;

            stream << "MasterScene " << id << " \"" << name << "\"";
            stream << " EndMasterScene" << std::endl;
        }
    } else {
        for (MasterSceneMap::const_iterator it = items.begin(); it != items.end(); ++it) {
            const LSFString& id = it->first;
            const LSFString& name = it->second.first;
            const MasterScene& msc = it->second.second;
            stream << GetString(name, id, msc);
        }
    }

    return stream.str();
}

std::string MasterSceneManager::GetUpdatesString(const std::set<LSFString>& updates)
{
    QCC_DbgTrace(("%s", __func__));
    std::ostringstream stream;
    if (0 == updates.size()) {
        if (initialState) {
            QCC_DbgPrintf(("%s: This is the initial state entry", __func__));
            stream << initialStateID << std::endl;
        } else {
            QCC_DbgPrintf(("%s: File is being reset", __func__));
            stream << resetID << std::endl;
        }
    } else {
        for (std::set<LSFString>::const_iterator it = updates.begin(); it != updates.end(); ++it) {
            stream << *it << std::endl;
        }
    }

    return stream.str();
}

bool MasterSceneManager::GetString(std::string& output, std::string& updates, uint32_t& checksum, uint64_t& timestamp, uint32_t& updatesChksum, uint64_t& updatesTs)
{
    QCC_DbgTrace(("%s", __func__));
    MasterSceneMap mapCopy;
    mapCopy.clear();
    std::set<LSFString> updatesCopy;
    updatesCopy.clear();
    bool ret = false;
    output.clear();
    updates.clear();

    masterScenesLock.Lock();
    // we can't hold this lock for the entire time!
    if (updated) {
        mapCopy = masterScenes;
        updatesCopy = masterSceneUpdates;
        updated = false;
        ret = true;
    }
    masterScenesLock.Unlock();

    if (ret) {
        output = GetString(mapCopy);
        updates = GetUpdatesString(updatesCopy);
        masterScenesLock.Lock();
        if (blobUpdateCycle) {
            timestamp = timeStamp;
            updatesTs = updatesTimeStamp;
            blobUpdateCycle = false;
        } else {
            if (initialState) {
                timeStamp = timestamp = 0UL;
                updatesTimeStamp = updatesTs = 0UL;
                initialState = false;
            } else {
                timeStamp = timestamp = GetTimestampInMs();
                updatesTimeStamp = updatesTs = GetTimestampInMs();
            }
        }
        checkSum = checksum = GetChecksum(output);
        updatesCheckSum = updatesChksum = GetChecksum(updates);
        masterScenesLock.Unlock();
    }

    return ret;
}

void MasterSceneManager::HandleReceivedBlob(const std::string& blob, uint32_t checksum, uint64_t timestamp)
{
    QCC_DbgPrintf(("%s", __func__));
    uint64_t currentTimestamp = GetTimestampInMs();
    masterScenesLock.Lock();
    if (((timeStamp == 0) || ((currentTimestamp - timeStamp) > timestamp)) && (checkSum != checksum)) {
        std::istringstream stream(blob.c_str());
        ReplaceMap(stream);
        timeStamp = currentTimestamp;
        checkSum = checksum;
        ScheduleFileWrite(true);
    }
    masterScenesLock.Unlock();
}

void MasterSceneManager::HandleReceivedUpdateBlob(const std::string& blob, uint32_t checksum, uint64_t timestamp)
{
    QCC_DbgPrintf(("%s", __func__));
    uint64_t currentTimestamp = GetTimestampInMs();
    masterScenesLock.Lock();
    if (((updatesTimeStamp == 0) || ((currentTimestamp - updatesTimeStamp) > timestamp)) && (updatesCheckSum != checksum)) {
        std::istringstream stream(blob.c_str());
        ReplaceUpdatesList(stream);
        updatesTimeStamp = currentTimestamp;
        updatesCheckSum = checksum;
        ScheduleFileWrite(true);
    }
    masterScenesLock.Unlock();
}

void MasterSceneManager::ReadWriteFile()
{
    QCC_DbgPrintf(("%s", __func__));

    if (filePath.empty() || updateFilePath.empty()) {
        return;
    }

    std::string output;
    uint32_t checksum;
    uint64_t timestamp;
    std::string updates;
    uint32_t updateChecksum;
    uint64_t updateTimestamp;
    bool status = false;

    status = GetString(output, updates, checksum, timestamp, updateChecksum, updateTimestamp);

    if (status) {
        WriteFileWithChecksumAndTimestamp(output, checksum, timestamp);
        if (timestamp != 0UL) {
            uint64_t currentTime = GetTimestampInMs();
            controllerService.SendBlobUpdate(LSF_MASTER_SCENE, output, checksum, (currentTime - timestamp));
        }

        WriteUpdatesFileWithChecksumAndTimestamp(updates, updateChecksum, updateTimestamp);
        if (updateTimestamp != 0UL) {
            uint64_t currentTime = GetTimestampInMs();
            controllerService.SendBlobUpdate(LSF_MASTER_SCENE_UPDATE, updates, updateChecksum, (currentTime - updateTimestamp));
        }
    }

    std::list<ajn::Message> tempMessageList;
    std::list<ajn::Message> tempUpdateMessageList;

    readMutex.Lock();
    if (read) {
        tempMessageList = readBlobMessages;
        readBlobMessages.clear();
        tempUpdateMessageList = readUpdateBlobMessages;
        readUpdateBlobMessages.clear();
        read = false;
    }
    readMutex.Unlock();

    if ((tempMessageList.size() || tempUpdateMessageList.size() || sendUpdate) && !status) {
        std::istringstream stream;
        bool fileStatus = ValidateFileAndReadInternal(checksum, timestamp, stream);
        if (fileStatus) {
            output = stream.str();
            while (!tempMessageList.empty()) {
                uint64_t currentTime = GetTimestampInMs();
                controllerService.SendGetBlobReply(tempMessageList.front(), LSF_MASTER_SCENE, output, checksum, (currentTime - timestamp));
                tempMessageList.pop_front();
            }
        } else {
            QCC_LogError(ER_FAIL, ("%s: MasterScene persistent store corrupted", __func__));
        }

        std::istringstream updateStream;
        bool updateStatus = ValidateUpdateFileAndReadInternal(updateChecksum, updateTimestamp, updateStream);
        if (updateStatus) {
            updates = updateStream.str();
            while (!tempUpdateMessageList.empty()) {
                uint64_t currentTime = GetTimestampInMs();
                controllerService.SendGetBlobReply(tempUpdateMessageList.front(), LSF_MASTER_SCENE_UPDATE, updates, updateChecksum, (currentTime - updateTimestamp));
                tempUpdateMessageList.pop_front();
            }
        } else {
            QCC_LogError(ER_FAIL, ("%s: Master Scene Update persistent store corrupted", __func__));
        }
    }

    if (sendUpdate) {
        sendUpdate = false;
        uint64_t currentTime = GetTimestampInMs();
        controllerService.GetLeaderElectionObj().SendBlobUpdate(LSF_MASTER_SCENE, output, checksum, (currentTime - timestamp));
        controllerService.GetLeaderElectionObj().SendBlobUpdate(LSF_MASTER_SCENE_UPDATE, updates, updateChecksum, (currentTime - updateTimestamp));
    }
}

uint32_t MasterSceneManager::GetControllerServiceMasterSceneInterfaceVersion(void)
{
    QCC_DbgPrintf(("%s: controllerMasterSceneInterfaceVersion=%d", __func__, ControllerServiceMasterSceneInterfaceVersion));
    return ControllerServiceMasterSceneInterfaceVersion;
}
