/*
 * Copyright AllSeen Alliance. All rights reserved.
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

package org.allseen.lsf;

import org.allseen.lsf.sdk.ControllerClientStatus;
import org.allseen.lsf.sdk.TrackingID;

public class PulseEffectManager extends BaseNativeClassWrapper {
    public static final int MAX_PULSE_EFFECTS = 100;

    public PulseEffectManager(ControllerClient controller, PulseEffectManagerCallback callback) {
        createNativeObject(controller, callback);
    }

    public native ControllerClientStatus getAllPulseEffectIDs();
    public native ControllerClientStatus getPulseEffect(String pulseEffectID);
    public native ControllerClientStatus applyPulseEffectOnLamps(String pulseEffectID, String[] lampIDs);
    public native ControllerClientStatus applyPulseEffectOnLampGroups(String pulseEffectID, String[] lampGroupIDs);
    public native ControllerClientStatus getPulseEffectName(String pulseEffectID, String language);
    public native ControllerClientStatus setPulseEffectName(String pulseEffectID, String pulseEffectName, String language);
    public native ControllerClientStatus createPulseEffect(TrackingID trackingID, PulseEffectV2 pulseEffect, String pulseEffectName, String language);
    public native ControllerClientStatus updatePulseEffect(String pulseEffectID, PulseEffectV2 pulseEffect);
    public native ControllerClientStatus deletePulseEffect(String pulseEffectID);
    public native ControllerClientStatus getPulseEffectDataSet(String pulseEffectID, String language);

    protected native void createNativeObject(ControllerClient controller, PulseEffectManagerCallback callback);

    @Override
    protected native void destroyNativeObject() ;
}
