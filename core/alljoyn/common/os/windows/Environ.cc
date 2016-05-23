/**
 * @file
 *
 * This file implements methods from the Environ class.
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

#include <qcc/platform.h>

#include <windows.h>
#include <map>

#include <qcc/Debug.h>
#include <qcc/Environ.h>
#include <qcc/String.h>
#include <qcc/StringUtil.h>
#include <qcc/Logger.h>
#include <qcc/Util.h>

#include <Status.h>

#define QCC_MODULE "ENVIRON"

using namespace std;

namespace qcc {

static uint64_t _environSingleton[RequiredArrayLength(sizeof(Environ), uint64_t)];
static Environ& environSingleton = (Environ&)_environSingleton;
static bool initialized = false;

void Environ::Init()
{
    if (!initialized) {
        new (&environSingleton)Environ();
        initialized = true;
    }
}

void Environ::Shutdown()
{
    if (initialized) {
        environSingleton.~Environ();
        initialized = false;
    }
}

Environ* Environ::GetAppEnviron(void)
{
    return &environSingleton;
}

qcc::String Environ::Find(const qcc::String& key, const char* defaultValue)
{
    qcc::String val;

    lock.Lock();
    if (vars.count(key) == 0) {
        char c;
        char* val = &c;
        DWORD len = GetEnvironmentVariableA(key.c_str(), val, 0);
        if (len) {
            val = new char[len];
            GetEnvironmentVariableA(key.c_str(), val, len);
            vars[key] = val;
            delete [] val;
        }
    }
    val = vars[key];
    if (val.empty() && defaultValue) {
        val = defaultValue;
    }
    lock.Unlock();

    return val;
}

void Environ::Preload(const char* keyPrefix)
{
    size_t prefixLen = strlen(keyPrefix);
    lock.Lock();
    LPTCH env = GetEnvironmentStrings();
    LPTSTR var = env ? reinterpret_cast<LPTSTR>(env) + 1 : NULL;
    if (var == NULL) {
        Log(LOG_ERR, "Environ::Preload unable to read Environment Strings");
        lock.Unlock();
        return;
    }
    while (*var != NULL) {
        size_t len = wcslen((const wchar_t*)var);
        char* ansiBuf = (char*)malloc(len + 1);
        if (NULL == ansiBuf) {
            break;
        }
        WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)var, (int)len, ansiBuf, (int)len, NULL, NULL);
        ansiBuf[len] = '\0';
        if (strncmp(ansiBuf, keyPrefix, prefixLen) == 0) {
            size_t nameLen = prefixLen;
            while (ansiBuf[nameLen] != '=') {
                ++nameLen;
            }
            qcc::String key(ansiBuf, nameLen);
            Find(key, NULL);
        }
        free(ansiBuf);
        var += len + 1;
    }
    if (env) {
        FreeEnvironmentStrings(env);
    }
    lock.Unlock();
}

void Environ::Add(const qcc::String& key, const qcc::String& value)
{
    lock.Lock();
    vars[key] = value;
    lock.Unlock();
}

QStatus Environ::Parse(Source& source)
{
    QStatus status = ER_OK;
    lock.Lock();
    while (ER_OK == status) {
        qcc::String line;
        status = source.GetLine(line);
        if (ER_OK == status) {
            size_t endPos = line.find("#");
            if (qcc::String::npos != endPos) {
                line = line.substr(0, endPos);
            }
            size_t eqPos = line.find("=");
            if (qcc::String::npos != eqPos) {
                vars[Trim(line.substr(0, eqPos))] = Trim(line.substr(eqPos + 1));
            }
        }
    }
    lock.Unlock();
    return (ER_EOF == status) ? ER_OK : status;
}

}   /* namespace */
