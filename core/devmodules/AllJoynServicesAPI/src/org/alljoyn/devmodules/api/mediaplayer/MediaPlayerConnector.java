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
package org.alljoyn.devmodules.api.mediaplayer;

import org.alljoyn.devmodules.APICoreImpl;
import org.alljoyn.devmodules.callbacks.CallbackObjectBase;
import org.alljoyn.devmodules.callbacks.TransactionHandler;
import org.json.JSONObject;

import org.alljoyn.devmodules.common.SongInfo;

import android.util.Log;

public class MediaPlayerConnector {
	
	// prevent instantiation via an explicit clone() call
	public Object clone() throws CloneNotSupportedException {
		throw new CloneNotSupportedException();
	}
	
	private static MediaPlayerConnectorInterface mediaPlayerInterface = null;
	
	private static void setupInterface() {
		if(mediaPlayerInterface == null) {
			mediaPlayerInterface = APICoreImpl.getInstance().getProxyBusObject("mediaplayer",
				new Class[] {MediaPlayerConnectorInterface.class}).getInterface(MediaPlayerConnectorInterface.class);
		}
	}
	
	public static void PlaySong(String peer, SongInfo si) throws Exception {
		setupInterface();
		Log.i("MediaPlayerConnector","placing call to onKeyDown!!!");
		mediaPlayerInterface.startStreaming(si);
	}

//	public static void PlaySong(String peer, SongInfo si) throws Exception {
//		setupInterface();
//		Log.i("MediaPlayerConnector","placing call to onKeyDown!!!");
//		//TransactionHandler th = new TransactionHandler();
//		//int transactionId = CallbackObject.AddTransaction(th);
//		mediaPlayerInterface.startStreaming(si);
//		//Log.i("RemoteKeyConnector", "waiting for onKeyDown result");
//		//th.latch.await();
//		//return th.getJSONData().getBoolean("return");
//	}
	
//	public static void HandleListener(int methodId,
//	String jsonCallbackData, byte[] rawData, int totalParts, int partNumber) {
//		try {
//			Log.i("RemoteKeyConnector", "jsonData: "+jsonCallbackData);
//			JSONObject jobj = new JSONObject(jsonCallbackData); 
//			switch(methodId) {
//				case 0:
//					Process process = Runtime.getRuntime().exec(new String[]{"input", "keyevent", ""+jobj.getInt("keycode")});
//					break;
//			}
//		} catch(Exception e) {
//			e.printStackTrace();
//		}
//	}
}
