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
#include "../ajs_cmdline.h"


int main(int argc, char* argv[])
{
    AJ_Status status;
    AJS_CmdOptions options;

    if (AJS_CmdlineOptions(argc, argv, &options)) {
        goto Usage;
    }
    if (options.daemonize || options.logFile || options.nvramFile) {
        goto Usage;
    }

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
    AJ_Printf("Usage: %s [--debug] [--name <device-name>] [script_file]\n", argv[0]);
#else
    AJ_Printf("Usage: %s [--name <device-name>] [script_file]\n", argv[0]);
#endif
    exit(1);
}

