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

import android.content.Context;
import android.graphics.Color;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ImageButton;
import android.widget.SeekBar;
import android.widget.TableRow;
import android.widget.TextView;
import android.widget.Toast;

public abstract class DimmableItemTableFragment
    extends ScrollableTableFragment
    implements
        View.OnClickListener,
        SeekBar.OnSeekBarChangeListener {

    protected abstract int getInfoButtonImageID();
    protected abstract Fragment getInfoFragment();

    public <T> TableRow insertDimmableItemRow(Context context, String itemID, Comparable<T> tag, boolean powerOn, boolean uniformPower, String name, long modelBrightness, boolean uniformBrightness, int infoBG) {
        return insertDimmableItemRow(
            context,
            (LayoutInflater)context.getSystemService(Context.LAYOUT_INFLATER_SERVICE),
            itemID,
            tag,
            powerOn,
            uniformPower,
            name,
            modelBrightness,
            uniformBrightness,
            infoBG,
            true);
    }

    public <T> TableRow insertDimmableItemRow(Context context, String itemID, Comparable<T> tag, boolean powerOn, boolean uniformPower, String name, long modelBrightness, boolean uniformBrightness, int infoBG, boolean enabled) {
        return insertDimmableItemRow(
            context,
            (LayoutInflater)context.getSystemService(Context.LAYOUT_INFLATER_SERVICE),
            itemID,
            tag,
            powerOn,
            uniformPower,
            name,
            modelBrightness,
            uniformBrightness,
            infoBG,
            enabled);
    }

    public <T> TableRow insertDimmableItemRow(Context context, LayoutInflater inflater, String itemID, Comparable<T> tag, boolean powerOn, boolean uniformPower, String name, long modelBrightness, boolean uniformBrightness, int infoBG, boolean enabled) {
        Log.d(SampleAppActivity.TAG, "insertDimmableItemRow(): " + itemID + ", " + tag + ", " + name);

        final boolean isEnabled = enabled;

        TableRow tableRow = (TableRow)table.findViewWithTag(itemID);

        if (tableRow == null) {
            tableRow = new TableRow(context);

            inflater.inflate(R.layout.view_dimmable_item_row, tableRow);

            ImageButton powerButton = (ImageButton)tableRow.findViewById(R.id.dimmableItemButtonPower);
            powerButton.setTag(itemID);
            powerButton.setBackgroundResource(uniformPower ? (powerOn ? R.drawable.power_button_on : R.drawable.power_button_off) : R.drawable.power_button_mix);
            powerButton.setOnClickListener(this);

            ((TextView)tableRow.findViewById(R.id.dimmableItemRowText)).setText(name);

            SeekBar seekBar = (SeekBar)tableRow.findViewById(R.id.dimmableItemRowSlider);
            seekBar.setProgress(DimmableItemScaleConverter.convertBrightnessModelToView(modelBrightness));
            seekBar.setTag(itemID);
            seekBar.setSaveEnabled(false);
            seekBar.setOnSeekBarChangeListener(this);
            seekBar.setThumb(getResources().getDrawable(uniformBrightness ? R.drawable.slider_thumb_normal : R.drawable.slider_thumb_midstate));
            seekBar.setEnabled(isEnabled);

            ImageButton infoButton = (ImageButton)tableRow.findViewById(R.id.dimmableItemButtonMore);
            infoButton.setImageResource(getInfoButtonImageID());
            infoButton.setTag(itemID);
            infoButton.setOnClickListener(this);
            if (infoBG != 0) {
                infoButton.setBackgroundColor(infoBG);
            }

            tableRow.setTag(itemID);
            TableSorter.insertSortedTableRow(table, tableRow, tag);
        } else {
            ((ImageButton)tableRow.findViewById(R.id.dimmableItemButtonPower)).setBackgroundResource(uniformPower ? (powerOn ? R.drawable.power_button_on : R.drawable.power_button_off) : R.drawable.power_button_mix);
            ((TextView)tableRow.findViewById(R.id.dimmableItemRowText)).setText(name);

            SeekBar seekBar = (SeekBar)tableRow.findViewById(R.id.dimmableItemRowSlider);
            seekBar.setProgress(DimmableItemScaleConverter.convertBrightnessModelToView(modelBrightness));
            seekBar.setThumb(getResources().getDrawable(uniformBrightness ? R.drawable.slider_thumb_normal : R.drawable.slider_thumb_midstate));
            seekBar.setEnabled(isEnabled);

            if (infoBG != 0) {
                ((ImageButton)tableRow.findViewById(R.id.dimmableItemButtonMore)).setBackgroundColor(infoBG);
            }

            TableSorter.updateSortedTableRow(table, tableRow, tag);
        }

        tableRow.setClickable(true);
        tableRow.setOnClickListener(this);
        ((SampleAppActivity)getActivity()).setTabTitles();
        return tableRow;
    }

    @Override
    public void onClick(View button) {
        Log.d(SampleAppActivity.TAG, "onClick()");

        int buttonID = button.getId();

        if (parent != null) {
            if (buttonID == R.id.dimmableItemButtonPower) {
                ((SampleAppActivity)getActivity()).togglePower(type, button.getTag().toString());
            } else if (buttonID == R.id.dimmableItemButtonMore) {
                ((SampleAppActivity)getActivity()).onItemButtonMore(parent, type, button, button.getTag().toString(), null);
            } else if (!((SeekBar)button.findViewById(R.id.dimmableItemRowSlider)).isEnabled()) {
            	((SampleAppActivity)getActivity()).showToast(R.string.no_support_dimmable);
            }
        }
    }

    @Override
    public void onProgressChanged(SeekBar seekBar, int brightness, boolean fromUser) {
        //AJSI-291: UI Slider behaviour change (from continuous updating to updating when finger is lifted)
        /*if (parent != null && fromUser) {
            ((SampleAppActivity)getActivity()).setBrightness(type, seekBar.getTag().toString(), seekBar.getProgress());
        }*/
    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {
        // Currently nothing to do
    }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {
        if (parent != null) {
            ((SampleAppActivity)getActivity()).setBrightness(type, seekBar.getTag().toString(), seekBar.getProgress());
        }
    }

    public abstract void addElement(String id);
}
