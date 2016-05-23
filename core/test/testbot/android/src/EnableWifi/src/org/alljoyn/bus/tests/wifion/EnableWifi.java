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
package org.alljoyn.bus.tests.wifion;

import java.util.List;
import android.app.Activity;
import android.content.Intent;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.util.Log;

public class EnableWifi extends Activity {
	private final String TAG = "EnableWifi";
	// Wifi Access Point key
	private final String AP_KEY="SSID";
	private final int TIMEOUT=90;
	
	private Thread mWifiThread = null;
	private WifiManager mWifiManager;
	private Intent mStartIntent;
	private String mWifiAp = null;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        mWifiManager = (WifiManager) getSystemService(getApplicationContext().WIFI_SERVICE);
        mStartIntent = this.getIntent();
        //
        if (null != mStartIntent)
        {
        	if (null != mStartIntent.getStringExtra(AP_KEY))
        	{
        		mWifiAp = mStartIntent.getStringExtra(AP_KEY);
        		Log.d(TAG, "Caller wants " + mWifiAp);
        	}
        	
        }
        //
        
    }
    
    @Override
    public void onResume()
    {
    	Log.d(TAG, "onResume...");
    	super.onResume();
    	
    	if (null == mWifiThread)
    	{
            mWifiThread = new Thread() 
            {
            	@Override
            	public void run()
            	{
            		enableWifi();
            	}
            };
    	}
    	
    	if (null != mWifiThread && false == mWifiThread.isAlive())
    	{
    		mWifiThread.start();
    	}
    }
    
    @Override
    public void onPause()
    {
    	Log.d(TAG, "onPause...");
    	super.onPause();
    	
    	mWifiThread = null;
    }
    
    private boolean switchAP()
    {
    	boolean switchedOK = false;
    	
		// If caller wants to enable a specific ap
		if (null != mWifiAp)
		{
			List<WifiConfiguration> aps = mWifiManager.getConfiguredNetworks();	
			
			if (!aps.isEmpty())
			{
				WifiInfo wifiInfo = mWifiManager.getConnectionInfo();
			
				if (null != wifiInfo)
				{
					String activeAP = wifiInfo.getSSID();
					if (activeAP != null && activeAP.equals(mWifiAp))
					{
						Log.d(TAG, "Already enabled " + activeAP);
						switchedOK = true;
					}
					else 
					{
						if (activeAP != null)
						{
							Log.d(TAG, "Current active AP is " + activeAP);
						}
						Log.d(TAG, "Try to switch to " + mWifiAp + mWifiAp.length());
						Log.d(TAG, "Configured aps are " + aps.size());
						
						for (WifiConfiguration ap: aps)
						{
							Log.d(TAG, "Current ap is " + ap.SSID + ap.SSID.length());
							// ap.SSID is double quoted, remove double quote to compare
							String unquotedSsid=ap.SSID.replace("\"","");
							Log.d(TAG, "unquoted ssid is " + unquotedSsid);
							
							if (mWifiAp.equals(unquotedSsid))
							{
								Log.d(TAG, "Switching...");
								
								if (mWifiManager.enableNetwork(ap.networkId, false))
								{
									Log.d(TAG, "Switching success");
									switchedOK=true;
								}
								break;
								
							}
						} //end for
					}
				}
			}
				
		}
		
		return switchedOK;
    }
    
    private boolean enableWifi()
    {  	
		// Setup WiFi
		boolean isWifiEnabled = mWifiManager.isWifiEnabled();
		
		if (isWifiEnabled)
		{		
			Log.d(TAG, "Wifi already enabled, switch AP if needed");
			
			switchAP();
		}
		else
		{
			mWifiManager.setWifiEnabled(true);	
			
			int timeout=0;
		
			while (!isWifiEnabled && timeout < TIMEOUT)
			{
				// Sleep 1 second to make sure wifi fully enabled
				try {
					Log.d(TAG, "Sleep one second to wait enable complete");
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					Log.e(TAG, "Sleep one second fail!");
				}
			
				isWifiEnabled = mWifiManager.isWifiEnabled();
				timeout++;
			}
		
			if (isWifiEnabled)
			{
				Log.d(TAG, "Wifi enabled successfully after " + timeout + "seconds");
			}
			else
			{ 
				Log.e(TAG, "Can't enable Wifi in 90 seconds!");
				return false;
			}
		
			// Switch AP if needed
			switchAP();
		}
		return true;
    	
    }
}
