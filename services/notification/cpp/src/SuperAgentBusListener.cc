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

#include "SuperAgentBusListener.h"
#include "Transport.h"
#include <alljoyn/notification/NotificationService.h>
#include <qcc/String.h>
#include <alljoyn/notification/LogModule.h>

namespace ajn {
namespace services {

SuperAgentBusListener::SuperAgentBusListener(ajn::BusAttachment* bus)
    : BusListener(), m_Bus(bus), m_SuperAgentBusUniqueName("")
{

}

SuperAgentBusListener::~SuperAgentBusListener()
{

}

void SuperAgentBusListener::FoundAdvertisedName(const char* name, TransportMask transport, const char* namePrefix)
{
    QCC_DbgPrintf(("FoundAdvertisedName name:%s", name));
    // We must enable concurrent callbacks since some of the calls below are blocking
    m_Bus->EnableConcurrentCallbacks();

    if (0 == strcmp(name, m_SuperAgentBusUniqueName.c_str())) {
        Transport::getInstance()->listenToSuperAgent(m_SuperAgentBusUniqueName.c_str());
    }
}

void SuperAgentBusListener::LostAdvertisedName(const char* name, TransportMask transport, const char* prefix)
{
    QCC_DbgTrace(("LostAdvertisedName"));
    if (0 == ::strcmp(name, m_SuperAgentBusUniqueName.c_str())) {
        Transport::getInstance()->cancelListenToSuperAgent(m_SuperAgentBusUniqueName.c_str());
    }
}

} //services
} //ajn
