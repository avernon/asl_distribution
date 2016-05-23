/******************************************************************************
 * Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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
#include <iostream>

SrpKeyXListener::SrpKeyXListener() : m_PassCode("000000"), m_GetPassCode(0)
{


}

SrpKeyXListener::~SrpKeyXListener()
{

}

void SrpKeyXListener::setPassCode(qcc::String const& passCode)
{
    m_PassCode = passCode;
}

void SrpKeyXListener::setGetPassCode(const char* (*getPassCode)())
{
    m_GetPassCode = getPassCode;
}

bool SrpKeyXListener::RequestCredentials(const char* authMechanism, const char* authPeer,
                                         uint16_t authCount, const char* userId, uint16_t credMask, Credentials& creds)
{
    std::cout << "RequestCredentials for authenticating " << authPeer << " using mechanism " << authMechanism << std::endl;
    if (strcmp(authMechanism, "ALLJOYN_SRP_KEYX") == 0 || strcmp(authMechanism, "ALLJOYN_PIN_KEYX") == 0) {
        if (credMask & AuthListener::CRED_PASSWORD) {
            if (authCount <= 3) {
                const char* passCodeFromGet = 0;
                if (m_GetPassCode) {
                    passCodeFromGet = m_GetPassCode();
                }
                std::cout << "RequestCredentials setPasscode to " << (passCodeFromGet ? passCodeFromGet : m_PassCode.c_str()) << std::endl;
                creds.SetPassword(passCodeFromGet ? passCodeFromGet : m_PassCode.c_str());
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
    std::cout << "Authentication with " << authMechanism << (success ? " was successful" : " failed") << std::endl;
}
