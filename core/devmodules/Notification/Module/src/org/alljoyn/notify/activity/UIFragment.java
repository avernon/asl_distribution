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
package org.alljoyn.notify.activity;

import org.alljoyn.notify.api.NotifyAPI;
import org.alljoyn.notify.api.NotifyListener;
import org.alljoyn.notifymodule.R;
import org.alljoyn.devmodules.common.NotificationData;
import org.alljoyn.devmodules.util.Utility;

import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;

public class UIFragment extends Fragment {
	private NotificationManager notificationManager;
	private int notificationId = 1;
	/**
	 * Mandatory empty constructor for the fragment manager to instantiate the
	 * fragment (e.g. upon screen orientation changes).
	 */
	public UIFragment() {
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	}
	
	@Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
		View view = inflater.inflate(Utility.getResourseIdByName(getActivity().getPackageName(),"layout","notify_uifragment"), container, false);
		Button b = (Button)view.findViewById(Utility.getResourseIdByName(getActivity().getPackageName(),"id","button1"));
		b.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				try {
					NotificationData data = new NotificationData();
					data.msg = "test";
					data.deviceName = "NotifyTest";
					data.eventType = 1;
					NotifyAPI.SendGlobalNotification(data);
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		});
		NotifyAPI.RegisterListener(new NotifyListener() {
			@Override
			public void onNotification(String peer, NotificationData msg) {
				try{
					Notification notification = new Notification.Builder(getActivity().getApplicationContext())
			         .setContentTitle(msg.msg)
			         .setContentText("From:"+ msg.deviceName)
			         .setSmallIcon(getActivity().getPackageManager().getApplicationInfo(getActivity().getPackageName(), 0).icon)
			         .build();
					notificationManager.notify(notificationId++, notification);
				}catch(Exception e) {
					e.printStackTrace();
				}
			}
		});
		
		notificationManager = (NotificationManager) getActivity().getApplicationContext().getSystemService(Context.NOTIFICATION_SERVICE);
        return view;
    }
	
	
}
