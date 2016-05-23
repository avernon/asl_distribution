/*
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

import org.allseen.lsf.sdk.LampCapabilities;
import org.allseen.lsf.sdk.LampStateUniformity;
import org.allseen.lsf.sdk.MyLampState;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class TransitionEffectV2Fragment extends EffectV2InfoFragment {
    public static PendingTransitionEffectV2 pendingTransitionEffect = null;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = super.onCreateView(inflater, container, savedInstanceState);

        setTextViewValue(statusView, R.id.statusLabelName, getString(R.string.label_effect_name), 0);
        setTextViewValue(view.findViewById(R.id.infoDurationRow), R.id.nameValueNameText, getString(R.string.effect_info_transition_duration), 0);

        TextView effectName = (TextView)statusView.findViewById(R.id.statusTextName);
        effectName.setClickable(true);
        effectName.setOnClickListener(this);

        TextView durationName = (TextView)view.findViewById(R.id.infoDurationRow).findViewById(R.id.nameValueNameText);
        durationName.setClickable(true);
        durationName.setOnClickListener(this);

        TextView durationValue = (TextView)view.findViewById(R.id.infoDurationRow).findViewById(R.id.nameValueValueText);
        durationValue.setClickable(true);
        durationValue.setOnClickListener(this);

        initLampState();

        updateInfoFields(pendingTransitionEffect.name, getPendingLampState(0), LampCapabilities.allCapabilities, pendingTransitionEffect.uniformity);

        return view;
    }

    @Override
    protected void updateInfoFields(String name, MyLampState state, LampCapabilities capability, LampStateUniformity uniformity) {
        stateAdapter.setCapability(capability);

        super.updateInfoFields(name, state, capability, uniformity);

        updateTransitionEffectInfoFields();
    }

    protected void updateTransitionEffectInfoFields() {
        // Superclass updates the icon, so we have to re-override
        setImageButtonBackgroundResource(statusView, R.id.statusButtonPower, R.drawable.list_transition_icon);

        String durationValue = String.format(getString(R.string.effect_info_duration_format), pendingTransitionEffect.duration / 1000.0);
        setTextViewValue(view.findViewById(R.id.infoDurationRow), R.id.nameValueValueText, durationValue, R.string.units_seconds);
    }

    @Override
    public void onClick(View view) {
        int viewID = view.getId();

        if (viewID == R.id.nameValueNameText || viewID == R.id.nameValueValueText) {
            onDurationClick();
        } else {
            super.onClick(view);
        }
    }

    protected void onDurationClick() {
        EnterDurationFragment.transition = false;
        EnterDurationFragment.duration = pendingTransitionEffect.duration;

        ((ScenesPageFragment)parent).showEnterDurationChildFragment();
    }

    @Override
    protected String getPendingEffectID() {
        return pendingTransitionEffect.id;
    }

    @Override
    protected int getTitleID() {
        return R.string.title_effect_transition_add;
    }

    @Override
    protected MyLampState getPendingLampState(int index) {
        return pendingTransitionEffect.state;
    }

    @Override
    protected String getPendingPresetID(int index) {
        return pendingTransitionEffect.presetID;
    }

    @Override
    protected void setPendingPresetID(int index, String presetID) {
        pendingTransitionEffect.presetID = presetID;
    }

    @Override
    protected int getLayoutID() {
        return R.layout.fragment_effect_transition;
    }

    @Override
    public void onActionDone() {
        SceneElementV2InfoFragment.pendingSceneElement.pendingTransitionEffect = pendingTransitionEffect;

        BasicSceneV2InfoFragment.onPendingSceneElementDone();

        parent.popBackStack(ScenesPageFragment.CHILD_TAG_INFO);
    }
}
