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

public class CapabilityData {

    public static final int UNSET = -1;
    public static final int NONE = 0;
    public static final int SOME = 1;
    public static final int ALL = 2;

    public int dimmable;
    public int color;
    public int temp;

    // creates a dirty, unset CapabilityData
    public CapabilityData() {
        dimmable = UNSET;
        color = UNSET;
        temp = UNSET;
    }

    public CapabilityData(CapabilityData other) {
        dimmable = other.dimmable;
        color = other.color;
        temp = other.temp;
    }

    public CapabilityData(boolean dimmable, boolean color, boolean temp) {
        this.dimmable = dimmable ? ALL : NONE;
        this.color = color ? ALL : NONE;
        this.temp = temp ? ALL : NONE;
    }

    public void includeData(CapabilityData data) {
        if (data != null) {
            dimmable = combine(dimmable, data.dimmable);
            color = combine(color, data.color);
            temp = combine(temp, data.temp);
        } else {
            // there is nothing to do with a null CapabilityData except to treat it as UNSET
            // that scenario reduces to doing nothing
            return;
        }
    }

    // determines if this capability is mixed
    public boolean isMixed() {
        // all lamps of the same type implies that there will be no SOME capability state
        // mixed lamps implies at least 1 mismatch in capabilities implies at least 1 SOME capability state
        return (dimmable == SOME) || (color == SOME) || (temp == SOME);
    }

    // determines if the combination of a and b is unset, none, some, or all
    private int combine(int a, int b) {
        switch (a) {
            case UNSET:
                // there's no real data in a, use b
                return b;
            case NONE:
                // none if b is none or unset, else some
                return (b == NONE || b == UNSET) ? NONE : SOME;
            case SOME:
                // some will always be some
                return SOME;
            case ALL:
                // all if b is all or unset, else some
                return (b == ALL || b == UNSET) ? ALL : SOME;
            default:
                return UNSET;
        }
    }

    @Override
    public String toString() {
        return "[dimmable: " + dimmable + " color: " + color + " temp: " + temp + " ]";
    }
}
