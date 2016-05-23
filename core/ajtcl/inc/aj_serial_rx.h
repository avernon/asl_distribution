#ifndef _AJ_SERIAL_RX_H
#define _AJ_SERIAL_RX_H

/**
 * @file
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
#ifdef AJ_SERIAL_CONNECTION

#include <ajtcl/aj_target.h>
#include <ajtcl/aj_status.h>
#include <ajtcl/aj_serial.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This function initializes the receive path
 */
AJ_Status AJ_SerialRX_Init(void);

/**
 * This function shuts down the receive path
 */
void AJ_SerialRX_Shutdown(void);

/**
 * This function resets the receive path
 */
AJ_Status AJ_SerialRX_Reset(void);

/**
 * Process the buffers read by the Receive callback - called by the StateMachine.
 */
void AJ_ProcessRxBufferList();

#ifdef __cplusplus
}
#endif

#endif /* AJ_SERIAL_CONNECTION */

#endif /* _AJ_SERIAL_RX_H */
