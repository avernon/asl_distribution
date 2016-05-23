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

import java.util.ArrayList;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.annotation.BusSignalHandler;
import org.alljoyn.devmodules.APICore;
import org.alljoyn.devmodules.callbacks.CallbackObjectBase;
import org.alljoyn.devmodules.callbacks.TransactionHandler;
import org.alljoyn.devmodules.common.WhiteboardLineInfo;

import android.util.Log;

public class WhiteboardCallbackObject extends CallbackObjectBase implements WhiteboardCallbackInterface, BusObject {
	private static final String TAG = "WhiteboardCallbackObject";
	// list of registered callbacks
	static ArrayList<WhiteboardListener> mListenerList = new ArrayList<WhiteboardListener>();

	/**
	 * Register a listener object which will be called if any of the associated signals are found
	 * @param listener the ChatListener object to register
	 */
	public static void registerListener (WhiteboardListener listener){
		if (listener != null){
			mListenerList.add(listener);
		} else {
			Log.e(TAG, "registerListener() Null listener supplied");
		}
	}
	
	public static void unregisterListener (WhiteboardListener listener){
		if (listener != null){
			mListenerList.remove(listener);
		} else {
			Log.e(TAG, "unregisterListener() Null listener supplied");
		}
	}
	
	public static void unregisterAllListener() {
		mListenerList.clear();
	}
	
	@BusSignalHandler(iface=WhiteboardCallbackInterface.SERVICE_NAME, signal="onDraw")
	public void onDraw(WhiteboardLineInfo lineInfo) throws BusException {
		APICore.getInstance().EnableConcurrentCallbacks();
		Log.d(TAG, "Recieved onDraw: "+lineInfo.x1+", "+lineInfo.y1 +", "+lineInfo.x2 +", "+lineInfo.y2 +", " +lineInfo.pressure+", "+lineInfo.width+", "+lineInfo.action);
		for(WhiteboardListener listener: mListenerList){
			if(listener != null) {
				listener.onRemoteDraw(lineInfo);
			}
		}
	}
	
	@BusSignalHandler(iface=WhiteboardCallbackInterface.SERVICE_NAME, signal="onGroupDraw")
	public void onGroupDraw(String groupId, WhiteboardLineInfo lineInfo) {
		APICore.getInstance().EnableConcurrentCallbacks();
		Log.d(TAG, "Recieved onGroupDraw: Group("+groupId+") "+lineInfo.x1+", "+lineInfo.y1 +", "+lineInfo.x2 +", "+lineInfo.y2 +", " +lineInfo.pressure+", "+lineInfo.width+", "+lineInfo.action);
		for(WhiteboardListener listener: mListenerList){
			if(listener != null) {
				listener.onRemoteGroupDraw(groupId, lineInfo);
			}
		}
	}

	@BusSignalHandler(iface=WhiteboardCallbackInterface.SERVICE_NAME, signal="onClear")
	public void onClear() throws BusException {
		Log.d(TAG, "Recieved a clear command");
		APICore.getInstance().EnableConcurrentCallbacks();
		for(WhiteboardListener listener: mListenerList){
			if(listener != null) {
				listener.onClear();
			}
		}
	}
	
	@BusSignalHandler(iface=WhiteboardCallbackInterface.SERVICE_NAME, signal="onGroupClear")
	public void onGroupClear(String group) {
		APICore.getInstance().EnableConcurrentCallbacks();
		Log.d(TAG, "Received a group clear command");
		for(WhiteboardListener listener: mListenerList) {
			if(listener != null) {
				listener.onGroupClear(group);
			}
		}
	}
	
	@Override
	public String getObjectPath() {
		return this.OBJECT_PATH;
	}
}
