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

import org.allseen.lsf.LampState;

import android.graphics.Color;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class LampsTableFragment extends DimmableItemTableFragment {

    public LampsTableFragment() {
        super();
        type = SampleAppActivity.Type.LAMP;
    }

    @Override
    protected int getInfoButtonImageID() {
        return R.drawable.light_status_icon;
    }

    @Override
    protected Fragment getInfoFragment() {
        return new LampInfoFragment();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View root = super.onCreateView(inflater, container, savedInstanceState);

        for (String id : ((SampleAppActivity) getActivity()).lampModels.keySet()) {
            addElement(id);
        }

        return root;
    }

    @Override
    public void removeElement(String id) {
        super.removeElement(id);
        updateLoading();
    }

    @Override
    public void addElement(String id) {
        LampDataModel lampModel = ((SampleAppActivity) getActivity()).lampModels.get(id);
        if (lampModel != null) {
            insertDimmableItemRow(getActivity(), lampModel.id, lampModel.tag, lampModel.state.getOnOff(), lampModel.uniformity.power, lampModel.getName(),
                    lampModel.state.getBrightness(), true, getColor(lampModel.state), lampModel.capability.dimmable >= CapabilityData.SOME);
            updateLoading();
        }
    }

    @Override
    public void updateLoading() {
        super.updateLoading();

        boolean hasLamps = ((SampleAppActivity) getActivity()).lampModels.size() > 0;

        if (AllJoynManager.controllerConnected && !hasLamps) {
            // connected but no lamps found; display loading lamps screen, hide the scroll table
            layout.findViewById(R.id.scrollLoadingView).setVisibility(View.VISIBLE);
            layout.findViewById(R.id.scrollScrollView).setVisibility(View.GONE);

            View loadingView = layout.findViewById(R.id.scrollLoadingView);

            ((TextView) loadingView.findViewById(R.id.loadingText1)).setText(getActivity().getText(R.string.no_lamps));
            ((TextView) loadingView.findViewById(R.id.loadingText2)).setText(getActivity().getText(R.string.loading_lamps));

        }
    }

    protected int getColor(LampState lampState) {
        int viewHue = DimmableItemScaleConverter.convertHueModelToView(lampState.getHue());
        int viewSaturation = DimmableItemScaleConverter.convertSaturationModelToView(lampState.getSaturation());
        int viewBrightness = DimmableItemScaleConverter.convertBrightnessModelToView(lampState.getBrightness());
        int viewColorTemp = DimmableItemScaleConverter.convertColorTempModelToView(lampState.getColorTemp());
        
        return DimmableItemScaleConverter.ColorTempToColorConverter.convert(viewColorTemp,
        		new float[] { viewHue,
                (float) (viewSaturation / 100.0),
                (float) (viewBrightness / 100.0) });
    }
}
