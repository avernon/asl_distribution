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
#ifndef _LAMP_ABOUT_DATA_H_
#define _LAMP_ABOUT_DATA_H_
/**
 * @file LampAboutData.h
 * @defgroup lamp_about About/Config PropertyStore used by the Lamp Service
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

#include <aj_status.h>
#include <aj_msg.h>
#include <aj_debug.h>

/**
 * Set up the About and Config Service data structures
 *
 * @param   None
 * @return  None
 */
void LAMP_SetupAboutConfigData(void);

/**
 * Callback to set the AllJoyn password
 *
 * @param buffer    The password buffer
 * @param bufLen    The buffer length
 * @return          The length of the password written to buffer
 */
uint32_t LAMP_PasswordCallback(uint8_t* buffer, uint32_t bufLen);


/**
 * Get the Lamp ID.  If the ID does not yet exist,
 * generate and persist it before returning it.
 *
 * @param   None
 * @return  The Lamp ID
 */
const char* LAMP_GetID(void);

/**
 * Get the Lamp Name
 *
 * @param   None
 * @return  The Lamp name
 */
const char* LAMP_GetName(void);

/**
 * Set the Lamp Name
 *
 * @param name  The Lamp name
 * @return      None
 */
void LAMP_SetName(const char* name);

/**
 * @}
 */
#endif
