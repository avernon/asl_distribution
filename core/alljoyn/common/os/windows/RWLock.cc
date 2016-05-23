/**
 * @file
 *
 * Define a class that abstracts Windows "slim reader/writer" locks.
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
#include <qcc/RWLock.h>
#include <Status.h>

/** @internal */
#define QCC_MODULE "RWLOCK"

using namespace qcc;

void RWLock::Init()
{
    isInitialized = false;
    isWriteLock = false;

    InitializeSRWLock(&rwlock);
    isInitialized = true;
}

RWLock::~RWLock()
{
    if (!isInitialized) {
        return;
    }

    isInitialized = false;
    isWriteLock = false;
}

QStatus RWLock::RDLock()
{
    if (!isInitialized) {
        return ER_INIT_FAILED;
    }

    AcquireSRWLockShared(&rwlock);

    return ER_OK;
}

QStatus RWLock::WRLock()
{
    if (!isInitialized) {
        return ER_INIT_FAILED;
    }

    AcquireSRWLockExclusive(&rwlock);
    isWriteLock = true;

    return ER_OK;
}

QStatus RWLock::Unlock()
{
    if (!isInitialized) {
        return ER_INIT_FAILED;
    }

    if (isWriteLock) {
        isWriteLock = false;
        ReleaseSRWLockExclusive(&rwlock);
    } else {
        ReleaseSRWLockShared(&rwlock);
    }

    return ER_OK;
}

bool RWLock::TryRDLock(void)
{
    if (!isInitialized) {
        return false;
    }

    return TryAcquireSRWLockShared(&rwlock) != 0;
}

bool RWLock::TryWRLock(void)
{
    if (!isInitialized) {
        return false;
    }

    return TryAcquireSRWLockExclusive(&rwlock) != 0;
}
