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

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import org.allseen.lsf.sdk.Effect;
import org.allseen.lsf.sdk.GroupMember;
import org.allseen.lsf.sdk.LightingDirector;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;

public class SceneElementV2SelectEffectFragment extends SelectEffectsFragment {

    public SceneElementV2SelectEffectFragment() {
        super(R.string.label_scene_element);
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        super.onCreateOptionsMenu(menu, inflater);

        SampleAppActivity activity = (SampleAppActivity)getActivity();

        activity.updateActionBar(isAddMode() ? R.string.title_scene_element_add : R.string.title_scene_element_edit, false, true, false, true, true);
    }

    @Override
    public void onClick(View view) {
        if (view.getId() == R.id.selectableItemButtonIcon) {
            String itemID = view.getTag().toString();

            if (LightingDirector.get().getPreset(itemID) != null) {
                ((SampleAppActivity)getActivity()).showPresetMorePopup(view, itemID);
            } else if (LightingDirector.get().getTransitionEffect(itemID) != null) {
                ((SampleAppActivity)getActivity()).showTransitionEffectMorePopup(view, itemID);
            } else if (LightingDirector.get().getPulseEffect(itemID) != null) {
                ((SampleAppActivity)getActivity()).showPulseEffectMorePopup(view, itemID);
            }
        } else {
            super.onClick(view);
        }
    }

    @Override
    protected boolean showPresets() {
        return true;
    }

    @Override
    protected boolean showTransitionEffects() {
        return SceneElementV2InfoFragment.pendingSceneElement.hasEffects;
    }

    @Override
    protected boolean showPulseEffects() {
        return showTransitionEffects();
    }

    @Override
    protected boolean isItemSelected(String itemID) {
        return false; //TODO-FIX itemID.equals(SceneElementV2InfoFragment.pendingSceneElement.effectID);
    }

    @Override
    protected String getHeaderText() {
        return getString(R.string.scene_element_select_effect);
    }

    @Override
    protected String getPendingItemID() {
        return SceneElementV2InfoFragment.pendingSceneElement.id;
    }

    @Override
    protected void processSelection(SampleAppActivity activity, List<String> presetIDs, List<String> transitionEffectIDs, List<String> pulseEffectIDs) {
        LightingDirector director = LightingDirector.get();
        Effect effect = null;

        if (presetIDs.size() > 0) {
            effect = director.getPreset(presetIDs.get(0));
        } else if (transitionEffectIDs.size() > 0) {
            effect = director.getTransitionEffect(transitionEffectIDs.get(0));
        } else if (pulseEffectIDs.size() > 0) {
            effect = director.getPulseEffect(pulseEffectIDs.get(0));
        }

        ArrayList<GroupMember> memberList = new ArrayList<GroupMember>();

        memberList.addAll(Arrays.asList(director.getLamps(SceneElementV2InfoFragment.pendingSceneElement.lamps)));
        memberList.addAll(Arrays.asList(director.getGroups(SceneElementV2InfoFragment.pendingSceneElement.groups)));

        GroupMember[] members = memberList.toArray(new GroupMember[memberList.size()]);

        if (!isAddMode()) {
            director.getSceneElement(SceneElementV2InfoFragment.pendingSceneElement.id).modify(effect, members);
        } else {
            director.createSceneElement(effect, members, SceneElementV2InfoFragment.pendingSceneElement.name);
        }
    }
}
