/*******************************************************************************
 *  Copyright AllSeen Alliance. All rights reserved.
 *
 *     Contributed by Qualcomm Connected Experiences, Inc.,
 *     with authorization from the AllSeen Alliance, Inc.
 *     
 *     Licensed under the Apache License, Version 2.0 (the "License");
 *     you may not use this file except in compliance with the License.
 *     You may obtain a copy of the License at
 *     
 *         http://www.apache.org/licenses/LICENSE-2.0
 *     
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 *     
 *     Pursuant to Section 1 of the License, the work of authorship constituting
 *     a Work and any Contribution incorporated in the Work shall mean only that
 *     Contributor's code submissions authored by that Contributor.  Any rights
 *     granted under the License are conditioned upon acceptance of these
 *     clarifications.
 *******************************************************************************/
package org.alljoyn.validation.simulator;

import java.util.HashMap;
import java.util.Map;

import org.alljoyn.about.AboutKeys;

public class SimpleDeviceDetails extends DeviceDetails
{

    private String manufacturerName = "Manufacturer Name";
    private String appName = "DUTSimulator App";
    private String description = "Device description";

    public SimpleDeviceDetails()
    {
        this("Manufacturer Name", "DUTSimulator App", "Device description", defaultDeviceName);
    }

    public SimpleDeviceDetails(String manufacturerName, String appName, String description, String deviceName)
    {
        this.manufacturerName = manufacturerName;
        this.appName = appName;
        this.description = description;
        defaultDeviceName = deviceName;

        setDefaultLanguage(defaultLang);
        setDeviceName(deviceName);

        Map<String, String> languageMap = new HashMap<String, String>();
        languageMap.put(AboutKeys.ABOUT_APP_NAME, appName);
        languageMap.put(AboutKeys.ABOUT_MANUFACTURER, manufacturerName);
        languageMap.put(AboutKeys.ABOUT_DESCRIPTION, description);

        addLanguageMap("en", languageMap);

    }

    public String getAppName()
    {
        return appName;
    }

    @Override
    public Map<String, Object> getAnnounceMap()
    {
        Map<String, Object> announceMap = super.getAnnounceMap();
        announceMap.put(AboutKeys.ABOUT_APP_NAME, appName);
        announceMap.put(AboutKeys.ABOUT_MANUFACTURER, manufacturerName);
        return announceMap;
    }

    @Override
    public Map<String, Object> getAbout(String languageTag)
    {
        Map<String, Object> aboutMap = super.getAbout(languageTag);

        if (aboutMap != null)
        {
            aboutMap.put(AboutKeys.ABOUT_APP_NAME, appName);
            aboutMap.put(AboutKeys.ABOUT_MANUFACTURER, manufacturerName);
            aboutMap.put(AboutKeys.ABOUT_DESCRIPTION, description);
        }
        return aboutMap;
    }

}
