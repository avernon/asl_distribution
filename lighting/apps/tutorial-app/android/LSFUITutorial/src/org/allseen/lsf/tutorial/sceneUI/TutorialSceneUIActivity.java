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
package org.allseen.lsf.tutorial.sceneUI;

import java.util.ArrayList;

import org.allseen.lsf.sdk.AllLightingItemListenerBase;
import org.allseen.lsf.sdk.LightingController;
import org.allseen.lsf.sdk.LightingControllerConfigurationBase;
import org.allseen.lsf.sdk.LightingDirector;
import org.allseen.lsf.sdk.Scene;
import org.allseen.lsf.sdk.TrackingID;

import android.app.ListActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class TutorialSceneUIActivity extends ListActivity {

    private ListView listView;
    private ArrayList<Scene> sceneList;
    private ArrayList<String> sceneNameList;
    private ArrayAdapter<String> listAdapter;


    // A global Listener that updates the UI when a Scene is initialized or removed.
    private class MyLightingListener extends AllLightingItemListenerBase {
        @Override
        public void onSceneInitialized(TrackingID trackingId, Scene scene) {
            //Update UI when a Scene is initialized.
            sceneList.add(scene);
            sceneNameList.add(scene.getName());
            updateUI();
        }

        @Override
        public void onSceneRemoved(Scene scene) {
            //Update UI when a Scene is removed.
            int index = sceneList.indexOf(scene);
            sceneList.remove(index);
            sceneNameList.remove(index);
            updateUI();
        }
    }

    @Override
    protected void onCreate(Bundle savedState) {
        super.onCreate(savedState);

        setContentView(R.layout.activity_tutorial_app);

        // STEP 1: Find the ListView resource and set the data ArrayList and adapter for the UI ListView.
        listView = (ListView) findViewById(android.R.id.list);
        sceneList = new ArrayList<Scene>();
        sceneNameList = new ArrayList<String>();
        listAdapter = new ArrayAdapter<String>(this, R.layout.simplerow, sceneNameList);
        listView.setAdapter(listAdapter);

        // STEP 2: Initialize a lighting controller with default configuration.
        LightingController lightingController = LightingController.get();
        lightingController.init(new LightingControllerConfigurationBase(getApplicationContext().getFileStreamPath("").getAbsolutePath()));
        lightingController.start();

        // STEP 3: Instantiate the director, add the custom listener, then start.
        LightingDirector lightingDirector = LightingDirector.get();
        lightingDirector.addListener(new MyLightingListener());
        lightingDirector.setNetworkConnectionStatus(true);
        lightingDirector.start("TutorialApp");
    }

    @Override
    protected void onResume(){
        super.onResume();
        updateUI();
    }

    @Override
    protected void onListItemClick(ListView l, View v, int position, long id) {
        sceneList.get(position).apply();
    }

    private void updateUI() {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                listAdapter.notifyDataSetChanged();
            }
        });
    }
}