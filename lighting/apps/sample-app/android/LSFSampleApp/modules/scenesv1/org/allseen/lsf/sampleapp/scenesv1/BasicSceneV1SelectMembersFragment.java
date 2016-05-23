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

import java.util.Arrays;
import java.util.Collection;
import org.allseen.lsf.sampleapp.R;
import org.allseen.lsf.sampleapp.SampleAppActivity;
import org.allseen.lsf.sampleapp.SceneItemSelectMembersFragment;
import org.allseen.lsf.sampleapp.ScenesPageFragment;
import org.allseen.lsf.sdk.ColorAverager;
import org.allseen.lsf.sdk.LampCapabilities;
import org.allseen.lsf.sdk.model.ColorStateConverter;
import android.view.Menu;
import android.view.MenuInflater;

public class BasicSceneV1SelectMembersFragment extends SceneItemSelectMembersFragment {

    public BasicSceneV1SelectMembersFragment() {
        super(R.string.label_basic_scene);
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        super.onCreateOptionsMenu(menu, inflater);

        ((SampleAppActivity)getActivity()).updateActionBar(R.string.title_basic_scene_element_add, false, false, true, false, true);
    }

    @Override
    protected String getHeaderText() {
        return getString(R.string.basic_scene_select_members);
    }

    @Override
    protected String getPendingItemID() {
        return BasicSceneV1InfoFragment.pendingBasicSceneModel.id;
    }

    @Override
    protected int getMixedSelectionMessageID() {
        return R.string.mixing_lamp_types_message_scene;
    }

    @Override
    protected int getMixedSelectionPositiveButtonID() {
        return R.string.create_scene;
    }

    @Override
    protected Collection<String> getPendingGroupIDs() {
        return Arrays.asList(EffectV1InfoFragment.pendingBasicSceneElementMembers.getLampGroups());
    }

    @Override
    protected Collection<String> getPendingLampIDs() {
        return Arrays.asList(EffectV1InfoFragment.pendingBasicSceneElementMembers.getLamps());
    }

    @Override
    protected void setPendingMemberIDs(Collection<String> lampIDs, Collection<String> groupIDs) {
        EffectV1InfoFragment.pendingBasicSceneElementMembers.setLamps(lampIDs.toArray(new String[lampIDs.size()]));
        EffectV1InfoFragment.pendingBasicSceneElementMembers.setLampGroups(groupIDs.toArray(new String[groupIDs.size()]));
    }

    @Override
    protected void setPendingCapability(LampCapabilities capability) {
        EffectV1InfoFragment.pendingBasicSceneElementCapability = capability;
    }

    @Override
    protected boolean getPendingMembersHaveEffects() {
        return EffectV1InfoFragment.pendingBasicSceneElementMembersHaveEffects;
    }

    @Override
    protected void setPendingMembersHaveEffects(boolean haveEffects) {
        EffectV1InfoFragment.pendingBasicSceneElementMembersHaveEffects = haveEffects;
    }

    @Override
    protected int getPendingMembersMinColorTemp() {
        return EffectV1InfoFragment.pendingBasicSceneElementMembersMinColorTemp;
    }

    @Override
    protected void setPendingMembersMinColorTemp(int minColorTemp) {
        EffectV1InfoFragment.pendingBasicSceneElementMembersMinColorTemp = minColorTemp;
    }

    @Override
    protected int getPendingMembersMaxColorTemp() {
        return EffectV1InfoFragment.pendingBasicSceneElementMembersMaxColorTemp;
    }

    @Override
    protected void setPendingMembersMaxColorTemp(int maxColorTemp) {
        EffectV1InfoFragment.pendingBasicSceneElementMembersMaxColorTemp = maxColorTemp;
    }

    @Override
    protected ColorAverager getPendingColorTempAverager() {
        return EffectV1InfoFragment.pendingBasicSceneElementColorTempAverager;
    }

    @Override
    protected void updatePendingColorTempAverager(int viewColorTemp) {
        getPendingColorTempAverager().add(ColorStateConverter.convertColorTempViewToModel(viewColorTemp));
    }

    @Override
    public void onActionNext() {
        SampleAppActivity activity = (SampleAppActivity)getActivity();

        if (processSelection()) {
            if (getPendingMembersHaveEffects()) {
                if (NoEffectFragment.pendingNoEffect != null) {
                    showNoEffectChildFragment(activity);
                } else if (TransitionEffectV1Fragment.pendingTransitionEffect != null) {
                    showTransitionEffectChildFragment(activity);
                } else if (PulseEffectV1Fragment.pendingPulseEffect != null) {
                    showPulseEffectChildFragment(activity);
                } else {
                    showSelectEffectChildFragment(activity);
                }
            } else {
                if (NoEffectFragment.pendingNoEffect == null) {
                    NoEffectFragment.pendingNoEffect = new PendingNoEffect();
                }

                showNoEffectChildFragment(activity);
            }
        }
    }

    protected void showSelectEffectChildFragment(SampleAppActivity activity) {
        NoEffectFragment.pendingNoEffect = null;
        TransitionEffectV1Fragment.pendingTransitionEffect = null;
        PulseEffectV1Fragment.pendingPulseEffect = null;

        ((ScenesPageFragment)parent).showSelectEffectTypeChildFragment();
    }

    protected void showNoEffectChildFragment(SampleAppActivity activity) {
        TransitionEffectV1Fragment.pendingTransitionEffect = null;
        PulseEffectV1Fragment.pendingPulseEffect = null;

        ((ScenesPageFragment)parent).showConstantEffectChildFragment();
    }

    protected void showTransitionEffectChildFragment(SampleAppActivity activity) {
        NoEffectFragment.pendingNoEffect = null;
        PulseEffectV1Fragment.pendingPulseEffect = null;

        ((ScenesPageFragment)parent).showTransitionEffectChildFragment();
    }

    protected void showPulseEffectChildFragment(SampleAppActivity activity) {
        NoEffectFragment.pendingNoEffect = null;
        TransitionEffectV1Fragment.pendingTransitionEffect = null;

        ((ScenesPageFragment)parent).showPulseEffectChildFragment();
    }
}
