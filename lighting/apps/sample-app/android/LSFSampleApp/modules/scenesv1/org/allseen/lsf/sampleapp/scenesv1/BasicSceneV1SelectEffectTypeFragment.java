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
package org.allseen.lsf.sampleapp.scenesv1;

import java.util.List;

import org.allseen.lsf.sampleapp.R;
import org.allseen.lsf.sampleapp.SceneItemSelectEffectTypeFragment;
import org.allseen.lsf.sampleapp.ScenesPageFragment;
import org.allseen.lsf.sdk.model.EffectType;

public class BasicSceneV1SelectEffectTypeFragment extends SceneItemSelectEffectTypeFragment {
    @Override
    protected int getPresetEffectNameID() {
        return R.string.effect_name_none;
    }

    @Override
    protected String getPendingSceneItemName() {
        return BasicSceneV1InfoFragment.pendingBasicSceneModel.getName();
    }

    @Override
    protected String[] getPendingSceneElementMemberLampIDs() {
        return EffectV1InfoFragment.pendingBasicSceneElementMembers.getLamps();
    }

    @Override
    protected String[] getPendingSceneElementMemberGroupIDs() {
        return EffectV1InfoFragment.pendingBasicSceneElementMembers.getLampGroups();
    }

    @Override
    protected boolean isItemSelected(String itemID) {
        EffectType effectType = EffectType.None;

        if (NoEffectFragment.pendingNoEffect != null) {
            effectType = EffectType.None;
        } else if (TransitionEffectV1Fragment.pendingTransitionEffect != null) {
            effectType = EffectType.Transition;
        } else if (PulseEffectV1Fragment.pendingPulseEffect != null) {
            effectType = EffectType.Pulse;
        }

        return effectType.toString().equals(itemID);
    }

    @Override
    public void onActionNext() {
        List<String> selectedIDs = getSelectedIDs();
        String effectID = selectedIDs != null && selectedIDs.size() > 0 ? selectedIDs.get(0) : EffectType.None.toString();

        if (effectID.equals(EffectType.None.toString())) {
            NoEffectFragment.pendingNoEffect = new PendingNoEffect();
            TransitionEffectV1Fragment.pendingTransitionEffect = null;
            PulseEffectV1Fragment.pendingPulseEffect = null;
            ((ScenesPageFragment)parent).showConstantEffectChildFragment();
        } else if (effectID.equals(EffectType.Transition.toString())) {
            NoEffectFragment.pendingNoEffect = null;
            TransitionEffectV1Fragment.pendingTransitionEffect = new PendingTransitionEffectV1();
            PulseEffectV1Fragment.pendingPulseEffect = null;
            ((ScenesPageFragment)parent).showTransitionEffectChildFragment();
        } else if (effectID.equals(EffectType.Pulse.toString())) {
            NoEffectFragment.pendingNoEffect = null;
            TransitionEffectV1Fragment.pendingTransitionEffect = null;
            PulseEffectV1Fragment.pendingPulseEffect = new PendingPulseEffectV1();
            ((ScenesPageFragment)parent).showPulseEffectChildFragment();
        }
    }
}
