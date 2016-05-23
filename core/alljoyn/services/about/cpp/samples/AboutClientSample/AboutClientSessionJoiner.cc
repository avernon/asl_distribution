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

#include "AboutClientSessionJoiner.h"
#include "AboutClientSessionListener.h"
#include <iostream>

using namespace ajn;

AboutClientSessionJoiner::AboutClientSessionJoiner(BusAttachment& bus, const qcc::String& busName, SessionJoinedCallback callback) :
    bus(bus), m_BusName(busName), m_Callback(callback) {
}

AboutClientSessionJoiner::~AboutClientSessionJoiner()
{

}

void AboutClientSessionJoiner::JoinSessionCB(QStatus status, SessionId id, const SessionOpts& opts, void* context)
{
    if (status == ER_OK) {
        std::cout << "JoinSessionCB(" << m_BusName << ") succeeded with id: " << id << std::endl;
        if (m_Callback) {
            std::cout << "Calling SessionJoiner Callback" << std::endl;
            m_Callback(m_BusName, id);
        }
    } else {
        std::cout << "JoinSessionCB(" << m_BusName << ") failed with status: " << QCC_StatusText(status) << std::endl;
    }


    bus.SetSessionListener(id, NULL);

    AboutClientSessionListener* t = (AboutClientSessionListener*) context;
    delete t;
    delete this;
}
