/**
 * @file
 *
 * Define a class that abstracts Linux rwlock's.
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

/*
 * When building for Android, the Mutex fallback implementation in
 * qcc/RWLock.h is used instead of the pThread based version since the rwlock
 * functionality is missing from the Android version of pThread.
 */
#if !defined(QCC_OS_ANDROID)

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <qcc/RWLock.h>

#include <Status.h>

/** @internal */
#define QCC_MODULE "RWLOCK"

using namespace qcc;

void RWLock::Init()
{
    isInitialized = false;
    int ret;

    ret = pthread_rwlock_init(&rwlock, NULL);
    if (ret != 0) {
        fflush(stdout);
        // Can't use ER_LogError() since it uses mutexes under the hood.
        printf("***** RWLock initialization failure: %d - %s\n", ret, strerror(ret));
        goto cleanup;
    }

    isInitialized = true;

cleanup:
    return;
}

RWLock::~RWLock()
{
    if (!isInitialized) {
        return;
    }

    int ret;
    ret = pthread_rwlock_destroy(&rwlock);
    if (ret != 0) {
        fflush(stdout);
        // Can't use QCC_LogError() since it uses mutexes under the hood.
        printf("***** RWLock destruction failure: %d - %s\n", ret, strerror(ret));
        assert(false);
    }
}

QStatus RWLock::RDLock()
{
    if (!isInitialized) {
        return ER_INIT_FAILED;
    }

    int ret = pthread_rwlock_rdlock(&rwlock);
    if (ret != 0) {
        fflush(stdout);
        // Can't use QCC_LogError() since it uses mutexes under the hood.
        printf("***** RWLock lock failure: %d - %s\n", ret, strerror(ret));
        assert(false);
        return ER_OS_ERROR;
    }
    return ER_OK;
}

QStatus RWLock::WRLock()
{
    if (!isInitialized) {
        return ER_INIT_FAILED;
    }

    int ret = pthread_rwlock_wrlock(&rwlock);
    if (ret != 0) {
        fflush(stdout);
        // Can't use QCC_LogError() since it uses mutexes under the hood.
        printf("***** RWLock lock failure: %d - %s\n", ret, strerror(ret));
        assert(false);
        return ER_OS_ERROR;
    }
    return ER_OK;
}

QStatus RWLock::Unlock()
{
    if (!isInitialized) {
        return ER_INIT_FAILED;
    }

    int ret = pthread_rwlock_unlock(&rwlock);
    if (ret != 0) {
        fflush(stdout);
        // Can't use QCC_LogError() since it uses mutexes under the hood.
        printf("***** RWLock unlock failure: %d - %s\n", ret, strerror(ret));
        assert(false);
        return ER_OS_ERROR;
    }
    return ER_OK;
}

bool RWLock::TryRDLock(void)
{
    if (!isInitialized) {
        return false;
    }
    return pthread_rwlock_tryrdlock(&rwlock) == 0;
}

bool RWLock::TryWRLock(void)
{
    if (!isInitialized) {
        return false;
    }
    return pthread_rwlock_trywrlock(&rwlock) == 0;
}

#endif
