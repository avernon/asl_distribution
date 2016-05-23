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
package org.alljoyn.dashboard.ui.activity;

import org.alljoyn.dashboard.R;
import org.alljoyn.dashboard.logic.WifiUtil;
import org.alljoyn.dashboard.ui.util.UIUtil;
import org.alljoyn.onboarding.sdk.OnboardingConfiguration;
import org.alljoyn.onboarding.sdk.WiFiNetworkConfiguration;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

public class SetupDeviceBaseActivity extends BaseActivity {

    protected static String m_deviceSSID;
    protected static String m_currentAP;
    protected static String m_onboardName;
    protected static boolean m_isHidden;
    protected static OnboardingConfiguration onboardingConfiguration;
    protected static WiFiNetworkConfiguration target;
    protected static WiFiNetworkConfiguration onboardee;

 // progress bar
    protected LinearLayout m_progressLayout;
    protected TextView m_progressText;
    
    protected String TAG = "DASHBOARD_Setup Device";

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // prevent tapping outside from closing the activity
        blockOutsideClicks();
    }

    @Override
    public void onBackPressed() {

        launchAreYouSureCancelSetupDialog(

                UIUtil.getUserFriendlyAP(m_deviceSSID),

                new Runnable() {

                    @Override
                    public void run() {
                        // don't call super.OnBackPressed() or else the transition
                        // animation will be called
                        SetupDeviceBaseActivity.this.finish();
                    }
                });

    }

    protected void updateProgress(final String msg) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (m_progressText != null && m_progressLayout != null){
                    m_progressText.setText(msg);
                    m_progressLayout.setVisibility(View.VISIBLE);
                }
            }
        });
    }

    protected void hideProgress() {
        if (m_progressLayout != null) {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    m_progressLayout.setVisibility(View.GONE);
                }
            });
        }
    }
    
    protected void handleError(String popupTitle, String popupMsg, final String ssid) {
        if (popupTitle == null || popupMsg == null) {
            if (m_currentAP == null || WifiUtil.getInstance().isSsidEquals(ssid, m_currentAP)) {
                enableAllWifi();
            } else {
                verifyWifiConnection(m_currentAP);
            }
            return;
        }
        launchBasicAlertDialog(popupTitle, 0, popupMsg, getString(R.string.dismiss), new Runnable() {
            @Override
            public void run() {
                verifyWifiConnection(ssid);
            }
        }, null, null, null, null);
    }

    protected void verifyWifiConnection(String lastFailedSsid) {
        Log.d(TAG, String.format("verifyWifiConnection lastFailedSsid=%s currentAP=%s", lastFailedSsid, m_currentAP));
        if (m_currentAP == null || (lastFailedSsid != null && WifiUtil.getInstance().isSsidEquals(lastFailedSsid, m_currentAP))) {
            enableAllWifi();
        } else {
            WifiUtil.getInstance().connectToNetwork(m_currentAP);
        }
    }


    protected void enableAllWifi() {
        Log.i(TAG, "enableAllWifi");
        WifiUtil.getInstance().enableAllWifiNetworks();
        final Intent launchIntent = new Intent(SetupDeviceBaseActivity.this, NearbyDevicesActivity.class);
        SetupDeviceBaseActivity.this.startActivity(launchIntent);
        finish();
    }


    protected void manageWifiConnectionFailed(final String ssid) {
        String popupTitle = getString(R.string.alert_title_connection_failed);
        String popupMsg = getString(R.string.alert_message_wifi_connection_failed, UIUtil.getUserFriendlyAP(target.getSSID()));

        handleError(popupTitle, popupMsg, ssid);
    }
}

