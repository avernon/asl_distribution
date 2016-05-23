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
#ifndef _PULSE_EFFECT_MANAGER_H_
#define _PULSE_EFFECT_MANAGER_H_
/**
 * \ingroup ControllerService
 */
/**
 * @file
 * This file provides definitions for pulse effect manager
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
#else
#include <Manager.h>
#endif

#include <Mutex.h>
#include <LSFTypes.h>

#include <string>
#include <map>
#include "LSFNamespaceSpecifier.h"

namespace lsf {

OPTIONAL_NAMESPACE_CONTROLLER_SERVICE

class LampGroupManager;
class SceneManager;
class SceneElementManager;
/**
 * class manages the pulse effect of the lamps. \n
 * pulse effect is the ability to save lamp states and to use them when required later on.
 */
class PulseEffectManager : public Manager {
    friend class LampManager;
    friend class SceneManager;
  public:
    /**
     * class constructor. \n
     * @param controllerSvc - reference to controller service instance
     * @param lampGroupMgrPtr - pointer to lamp group manager
     * @param sceneElementMgrPtr - pointer to sceneElement manager
     * @param pulseEffectFile - The full path of pulse effect file to be the persistent data
     */
    PulseEffectManager(ControllerService& controllerSvc, LampGroupManager* lampGroupMgrPtr, SceneElementManager* sceneElementMgrPtr, const std::string& pulseEffectFile);
    /**
     * Clears the pulseEffects data. \n
     * Send signal to the controller clients 'org.allseen.LSF.ControllerService.PulseEffect' 'PulseEffectsDeleted'. \n
     * @return LSF_OK on success. \n
     */
    LSFResponseCode Reset(void);
    /**
     * Get all pulse effect ids. \n
     * Return asynchronous all pulse effect ids which are not the default lamp state. \n
     * response code LSF_OK on success. \n
     */
    void GetAllPulseEffectIDs(ajn::Message& msg);
    /**
     * Get pulse effect name. \n
     * @param msg type Message with MsgArg unique id. \n
     * Return asynchronously the pulse effect name, id, language and response code. \n
     * response code LSF_OK on success. \n
     */
    void GetPulseEffectName(ajn::Message& msg);
    /**
     * Set pulse effect name. \n
     * @param msg type Message with MsgArg pulse effect unique id. \n
     * Return asynchronously the pulse effect new name, id, language and response code. \n
     * Send signal to the controller clients 'org.allseen.LSF.ControllerService.PulseEffect' 'PulseEffectsNameChanged'. \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_INVALID_ARGS - language not supported, name is too long. \n
     *      LSF_ERR_EMPTY_NAME - pulse effect name is empty. \n
     *      LSF_ERR_RESOURCES - blob is too big. \n
     */
    void SetPulseEffectName(ajn::Message& msg);
    /**
     * Create new pulseEffect. \n
     * @param msg type Message with MsgArgs: LampState, name, language. \n
     * Return asynchronously the pulse effect response code and auto generated unique id. \n
     * Send signal to the controller clients 'org.allseen.LSF.ControllerService.PulseEffect' 'PulseEffectsCreated'. \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_INVALID_ARGS - language not supported, name is too long. \n
     *      LSF_ERR_EMPTY_NAME - pulse effect name is empty. \n
     *      LSF_ERR_RESOURCES - blob is too big. \n
     *
     */
    void CreatePulseEffect(ajn::Message& msg);
    /**
     * Update existing pulseEffect. \n
     * @param msg type Message with MsgArgs: pulse effect id. \n
     * Return asynchronously the pulse effect response code and unique id. \n
     * Send signal to the controller clients 'org.allseen.LSF.ControllerService.PulseEffect' 'PulseEffectsUpdated'. \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_INVALID_ARGS - language not supported, name is too long. \n
     *      LSF_ERR_RESOURCES - blob is too big. \n
     */
    void UpdatePulseEffect(ajn::Message& msg);
    /**
     * Apply pulseEffect on Lamps. \n
     * @param msg type Message with MsgArgs: pulse effect id and list of lamp IDs. \n
     * Return asynchronously the response code and pulse effect id. \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_NOT_FOUND - pulse effect/lamp with requested id is not found. \n
     */
    void ApplyPulseEffectOnLamps(ajn::Message& msg);
    /**
     * Apply pulseEffect on Lamp Groups. \n
     * @param msg type Message with MsgArgs: pulse effect id and list of lamp group IDs. \n
     * Return asynchronously the response code and pulse effect id. \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_NOT_FOUND - pulse effect/lamp group with requested id is not found. \n
     */
    void ApplyPulseEffectOnLampGroups(ajn::Message& msg);
    /**
     * Delete existing pulseEffect. \n
     * @param msg type Message with MsgArgs: pulse effect id. \n
     * Return asynchronously the pulse effect response code and unique id. \n
     * Send signal to the controller clients 'org.allseen.LSF.ControllerService.PulseEffect' 'PulseEffectsDeleted'. \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_NOT_FOUND - pulse effect with requested id is not found. \n
     */
    void DeletePulseEffect(ajn::Message& msg);
    /**
     * Get existing pulseEffect. \n
     * @param msg type Message with MsgArgs: pulse effect id. \n
     * Return asynchronously the pulse effect response code, unique id and requested lamp state \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_NOT_FOUND - pulse effect with requested id is not found. \n
     */
    void GetPulseEffect(ajn::Message& msg);
    /**
     * Get existing pulseEffect. \n
     * @param pulseEffectID - The pulse effect unique id. \n
     * @param pulseEffect -   The pulse effect. \n
     * @return \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_NOT_FOUND - pulse effect with requested id is not found. \n
     */
    LSFResponseCode GetPulseEffectInternal(const LSFString& pulseEffectID, PulseEffect& pulseEffect);
    /**
     * Get all pulseEffects. \n
     * @param pulseEffectMap - the requested pulseEffects filled synchronously. \n
     * response code LSF_OK on success. \n
     */
    LSFResponseCode GetAllPulseEffects(PulseEffectMap& pulseEffectMap);
    /**
     * Read saved persistent data to cache
     */
    void ReadSavedData(void);
    /**
     * Write to cache persistent data
     */
    void ReadWriteFile(void);
    /**
     * Handle received blob. \n
     * Getting the blob string and wrting it to the file. \n
     */
    void HandleReceivedBlob(const std::string& blob, uint32_t checksum, uint64_t timestamp);
    /**
     * Handle Received Update Blob
     */
    void HandleReceivedUpdateBlob(const std::string& blob, uint32_t checksum, uint64_t timestamp);
    /**
     * Get Controller Service PulseEffect Interface Version. \n
     * @return 32 unsigned integer version. \n
     */
    uint32_t GetControllerServicePulseEffectInterfaceVersion(void);
    /**
     * Get the pulseEffects information as a string. \n
     * @return true if data is written to file
     */
    bool GetString(std::string& output, std::string& updates, uint32_t& checksum, uint64_t& timestamp, uint32_t& updatesChksum, uint64_t& updatesTs);
    /**
     * Get blob information about checksum and time stamp.
     */
    void GetBlobInfo(uint32_t& checksum, uint64_t& timestamp) {
        pulseEffectsLock.Lock();
        GetBlobInfoInternal(checksum, timestamp);
        pulseEffectsLock.Unlock();
    }
    /**
     * Get blob information about checksum and time stamp.
     */
    void GetUpdateBlobInfo(uint32_t& checksum, uint64_t& timestamp) {
        pulseEffectsLock.Lock();
        GetUpdateBlobInfoInternal(checksum, timestamp);
        pulseEffectsLock.Unlock();
    }

  private:

    void ReplaceMap(std::istringstream& stream);

    void ReplaceUpdatesList(std::istringstream& stream);

    LSFResponseCode CreatePulseEffectInternal(PulseEffect& pulseEffect, LSFString& name, LSFString& language, LSFString& pulseEffectID);

    LSFResponseCode DeletePulseEffectInternal(LSFString& pulseEffectID);

    void SendPulseEffectsCreatedSignal(LSFStringList& pulseEffectIds);

    PulseEffectMap pulseEffects;
    std::set<LSFString> pulseEffectUpdates;    /**< List of PulseEffectIDs that were updated */
    Mutex pulseEffectsLock;
    LampGroupManager* lampGroupManagerPtr;
    SceneElementManager* sceneElementManagerPtr;
    size_t blobLength;

    std::string GetString(const PulseEffectMap& items);
    std::string GetUpdatesString(const std::set<LSFString>& updates);
    std::string GetString(const std::string& name, const std::string& id, const PulseEffect& pulseEffect);
};

OPTIONAL_NAMESPACE_CLOSE

} //lsf


#endif
