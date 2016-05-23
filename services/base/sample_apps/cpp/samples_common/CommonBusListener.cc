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

#include "CommonBusListener.h"
#include <iostream>
#include <algorithm>

using namespace ajn;

CommonBusListener::CommonBusListener(ajn::BusAttachment* bus, void(*daemonDisconnectCB)()) :
    BusListener(), SessionPortListener(), m_SessionPort(0), m_Bus(bus), m_DaemonDisconnectCB(daemonDisconnectCB)
{
}

CommonBusListener::~CommonBusListener()
{
}

void CommonBusListener::setSessionPort(ajn::SessionPort sessionPort)
{
    m_SessionPort = sessionPort;
}

SessionPort CommonBusListener::getSessionPort()
{
    return m_SessionPort;
}

bool CommonBusListener::AcceptSessionJoiner(ajn::SessionPort sessionPort, const char* joiner, const ajn::SessionOpts& opts)
{
    QCC_UNUSED(joiner);
    QCC_UNUSED(opts);
    if (sessionPort != m_SessionPort) {
        return false;
    }

    std::cout << "Accepting JoinSessionRequest" << std::endl;
    return true;
}

void CommonBusListener::SessionJoined(SessionPort sessionPort, SessionId id, const char* joiner)
{
    QCC_UNUSED(sessionPort);
    QCC_UNUSED(joiner);
    std::cout << "Session has been joined successfully" << std::endl;
    if (m_Bus) {
        m_Bus->SetSessionListener(id, this);
    }
    m_SessionIds.push_back(id);
}

void CommonBusListener::SessionLost(SessionId sessionId, SessionLostReason reason)
{
    QCC_UNUSED(reason);
    std::cout << "Session has been lost" << std::endl;
    std::vector<SessionId>::iterator it = std::find(m_SessionIds.begin(), m_SessionIds.end(), sessionId);
    if (it != m_SessionIds.end()) {
        m_SessionIds.erase(it);
    }
}

void CommonBusListener::BusDisconnected()
{
    std::cout << "Bus has been disconnected" << std::endl;
    if (m_DaemonDisconnectCB) {
        m_DaemonDisconnectCB();
    }
}

const std::vector<SessionId>& CommonBusListener::getSessionIds() const
{
    return m_SessionIds;
}
