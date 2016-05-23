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
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class MasterSceneInfoFragment extends SceneItemInfoFragment {
    public static PendingMasterScene pendingMasterScene = new PendingMasterScene();

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        SampleAppActivity activity = (SampleAppActivity) getActivity();
        MasterScene masterScene = LightingDirector.get().getMasterScene(key);

        view = inflater.inflate(R.layout.fragment_master_scene_info, container, false);

        View statusView = view.findViewById(R.id.infoStatusRow);

        setImageButtonBackgroundResource(statusView, R.id.statusButtonPower, R.drawable.master_scene_set_icon);

        // Name
        TextView nameLabel = (TextView)statusView.findViewById(R.id.statusLabelName);
        nameLabel.setText(R.string.master_scene_info_name);
        nameLabel.setClickable(true);
        nameLabel.setOnClickListener(this);

        TextView nameText = (TextView)statusView.findViewById(R.id.statusTextName);
        nameText.setClickable(true);
        nameText.setOnClickListener(this);

        // Members
        View rowMembers = view.findViewById(R.id.sceneInfoRowMembers);
        rowMembers.setClickable(true);
        rowMembers.setOnClickListener(this);

        setTextViewValue(rowMembers, R.id.sceneMembersRowLabel, getString(R.string.master_scene_info_members), 0);

        updateMasterSceneInfoFields(activity, masterScene);

        return view;
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        ((SampleAppActivity)getActivity()).updateActionBar(R.string.title_master_scene_info, false, false, false, false, true);
    }

    @Override
    public void onClick(View view) {
        int viewID = view.getId();

        if (viewID == R.id.statusLabelName || viewID == R.id.statusTextName) {
            onHeaderClick();
        } else if (viewID == R.id.sceneInfoRowMembers){
            onMembersClick();
        }
    }

    protected void onHeaderClick() {
        SampleAppActivity activity = (SampleAppActivity)getActivity();
        MasterScene masterScene = LightingDirector.get().getMasterScene(key);

        activity.showItemNameDialog(R.string.title_master_scene_rename, new UpdateMasterSceneNameAdapter(masterScene, activity));
    }

    protected void onMembersClick() {
        pendingMasterScene.init(LightingDirector.get().getMasterScene(key));

        ((ScenesPageFragment)parent).showSelectMembersChildFragment();
    }

    @Override
    public void updateInfoFields() {
        updateMasterSceneInfoFields((SampleAppActivity)getActivity(), LightingDirector.get().getMasterScene(key));
    }

    protected void updateMasterSceneInfoFields(SampleAppActivity activity, MasterScene masterScene) {
        // Update name and members
        setTextViewValue(view, R.id.statusTextName, masterScene.getName(), 0);
        setTextViewValue(view.findViewById(R.id.sceneInfoRowMembers), R.id.sceneMembersRowText, Util.createSceneNamesString(activity, masterScene), 0);
    }
}
