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

#include <alljoyn/controlpanel/ControlPanelBusListener.h>
#include <iostream>
#include <algorithm>
#include <alljoyn/controlpanel/LogModule.h>

namespace ajn {
namespace services {

ControlPanelBusListener::ControlPanelBusListener() :
    BusListener(), SessionPortListener(), SessionListener(), m_SessionPort(0)
{
}

ControlPanelBusListener::~ControlPanelBusListener()
{
}

void ControlPanelBusListener::setSessionPort(ajn::SessionPort sessionPort)
{
    m_SessionPort = sessionPort;
}

SessionPort ControlPanelBusListener::getSessionPort()
{
    return m_SessionPort;
}

bool ControlPanelBusListener::AcceptSessionJoiner(ajn::SessionPort sessionPort, const char* joiner, const ajn::SessionOpts& opts)
{
    QCC_UNUSED(joiner);
    QCC_UNUSED(opts);
    if (sessionPort != m_SessionPort) {
        return false;
    }

    QCC_DbgPrintf(("Accepting JoinSessionRequest"));
    return true;
}

void ControlPanelBusListener::SessionJoined(SessionPort sessionPort, SessionId sessionId, const char* joiner)
{
    QCC_UNUSED(sessionPort);
    QCC_UNUSED(joiner);
    if (std::find(m_SessionIds.begin(), m_SessionIds.end(), sessionId) != m_SessionIds.end()) {
        return;
    }
    m_SessionIds.push_back(sessionId);
}

void ControlPanelBusListener::SessionMemberAdded(SessionId sessionId, const char* uniqueName)
{
    QCC_UNUSED(uniqueName);
    if (std::find(m_SessionIds.begin(), m_SessionIds.end(), sessionId) != m_SessionIds.end()) {
        return;
    }
    m_SessionIds.push_back(sessionId);
}

void ControlPanelBusListener::SessionMemberRemoved(SessionId sessionId, const char* uniqueName)
{
    QCC_UNUSED(uniqueName);
    std::vector<SessionId>::iterator it = std::find(m_SessionIds.begin(), m_SessionIds.end(), sessionId);
    if (it != m_SessionIds.end()) {
        m_SessionIds.erase(it);
    }
}

void ControlPanelBusListener::SessionLost(SessionId sessionId, SessionLostReason reason)
{
    QCC_UNUSED(reason);
    std::vector<SessionId>::iterator it = std::find(m_SessionIds.begin(), m_SessionIds.end(), sessionId);
    if (it != m_SessionIds.end()) {
        m_SessionIds.erase(it);
    }
}

const std::vector<SessionId>& ControlPanelBusListener::getSessionIds() const
{
    return m_SessionIds;
}

} /* namespace services */
} /* namespace ajn */
