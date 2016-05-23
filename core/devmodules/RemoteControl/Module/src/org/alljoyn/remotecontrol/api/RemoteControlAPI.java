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

import org.alljoyn.devmodules.APICore;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;

public class RemoteControlAPI {
	
	// prevent instantiation via an explicit clone() call
	public Object clone() throws CloneNotSupportedException {
		throw new CloneNotSupportedException();
	}
	
	private static RemoteControlAPIInterface remoteControlInterface = null;
	
	private static void setupInterface() {
		if(remoteControlInterface == null) {
			remoteControlInterface = APICore.getInstance().getProxyBusObject("remotecontrol",
				new Class[] {RemoteControlAPIInterface.class}).getInterface(RemoteControlAPIInterface.class);
		}
	}

	/**
	 * Send a keyDown event to a specific user
	 * 
	 * @param peer			The name of the peer to send a keycode to
	 * @param keyCode		the value of the key pressed
	 * @throws Exception
	 */
	public static void SendKey(String peer, int keyCode) throws Exception {
		setupInterface();
		remoteControlInterface.onKeyDown("", peer, keyCode);
	}
	
	/**
	 * Broadcast a keyDown event to a group
	 * 
	 * @param group			The name of the group to send a keycode to
	 * @param keyCode		the value of the key pressed
	 * @throws Exception
	 */
	public static void SendGroupKey(String group, int keyCode) throws Exception {
		setupInterface();
		remoteControlInterface.onKeyDown(group, "", keyCode);
	}
	
	/**
	 * Send an intent to a remote peer
	 * 
	 * @param peer			The name of the peer to send an intent to
	 * @param i				The intent that will be sent.  The action and dataString are only pulled out of the intent at this time.
	 * @throws Exception
	 */
	public static void SendIntent(String peer, Intent i) throws Exception {
		setupInterface();
		String intentAction = i.getAction();
		String intentData = i.getDataString();
		remoteControlInterface.sendIntent("", peer, intentAction, intentData == null ? "" : intentData);
	}
	
	/**
	 * Send an intent to a group
	 * 
	 * @param group			The name of the group to broadcast the supplied intent
	 * @param i				The intent that will be sent.  The action and dataString are only pulled out of the intent at this time.
	 * @throws Exception
	 */
	public static void SendGroupIntent(String group, Intent i) throws Exception {
		String intentAction = i.getAction();
		String intentData = i.getDataString();
		remoteControlInterface.sendIntent(group, "", intentAction, intentData == null ? "" : intentData);
	}
	
    /**
     * Assign a listener to be triggered when events occur from remote applications
     * 
     * @param listener		The implemented callback class that will be triggered
     */
	public static void RegisterListener(RemoteControlListener listener) {
		RemoteControlCallbackObject.registerListener(listener);
	}   
}
