/**
 * @file
 *
 * Define a class that abstracts mutexes.
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
#ifndef _QCC_MUTEX_H
#define _QCC_MUTEX_H

#include <qcc/platform.h>

#if defined(QCC_OS_GROUP_POSIX)
#include <pthread.h>
#endif

namespace qcc {

/**
 * a macro that can be passed into the Mutex::Lock/Unlock member functions to
 * help when debugging Mutex related issues. When running in debug mode, this
 * will cause the code to log the name of the file and the line number of that
 * file each time a Mutex lock is obtained and released. Logging must be turned
 * on to see this information.
 */
#ifndef NDEBUG
#define MUTEX_CONTEXT __FILE__, __LINE__
#else
#define MUTEX_CONTEXT
#endif

/**
 * The implementation of a Mutex abstraction class.
 */
class Mutex {
  public:
    /**
     * The constructor initializes the underlying mutex implementation.
     */
    Mutex();

    /**
     * The destructor will destroy the underlying mutex.
     */
    ~Mutex();

    /**
     * Acquires a lock on the mutex.  If another thread is holding the lock,
     * then this function will block until the other thread has released its
     * lock.
     *
     * NOTE: Best practice is to call `Mutex::Lock(MUTEX_CONTEXT)`
     *
     * @see MUTEX_CONTEXT
     *
     * @param file the name of the file this Mutex lock was called from
     * @param line the line number of the file this Mutex lock was called from
     *
     * @return
     *  - #ER_OK if the lock was acquired.
     *  - #ER_OS_ERROR if the underlying OS reports an error.
     */
    QStatus Lock(const char* file, uint32_t line);

    /**
     * Acquires a lock on the mutex.  If another thread is holding the lock,
     * then this function will block until the other thread has released its
     * lock.
     *
     * It is not safe to use static global data from within this function.
     *
     * @return
     * - #ER_OK if the lock was acquired.
     * - #ER_OS_ERROR if the underlying OS reports an error.
     */
    QStatus Lock();

    /**
     * Releases a lock on the mutex.  This will only release a lock for the
     * current thread if that thread was the one that aquired the lock in the
     * first place.
     *
     * NOTE: Best practice is to call `Mutex::Unlock(MUTEX_CONTEXT)`
     *
     * @see MUTEX_CONTEXT
     *
     * @param file the name of the file this Mutex unlock was called from
     * @param line the line number of the file this Mutex unlock was called from
     *
     * @return
     *  - #ER_OK if the lock was acquired.
     *  - #ER_OS_ERROR if the underlying OS reports an error.
     */
    QStatus Unlock(const char* file, uint32_t line);

    /**
     * Releases a lock on the mutex.  This will only release a lock for the
     * current thread if that thread was the one that aquired the lock in the
     * first place.
     *
     * It is not safe to use static global data from within this function.
     *
     * @return
     * - #ER_OK if the lock was acquired.
     * - #ER_OS_ERROR if the underlying OS reports an error.
     */
    QStatus Unlock();

    /**
     * Attempt to acquire a lock on a mutex. If another thread is holding the lock
     * this function return false otherwise the lock is acquired and the function returns true.
     *
     * @return  True if the lock was acquired.
     */
    bool TryLock();

    /**
     * Assert that current thread owns this Mutex.
     */
    void AssertOwnedByCurrentThread() const;

  private:

    Mutex(const Mutex& other);
    Mutex& operator=(const Mutex& other);

#if defined(QCC_OS_GROUP_POSIX)
    pthread_mutex_t mutex;  ///< The Linux mutex implementation uses pthread mutex's.
#elif defined(QCC_OS_GROUP_WINDOWS)
#include <qcc/windows/Mutex.h>
#else
#error No OS GROUP defined.
#endif

#endif
