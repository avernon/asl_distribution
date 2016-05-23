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

/**
 * Enum describing the type of the lamp base.
 */
public enum BaseType {
    /**
     * Specifies an invalid BaseType.
     */
    INVALID,

    /**
     * Specifies a lamp base type of E5.
     */
    E5,

    /**
     * Specifies a lamp base type of E10.
     */
    E10,

    /**
     * Specifies a lamp base type of E11.
     */
    E11,

    /**
     * Specifies a lamp base type of E12.
     */
    E12,

    /**
     * Specifies a lamp base type of E14.
     */
    E14,

    /**
     * Specifies a lamp base type of E17.
     */
    E17,

    /**
     * Specifies a lamp base type of E26.
     */
    E26,

    /**
     * Specifies a lamp base type of E27.
     */
    E27,

    /**
     * Specifies a lamp base type of E29.
     */
    E29,

    /**
     * Specifies a lamp base type of E39.
     */
    E39,

    /**
     * Specifies a lamp base type of B22.
     */
    B22,

    /**
     * Specifies a lamp base type of GU10.
     */
    GU10,

    /**
     * Specifies that the BaseType is unchanged and to use the last value
     * that was received.
     */
    LASTVALUE;

    /** Static lookup, used by the native code */
    @SuppressWarnings("unused")
    private static BaseType fromValue(int value) {
        for (BaseType c : BaseType.values()) {
            if (c.getValue() == value) {
                return c;
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
