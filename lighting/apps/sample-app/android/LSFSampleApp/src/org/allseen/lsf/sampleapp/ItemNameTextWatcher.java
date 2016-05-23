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

import android.text.Editable;
import android.text.TextWatcher;
import android.widget.EditText;

public abstract class ItemNameTextWatcher implements TextWatcher {

    protected EditText nameText;

    public ItemNameTextWatcher(EditText nameText) {
        super();

        this.nameText = nameText;
    }

    @Override
    public void afterTextChanged(Editable s) {
        doValidation();
    }

    @Override
    public void beforeTextChanged(CharSequence s, int start, int count, int after) {
        // Currently nothing to do
    }

    @Override
    public void onTextChanged(CharSequence s, int start, int before, int count) {
        // Currently nothing to do
    }

    public void doValidation() {
        Editable newName = nameText.getText();

        onTextValidation(newName != null && newName.length() > 0 && newName.charAt(0) != ' ');
    }

    protected abstract void onTextValidation(boolean isValid);
}
