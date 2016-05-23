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

public enum LampType {
    INVALID,
    A15,
    A17,
    A19,
    A20,
    A21,
    A23,
    AR70,
    AR111,
    B8,
    B10,
    B11,
    B13,
    BR25,
    BR30,
    BR38,
    BR40,
    BT15,
    BT28,
    BT37,
    BT56,
    C6,
    C7,
    C9,
    C11,
    C15,
    CA5,
    CA7,
    CA8,
    CA10,
    CA11,
    E17,
    E18,
    E23,
    E25,
    E37,
    ED17,
    ED18,
    ED23,
    ED28,
    ED37,
    F10,
    F15,
    F20,
    G9,
    G11,
    G12,
    G16,
    G19,
    G25,
    G30,
    G40,
    T2,
    T3,
    T4,
    T5,
    T6,
    T7,
    T8,
    T9,
    T10,
    T12,
    T14,
    T20,
    MR8,
    MR11,
    MR16,
    MR20,
    PAR14,
    PAR16,
    PAR20,
    PAR30,
    PAR36,
    PAR38,
    PAR46,
    PAR56,
    PAR64,
    PS25,
    PS35,
    R12,
    R14,
    R16,
    R20,
    R25,
    R30,
    R40,
    RP11,
    S6,
    S8,
    S11,
    S14,
    ST18,
    LASTVALUE;

    /** Static lookup, used by the native code */
    @SuppressWarnings("unused")
    private static LampType fromValue(int value) {
        for (LampType c : LampType.values()) {
            if (c.getValue() == value) {
                return c;
            }
        }

        return null;
    }

    /**
     * Gets the integer value.
     *
     * @return the integer value
     */
    public int getValue() { return ordinal(); }
}
