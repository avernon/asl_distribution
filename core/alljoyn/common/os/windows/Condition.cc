/**
 * @file
 *
 * This file implements qcc::Condition for Windows systems
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

#include <assert.h>
#include <windows.h>

#include <qcc/Debug.h>
#include <qcc/Condition.h>

#define QCC_MODULE "CONDITION"

using namespace qcc;

Condition::Condition()
{
    InitializeConditionVariable(&c);
}

Condition::~Condition()
{
}

QStatus Condition::Wait(qcc::Mutex& m)
{
    return TimedWait(m, INFINITE);
}

QStatus Condition::TimedWait(qcc::Mutex& m, uint32_t ms)
{
    bool ret = SleepConditionVariableCS(&c, &m.mutex, ms);
    if (ret == true) {
        return ER_OK;
    }

    DWORD error = GetLastError();
    if (error == ERROR_TIMEOUT) {
        return ER_TIMEOUT;
    }

    QCC_LogError(ER_OS_ERROR, ("Condition::TimedWait(): Cannot wait on Windows condition variable (%d)", error));
    return ER_OS_ERROR;
}

QStatus Condition::Signal()
{
    WakeConditionVariable(&c);
    return ER_OK;
}

QStatus Condition::Broadcast()
{
    WakeAllConditionVariable(&c);
    return ER_OK;
}
