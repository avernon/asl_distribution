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

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class MasterSceneInfoFragment extends PageFrameChildFragment implements View.OnClickListener {

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        SampleAppActivity activity = (SampleAppActivity) getActivity();
        MasterSceneDataModel masterSceneModel = activity.masterSceneModels.get(key);

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

        updateInfoFields(activity, masterSceneModel);

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
        MasterSceneDataModel masterSceneModel = activity.masterSceneModels.get(key);

        activity.showItemNameDialog(R.string.title_master_scene_rename, new UpdateMasterSceneNameAdapter(masterSceneModel, (SampleAppActivity) getActivity()));
    }

    protected void onMembersClick() {
        SampleAppActivity activity = (SampleAppActivity)getActivity();

        activity.pendingMasterSceneModel = new MasterSceneDataModel(activity.masterSceneModels.get(key));

        ((ScenesPageFragment)parent).showSelectMembersChildFragment();
    }

    public void updateInfoFields() {
        SampleAppActivity activity = (SampleAppActivity)getActivity();
        updateInfoFields(activity, activity.masterSceneModels.get(key));
    }

    public void updateInfoFields(SampleAppActivity activity, MasterSceneDataModel masterSceneModel) {
        // Update name and members
        setTextViewValue(view, R.id.statusTextName, masterSceneModel.getName(), 0);
        setTextViewValue(view.findViewById(R.id.sceneInfoRowMembers), R.id.sceneMembersRowText, Util.createSceneNamesString(activity, masterSceneModel.masterScene), 0);
    }
}
