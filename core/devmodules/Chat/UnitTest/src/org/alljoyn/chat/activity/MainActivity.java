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

package org.alljoyn.chat.activity;

import org.alljoyn.chat.api.ChatAPI;
import org.alljoyn.chat.api.ChatListener;
import org.alljoyn.devmodules.APICoreCallback;
import org.alljoyn.devmodules.APICoreImpl;

import com.example.chatmoduleunittest.R;

import android.support.v4.app.FragmentActivity;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends FragmentActivity {
	
	private static final String TAG = "ChatMainActivity";
	private org.alljoyn.chat.activity.UIFragment chatFragment;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
	    super.onCreate(savedInstanceState);
	    try {
			Log.v(TAG, "Setting up background service...");
			APICoreImpl.StartAllJoynServices(this, new APICoreCallback() {
				@Override
				public void onServiceReady() {				
					Log.v(TAG, "Background service started");
					try {
						Thread.sleep(5000);
						APICoreImpl.StartAllServices();
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			});
		} catch (Exception e1) {
			Log.e(TAG, "Error starting Framework Services: "+e1.toString());
		}
	    setContentView(R.layout.test);
	    chatFragment = (org.alljoyn.chat.activity.UIFragment) getSupportFragmentManager().findFragmentById(R.id.chatfragment);
	}
	
	
	
}
