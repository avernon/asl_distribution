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
package org.allseen.lsf.sampleapp.scenesv1;

import org.allseen.lsf.LampGroup;
import org.allseen.lsf.sampleapp.EnterNameFragment;
import org.allseen.lsf.sampleapp.R;
import org.allseen.lsf.sampleapp.SampleAppActivity;
import org.allseen.lsf.sampleapp.Util;
import org.allseen.lsf.sdk.LampCapabilities;
import org.allseen.lsf.sdk.LightingDirector;
import org.allseen.lsf.sdk.model.SceneDataModel;

import android.util.Log;

public class BasicSceneV1EnterNameFragment extends EnterNameFragment {

    public BasicSceneV1EnterNameFragment() {
        super(R.string.label_basic_scene);
    }

    @Override
    protected int getTitleID() {
        return R.string.title_basic_scene_add;
    }

    @Override
    protected void setName(String name) {
        SceneDataModel sceneModel = new SceneDataModel();

        sceneModel.setName(name);

        BasicSceneV1InfoFragment.pendingBasicSceneModel = sceneModel;
        EffectV1InfoFragment.pendingBasicSceneElementMembers = new LampGroup();
        EffectV1InfoFragment.pendingBasicSceneElementCapability = new LampCapabilities(true, true, true);

        Log.d(SampleAppActivity.TAG, "Pending basic scene name: " + BasicSceneV1InfoFragment.pendingBasicSceneModel.getName());
    }

    @Override
    protected String getDuplicateNameMessage() {
        return this.getString(R.string.duplicate_name_message_scene);
    }

    @Override
    protected boolean duplicateName(String basicSceneName) {
        return Util.isDuplicateName(LightingDirector.get().getScenes(), basicSceneName);
    }
}
