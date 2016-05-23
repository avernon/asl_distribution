/**
 * @file
 *
 * This file just provides static initialization for the OpenSSL libraries.
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
#include <qcc/Mutex.h>
#include <qcc/Thread.h>
#include <assert.h>

#include "Crypto.h"
#include "OpenSsl.h"
#define OPENSSL_THREAD_DEFINES
#include <openssl/opensslconf.h>

using namespace qcc;

#if defined(OPENSSL_THREADS)

OpenSsl_ScopedLock::OpenSsl_ScopedLock() {
}
OpenSsl_ScopedLock::~OpenSsl_ScopedLock() {
}

static Mutex* locks = 0;

static void LockingCb(int mode, int type, const char* file, int line)
{
    QCC_UNUSED(file);
    QCC_UNUSED(line);
    if (mode & CRYPTO_LOCK) {
        locks[type].Lock();
    } else {
        locks[type].Unlock();
    }
}

QStatus Crypto::Init()
{
    if (!locks) {
        locks = new Mutex[CRYPTO_num_locks()];
        CRYPTO_set_locking_callback(LockingCb);
    }
    return ER_OK;
}

void Crypto::Shutdown()
{
    CRYPTO_set_locking_callback(NULL);
    delete[] locks;
    locks = NULL;
}

#else /* !OPENSSL_THREADS */

static Mutex* mutex = NULL;
static volatile int32_t refCount = 0;

OpenSsl_ScopedLock::OpenSsl_ScopedLock()
{
    if (IncrementAndFetch(&refCount) == 1) {
        mutex = new Mutex();
    } else {
        DecrementAndFetch(&refCount);
        while (!mutex) {
            qcc::Sleep(1);
        }
    }
    mutex->Lock();
}

OpenSsl_ScopedLock::~OpenSsl_ScopedLock()
{
    assert(mutex);
    mutex->Unlock();
}

void Crypto::Init() {
}

void Crypto::Shutdown() {
}

#endif
