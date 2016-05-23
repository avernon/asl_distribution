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

import org.allseen.lsf.LampState;

public class PulseEffectDataModel extends BasicSceneElementDataModel {
    public static String defaultName = "";

    public boolean startWithCurrent;

    public String endPresetID;
    public LampState endState;

    public long period;
    public long duration;
    public long count;

    public PulseEffectDataModel() {
        super(EffectType.Pulse, defaultName);

        this.startWithCurrent = false;

        this.endPresetID = null;
        this.endState = new LampState();

        // State is always set to "on". To turn the lamp off as part of an effect,
        // you have to set the brightness to zero
        this.endState.setOnOff(true);

        this.period = 1000;
        this.duration = 500;
        this.count = 10;
    }

    public PulseEffectDataModel(PulseEffectDataModel other) {
        super(other);

        this.startWithCurrent = other.startWithCurrent;

        this.endPresetID = other.endPresetID;
        this.endState = new LampState(other.endState);

        this.period = other.period;
        this.duration = other.duration;
        this.count = other.count;
    }
}
