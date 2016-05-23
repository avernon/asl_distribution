/*
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;
import android.widget.ImageButton;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

public abstract class SceneItemInfoFragment extends PageFrameChildFragment implements View.OnClickListener {

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        ((SampleAppActivity) getActivity()).updateActionBar(R.string.title_basic_scene_info, false, true, false, true, true);
    }

    protected void addElementRow(SampleAppActivity activity, TableLayout elementTable, int iconID, String elementID, String memberNames, int detailsID) {
        addElementRow(activity, elementTable, iconID, elementID, memberNames, getString(detailsID));
    }

    protected void addElementRow(SampleAppActivity activity, TableLayout elementTable, int iconID, String elementID, String memberNames, String details) {
        TableRow tableRow = new TableRow(view.getContext());
        activity.getLayoutInflater().inflate(R.layout.view_scene_element_row, tableRow);

        ((ImageButton)tableRow.findViewById(R.id.detailedItemButtonIcon)).setImageResource(iconID);

        TextView textHeader = (TextView)tableRow.findViewById(R.id.detailedItemRowTextHeader);
        textHeader.setText(memberNames);
        textHeader.setTag(elementID);
        textHeader.setClickable(true);
        textHeader.setOnClickListener(this);

        TextView textDetails = (TextView)tableRow.findViewById(R.id.detailedItemRowTextDetails);
        textDetails.setText(details);
        textDetails.setTag(elementID);
        textDetails.setClickable(true);
        textDetails.setOnClickListener(this);

        ImageButton moreButton = (ImageButton)tableRow.findViewById(R.id.detailedItemButtonMore);
        moreButton.setImageResource(R.drawable.group_more_menu_icon);
        moreButton.setTag(elementID);
        moreButton.setOnClickListener(this);

        elementTable.addView(tableRow);
    }

    public abstract void updateInfoFields();
}
