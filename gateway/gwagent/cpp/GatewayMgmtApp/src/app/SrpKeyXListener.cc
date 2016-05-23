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

#include "SrpKeyXListener.h"
#include "../GatewayConstants.h"

using namespace ajn;
using namespace gw;

SrpKeyXListener::SrpKeyXListener() : m_PassCode("")
{
}

SrpKeyXListener::~SrpKeyXListener()
{
}

void SrpKeyXListener::setPassCode(qcc::String const& passCode)
{
    m_PassCode = passCode;
}

bool SrpKeyXListener::RequestCredentials(const char* authMechanism, const char* authPeer,
                                         uint16_t authCount, const char* userId, uint16_t credMask, Credentials& creds)
{
    QCC_DbgPrintf(("RequestCredentials for authenticating %s using mechanism %s", authPeer, authMechanism));
    if (strcmp(authMechanism, "ALLJOYN_SRP_KEYX") == 0 || strcmp(authMechanism, "ALLJOYN_PIN_KEYX") == 0 || strcmp(authMechanism, "ALLJOYN_ECDHE_PSK") == 0) {
        if (credMask & AuthListener::CRED_PASSWORD) {
            if (authCount <= 3) {
                QCC_DbgPrintf(("RequestCredentials setPasscode to %s", m_PassCode.c_str()));
                creds.SetPassword(m_PassCode.c_str());
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

void SrpKeyXListener::AuthenticationComplete(const char* authMechanism, const char* authPeer, bool success)
{
    QCC_DbgPrintf(("Authentication with %s %s", authMechanism, (success ? " was successful" : " failed")));
}
