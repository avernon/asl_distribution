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

import java.util.Locale;

import android.text.InputType;

public class EnterDurationFragment extends EnterNumberFragment {

    @Override
    protected int getTitleID() {
        SampleAppActivity activity = (SampleAppActivity)getActivity();

        return activity.pendingTransitionEffectModel != null ? R.string.title_effect_transition_duration : R.string.title_effect_pulse_duration;
    }

    @Override
    protected int getLabelID() {
        return R.string.label_enter_duration;
    }

    @Override
    protected int getInputType() {
        return InputType.TYPE_CLASS_NUMBER | InputType.TYPE_NUMBER_FLAG_DECIMAL;
    }

    @Override
    protected String getNumberString() {
        SampleAppActivity activity = (SampleAppActivity)getActivity();
        long duration = activity.pendingTransitionEffectModel != null ? activity.pendingTransitionEffectModel.duration : activity.pendingPulseEffectModel.duration;

        return String.format(Locale.ENGLISH, getString(R.string.effect_info_duration_format), duration / 1000.0);
    }

    @Override
    protected boolean setNumberValue(long numberValue) {
        SampleAppActivity activity = (SampleAppActivity)getActivity();

        if (activity.pendingTransitionEffectModel != null) {
            activity.pendingTransitionEffectModel.duration = numberValue;
        } else {
            activity.pendingPulseEffectModel.duration = numberValue;
        }

        // Go back to the effect info display
        activity.onBackPressed();

        return true;
    }
}

