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

#include "ajs_console.h"
#include "ajs_console_c.h"
#include "ajs_console_common.h"
#include <stdlib.h>

extern "C" {

AJS_DebugStatusCode AJS_Debug_StartDebugger(AJS_ConsoleCtx* ctx)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->StartDebugger();
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_StopDebugger(AJS_ConsoleCtx* ctx)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->StopDebugger();
    return DBG_OK;
}

char* AJS_Debug_GetVersion(AJS_ConsoleCtx* ctx)
{
    if (ctx) {
        if (ctx->version) {
            return ctx->version;
        }
    }
    return NULL;
}

void AJS_Debug_SetActiveDebug(AJS_ConsoleCtx* ctx, uint8_t active)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return;
    }
    console->activeDebug = active;
}

uint8_t AJS_Debug_GetActiveDebug(AJS_ConsoleCtx* ctx)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    return console->activeDebug;
}

AJS_DebugStatus AJS_Debug_GetDebugState(AJS_ConsoleCtx* ctx)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return AJS_DEBUG_DETACHED;
    }
    return console->GetDebugState();
}

AJS_DebugStatusCode AJS_Debug_SetDebugState(AJS_ConsoleCtx* ctx, AJS_DebugStatus state)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->SetDebugState(state);
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_BasicInfo(AJS_ConsoleCtx* ctx, uint16_t* version, char** description, char** targInfo, uint8_t* endianness)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->BasicInfo(version, description, targInfo, endianness);
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_Trigger(AJS_ConsoleCtx* ctx)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->Trigger();
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_StepIn(AJS_ConsoleCtx* ctx)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->StepIn();
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_StepOut(AJS_ConsoleCtx* ctx)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->StepOut();
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_StepOver(AJS_ConsoleCtx* ctx)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->StepOver();
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_Resume(AJS_ConsoleCtx* ctx)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->Resume();
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_Pause(AJS_ConsoleCtx* ctx)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->Pause();
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_Attach(AJS_ConsoleCtx* ctx)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->Attach();
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_Detach(AJS_ConsoleCtx* ctx)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->Detach();
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_AddBreakpoint(AJS_ConsoleCtx* ctx, char* file, uint16_t line)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->AddBreak(file, line);
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_DelBreakpoint(AJS_ConsoleCtx* ctx, uint8_t index)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->DelBreak(index);
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_GetVar(AJS_ConsoleCtx* ctx, char* var, uint8_t** value, uint32_t* size, uint8_t* type)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->GetVar(var, value, size, type);
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_PutVar(AJS_ConsoleCtx* ctx, char* name, uint8_t* value, uint32_t size, uint8_t type)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->PutVar(name, value, size, type);
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_GetCallStack(AJS_ConsoleCtx* ctx, AJS_CallStack** stack, uint8_t* size)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->GetCallStack(stack, size);
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_FreeCallStack(AJS_ConsoleCtx* ctx, AJS_CallStack* stack, uint8_t size)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->FreeCallStack(stack, size);
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_GetLocals(AJS_ConsoleCtx* ctx, AJS_Locals** locals, uint16_t* num)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->GetLocals(locals, num);
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_FreeLocals(AJS_ConsoleCtx* ctx, AJS_Locals* locals, uint8_t num)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->FreeLocals(locals, num);
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_ListBreakpoints(AJS_ConsoleCtx* ctx, AJS_BreakPoint** breakpoints, uint8_t* num)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->ListBreak(breakpoints, num);
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_FreeBreakpoints(AJS_ConsoleCtx* ctx, AJS_BreakPoint* breakpoints, uint8_t num)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->FreeBreakpoints(breakpoints, num);
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_Eval(AJS_ConsoleCtx* ctx, char* str, uint8_t** ret, uint32_t* size, uint8_t* type)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->DebugEval(str, ret, size, type);
    return DBG_OK;
}

AJS_DebugStatusCode AJS_Debug_GetScript(AJS_ConsoleCtx* ctx, uint8_t** script, uint32_t* size)
{
    AJS_Console* console;
    if (ctx && ctx->console) {
        console = static_cast<AJS_Console*>(ctx->console);
    } else {
        return DBG_ERR;
    }
    console->GetScript(script, size);
    return DBG_OK;
}
}
