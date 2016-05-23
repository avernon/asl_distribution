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

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;

public abstract class EnterNameFragment extends PageFrameChildFragment {
    protected int labelStringID;

    protected ItemNameFragmentTextWatcher nameWatcher;

    public EnterNameFragment(int labelStringID) {
        this.labelStringID = labelStringID;
    }

    protected abstract int getTitleID();

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        view = inflater.inflate(R.layout.fragment_enter_name, container, false);

        EditText nameText = (EditText)view.findViewById(R.id.enterNameText);
        nameWatcher = new ItemNameFragmentTextWatcher((SampleAppActivity)getActivity(), nameText);
        nameText.addTextChangedListener(nameWatcher);

        updateEnterNameFields();

        return view;
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        ((SampleAppActivity)getActivity()).updateActionBar(getTitleID(), false, false, true, false, true);

        if (nameWatcher != null) {
            nameWatcher.doValidation();
        }
    }

    public void updateEnterNameFields() {
        String text = String.format(getResources().getString(R.string.label_enter_name), getResources().getString(labelStringID));

        setTextViewValue(view, R.id.enterNameLabel, text, 0);

        nameWatcher.doValidation();
    }

    @Override
    public void onActionNext() {
        final String name = ((EditText)view.findViewById(R.id.enterNameText)).getText().toString().trim();

        if ((name != null) && (!name.isEmpty())) {
            if (parent != null) {
                // check for duplicate names
                if (duplicateName(name)) {
                    // create an alert
                    AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
                    builder.setTitle(R.string.duplicate_name);
                    builder.setMessage(String.format(getDuplicateNameMessage(), name));
                    builder.setPositiveButton(R.string.dialog_ok, new OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            setName(name);
                            showNextFragment();
                        }
                    });
                    builder.setNegativeButton(R.string.dialog_cancel, new OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            dialog.cancel();
                        }
                    });

                    builder.create().show();

                } else {
                    // we can go ahead and use this name
                    setName(name);
                    showNextFragment();
                }
            }
        } else {
            String text = String.format(getResources().getString(R.string.toast_name_missing), getResources().getString(labelStringID));
            ((SampleAppActivity)getActivity()).showToast(text);
        }
    }

    protected void showNextFragment() {
        ((PageMainContainerFragment)parent).showSelectMembersChildFragment();
    }

    protected abstract void setName(String name);
    protected abstract String getDuplicateNameMessage();
    protected abstract boolean duplicateName(String name);
}

