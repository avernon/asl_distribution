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
package org.alljoyn.devmodules.api.profilemanager;

import java.util.ArrayList;

import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.BusSignalHandler;

import org.alljoyn.devmodules.APICore;
import org.alljoyn.devmodules.api.groups.GroupsListener;
import org.alljoyn.devmodules.callbacks.CallbackObjectBase;
import org.alljoyn.devmodules.callbacks.TransactionHandler;

import android.util.Log;

public class ProfileManagerCallbackObject extends CallbackObjectBase implements ProfileManagerCallbackInterface, BusObject {

	// list of registered callbacks
	static ArrayList<ProfileManagerListener> mListenerList = new ArrayList<ProfileManagerListener>();
	//static ProfileManagerListener listener;
	private static final String TAG = "ProfileManagerCallbackObject";


	/**
	 * Register a listener object which will be called if any of the associated signals are found
	 * @param listener the GroupListener object to register
	 */
	public void registerListener (ProfileManagerListener listener){
		if (mListenerList==null){
			mListenerList.clear();
		}

		if (listener != null){
			mListenerList.add(listener);
		} else {
			Log.e(TAG, "registerListener() Null listener supplied");
		}
	}
	@BusSignalHandler(iface=ProfileManagerCallbackInterface.SERVICE_NAME, signal="onProfileFound")
	public void onProfileFound(String peer) {
		APICore.getInstance().EnableConcurrentCallbacks();
		Log.v(TAG, "onProfileFound("+peer+")");
		for (ProfileManagerListener listener: mListenerList){
			if (listener!=null) {
				listener.onProfileFound(peer);
			}
		}
	}

	@BusSignalHandler(iface=ProfileManagerCallbackInterface.SERVICE_NAME, signal="onProfileLost")
	public void onProfileLost(String peer) {
		APICore.getInstance().EnableConcurrentCallbacks();
		for (ProfileManagerListener listener: mListenerList){
			if (listener!=null) {
				listener.onProfileLost(peer);
			}
		}
	}

	@BusSignalHandler(iface=ProfileManagerCallbackInterface.SERVICE_NAME, signal="CallbackJSON")
	public void CallbackJSON(int transactionId, String module,
			String jsonCallbackData) {
		APICore.getInstance().EnableConcurrentCallbacks();
		Integer key = Integer.valueOf(transactionId);
		if(transactionList.containsKey(key)) {
			TransactionHandler th = transactionList.get(key);
			th.HandleTransaction(jsonCallbackData, null, 0, 0);
		}
	}

	@BusSignalHandler(iface=ProfileManagerCallbackInterface.SERVICE_NAME, signal="CallbackData")
	public void CallbackData(int transactionId, String module,
			byte[] rawData, int totalParts, int partNumber) {
		APICore.getInstance().EnableConcurrentCallbacks();
		Integer key = Integer.valueOf(transactionId);
		if(transactionList.containsKey(key)) {
			TransactionHandler th = transactionList.get(key);
			th.HandleTransaction(null, rawData, totalParts, partNumber);
		}
	}


	@Override
	public String getObjectPath() {
		return this.OBJECT_PATH;
	}
}
