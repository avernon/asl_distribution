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
package org.alljoyn.devmodules.api.debug;

import java.util.ArrayList;

import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.annotation.BusSignalHandler;
import org.alljoyn.devmodules.APICore;
import org.alljoyn.devmodules.api.groups.GroupsListener;
import org.alljoyn.devmodules.callbacks.CallbackObjectBase;
import org.alljoyn.devmodules.callbacks.TransactionHandler;

import android.util.Log;

public class DebugCallbackObject extends CallbackObjectBase implements DebugCallbackInterface, BusObject {
	static DebugListener mListener;
	
	public static final String TAG = "DebugCallbackObject";
	
	/**
	 * Register a mListener object which will be called if any of the associated signals are found
	 * @param mListener the GroupListener object to register
	 */
	public void registerListener (DebugListener listener){
		Log.i(TAG, "Debug Listener registered");
		mListener = listener;
	}
	
	@BusSignalHandler(iface=DebugCallbackInterface.SERVICE_NAME, signal="onDebugServiceAvailable")
	public void onDebugServiceAvailable(String service) {
		APICore.getInstance().EnableConcurrentCallbacks();
		mListener.onDebugServiceAvailable(service);
	}
	
	@BusSignalHandler(iface=DebugCallbackInterface.SERVICE_NAME, signal="onDebugServiceLost")
    public void onDebugServiceLost(String service) {
		APICore.getInstance().EnableConcurrentCallbacks();
		mListener.onDebugServiceLost(service);
	}
	
	@BusSignalHandler(iface=DebugCallbackInterface.SERVICE_NAME, signal="onDebugMessage")
    public void onDebugMessage(String service, int level, String message) {
		Log.v(TAG, "onDebugMessage("+message+")");
		APICore.getInstance().EnableConcurrentCallbacks();
		mListener.onDebugMessage(service, level, message);
	}

	@BusSignalHandler(iface=DebugCallbackInterface.SERVICE_NAME, signal="CallbackJSON")
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
	
	@BusSignalHandler(iface=DebugCallbackInterface.SERVICE_NAME, signal="CallbackData")
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
