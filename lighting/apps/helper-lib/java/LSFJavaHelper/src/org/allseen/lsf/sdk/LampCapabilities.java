/* Copyright (c) AllSeen Alliance. All rights reserved.
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
 * This class represents the current capabilities of a lamp or group in the Lighting system.
 * Such capabilities include: dimmable, color, and color temperature. For groups, if at least
 * one lamp in the group supports dimming, color, or color temperature, the capability will
 * be set to true.
 */
public class LampCapabilities extends org.allseen.lsf.sdk.model.LampCapabilities {

    /**
     * Default lamp capabilities all set to true.
     */
    public static final LampCapabilities allCapabilities = new LampCapabilities(true, true, true);

    /**
     * Default constructor for a LampCapabilities object.
     */
    public LampCapabilities() {
        super();
    }

    /**
     * Constructs a LampCapabilites object.
     *
     * @param dimmable Boolean true if your lamp is dimmable
     * @param color Boolean true if your lamp supports colors
     * @param temp Boolean true if your lamp supports color temperature
     */
    public LampCapabilities(boolean dimmable, boolean color, boolean temp) {
        super(dimmable, color, temp);
    }

    /**
     * Constructs a LampCapabilities object using the provided LampCapabilities object.
     *
     * @param that A LampCapabilities object
     */
    public LampCapabilities(org.allseen.lsf.sdk.model.LampCapabilities that) {
        super(that);
    }
}
