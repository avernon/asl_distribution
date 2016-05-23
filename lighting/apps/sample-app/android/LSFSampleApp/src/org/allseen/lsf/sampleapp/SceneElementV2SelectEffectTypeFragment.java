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

import java.util.Collection;
import java.util.List;

import org.allseen.lsf.sampleapp.SceneItemSelectEffectTypeFragment;
import org.allseen.lsf.sdk.Effect;

public class SceneElementV2SelectEffectTypeFragment extends SceneItemSelectEffectTypeFragment {
    public static void clearPendingEffects() {
        PresetEffectFragment.pendingPresetEffect = null;
        TransitionEffectV2Fragment.pendingTransitionEffect = null;
        PulseEffectV2Fragment.pendingPulseEffect = null;
    }

    @Override
    protected int getPresetEffectNameID() {
        return R.string.effect_name_preset;
    }

    @Override
    protected String getPendingSceneItemName() {
        return SceneElementV2InfoFragment.pendingSceneElement.name;
    }

    @Override
    protected String[] getPendingSceneElementMemberLampIDs() {
        Collection<String> lampIDs = SceneElementV2InfoFragment.pendingSceneElement.lamps;

        return lampIDs.toArray(new String[lampIDs.size()]);
    }

    @Override
    protected String[] getPendingSceneElementMemberGroupIDs() {
        Collection<String> groupIDs = SceneElementV2InfoFragment.pendingSceneElement.groups;

        return groupIDs.toArray(new String[groupIDs.size()]);
    }

    @Override
    protected boolean isItemSelected(String itemID) {
        boolean isSelected = false;

        if (itemID.equals(Effect.EFFECT_TYPE_PRESET) && PresetEffectFragment.pendingPresetEffect != null) {
            isSelected = true;
        } else if (itemID.equals(Effect.EFFECT_TYPE_TRANSITION) && TransitionEffectV2Fragment.pendingTransitionEffect != null) {
            isSelected = true;
        } else if (itemID.equals(Effect.EFFECT_TYPE_PULSE) && PulseEffectV2Fragment.pendingPulseEffect != null) {
            isSelected = true;
        }

        return isSelected;
    }

    @Override
    public void onActionNext() {
        List<String> selectedIDs = getSelectedIDs();
        String effectID = selectedIDs != null && selectedIDs.size() > 0 ? selectedIDs.get(0) : Effect.EFFECT_TYPE_PRESET;

        clearPendingEffects();

        if (effectID.equals(Effect.EFFECT_TYPE_PRESET)) {
            PresetEffectFragment.pendingPresetEffect = new PendingPresetEffect();
            ((ScenesPageFragment)parent).showConstantEffectChildFragment();
        } else if (effectID.equals(Effect.EFFECT_TYPE_TRANSITION)) {
            TransitionEffectV2Fragment.pendingTransitionEffect = new PendingTransitionEffectV2();
            ((ScenesPageFragment)parent).showTransitionEffectChildFragment();
        } else if (effectID.equals(Effect.EFFECT_TYPE_PULSE)) {
            PulseEffectV2Fragment.pendingPulseEffect = new PendingPulseEffectV2();
            ((ScenesPageFragment)parent).showPulseEffectChildFragment();
        }
    }
}
