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

package org.allseen.lsf.sdk;

import org.allseen.lsf.DefaultNativeClassWrapper;

/**
 * This class encapsulates all of the details for lamps and illustrates the make/model of the lamp
 * as well as the capabilities of the lamp.
 */
public class LampDetails extends DefaultNativeClassWrapper {
    /**
     * Constructs a LampDetails object.
     * <p>
     * <b>WARNING: This method is intended to be used internally. Client software should not instantiate
     * LampDetails directly, but should instead get them from the {@link Lamp} using the {@link Lamp#getDetails()}
     * method.</b>
     */
    public LampDetails() {
        createNativeObject();
    }

    /**
     * Constructs a LampDetails object using the provided LampDetails.
     * <p>
     * <b>WARNING: This method is intended to be used internally. Client software should not instantiate
     * LampDetails directly, but should instead get them from the {@link Lamp} using the {@link Lamp#getDetails()}
     * method.</b>
     *
     * @param other The LampDetails object to use
     */
    public LampDetails(LampDetails other) {
        //TODO-IMPL
    }

    //TODO-FIX The methods returning primitives should return their
    //         Object equivalent so that we can return NULL on failure

    /**
     * Returns the make of the lamp.
     *
     * @return LampMake
     */
    public native LampMake getMake();

    /**
     * Returns the model of the lamp.
     *
     * @return LampModel
     */
    public native LampModel getModel();

    /**
     * Returns the device type of the lamp.
     *
     * @return DeviceType
     */
    public native DeviceType getType();

    /**
     * Returns the base type of the lamp.
     *
     * @return LampType
     */
    public native LampType getLampType();

    /**
     * Returns the base type of the lamp.
     *
     * @return BaseType
     */
    public native BaseType getLampBaseType();

    /**
     * Returns the beam angle of the lamp.
     *
     * @return Beam angle of the lamp
     */
    public native int getLampBeamAngle();

    /**
     * Indicates whether or not the lamp is dimmable.
     *
     * @return True if the lamp is dimmable, false otherwise
     */
    public native boolean isDimmable();

    /**
     * Indicates whether or not the lamp supports color.
     *
     * @return True if the lamp supports color, false otherwise
     */
    public native boolean hasColor();

    /**
     * Indicates whether or not the lamp has a variable color temperature.
     *
     * @return True if the lamp supports variable color temperature, false otherwise
     */
    public native boolean hasVariableColorTemp();

    /**
     * Indicates whether or not the lamp supports effects (i.e. pulse effects, etc.).
     *
     * @return True if the lamp supports effects, false otherwise
     */
    public native boolean hasEffects();

    /**
     * Returns the minimum voltage of the lamp.
     *
     * @return Minimum lamp volatge
     */
    public native int getMinVoltage();

    /**
     * Returns the maximum voltage of the lamp.
     *
     * @return Maximum lamp volatge
     */
    public native int getMaxVoltage();

    /**
     * Returns the wattage of the lamp.
     *
     * @return Lamp wattage
     */
    public native int getWattage();

    /**
     * Returns the incandescent wattage of the lamp.
     *
     * @return Incandescent wattage equivalent.
     */
    public native int getIncandescentEquivalent();

    /**
     * Returns the max lumens supported by the lamp.
     *
     * @return Lamp max lumens
     */
    public native int getMaxLumens();

    /**
     * Returns the minimum color temperature of the lamp.
     *
     * @return Lamp minimum color temperature
     */
    public native int getMinTemperature();

    /**
     * Returns the maximum color temperature of the lamp.
     *
     * @return Lamp maximum color temperature
     */
    public native int getMaxTemperature();

    /**
     * Returns the color rendering index of the lamp.
     *
     * @return Lamp color rendering index.
     */
    public native int getColorRenderingIndex();

    /**
     * Returns the ID of the lamp.
     *
     * @return ID of the lamp
     */
    public native String getLampID();

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected native void createNativeObject();

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected native void destroyNativeObject();
}
