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

public class LampDetails extends DefaultNativeClassWrapper {
    public LampDetails() {
        createNativeObject();
    }

    public LampDetails(LampDetails other) {
        //TODO-IMPL
    }

    //TODO-FIX The methods returning primitives should return their
    //         Object equivalent so that we can return NULL on failure
    public native LampMake getMake();
    public native LampModel getModel();
    public native DeviceType getType();
    public native LampType getLampType();
    public native BaseType getLampBaseType();
    public native int getLampBeamAngle();
    public native boolean isDimmable();
    public native boolean hasColor();
    public native boolean hasVariableColorTemp();
    public native boolean hasEffects();
    public native int getMinVoltage();
    public native int getMaxVoltage();
    public native int getWattage();
    public native int getIncandescentEquivalent();
    public native int getMaxLumens();
    public native int getMinTemperature();
    public native int getMaxTemperature();
    public native int getColorRenderingIndex();
    public native String getLampID();

    @Override
    protected native void createNativeObject();

    @Override
    protected native void destroyNativeObject();
}
