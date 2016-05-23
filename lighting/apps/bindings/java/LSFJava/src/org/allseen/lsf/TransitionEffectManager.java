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

public class TransitionEffectManager extends BaseNativeClassWrapper {
    public static final int MAX_TRANSITION_EFFECTS = 100;

    public TransitionEffectManager(ControllerClient controller, TransitionEffectManagerCallback callback) {
         createNativeObject(controller, callback);
    }

    public native ControllerClientStatus getAllTransitionEffectIDs();
    public native ControllerClientStatus getTransitionEffect(String transitionEffectID);
    public native ControllerClientStatus applyTransitionEffectOnLamps(String transitionEffectID, String[] lampIDs);
    public native ControllerClientStatus applyTransitionEffectOnLampGroups(String transitionEffectID, String[] lampGroupIDs);
    public native ControllerClientStatus getTransitionEffectName(String transitionEffectID, String language);
    public native ControllerClientStatus setTransitionEffectName(String transitionEffectID, String transitionEffectName, String language);
    public native ControllerClientStatus createTransitionEffect(TrackingID trackingID, TransitionEffectV2 transitionEffect, String transitionEffectName, String language);
    public native ControllerClientStatus updateTransitionEffect(String transitionEffectID, TransitionEffectV2 transitionEffect);
    public native ControllerClientStatus deleteTransitionEffect(String transitionEffectID);
    public native ControllerClientStatus getTransitionEffectDataSet(String transitionEffectID, String language);

    protected native void createNativeObject(ControllerClient controller, TransitionEffectManagerCallback callback);

    @Override
    protected native void destroyNativeObject();
}
