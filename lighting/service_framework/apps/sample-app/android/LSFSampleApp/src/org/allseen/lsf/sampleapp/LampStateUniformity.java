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

public class LampStateUniformity {

    public boolean power;
    public boolean hue;
    public boolean saturation;
    public boolean brightness;
    public boolean colorTemp;

    public LampStateUniformity() {
        this(true, true, true, true, true);
    }

    public LampStateUniformity(boolean power, boolean hue, boolean saturation, boolean brightness, boolean colorTemp) {
        this.power = power;
        this.hue = hue;
        this.saturation = saturation;
        this.brightness = brightness;
        this.colorTemp = colorTemp;
    }

    public LampStateUniformity(LampStateUniformity other) {
        this.power = other.power;
        this.hue = other.hue;
        this.saturation = other.saturation;
        this.brightness = other.brightness;
        this.colorTemp = other.colorTemp;
    }
}
