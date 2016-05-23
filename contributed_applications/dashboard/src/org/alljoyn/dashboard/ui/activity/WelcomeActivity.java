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

import java.util.Timer;
import java.util.TimerTask;

import org.alljoyn.dashboard.R;
import org.alljoyn.dashboard.logic.Interface.IntentActions;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.ViewGroup;

public class WelcomeActivity extends BaseActivity
{
    private ViewGroup m_welcomeLayout = null;

    private boolean m_launchedEULA = false;

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        m_welcomeLayout = (ViewGroup) getLayoutInflater().inflate(R.layout.page_welcome, null);

        setContentView(m_welcomeLayout);

        final Activity instance = this;
        final Timer timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                if (!instance.isFinishing()) {
                    m_launchedEULA = true;

                    final Intent intent = new Intent(WelcomeActivity.this, SplashBackgroundActivity.class);
                    WelcomeActivity.this.startActivity(intent);

                    final Timer timer2 = new Timer();
                    timer2.schedule(new TimerTask() {
                        @Override
                        public void run() {
                            // AJAPPS-49: allow this activity to capture the back key before the EULA loads
                            finish();
                        }
                    }, 3000);
                }
            }
        }, 400);
    }

    @Override
    protected void verifyWifiIsEnabled(){}

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        if (KeyEvent.KEYCODE_BACK == keyCode)
        {
            if (handleBack())
            {
                return true;
            }
        }
        return super.onKeyDown(keyCode, event);
    }

    @Override
    public void onBackPressed()
    {
        if (!handleBack())
        {
            super.onBackPressed();
        }
    }

    protected boolean handleBack()
    {
        // AJAPPS-49: make sure we exit the app even if the the request to
        // launch the EULA has already occurred
        finish();
        if (m_launchedEULA)
        {
            final Timer timer = new Timer();
            timer.schedule(new TimerTask() {
                @Override
                public void run() {
                    final Intent intent = new Intent(IntentActions.AJ_ON_USER_EXIT_APP);
                    sendBroadcast(intent);
                }
            }, 1000);
        }

        return false;
    }

}
