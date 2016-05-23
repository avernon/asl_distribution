# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
#ifndef LSF_KEYLISTENER_H_
#define LSF_KEYLISTENER_H_
/**
 * \ingroup Common
 */
/**
 * \file  common/inc/LSFKeyListener.h
 * This file provides definitions for LSF key listener
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
/**
 * \ingroup Common
 */

#include <alljoyn/AuthListener.h>

namespace lsf {

/**
 * class SrpKeyXListener. \n
 * A listener for Authentication. \n
 * instance of that class is given by bus attachment EnablePeerSecurity().
 */
class LSFKeyListener : public ajn::AuthListener {
  public:
    /**
     * LSFKeyListener constructor
     */
    LSFKeyListener();

    /**
     * ~LSFKeyListener destructor
     */
    virtual ~LSFKeyListener();

    /**
     * SetPassCode - called by the application to set the password
     * @param code PassCode to set
     */
    void SetPassCode(qcc::String const& code);

    /**
     * SetGetPassCodeFunc
     * @param GetPassCodeFunc - callback function to set
     */
    void SetGetPassCodeFunc(const char* (*GetPassCodeFunc)());

    /**
     * Authentication mechanism requests user credentials. If the user name is not an empty string \n
     * the request is for credentials for that specific user. A count allows the listener to decide \n
     * whether to allow or reject multiple authentication attempts to the same peer. \n\n
     *
     * An implementation must provide RequestCredentials or RequestCredentialsAsync but not both. \n
     *
     * @param authMechanism  The name of the authentication mechanism issuing the request.
     * @param authPeer       The name of the remote peer being authenticated.  On the initiating
     *                       side this will be a well-known-name for the remote peer. On the
     *                       accepting side this will be the unique bus name for the remote peer.
     * @param authCount      Count (starting at 1) of the number of authentication request attempts made.
     * @param userId       The user name for the credentials being requested.
     * @param credMask       A bit mask identifying the credentials being requested. The application
     *                       may return none, some or all of the requested credentials.
     * @param[out] creds    The credentials returned.
     *
     * @return  The caller should return true if the request is being accepted or false if the
     *          requests is being rejected. If the request is rejected the authentication is
     *          complete.
     */
    bool RequestCredentials(const char* authMechanism, const char* authPeer, uint16_t authCount, const char* userId,
                            uint16_t credMask, Credentials& creds);

    /**
     * Reports successful or unsuccessful completion of authentication.
     *
     * @param authMechanism  The name of the authentication mechanism that was used or an empty
     *                       string if the authentication failed.
     * @param authPeer       The name of the remote peer being authenticated.  On the initiating
     *                       side this will be a well-known-name for the remote peer. On the
     *                       accepting side this will be the unique bus name for the remote peer.
     * @param success        true if the authentication was successful, otherwise false.
     */
    void AuthenticationComplete(const char* authMechanism, const char* authPeer, bool success);

  private:
    qcc::String passCode;

    const char* (*GetPassCode)();
};

}

#endif


