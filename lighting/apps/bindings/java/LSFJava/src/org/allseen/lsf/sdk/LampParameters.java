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
 * This class encapsulates all of the parameters for lamps and illustrates the current energy usage and
 * brightness output of the lamp.
 */
public class LampParameters extends DefaultNativeClassWrapper {
    /**
     * Constructs a LampParameters object.
     * <p>
     * <b>WARNING: This method is intended to be used internally. Client software should not instantiate
     * LampParameters directly, but should instead get them from the {@link Lamp} using the {@link Lamp#getParameters()}
     * method.</b>
     */
    public LampParameters() {
        createNativeObject();
    }

    /**
     * Constructs a LampParameters object using the provided LampParameters.
     * <p>
     * <b>WARNING: This method is intended to be used internally. Client software should not instantiate
     * LampParameters directly, but should instead get them from the {@link Lamp} using the {@link Lamp#getParameters()}
     * method.</b>
     *
     * @param other The LampParameters object to use
     */
    public LampParameters(LampParameters other) {
        //TODO-IMPL
    }

    //TODO-FIX The methods returning primitives should return their
    //         Object equivalent so that we can return NULL on failure

    /**
     * Returns the current energy usage of the lamp, in milliwatts.
     *
     * @return Energy usage of the lamp, in milliwatts
     */
    public native int getEnergyUsageMilliwatts();

    /**
     * Returns the current brightness of the lamp, in lumens.
     *
     * @return Brightness of the lamp, in lumens
     */
    public native int getLumens();

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
