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

import org.allseen.lsf.LampParameters;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class LampInfoFragment extends DimmableItemInfoFragment {

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = super.onCreateView(inflater, container, savedInstanceState);
        String lampID = key;

        itemType = SampleAppActivity.Type.LAMP;
        itemModels = ((SampleAppActivity)getActivity()).lampModels;

        ((TextView)statusView.findViewById(R.id.statusLabelName)).setText(R.string.label_lamp_name);

        // details
        view.findViewById(R.id.lampInfoTableRow5).setOnClickListener(this);

        updateInfoFields(((SampleAppActivity)getActivity()).lampModels.get(lampID));

        return view;
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        ((SampleAppActivity)getActivity()).updateActionBar(R.string.title_lamp_info, false, false, false, false, true);
    }

    @Override
    public void onClick(View view) {
        int viewID = view.getId();

        if (viewID == R.id.lampInfoTableRow5) {
            ((SampleAppActivity)getActivity()).showLampDetailsFragment((LampsPageFragment)parent, key);
        } else {
            super.onClick(view);
        }
    }

    public void updateInfoFields(LampDataModel lampModel) {
        if (lampModel.id.equals(key)) {
            stateAdapter.setCapability(lampModel.getCapability());
            super.updateInfoFields(lampModel);

            LampParameters lampParams = lampModel.getParameters() != null ? lampModel.getParameters() : EmptyLampParamaters.instance;
            setTextViewValue(view, R.id.lampInfoTextLumens, lampParams.getLumens(), 0);
            setTextViewValue(view, R.id.lampInfoTextEnergy, lampParams.getEnergyUsageMilliwatts(), R.string.units_mw);
        }
    }

    @Override
    protected int getLayoutID() {
        return R.layout.fragment_lamp_info;
    }

    @Override
    protected void onHeaderClick() {
        SampleAppActivity activity = (SampleAppActivity)getActivity();
        LampDataModel lampModel = activity.lampModels.get(key);

        activity.showItemNameDialog(R.string.title_lamp_rename, new UpdateLampNameAdapter(lampModel, (SampleAppActivity) getActivity()));
    }
}
