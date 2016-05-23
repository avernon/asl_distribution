/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

package org.alljoyn.ns.sampleapp;

import java.util.List;
import java.util.UUID;

import org.alljoyn.ns.Notification;

import android.os.AsyncTask;
import android.util.Log;

/**
 * Handle the received Dismiss signal asynchronously. <br>
 * If the {@link VisualNotification} hasn't dismissed previously and its notificationId and appId equals to the given
 * notificationId and appId, then mark the {@link VisualNotification} as dismissed and call {@link VisualNotificationAdapter#notifyDataSetChanged()}
 */
public class DismissSignalHandler extends AsyncTask<Void, Void, VisualNotification> {
	private static final String TAG = "ioe" + DismissSignalHandler.class.getSimpleName();
		
	/**
	 * Notification id
	 */
	private final int notifId;
	
	/**
	 * Application id
	 */
	private final UUID appId;
	
	/**
	 * List of {@link VisualNotification} objects to update
	 */
	private final List<VisualNotification> notificationList;
	
	/**
	 * Update view when the {@link VisualNotification} state changed 
	 */
	private final VisualNotificationAdapter notificationAdapter;
	
	/**
	 * Constructor
	 * @param notifId
	 * @param appId
	 * @param notificationList
	 * @param notificationAdapter
	 */
	public DismissSignalHandler(int notifId, UUID appId, List<VisualNotification> notificationList, VisualNotificationAdapter notificationAdapter) {
		super();
		this.notifId 			 = notifId;
		this.appId 		         = appId;
		this.notificationList    = notificationList;
		this.notificationAdapter = notificationAdapter;
	}
	
	/**
	 * @see android.os.AsyncTask#doInBackground(java.lang.Object[])
	 */
	@Override
	protected VisualNotification doInBackground(Void... args) {

		VisualNotification toDismiss = null;
		
		for ( VisualNotification vn : notificationList ) {
			
			if ( vn.isDismissed() ) {
				continue;
			}
			
			Notification notif = vn.getNotification();
			if ( notif.getAppId().equals(appId)  && notif.getMessageId() == notifId ) {
				toDismiss = vn;
				break;
			}
		}
		
		return toDismiss;
	}//doInBackground
	
	/**
	 * @see android.os.AsyncTask#onPostExecute(java.lang.Object)
	 */
	@Override
	protected void onPostExecute(VisualNotification toDismiss) {
		
		if ( toDismiss != null && !toDismiss.isDismissed() ) {
			Log.d(TAG, "DismissHandler has found the notification to be marked as Dismissed, appId: '" + appId + "', notifId: '" + notifId + "'");
			toDismiss.setDismissed(true);
			notificationAdapter.notifyDataSetChanged();
		}
		else {
			Log.d(TAG, "DismissHandler HAS NOT found the notification to be marked as Dismissed, appId: '" + appId + "', notifId: '" + notifId + "'");
		}
	}//onPostExecute
	
}
