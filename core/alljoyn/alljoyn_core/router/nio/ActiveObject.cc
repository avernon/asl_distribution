/*
 * ActiveObject.cc
 *
 *  Created on: May 14, 2015
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

#include "ActiveObject.h"

#include <assert.h>

namespace nio {

ActiveObject::ActiveObject(uint32_t num_threads) : m_running(true)
{
    assert(num_threads > 0);
    m_threads.resize(num_threads);

    for (size_t i = 0; i < m_threads.size(); ++i) {
        m_threads[i] = std::thread(&ActiveObject::Run, this);
    }
}

ActiveObject::~ActiveObject()
{
    Stop();
}


void ActiveObject::Dispatch(Function f)
{
    if (m_running) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_closures.push(f);
        m_condition.notify_one();
    }
}

void ActiveObject::Stop()
{
    if (m_running.exchange(false)) {
        m_condition.notify_all();
        for (size_t i = 0; i < m_threads.size(); ++i) {
            m_threads[i].join();
        }
    }
}

void ActiveObject::Run()
{
    while (m_running) {
        Function closure;

        {
            std::unique_lock<std::mutex> lock(m_mutex);

            //printf("ActiveObject::Run(): Wait for work\n");
            while (m_running == true && m_closures.empty()) {
                m_condition.wait(lock);
            }

            if (!m_running) {
                break;
            }

            // TODO: check the size of m_closures()

            closure = m_closures.front();
            m_closures.pop();
        }

        closure();
    }
}

} /* namespace nio */
