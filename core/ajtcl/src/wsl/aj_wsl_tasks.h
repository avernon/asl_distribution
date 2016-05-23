/**
 * @file Function declarations for tasks
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

#ifndef AJ_WSL_TASKS_H_
#define AJ_WSL_TASKS_H_

#include <ajtcl/aj_target.h>
#include <ajtcl/aj_status.h>

#include "aj_wsl_target.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This file contains the task and structure definitions for the WSL "driver" code
 *
 */

AJ_EXPORT void AJ_WSL_MBoxListenAndProcessTask(void* parameters);

#ifdef __cplusplus
}
#endif

#endif /* AJ_WSL_TASKS_H_ */
