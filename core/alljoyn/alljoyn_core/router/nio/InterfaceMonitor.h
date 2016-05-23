/*
 * InterfaceMonitor.h
 *
 *  Created on: Apr 1, 2015
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
#ifndef _ALLJOYN_INTERFACEMONITOR_H_
#define _ALLJOYN_INTERFACEMONITOR_H_

#ifndef __cplusplus
#error Only include TCPTransport.h in C++ code.
#endif

#include "SocketReadableEvent.h"

#include <list>
#include <map>
#include <mutex>
#include <functional>
#include <memory>

#include <qcc/IfConfig.h>

#ifdef QCC_OS_GROUP_WINDOWS
#include <ws2ipdef.h>
#include <iphlpapi.h>
#endif

namespace nio {

class Proactor;

class InterfaceMonitor {
  public:

    typedef std::function<void (const std::vector<qcc::IfConfigEntry>&)> IFCallback;

    InterfaceMonitor(Proactor& p);

    virtual ~InterfaceMonitor();

    void AddCallback(IFCallback cb);

  private:

    void Notify(const std::vector<qcc::IfConfigEntry>& entries);

    void DoInterfaceCheck();

    Proactor& proactor;

    void Register();

#ifdef QCC_OS_GROUP_POSIX
    void OnChange(qcc::SocketFd sock, QStatus status);

    qcc::SocketFd networkEventFd;
    std::shared_ptr<SocketReadableEvent> readEvent;
#elif defined QCC_OS_GROUP_WINDOWS
    HANDLE networkIfaceHandle;

    static VOID WINAPI IpInterfaceChangeCallback(PVOID arg, PMIB_IPINTERFACE_ROW row, MIB_NOTIFICATION_TYPE notificationType);
#endif

    typedef std::list<IFCallback> InterfaceMonitorCallbackList;
    InterfaceMonitorCallbackList m_callbacks;
    std::mutex m_callbacksLock;
};

} // namespace ajn

#endif /* _ALLJOYN_INTERFACEMONITOR_H_ */
