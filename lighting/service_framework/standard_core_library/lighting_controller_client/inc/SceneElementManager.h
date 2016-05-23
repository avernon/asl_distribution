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
#ifndef _SCENE_ELEMENT_MANAGER_H_
#define _SCENE_ELEMENT_MANAGER_H_
/**
 * \ingroup ControllerClient
 */
/**
 * \file lighting_controller_client/inc/SceneElementManager.h
 * This file provides definitions for Scene Element Manager
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

#include <LSFTypes.h>
#include <Manager.h>
#include <LSFResponseCodes.h>
#include <ControllerClientDefs.h>
#include <list>

namespace lsf {

class ControllerClient;

/**
 * SceneElement callback class
 */
class SceneElementManagerCallback {
  public:
    virtual ~SceneElementManagerCallback() { }

    /**
     * Response to SceneElementManager::GetAllSceneElementIds.
     *
     * @param responseCode    The response code
     * @param sceneElementIDs The list of sceneElement ID's
     */
    virtual void GetAllSceneElementIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& sceneElementIDs) { }

    /**
     * Response to SceneElementManager::GetSceneElementName.
     *
     * @param responseCode    The response code: \n
     *   LSF_OK - operation succeeded \n
     *   LSF_ERR_NOT_FOUND  - the sceneElement not found \n
     *   LSF_ERR_INVALID_ARGS - Language not supported \n
     * @param sceneElementID    The id of the sceneElement
     * @param language          The language of the sceneElement name
     * @param sceneElementName  The name of the sceneElement
     */
    virtual void GetSceneElementNameReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID, const LSFString& language, const LSFString& sceneElementName) { }

    /**
     * Response to SceneElementManager::SetSceneElementName.
     *
     * @param responseCode    The response code: \n
     *   LSF_OK - operation succeeded \n
     *   LSF_ERR_INVALID_ARGS - Language not supported, length exceeds LSF_MAX_NAME_LENGTH \n
     *   LSF_ERR_EMPTY_NAME - sceneElement name is empty \n
     *   LSF_ERR_RESOURCES - blob length is longer than MAX_FILE_LEN \n
     * @param sceneElementID    The id of the sceneElement whose name was changed
     * @param language          language of the sceneElement
     */
    virtual void SetSceneElementNameReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID, const LSFString& language) { }

    /**
     * This signal is fired any time a sceneElement's name is changed.
     *
     * @param sceneElementIDs    The id of the sceneElement whose name changed
     */
    virtual void SceneElementsNameChangedCB(const LSFStringList& sceneElementIDs) { }

    /**
     * Response to SceneElementManager::CreateSceneElement.
     *
     * @param responseCode    The response code: \n
     *  LSF_OK - operation succeeded \n
     *  LSF_ERR_INVALID_ARGS - Language not supported, sceneElement name is empty, Invalid SceneElement components specified, ame length exceeds \n
     *  LSF_ERR_RESOURCES - Could not allocate memory \n
     *  LSF_ERR_NO_SLOT - No slot for new SceneElement \n
     * @param sceneElementID    The id of the new SceneElement
     * @param trackingID     The tracking ID that the application can use to associate the method call with the reply
     */
    virtual void CreateSceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID, const uint32_t& trackingID) { }

    /**
     *  This signal is fired any time a sceneElement is been created.
     *
     * @param sceneElementIDs    The id of the new sceneElement
     */
    virtual void SceneElementsCreatedCB(const LSFStringList& sceneElementIDs) { }

    /**
     * Response to SceneElementManager::UpdateSceneElement.
     *
     * @param responseCode    The response code: \n
     *  LSF_OK - operation succeeded \n
     *  LSF_ERR_INVALID_ARGS - Language not supported, sceneElement name is empty, Invalid SceneElement components specified, ame length exceeds \n
     *  LSF_ERR_RESOURCES - Could not allocate memory \n
     *  LSF_ERR_NO_SLOT - No slot for new SceneElement \n
     * @param sceneElementID    The id of the new SceneElement
     */
    virtual void UpdateSceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID) { }

    /**
     * This signal is fired any time a sceneElement has been updated.
     *
     * @param sceneElementIDs    The id of the updated sceneElement
     */
    virtual void SceneElementsUpdatedCB(const LSFStringList& sceneElementIDs) { }

    /**
     * Response to SceneElementManager::DeleteSceneElement.
     *
     * @param responseCode    The response code: \n
     *  LSF_OK - operation succeeded \n
     *  LSF_ERR_NOT_FOUND - can't find sceneElement id \n
     * @param sceneElementID    The id of the deleted sceneElement
     */
    virtual void DeleteSceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID) { }

    /**
     * This signal is fired any time a sceneElement has been deleted.
     *
     * @param sceneElementIDs    The id of the deleted sceneElement
     */
    virtual void SceneElementsDeletedCB(const LSFStringList& sceneElementIDs) { }

    /**
     * Response to SceneElementManager::GetSceneElement.
     *
     * @param responseCode    The response code: \n
     *  return LSF_OK \n
     *  return LSF_ERR_NOT_FOUND - sceneElement not found \n
     * @param sceneElementID    The id of the sceneElement
     * @param sceneElement      The sceneElement data
     */
    virtual void GetSceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID, const SceneElement& sceneElement) { }

    /**
     * Response to SceneElementManager::ApplySceneElement.
     *
     * @param responseCode    The response code \n
     *  LSF_OK - on success \n
     *  LSF_ERR_NOT_FOUND - sceneElement id not found in current list of sceneElements
     * @param sceneElementID    The id of the sceneElement
     */
    virtual void ApplySceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID) { }

    /**
     * This signal is fired any time a sceneElement has been applied.
     *
     * @param sceneElementIDs    The id of the sceneElement
     */
    virtual void SceneElementsAppliedCB(const LSFStringList& sceneElementIDs) { }
};


/**
 * sceneElement management class
 */
class SceneElementManager : public Manager {

    friend class ControllerClient;

  public:
    /**
     * SceneElementManager CTOR.
     * @param controller - a reference to ControllerClient instance
     * @param callback - a reference to SceneElementManagerCallback instance, to get the callback messages
     */
    SceneElementManager(ControllerClient& controller, SceneElementManagerCallback& callback);

    /**
     * Get the IDs of all available sceneElements. \n
     * Response comes in SceneElementManagerCallback::GetAllSceneElementIDsReplyCB
     */
    ControllerClientStatus GetAllSceneElementIDs(void);

    /**
     * Get the name of the given SceneElement. \n
     * Response in SceneElementManagerCallback::GetSceneElementNameReplyCB
     *
     * @param sceneElementID    The id of the sceneElement
     * @param language   The requested language
     */
    ControllerClientStatus GetSceneElementName(const LSFString& sceneElementID, const LSFString& language = LSFString("en"));

    /**
     * Set the name of a SceneElement. \n
     * Response in SceneElementManagerCallback::SetSceneElementNameReplyCB
     *
     * @param sceneElementID    The id of the sceneElement to modify
     * @param sceneElementName  The new sceneElement name
     * @param language   The requested language
     */
    ControllerClientStatus SetSceneElementName(const LSFString& sceneElementID, const LSFString& sceneElementName, const LSFString& language = LSFString("en"));

    /**
     *  Create a new SceneElement. \n
     *  Response in SceneElementManagerCallback::CreateElementReplyCB
     *
     * @param trackingID  Controller Client returns a tracking ID in this variable which the application
     *                    can use to associate the reply for this call with the request
     * @param sceneElement      The sceneElement of type TransitionLampsLampGroupsToState
     * @param sceneElementName  The sceneElement name
     * @param language          The sceneElement language
     */
    ControllerClientStatus CreateSceneElement(uint32_t& trackingID, const SceneElement& sceneElement, const LSFString& sceneElementName, const LSFString& language = LSFString("en"));

    /**
     * Modify an existing sceneElement. \n
     * Response in SceneElementManagerCallback::UpdateElementReplyCB \n
     *
     * @param sceneElementID    The id of the sceneElement to modify
     * @param sceneElement      The new value of the sceneElement
     */
    ControllerClientStatus UpdateSceneElement(const LSFString& sceneElementID, const SceneElement& sceneElement);

    /**
     * Delete an existing sceneElement. \n
     * Response in SceneElementManagerCallback::DeleteSceneElementReplyCB
     *
     * @param sceneElementID    The id of the sceneElement to delete
     */
    ControllerClientStatus DeleteSceneElement(const LSFString& sceneElementID);

    /**
     * Get the information about the specified sceneElement. \n
     * Response in SceneElementManagerCallback::GetSceneElementReplyCB
     *
     * @param sceneElementID    The id of the sceneElement to find
     */
    ControllerClientStatus GetSceneElement(const LSFString& sceneElementID);

    /**
     * Apply a sceneElement. \n
     * Activate an already created sceneElement. Make it happen. \n
     * Response in SceneElementManagerCallback::ApplySceneElementReplyCB
     *
     * @param sceneElementID    The ID of the sceneElement to apply
     */
    ControllerClientStatus ApplySceneElement(const LSFString& sceneElementID);

    /**
     * Get the SceneElement Info and Name. \n
     * Combination of GetSceneElement and GetScneneName. Responses are accordingly. \n
     *
     * @param sceneElementID    The ID of the master sceneElement
     * @param language   The requested language
     */
    ControllerClientStatus GetSceneElementDataSet(const LSFString& sceneElementID, const LSFString& language = LSFString("en"));

  private:

    // Signal handlers:
    void SceneElementsNameChanged(LSFStringList& idList) {
        callback.SceneElementsNameChangedCB(idList);
    }

    void SceneElementsCreated(LSFStringList& idList) {
        callback.SceneElementsCreatedCB(idList);
    }

    void SceneElementsUpdated(LSFStringList& idList) {
        callback.SceneElementsUpdatedCB(idList);
    }

    void SceneElementsDeleted(LSFStringList& idList) {
        callback.SceneElementsDeletedCB(idList);
    }

    void SceneElementsApplied(LSFStringList& idList) {
        callback.SceneElementsAppliedCB(idList);
    }

    // asynch method response handlers
    void GetAllSceneElementIDsReply(LSFResponseCode& responseCode, LSFStringList& idList) {
        callback.GetAllSceneElementIDsReplyCB(responseCode, idList);
    }

    void GetSceneElementReply(ajn::Message& message);

    void ApplySceneElementReply(LSFResponseCode& responseCode, LSFString& lsfId) {
        callback.ApplySceneElementReplyCB(responseCode, lsfId);
    }

    void DeleteSceneElementReply(LSFResponseCode& responseCode, LSFString& lsfId) {
        callback.DeleteSceneElementReplyCB(responseCode, lsfId);
    }

    void SetSceneElementNameReply(LSFResponseCode& responseCode, LSFString& lsfId, LSFString& language) {
        callback.SetSceneElementNameReplyCB(responseCode, lsfId, language);
    }

    void GetSceneElementNameReply(LSFResponseCode& responseCode, LSFString& lsfId, LSFString& language, LSFString& lsfName) {
        callback.GetSceneElementNameReplyCB(responseCode, lsfId, language, lsfName);
    }

    void CreateSceneElementReply(LSFResponseCode& responseCode, LSFString& lsfId, uint32_t& trackingID) {
        callback.CreateSceneElementReplyCB(responseCode, lsfId, trackingID);
    }

    void UpdateSceneElementReply(LSFResponseCode& responseCode, LSFString& lsfId) {
        callback.UpdateSceneElementReplyCB(responseCode, lsfId);
    }

    SceneElementManagerCallback& callback;
};


}

#endif
