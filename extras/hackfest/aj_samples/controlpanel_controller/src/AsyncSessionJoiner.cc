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

#include "AsyncSessionJoiner.h"
#include "SessionListenerImpl.h"
#include <iostream>

using namespace ajn;

AsyncSessionJoiner::AsyncSessionJoiner(const char* name, SessionJoinedCallback callback) :
    m_Busname(""), m_Callback(callback)
{
    if (name) {
        m_Busname.assign(name);
    }
}

AsyncSessionJoiner::~AsyncSessionJoiner()
{

}

void AsyncSessionJoiner::JoinSessionCB(QStatus status, SessionId id, const SessionOpts& opts, void* context)
{
    if (status == ER_OK) {
        std::cout << "JoinSessionCB(" << m_Busname.c_str() << ") succeeded with id" << id << std::endl;
        if (m_Callback) {
            std::cout << "Calling SessionJoiner Callback" << std::endl;
            m_Callback(m_Busname, id);
        }
    } else {
        std::cout << "JoinSessionCB(" << m_Busname.c_str() << ") failed with status: " << QCC_StatusText(status) << std::endl;
    }

    SessionListenerImpl* listener = (SessionListenerImpl*) context;
    delete listener;
    delete this;
}
