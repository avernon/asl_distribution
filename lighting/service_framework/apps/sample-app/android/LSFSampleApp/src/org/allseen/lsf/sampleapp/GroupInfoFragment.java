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

public class GroupInfoFragment extends DimmableItemInfoFragment {

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = super.onCreateView(inflater, container, savedInstanceState);
        String groupID = key;

        itemType = SampleAppActivity.Type.GROUP;
        itemModels = ((SampleAppActivity)getActivity()).groupModels;

        ((TextView)statusView.findViewById(R.id.statusLabelName)).setText(R.string.label_group_name);

        // displays members of this group
        TextView membersLabel = (TextView)(view.findViewById(R.id.groupInfoMembers).findViewById(R.id.nameValueNameText));
        membersLabel.setText(R.string.group_info_label_members);
        membersLabel.setClickable(true);
        membersLabel.setOnClickListener(this);

        TextView membersValue = (TextView)(view.findViewById(R.id.groupInfoMembers).findViewById(R.id.nameValueValueText));
        membersValue.setClickable(true);
        membersValue.setOnClickListener(this);

        updateInfoFields(((SampleAppActivity)getActivity()).groupModels.get(groupID));

        return view;
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        ((SampleAppActivity)getActivity()).updateActionBar(R.string.title_group_info, false, false, false, false, true);
    }

    @Override
    public void onClick(View view) {
        int viewID = view.getId();

        if (viewID == R.id.nameValueNameText || viewID == R.id.nameValueValueText) {
            if ((parent != null) && (!AllLampsDataModel.ALL_LAMPS_GROUP_ID.equals(key))) {
                GroupDataModel groupModel = ((SampleAppActivity)getActivity()).groupModels.get(key);

                if (groupModel != null) {
                    ((SampleAppActivity)getActivity()).pendingGroupModel = new GroupDataModel(groupModel);
                    ((PageMainContainerFragment)parent).showSelectMembersChildFragment();
                }
            }
        } else {
            super.onClick(view);
        }
    }

    public void updateInfoFields(GroupDataModel groupModel) {
        if (groupModel.id.equals(key)) {
            stateAdapter.setCapability(groupModel.getCapability());
            super.updateInfoFields(groupModel);

            String details = Util.createMemberNamesString((SampleAppActivity)getActivity(), groupModel.members, ", ", R.string.group_info_members_none);
            TextView membersValue = (TextView)(view.findViewById(R.id.groupInfoMembers).findViewById(R.id.nameValueValueText));

            if (details != null && !details.isEmpty()) {
                membersValue.setText(details);
            }
        }
    }

    @Override
    protected int getLayoutID() {
        return R.layout.fragment_group_info;
    }

    @Override
    protected void onHeaderClick() {
        if (!AllLampsDataModel.ALL_LAMPS_GROUP_ID.equals(key)) {
            SampleAppActivity activity = (SampleAppActivity)getActivity();
            GroupDataModel groupModel = activity.groupModels.get(key);

            activity.showItemNameDialog(R.string.title_group_rename, new UpdateGroupNameAdapter(groupModel, (SampleAppActivity) getActivity()));
        }
    }
}
