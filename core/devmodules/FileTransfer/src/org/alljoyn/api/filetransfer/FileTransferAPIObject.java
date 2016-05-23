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
package org.alljoyn.api.filetransfer;

import org.alljoyn.devmodules.filetransfer.FileTransferImpl;

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

public class FileTransferAPIObject implements FileTransferAPIInterface, BusObject {
	public static final String OBJECT_PATH = "filetransfer";
	
	private HandlerThread handlerThread = new HandlerThread(OBJECT_PATH);
	{handlerThread.start();}
	private ConnectorHandler handler = new ConnectorHandler(handlerThread.getLooper());
	//Define constants for handler events
	private static final int ON_GET_FILE = 0;
	private static final int ON_OFFER_FILE = 1;
	private static final int ON_PUSH_FILE = 2;
	
	private static final String TAG = "FileTransferAPIObject" ;

//	public void TEMPLATEMETHOD(int transactionId, String data)
//			throws BusException {
//		try{
//			Log.i(TAG, "onKeyDown!!! peer:"+peer);
//			Message msg = handler.obtainMessage(ON_KEY_DOWN);
//			Bundle data = new Bundle();
//			data.putInt("transactionId", transactionId);
//			data.putString("data", data);
//			msg.setData(data);
//			handler.sendMessage(msg);
//		}catch(Exception e) {
//			e.printStackTrace();
//		}
//	}
	
	public void getFile(String peer, String path) 
		throws BusException {
		try{
			Log.i(TAG, "getFile from "+peer+" path:"+path);
			Message msg = handler.obtainMessage(ON_GET_FILE);
			Bundle data = new Bundle();
			data.putString("peer", peer);
			data.putString("path", path);
			msg.setData(data);
			handler.sendMessage(msg);
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public void offerFile(String filename, String path)
		throws BusException {
		try{
			Log.i(TAG, "offerFile fileName:"+filename+" path:"+path);
			Message msg = handler.obtainMessage(ON_OFFER_FILE);
			Bundle data = new Bundle();
			data.putString("filename", filename);
			data.putString("path", path);
			msg.setData(data);
			handler.sendMessage(msg);
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public void pushFile(String peer, String path)
		throws BusException {
		try{
			Log.i(TAG, "getFile from "+peer+" path:"+path);
			Message msg = handler.obtainMessage(ON_PUSH_FILE);
			Bundle data = new Bundle();
			data.putString("peer", peer);
			data.putString("path", path);
			msg.setData(data);
			handler.sendMessage(msg);
		} catch(Exception e) {
			e.printStackTrace();
		}
	}

	
	private class ConnectorHandler extends Handler
    {
		public ConnectorHandler(Looper loop) {
			super(loop);
		}
		public void handleMessage(Message msg) {
			FileTransferImpl impl = FileTransferImpl.getInstance();
			Bundle data = msg.getData();
			if(impl == null || data == null) {
				Log.i(TAG,"impl or data is null!");
				return;
			}
			switch(msg.what) {
				case ON_GET_FILE:
					Log.i(TAG,"placing call to the impl getFile");
					impl.getFile(data.getString("peer"), data.getString("path"));
					break;
				case ON_OFFER_FILE:
					Log.i(TAG,"placing call to the impl offerFile");
					impl.offerFile(data.getString("filename"), data.getString("path"));
					break;
				case ON_PUSH_FILE:
					Log.i(TAG,"placing call to the impl pushFile");
					impl.pushFile(data.getString("peer"), data.getString("path"));
					break;
			}
		}
    }	
}
