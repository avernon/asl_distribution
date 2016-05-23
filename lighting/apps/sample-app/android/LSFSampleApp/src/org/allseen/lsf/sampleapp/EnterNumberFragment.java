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
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;

public abstract class EnterNumberFragment extends PageFrameChildFragment {
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        view = inflater.inflate(R.layout.fragment_enter_number, container, false);

        setTextViewValue(view, R.id.enterNumberLabel, getString(getLabelID()), 0);

        ((EditText)view.findViewById(R.id.enterNumberText)).setInputType(getInputType());

        updateNumberField();

        return view;
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        ((SampleAppActivity)getActivity()).updateActionBar(getTitleID(), false, false, false, true, true);
    }

    @Override
    public void onActionDone() {
        final String stringValue = ((EditText)view.findViewById(R.id.enterNumberText)).getText().toString();

        if ((stringValue != null) && (!stringValue.isEmpty())) {
            try {
                long longValue = Math.round(Double.valueOf(stringValue) * getScale());
                long maxValue = (long)Integer.MAX_VALUE - Integer.MIN_VALUE;

                if (longValue >= 0 && longValue <= maxValue) {
                    setNumberValue(longValue);
                } else {
                	((SampleAppActivity)getActivity()).showToast(String.format(getString(R.string.toast_number_value_invalid), maxValue / getScale()));
                }
            } catch (NumberFormatException e) {
                ((SampleAppActivity)getActivity()).showToast(R.string.toast_number_format_invalid);
            }
        } else {
        	((SampleAppActivity)getActivity()).showToast(String.format(getString(R.string.toast_number_missing), getString(getLabelID())));
        }
    }

    protected double getScale() {
        return 1000.0;
    }

    public void updateNumberField() {
        String number = getNumberString();

        ((EditText)view.findViewById(R.id.enterNumberText)).setText(number);
    }

    protected abstract int getTitleID();
    protected abstract int getLabelID();
    protected abstract int getInputType();

    protected abstract String getNumberString();
    protected abstract boolean setNumberValue(long longValue);
}

