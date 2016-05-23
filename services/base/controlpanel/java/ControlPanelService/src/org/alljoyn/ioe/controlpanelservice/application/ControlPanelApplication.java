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

package org.alljoyn.ioe.controlpanelservice.application;

import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.BusAttachment.RemoteMessage;
import org.alljoyn.bus.SessionOpts;
import org.alljoyn.bus.Status;
import org.alljoyn.bus.alljoyn.DaemonInit;
import org.alljoyn.ioe.controlpanelservice.ControlPanelException;
import org.alljoyn.ioe.controlpanelservice.ControlPanelService;
import org.alljoyn.services.android.security.AuthPasswordHandler;
import org.alljoyn.services.android.security.SrpAnonymousKeyListener;
import org.alljoyn.services.android.utils.AndroidLogger;

import android.app.Application;
import android.util.Log;

public class ControlPanelApplication extends Application implements AuthPasswordHandler {
    private static final String TAG = "cpan" + ControlPanelApplication.class.getSimpleName();

    /**
     * The daemon should advertise itself "quietly" (directly to the calling
     * port) This is to reply directly to a TC looking for a daemon
     */
    private static final String DAEMON_NAME = "org.alljoyn.BusNode.IoeService";

    /**
     * The daemon should advertise itself "quietly" (directly to the calling
     * port) This is to reply directly to a TC looking for a daemon
     */
    private static final String DAEMON_QUIET_PREFIX = "quiet@";

    private static final String[] authMechanisms = new String[] { "ALLJOYN_SRP_KEYX", "ALLJOYN_ECDHE_PSK" };

    static {
        System.loadLibrary("alljoyn_java");
    }

    private BusAttachment bus;

    private ControlPanelService service;

    @Override
    public void onCreate() {
        super.onCreate();
        service = ControlPanelService.getInstance();

        DaemonInit.PrepareDaemon(this);
        bus = new BusAttachment("ControlPanel", RemoteMessage.Receive);

        // bus.setDaemonDebug("ALL", 7);
        // bus.setLogLevels("ALLJOYN=7");
        // bus.setLogLevels("ALL=7");
        // bus.useOSLogging(true);

        Log.d(TAG, "Setting the AuthListener");

        SrpAnonymousKeyListener authListener = new SrpAnonymousKeyListener(this, new AndroidLogger(), authMechanisms);
        Status status = bus.registerAuthListener(authListener.getAuthMechanismsAsString(), authListener, getFileStreamPath("alljoyn_keystore").getAbsolutePath());

        if (status != Status.OK) {
            Log.e(TAG, "Failed to register AuthListener");
        }

        status = bus.connect();
        if (status != Status.OK) {
            Log.e(TAG, "Failed to connect bus attachment, bus: '" + status + "'");
            return;
        }

        // Advertise the daemon so that the thin client can find it
        advertiseDaemon();

        try {
            service.init(bus, new ControlPanelTestApp());
        } catch (ControlPanelException cpe) {
            Log.e(TAG, "Failure happened, Error: '" + cpe.getMessage() + "'");
        } catch (Exception e) {
            Log.e(TAG, "Unexpected failure occurred, Error: '" + e.getMessage() + "'");
        }
    }// onCreate

    /**
     * @see org.alljoyn.services.android.security.AuthPasswordHandler#completed(java.lang.String,
     *      java.lang.String, boolean)
     */
    @Override
    public void completed(String mechanism, String authPeer, boolean authenticated) {

        Log.d(TAG, "The peer: '" + authPeer + "' has been authenticated: '" + authenticated + "', mechanism: '" + mechanism + "'");
    }

    /**
     * @see org.alljoyn.services.android.security.AuthPasswordHandler#getPassword(java.lang.String)
     */
    @Override
    public char[] getPassword(String peerName) {

        return SrpAnonymousKeyListener.DEFAULT_PINCODE;
    }

    /**
     * Advertise the daemon so that the thin client can find it
     * 
     * @param logger
     */
    private void advertiseDaemon() {
        // request the name
        int flag = BusAttachment.ALLJOYN_REQUESTNAME_FLAG_DO_NOT_QUEUE;
        Status reqStatus = bus.requestName(DAEMON_NAME, flag);
        if (reqStatus == Status.OK) {
            // advertise the name with a quite prefix for TC to find it
            Status adStatus = bus.advertiseName(DAEMON_QUIET_PREFIX + DAEMON_NAME, SessionOpts.TRANSPORT_ANY);
            if (adStatus != Status.OK) {
                bus.releaseName(DAEMON_NAME);
                Log.d(TAG, "failed to advertise daemon name " + DAEMON_NAME);
            } else {
                Log.d(TAG, "Succefully advertised daemon name " + DAEMON_NAME);
            }
        }
    }

}
