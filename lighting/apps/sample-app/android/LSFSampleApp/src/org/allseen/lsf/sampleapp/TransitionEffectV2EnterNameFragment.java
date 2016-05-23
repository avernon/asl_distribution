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

import org.allseen.lsf.sdk.LightingDirector;
import android.util.Log;

public class TransitionEffectV2EnterNameFragment extends EnterNameFragment {

    public TransitionEffectV2EnterNameFragment() {
        super(R.string.label_transition_effect);
    }

    @Override
    protected int getTitleID() {
        return R.string.title_effect_transition_add;
    }

    @Override
    protected void setName(String name) {
        TransitionEffectV2Fragment.pendingTransitionEffect.name = name;

        Log.d(SampleAppActivity.TAG, "Pending transition effect name: " + TransitionEffectV2Fragment.pendingTransitionEffect.name);
    }

    @Override
    protected void showNextFragment() {
        ((ScenesPageFragment)parent).showTransitionEffectChildFragment();
    }

    @Override
    protected String getDuplicateNameMessage() {
        return this.getString(R.string.duplicate_name_message_transition_effect);
    }

    @Override
    protected boolean duplicateName(String transitionEffectName) {
        return Util.isDuplicateName(LightingDirector.get().getTransitionEffects(), transitionEffectName);
    }
}
