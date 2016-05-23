# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
/**
 * @file
 *
 * This file declares a Mesa-Semantics Condition Variable class for Posix
 * systems.
 */

/******************************************************************************
 *
 *
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

#ifndef _OS_QCC_CONDITION_H
#define _OS_QCC_CONDITION_H

#include <qcc/platform.h>
#include <qcc/Mutex.h>
#include <Status.h>

namespace qcc {

/**
 * Declaration of a Mesa-Semantics condition variable.  This class provides the
 * mechanism used to implement the system aspects of a condition variable but
 * does not implement the variable itself.  It would be possible to implement a
 * templated virtual class to allow this to all be encapsulated into the the
 * condition variable, but in the interests of simplicity and flexibility, that
 * is left to the user of this class.
 *
 * The condition variable was invented to solve the bound buffer problem, and to
 * illustrate that use, the following code snippet shows how this class could be
 * used to address that type of problem using an STL deque as the protected
 * buffer.
 *
 * Since there are two conditions, buffer empty and buffer full, there are two
 * condition variables.  There is one Mutex protecting the shared buffer.
 * Notice that the Produce() function Wait()s on the full condition and
 * Signal()s the empty condition; while the Consume() function Wait()s on the
 * empty condition and Signal()s the full condition.
 *
 * @verbatim
 * std::deque<int32_t> prot;
 * const uint32_t B_MAX = 2;
 *
 * qcc:: Condition emtpy;
 * qcc:: Condition full;
 * qcc::Mutex m;
 *
 * void Produce(qcc::Condition& empty, qcc::Condition& full, qcc::Mutex& m, uint32_t thing)
 * {
 *     m.Lock();
 *     while (prot.size() == B_MAX) {
 *         full.Wait(m);
 *     }
 *     prot.push_back(thing);
 *     empty.Signal();
 *     m.Unlock();
 * }
 *
 * uint32_t Consume(qcc::Condition& empty, qcc::Condition& full, qcc::Mutex& m)
 * {
 *     m.Lock();
 *     while (prot.size() == 0) {
 *         empty.Wait(m);
 *     }
 *     uint32_t thing = prot.front();
 *     prot.pop_front();
 *     full.Signal();
 *     m.Unlock();
 *     return thing;
 * }
 * @endverbatim
 */
class Condition {
  public:

    /**
     * @brief Construct a condition variable with Mesa semantics.
     */
    Condition();

    /**
     * @brief Destroy a condition variable.
     */
    virtual ~Condition();

    /**
     * @brief Wait on the condition.
     *
     * A condition variable is always associated with a specific lock.  In
     * AllJoyn a lock is a Mutex.  According to Mesa Semantics, a call to Wait()
     * will enqueue the currenly executing thead on the condition variable
     * (suspending its execution) and Unlock() the associated Mutex in a single
     * atomic action.  When the thread resumes exucution the condition variable
     * will Lock() the associated mutex and return.
     *
     * @param m  The Mutex associated with the condition variable
     *
     * @return ER_OK if successful; otherwise an error.
     */
    QStatus Wait(qcc::Mutex& m);

    /**
     * @brief Wait on the condition.
     *
     * A condition variable is always associated with a specific lock.  In
     * AllJoyn a lock is a Mutex.  According to Mesa Semantics, a call to Wait()
     * will enqueue the currenly executing thead on the condition variable
     * (suspending its execution) and Unlock() the associated Mutex in a single
     * atomic action.  When the thread resumes exucution the condition variable
     * will Lock() the associated mutex and return.
     *
     * @param m   The Mutex associated with the condition variable.
     * @param ms  The maximum time to wait for the condition to become signaled.
     *
     * @return ER_OK if successful; otherwise an error.
     */
    QStatus TimedWait(qcc::Mutex& m, uint32_t ms);

    /**
     * @brief Signal the condition variable waking one thread.
     *
     * This function examines the queue of threads associated with the condition
     * and if at least one thread is blocked waiting on the condition variable,
     * exactly one thread will be allowed to resume execution.
     *
     * @return ER_OK if successful; otherwise an error.
     */
    QStatus Signal();

    /**
     * @brief Signal the condition variable waking all threads
     *
     * This function examines the queue of threads associated with the condition
     * and if any threads are blocked waiting on the condition variable, all
     * will be allowed to resume execution.
     *
     * @return ER_OK if successful; otherwise an error.
     */
    QStatus Broadcast();

  private:

    /**
     * The pthread condition variable that is going to do all of the work for us.
     */
    pthread_cond_t c;

    /**
     * Declare copy constructor private without implementation to prevent usage.
     */
    Condition(const Condition& other);

    /**
     * Declare assignment operator private without implementation to prevent usage.
     */
    Condition& operator=(const Condition& other);
};

} // namespace qcc

#endif // _OS_QCC_CONDITION_H
