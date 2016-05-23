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

#ifndef AJS_CONSOLE_COMMON_H_
#define AJS_CONSOLE_COMMON_H_
#include <stdint.h>

typedef enum {
    AJS_DEBUG_ATTACHED_PAUSED = 0,      /* Debugger is attached and execution is paused */
    AJS_DEBUG_ATTACHED_RUNNING = 1,     /* Debugger is attached and execution is running */
    AJS_DEBUG_DETACHED = 2              /* Debugger is detached */
}AJS_DebugStatus;

typedef struct {
    char* lang;
    char* txt;
}AJS_NotifText;

/*
 * Represents a single breakpoint
 */
typedef struct {
    char* fname;        /* File the breakpoint exists in */
    uint16_t line;       /* Line number the breakpoint is on */
} AJS_BreakPoint;

/*
 * Single frame of the callstack
 */
typedef struct {
    char* filename;     /* File the callstack frame is in */
    char* function;     /* Function scope the callstack is in */
    uint16_t line;      /* Line number of the previous scope */
    uint8_t pc;         /* Program counter for the callstack */
}AJS_CallStack;

/*
 * Represents a single local variable
 */
typedef struct {
    char* name;         /* Name of the variable */
    uint32_t size;      /* Size of the variables data */
    uint8_t* data;      /* Pointer to the variables data */
    uint8_t type;       /* The variables type */
}AJS_Locals;

/*
 * Notification function handler. This type of C function can be registered to
 * handle notifications without prior knowledge of AllJoyn data types
 */
typedef void (*AJS_NotificationHandler)(const char* appName, const char* deviceName, AJS_NotifText* strings, uint32_t numStrings);

/**
 * Print function handler. This type of C function can be registered to
 * handle print messages from AllJoyn.js
 */
typedef void (*AJS_PrintHandler)(const char* message);

/**
 * Alert function handler. This type of C function can be registered to
 * handle alert messages from AllJoyn.js
 */
typedef void (*AJS_AlertHandler)(const char* message);

/**
 * Throw function handler. This type of C function can be registered to
 * handler throw messages from AllJoyn.js
 */
typedef void (*AJS_ThrowHandler)(const char* message);

/**
 * Debug version handler. This C function can be registered to handler
 * debug notification signals which are sent when debugging begins.
 */
typedef void (*AJS_DebugVersionHandler)(const char* version);

/**
 * Debug notification handler. This C function can be registered to handle
 * debug notifications sent from the AllJoyn.js debug target
 */
typedef void (*AJS_DebugNotificationHandler)(uint8_t id, uint8_t state, const char* file, const char* function, uint8_t line, uint8_t pc);

/**
 * Deferred Eval signal handler. This type of C function can be registered to
 * handle the result of an eval.
 */
typedef void (*AJS_DeferredEvalHandler)(uint8_t code, const char* result);

/**
 * User can register their own functions to each type of signal
 * that is sent to the console.
 */
typedef struct {
    AJS_NotificationHandler notification;
    AJS_PrintHandler print;
    AJS_AlertHandler alert;
    AJS_ThrowHandler throwMsg;
    AJS_DebugVersionHandler dbgVersion;
    AJS_DebugNotificationHandler dbgNotification;
    AJS_DeferredEvalHandler evalResult;
}SignalRegistration;

typedef enum {
    DBG_OK = 0,
    DBG_ERR = 1
} AJS_DebugStatusCode;

typedef struct {
    void* console;  /* Pointer to the console class */
    char* version;  /* Debugger version */
    uint8_t verbose;
    uint8_t activeDebug;
    uint8_t quiet;
    uint8_t state;
} AJS_ConsoleCtx;

#endif /* AJS_CONSOLE_COMMON_H_ */
