/**
 * @file
 *
 * Define a class that abstracts Windows file locks.
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
#ifndef _OS_QCC_RWLOCK_H
#define _OS_QCC_RWLOCK_H

#include <qcc/platform.h>

#include <Status.h>

namespace qcc {

/**
 * The Windows implementation of a Rwlock abstraction class.
 */
class RWLock {

  public:
    /**
     * The constructor initializes the underlying rwlock implementation.
     */
    RWLock() { Init(); }

    /**
     * The destructor will destroy the underlying rwlock.
     */
    ~RWLock();

    /**
     * Acquires a lock on the rwlock.  If another thread is holding the lock,
     * then this function will block until the other thread has released its
     * lock.
     *
     * @return  ER_OK if the lock was acquired, ER_INIT_FAILED if there was a
     *          failure to initialize the lock.
     */
    QStatus RDLock();
    QStatus WRLock();

    /**
     * Releases a lock on the rwlock.  This will only release a lock for the
     * current thread if that thread was the one that aquired the lock in the
     * first place.
     *
     * @return  ER_OK if the lock was released, ER_INIT_FAILED if there was a
     *          failure to initialize the lock.
     */
    QStatus Unlock();

    /**
     * Attempt to acquire a lock on a rwlock. If another thread is holding the lock
     * this function return false otherwise the lock is acquired and the function returns true.
     *
     * @return  True if the lock was acquired.
     */
    bool TryRDLock();
    bool TryWRLock();

    /**
     * Rwlock copy constructor creates a new rwlock.
     */
    RWLock(const RWLock& other) { Init(); }

    /**
     * Rwlock assignment operator.
     */
    RWLock& operator=(const RWLock& other) { Init(); return *this; }

  private:
    SRWLOCK rwlock;         ///< The Windows "slim reader/writer" (SRW) lock object.
    bool isInitialized;     ///< true iff rwlock was successfully initialized.
    bool isWriteLock;       ///< true if the lock is being used to write.
    void Init();            ///< Initialize underlying OS rwlock
};

} /* namespace */

#endif
