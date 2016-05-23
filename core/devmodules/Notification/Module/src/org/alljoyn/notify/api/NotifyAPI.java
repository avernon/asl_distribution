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
package org.alljoyn.notify.api;

import org.alljoyn.devmodules.APICore;
import org.alljoyn.devmodules.callbacks.CallbackObjectBase;
import org.alljoyn.devmodules.callbacks.TransactionHandler;
import org.alljoyn.devmodules.common.NotificationData;
import org.alljoyn.devmodules.notify.NotifyConstants;
import org.json.JSONObject;

import android.util.Log;

public class NotifyAPI {
	
	// prevent instantiation via an explicit clone() call
	public Object clone() throws CloneNotSupportedException {
		throw new CloneNotSupportedException();
	}
	
	private static NotifyAPIInterface apiInterface = null;
	
	private static void setupInterface() {
		if(apiInterface == null) {
			apiInterface = APICore.getInstance().getProxyBusObject(NotifyAPIObject.OBJECT_PATH,
				new Class[] {NotifyAPIInterface.class}).getInterface(NotifyAPIInterface.class);
		}
	}
	
    /**
     * Assign a listener to be triggered when events occur from remote applications
     * 
     * @param listener		The implemented callback class that will be triggered
     */
	public static void RegisterListener(NotifyListener listener) {
		NotifyCallbackObject.listener = listener;
	}

	/**
	 * Sends a SessionLess signal that contains the NotificationData
	 * 
	 * @param data			Contains the notification information
	 * @throws Exception
	 */
	public static void SendGlobalNotification(NotificationData data) throws Exception {
		setupInterface();
		apiInterface.NotifyAll(data);
	}
	
	/**
	 * Sends a Signal to a supplied group
	 * 
	 * @param data			Contains the notification information
	 * @param groupId		The groupId that should receive the notification
	 * @throws Exception
	 */
	public static void SendGroupNotification(NotificationData data, String groupId) throws Exception {
		setupInterface();
		apiInterface.NotifyGroup(data, groupId);
	}
	
	/**
	 * Send a Notification to a specified user
	 * 
	 * @param data			Contains the notification information
	 * @param userId		The name of the user that should receive the Notification
	 * @throws Exception
	 */
	public static void SendUserNotification(NotificationData data, String userId) throws Exception {
		setupInterface();
		apiInterface.NotifyUser(data, userId);
	}
}
