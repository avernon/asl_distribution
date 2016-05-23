/*
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

import org.allseen.lsf.sdk.RankAvailability;
import org.allseen.lsf.sdk.RankMobility;
import org.allseen.lsf.sdk.RankNodeType;
import org.allseen.lsf.sdk.RankPower;

/**
 * Provides an interface for developers to implement and define the application and device
 * specific properties for the lighting controller. This includes AllJoyn keystore file path,
 * AllJoyn about properties, device MAC address, and other device specific properties.
 * <p>
 * <b>Note: Once implemented, the configuration must be registered with the LightingController
 * using the {@link LightingController#init(LightingControllerConfiguration) init} method.</b>
 */
public interface LightingControllerConfiguration {

    /**
     * Returns the file location to save LighingController specific files.
     *
     * @return Absolute directory path to be used for file storage.
     */
    public String getKeystorePath();

    /**
     * Populate the AllJoyn AboutData parameter with device specific about data. The about
     * data will be used by the LighingController.
     *
     * @param aboutData Reference to AllJoyn AboutData
     */
    public void populateDefaultProperties(AboutData aboutData);

    /**
     * Returns the MAC address of the device running the LightingController.
     * <p>
     * <b>Note: The MAC address is expected to be a 12-digit hex string (i.e. "XXXXXXXXXXXX").</b>
     *
     * @param generatedMacAddress
     *             Random hex string which can be used as the MAC address on devices where it cannot
     *             be queried.
     *
     * @return The 12-digit HEX string MAC address of the device
     */
    public String getMacAddress(String generatedMacAddress);

    /**
     * Determines if their is a network available for LightingController to connect.
     *
     * @return Return true their is a network available for the controller, false otherwise.
     */
    public boolean isNetworkConnected();

    /**
     * Returns the mobility capability of the device running the LightingController. The mobility
     * capability is used to determine the controllers rank.
     *
     * @return LightingController RankMobility
     */
    public RankMobility getRankMobility();

    /**
     * Returns the power capability of the device running the LightingController. The power
     * capability is used to determine the controllers rank.
     *
     * @return LightingController RankPower
     */
    public RankPower getRankPower();

    /**
     * Returns the availability capability of the device running the LightingController. The availability
     * capability is used to determine the controllers rank.
     *
     * @return LightingController RankAvailability
     */
    public RankAvailability getRankAvailability();

    /**
     * Returns the type of the device running the LightingController. The node type is used to determine
     * the controllers rank.
     *
     * @return LightingController RankNodeType
     */
    public RankNodeType getRankNodeType();
}
