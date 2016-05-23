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

package org.alljoyn.ioe.controlpanelservice.application;

import org.alljoyn.about.AboutServiceImpl;
import org.alljoyn.bus.AuthListener;
import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.BusAttachment.RemoteMessage;
import org.alljoyn.bus.PasswordManager;
import org.alljoyn.bus.SessionOpts;
import org.alljoyn.bus.Status;
import org.alljoyn.bus.alljoyn.DaemonInit;
import org.alljoyn.ioe.controlpanelservice.ControlPanelException;
import org.alljoyn.ioe.controlpanelservice.ControlPanelService;

import android.app.Application;
import android.util.Log;

public class ControlPanelApplication extends Application {
	private static final String TAG = "cpan" + ControlPanelApplication.class.getSimpleName(); 
	
	private class SrpKeyXListener implements AuthListener {
		
        /* Returns the list of supported mechanisms. */
        public String getMechanisms() {
            return "ALLJOYN_PIN_KEYX ALLJOYN_SRP_KEYX";
        }
		
        /**
         * Persistent authentication and encryption data is stored at this location.  
         * 
         * This uses the private file area associated with the application package.
         */
        public String getKeyStoreFileName() {
            return getFileStreamPath("alljoyn_keystore").getAbsolutePath();
        }//getKeyStoreFileName
        
        /**
         * @see org.alljoyn.bus.AuthListener#requested(java.lang.String, java.lang.String, int, java.lang.String, org.alljoyn.bus.AuthListener.AuthRequest[])
         */
		@Override
		public boolean requested(String mechanism, String peerName, int count, String userName, AuthListener.AuthRequest[] requests) {
			 Log.d(TAG, "AuthListener requested() called, checking the Auth mechanisms. Mechanism is: '" + mechanism + "'");
			 
			 if ( !getMechanisms().contains(mechanism) ) {
				 Log.w(TAG, "Recieved an unsupported Auth mechanism: '" + mechanism + "'");
				 return false;
			 }
			 
		     for (AuthRequest request : requests) {
                 if (request instanceof PasswordRequest) {
                	 Log.d(TAG, "Password request was found, setting it, returning TRUE");
                     ((PasswordRequest) request).setPassword(SECURED_SRP_PASSWORD.toCharArray());
                     return true;
                 }
             }//for :: AuthRequest
		     
		     Log.d(TAG, "Password request was NOT found, returning FALSE");
			 return false;
		}//requested

		/**
		 * @see org.alljoyn.bus.AuthListener#completed(java.lang.String, java.lang.String, boolean)
		 */
		@Override
		public void completed(String authMechanism, String authPeer, boolean authenticated) {
			if ( authenticated ) {
				Log.d(TAG, "The peer: '" + authPeer + "', authenticated successfully for authMechanism: '" + authMechanism + "'");
			}
			else {
				Log.w(TAG, "The peer: '" + authPeer + "', WAS NOT authenticated for authMechanism: '" + authMechanism + "'");
			}
		}//completed
		
	}
	
	// ================================================== //
	
	/**
	 * The daemon should advertise itself "quietly" (directly to the calling port)
	 * This is to reply directly to a TC looking for a daemon 
	 */
	private static final String DAEMON_NAME= "org.alljoyn.BusNode.IoeService";
	
	/**
	 * The daemon should advertise itself "quietly" (directly to the calling port)
	 * This is to reply directly to a TC looking for a daemon 
	 */
	private static final String DAEMON_QUIET_PREFIX      = "quiet@";
	
	private static final String DAEMON_CONN_PASSWORD     = "000000";
	
	private static final String SECURED_SRP_PASSWORD     = "000000";         // ABCDEFGH
		
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
		
		//bus.setDaemonDebug("ALL", 7);
		//bus.setLogLevels("ALLJOYN=7");
		//bus.setLogLevels("ALL=7");
		//bus.useOSLogging(true);
		
		//setting the password for the daemon to allow thin clients to connect
		Log.d(TAG, "Setting daemon password");
		Status pasStatus = PasswordManager.setCredentials("ALLJOYN_PIN_KEYX", DAEMON_CONN_PASSWORD);	
		if ( pasStatus != Status.OK ) {
			Log.e(TAG, "Failed to set password for daemon, Error: " + pasStatus);
		}
		
		Log.d(TAG, "Setting the AuthListener");
		
		SrpKeyXListener authListener = new SrpKeyXListener();
		Status status = bus.registerAuthListener(authListener.getMechanisms(), authListener, authListener.getKeyStoreFileName());
		
		if ( status != Status.OK ) {
			Log.e(TAG, "Failed to register AuthListener");
		}
		
		status = bus.connect();
		if ( status != Status.OK ) {
			Log.e(TAG, "Failed to connect bus attachment, bus: '" + status + "'");
			return;
		}
		
		//Advertise the daemon so that the thin client can find it
		advertiseDaemon();
		
		try {
			AboutServiceImpl.getInstance().startAboutClient(bus);
			service.init(bus, new ControlPanelTestApp());
			status = bus.addMatch("sessionless='t',type='error'");
			if ( status != Status.OK ) {
				Log.e(TAG, "Failed to call AddMatch: 'sessionless='t',type='error'");
			}
		} catch (ControlPanelException cpe) {
			Log.e(TAG, "Failure happened, Error: '" + cpe.getMessage() + "'");
		}
		catch (Exception e) {
			Log.e(TAG, "Unexpected failure occurred, Error: '" + e.getMessage() + "'");
		}
	}//onCreate
		
	/**
	 * Advertise the daemon so that the thin client can find it
	 * @param logger
	 */
	private void advertiseDaemon() {
		//request the name	
		int flag = BusAttachment.ALLJOYN_REQUESTNAME_FLAG_DO_NOT_QUEUE;
		Status reqStatus = bus.requestName(DAEMON_NAME, flag);
		if (reqStatus == Status.OK) {
			//advertise the name with a quite prefix for TC to find it
			Status adStatus = bus.advertiseName(DAEMON_QUIET_PREFIX + DAEMON_NAME, SessionOpts.TRANSPORT_ANY);
			if (adStatus != Status.OK){
				bus.releaseName(DAEMON_NAME);
				Log.d(TAG, "failed to advertise daemon name " + DAEMON_NAME);
			}
			else{
				Log.d(TAG, "Succefully advertised daemon name " + DAEMON_NAME);
			}
		}	
	}

}
