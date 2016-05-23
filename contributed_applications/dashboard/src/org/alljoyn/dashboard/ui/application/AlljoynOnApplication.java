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
package org.alljoyn.dashboard.ui.application;

import org.alljoyn.dashboard.logic.DeviceManagerImpl;
import org.alljoyn.dashboard.logic.NotificationsManagerImpl;
import org.alljoyn.dashboard.logic.WifiUtil;
import org.alljoyn.dashboard.ui.util.UISharedPreferencesManager;

import android.app.Application;
import android.content.Context;
import android.os.Handler;
import android.os.HandlerThread;
import android.view.inputmethod.InputMethodManager;

public class AlljoynOnApplication extends Application {

    // private static final String TAG = "DASHBOARD_AlljoynOnApplication";

    private static AlljoynOnApplication m_instance;

    private static Handler m_handler;

    private boolean isDialogDisplayed;
    private boolean isNotificationWithActionPopUpDisplayed;

    /**
     * Load the native alljoyn_java library. The actual AllJoyn code is written
     * in C++ and the alljoyn_java library provides the language bindings from
     * Java to C++ and vice versa.
     */
    static {
        try {
            System.loadLibrary("alljoyn_java");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public AlljoynOnApplication() {
        super();

        m_instance = this;
    }

    public static AlljoynOnApplication getInstance() {
        return m_instance;
    }

    public static Handler getHanlder() {
        return m_handler;
    }

    @Override
    public void onCreate() {
        super.onCreate();

        // TODO: Rachel: check keyStore name

        HandlerThread thread = new HandlerThread("AllJoynOnLooper");
        thread.start();
        m_handler = new Handler(thread.getLooper());

        UISharedPreferencesManager.initPreferences(this);
        initListeners();

    }

    public void initListeners() {

        WifiUtil.getInstance().init(this);
        if (UISharedPreferencesManager.isToSAccepted()) {
            final String keyStoreFileName = getApplicationContext().getFileStreamPath("alljoyn_keystore").getAbsolutePath();
            DeviceManagerImpl.getInstance().init(this, keyStoreFileName);
            NotificationsManagerImpl.getInstance().init(this);
        }
    }

    public InputMethodManager getImm() {
        return (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
    }

    public void setSetupHomeWifiOn() {
        isDialogDisplayed = true;
    }

    public void setSetupHomeWifiOff() {
        isDialogDisplayed = false;
    }

    public boolean isSetupHomeWifiDisplayed() {
        return isDialogDisplayed;
    }

    public void setNotificationWithActionPopUpDisplayed(boolean value) {
        isNotificationWithActionPopUpDisplayed = value;
    }

    public boolean istNotificationWithActionPopUpDisplayed() {
        return isNotificationWithActionPopUpDisplayed;
    }

}
