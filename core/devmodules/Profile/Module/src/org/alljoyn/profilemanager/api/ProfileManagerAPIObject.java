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
package org.alljoyn.profilemanager.api;

import java.util.ArrayList;
import java.util.HashMap;

import org.alljoyn.bus.*;
import org.alljoyn.devmodules.callbacks.CallbackInterface;
import org.alljoyn.devmodules.common.ProfileDescriptor;
import org.alljoyn.devmodules.interfaces.AllJoynContainerInterface;
import org.alljoyn.devmodules.profilemanager.ProfileManagerImpl;

import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.os.Message;
import android.util.Log;

public class ProfileManagerAPIObject implements ProfileManagerAPIInterface, BusObject {
	public static final String OBJECT_PATH = "profilemanager";

	private HandlerThread handlerThread = new HandlerThread(OBJECT_PATH);
	{handlerThread.start();}
	private ConnectorHandler handler = new ConnectorHandler(handlerThread.getLooper());
	private static final int GET_PROFILE = 0;

	/* Listener callback defines */
	public static final int PROFILE_FOUND = 0;
	public static final int PROFILE_LOST = 1;

	public String GetMyProfile() throws BusException {
		ProfileManagerImpl impl = ProfileManagerImpl.getInstance();
		Log.d(OBJECT_PATH, "HERE IN GETMYPROFILE!!!");
		String retString = "";
		if (impl != null){
			impl.SetupSession();
			retString = impl.getMyProfile();
		} else{
			Log.e(OBJECT_PATH, "GetMyProfile(): null ProfileManagerImpl !");
		}
		Log.d(OBJECT_PATH, "Returning profile: "+retString);
		return retString;
	}

	public String GetLocalProfile(String profileName) throws BusException {
		ProfileManagerImpl impl = ProfileManagerImpl.getInstance();
		Log.d(OBJECT_PATH, "HERE IN GETMYPROFILE!!!");
		String retString = "";
		if (impl != null){
			impl.SetupSession();
			retString = impl.getMyProfile();
		} else{
			Log.e(OBJECT_PATH, "GetMyProfile(): null ProfileManagerImpl !");
		}
		Log.d(OBJECT_PATH, "Returning profile: "+retString);
		return retString;
	}

	public void SetMyProfile(String jsonProfileData) throws BusException {
		ProfileManagerImpl impl = ProfileManagerImpl.getInstance();
		if (impl != null){
			impl.SetupSession();
			ProfileDescriptor profile = new ProfileDescriptor();
			profile.setJSONString(jsonProfileData);
			impl.setProfile(profile);
		}
	}

	public String[] GetNearbyUsers() throws BusException {
		Log.i(OBJECT_PATH, "HERE. DO I HAVE USERS???");
		ProfileManagerImpl impl = ProfileManagerImpl.getInstance();
		try{
			if (impl != null){
				ArrayList<String> profileSessions = impl.getPeers();
				return profileSessions.toArray(new String[profileSessions.size()]);
			}
		}catch(Exception e) {
			e.printStackTrace();
		}
		Log.e(OBJECT_PATH, "GetNearbyUsers(): null ProfileManagerImpl !");
		return new String[0];
	}

	public void GetProfile(int transactionId, String peer) throws BusException {
		Log.i(OBJECT_PATH, "----------------");
		Log.i(OBJECT_PATH, "----------------");
		Log.i(OBJECT_PATH, "GET PROFILE CALL ("+transactionId +", "+peer+")");
		Log.i(OBJECT_PATH, "----------------");
		Log.i(OBJECT_PATH, "----------------");
		try{
			Message msg = handler.obtainMessage(GET_PROFILE);
			Bundle data = new Bundle();
			data.putInt("transactionId", transactionId);
			data.putString("peer", peer);
			msg.setData(data);
			handler.sendMessage(msg);
		}catch(Exception e) {
			e.printStackTrace();
		}
	}

	// deprecated - just returns current profile name
	public String[] GetLocalProfileNames() {
		Log.w(OBJECT_PATH, "GetLocalProfileNames(): call to deprecated function !");
		return new String[0];
	}

	
	// Handler for synchronous AllJoyn or long operations
	private class ConnectorHandler extends Handler
	{
		public ConnectorHandler(Looper loop) {
			super(loop);
		}
		
		public void handleMessage(Message msg) {
			ProfileManagerImpl impl = ProfileManagerImpl.getInstance();
			if (impl != null){

				Bundle data = msg.getData();
				if(impl == null || data == null)
					return;
				switch(msg.what) {
				case GET_PROFILE:
					String jsonData = impl.getProfileData(data.getString("peer"));
					//ConnectorCore.callbackInterface.CallbackJSON(data.getInt("transactionId"), OBJECT_PATH, jsonData);
					ProfileManagerAPIImpl.profileCallback.CallbackJSON(data.getInt("transactionId"), OBJECT_PATH, jsonData);
					break;
				}
			} else{
				Log.e(OBJECT_PATH, "handleMessage(): null ProfileManagerImpl !");
			}

		}
	}
}
