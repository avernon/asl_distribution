/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#include "ContentSourceClient.h"
#include "LogModule.h"

namespace mdf {

ContentSourceClient::ContentSourceClient(BusAttachment* busAttachment, String busName, SessionId sessionId, SessionPort sessionPort) : m_BusAttachment(busAttachment), m_BusName(busName),  m_SessionId(sessionId), m_SessionPort(sessionPort), m_HasSession(false), m_ContentProxyBusObject(NULL), m_SessionOpts(NULL)
{
    QCC_DbgTrace(("ContentSourceClient: created"));

    m_ContentProxyBusObject = NULL;
    m_SessionOpts = new SessionOpts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
    m_ContentProxyBusObject = new ContentProxyBusObject(m_BusAttachment, m_BusName, m_SessionId);
}

ContentSourceClient::~ContentSourceClient()
{
    QCC_DbgTrace(("ContentSourceClient: Destructor"));

    delete m_SessionOpts;
    delete m_ContentProxyBusObject;
}

uint16_t ContentSourceClient::GetVersion()
{
    return m_Version;
}

void ContentSourceClient::SetVersion(uint16_t version)
{
    m_Version = version;
}

bool ContentSourceClient::GetHasSession()
{
    QCC_DbgTrace(("ContentSourceClient::GetHasSession"));
    return m_HasSession;
}

SessionListener* ContentSourceClient::GetSessionListener()
{
    QCC_DbgTrace(("ContentSourceClient::GetSessionListener=%ld", this));
    return this;
}

void ContentSourceClient::SetHasSession(bool hasSession)
{
    m_HasSession = hasSession;
}

//SessionListener
void ContentSourceClient::SessionLost(SessionId sessionId, SessionLostReason reason)
{
    QCC_DbgTrace(("ContentSourceClient::SessionLost"));
    SetHasSession(false);
}

QStatus ContentSourceClient::JoinSession()
{
    QCC_DbgTrace(("ContentSourceClient::JoinSession"));
    QStatus status = m_BusAttachment->JoinSession(m_BusName.c_str(), m_SessionPort, GetSessionListener(), m_SessionId, *m_SessionOpts);
    if (status != ER_OK) {
        QCC_LogError(status, ("ContentSourceClient: Failed to join session"));
        return status;
    }

    QCC_DbgTrace(("ContentSourceClient::JoinSession2"));
    SetHasSession(true);

    return ER_OK;
}

ContentProxyBusObject* ContentSourceClient::GetContentProxyBusObject()
{
    return m_ContentProxyBusObject;
}

} //mdf