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

import java.util.List;

import org.allseen.lsf.sampleapp.R;
import org.allseen.lsf.sampleapp.SampleAppActivity;
import org.allseen.lsf.sdk.LightingDirector;
import org.allseen.lsf.sdk.SceneElement;
import org.allseen.lsf.sdk.SceneV2;

import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;

public class BasicSceneV2SelectMembersFragment extends SelectMembersFragment {

    public BasicSceneV2SelectMembersFragment() {
        super(R.string.label_basic_scene);
    }

    @Override
    protected boolean showSceneElements() {
        return true;
    }

    @Override
    protected String getHeaderText() {
        return getString(R.string.basic_scene_select_elements);
    }

    @Override
    protected String[] getPendingSceneElements() {
        return null; //TODO-FIX BasicSceneV2InfoFragment.pendingSceneV2.sceneElementIDs;
    }

    @Override
    protected String getPendingItemID() {
        return BasicSceneV2InfoFragment.pendingSceneV2.id;
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        super.onCreateOptionsMenu(menu, inflater);

        ((SampleAppActivity)getActivity()).updateActionBar(R.string.title_basic_scene_add, false, false, false, true, true);
    }

    @Override
    public void onClick(View view) {
        if (view.getId() == R.id.selectHeader) {
            //TODO-FIX
        } else if (view.getId() == R.id.selectableItemButtonIcon) {
            ((SampleAppActivity)getActivity()).showSceneElementMorePopup(view, getPendingItemID(), view.getTag().toString(), true);
        } else {
            super.onClick(view);
        }
    }

    @Override
    protected void processSelection(SampleAppActivity activity, List<String> lampIDs, List<String> groupIDs, List<String> presetIDs, List<String> transitionEffectIDs, List<String> pulseEffectIDs, List<String> sceneElementIDs, List<String> sceneIDs) {
        LightingDirector director = LightingDirector.get();
        SceneElement[] sceneElements = director.getSceneElements(sceneElementIDs);

        if (!isAddMode()) {
            ((SceneV2)director.getScene(getPendingItemID())).modify(sceneElements);
        } else {
            director.createScene(sceneElements, BasicSceneV2InfoFragment.pendingSceneV2.name);
        }
    }

    @Override
    protected int getMixedSelectionMessageID() {
        return R.string.mixing_lamp_types_message_scene;
    }

    @Override
    protected int getMixedSelectionPositiveButtonID() {
        return R.string.create_scene;
    }

    //TODO-REF Common
    protected boolean isAddMode() {
        String pendingItemID = getPendingItemID();

        return pendingItemID == null || pendingItemID.isEmpty();
    }
}
