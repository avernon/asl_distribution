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

#include "ContentServiceSessionHandler.h"
#include <LogModule.h>
#include <sstream>

using namespace ajn;
//using namespace services;

namespace mdf {

/**
 * Constructor for MySessionHandler
 */
ContentServiceSessionHandler::ContentServiceSessionHandler() : m_SessionId(0), m_HasJoined(false), TAG("MySessionHandler") {
}

/**
 * Destructor for MySessionHandler
 */
ContentServiceSessionHandler::~ContentServiceSessionHandler() {

    m_SessionId = 0;
    m_HasJoined = false;
}

/**
 * SessionLost
 * @param sessionId
 */
void ContentServiceSessionHandler::SessionLost(ajn::SessionId sessionId) {
    std::stringstream sessionIdStr;
    sessionIdStr << sessionId;
    QCC_DbgHLPrintf(("Session lost for sessionId: %s", sessionIdStr.str().c_str()));

    m_SessionId = 0;
}

/**
 * JoinSessionCB
 * @param status
 * @param id
 * @param opts
 * @param context
 */
void ContentServiceSessionHandler::JoinSessionCB(QStatus status, ajn::SessionId id, const ajn::SessionOpts& opts, void* context)
{
    if (status != ER_OK) {
        QCC_LogError(status, ("Joining session failed."));
        return;
    }
    std::stringstream sessionIdStr;
    sessionIdStr << id;
    QCC_DbgHLPrintf(("Joining session succeeded. SessionId:  %s", sessionIdStr.str().c_str()));

    m_SessionId = id;
    m_HasJoined = true;
}

bool ContentServiceSessionHandler::HasJoined() {
    return m_HasJoined;
}

} //end ajn
