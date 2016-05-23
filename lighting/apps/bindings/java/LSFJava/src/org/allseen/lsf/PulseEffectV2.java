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
package org.allseen.lsf;

public class PulseEffectV2 extends DefaultNativeClassWrapper {
    public PulseEffectV2() {
        createNativeObject();
    }

    public PulseEffectV2(PulseEffectV2 other) {
        this();

        this.setToLampState(other.getToLampState());
        this.setFromLampState(other.getFromLampState());
        this.setToPresetID(other.getToPresetID());
        this.setFromPresetID(other.getFromPresetID());
        this.setPulsePeriod(other.getPulsePeriod());
        this.setPulseDuration(other.getPulseDuration());
        this.setNumPulses(this.getNumPulses());
    }

    public native void setToLampState(LampState lampState);
    public native LampState getToLampState();

    public native void setFromLampState(LampState lampState);
    public native LampState getFromLampState();

    public native void setToPresetID(String presetID);
    public native String getToPresetID();

    public native void setFromPresetID(String presetID);
    public native String getFromPresetID();

    public native void setPulsePeriod(long pulsePeriod);
    public native long getPulsePeriod();

    public native void setPulseDuration(long pulseDuration);
    public native long getPulseDuration();

    public native void setNumPulses(long numPulses);
    public native long getNumPulses();

    @Override
    protected native void createNativeObject();

    @Override
    protected native void destroyNativeObject();
}
