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

import android.app.ActionBar;
import android.content.Context;
import android.support.v4.view.ViewPager;
import android.util.AttributeSet;
import android.view.MotionEvent;

public class SampleAppViewPager extends ViewPager {

    SampleAppActivity activity;

    public SampleAppViewPager(Context context) {
        super(context);
    }

    public SampleAppViewPager(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public void setActivity(SampleAppActivity activity) {
        this.activity = activity;

        final ActionBar actionBar = activity.getActionBar();
        final PageFrameParentAdapter pageAdapter = new PageFrameParentAdapter(activity, activity.getSupportFragmentManager());

        actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_TABS);
        actionBar.setDisplayHomeAsUpEnabled(false);

        setAdapter(pageAdapter);
        setOffscreenPageLimit(3);

        setOnPageChangeListener(new ViewPager.SimpleOnPageChangeListener() {
            @Override
            public void onPageSelected(int tabIndex) {
                actionBar.setSelectedNavigationItem(tabIndex);
            }
        });

        for (int tabIndex = 0; tabIndex < pageAdapter.getCount(); tabIndex++) {
            actionBar.addTab(actionBar.newTab().setText(activity.getPageTitle(tabIndex)).setTabListener(activity));
        }
    }

    @Override
    public boolean onInterceptTouchEvent(MotionEvent event) {

    	if(activity.getToast().getView().isShown()){
			System.out.println("cancel the toast");
			activity.getToast().cancel();
		}

    	if ((activity != null) && (activity.isSwipeable())) {
    		return super.onInterceptTouchEvent(event);
    	} else {
    		return false;
    	}
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if ((activity != null) && (activity.isSwipeable())) {
            return super.onTouchEvent(event);
        } else {
            return false;
        }
    }
}
