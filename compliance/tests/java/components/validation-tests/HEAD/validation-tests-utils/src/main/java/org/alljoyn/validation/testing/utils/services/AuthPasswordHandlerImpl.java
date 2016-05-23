/*******************************************************************************
 *  Copyright AllSeen Alliance. All rights reserved.
 *
 *     Contributed by Qualcomm Connected Experiences, Inc.,
 *     with authorization from the AllSeen Alliance, Inc.
 *     
 *     Licensed under the Apache License, Version 2.0 (the "License");
 *     you may not use this file except in compliance with the License.
 *     You may obtain a copy of the License at
 *     
 *         http://www.apache.org/licenses/LICENSE-2.0
 *     
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 *     
 *     Pursuant to Section 1 of the License, the work of authorship constituting
 *     a Work and any Contribution incorporated in the Work shall mean only that
 *     Contributor's code submissions authored by that Contributor.  Any rights
 *     granted under the License are conditioned upon acceptance of these
 *     clarifications.
 *******************************************************************************/
package org.alljoyn.validation.testing.utils.services;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

import org.alljoyn.services.android.security.AuthPasswordHandler;
import org.alljoyn.services.android.security.SrpAnonymousKeyListener;
import org.alljoyn.validation.testing.utils.log.Logger;
import org.alljoyn.validation.testing.utils.log.LoggerFactory;

public class AuthPasswordHandlerImpl implements AuthPasswordHandler
{
    private static final String TAG = "AuthPasswordHandlerImpl";
    private static final Logger logger = LoggerFactory.getLogger(TAG);
    private PasswordStore passwordStore = new PasswordStore();
    private Map<String, Boolean> peerAuthenticated = new HashMap<String, Boolean>();
    private Map<String, Boolean> peerAuthenticationSuccessful = new HashMap<String, Boolean>();

    public AuthPasswordHandlerImpl(PasswordStore passwordStore)
    {
        this.passwordStore = passwordStore;
    }

    @Override
    public void completed(String mechanism, String authPeer, boolean authenticated)
    {
        if (!authenticated)
        {
            peerAuthenticated.put(authPeer, true);
            peerAuthenticationSuccessful.put(authPeer, false);
            logger.info(String.format(" ** %s failed to authenticate", authPeer));
        }
        else
        {
            peerAuthenticated.put(authPeer, true);
            peerAuthenticationSuccessful.put(authPeer, true);
            logger.info(String.format(" ** %s successfully authenticated", authPeer));
        }
    }

    @Override
    public char[] getPassword(String peerName)
    {
        char[] securedSessionPassword = passwordStore.getPassword(peerName);

        securedSessionPassword = (securedSessionPassword != null) ? securedSessionPassword : SrpAnonymousKeyListener.DEFAULT_PINCODE;
        logger.debug(String.format("Providing password for %s as %s", peerName, Arrays.toString(securedSessionPassword)));
        return securedSessionPassword;
    }

    public void resetAuthentication(String authPeer)
    {
        peerAuthenticated.put(authPeer, false);
        peerAuthenticationSuccessful.put(authPeer, false);
    }

    public boolean isPeerAuthenticated(String authPeer)
    {
        return isTrueBoolean(peerAuthenticated.get(authPeer));

    }

    public boolean isPeerAuthenticationSuccessful(String authPeer)
    {
        return isTrueBoolean(peerAuthenticationSuccessful.get(authPeer));
    }

    protected boolean isTrueBoolean(Boolean value)
    {
        boolean result;
        if (value == null)
        {
            result = false;
        }
        else
        {
            result = value;
        }
        return result;
    }
}