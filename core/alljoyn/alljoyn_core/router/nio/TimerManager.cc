/*
 * TimerManager.cc
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
#include "TimerManager.h"



using namespace nio;

TimerManager::TimerId TimerManager::NextTimer = 0;

TimerManager::TimerManager()
{

}

TimerManager::~TimerManager()
{
}

std::chrono::milliseconds TimerManager::RunTimerCallbacks()
{
    const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

    m_lock.lock();
    auto it = m_timeouts.begin();
    while (it != m_timeouts.end()) {
        if (it->first <= now) {
            auto cb_it = m_callbacks.find(it->second);
            if (cb_it != m_callbacks.end()) {
                // calls RunInternalCallback with the id, user-provided callback, and timeout period
                TimerCallback cb = cb_it->second;
                TimerId id = cb_it->first;
                m_lock.unlock();
                cb(id); // -> RunInternalCallback

                // RunInternalCallback will reacquire the lock
            }

            m_timeouts.erase(it);
            it = m_timeouts.begin();
        } else {
            break;
        }
    }

    std::chrono::milliseconds next = std::chrono::milliseconds::zero();
    if (!m_timeouts.empty()) {
        auto it = m_timeouts.begin();
        next = std::chrono::duration_cast<std::chrono::milliseconds>(it->first - now);
    }

    m_lock.unlock();
    return next;
}

void TimerManager::RunInternalCallback(TimerCallback cb, std::chrono::milliseconds repeat, TimerId id)
{
    // this is the user callback
    // we're calling with m_lock locked but that should be ok since it's a recursive mutex
    // therefore, it's safe for the user's callback to call AddTimer
    cb(id);

    // reacquire the lock
    //std::lock_guard<std::mutex> lock(m_lock);
    m_lock.lock();
    // if we're repeating, reinsert into the timeouts map
    if (repeat != std::chrono::milliseconds::zero()) {
        m_timeouts.insert(std::make_pair(std::chrono::steady_clock::now() + repeat, id));
    } else {
        auto it = m_callbacks.find(id);
        if (it != m_callbacks.end()) {
            m_callbacks.erase(id);
        }
    }
}

void TimerManager::CancelTimer(TimerId id)
{
    std::lock_guard<std::mutex> lock(m_lock);
    auto it = m_callbacks.find(id);
    if (it != m_callbacks.end()) {
        m_callbacks.erase(it);
    }
}

TimerManager::TimerId TimerManager::AddTimer(std::chrono::milliseconds when, TimerCallback cb, std::chrono::milliseconds repeat)
{
    std::chrono::steady_clock::time_point first = std::chrono::steady_clock::now() + when;
    std::lock_guard<std::mutex> lock(m_lock);
    TimerId id = ++NextTimer;
    m_timeouts.insert(std::make_pair(first, id));
    m_callbacks[id] = std::bind(&TimerManager::RunInternalCallback, this, cb, repeat, std::placeholders::_1);
    return id;
}
