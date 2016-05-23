/*
 * TimerEvent.h
 *
 *  Created on: May 18, 2015
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
#ifndef NIO_TIMEREVENT_H_
#define NIO_TIMEREVENT_H_

#include "EventBase.h"
#include "TimerManager.h"

#include <chrono>
#include <functional>

namespace nio {

class TimerEvent final : public EventBase {
  public:

    typedef std::function<void ()> TimerCallback;

    /**
     * Build a new TimerEvent
     *
     * @param when  How long until the timer fires.
     * @param cb    The callback to execute.
     * @param repeat    The repeat time.  Zero for one-shot.
     */
    TimerEvent(
        std::chrono::milliseconds when,
        TimerCallback cb,
        std::chrono::milliseconds repeat = std::chrono::milliseconds::zero());

    virtual ~TimerEvent();

    TimerEvent(const TimerEvent&) = delete;
    TimerEvent& operator=(const TimerEvent&) = delete;

    virtual void ExecuteInternal() override;

    std::chrono::milliseconds GetFirst() const;

    std::chrono::milliseconds GetRepeat() const;

    void SetId(TimerManager::TimerId id);

    TimerManager::TimerId GetId() const;

  private:
    std::chrono::milliseconds when;
    TimerCallback cb;
    std::chrono::milliseconds repeat;
    TimerManager::TimerId id;
};

} /* namespace nio */

#endif /* NIO_TIMEREVENT_H_ */
