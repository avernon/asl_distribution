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

import java.util.ArrayList;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.BusSignalHandler;

import org.alljoyn.devmodules.callbacks.CallbackObjectBase;

import android.net.Uri;
import android.util.Log;

public class RemoteControlCallbackObject extends CallbackObjectBase implements RemoteControlCallbackInterface, BusObject {
	static ArrayList<RemoteControlListener> mListenerList = null;

	/**
	 * Register a listener object which will be called if any of the associated signals are found
	 * @param listener the ChatListener object to register
	 */
	public static void registerListener (RemoteControlListener listener){
		if (mListenerList==null){
			mListenerList = new ArrayList<RemoteControlListener>();
			mListenerList.clear();
		}

		if (listener != null){
			mListenerList.add(listener);
		}
	}
	
	@BusSignalHandler(iface=RemoteControlCallbackInterface.SERVICE_NAME, signal="onKeyDown")
	public void onKeyDown(String groupId, int keyCode) throws BusException {
		for(RemoteControlListener listener : mListenerList) {
			listener.onKeyDown(groupId, keyCode);
		}
	}
	
	@BusSignalHandler(iface=RemoteControlCallbackInterface.SERVICE_NAME, signal="executeIntent")
	public void executeIntent(String groupId, String intentAction, String intentData) throws BusException {
		for(RemoteControlListener listener : mListenerList) {
			listener.onExecuteIntent(groupId, intentAction, intentData);
		}
	}
	
	@Override
	public String getObjectPath() {
		return this.OBJECT_PATH;
	}
}
