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
package org.alljoyn.devmodules.callbacks;

import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.CountDownLatch;

import org.json.JSONException;
import org.json.JSONObject;

import android.util.Log;

public class TransactionHandler {	
	public CountDownLatch latch = new CountDownLatch(1);
	private JSONObject jsonData;
	private Timer timer = new Timer();
	private TimerTask timeoutTask;
	
	public void HandleTransaction(String jsonCallbackData, byte[] rawData, int totalParts, int partNumber) {
		synchronized(latch) {
			try {
				jsonData = new JSONObject(jsonCallbackData);
			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			latch.countDown();
			if(timeoutTask != null)
				timeoutTask.cancel();
		}
	}
	
	public JSONObject getJSONData() {
		return jsonData;
	}
	
	public void startTimeout() {
		timeoutTask = new TimerTask() {
			@Override
			public void run() {
				synchronized(latch) {
					jsonData = new JSONObject();
					try {
						Log.d("TRANSACTIONHANDLER", "ERROR TIMEOUT!!!!");
						jsonData.put("error", "timeout");
					} catch (Exception e) {
						e.printStackTrace();
					}
					latch.countDown();
				}
			}
		};
		timer.schedule(timeoutTask, 30000);
	}
}
