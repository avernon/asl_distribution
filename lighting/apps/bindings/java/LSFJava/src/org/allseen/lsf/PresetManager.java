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

public class PresetManager extends BaseNativeClassWrapper {
    public static final int MAX_PRESETS = 100;

    public PresetManager(ControllerClient controller, PresetManagerCallback callback) {
         createNativeObject(controller, callback);
    }

    public native ControllerClientStatus getAllPresetIDs();
    public native ControllerClientStatus getPreset(String presetID);
    public native ControllerClientStatus getPresetName(String presetID, String language);
    public native ControllerClientStatus setPresetName(String presetID, String presetName, String language);
    public native ControllerClientStatus createPreset(LampState preset, String presetName, String language);
    public native ControllerClientStatus updatePreset(String presetID, LampState preset);
    public native ControllerClientStatus deletePreset(String presetID);
    public native ControllerClientStatus getDefaultLampState();
    public native ControllerClientStatus setDefaultLampState(LampState defaultLampState);
    public native ControllerClientStatus createPresetWithTracking(TrackingID trackingID, LampState preset, String presetName, String language);
    public native ControllerClientStatus getPresetDataSet(String presetID, String language);

    protected native void createNativeObject(ControllerClient controller, PresetManagerCallback callback);

    @Override
    protected native void destroyNativeObject();
}
