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

#ifndef AJS_CONSOLE_C_H_
#define AJS_CONSOLE_C_H_

#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include "ajs_console_common.h"

/**
 * Register any desired handler functions
 *
 * @param ctx       Console context
 * @param handlers  List of functions to be registered (any element can be NULL)
 */
void AJS_ConsoleRegisterSignalHandlers(AJS_ConsoleCtx* ctx, SignalRegistration* handlers);

/**
 * Set the verbose level for the console
 *
 * @param ctx           Console context
 * @param verbose       Set verbose on or off
 */
void AJS_ConsoleSetVerbose(AJS_ConsoleCtx* ctx, uint8_t verbose);

/**
 * Initialize the console. This must be called before any other
 * console/debug commands.
 *
 * @return              Context pointer needed for any subsequent console/debug commands
 */
AJS_ConsoleCtx* AJS_ConsoleInit(void);

/**
 * De-initialize the console
 *
 * @param ctx           Console context pointer
 */
void AJS_ConsoleDeinit(AJS_ConsoleCtx* ctx);

/**
 * Connect the console to an AllJoyn.js target
 *
 * @param ctx           Console context
 * @param deviceName    Name of the device your connecting to (can be NULL)
 * @param interrupt     Interrupt pointer (sigint handler, can be NULL)
 * @return              1 on success, 0 on failure
 */
int AJS_ConsoleConnect(AJS_ConsoleCtx* ctx, const char* deviceName, volatile sig_atomic_t* interrupt);

/**
 * Eval a JavaScript string
 *
 * @param ctx           Console context
 * @param script        Eval string
 * @return              Result of AJSConsole.Eval()
 */
int8_t AJS_ConsoleEval(AJS_ConsoleCtx* ctx, const char* script);

/**
 * Signal the AllJoyn.js target to reboot
 *
 * @param ctx           Console context
 * @return              1 on success, 0 on failure
 */
int AJS_ConsoleReboot(AJS_ConsoleCtx* ctx);

/**
 * Install a script
 *
 * @param ctx           Console context
 * @param name          Device name
 * @param script        Pointer to the script to be installed
 * @param len           Byte length of the script
 * @return              1 on success, 0 on failure.
 */
int AJS_ConsoleInstall(AJS_ConsoleCtx* ctx, const char* name, const uint8_t* script, size_t len);

#endif /* AJS_CONSOLE_C_H_ */
