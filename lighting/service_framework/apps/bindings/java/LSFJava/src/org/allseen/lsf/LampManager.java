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

public class LampManager extends BaseNativeClassWrapper {
    public LampManager(ControllerClient controller, LampManagerCallback callback) {
        createNativeObject(controller, callback);
    }

    public native ControllerClientStatus getAllLampIDs();
    public native ControllerClientStatus getLampManufacturer(String lampID, String language);
    public native ControllerClientStatus getLampName(String lampID, String language);
    public native ControllerClientStatus setLampName(String lampID, String lampName, String language);
    public native ControllerClientStatus getLampDetails(String lampID);
    public native ControllerClientStatus getLampParameters(String lampID);
    public native ControllerClientStatus getLampParametersEnergyUsageMilliwattsField(String lampID);
    public native ControllerClientStatus getLampParametersLumensField(String lampID);
    public native ControllerClientStatus getLampState(String lampID);
    public native ControllerClientStatus getLampStateOnOffField(String lampID);
    public native ControllerClientStatus getLampStateHueField(String lampID);
    public native ControllerClientStatus getLampStateSaturationField(String lampID);
    public native ControllerClientStatus getLampStateBrightnessField(String lampID);
    public native ControllerClientStatus getLampStateColorTempField(String lampID);
    public native ControllerClientStatus resetLampState(String lampID);
    public native ControllerClientStatus resetLampStateOnOffField(String lampID);
    public native ControllerClientStatus resetLampStateHueField(String lampID);
    public native ControllerClientStatus resetLampStateSaturationField(String lampID);
    public native ControllerClientStatus resetLampStateBrightnessField(String lampID);
    public native ControllerClientStatus resetLampStateColorTempField(String lampID);
    public native ControllerClientStatus transitionLampState(String lampID, LampState lampState, long transitionPeriod);
    public native ControllerClientStatus pulseLampWithState(String lampID, LampState toLampState, long period, long duration, long numPulses, LampState fromLampState);
    public native ControllerClientStatus pulseLampWithPreset(String lampID, String toPresetID, long period, long duration, long numPulses, String fromPresetID);
    public native ControllerClientStatus transitionLampStateOnOffField(String lampID, boolean onOff);
    public native ControllerClientStatus transitionLampStateHueField(String lampID, long hue, long transitionPeriod);
    public native ControllerClientStatus transitionLampStateSaturationField(String lampID, long saturation, long transitionPeriod);
    public native ControllerClientStatus transitionLampStateBrightnessField(String lampID, long brightness, long transitionPeriod);
    public native ControllerClientStatus transitionLampStateColorTempField(String lampID, long colorTemp, long transitionPeriod);
    public native ControllerClientStatus transitionLampStateToPreset(String lampID, String presetID, long transitionPeriod);
    public native ControllerClientStatus getLampFaults(String lampID);
    public native ControllerClientStatus getLampServiceVersion(String lampID);
    public native ControllerClientStatus clearLampFault(String lampID, long faultCode);
    public native ControllerClientStatus getLampSupportedLanguages(String lampID);
    public native ControllerClientStatus getLampDataSet(String lampID, String language);

    protected native void createNativeObject(ControllerClient controller, LampManagerCallback callback);

    @Override
    protected native void destroyNativeObject();
}
