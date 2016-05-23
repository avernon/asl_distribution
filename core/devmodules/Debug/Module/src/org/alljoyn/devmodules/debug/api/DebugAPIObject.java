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
package org.alljoyn.devmodules.debug.api;

import org.alljoyn.devmodules.debug.*;

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

public class DebugAPIObject implements DebugAPIInterface, BusObject {
	public static final String OBJECT_PATH = "debug";
	
	private HandlerThread handlerThread = new HandlerThread(OBJECT_PATH);
	{handlerThread.start();}
	private ConnectorHandler handler = new ConnectorHandler(handlerThread.getLooper());
	
	////////////////////////////////////////////////
	// Control of Local Service 
	////////////////////////////////////////////////
	
	private static final String TAG = "DebugConnector" ;

	// Get current filter string (OS-Specific)
	public String GetFilter() {
		return "";//DebugObject.mFilter;
	}

	// Set filter string (OS-Specific)
	public void SetFilter(String filter) {
		//DebugObject.mFilter = filter;
	}
	
	////////////////////////////////////////////////
	// Interaction with Remote Debug Services
	////////////////////////////////////////////////
	
	// Connect to a particular service (just use prefix for all services)
	public void Connect (String device, String service) {
		Log.d(TAG, "Connect("+device+","+service+")");	
		handler.sendMessage(handler.obtainMessage(0, device));
	}
	
	
	// Disconnect from a particular service
	public void Disconnect(String device, String service) {
		Log.d(TAG, "Disconnect("+device+","+service+")");	
		handler.sendMessage(handler.obtainMessage(1, device));
	}

	// List connected services
	public String[] GetServiceList() {
		Log.d(TAG, "GetServiceList()");
		DebugImpl impl = DebugImpl.getInstance();
		return impl.getDebugSessions();
	}
	
	// Get the list of messages received from a particular service
	public DebugMessageDescriptor[] GetMessageList (String service) {
		Log.d(TAG, "GetMessageList("+service+")");
//		return DebugGlobalData.mRemoteDebugList.getAll(service);
		return null;
	}
	
	private class ConnectorHandler extends Handler
    {
		public ConnectorHandler(Looper loop) {
			super(loop);
		}
		public void handleMessage(Message msg) {
			DebugImpl impl = DebugImpl.getInstance();
			switch(msg.what) {
				case 0:
					try {
						impl.ConnectToDevice((String)msg.obj);
					} catch (Exception e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					break;
				case 1:
					try {
						impl.DisconnectFromDevice((String)msg.obj);
					} catch (Exception e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					break;
			}
		}
    }

	public boolean IsEnabled() throws BusException {
		// TODO Auto-generated method stub
		return false;
	}

	public void Enable() throws BusException {
		// TODO Auto-generated method stub
		
	}

	public void Disable() throws BusException {
		// TODO Auto-generated method stub
		
	}
}
