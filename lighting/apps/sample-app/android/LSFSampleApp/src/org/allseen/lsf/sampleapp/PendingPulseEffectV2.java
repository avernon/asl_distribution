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

import org.allseen.lsf.sdk.Color;
import org.allseen.lsf.sdk.LampStateUniformity;
import org.allseen.lsf.sdk.MyLampState;
import org.allseen.lsf.sdk.Power;
import org.allseen.lsf.sdk.PulseEffect;

public class PendingPulseEffectV2 extends PendingLightingItem {
    public boolean startWithCurrent;

    public MyLampState startState;
    public MyLampState endState;

    public String startPresetID;
    public String endPresetID;

    public long period;
    public long duration;
    public long count;

    public final LampStateUniformity uniformity = new LampStateUniformity();

    public PendingPulseEffectV2() {
        this((PulseEffect)null);
    }

    public PendingPulseEffectV2(PulseEffect pulseEffect) {
        init(pulseEffect);

        startWithCurrent = pulseEffect != null ? pulseEffect.isStartWithCurrent() : false;

        // Note the lamp states must have their own instance of a Color object
        startState = pulseEffect != null ? pulseEffect.getStartState() : new MyLampState(Power.ON, new Color(Color.defaultColor()));
        endState = pulseEffect != null ? pulseEffect.getEndState() : new MyLampState(Power.ON, new Color(Color.defaultColor()));

        startPresetID = pulseEffect != null ? pulseEffect.getStartPresetID() : "";
        endPresetID = pulseEffect != null ? pulseEffect.getEndPresetID() : "";

        period = pulseEffect != null ? pulseEffect.getPeriod() : 1000;
        duration = pulseEffect != null ? pulseEffect.getDuration() : 500;
        count = pulseEffect != null ? pulseEffect.getCount() : 10;
    }

    public PendingPulseEffectV2(PendingPulseEffectV2 pendingPulseEffect) {
        init(pendingPulseEffect.id, pendingPulseEffect.name);

        startWithCurrent = pendingPulseEffect.startWithCurrent;

        startState = new MyLampState(pendingPulseEffect.startState);
        endState = new MyLampState(pendingPulseEffect.endState);

        startPresetID = pendingPulseEffect.startPresetID;
        endPresetID = pendingPulseEffect.endPresetID;

        period = pendingPulseEffect.period;
        duration = pendingPulseEffect.duration;
        count = pendingPulseEffect.count;
    }
}
