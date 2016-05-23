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

#include <LSFKeyListener.h>
#include <qcc/Debug.h>

#define QCC_MODULE "LSF_KEY_LISTENER"
using namespace lsf;

LSFKeyListener::LSFKeyListener() : passCode("000000"), GetPassCode(0)
{
    QCC_DbgTrace(("%s", __func__));
}

LSFKeyListener::~LSFKeyListener()
{
    QCC_DbgTrace(("%s", __func__));
    passCode.secure_clear();
}

void LSFKeyListener::SetPassCode(qcc::String const& code)
{
    QCC_DbgTrace(("%s", __func__));
    passCode = code;
}

void LSFKeyListener::SetGetPassCodeFunc(const char* (*GetPassCodeFunc)())
{
    QCC_DbgTrace(("%s", __func__));
    GetPassCode = GetPassCodeFunc;
}

bool LSFKeyListener::RequestCredentials(const char* authMechanism, const char* authPeer,
                                        uint16_t authCount, const char* userId, uint16_t credMask, Credentials& creds)
{
    QCC_DbgTrace(("%s", __func__));
    if (strcmp(authMechanism, "ALLJOYN_ECDHE_PSK") == 0 || strcmp(authMechanism, "ALLJOYN_PIN_KEYX") == 0) {
        if (credMask & AuthListener::CRED_PASSWORD) {
            if (authCount <= 3) {
                const char* passCodeFromGet = 0;
                if (GetPassCode) {
                    passCodeFromGet = GetPassCode();
                }
                creds.SetPassword(passCodeFromGet ? passCodeFromGet : passCode.c_str());
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

void LSFKeyListener::AuthenticationComplete(const char* authMechanism, const char* authPeer, bool success)
{
    QCC_DbgTrace(("%s", __func__));
}
