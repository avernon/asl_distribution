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
package org.alljoyn.chat.api;

import java.util.ArrayList;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.BusSignalHandler;
import org.alljoyn.devmodules.APICore;
import org.alljoyn.devmodules.callbacks.CallbackObjectBase;
import org.alljoyn.devmodules.callbacks.TransactionHandler;

import android.util.Log;

public class ChatCallbackObject extends CallbackObjectBase implements ChatCallbackInterface, BusObject {
	//static ChatListener listener;
	// list of registered callbacks
	static ArrayList<ChatListener> mListenerList = new ArrayList<ChatListener>();

	private static final String TAG = "ChatCallbackObject";

	
	/**
	 * Register a listener object which will be called if any of the associated signals are found
	 * @param listener the ChatListener object to register
	 */
	public void registerListener (ChatListener listener){
		if (listener != null){
			mListenerList.add(listener);
		} else {
			Log.e(TAG, "registerListener() Null listener supplied");
		}
	}

	
	@BusSignalHandler(iface=ChatCallbackInterface.SERVICE_NAME, signal="onChatRoomFound")
	public void onChatRoomFound(String room, String[] users) {
		APICore.getInstance().EnableConcurrentCallbacks();
		for (ChatListener listener: mListenerList){
			if (listener!=null) {
				listener.onChatRoomFound(room, users);
			} else {
				Log.e(TAG, "NULL Listener");
			}
		}
	}

	@BusSignalHandler(iface=ChatCallbackInterface.SERVICE_NAME, signal="onChatRoomLost")
	public void onChatRoomLost(String room) {
		APICore.getInstance().EnableConcurrentCallbacks();
		for (ChatListener listener: mListenerList){
			if (listener!=null) {
				listener.onChatRoomLost(room);
			} else {
				Log.e(TAG, "NULL Listener");
			}
		}
	}

	@BusSignalHandler(iface=ChatCallbackInterface.SERVICE_NAME, signal="onChatMsg")
	public void onChatMsg(String room, String user, String msg) {
		APICore.getInstance().EnableConcurrentCallbacks();
		for (ChatListener listener: mListenerList){
			if (listener!=null) {
				listener.onChatMsg(room, user, msg);
			} else {
				Log.e(TAG, "NULL Listener");
			}
		}
	}
	
	@Override
	@BusSignalHandler(iface=ChatCallbackInterface.SERVICE_NAME, signal="onGroupChatMsg")
	public void onGroupChatMsg(String groupId, String user, String msg)
			throws BusException {
		APICore.getInstance().EnableConcurrentCallbacks();
		for (ChatListener listener: mListenerList){
			if (listener!=null) {
				listener.onGroupChatMsg(groupId, user, msg);
			} else {
				Log.e(TAG, "NULL Listener");
			}
		}
	}
	
	@BusSignalHandler(iface=ChatCallbackInterface.SERVICE_NAME, signal="CallbackJSON")
	public void CallbackJSON(int transactionId, String module,
			String jsonCallbackData) {
		APICore.getInstance().EnableConcurrentCallbacks();
		Log.d(this.getClass().getName(),"callback id("+transactionId+") data: "+jsonCallbackData);
		Integer key = Integer.valueOf(transactionId);
		if(transactionList.containsKey(key)) {
			Log.d(this.getClass().getName(),"calling transactionHandler!!!");
			TransactionHandler th = transactionList.get(key);
			th.HandleTransaction(jsonCallbackData, null, 0, 0);
		}
	}
	
	@BusSignalHandler(iface=ChatCallbackInterface.SERVICE_NAME, signal="CallbackData")
	public void CallbackData(int transactionId, String module,
			byte[] rawData, int totalParts, int partNumber) {
		APICore.getInstance().EnableConcurrentCallbacks();
		Integer key = Integer.valueOf(transactionId);
		if(transactionList.containsKey(key)) {
			Log.d(this.getClass().getName(),"calling transactionHandler!!!");
			TransactionHandler th = transactionList.get(key);
			th.HandleTransaction(null, rawData, totalParts, partNumber);
		}
	}
	
	@Override
	public String getObjectPath() {
		return this.OBJECT_PATH;
	}

}
