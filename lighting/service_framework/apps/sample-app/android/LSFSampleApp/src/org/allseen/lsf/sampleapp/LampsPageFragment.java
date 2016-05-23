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

public class LampsPageFragment extends PageFrameParentFragment {
    public static final String CHILD_TAG_DETAILS = "DETAILS";

    public static String TAG;

    public void showDetailsChildFragment(String key) {
        showChildFragment(CHILD_TAG_DETAILS, key);
    }

    @Override
    protected PageFrameChildFragment createChildFragment(String tag)
    {
        return tag == CHILD_TAG_DETAILS ? createDetailsChildFragment() : super.createChildFragment(tag);
    }

    @Override
    public PageFrameChildFragment createTableChildFragment() {
        return new LampsTableFragment();
    }

    @Override
    public PageFrameChildFragment createInfoChildFragment() {
        return new LampInfoFragment();
    }

    @Override
    public PageFrameChildFragment createPresetsChildFragment() {
        return new LampPresetsFragment();
    }

    public PageFrameChildFragment createDetailsChildFragment() {
        return new LampDetailsFragment();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View root = super.onCreateView(inflater, container, savedInstanceState);

        LampsPageFragment.TAG = getTag();

        return root;
    }
}
