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
import org.allseen.lsf.sampleapp.EffectInfoFragment;
import org.allseen.lsf.sampleapp.PageFrameParentFragment;
import org.allseen.lsf.sampleapp.R;
import org.allseen.lsf.sdk.ColorAverager;
import org.allseen.lsf.sdk.LampCapabilities;
import org.allseen.lsf.sdk.model.ColorStateConverter;

public abstract class EffectV1InfoFragment extends EffectInfoFragment {
    public static LampGroup pendingBasicSceneElementMembers;
    public static LampCapabilities pendingBasicSceneElementCapability;
    public static ColorAverager pendingBasicSceneElementColorTempAverager = new ColorAverager();
    public static boolean pendingBasicSceneElementMembersHaveEffects;
    public static int pendingBasicSceneElementMembersMinColorTemp;
    public static int pendingBasicSceneElementMembersMaxColorTemp;

    @Override
    public int getTitleID() {
        return R.string.title_basic_scene_element_add;
    }

    @Override
    protected String getLampStateViewAdapterTag() {
        return STATE_ITEM_TAG;
    }

    @Override
    protected LampCapabilities getPendingMembersCapability() {
        return pendingBasicSceneElementCapability;
    }

    @Override
    public void onActionDone() {
        updatePendingSceneElement();

        pendingBasicSceneElementMembers = null;
        pendingBasicSceneElementCapability = null;

        NoEffectFragment.pendingNoEffect = null;
        TransitionEffectV1Fragment.pendingTransitionEffect = null;
        PulseEffectV1Fragment.pendingPulseEffect = null;

        parent.popBackStack(PageFrameParentFragment.CHILD_TAG_INFO);
    }

    @Override
    protected int getColorTempMin() {
        return pendingBasicSceneElementMembersMinColorTemp;
    }

    @Override
    protected int getColorTempSpan() {
        return pendingBasicSceneElementMembersMaxColorTemp - pendingBasicSceneElementMembersMinColorTemp;
    }

    @Override
    protected int getColorTempDefault() {
        return ColorStateConverter.convertColorTempModelToView(pendingBasicSceneElementColorTempAverager.getAverage());
    }

    protected abstract void updatePendingSceneElement();
}
