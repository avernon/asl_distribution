/*
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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
package org.allseen.lsf.tutorial;

import org.allseen.lsf.sdk.Color;
import org.allseen.lsf.sdk.Group;
import org.allseen.lsf.sdk.Lamp;
import org.allseen.lsf.sdk.LightingController;
import org.allseen.lsf.sdk.LightingControllerConfigurationBase;
import org.allseen.lsf.sdk.LightingDirector;
import org.allseen.lsf.sdk.NextControllerConnectionListener;
import org.allseen.lsf.sdk.Scene;

import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.widget.TextView;

public class TutorialActivity extends FragmentActivity implements NextControllerConnectionListener {
    private static final int CONTROLLER_CONNECTION_DELAY = 5000;

    private LightingDirector lightingDirector;

    @Override
    protected void onCreate(Bundle savedState) {
        super.onCreate(savedState);

        setContentView(R.layout.activity_tutorial_app);

        // Display the version number
        String version = "<unknown>";
        try { version = getPackageManager().getPackageInfo(getPackageName(), 0).versionName; } catch (Exception e) {}
        ((TextView)findViewById(R.id.appTextVersion)).setText(version);

        // STEP 1: Initialize a lighting controller with default configuration.
        LightingController lightingController = LightingController.get();
        lightingController.init(new LightingControllerConfigurationBase(getApplicationContext().getFileStreamPath("").getAbsolutePath()));
        lightingController.start();

        // STEP 2: Instantiate the director and wait for the connection, register a
        // global listener to handle Lighting events
        lightingDirector = LightingDirector.get();
        lightingDirector.setNetworkConnectionStatus(true);
        lightingDirector.postOnNextControllerConnection(this, CONTROLLER_CONNECTION_DELAY);
        lightingDirector.start("TutorialApp");
    }

    @Override
    protected void onDestroy() {
        lightingDirector.stop();
        super.onDestroy();
    }

    @Override
    public void onControllerConnected() {
        // Lamp operations
        Lamp[] lamps = lightingDirector.getLamps();

        for (int i = 0; i < lamps.length; i++) {
            lamps[i].turnOn();
        }

        try {Thread.sleep(2000);} catch(Exception e) { }

        for (int i = 0; i < lamps.length; i++) {
            lamps[i].turnOff();
        }

        try {Thread.sleep(2000);} catch(Exception e) { }

        for (int i = 0; i < lamps.length; i++) {
            lamps[i].setColor(new Color(180, 100, 50, 4000));
        }

        // Group operations
        Group[] groups = lightingDirector.getGroups();

        for (int i = 0; i < groups.length; i++) {
            groups[i].turnOn();
        }

        try {Thread.sleep(2000);} catch(Exception e) { }

        for (int i = 0; i < groups.length; i++) {
            groups[i].turnOff();
        }

        try {Thread.sleep(2000);} catch(Exception e) { }

        for (int i = 0; i < groups.length; i++) {
            groups[i].setColor(new Color(90, 100, 75, 4000));
        }

        try {Thread.sleep(2000);} catch(Exception e) { }

        // Scene operations
        Scene[] scenes = lightingDirector.getScenes();

        for (int i = 0; i < scenes.length; i++) {
            scenes[i].apply();
        }
    }
}
