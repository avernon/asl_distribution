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
#ifndef _LAMP_STATE_H_
#define _LAMP_STATE_H_
/**
 * @file LampState.h
 * @defgroup lamp_state The Lamp State related APIs used by the Lamp Service
 * @{
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

#include <alljoyn.h>

#include <LampResponseCodes.h>

/**
 * Struct LampState.
 * This is used to store the various lamp state fields.
 */
typedef struct _LampState {
    uint32_t hue;           /**< The lamp hue (in degree). 0 means 0. uint32_max-1 means 360. */
    uint32_t saturation;    /**< The lamp saturation (in percentage). 0 means 0. uint32_max-1 means 100. */
    uint32_t colorTemp;     /**< The lamp color temperature (in Kevin). 0 means 1000K. uint32_max-1 means 20000K. OEM implementation will need to take care of the scaling. */
    uint32_t brightness;    /**< The lamp brightness (in percentage). 0 means 0. uint32_max-1 means 100. */
    uint8_t onOff;          /**< Is the lamp on or off */
} LampState;

/**
 * Used to determine if OnOff field is present in the un-marshalled Lamp State.
 */
#define LAMP_STATE_ON_OFF_FIELD_INDICATOR     0x01

/**
 * Used to determine if Hue field is present in the un-marshalled Lamp State.
 */
#define LAMP_STATE_HUE_FIELD_INDICATOR        0x02

/**
 * Used to determine if Saturation field is present in the un-marshalled Lamp State.
 */
#define LAMP_STATE_SATURATION_FIELD_INDICATOR 0x04

/**
 * Used to determine if Color Temp field is present in the un-marshalled Lamp State.
 */
#define LAMP_STATE_COLOR_TEMP_FIELD_INDICATOR 0x08

/**
 * Used to determine if Brightness field is present in the un-marshalled Lamp State.
 */
#define LAMP_STATE_BRIGHTNESS_FIELD_INDICATOR 0x10

/**
 * Used to determine if all fields are present in the un-marshalled Lamp State.
 */
#define LAMP_STATE_ALL_FIELDS_INDICATOR       0x1F

/**
 * Struct LampStateContainer.
 * This is used to store the lamp state and indicate which of the
 * fields have valid values.
 */
typedef struct _LampStateContainer {
    LampState state;                  /**< The lamp state. */
    uint8_t stateFieldIndicators;     /**< Indicates which state fields have valid values. */
} LampStateContainer;

/**
 * Unmarshal the LampState fields from a message
 *
 * @param[out] state The lamp state container to read into
 * @param[in]  msg   The message to read from
 * @return Status of the operation
 */
LampResponseCode LAMP_UnmarshalState(LampStateContainer* state, AJ_Message* msg);

/**
 * Serialize the Lamp's current state
 *
 * @param state The state to marshal
 * @param msg   The msg to serialize data into
 * @return Status of the operation
 */
LampResponseCode LAMP_MarshalState(LampState* state, AJ_Message* msg);

/**
 * Initialize the LampState by reading it from NVRAM
 *
 * @param None
 * @param None
 */
void LAMP_InitializeState(void);

/**
 * Get the current LampState
 *
 * @param[out] state    A pointer to a LampState object
 */
void LAMP_GetState(LampState* state);

/**
 * Set the lamp state and save it in NVRAM.
 *
 * @param[in] state The new state
 */
void LAMP_SetState(const LampState* state);

/**
 * Clear the lamp state
 *
 * @param None
 * @param None
 */
void LAMP_ClearState(void);

/**
 * @}
 */
#endif
