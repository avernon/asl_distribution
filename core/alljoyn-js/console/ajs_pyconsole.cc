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

#include <alljoyn/Init.h>
#include <Python.h>
#include "ajs_console.h"
#include "alljoyn/Status.h"

using namespace qcc;
using namespace ajn;

class AJS_PyConsole : public AJS_Console {
  public:
    AJS_PyConsole();

    virtual void Notification(const InterfaceDescription::Member* member, const char* sourcePath, Message& msg);

    virtual void Print(const char* fmt, ...);

    virtual void PrintMsg(const InterfaceDescription::Member* member, const char* sourcePath, Message& msg);

    virtual void AlertMsg(const InterfaceDescription::Member* member, const char* sourcePath, Message& msg);

    virtual void DebugNotification(const ajn::InterfaceDescription::Member* member, const char* sourcePath, ajn::Message& msg);

    virtual void DebugVersion(const ajn::InterfaceDescription::Member* member, const char* sourcePath, ajn::Message& msg);

    virtual void EvalResult(const ajn::InterfaceDescription::Member* member, const char* sourcePath, ajn::Message& msg);

    void Msg(const char* msgType, const char* msgText);

    PyObject* pycallback; /* Only modify when Python GIL is held */

    PyObject* notifCallback; /* Python callback for debug notifications */

  private:
    virtual void RegisterHandlers(BusAttachment* ajb);

};

static volatile sig_atomic_t g_interrupt = false;

static void SigIntHandler(int sig)
{
    g_interrupt = true;
}

static uint32_t ByteSwap32(uint32_t x)
{
    return ((x >> 24) & 0x000000FF) | ((x >> 8) & 0x0000FF00) |
           ((x << 24) & 0xFF000000) | ((x << 8) & 0x00FF0000);
}

static uint64_t ByteSwap64(uint64_t x)
{
    return ((x >> 56) & 0x00000000000000FF) | ((x >> 40) & 0x000000000000FF00) |
           ((x << 56) & 0xFF00000000000000) | ((x << 40) & 0x00FF000000000000) |
           ((x >> 24) & 0x0000000000FF0000) | ((x >>  8) & 0x00000000FF000000) |
           ((x << 24) & 0x0000FF0000000000) | ((x <<  8) & 0x000000FF00000000);
}

static AJS_PyConsole* console = NULL;
static char debugVersion[128];
static uint16_t dbgCurrentLine = 0;
static uint16_t dbgPC = 0;

static void FatalError(void)
{
    printf("There was a fatal error, exiting\n");
    exit(1);
}

AJS_PyConsole::AJS_PyConsole() : AJS_Console(), pycallback(NULL), notifCallback(NULL) {
}

void AJS_PyConsole::Print(const char* fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);

    (void) vprintf(fmt, ap);

    va_end(ap);
}

void AJS_PyConsole::RegisterHandlers(BusAttachment* ajb)
{
    const InterfaceDescription* ifc;
    const InterfaceDescription* dbg_ifc;

    ifc = ajb->GetInterface("org.allseen.scriptConsole");
    dbg_ifc = ajb->GetInterface("org.allseen.scriptDebugger");
    ajb->RegisterSignalHandler(this,
                               static_cast<MessageReceiver::SignalHandler>(&AJS_PyConsole::PrintMsg),
                               ifc->GetMember("print"),
                               "/ScriptConsole");

    ajb->RegisterSignalHandler(this,
                               static_cast<MessageReceiver::SignalHandler>(&AJS_PyConsole::AlertMsg),
                               ifc->GetMember("alert"),
                               "/ScriptConsole");

    ajb->RegisterSignalHandler(this,
                               static_cast<MessageReceiver::SignalHandler>(&AJS_PyConsole::DebugNotification),
                               dbg_ifc->GetMember("notification"),
                               "/ScriptConsole");

    ajb->RegisterSignalHandler(this,
                               static_cast<MessageReceiver::SignalHandler>(&AJS_PyConsole::DebugVersion),
                               dbg_ifc->GetMember("version"),
                               "/ScriptConsole");

    ajb->RegisterSignalHandler(this,
                               static_cast<MessageReceiver::SignalHandler>(&AJS_PyConsole::EvalResult),
                               ifc->GetMember("evalResult"),
                               "/ScriptConsole");

    ifc = ajb->GetInterface("org.alljoyn.Notification");
    ajb->RegisterSignalHandler(this,
                               static_cast<MessageReceiver::SignalHandler>(&AJS_PyConsole::Notification),
                               ifc->GetMember("notify"),
                               NULL);
}

void AJS_PyConsole::DebugVersion(const InterfaceDescription::Member* member, const char* sourcePath, Message& msg)
{
    strcpy(debugVersion, msg->GetArg()->v_string.str);
}

void AJS_PyConsole::DebugNotification(const InterfaceDescription::Member* member, const char* sourcePath, Message& msg)
{
    uint8_t id = msg->GetArg()->v_byte;
    switch (id) {
    case STATUS_NOTIFICATION:
        {
            char fullString[128];
            uint8_t state;
            const char* fileName;
            const char* funcName;
            uint16_t lineNumber;
            uint8_t pc;
            msg->GetArgs("yyssqy", &id, &state, &fileName, &funcName, &lineNumber, &pc);
            dbgCurrentLine = lineNumber;
            dbgPC = pc;
            if (state == 1) {
                debugState = AJS_DEBUG_ATTACHED_PAUSED;
            } else if (state == 0) {
                debugState = AJS_DEBUG_ATTACHED_RUNNING;
            }
            sprintf(fullString, "State: %i, File: %s, Function: %s, Line: %i, PC: %i", state, fileName, funcName, lineNumber, pc);
            Msg("DebugNotification", fullString);

        }
        break;

    //TODO: Handle all notification types appropriately
    case PRINT_NOTIFICATION:
        QCC_SyncPrintf("PRINT NOTIFICATION: %s\n", msg->GetArg()->v_string.str);
        break;

    case ALERT_NOTIFICATION:
        QCC_SyncPrintf("ALERT NOTIFICATION: %s\n", msg->GetArg()->v_string.str);
        break;

    case LOG_NOTIFICATION:
        QCC_SyncPrintf("LOG NOTIFICATION: %u %s\n", msg->GetArg()->v_byte, msg->GetArg()->v_string.str);
        break;
    }
}

void AJS_PyConsole::EvalResult(const InterfaceDescription::Member* member, const char* sourcePath, Message& msg)
{
    uint8_t code;
    char* result;

    msg->GetArgs("ys", &code, &result);

    switch (code) {
    /* Success */
    case 0:
        Msg("EvalResult", result);
        break;

    /* Other possible errors */
    case 1:
        Msg("EvalResult", "Syntax Error");
        break;

    case 2:
        Msg("EvalResult", "Type or Range error");
        break;

    case 3:
        Msg("EvalResult", "Resource Error");
        break;

    case 5:
        Msg("EvalResult", "Internal Duktape Error");
        break;
    }
}

void AJS_PyConsole::Notification(const InterfaceDescription::Member* member, const char* sourcePath, Message& msg)
{
    const char* TYPES[] = { "Emergency", "Warning", "Informational", "Unknown" };
    uint16_t version;
    uint32_t notifId;
    uint16_t notifType;
    const char* deviceId;
    const char* deviceName;
    const uint8_t* appId;
    size_t appIdLen;
    const char* appName;
    const MsgArg* attrs;
    const MsgArg* cust;
    const MsgArg* strings;

    if (pycallback == NULL) {
        Print("No callback, skipping notification\n");
        return;
    }

    QStatus status = msg->GetArgs("qiqssays***", &version, &notifId, &notifType, &deviceId, &deviceName, &appIdLen, &appId, &appName, &attrs, &cust, &strings);
    if (status != ER_OK) {
        QCC_LogError(status, ("Notification GetArgs failed\n"));
        return;
    }
    if (notifType > 2) {
        notifType = 3;
    }

    /* Start Python work... Get the GIL */
    PyGILState_STATE gilstate = PyGILState_Ensure();

    /*
     * Unpack the notification strings
     */
    PyObject* tup;
    PyObject* list = PyList_New(0);
    if (list == NULL) {
        return;
    }

    MsgArg* entries;
    size_t num;
    strings->Get("a(ss)", &num, &entries);
    for (size_t i = 0; i < num; ++i) {
        char* lang;
        char* txt;
        entries[i].Get("(ss)", &lang, &txt);
        tup = Py_BuildValue("ss", lang, txt);
        if (tup != NULL) {
            PyList_Append(list, tup);
            Py_DECREF(tup);
        }
    }

    tup = PyList_AsTuple(list);
    Py_DECREF(list);
    PyObject* cbdata = Py_BuildValue("s(sssO)", "Notification", TYPES[notifType], appName, deviceName, tup);
    Py_DECREF(tup);

    if (cbdata != NULL) {
        PyObject* result = PyObject_CallObject(console->pycallback, cbdata);
        Py_DECREF(cbdata);

        if (result == NULL) {
            Print("Callback error\n");
        } else {
            Py_DECREF(result);
        }
    }

    /* Release interpreter lock */
    PyGILState_Release(gilstate);
}

void AJS_PyConsole::Msg(const char* msgType, const char* msgText)
{
    /* Start Python work... Get the GIL */
    PyGILState_STATE gilstate = PyGILState_Ensure();

    PyObject* cbdata = Py_BuildValue("ss", msgType, msgText);

    if (cbdata != NULL) {
        PyObject* result = PyObject_CallObject(console->pycallback, cbdata);
        Py_DECREF(cbdata);

        if (result == NULL) {
            Print("Callback error\n");
        } else {
            Py_DECREF(result);
        }
    }

    /* Release interpreter lock */
    PyGILState_Release(gilstate);
}

void AJS_PyConsole::PrintMsg(const InterfaceDescription::Member* member, const char* sourcePath, Message& msg)
{
    Msg("Print", msg->GetArg()->v_string.str);
}

void AJS_PyConsole::AlertMsg(const InterfaceDescription::Member* member, const char* sourcePath, Message& msg)
{
    Msg("Alert", msg->GetArg()->v_string.str);
}

static PyObject* statusobject(QStatus status)
{
    return Py_BuildValue("s", QCC_StatusText(status));
}

static PyObject* py_connect(PyObject* self, PyObject* args)
{
    QStatus status;
    const char* name;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    Py_BEGIN_ALLOW_THREADS
    if (strcmp(name, "") == 0) {
        status = console->Connect(NULL, &g_interrupt);
    } else {
        status = console->Connect(name, &g_interrupt);
    }
    Py_END_ALLOW_THREADS

    return statusobject(status);
}

static PyObject* py_eval(PyObject* self, PyObject* args)
{
    int8_t ret;
    const char* text;

    if (!PyArg_ParseTuple(args, "s", &text)) {
        return NULL;
    }

    Py_BEGIN_ALLOW_THREADS
        ret = console->Eval(String(text));
    Py_END_ALLOW_THREADS


    switch (ret) {
    /* Success */
    case 0:
        console->Msg("EvalResult", "Compile Sucess");
        break;

    /* Other possible errors */
    case 1:
        console->Msg("EvalResult", "Syntax Error");
        break;

    case 2:
        console->Msg("EvalResult", "Type or Range error");
        break;

    case 3:
        console->Msg("EvalResult", "Resource Error");
        break;

    case 5:
        console->Msg("EvalResult", "Internal Duktape Error");
        break;
    }

    return statusobject((QStatus)0);
}

static PyObject* py_install(PyObject* self, PyObject* args)
{
    QStatus status;
    const char* name;
    const uint8_t* script;
    int scriptlen;

    if (!PyArg_ParseTuple(args, "ss#", &name, &script, &scriptlen)) {
        return NULL;
    }

    Py_BEGIN_ALLOW_THREADS
        status = console->Install(String(name), script, scriptlen);
    Py_END_ALLOW_THREADS

    return statusobject(status);
}

static PyObject* py_reboot(PyObject* self, PyObject* args)
{
    QStatus status;

    Py_BEGIN_ALLOW_THREADS
        status = console->Reboot();
    Py_END_ALLOW_THREADS

    return statusobject(status);
}

static PyObject* py_setcallback(PyObject* self, PyObject* args)
{
    PyObject* tempCB;

    if (!PyArg_ParseTuple(args, "O", &tempCB)) {
        return NULL;
    }

    if (!PyCallable_Check(tempCB)) {
        PyErr_SetString(PyExc_TypeError, "Not a callable");
        return NULL;
    }

    Py_XINCREF(tempCB);
    Py_XDECREF(console->pycallback);
    console->pycallback = tempCB;

    return Py_BuildValue("");
}

static PyObject* py_gettargstatus(PyObject* self, PyObject* args)
{
    int8_t status;
    Py_BEGIN_ALLOW_THREADS
        status = console->GetDebugStatus();
    Py_END_ALLOW_THREADS

    return Py_BuildValue("i", (int8_t)status);
}

static PyObject* py_getversion(PyObject* self, PyObject* args)
{
    return Py_BuildValue("s", debugVersion);
}

static PyObject* py_getscript(PyObject* self, PyObject* args)
{
    bool ret = false;
    PyObject* tuple;
    char* script = NULL;
    uint32_t size;
    Py_BEGIN_ALLOW_THREADS
        ret = console->GetScript((uint8_t**)&script, &size);
    Py_END_ALLOW_THREADS
    if (ret == false) {
        return Py_BuildValue("s", "");
    }
    tuple = Py_BuildValue("s", script);
    free(script);
    return tuple;
}

static PyObject* py_startdebugger(PyObject* self, PyObject* args)
{
    Py_BEGIN_ALLOW_THREADS
    console->StartDebugger();
    Py_END_ALLOW_THREADS
    return statusobject(ER_OK);
}

static PyObject* py_stopdebugger(PyObject* self, PyObject* args)
{
    Py_BEGIN_ALLOW_THREADS
    console->StopDebugger();
    Py_END_ALLOW_THREADS
    return statusobject(ER_OK);
}

static PyObject* py_stepinto(PyObject* self, PyObject* args)
{
    Py_BEGIN_ALLOW_THREADS
    console->StepIn();
    Py_END_ALLOW_THREADS
    return statusobject(ER_OK);
}

static PyObject* py_stepout(PyObject* self, PyObject* args)
{
    Py_BEGIN_ALLOW_THREADS
    console->StepOut();
    Py_END_ALLOW_THREADS
    return statusobject(ER_OK);
}

static PyObject* py_stepover(PyObject* self, PyObject* args)
{
    Py_BEGIN_ALLOW_THREADS
    console->StepOver();
    Py_END_ALLOW_THREADS
    return statusobject(ER_OK);
}

static PyObject* py_resume(PyObject* self, PyObject* args)
{
    Py_BEGIN_ALLOW_THREADS
    console->Resume();
    Py_END_ALLOW_THREADS
    return statusobject(ER_OK);
}

static PyObject* py_pause(PyObject* self, PyObject* args)
{
    Py_BEGIN_ALLOW_THREADS
    console->Pause();
    Py_END_ALLOW_THREADS
    return statusobject(ER_OK);
}

static PyObject* py_getcurrentline(PyObject* self, PyObject* args)
{
    return Py_BuildValue("i", dbgCurrentLine);
}

static PyObject* py_getlocals(PyObject* self, PyObject* args)
{
    AJS_Locals* vars = NULL;
    uint16_t size;
    int i;
    PyObject* tuple;
    Py_BEGIN_ALLOW_THREADS
    console->GetLocals(&vars, &size);
    Py_END_ALLOW_THREADS

    if (vars && size > 0) {
        if (strcmp(vars[0].name, "N/A") != 0) {
            tuple = PyTuple_New(size);
            for (i = 0; i < size; i++) {
                if (vars[i].type == DBG_TYPE_UNUSED) {
                    PyTuple_SetItem(tuple, i, Py_BuildValue("ss", vars[i].name, "Uninitialized"));
                } else if (vars[i].type == DBG_TYPE_UNDEFINED) {
                    PyTuple_SetItem(tuple, i, Py_BuildValue("ss", vars[i].name, "Undefined"));
                } else if (vars[i].type == DBG_TYPE_NULL) {
                    PyTuple_SetItem(tuple, i, Py_BuildValue("ss", vars[i].name, "Null"));
                } else if (vars[i].type == DBG_TYPE_TRUE) {
                    PyTuple_SetItem(tuple, i, Py_BuildValue("ss", vars[i].name, "True"));
                } else if (vars[i].type == DBG_TYPE_FALSE) {
                    PyTuple_SetItem(tuple, i, Py_BuildValue("ss", vars[i].name, "False"));
                } else if (vars[i].type == DBG_TYPE_NUMBER) {
                    /* Convert the number to IEEE double */
                    uint64_t tmp;
                    double number;
                    memcpy(&tmp, vars[i].data, sizeof(uint64_t));
                    tmp = ByteSwap64(tmp);
                    memcpy(&number, &tmp, sizeof(uint64_t));
                    PyTuple_SetItem(tuple, i, Py_BuildValue("sd", vars[i].name, number));
                } else if (vars[i].type == DBG_TYPE_STRLOW) {
                    PyTuple_SetItem(tuple, i, Py_BuildValue("ss", vars[i].name, (char*)vars[i].data));
                } else if (vars[i].type == DBG_TYPE_OBJECT) {
                    PyTuple_SetItem(tuple, i, Py_BuildValue("ss", vars[i].name, "Object"));
                } else if ((vars[i].type == DBG_TYPE_POINTER) || (vars[i].type == DBG_TYPE_HEAPPTR)) {
                    PyTuple_SetItem(tuple, i, Py_BuildValue("ss", vars[i].name, "Pointer"));
                } else if (vars[i].type == DBG_TYPE_LIGHTFUNC) {
                    PyTuple_SetItem(tuple, i, Py_BuildValue("ss", vars[i].name, "Light function"));
                } else {
                    char toStrVal[64];
                    sprintf(toStrVal, "*%s[0] = 0x%02x", vars[i].name, *vars[i].data);
                    PyTuple_SetItem(tuple, i, Py_BuildValue("ss", vars[i].name, toStrVal));
                }
            }
            console->FreeLocals(vars, size);
            return tuple;
        } else {
            return Py_BuildValue("");
        }
    }
    return Py_BuildValue("");
}

static PyObject* py_getstacktrace(PyObject* self, PyObject* args)
{
    AJS_CallStack* stack = NULL;
    uint8_t size;
    int i;
    PyObject* tuple;
    Py_BEGIN_ALLOW_THREADS
    console->GetCallStack(&stack, &size);
    Py_END_ALLOW_THREADS
    if (stack) {
        tuple = PyTuple_New(size);
        for (i = 0; i < size; i++) {
            PyTuple_SetItem(tuple, i, Py_BuildValue("ssii", stack[i].filename, stack[i].function, stack[i].line, stack[i].pc));
        }
        console->FreeCallStack(stack, size);
        return tuple;
    }
    return Py_BuildValue("");
}

static PyObject* py_getbreakpoints(PyObject* self, PyObject* args)
{
    AJS_BreakPoint* list = NULL;
    uint8_t num;
    int i;
    PyObject* tuple;
    Py_BEGIN_ALLOW_THREADS
    console->ListBreak(&list, &num);
    Py_END_ALLOW_THREADS
    if (list) {
        tuple = PyTuple_New(num);
        for (i = 0; i < num; i++) {
            PyTuple_SetItem(tuple, i, Py_BuildValue("si", list[i].fname, list[i].line));
        }
        console->FreeBreakpoints(list, num);
        return tuple;
    }
    return Py_BuildValue("");
}

static PyObject* py_addbreakpoint(PyObject* self, PyObject* args)
{
    const char* text;
    char file[128];
    uint8_t line;
    uint16_t i = 0;

    if (!PyArg_ParseTuple(args, "s", &text)) {
        return NULL;
    }
    while (i < strlen(text)) {
        if (text[i] == ' ') {
            break;
        }
        i++;
    }

    strncpy(file, text, i);
    file[i] = '\0';
    line = atoi(text + i);

    Py_BEGIN_ALLOW_THREADS
    console->AddBreak(console->GetScriptName(), line);
    Py_END_ALLOW_THREADS

    return statusobject(ER_OK);
}

static PyObject* py_delbreakpoint(PyObject* self, PyObject* args)
{
    const char* text;
    uint8_t index;

    if (!PyArg_ParseTuple(args, "s", &text)) {
        return NULL;
    }

    index = atoi(text);

    Py_BEGIN_ALLOW_THREADS
    console->DelBreak(index);
    Py_END_ALLOW_THREADS

    return statusobject(ER_OK);
}

static PyObject* py_attach(PyObject* self, PyObject* args)
{
    Py_BEGIN_ALLOW_THREADS
    console->StartDebugger();
    Py_END_ALLOW_THREADS
    return statusobject(ER_OK);
}

static PyObject* py_detach(PyObject* self, PyObject* args)
{
    Py_BEGIN_ALLOW_THREADS
    console->Detach();
    Py_END_ALLOW_THREADS
    return statusobject(ER_OK);
}

static PyObject* py_putvar(PyObject* self, PyObject* args)
{
    char* newValue;
    char* varName;
    uint8_t type;
    if (!PyArg_ParseTuple(args, "ss", &varName, &newValue)) {
        return NULL;
    }
    /* Get the variables type */
    Py_BEGIN_ALLOW_THREADS
    console->GetVar(varName, NULL, NULL, &type);
    Py_END_ALLOW_THREADS
    if ((type >= 0x60) && (type <= 0x7f)) {
        /* Any characters can be treated as a string */
        Py_BEGIN_ALLOW_THREADS
        console->PutVar(varName, (uint8_t*)newValue, strlen(newValue), type);
        Py_END_ALLOW_THREADS
    } else if (type == 0x1a) {
        uint8_t k = 0;
        double number;
        /* Check the input to ensure its a number */
        for (k = 0; k < strlen(newValue); k++) {
            /* ASCII '0' and ASCII '9' */
            if (((uint8_t)newValue[k] <= 48) && ((uint8_t)newValue[k] >= 57)) {
                QCC_SyncPrintf("Invalid input for variable %s\n", varName);
                break;
            }
        }
        number = atof(newValue);
        Py_BEGIN_ALLOW_THREADS
        console->PutVar(varName, (uint8_t*)&number, sizeof(double), type);
        Py_END_ALLOW_THREADS
    } else if (type == 0x18) {
        /* True, can change to false */
        if ((strcmp(newValue, "False") == 0) || (strcmp(newValue, "false") == 0)) {
            uint8_t tmp = 0x19;
            Py_BEGIN_ALLOW_THREADS
            console->PutVar(varName, (uint8_t*)&tmp, 1, type);
            Py_END_ALLOW_THREADS
        }
    } else if (type == 0x19) {
        /* False, can change to true */
        if ((strcmp(newValue, "True") == 0) || (strcmp(newValue, "true") == 0)) {
            uint8_t tmp = 0x18;
            Py_BEGIN_ALLOW_THREADS
            console->PutVar(varName, (uint8_t*)&tmp, 1, type);
            Py_END_ALLOW_THREADS
        }
    } else {
        QCC_SyncPrintf("Invalid or not supported putVar type 0x%02x\n", type);
    }
    return statusobject(ER_OK);
}

static PyObject* py_debugeval(PyObject* self, PyObject* args)
{
    char* evalString;
    uint8_t* value;
    uint32_t size;
    uint8_t type;
    PyObject* tuple;

    if (!PyArg_ParseTuple(args, "s", &evalString)) {
        return NULL;
    }
    Py_BEGIN_ALLOW_THREADS
    console->DebugEval(evalString, &value, &size, &type);
    Py_END_ALLOW_THREADS
    if (value) {
        switch (type) {
        case DBG_TYPE_NUMBER:
            {
                /* Number (double) */
                uint64_t tmp;
                double number;
                memcpy(&tmp, value, sizeof(uint64_t));
                tmp = ByteSwap64(tmp);
                memcpy(&number, &tmp, sizeof(uint64_t));
                tuple = Py_BuildValue("d", number);
            }
            break;

        case DBG_TYPE_NULL:
            tuple = Py_BuildValue("s", "Null");
            break;

        case DBG_TYPE_TRUE:
            tuple = Py_BuildValue("s", "True");
            break;

        case DBG_TYPE_FALSE:
            tuple = Py_BuildValue("s", "False");
            break;

        case DBG_TYPE_UNUSED:
            tuple = Py_BuildValue("s", "Unused");
            break;

        case DBG_TYPE_UNDEFINED:
            tuple = Py_BuildValue("s", "Undefined");
            break;

        case DBG_TYPE_STRLOW:
            {
                /* String type */
                char* str = (char*)malloc(sizeof(char) * size + 1);
                if (!str) {
                    FatalError();
                }
                memcpy(str, value, size);
                str[size] = '\0';
                tuple = Py_BuildValue("s", str);
                free(str);
            }
            break;

        case DBG_TYPE_BUFFER2:
            {
                uint8_t i;
                tuple = PyTuple_New(size);
                for (i = 0; i < size; ++i) {
                    PyTuple_SetItem(tuple, i, Py_BuildValue("i", value[i]));
                }
            }
            break;

        case DBG_TYPE_STRING2:
            tuple = Py_BuildValue("s", (char*)value);
            break;

        case DBG_TYPE_OBJECT:
            tuple = Py_BuildValue("s", "<object>");
            break;

        default:
            printf("Currently unhandled type 0x%02x, size = %u\n", type, size);
            tuple = Py_BuildValue("");
            break;
        }
        return tuple;
    }
    return Py_BuildValue("");
}

static PyObject* py_lockdown(PyObject* self, PyObject* args)
{
    Py_BEGIN_ALLOW_THREADS
    if (console->LockdownConsole()) {
        console->Msg("DebugNotification", "Console locked down sucessfully\n");
    }
    Py_END_ALLOW_THREADS
    return statusobject(ER_OK);
}

static PyMethodDef AJSConsoleMethods[] = {
    { "Connect", py_connect, METH_VARARGS, "Make a connection" },
    { "Eval", py_eval, METH_VARARGS, "Evaluate a statement" },
    { "Install", py_install, METH_VARARGS, "Install a script" },
    { "Reboot", py_reboot, METH_VARARGS, "Reboot target" },
    { "SetCallback", py_setcallback, METH_VARARGS, "Set callback function" },
    { "GetScript", py_getscript, METH_VARARGS, "Get the installed script" },
    { "GetLine", py_getcurrentline, METH_VARARGS, "Get the current line of execution" },
    { "GetDebugVersion", py_getversion, METH_VARARGS, "Get the debugger version" },
    { "StartDebugger", py_startdebugger, METH_VARARGS, "Start the debugger" },
    { "StopDebugger", py_stopdebugger, METH_VARARGS, "Stop the debugger" },
    { "StepInto", py_stepinto, METH_VARARGS, "Debugger step into function" },
    { "StepOut", py_stepout, METH_VARARGS, "Debugger step out function" },
    { "StepOver", py_stepover, METH_VARARGS, "Debugger step over function" },
    { "Resume", py_resume, METH_VARARGS, "Resume the debugger (run)" },
    { "Pause", py_pause, METH_VARARGS, "Pause the debugger" },
    { "GetLocals", py_getlocals, METH_VARARGS, "Get all local variables" },
    { "GetBreakpoints", py_getbreakpoints, METH_VARARGS, "Get all breakpoints" },
    { "AddBreakpoint", py_addbreakpoint, METH_VARARGS, "Get all breakpoints" },
    { "DelBreakpoint", py_delbreakpoint, METH_VARARGS, "Delete a breakpoint at index" },
    { "GetStacktrace", py_getstacktrace, METH_VARARGS, "Get the current stack trace" },
    { "Attach", py_attach, METH_VARARGS, "Attach the debugger to the target" },
    { "Detach", py_detach, METH_VARARGS, "Detach the debugger from the target" },
    { "DebugEval", py_debugeval, METH_VARARGS, "Do an eval while debugging" },
    { "PutVar", py_putvar, METH_VARARGS, "Change a variables value" },
    { "GetTargetStatus", py_gettargstatus, METH_VARARGS, "Get the targets current status" },
    { "Lockdown", py_lockdown, METH_VARARGS, "Lockdown the console" },
    { NULL, NULL, 0, NULL }
};

struct module_state {
    PyObject*error;
};

#if PY_MAJOR_VERSION >= 3
#define GET_PY_STATE(s) ((struct module_state*)PyModule_GetState(s))
#else
#define GET_PY_STATE(s) (&_state)
#endif

#if PY_MAJOR_VERSION >= 3

#define INITERROR return NULL

static int myextension_traverse(PyObject*m, visitproc visit, void*arg) {
    Py_VISIT(GET_PY_STATE(m)->error);
    return 0;
}

static int myextension_clear(PyObject*m) {
    Py_CLEAR(GET_PY_STATE(m)->error);
    return 0;
}

static struct PyModuleDef consoleModule = {
    PyModuleDef_HEAD_INIT,
    "AJSConsole",
    NULL,
    sizeof(struct module_state),
    AJSConsoleMethods,
    NULL,
    myextension_traverse,
    myextension_clear,
    NULL
};


#endif


#if PY_MAJOR_VERSION >= 3
extern "C" PyObject * PyInit_AJSConsole(void)
{
    PyObject*module = PyModule_Create(&consoleModule);
    PyEval_InitThreads();
    /* Install SIGINT handler */
    signal(SIGINT, SigIntHandler);
    AllJoynInit();
    AllJoynRouterInit();
    if (module == NULL) {
        INITERROR;
    }
    struct module_state*st = GET_PY_STATE(module);

    st->error = PyErr_NewException("AJSConsole.Error", NULL, NULL);
    if (st->error == NULL) {
        Py_DECREF(module);
        INITERROR;
    }

    console = new AJS_PyConsole();
    return module;
}
#else
PyMODINIT_FUNC initAJSConsole(void)
{
    /* Install SIGINT handler */
    signal(SIGINT, SigIntHandler);
    AllJoynInit();
    AllJoynRouterInit();
    (void) Py_InitModule("AJSConsole", AJSConsoleMethods);

    PyEval_InitThreads();
    console = new AJS_PyConsole();
}
#endif
