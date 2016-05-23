/*
 * Copyright (c) AllSeen Alliance. All rights reserved.
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
package org.allseen.lsf.tutorial.transitioneffects;

import org.allseen.lsf.sdk.AllLightingItemListenerBase;
import org.allseen.lsf.sdk.Color;
import org.allseen.lsf.sdk.LightingController;
import org.allseen.lsf.sdk.LightingControllerConfigurationBase;
import org.allseen.lsf.sdk.LightingDirector;
import org.allseen.lsf.sdk.MyLampState;
import org.allseen.lsf.sdk.NextControllerConnectionListener;
import org.allseen.lsf.sdk.Power;
import org.allseen.lsf.sdk.TrackingID;
import org.allseen.lsf.sdk.TransitionEffect;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

/*
 * Tutorial illustrating how to create a TransitionEffect and apply it with a global listener.
 * This tutorial assumes that there exists a one Lamp and one Controller on the network.
 */
public class TutorialTransitionEffectActivity extends Activity implements NextControllerConnectionListener {
    private static final int CONTROLLER_CONNECTION_DELAY = 5000;

    private LightingDirector lightingDirector;

    /*
     *  The following defined global listener utilizes the initializations of a
     *  transition effect in order to apply it to the first bulb found found in the
     *  LightingDirector.
     */
    private class MyLightingListener extends AllLightingItemListenerBase {
        @Override
        public void onTransitionEffectInitialized(TrackingID trackingId, TransitionEffect effect){
            // STEP 4: Apply the TransitionEffect using onTransitionEffectInitialized as a trigger.
            effect.applyTo(lightingDirector.getLamps()[0]);
        }
    }

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
        lightingDirector.addListener(new MyLightingListener());
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
        // STEP 3: Create a TransitionEffect in the lightingDirector.
        MyLampState mLS = new MyLampState(Power.ON, Color.red());

        lightingDirector.createTransitionEffect(mLS, 5000, "TutorialTransition");
    }
}
