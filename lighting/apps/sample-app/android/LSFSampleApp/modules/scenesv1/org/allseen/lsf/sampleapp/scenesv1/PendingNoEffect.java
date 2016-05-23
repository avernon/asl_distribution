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
import org.allseen.lsf.sampleapp.PendingPresetEffect;
import org.allseen.lsf.sdk.Color;
import org.allseen.lsf.sdk.LampCapabilities;
import org.allseen.lsf.sdk.MyLampState;
import org.allseen.lsf.sdk.model.ColorStateConverter;
import org.allseen.lsf.sdk.model.NoEffectDataModel;

public class PendingNoEffect extends PendingPresetEffect {
    NoEffectDataModel dataModel;
    String presetID;

    public PendingNoEffect() {
        this(new NoEffectDataModel());
    }

    public PendingNoEffect(NoEffectDataModel dataModel) {
        this.dataModel = dataModel;

        id = dataModel.id;
        name = dataModel.getName();
        state = new MyLampState(dataModel.state);
        presetID = dataModel.presetID;
    }

    public void updateDataModel(LampGroup members, LampCapabilities capabilities) {
        dataModel.members = members;
        dataModel.setCapability(capabilities);

        dataModel.presetID = presetID;

        Color color = state.getColor();
        dataModel.state = new LampState();
        dataModel.state.setOnOff(state.isOn());
        dataModel.state.setHue(ColorStateConverter.convertHueViewToModel(color.getHue()));
        dataModel.state.setSaturation(ColorStateConverter.convertSaturationViewToModel(color.getSaturation()));
        dataModel.state.setBrightness(ColorStateConverter.convertBrightnessViewToModel(color.getBrightness()));
        dataModel.state.setColorTemp(ColorStateConverter.convertColorTempViewToModel(color.getColorTemperature()));
    }
}
