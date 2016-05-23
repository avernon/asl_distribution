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

import org.allseen.lsf.sampleapp.DimmableItemPresetsFragment;
import org.allseen.lsf.sdk.MyLampState;
import org.allseen.lsf.sdk.Preset;

import android.util.Log;

public class SceneElementV2PresetsFragment extends DimmableItemPresetsFragment {

    @Override
    protected MyLampState getItemLampState() {
        MyLampState lampState;

        if (PresetEffectFragment.pendingPresetEffect != null) {
            lampState = PresetEffectFragment.pendingPresetEffect.state;
        } else if (TransitionEffectV2Fragment.pendingTransitionEffect != null) {
            lampState = TransitionEffectV2Fragment.pendingTransitionEffect.state;
        } else if (key2 != PulseEffectV2Fragment.STATE2_ITEM_TAG) {
            lampState = PulseEffectV2Fragment.pendingPulseEffect.startState;
        } else {
            lampState = PulseEffectV2Fragment.pendingPulseEffect.endState;
        }

        return lampState;
    }

    @Override
    protected void doApplyPreset(Preset preset) {
        if (PresetEffectFragment.pendingPresetEffect != null) {
            Log.e(SampleAppActivity.TAG, "Cannot assign a preset to a preset");
        } else if (TransitionEffectV2Fragment.pendingTransitionEffect != null) {
            TransitionEffectV2Fragment.pendingTransitionEffect.presetID = preset.getId();
            TransitionEffectV2Fragment.pendingTransitionEffect.state = preset.getState();
        } else if (key2 != PulseEffectV2Fragment.STATE2_ITEM_TAG) {
            PulseEffectV2Fragment.pendingPulseEffect.startPresetID = preset.getId();
            PulseEffectV2Fragment.pendingPulseEffect.startState = preset.getState();
        } else {
            PulseEffectV2Fragment.pendingPulseEffect.endPresetID = preset.getId();
            PulseEffectV2Fragment.pendingPulseEffect.endState = preset.getState();
        }
    }
}
