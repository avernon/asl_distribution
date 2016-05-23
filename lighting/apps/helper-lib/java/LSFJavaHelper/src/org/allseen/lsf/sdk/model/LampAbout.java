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
package org.allseen.lsf.sdk.model;

import java.util.Map;

import org.alljoyn.bus.AboutKeys;
import org.alljoyn.bus.Variant;
import org.allseen.lsf.sdk.manager.AboutManager;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class LampAbout {
    public static String dataNotFound = "-";

    public String aboutPeer;
    public short aboutPort;
    public boolean aboutQuery;

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
        aboutPeer = null;
        aboutPort = 0;
        aboutQuery = false;

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

    public LampAbout(LampAbout that) {
        this.aboutPeer = that.aboutPeer;
        this.aboutPort = that.aboutPort;
        this.aboutQuery = that.aboutQuery;

        this.aboutDeviceID = that.aboutDeviceID;
        this.aboutAppID = that.aboutAppID;
        this.aboutDeviceName = that.aboutDeviceName;
        this.aboutDefaultLanguage = that.aboutDefaultLanguage;
        this.aboutAppName = that.aboutAppName;
        this.aboutManufacturer = that.aboutManufacturer;
        this.aboutModelNumber = that.aboutModelNumber;

        this.aboutDescription = that.aboutDescription;
        this.aboutDateOfManufacture = that.aboutDateOfManufacture;
        this.aboutSoftwareVersion = that.aboutSoftwareVersion;
        this.aboutHardwareVersion = that.aboutHardwareVersion;
        this.aboutSupportUrl = that.aboutSupportUrl;
    }

    public void setAnnouncedData(String peer, short port, Map<String, Variant> announcedData) {
        if (announcedData != null) {
            aboutPeer = peer;
            aboutPort = port;

            aboutAppID = AboutManager.getByteArrayHexStringFromVariantMap(AboutKeys.ABOUT_APP_ID, announcedData, dataNotFound);
        }
    }

    public void setQueriedData(Map<String, Variant> queriedData) {
        if (queriedData != null) {
            aboutQuery = true;

            aboutDeviceID = AboutManager.getStringFromVariantMap(AboutKeys.ABOUT_DEVICE_ID, queriedData, dataNotFound);
            aboutDeviceName = AboutManager.getStringFromVariantMap(AboutKeys.ABOUT_DEVICE_NAME, queriedData, dataNotFound);
            aboutDefaultLanguage = AboutManager.getStringFromVariantMap(AboutKeys.ABOUT_DEFAULT_LANGUAGE, queriedData, dataNotFound);
            aboutAppName = AboutManager.getStringFromVariantMap(AboutKeys.ABOUT_APP_NAME, queriedData, dataNotFound);
            aboutManufacturer = AboutManager.getStringFromVariantMap(AboutKeys.ABOUT_MANUFACTURER, queriedData, dataNotFound);
            aboutModelNumber = AboutManager.getStringFromVariantMap(AboutKeys.ABOUT_MODEL_NUMBER, queriedData, dataNotFound);
            aboutDescription = AboutManager.getStringFromVariantMap(AboutKeys.ABOUT_DESCRIPTION, queriedData, dataNotFound);
            aboutDateOfManufacture = AboutManager.getStringFromVariantMap(AboutKeys.ABOUT_DATE_OF_MANUFACTURE, queriedData, dataNotFound);
            aboutSoftwareVersion = AboutManager.getStringFromVariantMap(AboutKeys.ABOUT_SOFTWARE_VERSION, queriedData, dataNotFound);
            aboutHardwareVersion = AboutManager.getStringFromVariantMap(AboutKeys.ABOUT_HARDWARE_VERSION, queriedData, dataNotFound);
            aboutSupportUrl = AboutManager.getStringFromVariantMap(AboutKeys.ABOUT_SUPPORT_URL, queriedData, dataNotFound);
        }
    }
}
