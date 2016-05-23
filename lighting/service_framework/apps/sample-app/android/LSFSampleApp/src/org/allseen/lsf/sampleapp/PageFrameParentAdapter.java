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

import java.util.Locale;

import android.content.Context;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;

public class PageFrameParentAdapter extends FragmentPagerAdapter {

    private final Context context;

    public PageFrameParentAdapter(Context context, FragmentManager fragmentManager) {
        super(fragmentManager);

        this.context = context;
    }

    @Override
    public int getCount() {
        return 3;
    }

    @Override
    public Fragment getItem(int index) {
        PageFrameParentFragment parentFragment;

        if (index == 0) {
            parentFragment = new LampsPageFragment();
        } else if (index == 1) {
            parentFragment = new GroupsPageFragment();
        } else if (index == 2) {
            parentFragment = new ScenesPageFragment();
        } else {
            parentFragment = null;
        }

        return parentFragment;
    }

    @Override
    public CharSequence getPageTitle(int index) {
        return ((SampleAppActivity) context).getPageTitle(index);
    }
}
