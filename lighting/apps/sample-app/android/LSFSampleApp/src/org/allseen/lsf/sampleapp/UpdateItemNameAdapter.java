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

import org.allseen.lsf.sdk.LightingItem;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.util.Log;
import android.widget.EditText;

public abstract class UpdateItemNameAdapter implements ItemNameAdapter {
    protected LightingItem item;
    protected SampleAppActivity activity;

    public UpdateItemNameAdapter(LightingItem item, SampleAppActivity activity) {
        this.item = item;
        this.activity = activity;
    }

    @Override
    public String getCurrentName() {
        return item != null ? item.getName() : "";
    }

    @Override
    public void onClick(DialogInterface dialog, int id) {
        EditText nameText = (EditText)(((AlertDialog)dialog).findViewById(R.id.itemNameText));
        final String itemName = nameText.getText().toString();

        Log.d(SampleAppActivity.TAG, "Item ID: " + item.getId() + " New name: " + itemName);

        if (itemName != null && !itemName.isEmpty()) {

            // check for duplicate names
            if (duplicateName(itemName)) {
                // create an alert

                AlertDialog.Builder builder = new AlertDialog.Builder(activity);
                builder.setTitle(R.string.duplicate_name);
                builder.setMessage(String.format(getDuplicateNameMessage(), itemName));
                builder.setPositiveButton(R.string.dialog_ok, new OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        doUpdateName(itemName);
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
                doUpdateName(itemName);
            }
        }
    }

    protected void doUpdateName(String itemName) {
        item.rename(itemName);
    }

    protected abstract String getDuplicateNameMessage();
    protected abstract boolean duplicateName(String itemName);
}
