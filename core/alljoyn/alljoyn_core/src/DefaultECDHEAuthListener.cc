/**
 * @file
 * The implementation of the the default auth listener.
 */

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

#include <qcc/platform.h>
#include <qcc/String.h>
#include <qcc/Debug.h>

#include <alljoyn/AuthListener.h>

#define QCC_MODULE "ALLJOYN_AUTH"

using namespace std;
using namespace qcc;

namespace ajn {

DefaultECDHEAuthListener::DefaultECDHEAuthListener() : AuthListener(), psk(NULL), pskSize(0)
{
}

DefaultECDHEAuthListener::DefaultECDHEAuthListener(const uint8_t* psk, size_t pskSize) : AuthListener()
{
    assert(pskSize >= 16);  /* psk size should be 128 bits or longer */
    this->psk = new uint8_t[pskSize];
    assert(this->psk);
    memcpy(this->psk, psk, pskSize);
    this->pskSize = pskSize;
}


bool DefaultECDHEAuthListener::RequestCredentials(const char* authMechanism, const char* peerName, uint16_t authCount, const char* userName, uint16_t credMask, Credentials& credentials) {
    QCC_DbgTrace(("DefaultECDHEAuthListener::%s", __FUNCTION__));
    QCC_UNUSED(peerName);
    QCC_UNUSED(authCount);
    QCC_UNUSED(userName);
    QCC_UNUSED(credMask);
    QCC_UNUSED(credentials);
    if (strcmp(authMechanism, "ALLJOYN_ECDHE_NULL") == 0) {
        return true;
    } else if (strcmp(authMechanism, "ALLJOYN_ECDHE_PSK") == 0) {
        if (pskSize == 0) {
            return false;
        }
        qcc::String outPsk;
        outPsk.assign(reinterpret_cast<const char*>(psk), pskSize);
        credentials.SetPassword(outPsk);
        return true;
    } else if (strcmp(authMechanism, "ALLJOYN_ECDHE_ECDSA") == 0) {
        return true;
    }
    return false;
}

void DefaultECDHEAuthListener::AuthenticationComplete(const char* authMechanism, const char* peerName, bool success)
{
    QCC_DbgTrace(("DefaultECDHEAuthListener::%s", __FUNCTION__));
    QCC_UNUSED(authMechanism);
    QCC_UNUSED(peerName);
    QCC_UNUSED(success);
}

}
