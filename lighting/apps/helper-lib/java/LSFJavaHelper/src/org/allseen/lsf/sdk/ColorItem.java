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
package org.allseen.lsf.sdk;

import org.allseen.lsf.sdk.model.ColorItemDataModel;
import org.allseen.lsf.sdk.model.ColorStateConverter;
import org.allseen.lsf.sdk.model.LightingItemDataModel;

/**
 * Abstract base class for Lighting Items that support Color in the Lighting system.
 */
public abstract class ColorItem extends LightingItem {

    /**
     * Returns the HSVT color state of the Lighting item
     *
     * @return Integer array containing the HSVT color of the Lighting item
     */
    public int[] getColorHsvt() {
        return ColorStateConverter.convertModelToView(getColorDataModel().getState());
    }

    /**
     * Returns the power state of the Lighting item.
     *
     * @return Returns true if the Lighting item power state is on, false otherwise
     */
    public boolean getPowerOn() {
        return getColorDataModel().getState().getOnOff();
    }

    /**
     * Returns the power state of the Lighting item.
     *
     * @return Returns true if the Lighting item power state is on, false otherwise
     */
    public boolean isOn() {
        return getPowerOn();
    }

    /**
     * Returns the power state of the Lighting item.
     *
     * @return Returns true if the Lighting item power state is off, false otherwise
     */
    public boolean isOff() {
        return !isOn();
    }

    /**
     * Returns the power state of the Lighting item.
     *
     * @return Returns ON if the Lighting item power state is on, OFF otherwise
     */
    public Power getPower() {
        return (getPowerOn())? Power.ON : Power.OFF;
    }

    /**
     * Returns the HSVT color state of the Lighting item
     *
     * @return Reference to Color object
     */
    public Color getColor() {
        return new Color(getColorHsvt());
    }

    /**
     * Returns the power and color state of the Lighting item
     *
     * @return Reference to MyLampState object
     */
    public MyLampState getState() {
        return new MyLampState(getPower(), getColor());
    }

    /**
     * Returns the uniformity information of the Lighting item.
     *
     * @return Reference to LampStateUniformity object
     */
    public LampStateUniformity getUniformity() {
        return new LampStateUniformity(getColorDataModel().uniformity);
    }

    /**
     * Returns the capabilities of the Lighting item.
     *
     * @return Reference to LampCapabilities object
     */
    public LampCapabilities getCapability() {
        return new LampCapabilities(getColorDataModel().getCapability());
    }

    /**
     * Sets the capabilities of the Lighting item.
     *
     * @param capability Reference to LampCapabilities object
     */
    public void setCapability(LampCapabilities capability) {
        getColorDataModel().setCapability(capability);
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected LightingItemDataModel getItemDataModel() {
        return getColorDataModel();
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected abstract ColorItemDataModel getColorDataModel();
}
