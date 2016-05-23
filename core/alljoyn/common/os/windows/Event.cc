/*
 * @file
 *
 * Windows implementation of event
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
#include <qcc/platform.h>

#include <map>
#include <list>
#include <winsock2.h>
#include <ws2def.h>
#include <ws2ipdef.h>
#include <iphlpapi.h>
#include <windows.h>
#include <errno.h>
#include <time.h>

#include <qcc/Debug.h>
#include <qcc/Event.h>
#include <qcc/Mutex.h>
#include <qcc/Stream.h>
#include <qcc/Thread.h>
#include <qcc/time.h>
#include <qcc/Util.h>

using namespace std;

/** @internal */
#define QCC_MODULE "EVENT"

namespace qcc {

static const long READ_SET = FD_READ | FD_CLOSE | FD_ACCEPT;
static const long WRITE_SET = FD_WRITE | FD_CLOSE | FD_CONNECT;


VOID WINAPI IpInterfaceChangeCallback(PVOID arg, PMIB_IPINTERFACE_ROW row, MIB_NOTIFICATION_TYPE notificationType);

VOID CALLBACK IoEventCallback(PVOID arg, BOOLEAN TimerOrWaitFired);


void WINAPI IpInterfaceChangeCallback(PVOID arg, PMIB_IPINTERFACE_ROW row, MIB_NOTIFICATION_TYPE notificationType)
{
    Event* event = (Event*) arg;
    QCC_DbgHLPrintf(("Received network interface event type %u", notificationType));
    if (!::SetEvent(event->GetHandle())) {
        QCC_LogError(ER_OS_ERROR, ("Setting network interface event failed"));
    }
}

class IoEventMonitor {
  public:

    struct EventList {
        std::list<Event*> events;
        uint32_t fdSet;
        HANDLE ioEvent;
        HANDLE waitObject;
    };

    qcc::Mutex lock;

    /*
     * Mapping from socket handles to Event registrations
     */
    std::map<SocketFd, EventList*> eventMap;

    void RegisterEvent(Event* event) {
        SocketFd sock = event->GetFD();
        QCC_DbgHLPrintf(("RegisterEvent %s for fd %d (ioHandle=%d)", event->GetEventType() == Event::IO_READ ? "IO_READ" : "IO_WRITE", sock, event->GetHandle()));
        assert((event->GetEventType() == Event::IO_READ) || (event->GetEventType() == Event::IO_WRITE));

        lock.Lock();
        std::map<SocketFd, EventList*>::iterator iter = eventMap.find(sock);
        EventList*eventList;
        if (iter == eventMap.end()) {
            /* new IO */
            eventList = new EventList();
            eventList->ioEvent = WSACreateEvent();
            eventList->fdSet = 0;
            eventMap[sock] = eventList;
            if (RegisterWaitForSingleObject(&eventList->waitObject, eventList->ioEvent, IoEventCallback, (void*)sock, INFINITE, WT_EXECUTEINWAITTHREAD)) {
                QCC_DbgHLPrintf(("RegisterWaitForSingleObject %d", eventList->waitObject));
            } else {
                QCC_LogError(ER_OS_ERROR, ("RegisterWaitForSingleObject failed"));
            }
        } else {
            eventList = iter->second;
        }
        /*
         * Add the event to the list of events for this socket
         */
        eventList->events.push_back(event);
        /*
         * Check if the set of IO conditions being monitored has changed.
         */
        uint32_t fdSet = eventList->fdSet | ((event->GetEventType() == Event::IO_READ) ? READ_SET : WRITE_SET);
        if (eventList->fdSet != fdSet) {
            eventList->fdSet = fdSet;
            QCC_DbgHLPrintf(("WSAEventSelect %x", fdSet));
            WSAEventSelect(sock, eventList->ioEvent, fdSet);
        }
        lock.Unlock();
    }

    void DeregisterEvent(Event* event) {
        SocketFd sock = event->GetFD();

        QCC_DbgPrintf(("DeregisterEvent %s for fd %d", event->GetEventType() == Event::IO_READ ? "IO_READ" : "IO_WRITE", sock));
        assert((event->GetEventType() == Event::IO_READ) || (event->GetEventType() == Event::IO_WRITE));

        lock.Lock();
        std::map<SocketFd, EventList*>::iterator iter = eventMap.find(sock);
        if (iter != eventMap.end()) {
            EventList*eventList = iter->second;
            /*
             * Remove this event from the event list
             */
            eventList->events.remove(event);
            /*
             * Remove the eventList and clean up if all the events are gone.
             */
            if (eventList->events.empty()) {
                eventMap.erase(iter);
                WSAEventSelect(event->GetFD(), eventList->ioEvent, 0);
                /*
                 * Make sure event is not in a set state
                 */
                WSAResetEvent(eventList->ioEvent);
                /*
                 * Cannot be holding the lock while unregistering the wait because this can cause a
                 * deadlock if the wait callback is blocked waiting for the lock.
                 */
                QCC_DbgHLPrintf(("UnregisterWait %d", eventList->waitObject));
                lock.Unlock();
                UnregisterWait(eventList->waitObject);
                lock.Lock();
                WSACloseEvent(eventList->ioEvent);
                delete eventList;
            }
        } else {
            QCC_LogError(ER_OS_ERROR, ("eventList for fd %d missing from event map", event->GetFD()));
        }
        lock.Unlock();
    }

};

static uint64_t _alwaysSet[RequiredArrayLength(sizeof(Event), uint64_t)];
static uint64_t _neverSet[RequiredArrayLength(sizeof(Event), uint64_t)];
static IoEventMonitor* IoMonitor = NULL;
static bool initialized = false;

Event& Event::alwaysSet = (Event&)_alwaysSet;
Event& Event::neverSet = (Event&)_neverSet;

void Event::Init()
{
    if (!initialized) {
        new (&alwaysSet)Event(0, 0);
        new (&neverSet)Event(Event::WAIT_FOREVER, 0);
        IoMonitor = new IoEventMonitor;
        initialized = true;
    }
}

void Event::Shutdown()
{
    if (initialized) {
        delete IoMonitor;
        IoMonitor = NULL;
        neverSet.~Event();
        alwaysSet.~Event();
        initialized = false;
    }
}

VOID CALLBACK IoEventCallback(PVOID arg, BOOLEAN TimerOrWaitFired)
{
    SocketFd sock = (SocketFd)arg;
    IoMonitor->lock.Lock();
    std::map<SocketFd, IoEventMonitor::EventList*>::iterator iter = IoMonitor->eventMap.find(sock);
    if (iter != IoMonitor->eventMap.end()) {
        IoEventMonitor::EventList*eventList = iter->second;
        WSANETWORKEVENTS ioEvents;
        int ret = WSAEnumNetworkEvents(sock, eventList->ioEvent, &ioEvents);
        if (ret != 0) {
            QCC_LogError(ER_OS_ERROR, ("WSAEnumNetworkEvents returned %d", ret));
        } else {
            QCC_DbgHLPrintf(("IoEventCallback %x", ioEvents.lNetworkEvents));
            if (ioEvents.lNetworkEvents) {
                std::list<Event*>::iterator evit = eventList->events.begin();
                if (evit == eventList->events.end()) {
                    QCC_LogError(ER_OS_ERROR, ("Event list was empty"));
                }
                while (evit != eventList->events.end()) {
                    Event* ev = (*evit);
                    bool isSet = false;

                    if ((ioEvents.lNetworkEvents & WRITE_SET) && (ev->GetEventType() == Event::IO_WRITE)) {
                        isSet = true;
                        QCC_DbgHLPrintf(("Setting write event %d", ev->GetHandle()));
                    }
                    if ((ioEvents.lNetworkEvents & READ_SET) && (ev->GetEventType() == Event::IO_READ)) {
                        isSet = true;
                        QCC_DbgHLPrintf(("Setting read event %d", ev->GetHandle()));
                    }
                    if (isSet) {
                        if (!::SetEvent(ev->GetHandle())) {
                            QCC_LogError(ER_OS_ERROR, ("SetEvent returned %d", ret));
                        }
                    }
                    ++evit;
                }
            }
        }
    }
    IoMonitor->lock.Unlock();
}


QStatus AJ_CALL Event::Wait(Event& evt, uint32_t maxWaitMs, bool includeStopEvent)
{
    static const timeval toZero = { 0, 0 };
    HANDLE handles[3];
    int numHandles = 0;

    /*
     * The IO event is necessarily an auto-reset event. Calling select with a zero timeout to check
     * the I/O status before blocking ensures that Event::Wait is idempotent.
     */
    if ((evt.eventType == IO_READ) || (evt.eventType == IO_WRITE)) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(evt.ioFd, &fds);
        select(1, evt.eventType == IO_READ ? &fds : NULL, evt.eventType == IO_WRITE ? &fds : NULL, NULL, &toZero);
        if (FD_ISSET(evt.ioFd, &fds)) {
            ::SetEvent(evt.ioHandle);
        }
    }

    /*
     * The order of handle being added here is important because we want to prioritize the I/O handle.
     * In the event that multiple handles get set during the wait, we would get the prioritized one.
     * For example, if both the IO and stopEvent handles are set, this function would return ER_OK
     * instead of ER_ALERTED_THREAD.
     */
    if (nullptr != evt.ioHandle) {
        handles[numHandles++] = evt.ioHandle;
    } else if (nullptr != evt.handle) {
        handles[numHandles++] = evt.handle;
    } else if (nullptr != evt.timerHandle) {
        assert(TIMED == evt.eventType);
        handles[numHandles++] = evt.timerHandle;
    }

    Thread* thread = NULL;
    Event* stopEvent = NULL;
    if (includeStopEvent) {
        thread = Thread::GetThread();
        stopEvent = &thread->GetStopEvent();
        handles[numHandles++] = stopEvent->handle;
    }
    assert(numHandles <= ARRAYSIZE(handles));

    QStatus status = ER_OK;
    evt.IncrementNumThreads();
    DWORD ret = WaitForMultipleObjectsEx(numHandles, handles, FALSE, maxWaitMs, FALSE);
    evt.DecrementNumThreads();

    if ((ret >= WAIT_OBJECT_0) && (ret < (WAIT_OBJECT_0 + numHandles))) {
        if (handles[ret - WAIT_OBJECT_0] == stopEvent->handle) {
            status = (thread && thread->IsStopping()) ? ER_STOPPING_THREAD : ER_ALERTED_THREAD;
        } else {
            if (stopEvent && (handles[ret - WAIT_OBJECT_0] == stopEvent->handle)) {
                /* The wait returned due to stopEvent */
                status = ER_ALERTED_THREAD;
            } else {
                status = ER_TIMEOUT;
            }
        } else {
            QCC_DbgPrintf(("WaitForMultipleObjectsEx timeout %d", maxWaitMs));
            status = ER_TIMEOUT;
        }
    } else {
        status = ER_OS_ERROR;
        QCC_LogError(status, ("WaitForMultipleObjectsEx returned 0x%x.", ret));
        if (WAIT_FAILED == ret) {
            QCC_LogError(status, ("GetLastError=%d", GetLastError()));
            QCC_LogError(status, ("numHandles=%d, maxWaitMs=%d, Handles: ", numHandles, maxWaitMs));
            for (int i = 0; i < numHandles; ++i) {
                QCC_LogError(status, ("  0x%x", handles[i]));
            }
        }
    }
    return status;
}


QStatus Event::Wait(const vector<Event*>& checkEvents, vector<Event*>& signaledEvents, uint32_t maxWaitMs)
{
    static const timeval toZero = { 0, 0 };
    const int MAX_HANDLES = 64;

    int numHandles = 0;
    HANDLE handles[MAX_HANDLES];
    vector<Event*>::const_iterator it;

    for (it = checkEvents.begin(); it != checkEvents.end(); ++it) {
        Event* evt = *it;
        evt->IncrementNumThreads();
        if (INVALID_HANDLE_VALUE != evt->handle) {
            handles[numHandles++] = evt->handle;
            if (MAX_HANDLES <= numHandles) {
                break;
            }
        }
        if (INVALID_HANDLE_VALUE != evt->ioHandle) {
            handles[numHandles++] = evt->ioHandle;
            if (MAX_HANDLES <= numHandles) {
                break;
            }
        }
        if (evt->eventType == TIMED) {
            uint32_t now = GetTimestamp();
            if (evt->timestamp <= now) {
                maxWaitMs = 0;
            } else if ((WAIT_FOREVER == maxWaitMs) || ((evt->timestamp - now) < maxWaitMs)) {
                maxWaitMs = evt->timestamp - now;
            }
        }
        if ((evt->eventType == IO_READ) || (evt->eventType == IO_WRITE)) {
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(evt->ioFd, &fds);
            select(1, evt->eventType == IO_READ ? &fds : NULL, evt->eventType == IO_WRITE ? &fds : NULL, NULL, &toZero);
            if (FD_ISSET(evt->ioFd, &fds)) {
                ::SetEvent(evt->ioHandle);
            } else {
                /*
                 * FD_READ network event is level-triggered but not edge-triggered, This means that if the relevant network condition (data is available)
                 * is still valid after the application calls recv(), the network event is recorded and the associated event object is set.
                 * This expects the application routine to wait for the event object before it calls recv(). Unfortunately AllJoyn does not
                 * behave in that way: it may try to pull data one byte at a time; it also does not wait on the event object until recv()
                 * returns ER_WOULDBLOCK. This causes the problem that sometimes the event handle is signaled, but in fact the socket file
                 * descriptor is not in signaled state (FD_READ).
                 */
                ::ResetEvent(evt->ioHandle);
            }
        }
    }
    /* Restore thread counts if we are not going to block */
    if (numHandles >= MAX_HANDLES) {
        while (true) {
            Event* evt = *it;
            evt->DecrementNumThreads();
            if (it == checkEvents.begin()) {
                break;
            }
            --it;
        }
        QCC_LogError(ER_FAIL, ("Event::Wait: Maximum number of HANDLES reached"));
        return ER_FAIL;
    }
    bool somethingSet = true;
    DWORD ret = WAIT_FAILED;
    while (signaledEvents.empty() && somethingSet) {
        uint32_t orig = GetTimestamp();

        if (numHandles <= MAXIMUM_WAIT_OBJECTS) {
            assert(numHandles > 0);
            DWORD ret = WaitForMultipleObjectsEx(numHandles, handles.data(), FALSE, maxWaitMs, FALSE);

            /*
             * somethingSet will be true if the return value is between WAIT_OBJECT_0 and WAIT_OBJECT_0 + numHandles.
             * i.e. ret indicates that one of the handles passed in the array "handles" to WaitForMultipleObjectsEx
             * caused the function to return.
             */
            somethingSet = (ret >= WAIT_OBJECT_0) && (ret < (WAIT_OBJECT_0 + numHandles));
            timedOut = (WAIT_TIMEOUT == ret);

            if (WAIT_FAILED == ret) {
                QCC_LogError(ER_FAIL, ("WaitForMultipleObjectsEx(2) returned 0x%x, error=%d.", ret, GetLastError()));
            } else if (WAIT_ABANDONED == ret) {
                QCC_LogError(ER_FAIL, ("WaitForMultipleObjectsEx(2) returned WAIT_ABANDONED."));
            }
        } else {
            int32_t indexSignaled = -1;
            SuperWaiter waiter;
            status = waiter.Initialize();
            if (ER_OK == status) {
                status = waiter.WaitForMultipleObjects(numHandles, handles.data(), maxWaitMs, &indexSignaled);
                if (ER_OK == status) {
                    somethingSet = true;
                    timedOut = false;
                } else if (ER_TIMEOUT == status) {
                    somethingSet = false;
                    timedOut = true;
                }
            }
            if ((ER_OK != status) && (!timedOut)) {
                /* Restore thread counts if we did not block */
                for (it = checkEvents.begin(); it != checkEvents.end(); ++it) {
                    Event* evt = *it;
                    evt->DecrementNumThreads();
                }
                QCC_LogError(status, ("SuperWaiter::WaitForMultipleObjects: failed."));
                return ER_FAIL;
            }
        }

        for (it = checkEvents.begin(); it != checkEvents.end(); ++it) {
            Event* evt = *it;
            evt->DecrementNumThreads();

            if (somethingSet) {
                if (evt->eventType == TIMED) {
                    /*
                     * Avoid calling Wait() here: the Wait above already
                     * switched this timer to non-signaled state, so calling it
                     * again here would incorrectly return non-signaled.
                     */
                    if ((evt->timerHandle != nullptr) && (evt->timerHandle == signaledHandle)) {
                        signaledEvents.push_back(evt);
                    }
                } else if (ER_OK == Wait(*evt, 0, false)) {
                    signaledEvents.push_back(evt);
                }
            }
        }

        uint32_t now = GetTimestamp();
        /* Adjust the maxWaitMs by the time elapsed, in case we loop back up and call WaitForMultipleObjectsEx again. */
        maxWaitMs -= now - orig;
        /* If somethingSet is true, signaledEvents must not be empty here. But there are situations when WaitForMultipleObjectsEx
           can return even though the event is not set. So, if somethingSet is true, but signaledEvents is empty,
           we call WaitForMultipleObjectsEx again.
         */
    }

    QStatus status = ER_OK;
    if (somethingSet || (WAIT_TIMEOUT == ret)) {
        status = signaledEvents.empty() ? ER_TIMEOUT : ER_OK;
    } else {
        status = ER_FAIL;
        QCC_LogError(status, ("WaitForMultipleObjectsEx(2) returned 0x%x.", ret));
        if (WAIT_FAILED == ret) {
            QCC_LogError(status, ("GetLastError=%d", GetLastError()));
            QCC_LogError(status, ("numHandles=%d, maxWaitMs=%d, Handles: ", numHandles, maxWaitMs));
            for (int i = 0; i < numHandles; ++i) {
                QCC_LogError(status, ("  0x%x", handles[i]));
            }
        }
    }
    return status;
}

Event::Event() :
    handle(CreateEvent(NULL, TRUE, FALSE, NULL)),
    ioHandle(INVALID_HANDLE_VALUE),
    eventType(GEN_PURPOSE),
    timestamp(0),
    period(0),
    ioFd(INVALID_SOCKET_FD),
    numThreads(0),
    networkIfaceEvent(false),
    networkIfaceHandle(INVALID_HANDLE_VALUE)
{
}

Event::Event(bool networkIfaceEvent) :
    handle(CreateEvent(NULL, TRUE, FALSE, NULL)),
    ioHandle(INVALID_HANDLE_VALUE),
    eventType(GEN_PURPOSE),
    timestamp(0),
    period(0),
    ioFd(INVALID_SOCKET_FD),
    numThreads(0),
    networkIfaceEvent(networkIfaceEvent),
    networkIfaceHandle(INVALID_HANDLE_VALUE)
{
    if (networkIfaceEvent) {
        NotifyIpInterfaceChange(AF_UNSPEC, (PIPINTERFACE_CHANGE_CALLBACK)IpInterfaceChangeCallback, this, false, &networkIfaceHandle);
    }
}

Event::Event(Event& event, EventType eventType, bool genPurpose) :
    handle(INVALID_HANDLE_VALUE),
    ioHandle(INVALID_HANDLE_VALUE),
    eventType(eventType),
    timestamp(0),
    period(0),
    ioFd(event.ioFd),
    numThreads(0),
    networkIfaceEvent(false),
    networkIfaceHandle(INVALID_HANDLE_VALUE)
{
    /* Create an auto reset event for the socket fd */
    if (ioFd != INVALID_SOCKET_FD) {
        assert((eventType == IO_READ) || (eventType == IO_WRITE));
        ioHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
        IoMonitor->RegisterEvent(this);
    }
    if (genPurpose) {
        handle = CreateEvent(NULL, TRUE, FALSE, NULL);
    }
}

Event::Event(SocketFd ioFd, EventType eventType) :
    handle(INVALID_HANDLE_VALUE),
    ioHandle(INVALID_HANDLE_VALUE),
    eventType(eventType),
    timestamp(0),
    period(0),
    ioFd(ioFd),
    numThreads(0),
    networkIfaceEvent(false),
    networkIfaceHandle(INVALID_HANDLE_VALUE)
{
    /* Create an auto reset event for the socket fd */
    if (ioFd != INVALID_SOCKET_FD) {
        assert((eventType == IO_READ) || (eventType == IO_WRITE));
        ioHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
        IoMonitor->RegisterEvent(this);
    }
}

Event::Event(uint32_t timestamp, uint32_t period) :
    handle(INVALID_HANDLE_VALUE),
    ioHandle(INVALID_HANDLE_VALUE),
    eventType(TIMED),
    timestamp(WAIT_FOREVER == timestamp ? WAIT_FOREVER : GetTimestamp() + timestamp),
    period(period),
    ioFd(INVALID_SOCKET_FD),
    numThreads(0),
    networkIfaceEvent(false),
    networkIfaceHandle(INVALID_HANDLE_VALUE)
{
}

Event::~Event()
{
    /* Threads should not be waiting on this event */
    if ((handle != INVALID_HANDLE_VALUE) && !::SetEvent(handle)) {
        QCC_LogError(ER_FAIL, ("SetEvent failed with %d (%s)", GetLastError()));
    }
    if (TIMED == eventType) {
        timestamp = 0;
    }

    /* No longer monitoring I/O for this event */
    if (ioHandle != INVALID_HANDLE_VALUE) {
        IoMonitor->DeregisterEvent(this);
        CloseHandle(ioHandle);
    }

    /* Close the handles */
    if (handle != INVALID_HANDLE_VALUE) {
        CloseHandle(handle);
    }

    /* Cancel network change notification */
    if (networkIfaceEvent && networkIfaceHandle != INVALID_HANDLE_VALUE) {
        CancelMibChangeNotify2(networkIfaceHandle);
    }
}

QStatus Event::SetEvent()
{
    QStatus status = ER_OK;

    if (INVALID_HANDLE_VALUE != handle) {
        if (!::SetEvent(handle)) {
            status = ER_FAIL;
            QCC_LogError(status, ("SetEvent failed with %d", GetLastError()));
        }
    } else if (TIMED == eventType) {
        uint32_t now = GetTimestamp();
        if (now < timestamp) {
            if (0 < period) {
                timestamp -= (((now - timestamp) / period) + 1) * period;
            } else {
                timestamp = now;
            }
        }
        status = ER_OK;
    } else {
        /* Not a general purpose or timed event */
        status = ER_FAIL;
        QCC_LogError(status, ("Attempt to manually set an I/O event"));
    }
    return status;
}

QStatus Event::ResetEvent()
{
    QStatus status = ER_OK;

    if (INVALID_HANDLE_VALUE != handle) {
        if (!::ResetEvent(handle)) {
            status = ER_FAIL;
            QCC_LogError(status, ("ResetEvent failed with %d", GetLastError()));
        }
    } else if (TIMED == eventType) {
        if (0 < period) {
            uint32_t now = GetTimestamp();
            timestamp += (((now - timestamp) / period) + 1) * period;
        } else {
            timestamp = static_cast<uint32_t>(-1);
        }
    } else {
        /* Not a general purpose or timed event */
        status = ER_FAIL;
        QCC_LogError(status, ("Attempt to manually reset an I/O event"));
    }
    return status;
}

bool Event::IsSet()
{
    return (ER_TIMEOUT == Wait(*this, 0)) ? false : true;
}

void Event::ResetTime(uint32_t delay, uint32_t period)
{
    if (delay == WAIT_FOREVER) {
        this->timestamp = WAIT_FOREVER;
    } else {
        this->timestamp = GetTimestamp() + delay;
    }
    this->period = period;
}

}  /* namespace */

