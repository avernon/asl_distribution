/*
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
 */
package org.allseen.lsf.sampleapp;

import java.lang.reflect.Method;

import org.allseen.lsf.sdk.LightingControllerConfigurationBase;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.util.Log;

public class SampleAppControllerConfiguration extends LightingControllerConfigurationBase {

    private final Context appContext;

    public SampleAppControllerConfiguration(String keystorePath) {
        this(keystorePath, null);
    }

    public SampleAppControllerConfiguration(String keystorePath, Context context) {
        super(keystorePath);

        appContext = context;
    }

    @Override
    public String getMacAddress(String generatedMacAddress) {
        if (appContext == null) {
            return generatedMacAddress;
        }

        WifiManager wifiManager = (WifiManager) appContext.getSystemService(Context.WIFI_SERVICE);
        WifiInfo wInfo = wifiManager.getConnectionInfo();
        String originalMacAddress = wInfo.getMacAddress();

        if (originalMacAddress == null) {
            // If we don't have mac address, create one of length 12 which is
            // the usual length of mac address.
            originalMacAddress = generatedMacAddress;
        }

        originalMacAddress = originalMacAddress.replace(":", "");

        return originalMacAddress;
    }

    @Override
    public boolean isNetworkConnected() {
        if (appContext == null) {
            return super.isNetworkConnected();
        }

        return isWifiConnected();
    }

    private boolean isWifiConnected() {
        NetworkInfo wifiNetworkInfo = ((ConnectivityManager) appContext.getSystemService(Context.CONNECTIVITY_SERVICE)).getNetworkInfo(ConnectivityManager.TYPE_WIFI);

        // determine if wifi AP mode is on
        boolean isWifiApEnabled = false;
        WifiManager wifiManager = (WifiManager) appContext.getSystemService(Context.WIFI_SERVICE);
        // need reflection because wifi ap is not in the public API
        try {
            Method isWifiApEnabledMethod = wifiManager.getClass().getDeclaredMethod("isWifiApEnabled");
            isWifiApEnabled = (Boolean) isWifiApEnabledMethod.invoke(wifiManager);
        } catch (Exception e) {
            e.printStackTrace();
        }

        Log.d(SampleAppActivity.TAG, "Connectivity state " + wifiNetworkInfo.getState().name() + " - connected:" + wifiNetworkInfo.isConnected() + " hotspot:" + isWifiApEnabled);

        return wifiNetworkInfo.isConnected() || isWifiApEnabled;
    }
}

