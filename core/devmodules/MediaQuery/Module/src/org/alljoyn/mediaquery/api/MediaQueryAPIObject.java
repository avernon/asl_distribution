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
package org.alljoyn.mediaquery.api;

import org.alljoyn.devmodules.mediaquery.MediaQueryImpl;

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

public class MediaQueryAPIObject implements MediaQueryAPIInterface, BusObject {
	public static final String OBJECT_PATH = "mediaquery";

	private HandlerThread handlerThread = new HandlerThread(OBJECT_PATH);
	{handlerThread.start();}
	private ConnectorHandler handler = new ConnectorHandler(handlerThread.getLooper());
	private static final int COLLECT_MEDIA     = 0;
	private static final int COLLECT_MY_MEDIA  = 1;
	private static final int REQUEST_MEDIA     = 2;
	private static final int REQUEST_MY_MEDIA  = 3;
	private static final int ACTIVATE_MEDIA    = 4;
	private static final int SEND_FILE_REQUEST = 5;

	private static final String TAG = "MediaQueryAPIObject" ;

	public void CollectMediaList(int transactionId, String peer, String mtype)
			throws BusException {
		try{
			Log.i(TAG, "CollectMediaList!!! peer:"+peer);
			Message msg = handler.obtainMessage(COLLECT_MEDIA);
			Bundle data = new Bundle();
			data.putInt("transactionId", transactionId);
			data.putString("peer", peer);
			data.putString("mtype", mtype);
			msg.setData(data);
			handler.sendMessage(msg);
		}catch(Exception e) {
			e.printStackTrace();
		}
	}

	public void CollectMyMediaList(int transactionId, String mtype)
			throws BusException {
		try{
			Log.i(TAG, "CollectMyMediaList!!!");
			Message msg = handler.obtainMessage(COLLECT_MY_MEDIA);
			Bundle data = new Bundle();
			data.putInt("transactionId", transactionId);
			data.putString("mtype", mtype);
			msg.setData(data);
			handler.sendMessage(msg);
		}catch(Exception e) {
			e.printStackTrace();
		}
	}

	public int RequestMedia(int transactionId, String service, String mtype, String path)
			throws BusException {
		try{
			Log.i(TAG, "RequestMedia!!! service: "+service+",mtype: "+mtype+"path: "+path);
			Message msg = handler.obtainMessage(REQUEST_MEDIA);
			Bundle data = new Bundle();
			data.putInt("transactionId", transactionId);
			data.putString("service", service);
			data.putString("mtype", mtype);
			data.putString("path", path);
			msg.setData(data);
			handler.sendMessage(msg);
		}catch(Exception e) {
			Log.e(TAG, "RequestMedia() Exception: " + e.toString());
			e.printStackTrace();
		}
		return transactionId;
	}

	public int RequestMyMedia(int transactionId, String service, String mtype, String path)
			throws BusException {
		try{
			Log.i(TAG, "RequestMyMedia!!! service: "+service+",mtype: "+mtype+"path: "+path);
			Message msg = handler.obtainMessage(REQUEST_MY_MEDIA);
			Bundle data = new Bundle();
			data.putInt("transactionId", transactionId);
			data.putString("service", service);
			data.putString("mtype", mtype);
			data.putString("path", path);
			msg.setData(data);
			handler.sendMessage(msg);
		}catch(Exception e) {
			Log.e(TAG, "RequestMyMedia() Exception: " + e.toString());
			e.printStackTrace();
		}
		return transactionId;
	}

	public void RequestActivation(int transactionId, String peer, String mtype, String path)
			throws BusException {
		try{
			Log.i(TAG, "RequestActivation!!! peer: "+peer+",mtype: "+mtype+"path: "+path);
			Message msg = handler.obtainMessage(ACTIVATE_MEDIA);
			Bundle data = new Bundle();
			data.putInt("transactionId", transactionId);
			data.putString("peer", peer);
			data.putString("mtype", mtype);
			data.putString("path", path);
			msg.setData(data);
			handler.sendMessageAtFrontOfQueue(msg);
		}catch(Exception e) {
			e.printStackTrace();
		}
	}

	public void SendFileRequest(String service, String mtype, String filepath)
			throws BusException {
		try{
			Log.i(TAG, "SendFileRequest!!! service: "+service+", mtype: "+mtype+", path: "+filepath);
			Message msg = handler.obtainMessage(SEND_FILE_REQUEST);
			Bundle data = new Bundle();
			data.putString("service", service);
			data.putString("mtype", mtype);
			data.putString("path", filepath);
			msg.setData(data);
			handler.sendMessage(msg);
		}catch(Exception e) {
			Log.e(TAG, "SendFileRequest() Exception: " + e.toString());
			e.printStackTrace();
		}
	}

	private class ConnectorHandler extends Handler
	{
		public ConnectorHandler(Looper loop) {
			super(loop);
		}

		public void handleMessage(Message msg) {
			MediaQueryImpl impl = MediaQueryImpl.getInstance();
			Bundle data = msg.getData();
			if(impl == null || data == null)
				return;
			switch(msg.what) {
			case COLLECT_MEDIA:
				impl.collectMediaList(data.getInt("transactionId"), data.getString("peer"), data.getString("mtype"));
				//ConnectorCore.callbackInterface.MediaItemReady(transactionId, )
				//REFACTOR CHECK MediaQueryAPIImpl.mediaQueryCallback.onItemAvailable(service, item)
				break;
			case COLLECT_MY_MEDIA:
				impl.collectMyMediaList(data.getInt("transactionId"), data.getString("mtype"));
				break;
			case REQUEST_MEDIA:
				impl.requestMedia(data.getString("service"), data.getString("mtype"), data.getString("path"));
				break;
			case REQUEST_MY_MEDIA:
				Log.w(TAG, "REQUEST_MY_MEDIA: not sure what to do with this!");
				break;
			case ACTIVATE_MEDIA:
				impl.doRequestActivation(data.getInt("transactionId"), data.getString("peer"), data.getString("mtype"), data.getString("path"));
				break;
			case SEND_FILE_REQUEST:
				impl.sendFileRequest(data.getString("service"), data.getString("mtype"), data.getString("path"));
				break;
			default:
				Log.e(TAG, "handleMessage() Unkown msg: "+msg.what);
				break;
			}
		}//handleMessage
	}	
}
