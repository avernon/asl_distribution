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
package org.alljoyn.devmodules.remotecontrol;

import java.util.ArrayList;
import org.alljoyn.bus.*;
import org.alljoyn.bus.annotation.BusSignalHandler;
import org.alljoyn.remotecontrol.api.RemoteControlAPIImpl;
import org.alljoyn.devmodules.interfaces.AllJoynContainerInterface;
import org.alljoyn.devmodules.interfaces.ModuleInterface;
import org.json.JSONObject;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class RemoteControlImpl extends BusListener implements ModuleInterface  {
	private final String TAG = "RemoteControlImpl";

	private static RemoteControlImpl instance;
	public static RemoteControlImpl getInstance() { return instance; }

	private RemoteControlObject remotekeyObject = new RemoteControlObject();
	private AllJoynContainerInterface alljoynContainer;
	private String myWellknownName;

	private ArrayList<String> remotekeyPeerWellKnowns = new ArrayList<String>();
	private String namePrefix;

	public RemoteControlImpl(AllJoynContainerInterface alljoynContainer) {
		this.alljoynContainer = alljoynContainer;
		instance = this;
	}

	public void RegisterSignalHandlers() {
		alljoynContainer.getBusAttachment().registerSignalHandlers(this);
		alljoynContainer.getBusAttachment().addMatch("type='signal',interface='"+RemoteControlConstants.NAME_PREFIX+"',member='keyDown'");
		alljoynContainer.getBusAttachment().addMatch("type='signal',interface='"+RemoteControlConstants.NAME_PREFIX+"',member='executeIntent'");
	}

	public void SetupSession() {
		Log.i(TAG,"Advertised: "+getAdvertisedName());
	}

	public BusObject getBusObject() { return remotekeyObject; }

	public String getObjectPath() {
		return RemoteControlConstants.OBJECT_PATH;
	}

	public String getAdvertisedName() {
		if(myWellknownName == null) {
			myWellknownName = RemoteControlConstants.SERVICE_NAME+"."+alljoynContainer.getUniqueID();
		}
		return myWellknownName;
	}

	public String getServiceName() {
		return RemoteControlConstants.SERVICE_NAME;
	}

	public void foundAdvertisedName(String name, short transport, String namePrefix) {
		if(!name.contains(getAdvertisedName()) && name.contains(RemoteControlConstants.NAME_PREFIX)){
			name = name.substring(namePrefix.length()+1);
			remotekeyPeerWellKnowns.add(name);
			this.namePrefix = namePrefix;
			try { 
				JSONObject jsonData = new JSONObject();
				jsonData.put("name", name);
				//ConnectorCore.callbackInterface.ListenerJSON(getServiceName(), ProfileConnectorObject.PROFILE_FOUND, jsonData.toString());
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	public void lostAdvertisedName(String name, short transport, String namePrefix) {
		if(!name.contains(getAdvertisedName()) && name.contains(RemoteControlConstants.NAME_PREFIX)){
			//Log.i(TAG,"LostAdvertisedName: "+name);
			remotekeyPeerWellKnowns.remove(name);
			try { 
				JSONObject jsonData = new JSONObject();
				jsonData.put("name", name);
				//ConnectorCore.callbackInterface.ListenerJSON(getServiceName(), ProfileConnectorObject.PROFILE_LOST, jsonData.toString());
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	public void shutdown() {

	}

	public ArrayList<String> getPeers() { return remotekeyPeerWellKnowns; }

	/* ************************************** */
	/* Module specific implementation methods */
	/* ************************************** */
	public void sendRemoteKey(String groupId, String peer, int keyCode) {
		Log.i(TAG,"sendRemoteControl: "+keyCode);
		
		if(groupId != null && groupId.length() != 0) {
			//Send regular Signal on a Group
			//place call to get sessionId for group
			try {
				int sessionId = alljoynContainer.getGroupSessionId(groupId);
				SignalEmitter em = new SignalEmitter(getBusObject(), sessionId, SignalEmitter.GlobalBroadcast.On);
				em.getInterface(RemoteControlInterface.class).keyDown(groupId, "", keyCode);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		else { //have peer send signal just to peer
			try {
				int sessionId = alljoynContainer.getGroupSessionId("");
				SignalEmitter sigEm = new SignalEmitter(getBusObject(), sessionId, SignalEmitter.GlobalBroadcast.On);
				RemoteControlInterface remoteControlInterface = sigEm.getInterface(RemoteControlInterface.class);
				remoteControlInterface.keyDown("", peer, keyCode);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	public void sendIntent(String groupId, String peer, String intentAction, String intentData) {
		Log.i(TAG,"sendIntent: "+intentAction+", "+intentData);
		
		if(groupId != null && groupId.length() != 0) {
			//Send regular Signal on a Group
			//place call to get sessionId for group
			try {
				int sessionId = alljoynContainer.getGroupSessionId(groupId);
				SignalEmitter em = new SignalEmitter(getBusObject(), sessionId, SignalEmitter.GlobalBroadcast.On);
				em.getInterface(RemoteControlInterface.class).executeIntent(groupId, "", intentAction, intentData);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		else { //have peer send signal just to peer
			try {
				int sessionId = alljoynContainer.getGroupSessionId("");
				SignalEmitter sigEm = new SignalEmitter(getBusObject(), sessionId, SignalEmitter.GlobalBroadcast.On);
				RemoteControlInterface remoteControlInterface = sigEm.getInterface(RemoteControlInterface.class);
				remoteControlInterface.executeIntent("", peer, intentAction, intentData);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	@Override
	public void InitAPI(AllJoynContainerInterface coreLogic) {
		setupSession();
	}
	
	@SuppressLint("WrongCall")
	@BusSignalHandler(iface=RemoteControlConstants.NAME_PREFIX, signal="keyDown")
	public void KeyDownSignal(String groupId, String peer, int keyCode) {
		try {
			if(peer.equals("") || peer.equals(alljoynContainer.getUniqueID())) {
				//This was sent on the group so we recieved it or this was sent to me only
				RemoteControlAPIImpl.remoteControlCallback.onKeyDown(groupId, keyCode);
			}
		} catch (BusException e) {
			e.printStackTrace();
		}
	}
	
	@SuppressLint("WrongCall")
	@BusSignalHandler(iface=RemoteControlConstants.NAME_PREFIX, signal="executeIntent")
	public void ExecuteIntentSignal(String groupId, String peer, String intentAction, String intentData) {
		try {
			if(peer.equals("") || peer.equals(alljoynContainer.getUniqueID())) {
				//This was sent on the group so we recieved it or this was sent to me only
				RemoteControlAPIImpl.remoteControlCallback.executeIntent(groupId, intentAction, intentData);
			}
		} catch (BusException e) {
			e.printStackTrace();
		}
	}


	/* ****************************************************************** */
	/* Module specific implementation methods (running on handler thread) */
	/* ****************************************************************** */

	//Define constants for Handler events
	private static final int SETUP_SESSION  = 1; 


	private void setupSession (){
		mHandler.sendEmptyMessage(SETUP_SESSION);	
	}


	// Use this Handler for asynchronous transactions
	// Note that there may be several transactions active in parallel, so don't assume a single user

	private ImplHandler mHandler = new ImplHandler(); // Handler for complex functions

	private class ImplHandler extends Handler
	{
		public void handleMessage(Message msg) {
			// frequently-used variables
			String service;
			Bundle data = msg.getData();

			switch(msg.what) {
			case SETUP_SESSION: {
				SetupSession();
				break;
			}
			default:
				Log.e(TAG, "ImplHandler unknown msg type: "+msg.what);
				break;

			} // switch
		} // handleMessage
	}// ImplHandler

}
