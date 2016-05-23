/*
 * TimerManager.h
 *
 *  Created on: Apr 3, 2015
 *      Author: erongo
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
#ifndef NIO_TIMERMANAGER_H_
#define NIO_TIMERMANAGER_H_

#include <chrono>
#include <map>
#include <functional>
#include <mutex>

namespace nio {

class TimerManager {
  public:

    typedef uint64_t TimerId;

    TimerManager();
    virtual ~TimerManager();

    TimerManager(const TimerManager&) = delete;
    TimerManager& operator=(const TimerManager&) = delete;

    typedef std::function<void (TimerId)> TimerCallback;

    /**
     * Start a timer based on relative time 'when'
     *
     * @param when  The time when the callback happens, relative to now
     * @param cb    The function to call
     * @param repeat    How often to repeat after the initial time
     *
     * @return      A unique identifier representing the time to use
     */
    TimerId AddTimer(
        std::chrono::milliseconds when,
        TimerCallback cb,
        std::chrono::milliseconds repeat = std::chrono::milliseconds::zero());

    /**
     * Run all expired timers
     *
     * @return  the number of MILLISECONDS until the next timer expires
     */
    std::chrono::milliseconds RunTimerCallbacks();

    /**
     * Cancel the timer specified
     *
     * @param id    The id returned by AddTimer
     */
    void CancelTimer(TimerId id);

  private:

    static TimerId NextTimer;

    void RunInternalCallback(TimerCallback cb, std::chrono::milliseconds repeat, TimerId id);

    // map of callbacks, sorted by absolute expiration time
    std::multimap<std::chrono::steady_clock::time_point, TimerId> m_timeouts;

    // mapping of id to user callback
    std::map<TimerId, TimerCallback> m_callbacks;

    std::mutex m_lock;
};

}

#endif /* NIO_TIMERMANAGER_H_ */
