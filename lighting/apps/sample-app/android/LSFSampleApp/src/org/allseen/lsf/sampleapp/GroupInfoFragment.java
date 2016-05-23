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

import java.util.ArrayList;
import java.util.List;

import org.allseen.lsf.sdk.Group;
import org.allseen.lsf.sdk.LightingDirector;
import org.allseen.lsf.sdk.MyLampState;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class GroupInfoFragment extends DimmableItemInfoFragment {
    public static String pendingGroupID;
    public static String pendingGroupName;
    public static List<String> pendingGroupContainedGroups;
    public static List<String> pendingGroupContainedLamps;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = super.onCreateView(inflater, container, savedInstanceState);

        itemType = SampleAppActivity.Type.GROUP;

        ((TextView)statusView.findViewById(R.id.statusLabelName)).setText(R.string.label_group_name);

        // displays members of this group
        TextView membersLabel = (TextView)(view.findViewById(R.id.groupInfoMembers).findViewById(R.id.nameValueNameText));
        membersLabel.setText(R.string.group_info_label_members);
        membersLabel.setClickable(true);
        membersLabel.setOnClickListener(this);

        TextView membersValue = (TextView)(view.findViewById(R.id.groupInfoMembers).findViewById(R.id.nameValueValueText));
        membersValue.setClickable(true);
        membersValue.setOnClickListener(this);

        updateInfoFields(LightingDirector.get().getGroup(key));

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
            if (parent != null) {
                Group group = LightingDirector.get().getGroup(key);

                if ((group != null) && (!group.isAllLampsGroup())) {
                    pendingGroupID = group.getId();
                    pendingGroupName = group.getName();
                    pendingGroupContainedGroups = new ArrayList<String>();
                    pendingGroupContainedLamps = new ArrayList<String>();

                    ((PageMainContainerFragment)parent).showSelectMembersChildFragment();
                }
            }
        } else {
            super.onClick(view);
        }
    }

    public void updateInfoFields(Group group) {
        if (group.getId().equals(key)) {
            stateAdapter.setCapability(group.getCapability());
            super.updateInfoFields(group);

            String details = Util.createMemberNamesString((SampleAppActivity)getActivity(), group, ", ", R.string.group_info_members_none);
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
    protected int getColorTempMin() {
        Group group = LightingDirector.get().getGroup(key);
        int colorTempMin = group != null ? group.getColorTempMin() : LightingDirector.COLORTEMP_MIN;

        return colorTempMin;
    }

    @Override
    protected int getColorTempSpan() {
        Group group = LightingDirector.get().getGroup(key);
        int colorTempMin = group != null ? group.getColorTempMin() : LightingDirector.COLORTEMP_MIN;
        int colorTempMax = group != null ? group.getColorTempMax() : LightingDirector.COLORTEMP_MAX;

        return colorTempMax - colorTempMin;
    }

    @Override
    protected int getColorTempDefault() {
        Group group = LightingDirector.get().getGroup(key);

        return group != null ? group.getColor().getColorTemperature() : LightingDirector.COLORTEMP_MIN;
    }

    @Override
    protected void onHeaderClick() {
        Group group = LightingDirector.get().getGroup(key);

        if (!group.isAllLampsGroup()) {
            SampleAppActivity activity = (SampleAppActivity)getActivity();

            activity.showItemNameDialog(R.string.title_group_rename, new UpdateGroupNameAdapter(group, activity));
        }
    }

    @Override
    protected MyLampState getItemLampState(String groupID){
        Group group = LightingDirector.get().getGroup(groupID);
        return group != null ? group.getState() : null;
    }
}
