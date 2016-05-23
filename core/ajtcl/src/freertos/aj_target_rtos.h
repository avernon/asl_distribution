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

/******************************************************************************
 * Any time in this file there is a comment including FreeRTOS or calling a
 * FreeRTOS API, note that the API associated with it may be subject to the
 * FreeRTOS GPL with exception license copied here:
 * http://www.freertos.org/license.txt :

 * The FreeRTOS.org source code is licensed by the modified GNU General Public
 * License (GPL) text provided below.  The FreeRTOS download also includes
 * demo application source code, some of which is provided by third parties
 * AND IS LICENSED SEPARATELY FROM FREERTOS.ORG.
 * For the avoidance of any doubt refer to the comment included at the top
 * of each source and header file for license and copyright information.
 ******************************************************************************/

#ifndef AJ_TARGET_RTOS_H_
#define AJ_TARGET_RTOS_H_

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>
#include <semphr.h>

#include "aj_rtos.h"

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
 * This function is called when freeRTOS fails to allocate
 */
void vApplicationMallocFailedHook(void);

/**
 * This function is called when a tasks stack overflows
 *
 * @param pxTask        Task handle of the task thats stack overflowed
 * @param pcTaskName    Name of the task
 */
void vApplicationStackOverflowHook(xTaskHandle pxTask, signed char*pcTaskName);

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

/**
 * Resume a task that has been previously started
 *
 * @param handle        The task handle (returned from AJ_CreateTask())
 * @param inISR         If the calling function is in an interrupt routine
 *
 * @return              AJ_OK if the task was resumed sucessfully
 */
AJ_Status AJ_ResumeTask(struct AJ_TaskHandle* handle, uint8_t inISR);

#ifdef __cplusplus
}
#endif

#endif /* AJ_TARGET_RTOS_H_ */
