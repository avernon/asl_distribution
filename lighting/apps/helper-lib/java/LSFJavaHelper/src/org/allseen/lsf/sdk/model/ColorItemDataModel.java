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
package org.allseen.lsf.sdk.model;

import org.allseen.lsf.LampState;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class ColorItemDataModel extends LightingItemDataModel {
    public static final char TAG_PREFIX_UNKNOWN = 'X';

    public LampState state;
    public LampStateUniformity uniformity;

    protected LampCapabilities capability;
    protected boolean stateInitialized;

    public ColorItemDataModel() {
        this(null, TAG_PREFIX_UNKNOWN, "");
    }

    public ColorItemDataModel(String itemID, char prefix, String itemName) {
        super(itemID, prefix, itemName);

        state = new LampState();
        uniformity = new LampStateUniformity();

        capability = new LampCapabilities();

        state.setOnOff(false);
        state.setBrightness(0);
        state.setHue(0);
        state.setSaturation(0);
        state.setColorTemp(0);

        stateInitialized = false;
    }

    public ColorItemDataModel(ColorItemDataModel other) {
        super(other);

        this.state = new LampState(other.state);
        this.uniformity = new LampStateUniformity(other.uniformity);
        this.capability = other.getCapability();
        this.stateInitialized = other.stateInitialized;
    }

    public boolean stateEquals(ColorItemDataModel that) {
        return that != null ? stateEquals(that.state) : false;
    }

    public boolean stateEquals(LampState that) {
        return that != null ? stateEquals(that.getOnOff(), that.getHue(), that.getSaturation(), that.getBrightness(), that.getColorTemp()) : false;
    }

    public boolean stateEquals(boolean onOff, long hue, long saturation, long brightness, long colorTemp) {
        return
            this.state.getHue()         == hue          &&
            this.state.getSaturation()  == saturation   &&
            this.state.getBrightness()  == brightness   &&
            this.state.getColorTemp()   == colorTemp    &&
            this.state.getOnOff()       == onOff;
    }

    public void setCapability(LampCapabilities capability) {
        this.capability = capability;
    }

    public LampCapabilities getCapability() {
        return capability;
    }

    public LampState getState() {
        return state;
    }

    public void setState(LampState state) {
        this.state = state;
        stateInitialized = true;
    }

    @Override
    public boolean isInitialized() {
        return super.isInitialized() && stateInitialized;
    }
}
