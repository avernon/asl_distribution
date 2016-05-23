/*
 * Copyright AllSeen Alliance. All rights reserved.
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

/**
 * Enum describing how mobile the device that is running the controller service.
 */
public enum RankMobility {
    /**
     * Devices like smartphones will fall in this category
     */
    HIGH_MOBILITY,

    /**
     * Examples are tablets & laptops
     */
    INTERMEDIATE_MOBILITY,

    /**
     * Mostly stationary and proximal devices fall in this category. An example is wireless speaker
     */
    LOW_MOBILITY,

    /**
     * Examples are WiFi Access Point, TV
     */
    ALWAYS_STATIONARY,

    /**
     * If OEMs return this value, the Controller Service will use HIGH_MOBILITY as this is not a valid value
     */
    OEM_CS_RANKPARAM_MOBILITY_LAST_VALUE;

    /** Static lookup, used by the native code */
    @SuppressWarnings("unused")
    private static RankMobility fromValue(int value) {
        for (RankMobility r : RankMobility.values()) {
            if (r.getValue() == value) {
                return r;
            }
        }

        return null;
    }

    /**
     * Gets the integer value of the enum.
     *
     * @return the integer value
     */
    public int getValue() { return ordinal(); }
}

