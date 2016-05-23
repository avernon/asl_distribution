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

import java.util.Random;

import org.alljoyn.bus.AboutKeys;
import org.allseen.lsf.sdk.manager.AboutManager;

/**
 * Provides a base class for developers to extend or use directly to define the application and device
 * specific properties for the LightingController. This class can be instantiated and passed directly
 * to the LightingController without modification. Developers can override only the functions they wish
 * to change.
 * <p>
 * <b>Note: All parameters are set using hard coded values EXCEPT the absolute save path which must be
 * passed in to the constructor.</b>
 * <p>
 * <b>Note: Once implemented, the subclass must be registered with the LightingController using the
 * {@link LightingController#init(LightingControllerConfiguration) init} method.</b>
 * <p>
 * An example usage of a LightingControllerConfigurationBase can be found in the LSFTutorial project.
 */
public class LightingControllerConfigurationBase implements LightingControllerConfiguration {

    private final String keystorePath;

    /**
     * Constructs a LightingControllerConfigurationBase using the provided path.
     *
     * @param keystorePath Absolute path used by the LightingController to save files
     */
    public LightingControllerConfigurationBase(String keystorePath) {
        this.keystorePath = keystorePath;
    }

    /**
     * Returns the file location to save LighingController specific files.
     *
     * @return Absolute directory path to be used for file storage.
     */
    @Override
    public String getKeystorePath() {
        return this.keystorePath;
    }

    /**
     * Populate the AllJoyn AboutData parameter with device specific about data. The about
     * data will be used by the LighingController.
     *
     * @param aboutData Reference to AllJoyn AboutData
     */
    @Override
    public void populateDefaultProperties(AboutData aboutData) {
        byte[] randomAppID = new byte[16];
        Random random = new Random();

        random.nextBytes(randomAppID);

        String hexString = AboutManager.bytesToHexString(randomAppID).replaceAll("\\s", "");
        String deviceName = "LightingC-" + hexString.substring(hexString.length() - 5);

        aboutData.put(AboutKeys.ABOUT_APP_ID, randomAppID);
        aboutData.put(AboutKeys.ABOUT_DATE_OF_MANUFACTURE, "10/1/2199");
        aboutData.put(AboutKeys.ABOUT_DEFAULT_LANGUAGE, "en");
        aboutData.put(AboutKeys.ABOUT_HARDWARE_VERSION, "355.499. b");
        aboutData.put(AboutKeys.ABOUT_MODEL_NUMBER, "LSF-SDK-CS");
        aboutData.put(AboutKeys.ABOUT_SOFTWARE_VERSION, "12.20.44 build 44454");
        aboutData.put(AboutKeys.ABOUT_SUPPORT_URL, "http://www.company_a.com");

        aboutData.put(AboutKeys.ABOUT_SUPPORTED_LANGUAGES, new String[] {"en, de-AT"});
        aboutData.put(AboutKeys.ABOUT_APP_NAME, "LightingControllerService", "en");
        aboutData.put(AboutKeys.ABOUT_APP_NAME, "LightingControllerService", "de-AT");
        aboutData.put(AboutKeys.ABOUT_DESCRIPTION, "Controller Service", "en");
        aboutData.put(AboutKeys.ABOUT_DESCRIPTION, "Controller Service", "de-AT");
        aboutData.put(AboutKeys.ABOUT_DEVICE_NAME, deviceName, "en");
        aboutData.put(AboutKeys.ABOUT_DEVICE_NAME, deviceName, "de-AT");
        aboutData.put(AboutKeys.ABOUT_MANUFACTURER, "Company A (EN)", "en");
        aboutData.put(AboutKeys.ABOUT_MANUFACTURER, "Firma A (DE-AT)", "de-AT");
    }

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
    @Override
    public String getMacAddress(String generatedMacAddress) {
        return generatedMacAddress;
    }

    /**
     * Determines if their is a network available for LightingController to connect.
     *
     * @return Return true their is a network available for the controller, false otherwise.
     */
    @Override
    public boolean isNetworkConnected() {
        return true;
    }

    /**
     * Returns the mobility capability of the device running the LightingController. The mobility
     * capability is used to determine the controllers rank.
     *
     * @return LightingController RankMobility
     */
    @Override
    public RankPower getRankPower() {
        return RankPower.BATTERY_POWERED_CHARGABLE;
    }

    /**
     * Returns the power capability of the device running the LightingController. The power
     * capability is used to determine the controllers rank.
     *
     * @return LightingController RankPower
     */
    @Override
    public RankMobility getRankMobility() {
        return RankMobility.HIGH_MOBILITY;
    }

    /**
     * Returns the availability capability of the device running the LightingController. The availability
     * capability is used to determine the controllers rank.
     *
     * @return LightingController RankAvailability
     */
    @Override
    public RankAvailability getRankAvailability() {
        return RankAvailability.SIX_TO_NINE_HOURS;
    }

    /**
     * Returns the type of the device running the LightingController. The node type is used to determine
     * the controllers rank.
     *
     * @return LightingController RankNodeType
     */
    @Override
    public RankNodeType getRankNodeType() {
        return RankNodeType.WIRELESS;
    }
}
