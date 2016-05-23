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

package org.alljoyn.gatewaycontroller;

import org.alljoyn.bus.AuthListener;
import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.Status;
import org.alljoyn.services.android.security.AuthPasswordHandler;
import org.alljoyn.services.android.security.SrpAnonymousKeyListener;
import org.alljoyn.services.android.utils.AndroidLogger;

import android.content.Context;
import android.content.Intent;
import android.util.Log;

/**
 * Registers {@link AuthListener}. The default passcode is defined as in
 * {@link SrpAnonymousKeyListener#DEFAULT_PINCODE} If
 * {@link AuthListener#completed(String, String, boolean)} method call is
 * received with authenticated flag of FALSE, then the
 * {@link GWControllerActions#GWC_PASSWORD_REQUIRED} intent is broadcasted.
 */
public class AuthManager implements AuthPasswordHandler {
    private static final String TAG = "gwcapp" + AuthManager.class.getSimpleName();

    /**
     * The context object which is used to broadcast {@link Intent}
     */
    private Context context;

    /**
     * Current pass code of a Gateway Agent
     */
    private char[] passCode;

    /**
     * The authentication mechanisms that this application supports
     */
    private static final String[] AUTH_MECHANISMS = new String[] { "ALLJOYN_SRP_KEYX", "ALLJOYN_PIN_KEYX", "ALLJOYN_ECDHE_PSK" };

    /**
     * Constructor
     * 
     * @param context
     *            The {@link Context} object to be used for {@link Intent}
     *            broadcasting
     */
    public AuthManager(Context context) {

        this.context = context;
        this.passCode = SrpAnonymousKeyListener.DEFAULT_PINCODE;
    }

    /**
     * Set current pass code to authenticate a Gateway Agent
     * 
     * @param passCode
     * @throws IllegalArgumentException
     *             if the received passCode is undefined
     */
    public void setPassCode(String passCode) {

        if (passCode == null) {
            throw new IllegalArgumentException("passCode is undefined");
        }

        this.passCode = passCode.toCharArray();
    }

    /**
     * Register the AuthManager
     * 
     * @param bus
     *            {@link BusAttachment} to be used for the registration
     * @return {@link Status}
     */
    public Status register(BusAttachment bus) {

        SrpAnonymousKeyListener authListener = new SrpAnonymousKeyListener(this, new AndroidLogger(), AUTH_MECHANISMS);

        String keyStoreFileName = context.getFileStreamPath("alljoyn_keystore").getAbsolutePath();
        Status status           = bus.registerAuthListener(authListener.getAuthMechanismsAsString(), authListener,
                                                               keyStoreFileName);

        Log.d(TAG, "AuthListener has registered, Status: '" + status + "'");
        return status;
    }

    /**
     * @see org.alljoyn.services.android.security.AuthPasswordHandler#getPassword(java.lang.String)
     */
    @Override
    public char[] getPassword(String busName) {

        return passCode;
    }

    /**
     * @see org.alljoyn.services.android.security.AuthPasswordHandler#completed(java.lang.String,
     *      java.lang.String, boolean)
     */
    @Override
    public void completed(String mechanism, String peerName, boolean authenticated) {

        if (authenticated) {
            Log.d(TAG, "The authentication process has been completed successfully. Mechanism: '" + mechanism + "' ,peerName: '" + peerName + "'");
            return;
        }

        Log.d(TAG, "The authentication process has FAILED . Mechanism: '" + mechanism + "' ,peerName: '" + peerName + "' broadcasting Intent");

        Intent intent = new Intent(GWControllerActions.GWC_PASSWORD_REQUIRED.name());
        context.sendBroadcast(intent);
    }

}