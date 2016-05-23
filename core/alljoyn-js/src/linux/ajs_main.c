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


int main(int argc, char* argv[])
{
    AJ_Status status;
    AJS_CmdOptions options;

    if (AJS_CmdlineOptions(argc, argv, &options)) {
        goto Usage;
    }
    if (options.daemonize || options.logFile) {
        goto Usage;
    }
    return status;
}

#ifndef NDEBUG
extern uint8_t dbgMSG;
extern uint8_t dbgHELPER;
extern uint8_t dbgBUS;
extern uint8_t dbgABOUT;
extern uint8_t dbgINTROSPECT;
extern uint8_t dbgAJCPS;
extern uint8_t dbgAJS;
extern uint8_t dbgHEAP;
extern uint8_t dbgNET;
extern uint8_t dbgHEAPDUMP;
extern uint8_t dbgCONSOLE;
extern uint8_t dbgGPIO;
#endif

int main(int argc, char* argv[])
{
    const char* deviceName = NULL;
    const char* scriptName = NULL;
    int argn = 1;
    AJ_Status status = AJ_OK;
#ifndef NDEBUG
    AJ_DbgLevel = 2;
    dbgMSG = 0;
    dbgHELPER = 0;
    dbgABOUT = 0;
    dbgBUS = 0;
    dbgINTROSPECT = 0;
    dbgAJCPS = 0;
    dbgAJS = 0;
    dbgHEAP = 0;
    dbgNET = 0;
    dbgHEAPDUMP = 0;
    dbgCONSOLE = 0;
    dbgGPIO = 0;
#endif

    AJ_SetNVRAM_FilePath(options.nvramFile);
    AJ_Initialize();

    if (options.scriptName) {
        status = AJS_InstallScript(options.scriptName);
        if (status != AJ_OK) {
            AJ_Printf("Failed to install script %s\n", options.scriptName);
            exit(1);
        }
    }

    do {
        status = AJS_Main(options.deviceName);
    } while (status == AJ_ERR_RESTART);

    return (int)status;

Usage:

#ifndef NDEBUG
    AJ_Printf("Usage: %s [--debug] [--name <device-name>] [--nvram-file <nvram-file>] [script_file]\n", argv[0]);
#else
    AJ_Printf("Usage: %s [--name <device-name>] [--nvram-file <nvram-file>] [script_file]\n", argv[0]);
#endif
    exit(1);
}

