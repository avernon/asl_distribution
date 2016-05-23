/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

#include <alljoyn/gateway/GatewayBusListener.h>
#include "GatewayConstants.h"
#include <algorithm>

namespace ajn {
namespace gw {

GatewayBusListener::GatewayBusListener(BusAttachment* bus, void(*daemonDisconnectCB)()) :
    m_SessionPort(0), m_Bus(bus), m_DaemonDisconnectCB(daemonDisconnectCB)
{
}

GatewayBusListener::~GatewayBusListener()
{
}

void GatewayBusListener::setSessionPort(SessionPort sessionPort)
{
    m_SessionPort = sessionPort;
}

SessionPort GatewayBusListener::getSessionPort()
{
    return m_SessionPort;
}

bool GatewayBusListener::AcceptSessionJoiner(SessionPort sessionPort, const char* joiner, const SessionOpts& opts)
{
    if (sessionPort != m_SessionPort) {
        return false;
    }

    QCC_DbgPrintf(("Accepting JoinSessionRequest"));
    return true;
}

void GatewayBusListener::SessionJoined(SessionPort sessionPort, SessionId sessionId, const char* joiner)
{
    if (m_Bus) {
        m_Bus->SetSessionListener(sessionId, this);
    }
    if (std::find(m_SessionIds.begin(), m_SessionIds.end(), sessionId) != m_SessionIds.end()) {
        return;
    }
    m_SessionIds.push_back(sessionId);
}

void GatewayBusListener::SessionMemberAdded(SessionId sessionId, const char* uniqueName)
{
    if (std::find(m_SessionIds.begin(), m_SessionIds.end(), sessionId) != m_SessionIds.end()) {
        return;
    }
    m_SessionIds.push_back(sessionId);
}

void GatewayBusListener::SessionMemberRemoved(SessionId sessionId, const char* uniqueName)
{
    std::vector<SessionId>::iterator it = std::find(m_SessionIds.begin(), m_SessionIds.end(), sessionId);
    if (it != m_SessionIds.end()) {
        m_SessionIds.erase(it);
    }
}

void GatewayBusListener::SessionLost(SessionId sessionId, SessionLostReason reason)
{
    std::vector<SessionId>::iterator it = std::find(m_SessionIds.begin(), m_SessionIds.end(), sessionId);
    if (it != m_SessionIds.end()) {
        m_SessionIds.erase(it);
    }
}

void GatewayBusListener::BusDisconnected()
{
    if (m_DaemonDisconnectCB) {
        m_DaemonDisconnectCB();
    }
}

const std::vector<SessionId>& GatewayBusListener::getSessionIds() const
{
    return m_SessionIds;
}

} /* namespace gw */
} /* namespace ajn */
