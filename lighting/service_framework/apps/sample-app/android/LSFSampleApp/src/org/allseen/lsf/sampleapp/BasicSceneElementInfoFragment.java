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

import java.util.Map;

import org.allseen.lsf.LampState;
import org.allseen.lsf.PresetPulseEffect;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.SeekBar;

public abstract class BasicSceneElementInfoFragment extends DimmableItemInfoFragment {

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View root = super.onCreateView(inflater, container, savedInstanceState);
        SampleAppActivity activity = (SampleAppActivity)getActivity();
        BasicSceneElementDataModel pendingModel = getPendingSceneElementDataModel();

        if (pendingModel.presetID != null && !pendingModel.presetID.equals(PresetPulseEffect.PRESET_ID_CURRENT_STATE)) {
            PresetDataModel presetModel = activity.presetModels.get(pendingModel.presetID);

            if (presetModel != null) {
                pendingModel.state = presetModel.state;
            } else {
                pendingModel.presetID = null;
            }
        }

        return root;
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        super.onCreateOptionsMenu(menu, inflater);

        ((SampleAppActivity)getActivity()).updateActionBar(R.string.title_basic_scene_element_add, false, false, false, true, true);
    }

    @Override
    public void onClick(View view) {
        int viewID = view.getId();

        if (viewID == R.id.statusButtonPower) {
            onHeaderClick();
        } else {
            super.onClick(view);
        }
    }

    @Override
    protected void onHeaderClick() {
        // TODO-FIX dialog to change effect type here
    }

    // Override parent to update the pending lamp state rather than call the activity
    @Override
    public void setField(SeekBar seekBar) {
        int seekBarID = seekBar.getId();
        int seekBarProgress = seekBar.getProgress();
        Object seekBarTag = seekBar.getTag();
        LampState pendingState = getPendingSceneElementState(seekBarTag);

        if (seekBarID == R.id.stateSliderBrightness) {
            pendingState.setBrightness(DimmableItemScaleConverter.convertBrightnessViewToModel(seekBarProgress));
        } else if (seekBarID == R.id.stateSliderHue) {
            pendingState.setHue(DimmableItemScaleConverter.convertHueViewToModel(seekBarProgress));
        } else if (seekBarID == R.id.stateSliderSaturation) {
            pendingState.setSaturation(DimmableItemScaleConverter.convertSaturationViewToModel(seekBarProgress));
        } else if (seekBarID == R.id.stateSliderColorTemp) {
            pendingState.setColorTemp(DimmableItemScaleConverter.convertColorTempViewToModel(seekBarProgress + DimmableItemScaleConverter.VIEW_COLORTEMP_MIN));
        }

        updatePresetFields(pendingState, getLampStateViewAdapter(seekBarTag));
        updatePresetID(getMatchingPreset(pendingState), seekBarTag);

        setColorIndicator(getLampStateViewAdapter(seekBarTag).stateView, pendingState);
    }

    @Override
    public void updatePresetFields() {
        updatePresetFields(getPendingSceneElementDataModel());
    }

    protected void updatePresetID(String presetID, Object viewTag) {
        getPendingSceneElementDataModel().presetID = presetID;
    }

    protected LampState getPendingSceneElementState(Object viewTag) {
        return getPendingSceneElementDataModel().state;
    }

    protected LampStateViewAdapter getLampStateViewAdapter(Object viewTag) {
        return stateAdapter;
    }

    protected String getMatchingPreset(LampState itemState) {
        Map<String, PresetDataModel> presetModels = ((SampleAppActivity)getActivity()).presetModels;

        for (PresetDataModel presetModel : presetModels.values()) {
            if (presetModel.stateEquals(itemState)) {
                return presetModel.id;
            }
        }

        return null;
    }

    @Override
    public void onActionDone() {
        SampleAppActivity activity = (SampleAppActivity)getActivity();
        BasicSceneElementDataModel elementModel = getPendingSceneElementDataModel();

        elementModel.members = activity.pendingBasicSceneElementMembers;
        elementModel.capability = activity.pendingBasicSceneElementCapability;

        updatePendingSceneElement();

        activity.pendingBasicSceneElementMembers = null;
        activity.pendingBasicSceneElementCapability = null;

        activity.pendingNoEffectModel = null;
        activity.pendingTransitionEffectModel = null;
        activity.pendingPulseEffectModel = null;

        parent.popBackStack(PageFrameParentFragment.CHILD_TAG_INFO);
    }

    protected abstract BasicSceneElementDataModel getPendingSceneElementDataModel();
    protected abstract void updatePendingSceneElement();
}
