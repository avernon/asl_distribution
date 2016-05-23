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

import org.alljoyn.devmodules.common.NotificationData;
import org.alljoyn.devmodules.notify.NotifyImpl;

import java.util.LinkedList;
import java.util.Queue;

import org.alljoyn.bus.*;
import org.alljoyn.bus.AuthListener.AuthRequest;
import org.alljoyn.bus.AuthListener.PasswordRequest;
import org.alljoyn.bus.AuthListener.UserNameRequest;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.BusSignalHandler;

import android.app.ListActivity;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.hardware.*;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.Messenger;
import android.os.RemoteException;
import android.util.Log;

public class NotifyAPIObject implements NotifyAPIInterface, BusObject {
	public static final String OBJECT_PATH = "notify";
	
	private ConnectorHandler handler = new ConnectorHandler();
	private static final int ON_SEND_NOTIFY = 0;
	
	private static final String TAG = "NotifyAPIObject" ;

	public void NotifyAll(NotificationData data)
			throws BusException {
		try{
			Log.d(TAG,"Received request to send a notification");
			Message msg = handler.obtainMessage(ON_SEND_NOTIFY);
			msg.obj = data;
			handler.sendMessage(msg);
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public void NotifyGroup(NotificationData data, String groupId)
			throws BusException {
		try{
			Log.d(TAG,"Received request to send a notification");
			Message msg = handler.obtainMessage(ON_SEND_NOTIFY);
			msg.obj = data;
			Bundle b = new Bundle();
			b.putString("groupId", groupId);
			msg.setData(b);
			handler.sendMessage(msg);
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public void NotifyUser(NotificationData data, String userId)
			throws BusException {
		try{
			Log.d(TAG,"Received request to send a notification");
			Message msg = handler.obtainMessage(ON_SEND_NOTIFY);
			msg.obj = data;
			Bundle b = new Bundle();
			b.putString("userId", userId);
			msg.setData(b);
			handler.sendMessage(msg);
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	private class ConnectorHandler extends Handler
    {
		public void handleMessage(Message msg) {
			NotifyImpl impl = NotifyImpl.getInstance();
			Bundle data = msg.getData();
			if(impl == null) {
				Log.i(TAG,"impl or data is null!");
				return;
			}
			switch(msg.what) {
				case ON_SEND_NOTIFY:
					Log.i(TAG,"placing call to the impl");
					impl.sendNotification((NotificationData)msg.obj,
							data != null ? data.getString("groupId") : null,
									data != null ? data.getString("userId") : null);
					break;
			}
		}
    }	
}
