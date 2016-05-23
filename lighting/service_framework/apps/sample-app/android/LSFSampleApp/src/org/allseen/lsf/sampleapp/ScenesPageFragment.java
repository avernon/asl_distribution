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

public class ScenesPageFragment extends PageMainContainerFragment {
    public static final String CHILD_TAG_SELECT_EFFECT = "SELECT_EFFECT";
    public static final String CHILD_TAG_CONSTANT_EFFECT = "CONSTANT_EFFECT";
    public static final String CHILD_TAG_TRANSITION_EFFECT = "TRANSITION_EFFECT";
    public static final String CHILD_TAG_PULSE_EFFECT = "PULSE_EFFECT";

    public static final String CHILD_TAG_EFFECT_DURATION = "EFFECT_DURATION";
    public static final String CHILD_TAG_EFFECT_PERIOD = "EFFECT_PERIOD";
    public static final String CHILD_TAG_EFFECT_COUNT = "EFFECT_COUNT";

    public static String TAG;

    protected boolean isMasterMode;

    public void setMasterMode(boolean isMasterMode) {
        this.isMasterMode = isMasterMode;
    }

    public boolean isMasterMode() {
        return isMasterMode;
    }

    public void showSelectEffectChildFragment() {
        showChildFragment(CHILD_TAG_SELECT_EFFECT, null);
    }

    public void showNoEffectChildFragment() {
        showChildFragment(CHILD_TAG_CONSTANT_EFFECT, ((SampleAppActivity)getActivity()).pendingNoEffectModel.id);
    }

    public void showTransitionEffectChildFragment() {
        showChildFragment(CHILD_TAG_TRANSITION_EFFECT, ((SampleAppActivity)getActivity()).pendingTransitionEffectModel.id);
    }

    public void showPulseEffectChildFragment() {
        showChildFragment(CHILD_TAG_PULSE_EFFECT, ((SampleAppActivity)getActivity()).pendingPulseEffectModel.id);
    }

    public void showEnterDurationChildFragment() {
        SampleAppActivity activity = (SampleAppActivity)getActivity();
        String tag = activity.pendingTransitionEffectModel != null ? activity.pendingTransitionEffectModel.id : activity.pendingPulseEffectModel.id;
        showChildFragment(CHILD_TAG_EFFECT_DURATION, tag);
    }

    public void showEnterPeriodChildFragment() {
        showChildFragment(CHILD_TAG_EFFECT_PERIOD, ((SampleAppActivity)getActivity()).pendingPulseEffectModel.id);
    }

    public void showEnterCountChildFragment() {
        showChildFragment(CHILD_TAG_EFFECT_COUNT, ((SampleAppActivity)getActivity()).pendingPulseEffectModel.id);
    }

    @Override
    protected PageFrameChildFragment createChildFragment(String tag)
    {
        if (tag == CHILD_TAG_SELECT_EFFECT) {
            return createSelectEffectChildFragment();
        } else if (tag == CHILD_TAG_CONSTANT_EFFECT) {
            return createConstantEffectChildFragment();
        } else if (tag == CHILD_TAG_TRANSITION_EFFECT) {
            return createTransitionEffectChildFragment();
        } else if (tag == CHILD_TAG_PULSE_EFFECT) {
            return createPulseEffectChildFragment();
        } else if (tag == CHILD_TAG_EFFECT_DURATION) {
            return createEnterDurationChildFragment();
        } else if (tag == CHILD_TAG_EFFECT_PERIOD) {
            return createEnterPeriodChildFragment();
        } else if (tag == CHILD_TAG_EFFECT_COUNT) {
            return createEnterCountChildFragment();
        } else {
            return super.createChildFragment(tag);
        }
    }

    @Override
    public PageFrameChildFragment createTableChildFragment() {
        return new ScenesTableFragment();
    }

    @Override
    public PageFrameChildFragment createInfoChildFragment() {
        return isMasterMode ? new MasterSceneInfoFragment() : new BasicSceneInfoFragment();
    }

    @Override
    public PageFrameChildFragment createPresetsChildFragment() {
        return new BasicSceneElementPresetsFragment();
    }

    @Override
    public PageFrameChildFragment createEnterNameChildFragment() {
        return isMasterMode ? new MasterSceneEnterNameFragment() : new BasicSceneEnterNameFragment();
    }

    @Override
    public PageFrameChildFragment createSelectMembersChildFragment() {
        return isMasterMode ? new MasterSceneSelectMembersFragment() : new BasicSceneSelectMembersFragment();
    }

    public PageFrameChildFragment createSelectEffectChildFragment() {
        return isMasterMode ? null : new BasicSceneSelectEffectFragment();
    }

    public PageFrameChildFragment createConstantEffectChildFragment() {
        return isMasterMode ? null : new NoEffectFragment();
    }

    public PageFrameChildFragment createTransitionEffectChildFragment() {
        return isMasterMode ? null : new TransitionEffectFragment();
    }

    public PageFrameChildFragment createPulseEffectChildFragment() {
        return isMasterMode ? null : new PulseEffectFragment();
    }

    public PageFrameChildFragment createEnterDurationChildFragment() {
        return new EnterDurationFragment();
    }

    public PageFrameChildFragment createEnterPeriodChildFragment() {
        return new EnterPeriodFragment();
    }

    public PageFrameChildFragment createEnterCountChildFragment() {
        return new EnterCountFragment();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View root = super.onCreateView(inflater, container, savedInstanceState);

        ScenesPageFragment.TAG = getTag();

        return root;
    }

    @Override
    public int onBackPressed() {
        String startingChildTag = child.getTag();
        int backStackCount = super.onBackPressed();

        if (!isMasterMode && CHILD_TAG_ENTER_NAME.equals(startingChildTag)) {
            // To support the basic scene creation workflow, when going backwards
            // from the enter name fragment we have to skip over the dummy scene
            // info fragment (see SampleAppActivity.doAddScene()). So we queue up
            // a second back press here.
            ((SampleAppActivity)getActivity()).postOnBackPressed();
        }

        return backStackCount;
    }
}
