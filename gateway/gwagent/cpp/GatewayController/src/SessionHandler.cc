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

#include <alljoyn/gateway/SessionHandler.h>
#include <alljoyn/gateway/GatewayMgmtApp.h>
#include "Constants.h"
#include <sstream>
#include <alljoyn/gateway/LogModule.h>

namespace ajn {
namespace gwc {
using namespace gwcConsts;


SessionHandler::SessionHandler(GatewayMgmtApp* gateway) : m_SessionId(0), m_Gateway(gateway)
{

}

SessionHandler::~SessionHandler()
{
}


void SessionHandler::SessionLost(ajn::SessionId sessionId)
{
    QCC_DbgPrintf(("Session lost for sessionId: %u", sessionId));
    m_SessionId = 0;

    ajn::gwc::SessionListener* listener = m_Gateway->getListener();
    if (listener) {
        listener->sessionLost(m_Gateway);
    }
}

void SessionHandler::JoinSessionCB(QStatus status, ajn::SessionId id, const ajn::SessionOpts& opts, void* context)
{
    ajn::gwc::SessionListener* listener = m_Gateway->getListener();

    if (status != ER_OK) {
        QCC_LogError(status, ("Joining session failed."));

        if (listener) {
            listener->sessionLost(m_Gateway);
        }
        return;
    }

    QCC_DbgPrintf(("Joining session succeeded. SessionId: %u", id));

    m_SessionId = id;

    if (listener) {
        listener->sessionEstablished(m_Gateway);
    }
}

ajn::SessionId SessionHandler::getSessionId() const
{
    return m_SessionId;
}

}     /* namespace gwc */
} /* namespace ajn */
