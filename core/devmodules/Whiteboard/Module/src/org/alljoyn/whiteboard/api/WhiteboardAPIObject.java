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
package org.alljoyn.whiteboard.api;


import org.alljoyn.devmodules.common.WhiteboardLineInfo;
import org.alljoyn.devmodules.whiteboard.WhiteboardImpl;

import org.alljoyn.bus.*;

import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.os.Message;

public class WhiteboardAPIObject implements WhiteboardAPIInterface, BusObject {
	public static final String OBJECT_PATH = "whiteboard";
	
	private HandlerThread handlerThread = new HandlerThread(OBJECT_PATH);
	{handlerThread.start();}
	private ConnectorHandler handler = new ConnectorHandler(handlerThread.getLooper());
	private static final int DRAW = 0;
	private static final int CLEAR = 1;
	
	private static final String TAG = "WhiteboardAPIObject" ;

	public void Join(String peer) throws BusException {
		
	}

	public void Leave(String peer) throws BusException {
		
	}
	
	public void Draw(String groupId, String peer, WhiteboardLineInfo lineInfo) throws BusException {
		try{
			Message msg = handler.obtainMessage(DRAW, lineInfo);
			Bundle data = new Bundle();
			data.putString("groupId", groupId);
			data.putString("peer", peer);
			msg.setData(data);
			handler.sendMessage(msg);
		}catch(Exception e) {
			e.printStackTrace();
		}	
	}

	public void Clear(String groupId, String peer) throws BusException {
		try{
			Message msg = handler.obtainMessage(CLEAR);
			Bundle data = new Bundle();
			data.putString("groupId", groupId);
			data.putString("peer", peer);
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
			WhiteboardImpl impl = (WhiteboardImpl)WhiteboardImpl.getInstance();
			Bundle data = msg.getData();
			if(impl == null || data == null)
				return;
			switch(msg.what) {
				case DRAW:
					impl.Draw(data.getString("groupId"),(WhiteboardLineInfo)msg.obj);
					break;
				case CLEAR:
					impl.Clear(data.getString("groupId"),data.getString("peer"));
					break;
			}
		}
    }
}
