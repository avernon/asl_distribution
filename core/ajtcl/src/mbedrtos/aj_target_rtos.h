/**
 * @file   RTOS specific header file
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

#ifndef AJ_TARGET_RTOS_H_
#define AJ_TARGET_RTOS_H_

#include <ajtcl/aj_target.h>
#include <ajtcl/aj_status.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _AJ_FW_Version {
    uint32_t host_ver;
    uint32_t target_ver;
    uint32_t wlan_ver;
    uint32_t abi_ver;
} AJ_FW_Version;

/**
 * Enter a critical region of code. This function will disable all interrupts
 * until AJ_LeaveCriticalRegion() is called
 */
void AJ_EnterCriticalRegion(void);

/**
 * Leave a critical region of code. This function re-enables interrupts after
 * calling AJ_EnterCriticalRegion()
 */
void AJ_LeaveCriticalRegion(void);

/**
 * Generate an ephemeral (random) port.
 *
 * @return              A random port number
 */
uint16_t AJ_EphemeralPort(void);

/**
 * Initialize the platform. This function contains initialization such
 * as GPIO, Clock, UART etc.
 */
void AJ_PlatformInit(void);

#ifdef __cplusplus
}
#endif

#endif /* AJ_TARGET_RTOS_H_ */
