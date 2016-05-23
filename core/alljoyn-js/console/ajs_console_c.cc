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

#include <alljoyn/Init.h>
#include "ajs_console_common.h"
#include "ajs_console.h"

extern "C" {

AJS_ConsoleCtx* AJS_ConsoleInit(void)
{
    AJS_ConsoleCtx* ctx = (AJS_ConsoleCtx*)malloc(sizeof(AJS_ConsoleCtx));
    if (ctx) {
        AllJoynInit();
        AllJoynRouterInit();
        AJS_Console* console = new AJS_Console;
        if (console) {
            ctx->console = (void*)console;
            ctx->version = NULL;
            console->handlers = (SignalRegistration*)malloc(sizeof(SignalRegistration));
            if (!console->handlers) {
                free(ctx);
                return NULL;
            }
            memset(console->handlers, 0, sizeof(SignalRegistration));
        } else {
            free(ctx);
            ctx = NULL;
        }
    }
    return ctx;
}

void AJS_ConsoleDeinit(AJS_ConsoleCtx* ctx)
{
    if (ctx) {
        if (ctx->console) {
            delete static_cast<AJS_Console*>(ctx->console);
        }
        free(ctx);
    }
    AllJoynShutdown();
    AllJoynRouterShutdown();
}

void AJS_ConsoleRegisterSignalHandlers(AJS_ConsoleCtx* ctx, SignalRegistration* handlers)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return;
    }
    console->handlers->notification = handlers->notification;
    console->handlers->print = handlers->print;
    console->handlers->alert = handlers->alert;
    console->handlers->dbgVersion = handlers->dbgVersion;
    console->handlers->dbgNotification = handlers->dbgNotification;
}

int AJS_ConsoleConnect(AJS_ConsoleCtx* ctx, const char* deviceName, volatile sig_atomic_t* interrupt)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return 0;
    }
    console->Connect(deviceName, interrupt);
    return 1;
}

int8_t AJS_ConsoleEval(AJS_ConsoleCtx* ctx, const char* script)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return 0;
    }
    return console->Eval(qcc::String(script, 0, strlen(script)));
}

int AJS_ConsoleReboot(AJS_ConsoleCtx* ctx)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return 0;
    }
    if (console->Reboot() == ER_OK) {
        return 1;
    }
    return 0;
}

int AJS_ConsoleInstall(AJS_ConsoleCtx* ctx, const char* name, const uint8_t* script, size_t len)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return 0;
    }
    if (script) {
        if (console->Install(qcc::String(name), script, len) == ER_OK) {
            return 1;
        }
    }
    return 0;
}

int AJS_ConsoleLockdown(AJS_ConsoleCtx* ctx)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return 0;
    }
    return console->LockdownConsole();
}

void AJS_ConsoleSetVerbose(AJS_ConsoleCtx* ctx, uint8_t newValue)
{
    ctx->verbose = newValue;
}

uint8_t AJS_ConsoleGetVerbose(AJS_ConsoleCtx* ctx)
{
    return ctx->verbose;
}

void AJS_Debug_SetQuiet(AJS_ConsoleCtx* ctx, uint8_t quiet)
{
    ctx->quiet = quiet;
}
} // End of extern "C"



