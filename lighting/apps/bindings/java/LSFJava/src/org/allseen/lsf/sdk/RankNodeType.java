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
 * Enum describing how the device running the controller service connects to the network.
 */
public enum RankNodeType {
    /**
     * Indicates device is connected to the access point over a wireless link
     */
    WIRELESS,
    /**
     * Indicates device is connected to the access point over a wired link
     */
    WIRED,

    /**
     * Indicates device running the Controller Service is the access point itself
     */
    ACCESS_POINT,

    /**
     * If OEMs return this value, the Controller Service will use WIRELESS as this is not a valid value
     */
    OEM_CS_RANKPARAM_NODETYPE_LAST_VALUE;

    /** Static lookup, used by the native code */
    @SuppressWarnings("unused")
    private static RankNodeType fromValue(int value) {
        for (RankNodeType r : RankNodeType.values()) {
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

