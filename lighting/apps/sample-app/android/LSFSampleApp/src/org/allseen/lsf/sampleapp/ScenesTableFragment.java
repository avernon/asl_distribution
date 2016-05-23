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
package org.allseen.lsf.sampleapp;

import org.allseen.lsf.sdk.LightingDirector;
import org.allseen.lsf.sdk.MasterScene;
import org.allseen.lsf.sdk.Scene;
import org.allseen.lsf.sdk.SceneV1;
import org.allseen.lsf.sdk.SceneV2;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import android.widget.TextView.BufferType;

public class ScenesTableFragment extends DetailedItemTableFragment {

    public ScenesTableFragment() {
        super();
        type = SampleAppActivity.Type.SCENE;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View root = super.onCreateView(inflater, container, savedInstanceState);
        SampleAppActivity activity = (SampleAppActivity) getActivity();

        for (MasterScene masterScene : LightingDirector.get().getMasterScenes()) {
            addMasterScene(activity, masterScene);
        }

        for (Scene basicScene : LightingDirector.get().getScenes()) {
            addBasicScene(activity, basicScene);
        }

        return root;
    }

    @Override
    public void removeElement(String id) {
        super.removeElement(id);
        updateLoading();
    }

    public void addMasterScene(SampleAppActivity activity, MasterScene masterScene) {
        addItem(masterScene, Util.createSceneNamesString(activity, masterScene), R.drawable.master_scene_set_icon);
        updateLoading();
    }

    public void addBasicScene(SampleAppActivity activity, Scene basicScene) {
        String memberNames;

        if (basicScene instanceof SceneV2) {
            memberNames = Util.createMemberNamesString(activity, (SceneV2)basicScene, ", ", R.string.basic_scene_members_none);
        } else if (basicScene instanceof SceneV1) {
            memberNames = activity.basicSceneV1Module.createMemberNamesString(activity, basicScene, ", ");
        } else {
            memberNames = getString(R.string.basic_scene_members_none);
        }

        addItem(basicScene, memberNames, R.drawable.scene_set_icon);
        updateLoading();
    }

    @Override
    public void updateLoading() {
        super.updateLoading();

        SampleAppActivity activity = (SampleAppActivity)getActivity();
        int sceneItemCount = LightingDirector.get().getSceneCount();

        if (activity.isControllerConnected() && sceneItemCount == 0) {
            // connected but no scenes found; display create scenes screen, hide the scroll table
            layout.findViewById(R.id.scrollLoadingView).setVisibility(View.VISIBLE);
            layout.findViewById(R.id.scrollScrollView).setVisibility(View.GONE);

            View loadingView = layout.findViewById(R.id.scrollLoadingView);
            loadingView.findViewById(R.id.loadingProgressBar).setVisibility(View.GONE);

            ((TextView)loadingView.findViewById(R.id.loadingText1)).setText(activity.getText(R.string.no_scenes));
            ((TextView)loadingView.findViewById(R.id.loadingText2)).setText(Util.createTextWithIcon(activity, R.string.create_scenes, '+', R.drawable.nav_add_icon_normal), BufferType.SPANNABLE);
        } else {
            View loadingView = layout.findViewById(R.id.scrollLoadingView);
            loadingView.findViewById(R.id.loadingProgressBar).setVisibility(View.VISIBLE);
        }
    }
}
