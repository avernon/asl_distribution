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

import java.util.Map;

import org.allseen.lsf.LampState;

import android.graphics.Color;
import android.graphics.PorterDuff.Mode;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.SeekBar;
import android.widget.TextView;

public abstract class DimmableItemInfoFragment extends PageFrameChildFragment implements View.OnClickListener {
    public static final String STATE_ITEM_TAG = "STATE";
    public static int defaultIndicatorColor = 00000000;

    protected SampleAppActivity.Type itemType = SampleAppActivity.Type.LAMP;
    protected Map<String, ? extends DimmableItemDataModel> itemModels;
    protected LampStateViewAdapter stateAdapter;

    protected View statusView;
    protected View stateView;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        String itemID = key;

        view = inflater.inflate(getLayoutID(), container, false);
        statusView = view.findViewById(R.id.infoStatusRow);
        stateView = view.findViewById(R.id.infoStateRow);

        // power button
        ImageButton powerButton = (ImageButton)statusView.findViewById(R.id.statusButtonPower);
        powerButton.setTag(itemID);
        powerButton.setOnClickListener(this);

        // item name
        TextView nameLabel = (TextView)statusView.findViewById(R.id.statusLabelName);
        nameLabel.setClickable(true);
        nameLabel.setOnClickListener(this);

        TextView nameText = (TextView)statusView.findViewById(R.id.statusTextName);
        nameText.setClickable(true);
        nameText.setOnClickListener(this);

        // presets button
        Button presetsButton = (Button)stateView.findViewById(R.id.stateButton);
        presetsButton.setTag(STATE_ITEM_TAG);
        presetsButton.setClickable(true);
        presetsButton.setOnClickListener(this);

        // state adapter
        stateAdapter = new LampStateViewAdapter(stateView, itemID, this);

        return view;
    }

    @Override
    public void onClick(View view) {
        int viewID = view.getId();

        if (viewID == R.id.statusButtonPower) {
            ((SampleAppActivity)getActivity()).togglePower(itemType, key);
        } else if (viewID == R.id.statusLabelName || viewID == R.id.statusTextName) {
            onHeaderClick();
        } else if (viewID == R.id.stateButton) {
            parent.showPresetsChildFragment(key, view.getTag().toString());
        }
    }

    public void setField(SeekBar seekBar) {
        int seekBarID = seekBar.getId();

        if (seekBarID == R.id.stateSliderBrightness) {
            ((SampleAppActivity)getActivity()).setBrightness(itemType, seekBar.getTag().toString(), seekBar.getProgress());
        } else if (seekBarID == R.id.stateSliderHue) {
            ((SampleAppActivity)getActivity()).setHue(itemType, seekBar.getTag().toString(), seekBar.getProgress());
        } else if (seekBarID == R.id.stateSliderSaturation) {
            ((SampleAppActivity)getActivity()).setSaturation(itemType, seekBar.getTag().toString(), seekBar.getProgress());
        } else if (seekBarID == R.id.stateSliderColorTemp) {
            ((SampleAppActivity)getActivity()).setColorTemp(itemType, seekBar.getTag().toString(), seekBar.getProgress() + DimmableItemScaleConverter.VIEW_COLORTEMP_MIN);
        }
    }

    public void updateInfoFields(DimmableItemDataModel itemModel) {
        if (itemModel.id.equals(key)) {
            if (itemModel.uniformity.power) {
                setImageButtonBackgroundResource(statusView, R.id.statusButtonPower, itemModel.state.getOnOff() ? R.drawable.power_button_on : R.drawable.power_button_off);
            } else {
                setImageButtonBackgroundResource(statusView, R.id.statusButtonPower, R.drawable.power_button_mix);
            }

            setTextViewValue(statusView, R.id.statusTextName, itemModel.getName(), 0);

            stateAdapter.setBrightness(itemModel.state.getBrightness(), itemModel.uniformity.brightness);
            stateAdapter.setHue(itemModel.state.getHue(), itemModel.uniformity.hue);
            stateAdapter.setSaturation(itemModel.state.getSaturation(), itemModel.uniformity.saturation);
            stateAdapter.setColorTemp(itemModel.state.getColorTemp(), itemModel.uniformity.colorTemp);

            // presets button
            updatePresetFields(itemModel);

            setColorIndicator(stateAdapter.stateView, itemModel.state);
        }
    }

    public void updatePresetFields() {
        updatePresetFields(itemModels.get(key));
    }

    public void updatePresetFields(DimmableItemDataModel itemModel) {
        updatePresetFields(itemModel != null ? itemModel.state : null, stateAdapter);
    }

    public void updatePresetFields(LampState itemState, LampStateViewAdapter itemAdapter) {
        itemAdapter.setPreset(Util.createPresetNamesString((SampleAppActivity)getActivity(), itemState));
    }

    public static int getColor(LampState lampState) {
        if (lampState != null) {
            int viewHue = DimmableItemScaleConverter.convertHueModelToView(lampState.getHue());
            int viewSaturation = DimmableItemScaleConverter.convertSaturationModelToView(lampState.getSaturation());
            int viewBrightness = DimmableItemScaleConverter.convertBrightnessModelToView(lampState.getBrightness());
            int viewColorTemp = DimmableItemScaleConverter.convertColorTempModelToView(lampState.getColorTemp());

            return DimmableItemScaleConverter.ColorTempToColorConverter.convert(viewColorTemp,
            		new float[] { viewHue,
                    (float) (viewSaturation / 100.0),
                    (float) (viewBrightness / 100.0) });
        } else {
            return defaultIndicatorColor;
        }
    }

    public void setColorIndicator(View parentStateView, LampState lampState) {
        parentStateView.findViewById(R.id.stateRowColorIndicator).getBackground().setColorFilter(getColor(lampState), Mode.MULTIPLY);
    }

    protected abstract int getLayoutID();
    protected abstract void onHeaderClick();
}
