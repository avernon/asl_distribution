#ifndef AJS_DEBUGGER_H_
#define AJS_DEBUGGER_H_
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

#include "duktape.h"
#include "ajs.h"

/*
 * Debug messages (org.allseen.scriptDebugger)
 */
#define DBG_NOTIF_MSGID         AJ_APP_MESSAGE_ID(0, 2, 0)
#define DBG_BASIC_MSGID         AJ_APP_MESSAGE_ID(0, 2, 1)
#define DBG_TRIGGER_MSGID       AJ_APP_MESSAGE_ID(0, 2, 2)
#define DBG_PAUSE_MSGID         AJ_APP_MESSAGE_ID(0, 2, 3)
#define DBG_RESUME_MSGID        AJ_APP_MESSAGE_ID(0, 2, 4)
#define DBG_STEPIN_MSGID        AJ_APP_MESSAGE_ID(0, 2, 5)
#define DBG_STEPOVER_MSGID      AJ_APP_MESSAGE_ID(0, 2, 6)
#define DBG_STEPOUT_MSGID       AJ_APP_MESSAGE_ID(0, 2, 7)
#define DBG_LISTBREAK_MSGID     AJ_APP_MESSAGE_ID(0, 2, 8)
#define DBG_ADDBREAK_MSGID      AJ_APP_MESSAGE_ID(0, 2, 9)
#define DBG_DELBREAK_MSGID      AJ_APP_MESSAGE_ID(0, 2, 10)
#define DBG_GETVAR_MSGID        AJ_APP_MESSAGE_ID(0, 2, 11)
#define DBG_PUTVAR_MSGID        AJ_APP_MESSAGE_ID(0, 2, 12)
#define DBG_GETCALL_MSGID       AJ_APP_MESSAGE_ID(0, 2, 13)
#define DBG_GETLOCALS_MSGID     AJ_APP_MESSAGE_ID(0, 2, 14)
#define DBG_DUMPHEAP_MSGID      AJ_APP_MESSAGE_ID(0, 2, 15)
#define DBG_VERSION_MSGID       AJ_APP_MESSAGE_ID(0, 2, 16)
#define DBG_GETSCRIPT_MSGID     AJ_APP_MESSAGE_ID(0, 2, 17)
#define DBG_DETACH_MSGID        AJ_APP_MESSAGE_ID(0, 2, 18)
#define DBG_EVAL_MSGID          AJ_APP_MESSAGE_ID(0, 2, 19)
#define DBG_BEGIN_MSGID         AJ_APP_MESSAGE_ID(0, 2, 20)
#define DBG_END_MSGID           AJ_APP_MESSAGE_ID(0, 2, 21)
#define DBG_GETSTATUS_MSGID     AJ_APP_MESSAGE_ID(0, 2, 22)
#define DBG_GETSCRIPTNAME_MSGID AJ_APP_MESSAGE_ID(0, 2, 23)
/* Duplicate from console because an Eval can be processed in the debugger as well */
#define EVAL_MSGID              AJ_APP_MESSAGE_ID(0,  1, 3)
#define LOCK_CONSOLE_MSGID      AJ_APP_MESSAGE_ID(0,  1, 10)
/**
 * Put the console output into quiet mode.
 *
 * @param quiet  If non zero enable quiet mode, if zero disable quiet mode
 */
void AJS_ConsoleSetQuiet(uint8_t quiet);

/**
 * Handle a Debugger Start command.
 *
 * @param ctx  An opaque pointer to a duktape context structure
 * @param msg  The message to handle
 *
 * @return - AJ_OK if the message was handled
 *         - Otherwise and error status
 */
AJ_Status AJS_StartDebugger(duk_context* ctx, AJ_Message* msg);

/**
 * Handle a Debugger Stop command.
 *
 * @param ctx  An opaque pointer to a duktape context structure
 * @param msg  The message to handle
 *
 * @return - AJ_OK if the message was handled
 *         - Otherwise and error status
 */
AJ_Status AJS_StopDebugger(duk_context* ctx, AJ_Message* msg);

/**
 * Handle a Debugger GetStatus command.
 *
 * @param ctx  An opaque pointer to a duktape context structure
 * @param msg  The message to handle
 *
 * @return - AJ_OK if the message was handled
 *         - Otherwise and error status
 */
AJ_Status AJS_DebuggerGetStatus(duk_context* ctx, AJ_Message* msg);

/**
 * Check if a debug client is currently attached
 *
 * @return  TRUE if attached
 *          FALSE if detached
 */
uint8_t AJS_DebuggerIsAttached(void);

/**
 * Handle a Debugger GetScriptName command.
 *
 * @param ctx  An opaque pointer to a duktape context structure
 * @param msg  The message to handle
 *
 * @return - AJ_OK if the message was handled
 *         - Otherwise and error status
 */
AJ_Status AJS_DebuggerGetScriptName(duk_context* ctx, AJ_Message* msg);

/**
 * Handle a Debugger GetScript command.
 *
 * @param ctx  An opaque pointer to a duktape context structure
 * @param msg  The message to handle
 *
 * @return - AJ_OK if the message was handled
 *         - Otherwise and error status
 */
AJ_Status AJS_DebuggerGetScript(duk_context* ctx, AJ_Message* msg);

/**
 * Handle a Debugger control command.
 *
 * @param ctx  An opaque pointer to a duktape context structure
 * @param msg  The message to handle
 *
 * @return - AJ_OK if the message was handled
 *         - Otherwise and error status
 */
AJ_Status AJS_DebuggerCommand(duk_context* ctx, AJ_Message* msg);

#endif /* AJS_DEBUGGER_H_ */
