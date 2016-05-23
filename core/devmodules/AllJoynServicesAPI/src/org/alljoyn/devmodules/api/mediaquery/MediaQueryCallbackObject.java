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
package org.alljoyn.devmodules.api.mediaquery;

import java.util.ArrayList;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.BusSignalHandler;

import org.alljoyn.devmodules.APICore;
import org.alljoyn.devmodules.api.groups.GroupsListener;
import org.alljoyn.devmodules.callbacks.CallbackObjectBase;
import org.alljoyn.devmodules.callbacks.TransactionHandler;
import org.alljoyn.devmodules.common.MediaIdentifier;

import android.util.Log;

public class MediaQueryCallbackObject extends CallbackObjectBase implements MediaQueryCallbackInterface, BusObject {
	static MediaQueryListener listener;
	
	private final String TAG = "MediaQueryCallbackObject";

	// list of registered callbacks
	static ArrayList<MediaQueryListener> mListenerList = null;

	/**
	 * Register a listener object which will be called if any of the associated signals are found
	 * @param listener the GroupListener object to register
	 */
	public void registerListener (MediaQueryListener listener){
		if (mListenerList==null){
			mListenerList = new ArrayList<MediaQueryListener>();
			mListenerList.clear();
		}

		if (listener != null){
			mListenerList.add(listener);
		} else {
			Log.e(TAG, "registerListener() Null listener supplied");
		}
	}

	@BusSignalHandler(iface=MediaQueryCallbackInterface.SERVICE_NAME, signal="onMediaQueryServiceAvailable")
	public void onMediaQueryServiceAvailable(String service)
			throws BusException {
		APICore.getInstance().EnableConcurrentCallbacks();
		listener.onMediaQueryServiceAvailable(service);
	}

	@BusSignalHandler(iface=MediaQueryCallbackInterface.SERVICE_NAME, signal="onMediaQueryServiceLost")
	public void onMediaQueryServiceLost(String service) throws BusException {
		APICore.getInstance().EnableConcurrentCallbacks();
		for (MediaQueryListener listener: mListenerList){
			if (listener!=null) {
				listener.onMediaQueryServiceLost(service);
			}
		}
	}

	@BusSignalHandler(iface=MediaQueryCallbackInterface.SERVICE_NAME, signal="onQueryComplete")
	public void onQueryComplete(String service, String mtype)
			throws BusException {
		APICore.getInstance().EnableConcurrentCallbacks();
		for (MediaQueryListener listener: mListenerList){
			if (listener!=null) {
				listener.onQueryComplete(service, mtype);
			}
		}
	}

	@BusSignalHandler(iface=MediaQueryCallbackInterface.SERVICE_NAME, signal="onItemAvailable")
	public void onItemAvailable(String service, MediaIdentifier item)
			throws BusException {
		APICore.getInstance().EnableConcurrentCallbacks();
		Log.d(TAG,"onItemAvailable...");
		for (MediaQueryListener listener: mListenerList){
			if (listener!=null) {
				listener.onItemAvailable(service, item);
			}
		}
	}

	@BusSignalHandler(iface=MediaQueryCallbackInterface.SERVICE_NAME, signal="onTransferComplete")
	public void onTransferComplete(String service, String path, String mtype, String localpath) throws BusException {
		APICore.getInstance().EnableConcurrentCallbacks();
		Log.v(TAG, "onTransferComplete("+localpath+")");
		for (MediaQueryListener listener: mListenerList){
			if (listener!=null) {
				listener.onTransferComplete(service, path, mtype, localpath);
			}
		}
	}

	@BusSignalHandler(iface=MediaQueryCallbackInterface.SERVICE_NAME, signal="onTransferError")
	public void onTransferError(int transaction, String service, String mtype,
			String path) throws BusException {
		APICore.getInstance().EnableConcurrentCallbacks();
		for (MediaQueryListener listener: mListenerList){
			if (listener!=null) {
				listener.onTransferError(transaction, service, mtype, path);
			}
		}
	}

	@BusSignalHandler(iface=MediaQueryCallbackInterface.SERVICE_NAME, signal="CallbackJSON")
	public void CallbackJSON(int transactionId, String module,
			String jsonCallbackData) {
		APICore.getInstance().EnableConcurrentCallbacks();
		Integer key = Integer.valueOf(transactionId);
		if(transactionList.containsKey(key)) {
			TransactionHandler th = transactionList.get(key);
			th.HandleTransaction(jsonCallbackData, null, 0, 0);
		}
	}
	
	@BusSignalHandler(iface=MediaQueryCallbackInterface.SERVICE_NAME, signal="CallbackData")
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
