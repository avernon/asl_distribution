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

import org.alljoyn.devmodules.chat.ChatImpl;

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

public class ChatAPIObject implements ChatAPIInterface, BusObject {
	public static final String OBJECT_PATH = "chat";
	
	private HandlerThread handlerThread = new HandlerThread(OBJECT_PATH);
	{handlerThread.start();}
	private ConnectorHandler handler = new ConnectorHandler(handlerThread.getLooper());
	private static final int ON_SEND_MSG = 0;
	private static final int ON_GROUP_SEND_MSG = 1;
	private static final int ON_START_ROOM = 2;
	private static final int ON_LEAVE_ROOM = 3;
	
	/* Listener callback defines */
	public static final int CHAT_ROOM_FOUND = 0;
	public static final int CHAT_ROOM_LOST = 1;
	public static final int CHAT_MSG = 2;
	
	private static final String TAG = "ChatAPIObject" ;

	public void send(String room, String chatMsg, String user) throws BusException {
		try{
			Message msg = handler.obtainMessage(ON_SEND_MSG);
			Bundle data = new Bundle();
			data.putString("room", room);
			data.putString("msg", chatMsg);
			if(!"".equals(user))
				data.putString("user", user);
			msg.setData(data);
			handler.sendMessage(msg);
		}catch(Exception e) {
			e.printStackTrace();
		}		
	}	
	
	public void sendGroup(String groupId, String chatMsg, String user) throws BusException {
		try{
			Message msg = handler.obtainMessage(ON_GROUP_SEND_MSG);
			Bundle data = new Bundle();
			data.putString("group", groupId);
			data.putString("msg", chatMsg);
			if(!"".equals(user))
				data.putString("user", user);
			msg.setData(data);
			handler.sendMessage(msg);
		}catch(Exception e) {
			e.printStackTrace();
		}
	}

	public void createChat(String room, String[] users) throws BusException {
		try{
			Message msg = handler.obtainMessage(ON_START_ROOM);
			Bundle data = new Bundle();
			data.putString("room", room);
			data.putStringArray("users", users);
			msg.setData(data);
			handler.sendMessage(msg);
		}catch(Exception e) {
			e.printStackTrace();
		}	
	}
	
	public void leaveChat(String room) throws BusException {
		try{
			Message msg = handler.obtainMessage(ON_LEAVE_ROOM);
			Bundle data = new Bundle();
			data.putString("room", room);
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
			ChatImpl impl = ChatImpl.getInstance();
			Bundle data = msg.getData();
			if(impl == null || data == null) {
				Log.d(TAG,"impl or data is null!");
				return;
			}
			switch(msg.what) {
				case ON_GROUP_SEND_MSG:
					Log.d(TAG, "placing call to send group message");
					impl.Send(data.getString("group"), data.getString("msg"));
					break;
				case ON_START_ROOM:
					Log.d(TAG, "placing call to start chat room");
					impl.StartRoom(data.getString("room"), data.getStringArray("users"));
					break;
				case ON_SEND_MSG:
					Log.d(TAG,"placing call to send chat message");
					impl.Send(data.getString("room"), data.getString("msg"), data.getString("user"));
					break;
				case ON_LEAVE_ROOM:
					impl.LeaveRoom(data.getString("room"));
					break;
			}
		}
    }
}
