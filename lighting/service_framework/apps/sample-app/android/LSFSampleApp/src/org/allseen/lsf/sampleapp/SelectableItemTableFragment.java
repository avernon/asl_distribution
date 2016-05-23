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

import java.util.ArrayList;
import java.util.List;

import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

public abstract class SelectableItemTableFragment extends ScrollableTableFragment implements OnClickListener, OnCheckedChangeListener {

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        view = inflater.inflate(R.layout.fragment_selectable_table, container, false);

        table = (TableLayout) view.findViewById(R.id.scrollableTable);
        layout = (LinearLayout) view.findViewById(R.id.scrollLayout);

        ((TextView)view.findViewById(R.id.selectHeader)).setText(getHeaderText());

        if (!isExclusive()) {
            view.findViewById(R.id.selectAll).setOnClickListener(this);
            view.findViewById(R.id.selectNone).setOnClickListener(this);
        } else {
            view.findViewById(R.id.selectAll).setVisibility(View.GONE);
            view.findViewById(R.id.selectNone).setVisibility(View.GONE);
        }

        return view;
    }

    protected <T> void updateSelectableItemRow(Context context, String itemID, Comparable<T> tag, int imageID, String name, boolean checked) {
        updateSelectableItemRow(
            context,
            (LayoutInflater)context.getSystemService(Context.LAYOUT_INFLATER_SERVICE),
            (TableLayout)getView().findViewById(R.id.scrollableTable),
            itemID,
            tag,
            imageID,
            name,
            checked);
    }

    protected <T> void updateSelectableItemRow(LayoutInflater inflater, View root, String itemID, Comparable<T> tag, int imageID, String name, boolean checked) {
        updateSelectableItemRow(
            root.getContext(),
            inflater,
            (TableLayout)root.findViewById(R.id.scrollableTable),
            itemID,
            tag,
            imageID,
            name,
            checked);
    }

    protected <T> void updateSelectableItemRow(Context context, LayoutInflater inflater, TableLayout table, String itemID, Comparable<T> tag, int imageID, String name, boolean checked) {
        TableRow tableRow = new TableRow(context);

        inflater.inflate(getTableRowLayout(), tableRow);

        tableRow.setTag(itemID);

        ImageButton imageButton = (ImageButton)tableRow.findViewById(R.id.selectableItemButtonIcon);
        imageButton.setTag(itemID);
        imageButton.setBackgroundResource(imageID);
        imageButton.setClickable(true);
        imageButton.setOnClickListener(this);

        ((TextView)tableRow.findViewById(R.id.selectableItemRowText)).setText(name);

        CompoundButton selectButton = getCompoundButton(tableRow);
        selectButton.setTag(itemID);
        selectButton.setClickable(true);
        selectButton.setOnClickListener(this);
        selectButton.setOnCheckedChangeListener(this);
        selectButton.setButtonDrawable(getSelectButtonDrawableID());
        selectButton.setChecked(checked);

        TableSorter.insertSortedTableRow(table, tableRow, tag);
    }

    protected int getTableRowLayout() {
        return R.layout.view_selectable_item_row;
    }

    protected int getSelectButtonDrawableID() {
        return isExclusive() ? R.drawable.radiobutton : R.drawable.checkbox;
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        updateTableRows();
    }

    protected void updateTableRows() {
        // On certain handsets (e.g., the HTC One M7), this routine can be called before
        // the table member variable is initialized on the onCreateView() method
        if (table != null) {
            int rowCount = table.getChildCount();

            for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
                TableRow tableRow = (TableRow)(table.getChildAt(rowIndex));

                getCompoundButton(tableRow).setChecked(isItemSelected(getItemID(tableRow)));
            }

            doValidation();
        }
    }

    protected boolean isExclusive() {
        // Default to false for checkbox behavior, override and return true for radio behavior
        return false;
    }

    protected CompoundButton getCompoundButton(TableRow tableRow) {
        return (CompoundButton)tableRow.findViewById(R.id.selectableItemRowTick);
    }

    protected String getItemID(TableRow tableRow) {
        return tableRow.getTag().toString();
    }

    protected abstract String getHeaderText();
    protected abstract boolean isItemSelected(String itemID);

    protected boolean isRowSelected(TableRow tableRow) {
        return getCompoundButton(tableRow).isChecked();
    }

    protected void setAll(boolean state) {
        int rowCount = table.getChildCount();

        for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
            TableRow tableRow = (TableRow) table.getChildAt(rowIndex);

            getCompoundButton(tableRow).setChecked(state);
        }
    }

    @Override
    public void onClick(View v) {
        if (!isExclusive()) {
            switch (v.getId()) {
                case R.id.selectAll:
                    setAll(true);
                    break;
                case R.id.selectNone:
                    setAll(false);
                    break;
                default:
                    break;
            }
        } else if (v.getId() == R.id.selectableItemRowTick) {
            // For exclusive behavior, prevent a click on the already selected
            // item from causing it to become unchecked.
            ((CompoundButton) v).setChecked(true);
        }
    }

    protected List<String> getSelectedIDs() {
        ArrayList<String> selectedIDs = new ArrayList<String>();
        int rowCount = table.getChildCount();

        for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
            TableRow tableRow = (TableRow)(table.getChildAt(rowIndex));

            if (isRowSelected(tableRow)) {
                selectedIDs.add(getItemID(tableRow));
            }
        }

        return selectedIDs;
    }

    @Override
    public void onCheckedChanged(CompoundButton selectButton, boolean checked) {
        if (isExclusive() && checked) {
            int rowCount = table.getChildCount();

            for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
                TableRow tableRow = (TableRow)(table.getChildAt(rowIndex));

                if (!getItemID(tableRow).equals(selectButton.getTag().toString())) {
                    getCompoundButton(tableRow).setChecked(false);
                }
            }
        }

        doValidation();
    }

    protected void doValidation() {
        boolean valid = false;
        int rowCount = table.getChildCount();

        for (int rowIndex = 0; !valid && rowIndex < rowCount; rowIndex++) {
            TableRow tableRow = (TableRow)(table.getChildAt(rowIndex));

            if (isRowSelected(tableRow)) {
                valid = true;
            }
        }

        SampleAppActivity activity = (SampleAppActivity)getActivity();

        activity.setActionBarNextEnabled(valid);
        activity.setActionBarDoneEnabled(valid);
    }
}
