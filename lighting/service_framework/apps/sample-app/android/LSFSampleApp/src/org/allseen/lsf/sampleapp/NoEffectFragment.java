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
package org.allseen.lsf.sampleapp;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class NoEffectFragment extends BasicSceneElementInfoFragment {
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = super.onCreateView(inflater, container, savedInstanceState);

        setImageButtonBackgroundResource(statusView, R.id.statusButtonPower, R.drawable.list_constant_icon);

        ((TextView)statusView.findViewById(R.id.statusLabelName)).setText(R.string.label_effect_name);

        updateInfoFields(((SampleAppActivity)getActivity()).pendingNoEffectModel);

        return view;
    }

    @Override
    public void updateInfoFields(DimmableItemDataModel itemModel) {
        SampleAppActivity activity = (SampleAppActivity)getActivity();

        // Capabilities can change if the member set is edited
        itemModel.setCapability(activity.pendingBasicSceneElementCapability);

        stateAdapter.setCapability(itemModel.getCapability());

        super.updateInfoFields(itemModel);

        updateNoEffectInfoFields(activity, (NoEffectDataModel)itemModel);
    }

    protected void updateNoEffectInfoFields(SampleAppActivity activity, NoEffectDataModel elementModel) {
        String members = MemberNamesString.format(activity, activity.pendingBasicSceneElementMembers, MemberNamesOptions.en, 3, R.string.effect_info_help_no_members);
        setTextViewValue(view.findViewById(R.id.infoHelpRow), R.id.helpText, String.format(getString(R.string.effect_info_help_none), members), 0);

        // Superclass updates the icon, so we have to re-override
        setImageButtonBackgroundResource(statusView, R.id.statusButtonPower, R.drawable.list_constant_icon);
    }

    @Override
    protected int getLayoutID() {
        return R.layout.fragment_effect_constant;
    }

    @Override
    protected BasicSceneElementDataModel getPendingSceneElementDataModel() {
        return ((SampleAppActivity)getActivity()).pendingNoEffectModel;
    }

    @Override
    public void updatePendingSceneElement() {
        SampleAppActivity activity = (SampleAppActivity)getActivity();
        activity.pendingBasicSceneModel.updateNoEffect(activity.pendingNoEffectModel);
    }
}
