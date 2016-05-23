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
#ifndef _PRESET_MANAGER_H_
#define _PRESET_MANAGER_H_
/**
 * \ingroup ControllerClient
 */
/**
 * \file lighting_controller_client/inc/PresentManager.h
 * This file provides definitions for present manager
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
#include <ControllerClientDefs.h>

#include <list>
#include <LSFResponseCodes.h>

namespace lsf {

class ControllerClient;

/**
 * a callback class which object delivered to the PresentManager and its object and methods delivered as a handle to get method replies and signals related to presence of the lamps.
 */
class PresetManagerCallback {
  public:
    /**
     * Destructor
     */
    virtual ~PresetManagerCallback() { }

    /**
     * Response to PresetManager::GetPreset. \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_NOT_FOUND - preset with requested id is not found. \n
     * @param responseCode    The return code
     * @param presetID    The id of the Preset
     * @param preset The state information
     *
     */
    virtual void GetPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const LampState& preset) { }

    /**
     * Response to PresetManager::GetAllPresetIDs. \n
     * response code LSF_OK on success. \n
     * @param responseCode    The return code
     * @param presetIDs   A list of LSFString's
     */
    virtual void GetAllPresetIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& presetIDs) { }

    /**
     * Response to PresetManager::GetPresetName. \n
     * Response code LSF_OK on success. \n
     * @param responseCode    The return code
     * @param presetID    The id of the Preset
     * @param language
     * @param presetName  The name of the Preset
     */
    virtual void GetPresetNameReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const LSFString& language, const LSFString& presetName) { }

    /**
     * Response to PresetManager::SetPresetName. \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_INVALID_ARGS - language not supported, name is too long. \n
     *      LSF_ERR_EMPTY_NAME - preset name is empty. \n
     *      LSF_ERR_RESOURCES - blob is too big. \n
     * @param responseCode    The return code
     * @param presetID    The id of the Preset
     * @param language
     */
    virtual void SetPresetNameReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const LSFString& language) { }

    /**
     * A Preset has been renamed
     *
     * @param presetIDs    The id of the Preset
     */
    virtual void PresetsNameChangedCB(const LSFStringList& presetIDs) { }

    /**
     * Response to PresetManager::CreatePreset. \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_INVALID_ARGS - language not supported, name is too long. \n
     *      LSF_ERR_EMPTY_NAME - preset name is empty. \n
     *      LSF_ERR_RESOURCES - blob is too big. \n
     * @param responseCode    The return code
     * @param presetID    The id of the new Preset
     */
    virtual void CreatePresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID) { }

    /**
     * Indicates that a reply has been received for the CreatePresetWithTracking method call.
     *
     * @param responseCode   The response code
     * @param presetID       The Preset ID
     * @param trackingID     The tracking ID that the application can use to associate the CreatePresetWithTracking
     *                       method call with the reply
     */
    virtual void CreatePresetWithTrackingReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const uint32_t& trackingID) { }

    /**
     * A Preset has been created
     *
     * @param presetIDs    The id of the Preset
     */
    virtual void PresetsCreatedCB(const LSFStringList& presetIDs) { }

    /**
     * Response to PresetManager::UpdatePreset. \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_INVALID_ARGS - language not supported, name is too long. \n
     *      LSF_ERR_RESOURCES - blob is too big. \n
     * @param responseCode    The return code
     * @param presetID    The id of the new Preset
     */
    virtual void UpdatePresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID) { }

    /**
     * A Preset has been updated
     *
     * @param presetIDs    The id of the Preset
     */
    virtual void PresetsUpdatedCB(const LSFStringList& presetIDs) { }

    /**
     * Response to PresetManager::DeletePreset. \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_NOT_FOUND - preset with requested id is not found. \n
     * @param responseCode    The return code
     * @param presetID    The id of the Preset
     */
    virtual void DeletePresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID) { }

    /**
     * A Preset has been deleted
     *
     * @param presetIDs    The id of the Preset
     */
    virtual void PresetsDeletedCB(const LSFStringList& presetIDs) { }

    /**
     *  Indicates that a reply has been received for the GetDefaultLampState method call. \n
     *  response code LSF_OK on success. \n
     *  @param responseCode    The response code
     *  @param defaultLampState   The default LampState
     */
    virtual void GetDefaultLampStateReplyCB(const LSFResponseCode& responseCode, const LampState& defaultLampState) { }

    /**
     *  Indicates that a reply has been received for the SetDefaultLampState method call. \n
     *  response code LSF_OK on success. \n
     *      LSF_ERR_RESOURCES - blob is too big. \n
     *  @param responseCode   The response code from the LightingControllerService
     */
    virtual void SetDefaultLampStateReplyCB(const LSFResponseCode& responseCode) { }

    /**
     * Indicates that a DefaultLampStateChanged signal has been received
     */
    virtual void DefaultLampStateChangedCB(void) { }
};

/**
 * a class manage the status of the lamps
 */
class PresetManager : public Manager {

    friend class ControllerClient;

  public:
    /**
     * class constructor
     */
    PresetManager(ControllerClient& controller, PresetManagerCallback& callback);

    /**
     * Get all preset ids. \n
     * Return asynchronous all preset ids which are not the default lamp state. \n
     * Response in PresetManagerCallback::GetAllPresetIDsReplyCB. \n
     * @return CONTROLLER_CLIENT_OK on success to send the request. \n
     */
    ControllerClientStatus GetAllPresetIDs(void);

    /**
     * Get existing preset. \n
     * Response in PresetManagerCallback::GetPresetReplyCB. \n
     * @param presetID type LSFString which is preset id. \n
     * Return asynchronously the preset response code, unique id and requested lamp state \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_NOT_FOUND - preset with requested id is not found. \n
     */
    ControllerClientStatus GetPreset(const LSFString& presetID);

    /**
     * Get the name of a Preset. \n
     * Response in PresetManagerCallback::GetPresetNameReplyCB. \n
     * Return asynchronously the preset name, id, language and response code. \n
     *
     * @param presetID    The id of the Preset
     * @param language
     */
    ControllerClientStatus GetPresetName(const LSFString& presetID, const LSFString& language = LSFString("en"));

    /**
     * Set the name of a Preset. \n
     * Return asynchronously the preset new name, id, language and response code. \n
     * Response in PresetManagerCallback::SetPresetNameReplyCB
     *
     * @param presetID    The id of the Preset
     * @param presetName  The new name of the Preset
     * @param language
     */
    ControllerClientStatus SetPresetName(const LSFString& presetID, const LSFString& presetName, const LSFString& language = LSFString("en"));

    /**
     * Create a new preset. \n
     * Response in PresetManagerCallback::CreatePresetReplyCB. \n
     * Return asynchronously the preset response code and auto generated unique id. \n
     *
     * @param preset The new state information
     * @param presetName
     * @param language
     */
    ControllerClientStatus CreatePreset(const LampState& preset, const LSFString& presetName, const LSFString& language = LSFString("en"));

    /**
     * Create a new Preset and provide a API call tracking ID back to the application. \n
     * Response in PresetManagerCallback::CreatePresetWithTrackingReplyCB
     *
     * @param trackingID  Controller Client returns a tracking ID in this variable which the application
     *                    can use to associate the reply for this call with the request
     * @param preset   Preset
     * @param presetName
     * @param language
     * @return
     *      - CONTROLLER_CLIENT_OK if successful
     *      - An error status otherwise
     *
     */
    ControllerClientStatus CreatePresetWithTracking(uint32_t& trackingID, const LampState& preset, const LSFString& presetName, const LSFString& language = LSFString("en"));

    /**
     * Update an existing Preset. \n
     * Response in PresetManagerCallback::UpdatePresetReplyCB. \n
     * Return asynchronously the preset response code and unique id. \n
     *
     * @param presetID    The id of the Preset
     * @param preset The new state information
     */
    ControllerClientStatus UpdatePreset(const LSFString& presetID, const LampState& preset);

    /**
     * Delete a preset. \n
     * Return asynchronously the preset response code and unique id. \n
     * Response in PresetManagerCallback::DeletePresetReplyCB. \n
     *
     * @param presetID    The id of the Preset to delete
     */
    ControllerClientStatus DeletePreset(const LSFString& presetID);

    /**
     * Get the default Lamp State. \n
     * Return asynchronously the preset response code and lamp state which id is 'DefaultLampState'. \n
     * Response comes in LampManagerCallback::GetDefaultLampStateReplyCB. \n
     *
     * @return
     *      - CONTROLLER_CLIENT_OK if successful. \n
     *      - An error status otherwise. \n
     */
    ControllerClientStatus GetDefaultLampState(void);

    /**
     * Set the default state of new Lamps. \n
     * Response comes in LampManagerCallback::SetDefaultLampStateReplyCB. \n
     * Fill the preset with id 'DefaultLampState' new lamp state value. \n
     * Creating it if it is not already exists. In this case the name and the id are the same. \n
     * @param  defaultLampState The Lamp state
     * @return
     *      - CONTROLLER_CLIENT_OK if successful. \n
     *      - An error status otherwise. \n
     */
    ControllerClientStatus SetDefaultLampState(const LampState& defaultLampState);

    /**
     * Get the Preset Info and Name. \n
     * Combination of GetPreset and GetPresetName. \n
     *
     * @param presetID    The ID of the master preset
     * @param language
     */
    ControllerClientStatus GetPresetDataSet(const LSFString& presetID, const LSFString& language = LSFString("en"));

  private:

    // signal handlers
    void PresetsNameChanged(LSFStringList& idList) {
        callback.PresetsNameChangedCB(idList);
    }

    void PresetsCreated(LSFStringList& idList) {
        callback.PresetsCreatedCB(idList);
    }

    void PresetsUpdated(LSFStringList& idList) {
        callback.PresetsUpdatedCB(idList);
    }

    void PresetsDeleted(LSFStringList& idList) {
        callback.PresetsDeletedCB(idList);
    }

    /**
     * Handler for the signal DefaultLampStateChanged
     */
    void DefaultLampStateChanged(void) {
        callback.DefaultLampStateChangedCB();
    }

    // method reply handlers
    void GetAllPresetIDsReply(LSFResponseCode& responseCode, LSFStringList& idList) {
        callback.GetAllPresetIDsReplyCB(responseCode, idList);
    }

    void GetPresetReply(ajn::Message& message);

    void GetPresetNameReply(LSFResponseCode& responseCode, LSFString& lsfId, LSFString& language, LSFString& lsfName) {
        callback.GetPresetNameReplyCB(responseCode, lsfId, language, lsfName);
    }

    void SetPresetNameReply(LSFResponseCode& responseCode, LSFString& lsfId, LSFString& language) {
        callback.SetPresetNameReplyCB(responseCode, lsfId, language);
    }

    void CreatePresetReply(LSFResponseCode& responseCode, LSFString& lsfId) {
        callback.CreatePresetReplyCB(responseCode, lsfId);
    }

    void CreatePresetWithTrackingReply(LSFResponseCode& responseCode, LSFString& lsfId, uint32_t& trackingID) {
        callback.CreatePresetWithTrackingReplyCB(responseCode, lsfId, trackingID);
    }

    void UpdatePresetReply(LSFResponseCode& responseCode, LSFString& lsfId) {
        callback.UpdatePresetReplyCB(responseCode, lsfId);
    }

    void DeletePresetReply(LSFResponseCode& responseCode, LSFString& lsfId) {
        callback.DeletePresetReplyCB(responseCode, lsfId);
    }

    /**
     * Method Reply Handler for the signal GetDefaultLampState
     */
    void GetDefaultLampStateReply(ajn::Message& message);

    /**
     * Method Reply Handler for the signal GetDefaultLampState
     */
    void SetDefaultLampStateReply(uint32_t& responseCode) {
        callback.SetDefaultLampStateReplyCB((LSFResponseCode &)responseCode);
    }

    PresetManagerCallback& callback;
};

}

#endif
