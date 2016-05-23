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

import org.allseen.lsf.sampleapp.R;
import org.allseen.lsf.sdk.LampCapabilities;
import org.allseen.lsf.sdk.LampStateUniformity;
import org.allseen.lsf.sdk.MyLampState;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

public class PresetEffectFragment extends EffectV2InfoFragment {
    public static PendingPresetEffect pendingPresetEffect = null;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = super.onCreateView(inflater, container, savedInstanceState);

        setImageButtonBackgroundResource(statusView, R.id.statusButtonPower, R.drawable.list_constant_icon);

        ((TextView)statusView.findViewById(R.id.statusLabelName)).setText(R.string.label_effect_name);
        ((Button)stateView.findViewById(R.id.stateButton)).setVisibility(View.GONE);

        initLampState();

        updateInfoFields(pendingPresetEffect.name, new MyLampState(pendingPresetEffect.state), LampCapabilities.allCapabilities, pendingPresetEffect.uniformity);

        return view;
    }

    @Override
    public int getTitleID() {
        return R.string.title_preset_add;
    }

    @Override
    protected void updateInfoFields(String name, MyLampState state, LampCapabilities capability, LampStateUniformity uniformity) {
        stateAdapter.setCapability(capability);

        super.updateInfoFields(name, state, capability, uniformity);

        updatePresetInfoFields();
    }

    protected void updatePresetInfoFields() {
        // Superclass updates the icon, so we have to re-override
        setImageButtonBackgroundResource(statusView, R.id.statusButtonPower, R.drawable.list_constant_icon);
    }

    @Override
    protected int getLayoutID() {
        return R.layout.fragment_effect_constant;
    }

    @Override
    protected String getPendingEffectID() {
        return pendingPresetEffect.id;
    }

    @Override
    protected MyLampState getPendingLampState(int index) {
        return pendingPresetEffect.state;
    }

    @Override
    protected String getPendingPresetID(int index) {
        return pendingPresetEffect.id;
    }

    @Override
    protected void setPendingPresetID(int index, String presetID) {
        // Preset effects cannot reference other presets, so we
        // just validate the index here.
        logErrorOnInvalidIndex(index);
    }

    @Override
    public void onActionDone() {
        SceneElementV2InfoFragment.pendingSceneElement.pendingPresetEffect = pendingPresetEffect;

        BasicSceneV2InfoFragment.onPendingSceneElementDone();

        parent.popBackStack(ScenesPageFragment.CHILD_TAG_INFO);
    }
}
