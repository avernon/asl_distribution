/*
 * ActiveObject.h
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
#ifndef NIO_ACTIVEOBJECT_H_
#define NIO_ACTIVEOBJECT_H_

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <thread>

#include "DispatcherBase.h"

namespace nio {

class ActiveObject : public DispatcherBase {
  public:

    ActiveObject(uint32_t num_threads = 1);
    virtual ~ActiveObject();

    ActiveObject(const ActiveObject&) = delete;
    ActiveObject& operator=(const ActiveObject&) = delete;

    void Dispatch(Function f) override;

    void Stop();

  private:

    void Run();

    std::atomic<bool> m_running;
    std::vector<std::thread> m_threads;

    std::mutex m_mutex;
    std::condition_variable m_condition;
    std::queue<Function> m_closures;
};

} /* namespace nio */

#endif /* NIO_ACTIVEOBJECT_H_ */
