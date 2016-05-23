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
import org.alljoyn.dashboard.logic.Interface.IntentExtraKeys;
import org.alljoyn.dashboard.ui.util.UISharedPreferencesManager;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.ViewGroup;

public class SplashBackgroundActivity extends BaseActivity
{
    private ViewGroup m_welcomeLayout = null;
    private boolean m_showSetHomeWifi = true;

    final int setupHome = 1222;

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        Intent intent = getIntent();

        m_showSetHomeWifi = getIntent().getBooleanExtra(IntentExtraKeys.EXTRA_BOOLEAN_KEY, true);
        if (intent.hasExtra(IntentExtraKeys.EXTRA_BOOLEAN_KEY)){
            m_showSetHomeWifi = getIntent().getBooleanExtra(IntentExtraKeys.EXTRA_BOOLEAN_KEY, true);
        }
        m_welcomeLayout = (ViewGroup) getLayoutInflater().inflate(R.layout.page_welcome, null);

        setContentView(m_welcomeLayout);

        showSetupHomeWiFiActivity();
    }

    @Override
    protected void onResume() {
        // TODO Auto-generated method stub
        super.onResume();
    }

    private void showSetupHomeWiFiActivity()
    {
        String name = UISharedPreferencesManager.getStoredNetworkName();
        if ((name == null  || name.length() == 0)&& m_showSetHomeWifi)
        {
            Intent startup = new Intent(SplashBackgroundActivity.this, SetupHomeWiFiActivity.class);
            startup.putExtra(IntentExtraKeys.EXTRA_BOOLEAN_KEY, true);
            startActivityForResult(startup, setupHome);
        }
        else
        {
            final Intent launchIntent = new Intent(SplashBackgroundActivity.this, NearbyDevicesActivity.class);
            startActivity(launchIntent);
            finish();
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        Log.i("TAG", "onActivityResult requestCode = " + requestCode);
        if (requestCode == setupHome){
            finish();
        }
    }


}
