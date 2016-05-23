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
package org.allseen.lsf.sampleapp.scenesv1;

import org.allseen.lsf.LampGroup;
import org.allseen.lsf.LampState;
import org.allseen.lsf.sampleapp.EnterCountFragment;
import org.allseen.lsf.sampleapp.EnterDurationFragment;
import org.allseen.lsf.sampleapp.EnterPeriodFragment;
import org.allseen.lsf.sampleapp.PendingPulseEffectV2;
import org.allseen.lsf.sdk.Color;
import org.allseen.lsf.sdk.LampCapabilities;
import org.allseen.lsf.sdk.MyLampState;
import org.allseen.lsf.sdk.model.ColorStateConverter;
import org.allseen.lsf.sdk.model.PulseEffectDataModel;

public class PendingPulseEffectV1 extends PendingPulseEffectV2 {
    PulseEffectDataModel dataModel;

    public PendingPulseEffectV1() {
        this(new PulseEffectDataModel());
    }

    public PendingPulseEffectV1(PulseEffectDataModel dataModel) {
        this.dataModel = dataModel;

        id = dataModel.id;
        name = dataModel.getName();

        startState = new MyLampState(dataModel.state);
        startPresetID = dataModel.presetID;
        startWithCurrent = dataModel.startWithCurrent;

        endState = new MyLampState(dataModel.endState);
        endPresetID = dataModel.endPresetID;

        EnterPeriodFragment.period = dataModel.period;
        EnterDurationFragment.duration = dataModel.duration;
        EnterCountFragment.count = dataModel.count;
    }

    public void updateDataModel(LampGroup members, LampCapabilities capabilities) {
        dataModel.members = members;
        dataModel.setCapability(capabilities);

        dataModel.state = copyLampState(startState, new LampState());
        dataModel.presetID = startPresetID;
        dataModel.startWithCurrent = startWithCurrent;

        dataModel.endState = copyLampState(endState, new LampState());
        dataModel.endPresetID = endPresetID;

        dataModel.period = EnterPeriodFragment.period;
        dataModel.duration = EnterDurationFragment.duration;
        dataModel.count = EnterCountFragment.count;
    }

    protected static LampState copyLampState(MyLampState source, LampState destination) {
        Color color = source.getColor();

        destination.setOnOff(source.isOn());
        destination.setHue(ColorStateConverter.convertHueViewToModel(color.getHue()));
        destination.setSaturation(ColorStateConverter.convertSaturationViewToModel(color.getSaturation()));
        destination.setBrightness(ColorStateConverter.convertBrightnessViewToModel(color.getBrightness()));
        destination.setColorTemp(ColorStateConverter.convertColorTempViewToModel(color.getColorTemperature()));

        return destination;
    }
}
