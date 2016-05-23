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
#ifndef _LAMP_MANAGER_H_
#define _LAMP_MANAGER_H_
/**
 * \ingroup ControllerService
 */
/**
 * @file
 * This file provides definitions for lamp manager
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
#include <lsf/controllerservice/PresetManager.h>
#include <lsf/controllerservice/LampClients.h>
#else
#include <Manager.h>
#include <PresetManager.h>
#include <LampClients.h>
#endif

#include <Mutex.h>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "LSFNamespaceSpecifier.h"

namespace lsf {

OPTIONAL_NAMESPACE_CONTROLLER_SERVICE

/**
 * Lamps and state details
 */
class LampsAndState {
  public:
    /**
     * LampsAndState constructor
     */
    LampsAndState(LSFStringList lampList, LampState lampState, uint32_t period) :
        state(lampState), transitionPeriod(period) {
        for (LSFStringList::iterator it = lampList.begin(); it != lampList.end(); it++) {
            LSFString uniqueId = *it;
            if (std::find(lamps.begin(), lamps.end(), uniqueId) == lamps.end()) {
                lamps.push_back(uniqueId);
            }
        }
    }
    LSFStringList lamps;         /**< list of lamps */
    LampState state;         /**< state of lamps */
    uint32_t transitionPeriod;         /**< transition period */
};
/**
 * lamps and present details
 */
class LampsAndPreset {
  public:
    /**
     * LampsAndPreset constructor
     */
    LampsAndPreset(LSFStringList lampList, LSFString presetID, uint32_t period) :
        lamps(lampList), presetID(presetID), transitionPeriod(period) { }

    LSFStringList lamps;         /**< list of lamps */
    LSFString presetID;         /**< present ID */
    uint32_t transitionPeriod;         /**< transition period */
};
/**
 * a class that contains a list of lamps and the new state wanted for them.
 */
class LampsAndStateField {
  public:
    /**
     * LampsAndStateField constructor
     */
    LampsAndStateField(LSFStringList lampList, LSFString fieldName, ajn::MsgArg arg, uint32_t period) :
        lamps(lampList), stateFieldName(fieldName), stateFieldValue(arg), transitionPeriod(period) { }

    LSFStringList lamps;         /**< list of lamps */
    LSFString stateFieldName;         /**< state field name */
    ajn::MsgArg stateFieldValue;         /**< state field value */
    uint32_t transitionPeriod;         /**< transition period */
};
/**
 * pulse lamp details
 */
class PulseLampsWithState {
  public:
    /**
     * pulse lamps with state constructor
     */
    PulseLampsWithState(LSFStringList lampList, LampState fromLampState, LampState toLampState, uint32_t period, uint32_t duration, uint32_t numPulses) :
        lamps(lampList), fromState(fromLampState), toState(toLampState), period(period), duration(duration), numPulses(numPulses) { }

    LSFStringList lamps;         /**< list of lamps */
    LampState fromState;         /**< from state */
    LampState toState;         /**< to state */
    uint32_t period;         /**< period of time */
    uint32_t duration;         /**< duration of time */
    uint32_t numPulses;         /**< number of pulses */
};
/**
 * pulse lamps details
 */
class PulseLampsWithPreset {
  public:
    /**
     * PulseLampsWithPreset constructor
     */
    PulseLampsWithPreset(LSFStringList lampList, LSFString fromPreset, LSFString toPreset, uint32_t period, uint32_t duration, uint32_t numPulses) :
        lamps(lampList), fromPreset(fromPreset), toPreset(toPreset), period(period), duration(duration), numPulses(numPulses) { }

    LSFStringList lamps;         /**< list of lamps */
    LSFString fromPreset;         /**< from present */
    LSFString toPreset;         /**< to present */
    uint32_t period;         /**< period of time */
    uint32_t duration;         /**< duration of time */
    uint32_t numPulses;         /**< number of pulses */
};

typedef std::list<LampsAndState> LampsAndStateList;
typedef std::list<LampsAndPreset> LampsAndPresetList;
typedef std::list<LampsAndStateField> LampsAndStateFieldList;
typedef std::list<PulseLampsWithState> PulseLampsWithStateList;
typedef std::list<PulseLampsWithPreset> PulseLampsWithPresetList;
/**
 * lamp management class
 */
class LampManager : public Manager {
  public:
    friend class LampGroupManager;
    /**
     * LampManager constructor
     */
    LampManager(ControllerService& controllerSvc, PresetManager& presetMgr);
    /**
     * Lamp manager destructor
     */
    ~LampManager();

    /**
     * Start the Lamp Manager
     *
     * @param   keyStoreFileLocation
     * @return  ER_OK if successful, error otherwise
     */
    QStatus Start(const char* keyStoreFileLocation);

    /**
     * Stop the Lamp Manager
     *
     * @return  ER_OK if successful, error otherwise
     */
    void Stop(void);
    /**
     * join thread
     */
    void Join(void);

    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.GetAllLampIDs
     *
     * @param message   The params
     */
    void GetAllLampIDs(ajn::Message& message);
    /**
     * Get all lamps
     */
    void GetAllLamps(LampNameMap& lamps) {
        lampClients.GetAllLamps(lamps);
    }

    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.GetLampFaults
     *
     * @param message   The params
     */
    void GetLampFaults(ajn::Message& message);

    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.GetLampServiceVersion
     *
     * @param message   The params
     */
    void GetLampServiceVersion(ajn::Message& message);


    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.ClearLampFault
     *
     * @param message   The params
     */
    void ClearLampFault(ajn::Message& message);

    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.GetLampSupportedLanguages
     *
     * @param message   The params
     */
    void GetLampSupportedLanguages(ajn::Message& message);

    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.GetLampManufacturer
     *
     * @param message   The params
     */
    void GetLampManufacturer(ajn::Message& message);

    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.GetLampName
     *
     * @param message   The params
     */
    void GetLampName(ajn::Message& message);

    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.SetLampName
     * @param message   The params
     */
    void SetLampName(ajn::Message& message);

    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.GetLampDetails
     *
     * @param message   The params
     */
    void GetLampDetails(ajn::Message& message);

    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.GetLampParameters
     *
     * @param message   The params
     */
    void GetLampParameters(ajn::Message& message);

    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.GetLampParametersField
     *
     * @param message   The params
     */
    void GetLampParametersField(ajn::Message& message);

    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.GetLampState
     *
     * @param message   The params
     */
    void GetLampState(ajn::Message& message);

    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.GetLampStateField
     *
     * @param message   The params
     */
    void GetLampStateField(ajn::Message& message);

    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.TransitionLampState
     *
     * @param message   The params
     */
    void TransitionLampState(ajn::Message& message);

    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.PulseLampWithState
     *
     * @param message   The params
     */
    void PulseLampWithState(ajn::Message& message);

    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.PulseLampWithPreset
     *
     * @param message   The params
     */
    void PulseLampWithPreset(ajn::Message& message);

    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.TransitionLampStateToPreset
     *
     * @param message   The params
     */
    void TransitionLampStateToPreset(ajn::Message& message);

    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.TransitionLampStateField
     *
     * @param message   The params
     */
    void TransitionLampStateField(ajn::Message& message);

    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.ResetLampState
     *
     * @param message   The params
     */
    void ResetLampState(ajn::Message& message);

    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.ResetLampStateField
     *
     * @param message   The params
     */
    void ResetLampStateField(ajn::Message& message);

    /**
     * Process an AllJoyn call to org.allseen.LSF.ControllerService.DataSet.GetLampDataSet
     *
     * @param message   The params
     */
    void GetLampDataSet(ajn::Message& message);

    /**
     * Get interface version
     */
    uint32_t GetControllerServiceLampInterfaceVersion(void);
    /**
     * Get data set interface version
     */
    uint32_t GetControllerServiceDataSetInterfaceVersion(void);
    /**
     * connect to lamps
     */
    void ConnectToLamps(void) {
        lampClients.ConnectToLamps();
    }
    /**
     * Disconnect from lamps
     */
    void DisconnectFromLamps(void) {
        lampClients.DisconnectFromLamps();
    }

  private:

    void ResetLampStateInternal(ajn::Message& message, LSFStringList lamps, bool groupOperation = false, bool allLamps = false);

    void ResetLampStateFieldInternal(ajn::Message& message, LSFStringList lamps, LSFString stateFieldName, bool groupOperation = false, bool allLamps = false);

    void ChangeLampStateAndField(ajn::Message& message,
                                 LampsAndStateList& transitionToStateComponent,
                                 LampsAndPresetList& transitionToPresetComponent,
                                 LampsAndStateFieldList& stateFieldComponent,
                                 PulseLampsWithStateList& pulseWithStateComponent,
                                 PulseLampsWithPresetList& pulseWithPresetComponent,
                                 bool groupOperation = false,
                                 bool allLamps = false,
                                 bool sceneOperation = false,
                                 LSFString sceneOrMasterSceneId = LSFString(),
                                 bool effectOperation = false);

    LampClients lampClients;
    PresetManager& presetManager;

};

OPTIONAL_NAMESPACE_CLOSE

} //lsf

#endif
