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
package org.allseen.lsf;

import org.allseen.lsf.sdk.ControllerClientStatus;
import org.allseen.lsf.sdk.TrackingID;

public class LampGroupManager extends BaseNativeClassWrapper {
    public static final int MAX_LAMP_GROUPS = 100;

    public LampGroupManager(ControllerClient controller, LampGroupManagerCallback callback) {
           createNativeObject(controller, callback);
    }

    public native ControllerClientStatus getAllLampGroupIDs();
    public native ControllerClientStatus getLampGroupName(String groupID, String language);
    public native ControllerClientStatus setLampGroupName(String groupID, String groupName, String language);
    public native ControllerClientStatus createLampGroup(LampGroup group, String groupName, String language);
    public native ControllerClientStatus updateLampGroup(String groupID, LampGroup group);
    public native ControllerClientStatus getLampGroup(String groupID);
    public native ControllerClientStatus deleteLampGroup(String groupID);
    public native ControllerClientStatus transitionLampGroupState(String groupID, LampState state, long duration);
    public native ControllerClientStatus pulseLampGroupWithState(String groupID, LampState toState, long period, long duration, long count, LampState fromState);
    public native ControllerClientStatus pulseLampGroupWithPreset(String groupID, String toPresetID, long period, long duration, long count, String fromPresetID);
    public native ControllerClientStatus transitionLampGroupStateOnOffField(String groupID, boolean onOff);
    public native ControllerClientStatus transitionLampGroupStateHueField(String groupID, long hue, long duration);
    public native ControllerClientStatus transitionLampGroupStateSaturationField(String groupID, long saturation, long duration);
    public native ControllerClientStatus transitionLampGroupStateBrightnessField(String groupID, long brightness, long duration);
    public native ControllerClientStatus transitionLampGroupStateColorTempField(String groupID, long colorTemp, long duration);
    public native ControllerClientStatus transitionLampGroupStateToPreset(String groupID, String presetID, long duration);
    public native ControllerClientStatus resetLampGroupState(String groupID);
    public native ControllerClientStatus resetLampGroupStateOnOffField(String groupID);
    public native ControllerClientStatus resetLampGroupStateHueField(String groupID);
    public native ControllerClientStatus resetLampGroupStateSaturationField(String groupID);
    public native ControllerClientStatus resetLampGroupStateBrightnessField(String groupID);
    public native ControllerClientStatus resetLampGroupStateColorTempField(String groupID);
    public native ControllerClientStatus createLampGroupWithTracking(TrackingID trackingID, LampGroup lampGroup, String lampGroupName, String language);
    public native ControllerClientStatus getLampGroupDataSet(String lampGroupID, String language);
    public native ControllerClientStatus setLampGroupEffect(String lampGroupID, String effectID);

    protected native void createNativeObject(ControllerClient controller, LampGroupManagerCallback callback);

    @Override
    protected native void destroyNativeObject();
}
