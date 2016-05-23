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

#include "NotificationProducerListener.h"
#include <iostream>
#include <algorithm>
#include <alljoyn/notification/NotificationService.h>
#include "NotificationConstants.h"
#include <alljoyn/notification/LogModule.h>

using namespace ajn;
using namespace services;
using namespace qcc;
using namespace nsConsts;

NotificationProducerListener::NotificationProducerListener() :
    SessionPortListener(), m_SessionPort(0)
{
}

NotificationProducerListener::~NotificationProducerListener()
{
}

void NotificationProducerListener::setSessionPort(ajn::SessionPort sessionPort)
{
    m_SessionPort = sessionPort;
}

SessionPort NotificationProducerListener::getSessionPort()
{
    return m_SessionPort;
}

bool NotificationProducerListener::AcceptSessionJoiner(ajn::SessionPort sessionPort, const char* joiner, const ajn::SessionOpts& opts)
{
    if (sessionPort != m_SessionPort) {
        return false;
    }

    QCC_DbgPrintf(("NotificationProducerListener::AcceptSessionJoiner() sessionPort=%hu joiner:%s", sessionPort, joiner));
    return true;
}

void NotificationProducerListener::SessionJoined(SessionPort sessionPort, SessionId sessionId, const char* joiner)
{

}
