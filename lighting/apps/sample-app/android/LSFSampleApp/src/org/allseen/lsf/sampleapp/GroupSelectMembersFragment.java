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
import java.util.Arrays;
import java.util.Collection;
import java.util.List;

import org.allseen.lsf.sdk.Group;
import org.allseen.lsf.sdk.GroupMember;
import org.allseen.lsf.sdk.LightingDirector;

import android.view.Menu;
import android.view.MenuInflater;

public class GroupSelectMembersFragment extends SelectMembersFragment {

    public GroupSelectMembersFragment() {
        super(R.string.label_group);
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        super.onCreateOptionsMenu(menu, inflater);

        SampleAppActivity activity = (SampleAppActivity)getActivity();

        activity.updateActionBar(isAddMode() ? R.string.title_group_add : R.string.title_group_edit, false, false, false, true, true);
    }

    @Override
    protected boolean isParentOfPendingGroup(Group group) {
        return !isAddMode() && group.hasGroupID(GroupInfoFragment.pendingGroupID);
    }

    @Override
    protected String getHeaderText() {
        return getString(R.string.group_select_members);
    }

    @Override
    protected String getPendingItemID() {
        return GroupInfoFragment.pendingGroupID;
    }

    @Override
    protected Collection<String> getPendingGroupIDs() {
        return GroupInfoFragment.pendingGroupContainedGroups;
    }

    @Override
    protected Collection<String> getPendingLampIDs() {
        return GroupInfoFragment.pendingGroupContainedLamps;
    }

    @Override
    protected void processSelection(SampleAppActivity activity, List<String> lampIDs, List<String> groupIDs, List<String> presetIDs, List<String> transitionEffectIDs, List<String> pulseEffectIDs, List<String> sceneElementIDs, List<String> sceneIDs) {
        List<GroupMember> members = new ArrayList<GroupMember>();

        members.addAll(Arrays.asList(LightingDirector.get().getLamps(lampIDs)));
        members.addAll(Arrays.asList(LightingDirector.get().getGroups(groupIDs)));

        if (!isAddMode()) {
            Group group = LightingDirector.get().getGroup(GroupInfoFragment.pendingGroupID);

            if (group != null) {
                group.modify(members.toArray(new GroupMember[members.size()]));
            }
        } else {
            LightingDirector.get().createGroup(members.toArray(new GroupMember[members.size()]), GroupInfoFragment.pendingGroupName);
        }
    }

    @Override
    protected int getMixedSelectionMessageID() {
        return R.string.mixing_lamp_types_message_group;
    }

    @Override
    protected int getMixedSelectionPositiveButtonID() {
        return R.string.create_group;
    }

    //TODO-REF Common
    protected boolean isAddMode() {
        return GroupInfoFragment.pendingGroupID == null || GroupInfoFragment.pendingGroupID.isEmpty();
    }
}
