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

#ifndef SRPKEYLISTENER_H_
#define SRPKEYLISTENER_H_

#include <alljoyn/AuthListener.h>

#if defined(QCC_OS_GROUP_WINDOWS)
/* Disabling warning C 4100. Function doesnt use all passed in parameters */
#pragma warning(push)
#pragma warning(disable: 4100)
#endif


/**
 * class SrpKeyXListener
 * A listener for Authentication
 */
class SrpKeyXListener : public ajn::AuthListener {
  public:
    /**
     * SrpKeyXListener
     */
    SrpKeyXListener();

    /**
     * ~SrpKeyXListener
     */
    virtual ~SrpKeyXListener();

    /**
     * setPassCode
     * @param passCode to set
     */
    void setPassCode(qcc::String const& passCode);

    /**
     * setGetPassCode
     * @param getPassCode - callback function to set
     */
    void setGetPassCode(void (*getPassCode)(qcc::String&));

    /**
     * RequestCredentials
     * @param authMechanism
     * @param authPeer
     * @param authCount
     * @param userId
     * @param credMask
     * @param creds
     * @return boolean
     */
    bool RequestCredentials(const char* authMechanism, const char* authPeer, uint16_t authCount, const char* userId,
                            uint16_t credMask, Credentials& creds);

    /**
     * AuthenticationComplete
     * @param authMechanism
     * @param authPeer
     * @param success
     */
    void AuthenticationComplete(const char* authMechanism, const char* authPeer, bool success);

  private:
    qcc::String m_PassCode;

    void (*m_GetPassCode)(qcc::String&);
};

#endif /* SRPKEYLISTENER_H_ */


