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
 * \ingroup ControllerClient
 */
/**
 * \file  lighting_controller_client/inc/MasterSceneManager.h
 * This file provides definitions for controller client
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

#include <list>

#include <Manager.h>
#include <ControllerClientDefs.h>

namespace lsf {

class ControllerClient;
/**
 * a callback class that its instance and members are given to the MasterScene to get the methods reply and signals that are coming from the controller service.
 */
class MasterSceneManagerCallback {
  public:
    virtual ~MasterSceneManagerCallback() { }

    /**
     * Response to MasterSceneManager::GetAllMasterSceneIDs
     *
     * @param responseCode        The response code
     * @param masterSceneList    The masterScene ID's
     */
    virtual void GetAllMasterSceneIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& masterSceneList) { }

    /**
     * Response to MasterSceneManager::GetMasterSceneName
     *
     * @param responseCode    The response code
     * @param masterSceneID    The masterScene id
     * @param language
     * @param masterSceneName  The masterScene masterSceneName
     */
    virtual void GetMasterSceneNameReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const LSFString& language, const LSFString& masterSceneName) { }

    /**
     * Response to MasterSceneManager::SetMasterSceneName
     *
     * @param responseCode    The response code
     * @param masterSceneID    The Lamp masterScene id
     * @param language
     */
    virtual void SetMasterSceneNameReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const LSFString& language) { }

    /**
     * A masterScene has had its masterSceneName set
     *
     * @param masterSceneIDs    The masterScene id
     */
    virtual void MasterScenesNameChangedCB(const LSFStringList& masterSceneIDs) { }

    /**
     * Response to MasterSceneManager::CreateMasterScene
     *
     * @param responseCode    The response code
     * @param masterSceneID    The masterScene id
     */
    virtual void CreateMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID) { }

    /**
     * Indicates that a reply has been received for the CreateMasterSceneWithTracking method call.
     *
     * @param responseCode   The response code
     * @param masterSceneID  The Master Scene ID
     * @param trackingID     The tracking ID that the application can use to associate the CreateMasterSceneWithTracking
     *                       method call with the reply
     */
    virtual void CreateMasterSceneWithTrackingReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const uint32_t& trackingID) { }

    /**
     *  A masterScene has been created
     *
     *  @param masterSceneIDs   The masterScene id
     */
    virtual void MasterScenesCreatedCB(const LSFStringList& masterSceneIDs) { }

    /**
     * Response to MasterSceneManager::GetMasterScene
     *
     * @param responseCode    The response code
     * @param masterSceneID    The Lamp masterScene id
     * @param masterScene The GroupID
     */
    virtual void GetMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const MasterScene& masterScene) { }

    /**
     * Response to MasterSceneManager::DeleteMasterScene
     *
     * @param responseCode    The response code
     * @param masterSceneID    The Lamp masterScene id
     */
    virtual void DeleteMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID) { }

    /**
     *  A masterScene has been deleted
     *
     *  @param masterSceneIDs   The masterScene id
     */
    virtual void MasterScenesDeletedCB(const LSFStringList& masterSceneIDs) { }

    /**
     * Response to MasterSceneManager::UpdateMasterScene
     *
     * @param responseCode    The response code
     * @param masterSceneID    The Lamp masterScene id
     */
    virtual void UpdateMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID) { }

    /**
     * A Lamp masterScene has been updated
     *
     * @param masterSceneIDs    The id of the Lamp masterScene
     */
    virtual void MasterScenesUpdatedCB(const LSFStringList& masterSceneIDs) { }

    /**
     * Response to MasterSceneManager::ApplyMasterScene
     *
     * @param responseCode    The response code
     * @param masterSceneID    The id of the scene masterScene
     */
    virtual void ApplyMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID) { }

    /**
     * A scene masterScene has been applied
     *
     * @param masterSceneIDs    The id of the scene masterScene
     */
    virtual void MasterScenesAppliedCB(const LSFStringList& masterSceneIDs) { }
};

/**
 * Master Scene Manager
 */
class MasterSceneManager : public Manager {

    friend class ControllerClient;

  public:
    /**
     * MasterSceneManager constructor
     */
    MasterSceneManager(ControllerClient& controller, MasterSceneManagerCallback& callback);

    /**
     * Get the IDs of all masterSceneList. \n
     * Response in MasterSceneManagerCallback::GetAllMasterSceneIDsReplyCB
     */
    ControllerClientStatus GetAllMasterSceneIDs(void);

    /**
     * Get the names of the masterScene. \n
     * Response in MasterSceneManagerCallback::GetMasterSceneNameCB
     *
     * @param masterSceneID    The masterScene id
     * @param language
     */
    ControllerClientStatus GetMasterSceneName(const LSFString& masterSceneID, const LSFString& language = LSFString("en"));

    /**
     * Set the masterSceneName of the specified masterScene. \n
     * Response in MasterSceneManagerCallback::SetMasterSceneNameReplyCB
     *
     * @param masterSceneID    The id of the masterScene
     * @param masterSceneName  The Master Scene Name
     * @param language
     */
    ControllerClientStatus SetMasterSceneName(const LSFString& masterSceneID, const LSFString& masterSceneName, const LSFString& language = LSFString("en"));

    /**
     * Create a new Scene masterScene. \n
     * Response in MasterSceneManagerCallback::CreateMasterSceneReplyCB
     *
     */
    ControllerClientStatus CreateMasterScene(const MasterScene& masterScene, const LSFString& masterSceneName, const LSFString& language = LSFString("en"));

    /**
     * Create a new Master Scene and provide a API call tracking ID back to the application. \n
     * Response in MasterSceneManagerCallback::CreateMasterSceneWithTrackingReplyCB
     *
     * @param trackingID  Controller Client returns a tracking ID in this variable which the application
     *                    can use to associate the reply for this call with the request
     * @param masterScene   Master Scene
     * @param masterSceneName
     * @param language
     * @return
     *      - CONTROLLER_CLIENT_OK if successful
     *      - An error status otherwise
     *
     */
    ControllerClientStatus CreateMasterSceneWithTracking(uint32_t& trackingID, const MasterScene& masterScene, const LSFString& masterSceneName, const LSFString& language = LSFString("en"));

    /**
     * Modify a masterScene. \n
     * Change master scene to another master scene. \n
     * Response in MasterSceneManagerCallback::UpdateMasterSceneReplyCB
     *
     * @param masterSceneID    The id of the masterScene to modify
     * @param masterScene
     */
    ControllerClientStatus UpdateMasterScene(const LSFString& masterSceneID, const MasterScene& masterScene);

    /**
     * Get the information about the masterScene. \n
     * Response in MasterSceneManagerCallback::GetMasterSceneReplyCB
     *
     * @param masterSceneID    Group id to get
     */
    ControllerClientStatus GetMasterScene(const LSFString& masterSceneID);

    /**
     * Delete a Lamp masterScene. \n
     * Response in MasterSceneManagerCallback::DeleteMasterSceneReplyCB
     *
     * @param masterSceneID    The id of the masterScene to delete
     */
    ControllerClientStatus DeleteMasterScene(const LSFString& masterSceneID);

    /**
     * Apply a scene masterScene. \n
     * Make the master scene happen. \n
     * Response in MasterSceneManagerCallback::ApplyMasterSceneReplyCB
     *
     * @param masterSceneID    The ID of the scene to apply
     */
    ControllerClientStatus ApplyMasterScene(const LSFString& masterSceneID);

    /**
     * Get the Master Scene Info and Name
     *
     * @param masterSceneID    The ID of the master scene
     * @param language
     */
    ControllerClientStatus GetMasterSceneDataSet(const LSFString& masterSceneID, const LSFString& language = LSFString("en"));

  private:

    // signal handlers
    void MasterScenesNameChanged(LSFStringList& idList) {
        callback.MasterScenesNameChangedCB(idList);
    }

    void MasterScenesCreated(LSFStringList& idList) {
        callback.MasterScenesCreatedCB(idList);
    }

    void MasterScenesDeleted(LSFStringList& idList) {
        callback.MasterScenesDeletedCB(idList);
    }

    void MasterScenesUpdated(LSFStringList& idList) {
        callback.MasterScenesUpdatedCB(idList);
    }

    void MasterScenesApplied(LSFStringList& idList) {
        callback.MasterScenesAppliedCB(idList);
    }

    // method response handlers
    void GetAllMasterSceneIDsReply(LSFResponseCode& responseCode, LSFStringList& idList) {
        callback.GetAllMasterSceneIDsReplyCB(responseCode, idList);
    }

    void GetMasterSceneNameReply(LSFResponseCode& responseCode, LSFString& lsfId, LSFString& language, LSFString& lsfName) {
        callback.GetMasterSceneNameReplyCB(responseCode, lsfId, language, lsfName);
    }

    void ApplyMasterSceneReply(LSFResponseCode& responseCode, LSFString& lsfId) {
        callback.ApplyMasterSceneReplyCB(responseCode, lsfId);
    }

    void SetMasterSceneNameReply(LSFResponseCode& responseCode, LSFString& lsfId, LSFString& language) {
        callback.SetMasterSceneNameReplyCB(responseCode, lsfId, language);
    }

    void CreateMasterSceneReply(LSFResponseCode& responseCode, LSFString& lsfId) {
        callback.CreateMasterSceneReplyCB(responseCode, lsfId);
    }

    void CreateMasterSceneWithTrackingReply(LSFResponseCode& responseCode, LSFString& lsfId, uint32_t& trackingID) {
        callback.CreateMasterSceneWithTrackingReplyCB(responseCode, lsfId, trackingID);
    }

    void UpdateMasterSceneReply(LSFResponseCode& responseCode, LSFString& lsfId) {
        callback.UpdateMasterSceneReplyCB(responseCode, lsfId);
    }

    void GetMasterSceneReply(ajn::Message& message);

    void DeleteMasterSceneReply(LSFResponseCode& responseCode, LSFString& lsfId) {
        callback.DeleteMasterSceneReplyCB(responseCode, lsfId);
    }

    MasterSceneManagerCallback&   callback;
};


}

#endif
