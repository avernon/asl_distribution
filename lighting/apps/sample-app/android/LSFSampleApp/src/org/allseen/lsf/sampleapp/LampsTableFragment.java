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

import org.allseen.lsf.sdk.Lamp;
import org.allseen.lsf.sdk.LightingDirector;

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

        // We don't user super.addItems() here because we need to call
        // ViewColor.calculate() for each lamp.
        addLamps(LightingDirector.get().getLamps());

        return root;
    }

    public void addLamps(Lamp[] lamps) {
        for (Lamp lamp : lamps) {
            addLamp(lamp);
        }
    }

    public void addLamp(Lamp lamp) {
        addItem(lamp, ViewColor.calculate(lamp.getState(), lamp.getCapability(), lamp.getDetails()));
    }

    @Override
    public void removeElement(String id) {
        super.removeElement(id);
        updateLoading();
    }

    @Override
    public void updateLoading() {
        super.updateLoading();

        SampleAppActivity activity = (SampleAppActivity) getActivity();
        boolean hasLamps = LightingDirector.get().getLampCount() > 0;

        if (activity.isControllerConnected() && !hasLamps) {
            // connected but no lamps found; display loading lamps screen, hide the scroll table
            layout.findViewById(R.id.scrollLoadingView).setVisibility(View.VISIBLE);
            layout.findViewById(R.id.scrollScrollView).setVisibility(View.GONE);

            View loadingView = layout.findViewById(R.id.scrollLoadingView);

            ((TextView) loadingView.findViewById(R.id.loadingText1)).setText(activity.getText(R.string.no_lamps));
            ((TextView) loadingView.findViewById(R.id.loadingText2)).setText(activity.getText(R.string.loading_lamps));
        }
    }
}
