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

#include "ContentBusListenerClient.h"
#include "ContentConstants.h"
#include <LogModule.h>

namespace mdf {

using namespace ajn;
using namespace qcc;

ContentBusListenerClient::ContentBusListenerClient(BusAttachment* busAttachment, SessionListener* sessionListener, SessionPort sessionPort, SessionId sessionId)
{
    QCC_DbgTrace(("Init - ContentBusListenerClient sessionId=%d,sessionPort=%d", sessionId, sessionPort));
    m_SessionId = sessionId;
    m_FoundAdvertisedName = false;
    m_BusAttachment = busAttachment;
    m_SessionListner = sessionListener;
}

ContentBusListenerClient::~ContentBusListenerClient()
{
}

bool ContentBusListenerClient::FoundAdvertisedName()
{
    return m_FoundAdvertisedName;
}

void ContentBusListenerClient::FoundAdvertisedName(const char* name, TransportMask transport, const char* namePrefix)
{
    QCC_DbgTrace(("FoundAdvertisedName name=%s", name));
    if (s_CONTENT_INTERFACE == name) {
        /* We found a remote bus that is advertising basic service's well-known name so connect to it. */
        /* Since we are in a callback we must enable concurrent callbacks before calling a synchronous method. */
        m_BusAttachment->EnableConcurrentCallbacks();

        SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);

        QStatus status = m_BusAttachment->JoinSession(name, m_SessionPort, m_SessionListner, m_SessionId, opts);
        if (status != ER_OK) {
            QCC_LogError(status, ("m_BusAttachment->JoinSession failed"));
            return;
        }

    }
    m_FoundAdvertisedName = true;
}

void ContentBusListenerClient::NameOwnerChanged(const char* busName, const char* previousOwner, const char* newOwner)
{
    QCC_DbgTrace(("NameOwnerChanged busName=%s, previous=%s, newOwner=%s", busName, previousOwner, newOwner));
    if (newOwner && (s_CONTENT_INTERFACE == busName)) {
        QCC_DbgTrace(("NameOwnerChanged: name='%s', oldOwner='%s', newOwner='%s'.\n",
                      busName,
                      previousOwner ? previousOwner : "<none>",
                      newOwner ? newOwner : "<none>"));
    }
}

} /* namespace mdf */
