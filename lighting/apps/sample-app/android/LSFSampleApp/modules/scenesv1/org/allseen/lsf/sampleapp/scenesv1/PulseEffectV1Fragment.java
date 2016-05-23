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
package org.allseen.lsf.sampleapp.scenesv1;

import org.allseen.lsf.sampleapp.EnterCountFragment;
import org.allseen.lsf.sampleapp.EnterDurationFragment;
import org.allseen.lsf.sampleapp.EnterPeriodFragment;
import org.allseen.lsf.sampleapp.LampStateViewAdapter;
import org.allseen.lsf.sampleapp.MemberNamesOptions;
import org.allseen.lsf.sampleapp.R;
import org.allseen.lsf.sampleapp.SampleAppActivity;
import org.allseen.lsf.sampleapp.ScenesPageFragment;
import org.allseen.lsf.sdk.Color;
import org.allseen.lsf.sdk.LampCapabilities;
import org.allseen.lsf.sdk.LampStateUniformity;
import org.allseen.lsf.sdk.MyLampState;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.SeekBar;
import android.widget.TextView;

public class PulseEffectV1Fragment extends EffectV1InfoFragment implements OnCheckedChangeListener {
    public static PendingPulseEffectV1 pendingPulseEffect;

    protected LampStateViewAdapter stateAdapter2;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = super.onCreateView(inflater, container, savedInstanceState);

        setTextViewValue(view.findViewById(R.id.infoStatusRow), R.id.statusLabelName, getString(R.string.label_effect_name), 0);

        setTextViewValue(view.findViewById(R.id.infoStateRow), R.id.stateMainLabel, getString(R.string.state_label_header_start), 0);
        setTextViewValue(view.findViewById(R.id.infoStateRow2), R.id.stateMainLabel, getString(R.string.state_label_header_end), 0);

        setTextViewValue(view.findViewById(R.id.infoPeriodRow), R.id.nameValueNameText, getString(R.string.effect_info_period_name), 0);
        setTextViewValue(view.findViewById(R.id.infoDurationRow), R.id.nameValueNameText, getString(R.string.effect_info_pulse_duration), 0);
        setTextViewValue(view.findViewById(R.id.infoCountRow), R.id.nameValueNameText, getString(R.string.effect_info_count_name), 0);

        // second presets button
        Button presetsButton2 = (Button)view.findViewById(R.id.infoStateRow2).findViewById(R.id.stateButton);
        presetsButton2.setTag(STATE2_ITEM_TAG);
        presetsButton2.setClickable(true);
        presetsButton2.setOnClickListener(this);

        TextView periodName = (TextView)view.findViewById(R.id.infoPeriodRow).findViewById(R.id.nameValueNameText);
        periodName.setTag(R.id.infoPeriodRow);
        periodName.setClickable(true);
        periodName.setOnClickListener(this);

        TextView periodValue = (TextView)view.findViewById(R.id.infoPeriodRow).findViewById(R.id.nameValueValueText);
        periodValue.setTag(R.id.infoPeriodRow);
        periodValue.setClickable(true);
        periodValue.setOnClickListener(this);

        TextView durationName = (TextView)view.findViewById(R.id.infoDurationRow).findViewById(R.id.nameValueNameText);
        durationName.setTag(R.id.infoDurationRow);
        durationName.setClickable(true);
        durationName.setOnClickListener(this);

        TextView durationValue = (TextView)view.findViewById(R.id.infoDurationRow).findViewById(R.id.nameValueValueText);
        durationValue.setTag(R.id.infoDurationRow);
        durationValue.setClickable(true);
        durationValue.setOnClickListener(this);

        TextView countName = (TextView)view.findViewById(R.id.infoCountRow).findViewById(R.id.nameValueNameText);
        countName.setTag(R.id.infoCountRow);
        countName.setClickable(true);
        countName.setOnClickListener(this);

        TextView countValue = (TextView)view.findViewById(R.id.infoCountRow).findViewById(R.id.nameValueValueText);
        countValue.setTag(R.id.infoCountRow);
        countValue.setClickable(true);
        countValue.setOnClickListener(this);

        View currentStateRow = view.findViewById(R.id.infoStateRow).findViewById(R.id.startWithCurrentStateRow);
        currentStateRow.setVisibility(View.VISIBLE);

        CompoundButton currentStateRowTick = (CompoundButton) currentStateRow.findViewById(R.id.startWithCurrentStateTick);
        currentStateRowTick.setClickable(true);
        currentStateRowTick.setOnClickListener(this);
        currentStateRowTick.setOnCheckedChangeListener(this);
        currentStateRowTick.setChecked(pendingPulseEffect.startWithCurrent);

        // state adapter
        stateAdapter2 = new LampStateViewAdapter(view.findViewById(R.id.infoStateRow2), STATE2_ITEM_TAG, getColorTempMin(), getColorTempSpan(), this);

        initLampState();

        setColorIndicator(view.findViewById(R.id.infoStateRow2), pendingPulseEffect.endState, EffectV1InfoFragment.pendingBasicSceneElementCapability, getColorTempDefault());

        updateInfoFields(pendingPulseEffect.name, pendingPulseEffect.startState, EffectV1InfoFragment.pendingBasicSceneElementCapability, pendingPulseEffect.uniformity);

        return view;
    }

    // Override parent to initiate an effect type change on button press
    @Override
    public void onClick(View view) {
        int viewID = view.getId();

        if (viewID == R.id.nameValueNameText || viewID == R.id.nameValueValueText) {
            int viewSubID = ((Integer)view.getTag()).intValue();

            if (viewSubID == R.id.infoPeriodRow) {
                onPeriodClick();
            } else if (viewSubID == R.id.infoDurationRow) {
                onDurationClick();
            } else if (viewSubID == R.id.infoCountRow) {
                onCountClick();
            }
        } else {
            super.onClick(view);
        }
    }

    @Override
    protected void updateInfoFields(String name, MyLampState state, LampCapabilities capability, LampStateUniformity uniformity) {
        // Capabilities can change if the member set is edited
        stateAdapter.setCapability(capability);
        stateAdapter2.setCapability(capability);

        super.updateInfoFields(name, state, capability, uniformity);

        updatePulseEffectInfoFields((SampleAppActivity)getActivity());
    }

    @Override
    public void updatePresetFields(MyLampState itemState) {
        super.updatePresetFields(itemState);

        updatePresetFields(new MyLampState(PulseEffectV1Fragment.pendingPulseEffect.endState), stateAdapter2);
    }

    protected void updatePulseEffectInfoFields(SampleAppActivity activity) {
        String members = BasicSceneV1Util.formatMemberNamesString(activity, PulseEffectV1Fragment.pendingBasicSceneElementMembers, MemberNamesOptions.en, 3, R.string.effect_info_help_no_members);
        setTextViewValue(view.findViewById(R.id.infoHelpRow), R.id.helpText, String.format(getString(R.string.effect_info_help_pulse), members), 0);

        // Superclass updates the icon, so we have to re-override
        setImageButtonBackgroundResource(statusView, R.id.statusButtonPower, R.drawable.list_pulse_icon);

        Color endColor = pendingPulseEffect.endState.getColor();
        stateAdapter2.setBrightness(endColor.getBrightness(), true);
        stateAdapter2.setHue(endColor.getHue(), true);
        stateAdapter2.setSaturation(endColor.getSaturation(), true);
        stateAdapter2.setColorTemp(endColor.getColorTemperature(), true);

        String periodValue = String.format(getString(R.string.effect_info_period_format), EnterPeriodFragment.period / 1000.0);
        setTextViewValue(view.findViewById(R.id.infoPeriodRow), R.id.nameValueValueText, periodValue, R.string.units_seconds);

        String durationValue = String.format(getString(R.string.effect_info_period_format), EnterDurationFragment.duration / 1000.0);
        setTextViewValue(view.findViewById(R.id.infoDurationRow), R.id.nameValueValueText, durationValue, R.string.units_seconds);

        setTextViewValue(view.findViewById(R.id.infoCountRow), R.id.nameValueValueText, EnterCountFragment.count, 0);
    }

    @Override
    protected int getLayoutID() {
        return R.layout.fragment_effect_pulse;
    }

    protected void onPeriodClick() {
        ((ScenesPageFragment)parent).showEnterPeriodChildFragment();
    }

    protected void onDurationClick() {
        ((ScenesPageFragment)parent).showEnterDurationChildFragment();
    }

    protected void onCountClick() {
        ((ScenesPageFragment)parent).showEnterCountChildFragment();
    }

    @Override
    protected int getLampStateCount() {
        return 2;
    }

    @Override
    protected int getIndexForTag(Object tag) {
        return tag == STATE2_ITEM_TAG ? 1 : super.getIndexForTag(tag);
    }

    @Override
    protected MyLampState getPendingLampState(int index) {
        logErrorOnInvalidIndex(index);

        return index == 1 ? pendingPulseEffect.endState : pendingPulseEffect.startState;
    }

    @Override
    protected LampStateViewAdapter getLampStateViewAdapter(int index) {
        logErrorOnInvalidIndex(index);

        return index == 1 ? stateAdapter2 : super.getLampStateViewAdapter(index);
    }

    @Override
    protected String getPendingPresetID(int index) {
        logErrorOnInvalidIndex(index);

        return index == 1 ? pendingPulseEffect.endPresetID : pendingPulseEffect.startPresetID;
    }

    @Override
    protected void setPendingPresetID(int index, String presetID) {
        logErrorOnInvalidIndex(index);

        if (index == 1) {
            pendingPulseEffect.endPresetID = presetID;
        } else {
            pendingPulseEffect.startPresetID = presetID;
        }
    }

    @Override
    public void updatePendingSceneElement() {
        pendingPulseEffect.updateDataModel(pendingBasicSceneElementMembers, pendingBasicSceneElementCapability);

        BasicSceneV1InfoFragment.pendingBasicSceneModel.updatePulseEffect(pendingPulseEffect.dataModel);
    }

    @Override
    public void onCheckedChanged(CompoundButton stateRowTick, boolean checked) {
        pendingPulseEffect.startWithCurrent = checked;

        ((SeekBar)view.findViewById(R.id.stateSliderBrightness)).setEnabled(!checked);
        ((SeekBar)view.findViewById(R.id.stateSliderHue)).setEnabled(!checked);
        ((SeekBar)view.findViewById(R.id.stateSliderSaturation)).setEnabled(!checked);
        ((SeekBar)view.findViewById(R.id.stateSliderColorTemp)).setEnabled(!checked);
        ((Button)view.findViewById(R.id.stateButton)).setClickable(!checked);
    }
}
