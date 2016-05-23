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

import org.alljoyn.devmodules.APICore;
import org.alljoyn.devmodules.callbacks.CallbackObjectBase;
import org.alljoyn.devmodules.callbacks.TransactionHandler;
import org.alljoyn.devmodules.common.WhiteboardLineInfo;
import org.json.JSONObject;

import android.util.Log;

public class WhiteboardAPI {
	
	// prevent instantiation via an explicit clone() call
	public Object clone() throws CloneNotSupportedException {
		throw new CloneNotSupportedException();
	}
	
	
	private static WhiteboardAPIInterface whiteboardInterface = null;
	
	private static void setupInterface() {
		if(whiteboardInterface == null) {
			whiteboardInterface = APICore.getInstance().getProxyBusObject("whiteboard",
				new Class[] {WhiteboardAPIInterface.class}).getInterface(WhiteboardAPIInterface.class);
		}
	}

	/**
	 * This method will send a line part to a group or peer
	 * 
	 * @param groupId		the name of the group
	 * @param peer			the name of the peer, if groupId is supplied it takes precedence
	 * @param lineInfo		the line information
	 * @throws Exception
	 */
	public static void Draw(String groupId, String peer, WhiteboardLineInfo lineInfo) throws Exception
	{
		setupInterface();
		if(lineInfo.sender == null)
			lineInfo.sender = "";
		whiteboardInterface.Draw(groupId == null ? "" : groupId,
							peer == null ? "" : peer,
									lineInfo);
	}
    
	/**
	 * This method will clear all the lines on a supplied group or peer.
	 * 
	 * @param groupId		the name of the group
	 * @param peer			the name of the peer, if groupId is supplied it takes precedence
	 * @throws Exception
	 */
    public static void Clear(String groupId, String peer) throws Exception
	{
    	setupInterface();
		whiteboardInterface.Clear(groupId, peer);
	}
    
    /**
     * Assign a listener to be triggered when events occur from remote applications
     * 
     * @param listener		The implemented callback class that will be triggered
     */
	public static void RegisterListener(WhiteboardListener listener) {
		WhiteboardCallbackObject.registerListener(listener);
	}
	
	/**
     * Remove all listeners that are triggered when events occur from remote applications
     * 
     * @param listener		The implemented callback class that will be triggered
     */
	public static void UnregisterListener(WhiteboardListener listener) {
		WhiteboardCallbackObject.unregisterListener(listener);
	}
	
	/**
     * Remove all listeners that are triggered when events occur from remote applications
     * 
     * @param listener		The implemented callback class that will be triggered
     */
	public static void UnregisterAllListeners() {
		WhiteboardCallbackObject.unregisterAllListener();
	}  
}
