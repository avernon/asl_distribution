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

public class DimmableItemDataModel extends ItemDataModel {
    public static final char TAG_PREFIX_UNKNOWN = 'X';

    public LampState state;
    public LampStateUniformity uniformity;

    protected CapabilityData capability;

    public DimmableItemDataModel() {
        this("", TAG_PREFIX_UNKNOWN, "");
    }

    public DimmableItemDataModel(String itemID, char prefix, String itemName) {
        super(itemID, prefix, itemName);

        state = new LampState();
        uniformity = new LampStateUniformity();

        capability = new CapabilityData();

        state.setOnOff(false);
        state.setBrightness(0);
        state.setHue(0);
        state.setSaturation(0);
        state.setColorTemp(0);
    }

    public DimmableItemDataModel(DimmableItemDataModel other) {
        super(other);

        this.state = new LampState(other.state);
        this.uniformity = new LampStateUniformity(other.uniformity);
        this.capability = other.getCapability();
    }

    public boolean stateEquals(DimmableItemDataModel that) {
        return that != null ? stateEquals(that.state) : false;
    }

    public boolean stateEquals(LampState thatState) {
        boolean result = false;

        if (thatState != null) {
            // See if we are comparing full color (hsv) or color temp (ct) values
            boolean modeHSV = this.state.getSaturation() != 0;

            if (modeHSV) {
                result =
                    this.state.getHue() == thatState.getHue() &&
                    this.state.getSaturation() == thatState.getSaturation() &&
                    this.state.getBrightness() == thatState.getBrightness() &&
                    this.state.getOnOff() == thatState.getOnOff();
            } else {
                result =
                    this.state.getSaturation() == thatState.getSaturation() &&
                    this.state.getBrightness() == thatState.getBrightness() &&
                    this.state.getColorTemp() == thatState.getColorTemp() &&
                    this.state.getOnOff() == thatState.getOnOff();
            }
        }

        return result;
    }

    public void setCapability(CapabilityData capability) {
        this.capability = capability;
    }

    public CapabilityData getCapability() {
        return capability;
    }
}
