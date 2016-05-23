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

import org.allseen.lsf.LampGroup;
import org.allseen.lsf.sampleapp.PageFrameChildFragment;
import org.allseen.lsf.sampleapp.R;
import org.allseen.lsf.sampleapp.SampleAppActivity;
import org.allseen.lsf.sdk.LampCapabilities;
import org.allseen.lsf.sdk.LightingDirector;
import org.allseen.lsf.sdk.Scene;
import org.allseen.lsf.sdk.SceneV1;
import org.allseen.lsf.sdk.model.NoEffectDataModel;
import org.allseen.lsf.sdk.model.PulseEffectDataModel;
import org.allseen.lsf.sdk.model.SceneDataModel;
import org.allseen.lsf.sdk.model.TransitionEffectDataModel;

import android.content.Context;

public class BasicSceneV1Module {
    public void init(Context context) {
        NoEffectDataModel.defaultName = context.getString(R.string.effect_name_none);
        TransitionEffectDataModel.defaultName = context.getString(R.string.effect_name_transition);
        PulseEffectDataModel.defaultName = context.getString(R.string.effect_name_pulse);
        SceneDataModel.defaultName = context.getString(R.string.default_basic_scene_name);
    }

    public void doDeleteSceneElement(String elementID ) {
        if (BasicSceneV1InfoFragment.pendingBasicSceneModel != null) {
            BasicSceneV1InfoFragment.pendingBasicSceneModel.removeElement(elementID);
        }
    }

    public void resetPendingScene(String sceneID) {
        Scene scene = sceneID != null ? LightingDirector.get().getScene(sceneID) : null;

        if (scene != null && scene instanceof SceneV1) {
            BasicSceneV1InfoFragment.pendingBasicSceneModel = BasicSceneV1Util.createSceneDataModelFrom((SceneV1)scene);
        } else {
            BasicSceneV1InfoFragment.pendingBasicSceneModel = new SceneDataModel();
        }

        EffectV1InfoFragment.pendingBasicSceneElementMembers = new LampGroup();
        EffectV1InfoFragment.pendingBasicSceneElementCapability = new LampCapabilities(true, true, true);
    }

    public void resetPendingEffects() {
        NoEffectFragment.pendingNoEffect = null;
        TransitionEffectV1Fragment.pendingTransitionEffect = null;
        PulseEffectV1Fragment.pendingPulseEffect = null;
    }

    public String createMemberNamesString(SampleAppActivity activity, Scene basicScene, String separator) {
        return BasicSceneV1Util.createMemberNamesString(activity, basicScene, separator);
    }

    public boolean isNoEffectPending() {
        return NoEffectFragment.pendingNoEffect != null;
    }

    public boolean isTransitionEffectPending() {
        return TransitionEffectV1Fragment.pendingTransitionEffect != null;
    }

    public boolean isPulseEffectPending() {
        return PulseEffectV1Fragment.pendingPulseEffect != null;
    }

    public String getPendingNoEffectID() {
        return NoEffectFragment.pendingNoEffect.id;
    }

    public String getPendingTransitionEffectID() {
        return TransitionEffectV1Fragment.pendingTransitionEffect.id;
    }

    public String getPendingPulseEffectID() {
        return PulseEffectV1Fragment.pendingPulseEffect.id;
    }

    public PageFrameChildFragment createBasicSceneInfoFragment() {
        return new BasicSceneV1InfoFragment();
    }

    public PageFrameChildFragment createSceneElementPresetsFragment() {
        return new SceneElementV1PresetsFragment();
    }

    public PageFrameChildFragment createBasicSceneEnterNameFragment() {
        return new BasicSceneV1EnterNameFragment();
    }

    public PageFrameChildFragment createBasicSceneSelectMembersFragment() {
        return new BasicSceneV1SelectMembersFragment();
    }

    public PageFrameChildFragment createBasicSceneSelectEffectTypeFragment() {
        return new BasicSceneV1SelectEffectTypeFragment();
    }

    public PageFrameChildFragment createNoEffectFragment() {
        return new NoEffectFragment();
    }

    public PageFrameChildFragment createTransitionEffectFragment() {
        return new TransitionEffectV1Fragment();
    }

    public PageFrameChildFragment createPulseEffectFragment() {
        return new PulseEffectV1Fragment();
    }
}
