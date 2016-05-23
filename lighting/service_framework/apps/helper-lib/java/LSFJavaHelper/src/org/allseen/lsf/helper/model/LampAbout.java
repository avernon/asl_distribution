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
package org.allseen.lsf.helper.model;

import java.util.Map;

import org.alljoyn.about.AboutKeys;
import org.alljoyn.bus.Variant;
import org.allseen.lsf.helper.manager.AboutManager;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class LampAbout {
    public static String dataNotFound = "-";

    // Announced data
    public String aboutDeviceID;
    public String aboutAppID;
    public String aboutDeviceName;
    public String aboutDefaultLanguage;
    public String aboutAppName;
    public String aboutManufacturer;
    public String aboutModelNumber;

    // Queried data
    public String aboutDescription;
    public String aboutDateOfManufacture;
    public String aboutSoftwareVersion;
    public String aboutHardwareVersion;
    public String aboutSupportUrl;

    public LampAbout() {
        aboutDeviceID = dataNotFound;
        aboutAppID = dataNotFound;
        aboutDeviceName = dataNotFound;
        aboutDefaultLanguage = dataNotFound;
        aboutAppName = dataNotFound;
        aboutManufacturer = dataNotFound;
        aboutModelNumber = dataNotFound;

        aboutDescription = dataNotFound;
        aboutDateOfManufacture = dataNotFound;
        aboutSoftwareVersion = dataNotFound;
        aboutHardwareVersion = dataNotFound;
        aboutSupportUrl = dataNotFound;
    }

    public void setAnnouncedData(Map<String, Variant> announcedData) {
        if (announcedData != null) {
            aboutDeviceID = AboutManager.getStringFromAnnounceData(AboutKeys.ABOUT_DEVICE_ID, announcedData, dataNotFound);
            aboutAppID = AboutManager.getByteArrayHexStringFromAnnounceData(AboutKeys.ABOUT_APP_ID, announcedData, dataNotFound);
            aboutDeviceName = AboutManager.getStringFromAnnounceData(AboutKeys.ABOUT_DEVICE_NAME, announcedData, dataNotFound);
            aboutDefaultLanguage = AboutManager.getStringFromAnnounceData(AboutKeys.ABOUT_DEFAULT_LANGUAGE, announcedData, dataNotFound);
            aboutAppName = AboutManager.getStringFromAnnounceData(AboutKeys.ABOUT_APP_NAME, announcedData, dataNotFound);
            aboutManufacturer = AboutManager.getStringFromAnnounceData(AboutKeys.ABOUT_MANUFACTURER, announcedData, dataNotFound);
            aboutModelNumber = AboutManager.getStringFromAnnounceData(AboutKeys.ABOUT_MODEL_NUMBER, announcedData, dataNotFound);
        }
    }

    public void setQueriedData(Map<String, Object> queriedData) {
        if (queriedData != null) {
            aboutDescription = AboutManager.getStringFromAboutData(AboutKeys.ABOUT_DESCRIPTION, queriedData, dataNotFound);
            aboutDateOfManufacture = AboutManager.getStringFromAboutData(AboutKeys.ABOUT_DATE_OF_MANUFACTURE, queriedData, dataNotFound);
            aboutSoftwareVersion = AboutManager.getStringFromAboutData(AboutKeys.ABOUT_SOFTWARE_VERSION, queriedData, dataNotFound);
            aboutHardwareVersion = AboutManager.getStringFromAboutData(AboutKeys.ABOUT_HARDWARE_VERSION, queriedData, dataNotFound);
            aboutSupportUrl = AboutManager.getStringFromAboutData(AboutKeys.ABOUT_SUPPORT_URL, queriedData, dataNotFound);
        }
    }
}
