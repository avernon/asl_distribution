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
import org.allseen.lsf.sdk.Preset;

public class PendingPresetEffect extends PendingLightingItem {
    public final LampStateUniformity uniformity = new LampStateUniformity();

    public MyLampState state;

    public PendingPresetEffect() {
        this((Preset)null);
    }

    public PendingPresetEffect(Preset preset) {
        init(preset);

        // Note the lamp state must have its own instance of a Color object
        state = preset != null ? preset.getState() : new MyLampState(Power.ON, new Color(Color.defaultColor()));
    }

    public PendingPresetEffect(PendingPresetEffect pendingPresetEffect) {
        init(pendingPresetEffect.id, pendingPresetEffect.name);

        state = new MyLampState(pendingPresetEffect.state);
    }
}
