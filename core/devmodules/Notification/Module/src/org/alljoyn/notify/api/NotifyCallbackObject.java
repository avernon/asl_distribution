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
package org.alljoyn.notify.api;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.BusSignalHandler;
import org.alljoyn.devmodules.callbacks.CallbackObjectBase;
import org.alljoyn.devmodules.callbacks.TransactionHandler;
import org.alljoyn.devmodules.common.NotificationData;
import org.alljoyn.devmodules.notify.NotifyConstants;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.util.Log;

public class NotifyCallbackObject extends CallbackObjectBase implements NotifyCallbackInterface, BusObject {
	private static final String TAG = "NotifyCallbackObject";
	static NotifyListener listener;
	
	@BusSignalHandler(iface=NotifyCallbackInterface.SERVICE_NAME, signal="onNotification")
	public void onNotification(String peer, NotificationData msg) throws BusException {
		Log.d(TAG, "Recieved a notification: "+msg.msg);
		if(listener != null) {
			listener.onNotification(peer, msg);
		}
	}

	@BusSignalHandler(iface=NotifyCallbackInterface.SERVICE_NAME, signal="CallbackJSON")
	public void CallbackJSON(int transactionId, String module,
			String jsonCallbackData) {
		Log.d(this.getClass().getName(),"callback id("+transactionId+") data: "+jsonCallbackData);
		Integer key = Integer.valueOf(transactionId);
		if(transactionList.containsKey(key)) {
			Log.d(this.getClass().getName(),"calling transactionHandler!!!");
			TransactionHandler th = transactionList.get(key);
			th.HandleTransaction(jsonCallbackData, null, 0, 0);
		}
	}
	
	@BusSignalHandler(iface=NotifyCallbackInterface.SERVICE_NAME, signal="CallbackData")
	public void CallbackData(int transactionId, String module,
			byte[] rawData, int totalParts, int partNumber) {
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
