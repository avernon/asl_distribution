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
#define AJ_MODULE TEST

#include "alljoyn.h"
#include "aj_debug.h"
/**
 * 5 means AJ_DEBUG_ALL
 * However, if AJ_DbgLevel in aj_debug.c is set to AJ_DEBUG_ERROR,
 * only error messages are printed.
 * To print info messages, AJ_DbgLevel need to be AJ_DEBUG_INFO/AJ_DEBUG_ALL and
 * AJ_DEBUG_RESTRICT needs to be AJ_DEBUG_INFO/AJ_DEBUG_ALL
 */
uint8_t dbgTEST = 5;

int AJ_Main()
{
    AJ_Status status = AJ_OK;
    AJ_ErrPrintf(("Got error status %s\n", AJ_StatusText(status)));
    AJ_ErrPrintf(("Error print\n"));
    AJ_WarnPrintf(("Got warn status %s\n", AJ_StatusText(status)));
    AJ_WarnPrintf(("Warn print\n"));
    AJ_InfoPrintf(("Got info status %s\n", AJ_StatusText(status)));
    AJ_InfoPrintf(("Info print\n"));

    return 0;
}

#ifdef AJ_MAIN
int main()
{
    return AJ_Main();
}
#endif
