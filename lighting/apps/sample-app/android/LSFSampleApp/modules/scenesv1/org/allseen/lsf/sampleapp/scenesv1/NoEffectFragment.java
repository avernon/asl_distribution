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

import org.allseen.lsf.sampleapp.MemberNamesOptions;
import org.allseen.lsf.sampleapp.R;
import org.allseen.lsf.sampleapp.SampleAppActivity;
import org.allseen.lsf.sdk.LampCapabilities;
import org.allseen.lsf.sdk.LampStateUniformity;
import org.allseen.lsf.sdk.MyLampState;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class NoEffectFragment extends EffectV1InfoFragment {
    public static PendingNoEffect pendingNoEffect;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = super.onCreateView(inflater, container, savedInstanceState);

        setImageButtonBackgroundResource(statusView, R.id.statusButtonPower, R.drawable.list_constant_icon);

        ((TextView)statusView.findViewById(R.id.statusLabelName)).setText(R.string.label_effect_name);

        initLampState();

        updateInfoFields(pendingNoEffect.name, pendingNoEffect.state, EffectV1InfoFragment.pendingBasicSceneElementCapability, pendingNoEffect.uniformity);

        return view;
    }

    @Override
    protected void updateInfoFields(String name, MyLampState state, LampCapabilities capability, LampStateUniformity uniformity) {
        // Capabilities can change if the member set is edited
        stateAdapter.setCapability(capability);

        super.updateInfoFields(name, state, capability, uniformity);

        updateNoEffectInfoFields();
    }

    protected void updateNoEffectInfoFields() {
        SampleAppActivity activity = (SampleAppActivity)getActivity();
        String members = BasicSceneV1Util.formatMemberNamesString(activity, EffectV1InfoFragment.pendingBasicSceneElementMembers, MemberNamesOptions.en, 3, R.string.effect_info_help_no_members);

        setTextViewValue(view.findViewById(R.id.infoHelpRow), R.id.helpText, String.format(getString(R.string.effect_info_help_none), members), 0);

        // Superclass updates the icon, so we have to re-override
        setImageButtonBackgroundResource(statusView, R.id.statusButtonPower, R.drawable.list_constant_icon);
    }

    @Override
    protected int getLayoutID() {
        return R.layout.fragment_effect_constant;
    }

    @Override
    protected MyLampState getPendingLampState(int index) {
        logErrorOnInvalidIndex(index);

        return pendingNoEffect.state;
    }

    @Override
    protected String getPendingPresetID(int index) {
        logErrorOnInvalidIndex(index);

        return pendingNoEffect.presetID;
    }

    @Override
    protected void setPendingPresetID(int index, String presetID) {
        logErrorOnInvalidIndex(index);

        pendingNoEffect.presetID = presetID;
    }

    @Override
    public void updatePendingSceneElement() {
        pendingNoEffect.updateDataModel(pendingBasicSceneElementMembers, pendingBasicSceneElementCapability);

        BasicSceneV1InfoFragment.pendingBasicSceneModel.updateNoEffect(pendingNoEffect.dataModel);
    }
}
