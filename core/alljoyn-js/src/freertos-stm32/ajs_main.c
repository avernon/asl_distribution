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

#include "../ajs.h"
#include "../ajs_target.h"

extern uint8_t dbgMSG;
extern uint8_t dbgHELPER;
extern uint8_t dbgBUS;
extern uint8_t dbgABOUT;
extern uint8_t dbgINTROSPECT;
extern uint8_t dbgAJCPS;
extern uint8_t dbgAJS;
extern uint8_t dbgAJOBS;
extern uint8_t dbgHEAP;
extern uint8_t dbgDISCO;
extern uint8_t dbgCONNECT;
extern uint8_t dbgPEER;
extern uint8_t dbgAJSVC;

int AJ_Main()
{
    AJ_Status status;

#ifndef NDEBUG
    AJ_DbgLevel = AJ_DEBUG_DUMP;
    dbgMSG = 1;
    dbgHELPER = 1;
    dbgABOUT = 1;
    dbgBUS = 1;
    dbgINTROSPECT = 1;
    dbgAJCPS = 1;
    dbgAJS = 1;
    dbgAJOBS = 1;
    dbgCONNECT = 1;
    dbgDISCO = 1;
    dbgAJSVC = 1;
    dbgHEAP = 0;
    dbgPEER = 1;
#endif

    AJ_Initialize();

    /*
     * This is just for testing onboarding and config
     */
#ifdef NVRAM_CLEAR_ON_START
    AJ_NVRAM_Clear();
#endif

    while (1) {
        status = AJS_Main("STM32");
        if (status != AJ_ERR_RESTART) {
            AJ_Reboot();
        }
    }
}
