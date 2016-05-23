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

#ifdef _WIN32
/* Disable deprecation warnings */
#pragma warning(disable: 4996)
#endif

#include <alljoyn/controlpanel/ControlPanelSessionHandler.h>
#include <alljoyn/controlpanel/ControlPanelDevice.h>
#include <alljoyn/controlpanel/ControlPanelService.h>
#include "ControlPanelConstants.h"
#include <sstream>
#include <alljoyn/controlpanel/LogModule.h>

namespace ajn {
namespace services {
using namespace cpsConsts;


ControlPanelSessionHandler::ControlPanelSessionHandler(ControlPanelDevice* device) : m_SessionId(0), m_Device(device)
{

}

ControlPanelSessionHandler::~ControlPanelSessionHandler()
{
}


void ControlPanelSessionHandler::SessionLost(ajn::SessionId sessionId)
{
    QCC_UNUSED(sessionId); //session id only used in debug build
    QCC_DbgPrintf(("Session lost for sessionId: %u", sessionId));
    m_SessionId = 0;

    ControlPanelListener* listener = m_Device->getListener();
    if (listener) {
        listener->sessionLost(m_Device);
    }
}

void ControlPanelSessionHandler::JoinSessionCB(QStatus status, ajn::SessionId id, const ajn::SessionOpts& opts, void* context)
{
    QCC_UNUSED(opts);
    QCC_UNUSED(context);
    if (status != ER_OK) {
        QCC_LogError(status, ("Joining session failed."));
        ControlPanelListener* listener = m_Device->getListener();
        if (listener) {
            listener->errorOccured(m_Device, status, SESSION_JOIN, "Could not join session");
        }
        return;
    }

    QCC_DbgPrintf(("Joining session succeeded. SessionId: %u", id));

    m_SessionId = id;
    m_Device->handleSessionJoined();
}

ajn::SessionId ControlPanelSessionHandler::getSessionId() const
{
    return m_SessionId;
}

} /* namespace services */
} /* namespace ajn */
