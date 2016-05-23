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
#ifndef _TRANSITION_EFFECT_MANAGER_H_
#define _TRANSITION_EFFECT_MANAGER_H_
/**
 * \ingroup ControllerService
 */
/**
 * @file
 * This file provides definitions for transition effect manager
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
 * class manages the transition effect of the lamps. \n
 * transition effect is the ability to save lamp states and to use them when required later on.
 */
class TransitionEffectManager : public Manager {
    friend class SceneManager;
  public:
    /**
     * class constructor. \n
     * @param controllerSvc - reference to controller service instance
     * @param lampGroupMgrPtr - pointer to lamp group manager
     * @param sceneElementMgrPtr - pointer to sceneElement manager
     * @param transitionEffectFile - The full path of transition effect file to be the persistent data
     */
    TransitionEffectManager(ControllerService& controllerSvc, LampGroupManager* lampGroupMgrPtr, SceneElementManager* sceneElementMgrPtr, const std::string& transitionEffectFile);
    /**
     * Clears the transitionEffects data. \n
     * Send signal to the controller clients 'org.allseen.LSF.ControllerService.TransitionEffect' 'TransitionEffectsDeleted'. \n
     * @return LSF_OK on success. \n
     */
    LSFResponseCode Reset(void);
    /**
     * Get all transition effect ids. \n
     * Return asynchronous all transition effect ids which are not the default lamp state. \n
     * response code LSF_OK on success. \n
     */
    void GetAllTransitionEffectIDs(ajn::Message& msg);
    /**
     * Get transition effect name. \n
     * @param msg type Message with MsgArg unique id. \n
     * Return asynchronously the transition effect name, id, language and response code. \n
     * response code LSF_OK on success. \n
     */
    void GetTransitionEffectName(ajn::Message& msg);
    /**
     * Set transition effect name. \n
     * @param msg type Message with MsgArg transition effect unique id. \n
     * Return asynchronously the transition effect new name, id, language and response code. \n
     * Send signal to the controller clients 'org.allseen.LSF.ControllerService.TransitionEffect' 'TransitionEffectsNameChanged'. \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_INVALID_ARGS - language not supported, name is too long. \n
     *      LSF_ERR_EMPTY_NAME - transition effect name is empty. \n
     *      LSF_ERR_RESOURCES - blob is too big. \n
     */
    void SetTransitionEffectName(ajn::Message& msg);
    /**
     * Create new transitionEffect. \n
     * @param msg type Message with MsgArgs: LampState, name, language. \n
     * Return asynchronously the transition effect response code and auto generated unique id. \n
     * Send signal to the controller clients 'org.allseen.LSF.ControllerService.TransitionEffect' 'TransitionEffectsCreated'. \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_INVALID_ARGS - language not supported, name is too long. \n
     *      LSF_ERR_EMPTY_NAME - transition effect name is empty. \n
     *      LSF_ERR_RESOURCES - blob is too big. \n
     *
     */
    void CreateTransitionEffect(ajn::Message& msg);
    /**
     * Update existing transitionEffect. \n
     * @param msg type Message with MsgArgs: transition effect id. \n
     * Return asynchronously the transition effect response code and unique id. \n
     * Send signal to the controller clients 'org.allseen.LSF.ControllerService.TransitionEffect' 'TransitionEffectsUpdated'. \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_INVALID_ARGS - language not supported, name is too long. \n
     *      LSF_ERR_RESOURCES - blob is too big. \n
     */
    void UpdateTransitionEffect(ajn::Message& msg);
    /**
     * Apply transitionEffect on Lamps. \n
     * @param msg type Message with MsgArgs: transition effect id and list of lamp IDs. \n
     * Return asynchronously the response code and transition effect id. \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_NOT_FOUND - transition effect/lamp with requested id is not found. \n
     */
    void ApplyTransitionEffectOnLamps(ajn::Message& msg);
    /**
     * Apply transitionEffect on Lamp Groups. \n
     * @param msg type Message with MsgArgs: transition effect id and list of lamp group IDs. \n
     * Return asynchronously the response code and transition effect id. \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_NOT_FOUND - transition effect/lamp group with requested id is not found. \n
     */
    void ApplyTransitionEffectOnLampGroups(ajn::Message& msg);
    /**
     * Delete existing transitionEffect. \n
     * @param msg type Message with MsgArgs: transition effect id. \n
     * Return asynchronously the transition effect response code and unique id. \n
     * Send signal to the controller clients 'org.allseen.LSF.ControllerService.TransitionEffect' 'TransitionEffectsDeleted'. \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_NOT_FOUND - transition effect with requested id is not found. \n
     */
    void DeleteTransitionEffect(ajn::Message& msg);
    /**
     * Get existing transitionEffect. \n
     * @param msg type Message with MsgArgs: transition effect id. \n
     * Return asynchronously the transition effect response code, unique id and requested lamp state \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_NOT_FOUND - transition effect with requested id is not found. \n
     */
    void GetTransitionEffect(ajn::Message& msg);
    /**
     * Get existing transitionEffect. \n
     * @param transitionEffectID - The transition effect unique id. \n
     * @param transitionEffect -   The requested transition effect. \n
     * @return \n
     * response code LSF_OK on success. \n
     *      LSF_ERR_NOT_FOUND - transition effect with requested id is not found. \n
     */
    LSFResponseCode GetTransitionEffectInternal(const LSFString& transitionEffectID, TransitionEffect& transitionEffect);
    /**
     * Get all transitionEffects. \n
     * @param transitionEffectMap - the requested transitionEffects filled synchronously. \n
     * response code LSF_OK on success. \n
     */
    LSFResponseCode GetAllTransitionEffects(TransitionEffectMap& transitionEffectMap);
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
     * Get Controller Service TransitionEffect Interface Version. \n
     * @return 32 unsigned integer version. \n
     */
    uint32_t GetControllerServiceTransitionEffectInterfaceVersion(void);
    /**
     * Get the transitionEffects information as a string. \n
     * @return true if data is written to file
     */
    bool GetString(std::string& output, std::string& updates, uint32_t& checksum, uint64_t& timestamp, uint32_t& updatesChksum, uint64_t& updatesTs);
    /**
     * Get blob information about checksum and time stamp.
     */
    void GetBlobInfo(uint32_t& checksum, uint64_t& timestamp) {
        transitionEffectsLock.Lock();
        GetBlobInfoInternal(checksum, timestamp);
        transitionEffectsLock.Unlock();
    }
    /**
     * Get blob information about checksum and time stamp.
     */
    void GetUpdateBlobInfo(uint32_t& checksum, uint64_t& timestamp) {
        transitionEffectsLock.Lock();
        GetUpdateBlobInfoInternal(checksum, timestamp);
        transitionEffectsLock.Unlock();
    }

  private:

    void ReplaceMap(std::istringstream& stream);

    void ReplaceUpdatesList(std::istringstream& stream);

    LSFResponseCode CreateTransitionEffectInternal(TransitionEffect& transitionEffect, LSFString& name, LSFString& language, LSFString& transitionEffectID);

    LSFResponseCode DeleteTransitionEffectInternal(LSFString& transitionEffectID);

    void SendTransitionEffectsCreatedSignal(LSFStringList& transitionEffectIds);

    TransitionEffectMap transitionEffects;
    std::set<LSFString> transitionEffectUpdates;    /**< List of TransitionEffectIDs that were updated */
    Mutex transitionEffectsLock;
    LampGroupManager* lampGroupManagerPtr;
    SceneElementManager* sceneElementManagerPtr;
    size_t blobLength;

    std::string GetString(const TransitionEffectMap& items);
    std::string GetUpdatesString(const std::set<LSFString>& updates);
    std::string GetString(const std::string& name, const std::string& id, const TransitionEffect& transitionEffect);
};

OPTIONAL_NAMESPACE_CLOSE

} //lsf


#endif
