/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

package org.allseen.sample.eventaction;

import android.app.Notification;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.HandlerThread;
import android.os.IBinder;
import android.os.PowerManager;

public class BackgroundService extends Service {
	public static org.allseen.sample.event.tester.BusHandler mEventHandler;
	private PowerManager.WakeLock wakelock;
	
	private static final int NOTIFICATION_ID = 0x12fa5ed;
	
	@Override
	public void onCreate() {
		
	}
	
	@Override
	public int onStartCommand(Intent i, int flags, int startId) {
		Thread t = new Thread(new Runnable() {
			public void run() {
				if(mEventHandler == null) {
					HandlerThread busThread = new HandlerThread("BusHandler");
					busThread.start();
					HandlerThread busThread2 = new HandlerThread("BusHandler");
					busThread2.start();
					mEventHandler = new org.allseen.sample.event.tester.BusHandler(busThread.getLooper(), BackgroundService.this, (EventActionListener)BackgroundService.this.getApplication());

					mEventHandler.initialize(BackgroundService.this.getPackageName()+"Event");
					
					CharSequence title = "EventAction Rule Engine";
			        CharSequence message = "Rule engine running";
			        Intent intent = new Intent(BackgroundService.this, RulesActivity.class);
			        PendingIntent pendingIntent = PendingIntent.getActivity(BackgroundService.this, 0, intent, 0);
			        Notification notification = new Notification(R.drawable.ic_launcher, null, System.currentTimeMillis());
			        notification.setLatestEventInfo(BackgroundService.this, title, message, pendingIntent);
			        notification.flags |= Notification.DEFAULT_SOUND | Notification.FLAG_ONGOING_EVENT | Notification.FLAG_NO_CLEAR;
			
			        startForeground(NOTIFICATION_ID, notification);
			        
			        PowerManager powerManager = (PowerManager) getSystemService(Context.POWER_SERVICE);
			        wakelock = powerManager.newWakeLock(PowerManager.SCREEN_DIM_WAKE_LOCK, Constants.TAG);
			        wakelock.acquire();
			         	        
        			RulesFragment.loadRules();
				}
			}});
		t.start();
		
		return Service.START_NOT_STICKY;
	}/* Start our service. */
	
	@Override
	public void onDestroy() {
		if (null != wakelock) {
		    wakelock.release();
		}
	}

	@Override
	public IBinder onBind(Intent intent) {
		return null;
	}
}
