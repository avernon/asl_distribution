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
package org.alljoyn.remotecontrol.api;

import org.alljoyn.devmodules.remotecontrol.RemoteControlImpl;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Vector;

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
import android.os.HandlerThread;
import android.os.Looper;
import android.os.Message;
import android.os.Messenger;
import android.os.RemoteException;
import android.util.Log;

public class RemoteControlAPIObject implements RemoteControlAPIInterface, BusObject {
	public static final String OBJECT_PATH = "remotecontrol";
	
	private HandlerThread handlerThread = new HandlerThread(OBJECT_PATH);
	{handlerThread.start();}
	private ConnectorHandler handler = new ConnectorHandler(handlerThread.getLooper());
	private static final int ON_KEY_DOWN = 0;
	private static final int SEND_INTENT = 1;
	
	private static final String TAG = "RemoteControlConnector" ;

	public void onKeyDown(String groupId, String peer, int keyCode)
			throws BusException {
		try{
			Log.i(TAG, "onKeyDown!!! peer:"+peer);
			Message msg = handler.obtainMessage(ON_KEY_DOWN);
			Bundle data = new Bundle();
			data.putString("groupId", groupId);
			data.putString("peer", peer);
			data.putInt("keyCode", keyCode);
			msg.setData(data);
			handler.sendMessage(msg);
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public void sendIntent(String groupId, String peer, String intentAction, String intentData)
			throws BusException {
		try{
			Log.i(TAG, "onKeyDown!!! peer:"+peer);
			Message msg = handler.obtainMessage(SEND_INTENT);
			Bundle data = new Bundle();
			data.putString("groupId", groupId);
			data.putString("peer", peer);
			data.putString("intentAction", intentAction);
			data.putString("intentData", intentData);
			msg.setData(data);
			handler.sendMessage(msg);
		}catch(Exception e) {
			e.printStackTrace();
		}
	}

	
	private class ConnectorHandler extends Handler
    {
		public ConnectorHandler(Looper loop) {
			super(loop);
		}
		public void handleMessage(Message msg) {
			RemoteControlImpl impl = RemoteControlImpl.getInstance();
			Bundle data = msg.getData();
			if(impl == null || data == null) {
				Log.i(TAG,"impl or data is null!");
				return;
			}
			switch(msg.what) {
				case ON_KEY_DOWN:
					impl.sendRemoteKey(data.getString("groupId"), data.getString("peer"), data.getInt("keyCode"));
					break;
				case SEND_INTENT:
					Log.i(TAG, "placing call to sendIntent");
					impl.sendIntent(data.getString("groupId"), data.getString("peer"), data.getString("intentAction"), data.getString("intentData"));
					break;
			}
		}
    }	
}
