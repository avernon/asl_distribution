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
#ifndef _LAMP_SERVICE_H_
#define _LAMP_SERVICE_H_
/**
 * @file LampService.h
 * @defgroup lamp_service The AllJoyn Lamp Service APIs
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

/**
 * Run the lamp service with no callback.
 * This is useful if you want to run the lamp service from its own thread
 *
 * @param None
 * @return None
 */
void LAMP_RunService(void);

/**
 * Typedef for the LSF callback
 *
 * @param  None
 * @return None
 */
typedef void (*LampServiceCallback)(void);

/**
 * Get the LSF version
 *
 * @param   None
 * @return  The version
 */
uint32_t LAMP_GetServiceVersion(void);

/**
 * Run the Lamp Service with a callback that occurs after
 * we time out waiting for a message.  Use this if you want to run
 * OEM-specific code on the same thread as the AllJoyn event loop
 *
 * @param timeout   The timeout (in ms)
 * @param callback  The callback function
 * @return          None
 */
void LAMP_RunServiceWithCallback(uint32_t timeout, LampServiceCallback callback);

/**
 * Schedule the signal org.allseen.LSF.LampService.LampStateChanged to be sent ASAP.
 * We call this every time the Lamp State is changed and written to NVRAM.
 *
 * @param  None
 * @return None
 */
void LAMP_SendStateChangedSignal(void);

/**
 * Call this method to indicate that some fault has occurred
 * in the Lamp
 *
 * @param  None
 * @return None
 */
void LAMP_SetFaults(void);

/**
 * This function must be called when all faults are cleared
 * in order to clear the Faults notification.
 *
 * @param  None
 * @return None
 */
void LAMP_ClearFaults(void);

/**
 * @}
 */
#endif
