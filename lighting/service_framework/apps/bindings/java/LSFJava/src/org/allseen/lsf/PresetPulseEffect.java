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

public class PresetPulseEffect extends DefaultNativeClassWrapper implements PulseEffect {
    public static String PRESET_ID_CURRENT_STATE = "CURRENT_STATE";

    public PresetPulseEffect() {
        createNativeObject();
    }

    public PresetPulseEffect(PresetPulseEffect other) {
        this();

        this.setLamps(other.getLamps());
        this.setLampGroups(other.getLampGroups());
        this.setPulsePeriod(other.getPulsePeriod());
        this.setPulseDuration(other.getPulseDuration());
        this.setPulseCount(other.getPulseCount());
        this.setFromPreset(other.getFromPreset());
        this.setToPreset(other.getToPreset());
    }

    @Override
    public native void setLamps(String[] lampIDs);
    @Override
    public native String[] getLamps();

    @Override
    public native void setLampGroups(String[] lampGroupIDs);
    @Override
    public native String[] getLampGroups();

    @Override
    public native void setPulsePeriod(long pulsePeriod);
    @Override
    public native long getPulsePeriod();

    @Override
    public native void setPulseDuration(long pulseDuration);
    @Override
    public native long getPulseDuration();

    @Override
    public native void setPulseCount(long pulseCount);
    @Override
    public native long getPulseCount();

    public native void setFromPreset(String presetID);
    public native String getFromPreset();

    public native void setToPreset(String presetID);
    public native String getToPreset();

    @Override
    public native String toString();

    @Override
    protected native void createNativeObject();

    @Override
    protected native void destroyNativeObject();
}
