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
package org.alljoyn.devmodules.whiteboard;

import java.util.ArrayList;
import org.alljoyn.bus.*;
import org.alljoyn.bus.annotation.BusSignalHandler;
import org.alljoyn.devmodules.common.WhiteboardLineInfo;
import org.alljoyn.devmodules.interfaces.AllJoynContainerInterface;
import org.alljoyn.devmodules.interfaces.ModuleInterface;
import org.alljoyn.whiteboard.api.WhiteboardAPIImpl;
import org.json.JSONObject;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class WhiteboardImpl extends BusListener implements ModuleInterface  {
	private final String TAG = "ProfileImpl";

	private static WhiteboardImpl instance;
	public static WhiteboardImpl getInstance() { return instance; }
	
	private WhiteboardObject remotekeyObject = new WhiteboardObject();
	private AllJoynContainerInterface alljoynContainer;
	private String myWellknownName;

	private ArrayList<String> profilePeerWellKnowns = new ArrayList<String>();
	private String namePrefix;

	public WhiteboardImpl(AllJoynContainerInterface alljoynContainer) {
		this.alljoynContainer = alljoynContainer;
		instance = this;
	}

	public void RegisterSignalHandlers() {
		alljoynContainer.getBusAttachment().registerSignalHandlers(this);
		alljoynContainer.getBusAttachment().addMatch("type='signal',interface='"+WhiteboardConstants.NAME_PREFIX+"',member='Draw'");
		alljoynContainer.getBusAttachment().addMatch("type='signal',interface='"+WhiteboardConstants.NAME_PREFIX+"',member='GroupDraw'");
		alljoynContainer.getBusAttachment().addMatch("type='signal',interface='"+WhiteboardConstants.NAME_PREFIX+"',member='Clear'");
		alljoynContainer.getBusAttachment().addMatch("type='signal',interface='"+WhiteboardConstants.NAME_PREFIX+"',member='GroupClear'");
	}

	public void SetupSession() {

	}

	public BusObject getBusObject() { return remotekeyObject; }

	public String getObjectPath() {
		return WhiteboardConstants.OBJECT_PATH;
	}

	public String getAdvertisedName() {
		if(myWellknownName == null) {
			myWellknownName = WhiteboardConstants.SERVICE_NAME+"."+alljoynContainer.getUniqueID();
		}
		return myWellknownName;
	}

	public String getServiceName() {
		return WhiteboardConstants.SERVICE_NAME;
	}

	public void foundAdvertisedName(String name, short transport, String namePrefix) {

	}

	public void lostAdvertisedName(String name, short transport, String namePrefix) {

	}

	public void shutdown() {
		
	}

	public ArrayList<String> getPeers() { return profilePeerWellKnowns; }


	/* ************************************** */
	/* Module specific implementation methods */
	/* ************************************** */

	public void Draw(String groupId, WhiteboardLineInfo lineInfo) {
		if(groupId != null) {
			//Send regular Signal on a Group
			//place call to get sessionId for group
			try {
				int sessionId = alljoynContainer.getGroupSessionId(groupId);
				SignalEmitter em = new SignalEmitter(getBusObject(), sessionId, SignalEmitter.GlobalBroadcast.On);
				em.getInterface(WhiteboardInterface.class).GroupDraw(groupId, lineInfo);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		else {
			SignalEmitter sigEm = new SignalEmitter(getBusObject(), 0, SignalEmitter.GlobalBroadcast.On);
			WhiteboardInterface whiteBoardInterface = sigEm.getInterface(WhiteboardInterface.class);
			try {
				whiteBoardInterface.Draw(lineInfo);
			} catch (BusException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	public void Clear(String groupId, String peer) {
		System.out.println("Clear: "+groupId +", "+peer);
		if(groupId != null) {
			//Send regular Signal on a Group
			//place call to get sessionId for group
			try {
				int sessionId = alljoynContainer.getGroupSessionId(groupId);
				System.out.println("Clear SessionId "+sessionId);
				SignalEmitter em = new SignalEmitter(getBusObject(), sessionId, SignalEmitter.GlobalBroadcast.On);
				em.getInterface(WhiteboardInterface.class).GroupClear(groupId);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		else {
			System.out.println("Clear Global");
			SignalEmitter sigEm = new SignalEmitter(getBusObject(), 0, SignalEmitter.GlobalBroadcast.On);
			WhiteboardInterface whiteBoardInterface = sigEm.getInterface(WhiteboardInterface.class);
			try {
				whiteBoardInterface.Clear();
			} catch (BusException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	@SuppressLint("WrongCall")
	@BusSignalHandler(iface=WhiteboardConstants.NAME_PREFIX, signal="Draw")
	public void DrawSignal(WhiteboardLineInfo lineInfo) {
		MessageContext ctx = alljoynContainer.getBusAttachment().getMessageContext();
		if(ctx.sender.equals(alljoynContainer.getBusAttachment().getUniqueName()))
		{
			Log.i(WhiteboardConstants.COMPONENT_NAME, "ignoring my own signal");
			return;
		}
		Log.i(WhiteboardConstants.COMPONENT_NAME, "Remote sender: "+ctx.sender);
		try {
			alljoynContainer.getBusAttachment().enableConcurrentCallbacks();
			WhiteboardAPIImpl.callback.onDraw(lineInfo);
		} catch (BusException e) {
			e.printStackTrace();
		}
	}
	
	@SuppressLint("WrongCall")
	@BusSignalHandler(iface=WhiteboardConstants.NAME_PREFIX, signal="GroupDraw")
	public void GroupDrawSignal(String groupId, WhiteboardLineInfo lineInfo) {
		MessageContext ctx = alljoynContainer.getBusAttachment().getMessageContext();
		if(ctx.sender.equals(alljoynContainer.getBusAttachment().getUniqueName()))
		{
			Log.i(WhiteboardConstants.COMPONENT_NAME, "ignoring my own signal");
			return;
		}
		Log.i(WhiteboardConstants.COMPONENT_NAME, "Remote sender: "+ctx.sender);
		try {
			alljoynContainer.getBusAttachment().enableConcurrentCallbacks();
			WhiteboardAPIImpl.callback.onGroupDraw(groupId, lineInfo);
		} catch (BusException e) {
			e.printStackTrace();
		}
	}

	@BusSignalHandler(iface=WhiteboardConstants.NAME_PREFIX, signal="Clear")
	public void ClearSignal() {
		MessageContext ctx = alljoynContainer.getBusAttachment().getMessageContext();
		if(ctx.sender.equals(alljoynContainer.getBusAttachment().getUniqueName()))
		{
			Log.i(WhiteboardConstants.COMPONENT_NAME, "ignoring my own signal");
			return;
		}
		Log.i(WhiteboardConstants.COMPONENT_NAME, "Remote Sender: "+ctx.sender);
		try { 
			alljoynContainer.getBusAttachment().enableConcurrentCallbacks();
			WhiteboardAPIImpl.callback.onClear();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	

	@BusSignalHandler(iface=WhiteboardConstants.NAME_PREFIX, signal="GroupClear")
	public void GroupClearSignal(String groupId) {
		MessageContext ctx = alljoynContainer.getBusAttachment().getMessageContext();
		if(ctx.sender.equals(alljoynContainer.getBusAttachment().getUniqueName()))
		{
			Log.i(WhiteboardConstants.COMPONENT_NAME, "ignoring my own signal");
			return;
		}
		Log.i(WhiteboardConstants.COMPONENT_NAME, "Remote Sender: "+ctx.sender);
		try { 
			alljoynContainer.getBusAttachment().enableConcurrentCallbacks();
			WhiteboardAPIImpl.callback.onGroupClear(groupId);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public void InitAPI(AllJoynContainerInterface coreLogic) {
		setupSession();
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
