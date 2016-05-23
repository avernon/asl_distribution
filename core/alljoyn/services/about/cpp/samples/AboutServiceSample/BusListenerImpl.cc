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

#include "BusListenerImpl.h"
#include <iostream>

using namespace ajn;

BusListenerImpl::BusListenerImpl() :
    BusListener(), SessionPortListener(), m_SessionPort(0)
{
}

BusListenerImpl::BusListenerImpl(ajn::SessionPort sessionPort) :
    BusListener(), SessionPortListener(), m_SessionPort(sessionPort)
{

}

BusListenerImpl::~BusListenerImpl()
{
}

void BusListenerImpl::setSessionPort(ajn::SessionPort sessionPort)
{
    m_SessionPort = sessionPort;
}

SessionPort BusListenerImpl::getSessionPort()
{
    return m_SessionPort;
}

bool BusListenerImpl::AcceptSessionJoiner(ajn::SessionPort sessionPort, const char* joiner, const ajn::SessionOpts& opts)
{
    if (sessionPort != m_SessionPort) {
        std::cout << "Rejecting join attempt on unexpected session port " << sessionPort << std::endl;
        return false;
    }

    std::cout << "Accepting JoinSessionRequest from " << joiner << " (opts.proximity= " << opts.proximity
              << ", opts.traffic=" << opts.traffic << ", opts.transports=" << opts.transports << ")." << std::endl;
    return true;
}
