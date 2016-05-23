/*
 * Proactor.cc
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
#include "Proactor.h"

#include "EventNotifier.h"
#include "SocketReadableEvent.h"
#include "SocketWriteableEvent.h"
#include "TimerEvent.h"

using namespace nio;

Proactor::Proactor(uint32_t num_threads) : activeObject(num_threads)
{
}

Proactor::~Proactor()
{
}

void Proactor::Run()
{
    reactor.Run();
}

void Proactor::Stop()
{
    reactor.Stop();
    activeObject.Stop();
}

void Proactor::Dispatch(Function f)
{
    activeObject.Dispatch(f);
}

void Proactor::Register(std::shared_ptr<EventNotifier> notifier)
{
    // push notifications directly to activeObject
    notifier->SetDispatcher(&activeObject);
}

void Proactor::Cancel(std::shared_ptr<EventNotifier> notifier)
{
    notifier->SetDispatcher(nullptr);
}


void Proactor::ReRegisterRead(qcc::SocketFd fd)
{
    std::shared_ptr<SocketReadableEvent> evt;

    {
        std::lock_guard<std::mutex> lock(readEventsLock);
        auto it = readEvents.find(fd);
        if (it != readEvents.end()) {
            evt = it->second;
        }
    }

    if (evt.get()) {
        // cancel our internal event wrapper
        reactor.Register(evt);
    }
}

void Proactor::Register(std::shared_ptr<SocketReadableEvent> sockevent)
{

    // this will be pushed to the activeObject thread pool
    auto fcn = [this, sockevent] (QStatus status) {
                   // make the user callback
                   sockevent->SetEnabled(true);
                   sockevent->Execute();
                   // re-register the read event

                   if (status == ER_OK) {
                       ReRegisterRead(sockevent->GetSocket());
                   }
               };

    // fcn2 will be called from the
    auto fcn2 = [this, sockevent, fcn] (qcc::SocketFd, QStatus status) {
                    // make sure Reactor doesn't continue to poll this socket for readable
                    // until *AFTER* the user callback has completed.
                    sockevent->SetEnabled(false);
                    sockevent->SetStatus(status);
                    reactor.Cancel(sockevent);
                    activeObject.Dispatch(std::bind(fcn, status));
                };

    auto evt = std::make_shared<SocketReadableEvent>(sockevent->GetSocket(), fcn2);

    {
        std::lock_guard<std::mutex> lock(readEventsLock);
        readEvents[sockevent->GetSocket()] = evt;
    }

    reactor.Register(evt);
}

void Proactor::Cancel(std::shared_ptr<SocketReadableEvent> sockevent)
{
    sockevent->SetEnabled(false);

    std::shared_ptr<SocketReadableEvent> evt;

    {
        std::lock_guard<std::mutex> lock(readEventsLock);
        auto it = readEvents.find(sockevent->GetSocket());
        if (it != readEvents.end()) {
            evt = it->second;
            readEvents.erase(it);
        }
    }

    if (evt.get()) {
        // cancel our internal event wrapper
        reactor.Cancel(evt);
    }
}


void Proactor::ReRegisterWrite(qcc::SocketFd fd)
{
    std::shared_ptr<SocketWriteableEvent> evt;

    {
        std::lock_guard<std::mutex> lock(writeEventsLock);
        auto it = writeEvents.find(fd);
        if (it != writeEvents.end()) {
            evt = it->second;
        }
    }

    if (evt.get()) {
        // cancel our internal event wrapper
        reactor.Register(evt);
    }
}

void Proactor::Register(std::shared_ptr<SocketWriteableEvent> sockevent)
{
    // this will be pushed to the activeObject thread pool
    auto fcn = [this, sockevent] (QStatus status) {
                   sockevent->SetEnabled(true);
                   // make the user callback
                   sockevent->Execute();
                   // re-register the read event
                   if (status == ER_OK) {
                       ReRegisterWrite(sockevent->GetSocket());
                   }
               };

    // fcn2 will be called from the
    auto fcn2 = [this, sockevent, fcn] (qcc::SocketFd, QStatus status) {
                    // make sure Reactor doesn't continue to poll this socket for readable
                    // until *AFTER* the user callback has completed.
                    sockevent->SetEnabled(false);
                    sockevent->SetStatus(status);
                    reactor.Cancel(sockevent);
                    activeObject.Dispatch(std::bind(fcn, status));
                };

    auto evt = std::make_shared<SocketWriteableEvent>(sockevent->GetSocket(), fcn2);

    {
        std::lock_guard<std::mutex> lock(writeEventsLock);
        writeEvents[sockevent->GetSocket()] = evt;
    }

    reactor.Register(evt);
}

void Proactor::Cancel(std::shared_ptr<SocketWriteableEvent> sockevent)
{
    sockevent->SetEnabled(false);
    std::shared_ptr<SocketWriteableEvent> evt;

    {
        std::lock_guard<std::mutex> lock(writeEventsLock);
        auto it = writeEvents.find(sockevent->GetSocket());
        if (it != writeEvents.end()) {
            evt = it->second;
            writeEvents.erase(it);
        }
    }

    if (evt.get()) {
        // cancel our internal event wrapper
        reactor.Cancel(evt);
    }
}


void Proactor::Register(std::shared_ptr<TimerEvent> event)
{
    auto func1 = [event] () {
                     event->Execute();
                 };
    auto func2 = [this, func1] (TimerManager::TimerId) {
                     activeObject.Dispatch(func1);
                 };
    TimerManager::TimerId id = reactor.timerManager.AddTimer(event->GetFirst(), func2, event->GetRepeat());
    // need to restart the epoll loop
    reactor.SignalReactor();
    // we need to hold on to the id so we can cancel!
    event->SetId(id);
}

void Proactor::Cancel(std::shared_ptr<TimerEvent> event)
{
    reactor.Cancel(event);
}
