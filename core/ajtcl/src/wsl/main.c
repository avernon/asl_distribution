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

#include <ajtcl/aj_target_platform.h>
#include <ajtcl/aj_target.h>
#include <ajtcl/aj_debug.h>
#include <ajtcl/aj_target_rtos.h>

static void main_task(void* parameters)
{
    AJ_PlatformInit();
    AJ_AlwaysPrintf((" ==============================================\n"));
    AJ_AlwaysPrintf(("||       Alljoyn Thin Client + FreeRTOS       ||\n"));
    AJ_AlwaysPrintf((" ==============================================\n"));
    AllJoyn_Start(0);
    while (1);
}

int main(void)
{
    AJ_CreateTask(main_task, (const signed char*)"AlljoynTask", AJ_WSL_STACK_SIZE, NULL, 2, NULL);
    AJ_StartScheduler();
    return 0;
}

