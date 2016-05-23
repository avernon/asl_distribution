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

import org.alljoyn.lsf.tutorial.R;
import org.allseen.lsf.helper.facade.Group;
import org.allseen.lsf.helper.facade.Lamp;
import org.allseen.lsf.helper.facade.LightingDirector;
import org.allseen.lsf.helper.facade.Scene;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.support.v4.app.FragmentActivity;
import android.widget.TextView;

public class TutorialActivity extends FragmentActivity {
    private LightingDirector lightingDirector;

    @Override
    protected void onCreate(Bundle savedState) {
        super.onCreate(savedState);

        setContentView(R.layout.activity_tutorial_app);

        // Display the version number
        String version = "<unknown>";
        try { version = getPackageManager().getPackageInfo(getPackageName(), 0).versionName; } catch (Exception e) {}
        ((TextView)findViewById(R.id.appTextVersion)).setText(version);

        // Instantiate the director and wait for the connection
        lightingDirector = new LightingDirector(new Handler(Looper.getMainLooper()));
        lightingDirector.postOnNextControllerConnection(new Runnable() {
            @Override
            public void run() {
                performLightingOperations();
            }}, 5000);
        lightingDirector.start(getSupportFragmentManager());
    }

    @Override
    protected void onDestroy() {
        lightingDirector.stop(getSupportFragmentManager());
        super.onDestroy();
    }

    protected void performLightingOperations() {
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
            lamps[i].setColor(180, 100, 50, 4000);
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
            groups[i].setColor(90, 100, 75, 4000);
        }

        try {Thread.sleep(2000);} catch(Exception e) { }

        // Scene operations
        Scene[] scenes = lightingDirector.getScenes();

        for (int i = 0; i < scenes.length; i++) {
            scenes[i].apply();
        }
    }
}