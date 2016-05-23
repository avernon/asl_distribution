/*
 * Proactor.h
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
#ifndef NIO_PROACTOR_H_
#define NIO_PROACTOR_H_

#include "ActiveObject.h"
#include "Reactor.h"
#include "DispatcherBase.h"

#include <thread>

namespace nio {

class EventNotifier;
class SocketReadableEvent;
class SocketWriteableEvent;
class TimerEvent;

/**
 * The Proactor owns a Reactor and dispatches callbacks to an ActiveObject.
 * The Reactor uses a single thread to wait for events and makes the callbacks that
 * have been associated with those events.
 *
 * Those callbacks are intercepted by the Proactor and placed into a queue.  The callbacks
 * are then picked up by the ActiveObject's thread pool and executed.  Callbacks registered
 * with the Proactor are not guaranteed to happen on the same thread so protection
 * must be used.
 */
class Proactor : public DispatcherBase {
  public:
    Proactor(uint32_t num_threads);
    virtual ~Proactor();

    /**
     * As with Reactor, Run will block until Stop() is called
     */
    void Run();

    /**
     * Stop running.
     */
    void Stop();

    /**
     * Register an notifier event.  This is used to signal the reactor thread
     * to wake up and do something.  That "something" is specified by the
     * callback in EventNotifier.
     */
    void Register(std::shared_ptr<EventNotifier> notifier);
    void Cancel(std::shared_ptr<EventNotifier> notifier);

    /**
     * Execute a callback when a socket becomes readable
     */
    void Register(std::shared_ptr<SocketReadableEvent> sockevent);
    void Cancel(std::shared_ptr<SocketReadableEvent> sockevent);

    /**
     * Execute a callback when a socket becomes writeable
     */
    void Register(std::shared_ptr<SocketWriteableEvent> sockevent);
    void Cancel(std::shared_ptr<SocketWriteableEvent> sockevent);

    /**
     * Execute a callback after a specified amount of time.
     */
    void Register(std::shared_ptr<TimerEvent> event);
    void Cancel(std::shared_ptr<TimerEvent> event);


    /**
     * Dispatch function F to the ActiveObject.
     * This will bypass the Reactor.
     */
    void Dispatch(Function f) override;

  private:

    Proactor(const Proactor&) = delete;
    Proactor& operator=(const Proactor&) = delete;

    void ReRegisterRead(qcc::SocketFd fd);
    void ReRegisterWrite(qcc::SocketFd fd);

    Reactor reactor;
    ActiveObject activeObject;

    std::map<qcc::SocketFd, std::shared_ptr<SocketReadableEvent> > readEvents;
    std::mutex readEventsLock;

    std::map<qcc::SocketFd, std::shared_ptr<SocketWriteableEvent> > writeEvents;
    std::mutex writeEventsLock;
};

}

#endif /* NIO_PROACTOR_H_ */
