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
import android.text.InputType;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class EnterCountFragment extends EnterNumberFragment {
    public static long count;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = super.onCreateView(inflater, container, savedInstanceState);
        ((TextView) view.findViewById(R.id.enterNumberUnits)).setText(getString(R.string.units_pulses));
        return view;
    }

    @Override
    protected int getTitleID() {
        return R.string.title_effect_pulse_count;
    }

    @Override
    protected int getLabelID() {
        return R.string.label_enter_count;
    }

    @Override
    protected int getInputType() {
        return InputType.TYPE_CLASS_NUMBER | InputType.TYPE_NUMBER_FLAG_DECIMAL;
    }

    @Override
    protected String getNumberString() {
        return String.valueOf(EnterCountFragment.count);
    }

    @Override
    protected double getScale() {
        return 1.0;
    }

    @Override
    protected boolean setNumberValue(long numberValue) {
        EnterCountFragment.count = numberValue;

        if (PulseEffectV2Fragment.pendingPulseEffect != null) {
            PulseEffectV2Fragment.pendingPulseEffect.count = numberValue;
        }

        // Go back to the effect info display
        getActivity().onBackPressed();

        return true;
    }
}

