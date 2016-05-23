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
import android.view.View;
import android.view.ViewGroup;

public class GroupsPageFragment extends PageMainContainerFragment {
    public static String TAG;

    @Override
    public PageFrameChildFragment createTableChildFragment() {
        return new GroupsTableFragment();
    }

    @Override
    public PageFrameChildFragment createInfoChildFragment() {
        return new GroupInfoFragment();
    }

    @Override
    public PageFrameChildFragment createPresetsChildFragment() {
        return new GroupPresetsFragment();
    }

    @Override
    public PageFrameChildFragment createEnterNameChildFragment() {
        return new GroupEnterNameFragment();
    }

    @Override
    public PageFrameChildFragment createSelectMembersChildFragment() {
        return new GroupSelectMembersFragment();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View root = super.onCreateView(inflater, container, savedInstanceState);

        GroupsPageFragment.TAG = getTag();

        return root;
    }
}
