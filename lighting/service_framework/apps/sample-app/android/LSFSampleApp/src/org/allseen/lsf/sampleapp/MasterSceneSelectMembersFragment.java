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

import java.util.List;

import android.view.Menu;
import android.view.MenuInflater;

public class MasterSceneSelectMembersFragment extends SelectMembersFragment {

    public MasterSceneSelectMembersFragment() {
        super(R.string.label_master_scene);
    }

    @Override
    protected boolean showScenes() {
        return true;
    }

    @Override
    protected String getHeaderText() {
        return getString(R.string.master_scene_select_members);
    }

    @Override
    protected String[] getPendingScenes() {
        return ((SampleAppActivity)getActivity()).pendingMasterSceneModel.masterScene.getScenes();
    }

    @Override
    protected String getPendingItemID() {
        return ((SampleAppActivity)getActivity()).pendingMasterSceneModel.id;
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        super.onCreateOptionsMenu(menu, inflater);

        ((SampleAppActivity)getActivity()).updateActionBar(R.string.title_master_scene_add, false, false, false, true, true);
    }

    @Override
    protected void processSelection(SampleAppActivity activity, List<String> lampIDs, List<String> groupIDs, List<String> sceneIDs) {
        activity.pendingMasterSceneModel.masterScene.setScenes(sceneIDs.toArray(new String[sceneIDs.size()]));

        if (activity.pendingMasterSceneModel.id.isEmpty()) {
            AllJoynManager.masterSceneManager.createMasterScene(activity.pendingMasterSceneModel.masterScene, activity.pendingMasterSceneModel.getName(), SampleAppActivity.LANGUAGE);
        } else {
            AllJoynManager.masterSceneManager.updateMasterScene(activity.pendingMasterSceneModel.id, activity.pendingMasterSceneModel.masterScene);
        }
    }

    @Override
    protected int getMixedSelectionMessageID() {
        return R.string.mixing_lamp_types_message_scene;
    }

    @Override
    protected int getMixedSelectionPositiveButtonID() {
        // TODO Auto-generated method stub
        return R.string.create_scene;
    }
}
