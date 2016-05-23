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

package org.allseen.sample.action.tester;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Vector;

import org.allseen.sample.action.tester.BusHandler;
import org.allseen.sample.action.tester.R;

import android.content.Context;
import android.net.wifi.WifiManager;
import android.net.wifi.WifiManager.MulticastLock;
import android.os.Bundle;
import android.os.HandlerThread;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentActivity;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;

public class RulesActivity extends FragmentActivity implements EventActionListener {
	static BusHandler mBusHandler;

	private ActionsFragment actionsFragment;
	
	private MulticastLock m_multicastLock;
	private WifiManager m_wifi;
	
    private ArrayAdapter<String> ruleEngineAdapter;
    private HashMap<String, String> mfriendlyToBusMap = new HashMap<String, String>();

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.rulesassigner_main);
		
		m_wifi = (WifiManager) getSystemService(Context.WIFI_SERVICE);

		FragmentManager fm = this.getSupportFragmentManager();
		actionsFragment = (ActionsFragment) fm.findFragmentById(R.id.rules_actions_fragment);

		Button b = (Button)this.findViewById(R.id.rule_save);
		b.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				try {
					Bundle b;
					Vector<Description> actions;
					actions = actionsFragment.getSelectedActions();
					for(int i = 0; i < actions.size(); i++) {
						b = new Bundle();
						//action
						b.putString("aUniqueName", actions.get(i).getSessionName());
						b.putString("aPath", actions.get(i).getPath());
						b.putString("aIface", actions.get(i).getIface());
						b.putString("aMember", actions.get(i).getMemberName());
						b.putString("aSig", actions.get(i).getSignature());
						RulesActivity.mBusHandler.callAction(b);
					}
					//Unset the checkboxes since saved
					actionsFragment.unsetAllChecks();
					actionsFragment.clearSelectedActions();
				} catch(Exception e) {
					e.printStackTrace();
				}
			}
		});
		
		if (mBusHandler == null) {
			/* Make all AllJoyn calls through a separate handler thread to prevent blocking the UI. */
			HandlerThread busThread = new HandlerThread("BusHandler");
			busThread.start();
			mBusHandler = new BusHandler(busThread.getLooper(), this, this);
			mBusHandler.sendEmptyMessage(BusHandler.INITIALIZE);
		}
		lockMulticast();
	}
	
	@Override
    public void onDestroy() {
        super.onDestroy();
        unlockMulticast();
	}
	
	public void lockMulticast() {
		Log.d(BusHandler.TAG, "Trying to check if we already have a lock");
		if(m_multicastLock == null) {
			m_multicastLock = m_wifi.createMulticastLock("multicastLock");
			m_multicastLock.setReferenceCounted(true);
			m_multicastLock.acquire();
			Log.d(BusHandler.TAG, "MulticastLock acquired");
		}
	}
	
	public void unlockMulticast() {
		Log.d(BusHandler.TAG, "Trying to check if we have a lock to release");
		if(m_multicastLock != null) {
			Log.d(BusHandler.TAG, "releasing MulticastLock");
			m_multicastLock.release();
			m_multicastLock = null;
			Log.d(BusHandler.TAG, "released MulticastLock");
		}
	}

	public void onSaveInstanceState(Bundle outState) {
		super.onSaveInstanceState(outState);
	}

	@Override
	public void onActionsFound(Device info) {
		actionsFragment.addDevice(info);
	}
	
	@Override
	public void onActionLost(int sessionId) {
		actionsFragment.removeDevice(sessionId);
	}
	
	@Override
	public void onRuleEngineFound(final String sessionName, final String friendlyName) {
		runOnUiThread(new Runnable() {
			public void run() {
				mfriendlyToBusMap.put(friendlyName, sessionName);
				ruleEngineAdapter.add(friendlyName);
				ruleEngineAdapter.notifyDataSetChanged();
			}
		});
	}

}
