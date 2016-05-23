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
import org.allseen.lsf.sdk.Effect;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;
import android.view.ViewGroup;

public abstract class SceneItemSelectEffectTypeFragment extends SelectableItemTableFragment {
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View root = super.onCreateView(inflater, container, savedInstanceState);

        updateSelectableItemRow(inflater, root, Effect.EFFECT_TYPE_PRESET, getResources().getString(R.string.effect_sort_constant), R.drawable.list_constant_icon, getResources().getString(getPresetEffectNameID()), true);
        updateSelectableItemRow(inflater, root, Effect.EFFECT_TYPE_TRANSITION, getResources().getString(R.string.effect_sort_transition), R.drawable.list_transition_icon, getResources().getString(R.string.effect_name_transition), false);
        updateSelectableItemRow(inflater, root, Effect.EFFECT_TYPE_PULSE, getResources().getString(R.string.effect_sort_pulse), R.drawable.list_pulse_icon, getResources().getString(R.string.effect_name_pulse), false);

        return root;
    }

    @Override
    protected String getHeaderText() {
        SampleAppActivity activity = (SampleAppActivity)getActivity();
        String members = Util.formatMemberNamesString(activity, getPendingSceneElementMemberLampIDs(), getPendingSceneElementMemberGroupIDs(), MemberNamesOptions.en, 3, getPendingSceneItemName());

        return String.format(getString(R.string.basic_scene_select_effect), members);
    }


    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        super.onCreateOptionsMenu(menu, inflater);

        ((SampleAppActivity)getActivity()).updateActionBar(R.string.title_effect_add, false, false, true, false, true);
    }

    @Override
    protected boolean isExclusive() {
        return true;
    }

    protected abstract int getPresetEffectNameID();
    protected abstract String getPendingSceneItemName();
    protected abstract String[] getPendingSceneElementMemberLampIDs();
    protected abstract String[] getPendingSceneElementMemberGroupIDs();
}
