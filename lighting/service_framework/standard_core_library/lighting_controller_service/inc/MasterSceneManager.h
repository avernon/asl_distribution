# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
#ifndef _MASTER_SCENE_MANAGER_H_
#define _MASTER_SCENE_MANAGER_H_
/**
 * \ingroup ControllerService
 */
/**
 * @file
 * This file provides definitions for master scene manager
 */
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
#include <lsf/controllerservice/Manager.h>
#include <lsf/controllerservice/SceneManager.h>
#else
#include <Manager.h>
#include <SceneManager.h>
#endif

#include <Mutex.h>
#include <LSFTypes.h>

#include <string>
#include <map>
#include "LSFNamespaceSpecifier.h"

namespace lsf {

OPTIONAL_NAMESPACE_CONTROLLER_SERVICE

/**
 * Master Scene Manager
 */
class MasterSceneManager : public Manager {

  public:
    /**
     * MasterSceneManager constructor
     */
    MasterSceneManager(ControllerService& controllerSvc, SceneManager& sceneMgr, const std::string& masterSceneFile);
    /**
     * Clearing all master scenes.
     * @return
     *      LSF_OK - in case operation succeeded
     */
    LSFResponseCode Reset(void);
    /**
     * Check if the master scene is depend on scene. \n
     * @param sceneID - the scene id to check dependency on \n
     * @return LSF_OK if there is not dependency. \n
     */
    LSFResponseCode IsDependentOnScene(LSFString& sceneID);
    /**
     * Get All Master scene IDs. \n
     * Return asynchronous reply with response code: \n
     *  LSF_OK - operation succeeded
     */
    void GetAllMasterSceneIDs(ajn::Message& message);
    /**
     * Get master scene name. \n
     * @param message type Message contains: scene unique id (type 's') and requested language (type 's') \n
     * Return asynchronous reply with response code: \n
     *  LSF_OK - operation succeeded \n
     */
    void GetMasterSceneName(ajn::Message& message);
    /**
     * Set Scene name. \n
     * @param message with  MsgArgs -  unique id (signature 's'), name (signature 's'), language (signature 's') . \n
     * Return asynchronous reply with response code: \n
     *  LSF_OK - operation succeeded \n
     */
    void SetMasterSceneName(ajn::Message& message);
    /**
     * Delete master scene \n
     * @param message type Message. Contains one MsgArg with scene id. \n
     * Return asynchronous reply with response code: \n
     *  LSF_OK - operation succeeded \n
     */
    void DeleteMasterScene(ajn::Message& message);
    /**
     * Create master scene and sending signal 'MasterScenesCreated' \n
     * @param message
     *
     * Return asynchronous reply with response code: \n
     *  LSF_OK - operation succeeded \n
     */
    void CreateMasterScene(ajn::Message& message);
    /**
     * Modify an existing master scene and then sending signal 'MasterScenesUpdated'. \n
     */
    void UpdateMasterScene(ajn::Message& message);
    /**
     * Get master scene. - reply asynchronously \n
     * @param message type Message contains MsgArg with parameter unique id (type 's') \n
     *  return LSF_OK \n
     */
    void GetMasterScene(ajn::Message& message);
    /**
     * Apply master scene. \n
     * @param message type Message with MsgArg parameter - scene id (type 's') \n
     * reply asynchronously with response code: \n
     *  LSF_OK - on success \n
     */
    void ApplyMasterScene(ajn::Message& message);
    /**
     * Send Master Scene Applied Signal. \n
     * Sending signals in case a master scene applied: \n
     *      'MasterScenesApplied' signal - in case that master scene applied. \n
     *
     * @param sceneorMasterSceneId - the applied scene id or master scene id
     */
    void SendMasterSceneAppliedSignal(LSFString& sceneorMasterSceneId);
    /**
     * Get All master scenes. \n
     * Return asynchronous answer - the all master scenes by its reference parameter \n
     * @param masterSceneMap of type MasterSceneMap - reference of MasterSceneMap to get all master scenes \n
     * @return LSF_OK on success.
     */
    LSFResponseCode GetAllMasterScenes(MasterSceneMap& masterSceneMap);
    /**
     * Read Saved Data. \n
     * Reads saved info from persistent data
     */
    void ReadSavedData();
    /**
     * Read Write File \n
     * Reading master scenes information from the persistent data and might update other interested controller services by sending blob messages.
     */
    void ReadWriteFile();
    /**
     * Get the version of the master scene inerface. \n
     * Return asynchronously. \n
     * @return version of the master scene inerface
     */
    uint32_t GetControllerServiceMasterSceneInterfaceVersion(void);
    /**
     * Get string representation of master scene objects. \n
     * @param output - string representation of master scene objects
     * @param checksum - of the output
     * @param timestamp - current time
     */
    bool GetString(std::string& output, std::string& updates, uint32_t& checksum, uint64_t& timestamp, uint32_t& updatesChksum, uint64_t& updatesTs);
    /**
     * Get file information. \n
     * Derived from Manager class. \n
     * Answer returns synchronously by the reference parameters.
     * @param checksum
     * @param timestamp
     */
    void GetBlobInfo(uint32_t& checksum, uint64_t& timestamp) {
        masterScenesLock.Lock();
        GetBlobInfoInternal(checksum, timestamp);
        masterScenesLock.Unlock();
    }
    /**
     * Get file information. \n
     * Derived from Manager class. \n
     * Answer returns synchronously by the reference parameters.
     * @param checksum
     * @param timestamp
     */
    void GetUpdateBlobInfo(uint32_t& checksum, uint64_t& timestamp) {
        masterScenesLock.Lock();
        GetUpdateBlobInfoInternal(checksum, timestamp);
        masterScenesLock.Unlock();
    }
    /**
     * Write the blob containing scene information to persistent data. \n
     * @param blob - string containing scenes information.
     * @param checksum
     * @param timestamp
     */
    void HandleReceivedBlob(const std::string& blob, uint32_t checksum, uint64_t timestamp);
    /**
     * Handle Received Update Blob
     */
    void HandleReceivedUpdateBlob(const std::string& blob, uint32_t checksum, uint64_t timestamp);

  private:

    void ReplaceMap(std::istringstream& stream);

    void ReplaceUpdatesList(std::istringstream& stream);

    MasterSceneMap masterScenes;
    std::set<LSFString> masterSceneUpdates;    /**< List of MasterSceneIDs that were updated */
    Mutex masterScenesLock;
    SceneManager& sceneManager;
    size_t blobLength;

    std::string GetString(const MasterSceneMap& items);
    std::string GetUpdatesString(const std::set<LSFString>& updates);
    std::string GetString(const std::string& name, const std::string& id, const MasterScene& msc);
};

OPTIONAL_NAMESPACE_CLOSE

} //lsf

#endif
