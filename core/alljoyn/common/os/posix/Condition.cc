/**
 * @file
 *
 * This file implements qcc::Condition for Posix systems
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
#include <pthread.h>
#include <errno.h>

#if defined(QCC_OS_DARWIN)
#include <sys/time.h>
#endif

#include <qcc/Debug.h>
#include <qcc/Condition.h>

#define QCC_MODULE "CONDITION"

using namespace qcc;

Condition::Condition()
{
    int ret = pthread_cond_init(&c, NULL);
    if (ret != 0) {
        QCC_LogError(ER_OS_ERROR, ("Condition::Condition(): Cannot initialize pthread condition variable (%d)", ret));
    }
    assert(ret == 0 && "Condition::Condition(): Cannot initialize pthread condition variable");
}

Condition::~Condition()
{
    int ret = pthread_cond_destroy(&c);
    if (ret != 0) {
        QCC_LogError(ER_OS_ERROR, ("Condition::Condition(): Cannot destroy pthread condition variable (%d)", ret));
    }
    assert(ret == 0 && "Condition::Condition(): Cannot destroy pthread condition variable");
}

QStatus Condition::Wait(qcc::Mutex& m)
{
    int ret = pthread_cond_wait(&c, &m.mutex);
    if (ret != 0) {
        QCC_LogError(ER_OS_ERROR, ("Condition::Wait(): Cannot wait on pthread condition variable (%d)", ret));
        return ER_OS_ERROR;
    }
    return ER_OK;
}

QStatus Condition::TimedWait(qcc::Mutex& m, uint32_t ms)
{
    struct timespec tsTimeout;
    tsTimeout.tv_sec = ms / 1000;
    tsTimeout.tv_nsec = (ms % 1000) * 1000000;

    struct timespec tsNow;

#if defined(QCC_OS_DARWIN)
    struct timeval tvNow;
    gettimeofday(&tvNow, NULL);
    TIMEVAL_TO_TIMESPEC(&tvNow, &tsNow);
#else
    clock_gettime(CLOCK_REALTIME, &tsNow);
#endif

    tsTimeout.tv_nsec += tsNow.tv_nsec;
    tsTimeout.tv_sec += tsTimeout.tv_nsec / 1000000000;
    tsTimeout.tv_nsec %= 1000000000;
    tsTimeout.tv_sec += tsNow.tv_sec;

    int ret = pthread_cond_timedwait(&c, &m.mutex, &tsTimeout);
    if (ret == 0) {
        return ER_OK;
    }
    if (ret == ETIMEDOUT) {
        return ER_TIMEOUT;
    }
    QCC_LogError(ER_OS_ERROR, ("Condition::TimedWait(): Cannot wait on pthread condition variable (%d)", ret));
    return ER_OS_ERROR;
}

QStatus Condition::Signal()
{
    int ret = pthread_cond_signal(&c);
    if (ret != 0) {
        QCC_LogError(ER_OS_ERROR, ("Condition::Signal(): Cannot signal pthread condition variable (%d)", ret));
        return ER_OS_ERROR;
    }
    return ER_OK;
}

QStatus Condition::Broadcast()
{
    int ret = pthread_cond_broadcast(&c);
    if (ret != 0) {
        QCC_LogError(ER_OS_ERROR, ("Condition::Broadcast(): Cannot broadcast signal pthread condition variable (%d)", ret));
        return ER_OS_ERROR;
    }
    return ER_OK;
}
