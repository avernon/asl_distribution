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

import org.allseen.lsf.LampState;
import org.allseen.lsf.sdk.model.ColorItemDataModel;
import org.allseen.lsf.sdk.model.PresetDataModel;
import org.allseen.lsf.sdk.model.PulseEffectDataModel;
import org.allseen.lsf.sdk.model.SceneElementDataModel;

public class BasicSceneElementPresetsFragment extends DimmableItemPresetsFragment {

    @Override
    protected ColorItemDataModel getDimmableItemDataModel() {
        SampleAppActivity activity = (SampleAppActivity)getActivity();
        ColorItemDataModel itemModel;

        if (activity.pendingNoEffectModel != null) {
            itemModel = activity.pendingNoEffectModel;
        } else if (activity.pendingTransitionEffectModel != null) {
            itemModel = activity.pendingTransitionEffectModel;
        } else {
            itemModel = activity.pendingPulseEffectModel;
        }

        return itemModel;
    }

    @Override
    protected boolean isItemSelected(PresetDataModel presetModel) {
        if (key2 == PulseEffectFragment.STATE2_ITEM_TAG) {
            PulseEffectDataModel pulseModel = (PulseEffectDataModel)getDimmableItemDataModel();
            return presetModel.stateEquals(pulseModel.endState);
        } else {
            return super.isItemSelected(presetModel);
        }
    }

    @Override
    protected void doSavePreset(String presetName) {
        if (key2 == PulseEffectFragment.STATE2_ITEM_TAG) {
            PulseEffectDataModel pulseModel = (PulseEffectDataModel)getDimmableItemDataModel();
            doSavePreset(presetName, pulseModel.endState);
        } else {
            super.doSavePreset(presetName);
        }
    }

    @Override
    protected void doApplyPreset(PresetDataModel presetModel) {
        if (key2 == PulseEffectFragment.STATE2_ITEM_TAG) {
            PulseEffectDataModel pulseModel = (PulseEffectDataModel)getDimmableItemDataModel();
            pulseModel.endPresetID = presetModel.id;
            pulseModel.endState = new LampState(presetModel.state);
        } else {
            SceneElementDataModel elementModel = (SceneElementDataModel)getDimmableItemDataModel();
            elementModel.presetID = presetModel.id;
            elementModel.state = new LampState(presetModel.state);
        }
    }
}
